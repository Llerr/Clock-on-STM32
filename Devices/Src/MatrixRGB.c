/*
 * MatrixRGB.c
 *
 *  Created on: Feb 12, 2021
 *      Author: lex
 */
#include <stdio.h>
#include <string.h>

#include "main.h"
#include "MatrixRGB.h"
#include "Screens.h"
#include "tim.h"

uint8_t matrix[MATRIX_HEIGHT][MATRIX_WIDTH];

int stepPWM = 0;
int brightPWM = 0;

//----------------------------------------------------------------------------------------------------------------------
void initMatrix()
{
  stepPWM = htim1.Init.Period/255.0;
  calcBrightPWM();
}

//----------------------------------------------------------------------------------------------------------------------
void calcBrightPWM()
{
  brightPWM = stepPWM*curBright;
  if(0 == brightPWM) brightPWM = 1;

  TIM1->CCR1 = brightPWM;
}


//----------------------------------------------------------------------------------------------------------------------
void clearMatrix()
{
  memset(matrix[0], 0, MATRIX_SIZE);
}

//----------------------------------------------------------------------------------------------------------------------
void updateScreen()
{
  static int y = 0;
  int addr = 0;
  int x;
//  MATRX_GPIO_Port->BRR = MATRX_ADDR_Pins; // Сбросим адрес
  addr = y;
  addr = ~addr;
  addr &=0x0F;
  addr = ((addr<<6)<<16u) | (y<<6); //Установим нужные и сбросим другие биты адреса  (6 посчитано вручную
//  HAL_GPIO_WritePin(MATRIX_OE_PWM_GPIO_Port, MATRIX_OE_PWM_Pin, GPIO_PIN_SET);
  MATRX_GPIO_Port->BSRR = addr; // запишем в регистр
  //------------- ШИМ  ---------------
  TIM1->CCR1 = 0; // Установка ШИМ
  TIM1->EGR = TIM_EGR_UG;
  //-------------------------------------

  for(x = 0; x < MATRIX_WIDTH; ++x)
  {
    MATRX_GPIO_Port->BRR = MATRX_RGB_Pins;
//    MATRX_GPIO_Port->BRR = MATRX_RGB_Pins;
//    if(y%2)
//    {
    MATRX_GPIO_Port->BSRR = matrix[y][x]; //Первая половина экрана
//    MATRX_GPIO_Port->BSRR = matrix[y][x]; //Первая половина экрана
    MATRX_GPIO_Port->BSRR = matrix[y+16][x]<<3; //Вторая половина экрана
//    MATRX_GPIO_Port->BSRR = matrix[y+16][x]<<3; //Вторая половина экрана
//    }
    tick(MATRX_CLK_Pin);
  }
  //disable output
  HAL_GPIO_WritePin(MATRX_GPIO_Port, MATRX_STB_Pin, GPIO_PIN_SET);
  // Enable the display
  HAL_GPIO_WritePin(MATRX_GPIO_Port, MATRX_STB_Pin, GPIO_PIN_RESET);
  //------------ ШИМ --------------------
  /* Enable the Capture compare channel */
  TIM1->CCR1 = brightPWM; // Установка ШИМ
  TIM1->EGR = TIM_EGR_UG;
  //----------------------------------------
  ++y;
  y = (y < (MATRIX_HEIGHT/2))?y:0;
}

//----------------------------------------------------------------------------------------------------------------------
void drawPoint(int x, int y, uint16_t color)
{
  if( y > (MATRIX_HEIGHT-1) || y < 0)
    return;
  if( x > (MATRIX_WIDTH-1) || x < 0)
    return;
  if(TRANSPARENT == color) return;
  matrix[y][x] = color;
}

//----------------------------------------------------------------------------------------------------------------------
void testDraw(uint16_t x, uint16_t y)
{
  clearMatrix();
  x = (x>(MATRIX_WIDTH-1))?(MATRIX_WIDTH-1):x;
  y = (y>(MATRIX_HEIGHT-1))?(MATRIX_HEIGHT-1):y;
  printf("testDraw(%d, %d)\n", x, y);
  for(int i = 0; i < MATRIX_WIDTH; ++i)
  {
    matrix[y][i] = 7;
  }
  for(int i = 0; i < MATRIX_HEIGHT; ++i)
  {
    matrix[i][x] = 7;
  }

  matrix[y-1][x-1] = 1;
  matrix[y-1][x+1] = 2;
  matrix[y+1][x-1] = 3;
  matrix[y+1][x+1] = 4;

  matrix[y-2][x-2] = 1;
  matrix[y-2][x+2] = 2;
  matrix[y+2][x-2] = 3;
  matrix[y+2][x+2] = 4;
}

