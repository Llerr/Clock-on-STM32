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
  const uint16_t *table; // Таблица с данными
  uint16_t width;        // Ширина символа (в пикселях)
  uint16_t height;       // Высота символа (в пикселях)
}UB_Font;


//--------------------------------------------------------------
// Структура шрифта одного размера (неболее 32 пикселей шириной)
//--------------------------------------------------------------
typedef struct UB_Font32_t
{
  const uint32_t *table; // Таблица с данными
  uint16_t width;        // Ширина символа (в пикселях)
  uint16_t height;       // Высота символа (в пикселях)
}UB_Font32;


//--------------------------------------------------------------
// Структура пропорционального шрифта (не более 16 пикселей шириной)
//--------------------------------------------------------------
typedef struct UB_pFont_t {
  const uint16_t *table; // Таблица с данными
  uint16_t height;       // Высота символа (в пикселях)
  uint16_t first_char;   // Первый символ  (Ascii код)
  uint16_t last_char;    // Последний символ (Ascii код)
}UB_pFont;


//--------------------------------------------------------------
// Структура пропорционального шрифта (не более 32 пикселей шириной)
//--------------------------------------------------------------
typedef struct UB_pFont32_t {
  const uint32_t *table; // Таблица с данными
  uint16_t height;       // Высота символа (в пикселях)
  uint16_t first_char;   // Первый символ  (Ascii код)
  uint16_t last_char;    // Последний символ (Ascii код)
}UB_pFont32;


//--------------------------------------------------------------
// Активация различных шрифтов
// (Неиспользуемое закоментировать)
// Для всех используемых шрифтов должны быть соответствующие С-файлы
// которые необходимо подключить в CooCox-IDE
//--------------------------------------------------------------
// Символы одной ширины
extern UB_Font Font_5x8;
extern UB_Font Arial_7x10; 
extern UB_Font Arial_8x13;
extern UB_Font Arial_10x15;
extern UB_Font Arial_11x18;
extern UB_Font Arial_13x19;
extern UB_Font Arial_14x22;
extern UB_Font Arial_16x25;
extern UB_Font32 Arial_18x27;
// Пропорциональные символы
extern UB_pFont pLcd_4x6;
extern UB_pFont pArial_10;
extern UB_pFont pArial_13;
extern UB_pFont pComic_12;
extern UB_pFont pComic_16;
extern UB_pFont pTimes_12;
extern UB_pFont pTimes_15;
extern UB_pFont32 pArial_21;
extern UB_pFont32 pComic_19;
extern UB_pFont32 pTimes_18;
extern UB_pFont pDigital_7_28;
extern UB_pFont32 pDejaV_21;


//--------------------------------------------------------------
// Глобальная функция
//--------------------------------------------------------------
void UB_Font_DrawChar(int16_t x, int16_t y, uint8_t ascii, UB_Font *font, uint16_t fg);
void UB_Font_DrawString(int16_t x, int16_t y,char *ptr, UB_Font *font, uint16_t fg);
void UB_Font_DrawChar32(int16_t x, int16_t y, uint8_t ascii, UB_Font32 *font, uint16_t fg);
void UB_Font_DrawString32(int16_t x, int16_t y,char *ptr, UB_Font32 *font, uint16_t fg);
uint16_t UB_Font_DrawPChar(int16_t x, int16_t y, uint8_t ascii, UB_pFont *font, uint16_t fg);
void UB_Font_DrawPString(int16_t x, int16_t y,char *ptr, UB_pFont *font, uint16_t fg);
uint16_t UB_Font_DrawPChar32(int16_t x, int16_t y, uint8_t ascii, UB_pFont32 *font, uint16_t fg);
void UB_Font_DrawPString32(int16_t x, int16_t y,char *ptr, UB_pFont32 *font, uint16_t fg);

//--------------------------------------------------------------
#endif // __STM32F4_UB_FONT_H
