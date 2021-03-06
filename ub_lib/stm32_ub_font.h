//--------------------------------------------------------------
// File     : stm32_ub_Font.h
//--------------------------------------------------------------

//--------------------------------------------------------------
#ifndef __STM32F4_UB_FONT_H
#define __STM32F4_UB_FONT_H

//--------------------------------------------------------------
// Includes
//--------------------------------------------------------------
#include <stdint.h>

//--------------------------------------------------------------
// Структура шрифта одного размера (не более 16 пикселей шириной)
//-------------------------------------------------------------- 
typedef struct UB_Font_t
{
  uint16_t width;        // Ширина символа (в пикселях)
  uint16_t height;       // Высота символа (в пикселях)
  const uint16_t *table; // Таблица с данными
} UB_Font;


//--------------------------------------------------------------
// Структура шрифта одного размера (неболее 32 пикселей шириной)
//--------------------------------------------------------------
typedef struct UB_Font32_t
{
  uint16_t width;        // Ширина символа (в пикселях)
  uint16_t height;       // Высота символа (в пикселях)
  const uint32_t *table; // Таблица с данными
} UB_Font32;


//--------------------------------------------------------------
// Структура пропорционального шрифта (не более 16 пикселей шириной)
//--------------------------------------------------------------
typedef struct UB_pFont16_t
{
  uint16_t height;       // Высота символа (в пикселях)
  uint16_t first_char;   // Первый символ  (Ascii код)
  uint16_t last_char;    // Последний символ (Ascii код)
  const uint16_t *table; // Таблица с данными
} UB_pFont;


//--------------------------------------------------------------
// Структура пропорционального шрифта (не более 32 пикселей шириной)
//--------------------------------------------------------------
typedef struct UB_pFont32_t
{
  uint16_t height;       // Высота символа (в пикселях)
  uint16_t first_char;   // Первый символ  (Ascii код)
  uint16_t last_char;    // Последний символ (Ascii код)
  const uint32_t *table; // Таблица с данными
} UB_pFont32;


//--------------------------------------------------------------
// Активация различных шрифтов
// (Неиспользуемое закоментировать)
// Для всех используемых шрифтов должны быть соответствующие С-файлы
// которые необходимо подключить в CooCox-IDE
//--------------------------------------------------------------
// Символы одной ширины
#include  "Arial_7x10.h"
//extern UB_Font Arial_10x15;
//extern UB_Font Arial_11x18;
//extern UB_Font Arial_13x19;
//extern UB_Font Arial_14x22;
//extern UB_Font Arial_16x25;
//#include "Arial_18x27.h"
// Пропорциональные символы
#include "Font_5x8.h"
extern UB_pFont Arial_8x13;
extern UB_pFont pLcd_4x6;
extern UB_pFont pArial_10;
extern UB_pFont pArial_13;
extern UB_pFont pComic_12;
extern UB_pFont pComic_16;
extern UB_pFont pTimes_12;
extern UB_pFont pTimes_15;
extern UB_pFont pDigital_7_28;
//----------------------------------------------
extern UB_pFont32 pDejaVu_Sans_19;
extern UB_pFont32 pDejaV_21;
extern UB_pFont32 pArial_21;
extern UB_pFont32 pComic_19;
extern UB_pFont32 pTimes_18;


//--------------------------------------------------------------
// Глобальная функция
//--------------------------------------------------------------
uint16_t UB_Font_WidthPChar16(uint8_t ascii, UB_pFont *font);
uint16_t UB_Font_DrawPChar16(int16_t x, int16_t y, uint8_t ascii, UB_pFont *font, uint16_t fg, uint16_t bg);
uint16_t UB_Font_DrawPString16(int16_t x, int16_t y,char *ptr, UB_pFont *font, uint16_t fg, uint16_t bg);

uint16_t UB_Font_WidthPChar32(uint8_t ascii, UB_pFont32 *font);
uint16_t UB_Font_DrawPChar32(int16_t x, int16_t y, uint8_t ascii, UB_pFont32 *font, uint16_t fg, uint16_t bg);
uint16_t UB_Font_DrawPString32(int16_t x, int16_t y,char *ptr, UB_pFont32 *font, uint16_t fg, uint16_t bg);

//--------------------------------------------------------------
#endif // __STM32F4_UB_FONT_H
