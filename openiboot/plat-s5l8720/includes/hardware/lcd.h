#ifndef HW_LCD_H
#define HW_LCD_H

// Device
#define LCD 0x38900000
//#define LCD_I2C_BUS 0

// Registers
#define LCD_0 0x0
#define LCD_CON 0x4
#define LCD_CON2 0x8
#define WND_CON 0x20
#define VIDCON0 0x200
#define VIDCON1 0x204
#define VIDTCON0 0x20C
#define VIDTCON1 0x210
#define VIDTCON2 0x214
#define VIDTCON3 0x218

// Values
#define VIDCON0_INTERNALCLOCK 0
#define VIDCON0_DISPLAYCLOCK 1
#define VIDCON0_BUSCLOCK 2
#define VIDCON0_CLOCKMASK 0x3
#define VIDCON0_CLOCKSHIFT 6
#define VIDCON0_OPTION4MASK 0x3
#define VIDCON0_OPTION4SHIFT 4
#define VIDCON0_OTFCLOCKDIVISORMASK 0xF
#define VIDCON0_OTFCLOCKDIVISORSHIFT 8
#define VIDCON0_ENVID_F 1
#define VIDCON1_IVCLKSHIFT 3
#define VIDCON1_IHSYNCSHIFT 2
#define VIDCON1_IVSYNCSHIFT 1
#define VIDCON1_IVDENSHIFT 0
#define VIDTCON_BACKPORCHSHIFT 16
#define VIDTCON_BACKPORCHMASK 0xFF
#define VIDTCON_FRONTPORCHSHIFT 8
#define VIDTCON_FRONTPORCHMASK 0xFF
#define VIDTCON_SYNCPULSEWIDTHSHIFT 0
#define VIDTCON_SYNCPULSEWIDTHMASK 0xFF
#define VIDTCON2_LINEVALMASK 0x3FF
#define VIDTCON2_LINEVALSHIFT 0
#define VIDTCON2_HOZVALMASK 0x3FF
#define VIDTCON2_HOZVALSHIFT 16

#define GET_HSTATUS(x) GET_BITS(x, 4, 2);
#define GET_VSTATUS(x) GET_BITS(x, 6, 2);
#define GET_LINECNT(x) GET_BITS(x, 8, 9);
#define LCD_CLOCKGATE1 0x7
#define LCD_CLOCKGATE2 0x1D

#define LCD_GPIO_MPL_RX_ENABLE_IPHONE_2G 0x1804
#define LCD_GPIO_MPL_RX_ENABLE_IPOD 0x607
#define LCD_GPIO_MPL_RX_ENABLE_IPHONE_3G 0x0
#define LCD_GPIO_MPL_RX_ENABLE_IPHONE_4G 0x0 // No!

#define LCD_GPIO_RESET 0x1
#define LCD_GPIO_POWER_ENABLE 0x2
#define LCD_GPIO_PIXEL_CLOCK_ENABLE 0x3
#define LCD_GPIO_CONTROL_ENABLE 0x304

#define LCD_GPIO_CONFIG1 0xE04
#define LCD_GPIO_CONFIG2 0xE05
#define LCD_GPIO_CONFIG3 0xE06

#ifdef CONFIG_IPOD_TOUCH_1G
#define LCD_GPIO_MPL_RX_ENABLE LCD_GPIO_MPL_RX_ENABLE_IPOD
#endif
#ifdef CONFIG_IPHONE_2G
#define LCD_GPIO_MPL_RX_ENABLE LCD_GPIO_MPL_RX_ENABLE_IPHONE_2G
#endif
#ifdef CONFIG_IPHONE_3G
#define LCD_GPIO_MPL_RX_ENABLE LCD_GPIO_MPL_RX_ENABLE_IPHONE_3G
#endif
#if defined(CONFIG_IPHONE_4) || defined(CONFIG_IPAD_1G)
#define LCD_GPIO_MPL_RX_ENABLE LCD_GPIO_MPL_RX_ENABLE_IPHONE_4G
#endif

//TODO: fix this up
#ifdef CONFIG_IPOD_TOUCH_2G
#define LCD_GPIO_MPL_RX_ENABLE LCD_GPIO_MPL_RX_ENABLE_IPHONE_4G
#endif

#define LCD_GPIO_IPHONE_3G_ENABLE 0xE01

#ifdef CONFIG_IPHONE_3G
#define LCD_PANEL_SPI 0
#define LCD_PANEL_CS GPIO_SPI0_CS1
#define LCD_SPI 0
#define LCD_CS GPIO_SPI0_CS2
#else
#define LCD_PANEL_SPI 1
#define LCD_PANEL_CS GPIO_SPI1_CS0
#define LCD_SPI 0
#define LCD_CS GPIO_SPI0_CS0
#endif

#define LCD_I2C_COMMAND 0x31
#define LCD_I2C_COMMANDMODE_ON 0x35
#define LCD_I2C_COMMANDMODE_OFF 0x15

#define NUM_WINDOWS 3

#define LCD_MAX_BACKLIGHT 245
#define LCD_BACKLIGHT_REG 0x30
#define LCD_BACKLIGHT_REGMASK 0xFF

#endif

