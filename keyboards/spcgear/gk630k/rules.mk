# project specific files
SRC = ../../../drivers/led/sn32/matrix_sn32f24xx.c
SRC += config_led.c

# MCU name
MCU = SN32F248BF

# Build Options
#   change yes to no to disable
#
LTO_ENABLE = no

MAGIC_ENABLE = yes
MAGIC_KEYCODE_ENABLE = yes
BOOTMAGIC_ENABLE = yes		# Virtual DIP switch configuration

CONSOLE_ENABLE = no     	# Console for debug
COMMAND_ENABLE = no     	# Commands for debug and configuration

NKRO_ENABLE = yes       	# USB Nkey Rollover

MOUSEKEY_ENABLE = no    	# Mouse keys
EXTRAKEY_ENABLE = yes   	# Audio control and System control

BACKLIGHT_ENABLE = no		# Enable keyboard backlight functionality
RGBLIGHT_ENABLE = no		# Enable keyboard RGB underglow

AUDIO_ENABLE = no			# Audio output

WAIT_FOR_USB = yes
CUSTOM_MATRIX = yes
KEYBOARD_SHARED_EP = no

# Custom RGB matrix handling
RGB_MATRIX_ENABLE = yes
RGB_MATRIX_DRIVER = SN32F24xB
