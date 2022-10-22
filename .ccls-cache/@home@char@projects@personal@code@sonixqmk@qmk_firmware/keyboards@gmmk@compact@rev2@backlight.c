#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <SN32F260.h>
#include "ch.h"
#include "hal.h"
#include "color.h"
#include "wait.h"
#include "util.h"
#include "matrix.h"
#include "debounce.h"
#include "quantum.h"

#define I2C_SCL C1
#define I2C_SDA C2

#define I2C_SCL_IN readPin(I2C_SCL)
#define I2C_SDA_IN readPin(I2C_SDA)
#define I2C_SDB C0

#define I2C_SCL_HI  do { setPinOutput(I2C_SCL); writePinHigh(I2C_SCL); } while (0)
#define I2C_SCL_LO  do { setPinOutput(I2C_SCL); writePinLow(I2C_SCL); } while (0)
#define I2C_SCL_HIZ do { setPinInputHigh(I2C_SCL); } while (0)

#define I2C_SDA_HI  do { setPinOutput(I2C_SDA); writePinHigh(I2C_SDA); } while (0)
#define I2C_SDA_LO  do { setPinOutput(I2C_SDA); writePinLow(I2C_SDA); } while (0)
#define I2C_SDA_HIZ do { setPinInputHigh(I2C_SDA); } while (0)

/*
 * according to the spec, high SCL peroid 0.7us, low SCL peroid 1.3us
 *
 * i2c_delay 1 loop about 7 cycles. Under 48MHz, the actual delay is around 0.9us and 1.5us respectively.
 */
#define I2C_SCL_HI_DELAY    i2c_delay(2)
#define I2C_DELAY           i2c_delay(10)

static uint8_t sel_frame[2] = {0xFF, 0xFF};
static uint8_t sel_frame_idx = 0;
#ifdef VIA_OPENRGB_HYBRID
uint8_t is_orgb_mode;
#endif

static void i2c_delay(uint32_t loop)
{
    #pragma GCC unroll 0
    for (int32_t i = 0; i < loop; i++)
        SN_WDT->FEED = 0x5AFA55AA;
}

void i2c_init(void)
{   
    // drive strength all gpio A 20ma
    SN_GPIO0->MODE |= 0xFFFF0000;

    setPinOutput(I2C_SCL);
    I2C_SCL_HI;
    I2C_SDA_HI;
    I2C_SDA_HIZ;

    writePinHigh(I2C_SDB);
    setPinOutput(I2C_SDB);    
    i2c_delay(100);

}

static void i2c_process_bit(uint8_t *i2c_tx_byte)
{
    if (*i2c_tx_byte & 0x80)
    {
        I2C_SDA_HI;
    }
    else
    {
        I2C_SDA_LO;
    }

    *i2c_tx_byte = *i2c_tx_byte << 1;

    I2C_SCL_HI;
    I2C_SCL_HI_DELAY;
    I2C_SCL_LO;
    I2C_DELAY;
}

static uint8_t i2c_transaction(uint8_t i2c_addr_rw, uint8_t* i2c_data_ptr, uint8_t i2c_byte_ct)
{
    uint8_t txb;
    uint8_t fail = 0;

    /* START */
    I2C_SDA_LO;
    I2C_DELAY;
    I2C_SCL_LO;
    I2C_DELAY;

    txb = i2c_addr_rw;
    i2c_process_bit(&txb);
    i2c_process_bit(&txb);
    i2c_process_bit(&txb);
    i2c_process_bit(&txb);
    i2c_process_bit(&txb);
    i2c_process_bit(&txb);
    i2c_process_bit(&txb);
    i2c_process_bit(&txb);

    goto I2C_STATE_READ_ACK;

I2C_STATE_WRITE_BYTE:

    I2C_SDA_LO;
    I2C_SCL_LO;

    txb = *i2c_data_ptr++;
    i2c_process_bit(&txb);
    i2c_process_bit(&txb);
    i2c_process_bit(&txb);
    i2c_process_bit(&txb);
    i2c_process_bit(&txb);
    i2c_process_bit(&txb);
    i2c_process_bit(&txb);
    i2c_process_bit(&txb);

    i2c_byte_ct--;

I2C_STATE_READ_ACK:
    I2C_SDA_HIZ;
    
    I2C_SCL_HI;

    I2C_SCL_HI_DELAY;
    
    /* ignore ACK */
    fail = I2C_SDA_IN;
    
    I2C_SCL_LO;
    I2C_DELAY;

    if (i2c_byte_ct > 0)
        goto I2C_STATE_WRITE_BYTE;

    I2C_SDA_LO;
    I2C_DELAY;

    /* STOP */
    I2C_SCL_HI;
    I2C_DELAY;
    I2C_SDA_HI;
    I2C_SDA_HIZ;

    return fail;
}