//----------------------------------------------------------------------------------------------------------------------
void dumpScreen()
{
  printf("-----------------------------------------------------------------\n");
   for(int y1 = 0; y1 < MATRIX_HEIGHT/2; ++y1)
   {
     printf("%02d: ", y1);
     for(int x1 = 0; x1 < MATRIX_WIDTH; ++x1)
     {
       printf("%d ", matrix[y1][x1]); //Первая половина экрана
//       HAL_Delay(10);
     }
     printf("\n");
   }
   printf("-----------------------------------------------------------------\n");
   for(int y1 = 0; y1 < MATRIX_HEIGHT/2; ++y1)
   {
     printf("%02d: ", y1+16);
     for(int x1 = 0; x1 < MATRIX_WIDTH; ++x1)
     {
       printf("%d ", matrix[y1+16][x1]); //Вторая половина экрана
//       HAL_Delay(10);
    }
//     HAL_Delay(10);
     printf("\n");
   }
   printf("--------------------------------------------------------------------\n");
}

//----------------------------------------------------------------------------------------------------------------------
void tick(uint16_t pin)
{
  MATRX_GPIO_Port->BSRR = pin; // Set
//  MATRX_GPIO_Port->BSRR = pin; // Set
  MATRX_GPIO_Port->BRR = pin; // reset;
//  MATRX_GPIO_Port->BRR = pin; // reset;
}

//----------------------------------------------------------------------------------------------------------------------
//void drawPointT(int x, int y)
//{
//  printf("draw(%d, %d)\n", x, y);
//  clearMatrixT();
//  y = (y==0)?32:y;
//  y = MATRIX_HEIGHT - y;
//  y = (y<0)?0:y;
//  int half = y/(MATRIX_HEIGHT/2); // Определим половину
//  y = y%(MATRIX_HEIGHT/2); // Определим смещение
//  //disable output
////  HAL_GPIO_WritePin(MATRX_GPIO_Port, MATRX_OE_Pin, GPIO_PIN_SET);
//  //--------------------------------------------------------------------------------------------------------------------
//  HAL_GPIO_WritePin(MATRX_GPIO_Port, MATRX_OE_Pin|MATRX_STB_Pin, GPIO_PIN_SET);
//  MATRX_GPIO_Port->BRR = MATRX_ADDR_Pins; // Сбросим адрес
//  MATRX_GPIO_Port->BSRR = y<<6;
//  // Shift in some data
//  if(half)
//    HAL_GPIO_WritePin(MATRX_GPIO_Port, MATRX_RGB2_Pins, GPIO_PIN_SET);
//  else
//    HAL_GPIO_WritePin(MATRX_GPIO_Port, MATRX_RGB1_Pins, GPIO_PIN_SET);
//
//  tick(MATRX_CLK_Pin);
//  HAL_GPIO_WritePin(MATRX_GPIO_Port, MATRX_RGB1_Pins, GPIO_PIN_RESET);
//  HAL_GPIO_WritePin(MATRX_GPIO_Port, MATRX_RGB2_Pins, GPIO_PIN_RESET);
//
//  for(int i = 0; i < x; ++i)
//  {
//    tick(MATRX_CLK_Pin);
//  }
////  tick(MATRX_STB_Pin);
//  tick(MATRX_STB_Pin|MATRX_OE_Pin);
//}

