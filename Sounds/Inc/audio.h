/*
 * audio.h
 *
 *  Created on: Jul 10, 2021
 *      Author: lex
 */

#ifndef INC_AUDIO_H_
#define INC_AUDIO_H_

#include <stdint.h>

#include "stm32f1xx_hal.h"

/**
 * @struct Audio_t
 * Описание структуры аудиоданных
 */
typedef struct Audio_t
{
  uint16_t bitrate;    ///< Частота выборки
  uint8_t numChanel;   ///< Количество каналов
  uint32_t dataLength; ///< Количество выборок
  const uint16_t *data; ///< PCM данные. (выборки)
} Audio;

extern Audio buttonSound;
extern Audio clockSound;
extern Audio countDownSound;

//----------------------------------------------------------------------------------------------------------------------
/**
 * @fn void initAudio()
 * Начальная установка аудио
 */
void initAudio();

/**
 * @fn void setFreq(uint32_t)
 * Установка предделителя и счётчика, для получения требуемой частоты
 * @note Установка приблизительная, самым простым способом.
 * @param freq
 */
void setFreq(uint32_t freq);

/**
 * @fn void play(Audio*, uint8_t)
 * Воспроизвести звук
 * @param track указатель на данные для воспроизведения
 * @param loop зацикливать ли данные (1 - воспроизводить циклически)
 */
void playSound(Audio *track, uint8_t loop);

void stopSound();

#endif /* INC_AUDIO_H_ */
