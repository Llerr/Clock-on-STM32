//--------------------------------------------------------------
// File     : stm32_ub_font.c
// Datum    : 24.07.2014
// Version  : 1.5
// Autor    : UB
// EMail    : mc-4u(@)t-online.de
// Web      : www.mikrocontroller-4u.de 
// CPU      : STM32F4
// IDE      : CooCox CoIDE 1.7.4
// GCC      : 4.7 2012q4
// Module   : STM32_UB_LCD_ST7783
// Funktion : Text-LCD Funktionen
//--------------------------------------------------------------


//--------------------------------------------------------------
// Includes
//--------------------------------------------------------------
#include <stdio.h>

#include "stm32_ub_font.h"
#include "MatrixRGB.h"

//--------------------------------------------------------------
// Рисует ASCII символ шрифтом одного размера на позиции х, у.
// Цвет шрифта и фон (шрифт = макс 16 пикселей в ширину)
// Шрифт должен быть передан с оператором &
//--------------------------------------------------------------
void UB_Font_DrawChar(int16_t x, int16_t y, uint8_t ascii, UB_Font *font, uint16_t fg)
{
  uint16_t xn = 0;
  uint16_t yn = 0;
  uint16_t start_mask;
  uint16_t mask = 0;
  const uint16_t *symb;

  ascii -= 32;
  symb=&font->table[ascii * font->height];

  start_mask=0x80;
  if(font->width>8) start_mask=0x8000;

  for(yn = 0; yn < font->height; yn++)
  {
    if( (y+yn)>(MATRIX_HEIGHT-1) || (y+yn)<0  )
      continue;
    mask=start_mask;
    for(xn = 0; xn < font->width; xn++)
    {
      if( (x+xn) > (MATRIX_WIDTH-1) || (x+xn) < 0 )
        continue;
      if(symb[yn] & mask)
      {
        // Рисование пикселя шрифта
        matrix[y+yn][x+xn] = fg;
      }
      mask=(mask>>1);
    }
  }

}


//--------------------------------------------------------------
// Рисует строку шрифтом одного размера на позиции х, у.
// Цвет шрифта и фон (шрифт = макс 16 пикселей в ширину)
// Шрифт должен быть передан с оператором & 
//--------------------------------------------------------------
void UB_Font_DrawString(int16_t x, int16_t y,char *ptr, UB_Font *font, uint16_t fg)
{
  uint16_t pos = x;

  while (*ptr != 0)
  {
    UB_Font_DrawChar(pos,y,*ptr,font,fg);
    pos+=font->width;
    ptr++;
  }

}

#define DRAW32
#ifdef DRAW32
//--------------------------------------------------------------
// Рисует ASCII символ шрифтом одного размера на позиции х, у.
// Цвет шрифта и фон (шрифт = макс 32 пикселя в ширину)
// Шрифт должен быть передан с оператором & 
//--------------------------------------------------------------
void UB_Font_DrawChar32(int16_t x, int16_t y, uint8_t ascii, UB_Font32 *font, uint16_t fg)
{
  uint16_t xn;
  uint16_t yn;
  uint32_t start_mask;
  uint32_t mask;
  const uint32_t *symb;

  start_mask=0x80;
  if(font->width>8) start_mask=0x8000;
  if(font->width>16) start_mask=0x80000000;
  printf("[%d, %d]\n",x, y);
  ascii -= 32;
  symb=&font->table[ascii * font->height];

  for(yn = 0; yn < font->height; yn++)
  {
    if( (y+yn)>(MATRIX_HEIGHT-1) || (y+yn)<0  )
      continue;
    mask=start_mask;
    for(xn = 0; xn < font->width; xn++)
    {
      if( (x+xn) > (MATRIX_WIDTH-1) || (x+xn) < 0 )
        continue;
      if(symb[yn] & mask)
      {
        // Рисование пикселя шрифта
        matrix[y+yn][x+xn] = fg;
      }
      mask=(mask>>1);
    }
  }
}


//--------------------------------------------------------------
// Рисует строку шрифтом одного размера на позиции х, у.
// Цвет шрифта и фон (шрифт = макс 32 пикселя в ширину)
// Шрифт должен быть передан с оператором & 
//--------------------------------------------------------------
void UB_Font_DrawString32(int16_t x, int16_t y,char *ptr, UB_Font32 *font, uint16_t fg)
{
  uint16_t pos = x;

  while (*ptr != 0)
  {
    UB_Font_DrawChar32(pos,y,*ptr,font,fg);
    pos+=font->width;
    ptr++;
  }
}
#endif //DRAW32