//----------------------------------------------------------------------------------------------------------------------
void testMatrix()
{
  printf("Test matrix\n");
  clearMatrixT();
//  HAL_GPIO_WritePin(GPIOx, GPIO_Pin, PinState);
  // Select 1 of 8 sections A, B, C, D установим в 0
//  HAL_GPIO_WritePin(MATRX_GPIO_Port, MATRX_ADDR_Pins, GPIO_PIN_RESET);
  MATRX_GPIO_Port->BRR = 15<<6;
MATRX_GPIO_Port->BSRR = 2<<6;

  //Set R1 high, clock, latch, and enable
  //disable output
  HAL_GPIO_WritePin(MATRX_GPIO_Port, MATRX_OE_Pin, GPIO_PIN_SET);

  // Shift in some data
  HAL_GPIO_WritePin(MATRX_GPIO_Port, MATRX_RGB1_Pins, GPIO_PIN_SET);
  HAL_GPIO_WritePin(MATRX_GPIO_Port, MATRX_R2_Pin, GPIO_PIN_SET);

  tick(MATRX_CLK_Pin);

  HAL_GPIO_WritePin(MATRX_GPIO_Port, MATRX_RGB1_Pins, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(MATRX_GPIO_Port, MATRX_R2_Pin, GPIO_PIN_RESET);

  for(int i = 0; i < 2; ++i)
  {
    tick(MATRX_CLK_Pin);
  }
  HAL_GPIO_WritePin(MATRX_GPIO_Port, MATRX_OE_Pin|MATRX_STB_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(MATRX_GPIO_Port, MATRX_OE_Pin|MATRX_STB_Pin, GPIO_PIN_SET);


//  HAL_GPIO_WritePin(MATRX_GPIO_Port, MATRX_B1_Pin, GPIO_PIN_SET);
//  HAL_GPIO_WritePin(MATRX_GPIO_Port, MATRX_R2_Pin, GPIO_PIN_SET);
//
//  HAL_GPIO_WritePin(MATRX_GPIO_Port, MATRX_CLK_Pin, GPIO_PIN_SET);
//  HAL_GPIO_WritePin(MATRX_GPIO_Port, MATRX_CLK_Pin, GPIO_PIN_RESET);
//
//  HAL_GPIO_WritePin(MATRX_GPIO_Port, MATRX_B1_Pin, GPIO_PIN_RESET);
//  HAL_GPIO_WritePin(MATRX_GPIO_Port, MATRX_R2_Pin, GPIO_PIN_RESET);
//
//  for(int i = 0; i < 16; ++i)
//  {
//    HAL_GPIO_WritePin(MATRX_GPIO_Port, MATRX_CLK_Pin, GPIO_PIN_SET);
//    HAL_GPIO_WritePin(MATRX_GPIO_Port, MATRX_CLK_Pin, GPIO_PIN_RESET);
//  }

  //Latch the data
//  tick(MATRX_STB_Pin);

//  Enable the display
//  HAL_GPIO_WritePin(MATRX_GPIO_Port, MATRX_OE_Pin, GPIO_PIN_RESET);

}

//----------------------------------------------------------------------------------------------------------------------
void clearMatrixT()
{
  HAL_GPIO_WritePin(MATRX_GPIO_Port, MATRX_ADDR_Pins, GPIO_PIN_RESET);

   //Set R1 high, clock, latch, and enable
   //disable output
   HAL_GPIO_WritePin(MATRX_GPIO_Port, MATRX_OE_Pin, GPIO_PIN_SET);

   // Shift in some data
   HAL_GPIO_WritePin(MATRX_GPIO_Port, MATRX_B1_Pin, GPIO_PIN_RESET);
   HAL_GPIO_WritePin(MATRX_GPIO_Port, MATRX_R2_Pin, GPIO_PIN_RESET);

   tick(MATRX_CLK_Pin);

   HAL_GPIO_WritePin(MATRX_GPIO_Port, MATRX_B1_Pin, GPIO_PIN_RESET);
   HAL_GPIO_WritePin(MATRX_GPIO_Port, MATRX_R2_Pin, GPIO_PIN_RESET);

   for(int i = 0; i < 64; ++i)
   {
     tick(MATRX_CLK_Pin);
   }

   //Latch the data
   tick(MATRX_STB_Pin);

 //  Enable the display
   HAL_GPIO_WritePin(MATRX_GPIO_Port, MATRX_OE_Pin, GPIO_PIN_RESET);
}

//----------------------------------------------------------------------------------------------------------------------
void resetColors()
{
  MATRX_GPIO_Port->BRR = MATRX_RGB_Pins;
}
//----------------------------------------------------------------------------------------------------------------------
void resetAllPins()
{
  MATRX_GPIO_Port->BRR = MATRX_ALL_Pins;
}

//----------------------------------------------------------------------------------------------------------------------
void testMatrix1()
{
    //Set a pixel of given section, half, and bit
    int section=3;  //0..7
    int half=1;  //1..2
    int bit=10;  //0..31
    printf("Test matrix 1\n");
    clearMatrixT();
    //Set all pins to output low
    resetAllPins();

    int i=0;   //initialize main loop section iterator

    while(1) //Main loop
    {
      printf("i: %d, section: %d, half: %d\n", i, section, half);
      //Shift out the data for current section
      for(int j=0; j < 32; ++j)
      {
        resetColors();  //start with all zeros
        if( i==section && j==bit)  //if this is the right bit position
        {
          //set rgb in our half to one
          if (half==1)
          {
            HAL_GPIO_WritePin(MATRX_GPIO_Port, MATRX_RGB1_Pins, GPIO_PIN_SET);
          }
          else
          {
            HAL_GPIO_WritePin(MATRX_GPIO_Port, MATRX_RGB2_Pins, GPIO_PIN_SET);
          }
        }
        //Toggle the clock
        tick(MATRX_CLK_Pin);
      }
      //disable display while latching and selecting this section (OE)
      HAL_GPIO_WritePin(MATRX_GPIO_Port, MATRX_OE_Pin, GPIO_PIN_SET);


      //Latch the data (STB)
      tick(MATRX_STB_Pin);

      //Select this section
//      OUTA[Pin_C..Pin_A]:=i
      MATRX_GPIO_Port->BSRR = i<<6; // Сдвинем в область битов адресов (A, B, C, D)

      if (i++==8)  //keep i in range 0..7
        i=0;

      //enable display now that data latched and section selected
        HAL_GPIO_WritePin(MATRX_GPIO_Port, MATRX_OE_Pin, GPIO_PIN_RESET);
        HAL_Delay(100);
    }
}



