# MCU name
MCU = atmega32u4

# Bootloader selection
BOOTLOADER = atmel-dfu

# Build Options
#   change yes to no to disable
#
LTO_ENABLE = yes            # Link-time optimization

# Project specific files
QUANTUM_LIB_SRC += uart.c