//--------------------------------------------------------------
// Рисование ASCII символ пропорционального шрифта с позицией X, Y
// Цвет шрифта плана и фона (шрифт = макс 16 пикселей в ширину)
// Шрифт должен быть передан с оператором & 
// Возвращает: ширину нарисованного символа
//--------------------------------------------------------------
uint16_t UB_Font_DrawPChar(int16_t x, int16_t y, uint8_t ascii, UB_pFont *font, uint16_t fg)
{
  uint16_t xn=0;
  uint16_t yn=0;
  uint16_t start_mask=0;
  uint16_t mask=0;
  uint16_t width=0;
  const uint16_t *symb;

  // Проверка границы символа
  if(ascii<font->first_char) return 0;
  if(ascii>font->last_char) return 0;

  ascii -= font->first_char;
  symb=&font->table[ascii * (font->height+1)];
  width=symb[0];

  start_mask=0x80;
  if(width>8) start_mask<<=8;
//  printf("Width: %d", width);
  for(yn = 0; yn < font->height; yn++)
  {
    if( (y+yn)>(MATRIX_HEIGHT-1) || (y+yn)<0  )
      continue;
    mask=start_mask;
//    printf("%02X, \n", symb[yn+1]);
    // Установка курсора
    for(xn = 0; xn < width; xn++)
    {
//      printf("0x%02X|", mask);
      if( (x+xn) > (MATRIX_WIDTH-1) || (x+xn) < 0 )
        continue;
      if(symb[yn+1] & mask)
      {
        // Рисование пикселя шрифта
        matrix[y+yn][x+xn] = fg;
      }
      mask=(mask>>1);
    }
  }
//  printf("\n");
  return width;
}


//--------------------------------------------------------------
// Рисование строки пропорционального шрифта с позицией X, Y
// Цвет шрифта плана и фона (шрифт = макс 16 пикселей в ширину)
// Шрифт должен быть передан с оператором & 
//--------------------------------------------------------------
void UB_Font_DrawPString(int16_t x, int16_t y,char *ptr, UB_pFont *font, uint16_t fg)
{
  uint16_t pos = x;
  uint16_t width=0;

  while (*ptr != 0)
  {
    width=UB_Font_DrawPChar(pos,y,*ptr,font,fg);
    pos+=width;
    ptr++;
  }
}

//--------------------------------------------------------------
// Рисование ASCII символ пропорционального шрифта с позицией X, Y
// Цвет шрифта плана и фона (шрифт = макс 32 пикселя в ширину)
// Шрифт должен быть передан с оператором & 
// Возвращает: ширину нарисованного символа
//--------------------------------------------------------------
uint16_t UB_Font_DrawPChar32(int16_t x, int16_t y, uint8_t ascii, UB_pFont32 *font, uint16_t fg)
{
  uint16_t xn;
  uint16_t yn;
  uint16_t width;
  uint32_t start_mask;
  uint32_t mask;
  const uint32_t *symb;

  // Проверка границы символа
  if(ascii<font->first_char) return 0;
  if(ascii>font->last_char) return 0;
  printf("symb: %c [%d],", ascii, ascii);
  ascii -= font->first_char;
  symb=&font->table[ascii * (font->height+1)];
  width=symb[0];

  start_mask=0x80;
  start_mask=start_mask<<((width/8)*8);
  printf("Width: %d[%d], start mask: %lX\n", width, (width/8)*8, start_mask);

  for(yn = 0; yn < font->height; yn++)
  {
    if( (y+yn)>(MATRIX_HEIGHT-1) || (y+yn)<0  )
      continue;
    mask=start_mask;
    for(xn = 0; xn < width; xn++)
    {
      if( (x+xn) > (MATRIX_WIDTH-1) || (x+xn) < 0 )
        continue;
      if(symb[yn+1] & mask)
      {
        // Рисование пикселя шрифта
        matrix[y+yn][x+xn] = fg;
      }
      mask=(mask>>1);
    }
  }

  return width;
}


//--------------------------------------------------------------
// Рисование строку пропорционального шрифта с позицией X, Y
// Цвет шрифта плана и фона (шрифт = макс 32 пикселя в ширину)
// Шрифт должен быть передан с оператором & 
//--------------------------------------------------------------
void UB_Font_DrawPString32(int16_t x, int16_t y,char *ptr, UB_pFont32 *font, uint16_t fg)
{
  uint16_t pos = x;
  uint16_t width = 0;


  while (*ptr != 0)
  {
    width=UB_Font_DrawPChar32(pos,y,*ptr,font,fg);
    pos+=width;
    ptr++;
  }
}
//--------------------------------------------------------*/