static uint8_t i2c_write_buf(uint8_t devid, uint8_t* data, uint8_t len)
{
    int32_t tries = 1;
    
    while ((tries-- > 0) && i2c_transaction(devid, data, len));
    
    return 0;
}

static void i2c_write_reg(uint8_t devid, uint8_t reg, uint8_t data)
{
    uint8_t i2c_data[2];
    
    i2c_data[0] = reg;
    i2c_data[1] = data;

    i2c_write_buf(devid, i2c_data, 2);
}

static void reset_rgb(int devid)
{
    i2c_write_reg(devid, 0xFD, 0x0B);

    i2c_write_reg(devid, 0x0A, 0x00);
    i2c_write_reg(devid, 0x00, 0x00);
    i2c_write_reg(devid, 0x01, 0x10);
    i2c_write_reg(devid, 0x05, 0x00);
    i2c_write_reg(devid, 0x06, 0x00);
    i2c_write_reg(devid, 0x08, 0x00);
    i2c_write_reg(devid, 0x09, 0x00);
    i2c_write_reg(devid, 0x0B, 0x00);
    i2c_write_reg(devid, 0x0D, 0x0F);
    i2c_write_reg(devid, 0x0E, 0x01);
    i2c_write_reg(devid, 0x14, 68);
    i2c_write_reg(devid, 0x15, 128);
    i2c_write_reg(devid, 0x0F, 153);

    i2c_write_reg(devid, 0xFD, 0);
    for (int32_t i = 0; i < 0x10; i++)
        i2c_write_reg(devid, i, 0xFF);
    /* skip blink control 0x10~0x1F as reset 0 */
    for (int32_t i = 0x20; i < 0xA0; i++)
        i2c_write_reg(devid, i, 0);

    i2c_write_reg(devid, 0xFD, 1);
    for (int32_t i = 0; i < 0x10; i++)
        i2c_write_reg(devid, i, 0xFF);
    /* skip blink control 0x10~0x1F as reset 0 */
    for (int32_t i = 0x20; i < 0xA0; i++)
        i2c_write_reg(devid, i, 0);

    i2c_write_reg(devid, 0xFD, 0xB);
    i2c_write_reg(devid, 0x0A, 1);
}

/*
 * led index to RGB address
 */
static const uint8_t g_led_pos[DRIVER_LED_TOTAL] = {
/*0*/	0xC0,
/*1*/	0xC1,0xC2,0xC3,0xC4,0xC5,0xC6,0xC7,0xC8,0xC9,0xCA,0xB,0xD,0xC,
/*2*/	0x90,0x91,0x92,0x93,0x94,0x95,0x96,0x97,0x98,0x9C,0x9D,0x9E,0x9F,
/*3*/	0x60,0x61,0x62,0x63,0x64,0x65,0x69,0x6A,0x6B,0x6C,0x6D,0x6E,0xF,0x6F,
/*4*/	0x30,0x2,0x31,0x32,0x36,0x37,0x38,0x39,0x3A,0x3B,0x3C,0x3D,0x3E,
/*5*/	0x3,0x4,0x5,0x6,0x7,0x8,0x9,0xA   
};


static void set_pwm(uint8_t dev, uint8_t addr, uint8_t value)
{
    /* >=0x80 for frame 2 otherwise frame 1 */
    if (addr >= 0x80) {
        if (sel_frame[sel_frame_idx] != 1) {
            i2c_write_reg(dev, 0xFD, 1);
            sel_frame[sel_frame_idx] = 1;
        }
        addr -= 0x80;
    }
    else if (sel_frame[sel_frame_idx] != 0) {
        i2c_write_reg(dev, 0xFD, 0);
        sel_frame[sel_frame_idx] = 0;
    }

    i2c_write_reg(dev, addr + 0x20, value);
}

static void _set_color_direct(int index, uint8_t r, uint8_t g, uint8_t b)
{   
    uint8_t dev;
    int l = g_led_pos[index];

    dev = 0xEE;

    set_pwm(dev, l, r);
    set_pwm(dev, l + 0x10, g);
    set_pwm(dev, l + 0x20, b);
}

void _set_color(int index, uint8_t r, uint8_t g, uint8_t b)
{
#ifdef VIA_OPENRGB_HYBRID
    if (!is_orgb_mode && (index == 15 || index == 35 || index == 49))
        r = g = b = 255;
#endif

    _set_color_direct(index, r, g, b);
}

void _read_color(int index, uint8_t *r, uint8_t *g, uint8_t *b)
{
    *r = 0;
    *g = 0;
    *b = 0;
}

void process_backlight(uint8_t devid, volatile LED_TYPE *states)
{
    static unsigned char state = 0;

    switch (state)
    {
        case 0: /* init RGB chips */
            i2c_init();
            reset_rgb(0xEE);

            state = 1;
            break;
    }
}