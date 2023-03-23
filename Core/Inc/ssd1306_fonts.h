#include <stdint.h>

#ifndef __SSD1306_FONTS_H__
#define __SSD1306_FONTS_H__

typedef struct {
	const uint8_t FontWidth;    /*!< Font width in pixels */
	uint8_t FontHeight;   /*!< Font height in pixels */
	const uint16_t *data; /*!< Pointer to data font data array */
} FontDef;

extern FontDef Font_6x8;
extern FontDef Font_7x10;
extern FontDef Font_11x18;
extern FontDef Font_16x26;
extern FontDef Font_7x10_2;
extern const uint8_t c_chSingal816[16];

extern const uint8_t w4[104];
extern const uint8_t w3[104];
extern const uint8_t w2[104];
extern const uint8_t w1[104];
extern const uint8_t w0[104];
extern const uint8_t line[16];
extern const uint8_t Splash[1024];


extern const uint8_t c_chBat816[16];

#endif // __SSD1306_FONTS_H__
