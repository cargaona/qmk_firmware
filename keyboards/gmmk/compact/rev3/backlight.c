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

#include "SPI.h"

#define SDB     B0

extern void SPI0_Flush(void);

#ifdef VIA_OPENRGB_HYBRID
uint8_t is_orgb_mode;
#endif
static int g_cs_pin = 0;

void spi_init(void)
{
    SPI0_Init();
    SPI0_Enable();
}

void spi_set_cspin(int pin)
{   
    if (g_cs_pin == pin)
        return;

    writePinHigh(B2); 
    setPinOutput(B2);    
    writePinHigh(B1); 
    setPinOutput(B1);

    g_cs_pin = pin;
}

extern void SPI0_Read3(unsigned char b1, unsigned char b2, unsigned char *b3);

void spi_read3(unsigned char b1, unsigned char b2, unsigned char *b3)
{    
    writePinLow(g_cs_pin);    
    SPI0_Read3(b1, b2, b3);    
    writePinHigh(g_cs_pin);
}


void spi_write(uint8_t *data_p, int len)
{    
    writePinLow(g_cs_pin);    
    SPI0_Write(data_p, len);
    SPI0_Flush();
    writePinHigh(g_cs_pin);
}

void spi_w3(uint8_t page, uint8_t addr, uint8_t data)
{
    uint8_t c[4];
    c[0] = page | 0x20;
    c[1] = addr;
    c[2] = data;
    spi_write(c, 3);
}

void spi_r3(uint8_t page, uint8_t addr, uint8_t *data)
{
    uint8_t c[4];
    c[0] = page | 0x20;
    c[1] = addr;    
    spi_read3(c[0], c[1], data);
}

/* 
 * LED index to RGB address
 * >100 means it belongs to pin B1 chipselected SN2735 chip, the real addr is minus by 100 
 */

/* ANSI */
static const uint8_t g_led_pos[DRIVER_LED_TOTAL] = {
/*  0 */ 100, 101, 102, 103, 104, 105, 106, 107, 108, 109,  110, 111, 112, 113, 
/* 14 */ 116, 117, 118, 119, 120, 121, 122, 123, 124, 125,  126, 127, 128, 129,
/* 28 */ 132, 133, 134, 135, 136, 137, 138, 139, 140, 141,  142, 143, 145,   
/* 41 */ 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158,  159, 161,
/* 53 */ 114, 115, 130, 131, 146, 147, 162, 163
};

static void _set_color_direct(int index, uint8_t r, uint8_t g, uint8_t b)
{
    int l = g_led_pos[index];

    if (l >= 100)
    {
        l -= 100;
        spi_set_cspin(B1);
    }
    else
        spi_set_cspin(B2);

    int y = l / 16;
    int a = l % 16;
            
    spi_w3(1, y * 48 + a, r);       // r
    spi_w3(1, y * 48 + a + 2*8, b); // b
    spi_w3(1, y * 48 + a + 4*8, g); // g  
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
    int l = g_led_pos[index];

    if (l >= 100)
    {
        l -= 100;
        spi_set_cspin(B1);
    }
    else
        spi_set_cspin(B2);

    int y = l / 16;
    int a = l % 16;
            
    spi_r3(1, y * 48 + a, r);       // r
    spi_r3(1, y * 48 + a + 2*8, b); // b
    spi_r3(1, y * 48 + a + 4*8, g); // g  
}

void reset_rgb(int pin)
{
    spi_set_cspin(pin);
    
    spi_w3(3, 0, 0);
    spi_w3(3, 0x13, 0xAA);
    spi_w3(3, 0x14, 0);
    // spi_w3(3, 0x15, 4);
    spi_w3(3, 0x15, 0);
    spi_w3(3, 0x16, 0xC0);
    spi_w3(3, 0x1A, 0);
    
    // set curent
    for (int i = 0; i < 12; i++)
    {
        spi_w3(4, i, 0x80);
    }               
    
    // led all on
    for (int i = 0; i < 192/8; i++)
    {
        spi_w3(0, i, 0xFF);
    }

    // turn off pwm
    for (int i = 0; i < 192; i++)
    {
        spi_w3(1, i, 0);
    }
                
    // normal mode
    spi_w3(3, 0, 1);
}

void process_backlight(uint8_t devid, volatile LED_TYPE* states)
{
    static unsigned char state = 0;       

    switch (state)
    {
        case 0: /* init RGB chips */
            spi_init();

            writePinHigh(SDB);
            setPinOutput(SDB);
            reset_rgb(B1);
            reset_rgb(B2);

            state = 1;
            break;
    }
}