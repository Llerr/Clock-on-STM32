/*
 * MatrixRGB.h
 *
 *  Created on: Feb 12, 2021
 *      Author: lex
 */

#ifndef INC_MATRIXRGB_H_
#define INC_MATRIXRGB_H_

#include <stdint.h>
#include "pictures.h"
/*
 * Распиновка разъёма матрицы
 *         +---+
 *     R1  |* *| G1
 *     B1  |* *| GND
 *     R2  |* *| G2
 *     B2   * *| GND
 *     A    * *| B
 *     C   |* *| D
 *     CLK |* *| STB
 *     OE  |* *| GND
 *         +---+
 */

#define MATRIX_HEIGHT  32
#define MATRIX_WIDTH   64
#define MATRIX_SIZE (MATRIX_HEIGHT*MATRIX_WIDTH)

void initMatrix();
void calcBrightPWM();

void clearMatrix();
void updateScreen();
void drawPoint(int x, int y, uint16_t color);
void drawPicture(int x, int y, Picture *pic);
void drawRect(const int x1, const int y1, const int x2, const int y2, uint16_t lineColor, uint16_t fillColor);

void testDraw(uint16_t x, uint16_t y);

void dumpScreen();

void tick(uint16_t pin);

void drawPointT(int x, int y);
void testMatrix();

void clearMatrixT();

void resetAllPins();

void testMatrix1();

extern uint8_t matrix[MATRIX_HEIGHT][MATRIX_WIDTH];

#endif /* INC_MATRIXRGB_H_ */
