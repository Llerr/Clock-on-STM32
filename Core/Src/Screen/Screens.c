#include <stdio.h>

#include "stm32_ub_font.h"
#include "MatrixRGB.h"
#include "sensors.h"
#include "buttons.h"
#include "rtc.h"
#include "backup.h"
#include "utils.h"
#include "audio.h"
#include "bmp280.h"
#include "aht10.h"

#include "pomidoro.h"
#include "pictures.h"
#include "Screen/Screens.h"
#include "Screen/ScreensDescriptions.h"

#define NUM_MAIN_SCREENS 4
#define SLEEP_TIME (10*60)
#define BELL_TIME_OFF (15*60)

int brightCur = 255; ///< Текущая яркость
uint8_t useCountdown = 0;
uint8_t counterForScreens = 0; ///< счётчик для перехода к следующему экрану
uint8_t resetCounter = 0;      ///< Счётчик для перехода к начальному режиму (Отображение времени)

int32_t bellTimeOff = -1;

//int menu = 0;  ///<  Пункт меню
char editMode = 0; ///< Флаг редактирования
char editText[32] = {0};
char editTextDays[32] = {0};
char editTextOffDays[32] = {0};
char editTextAlarmOn[32] = {0};
char blinkText[32] = {0};

//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void drawScreen()
{
  if(!screenCur)
    return;
  //  clearMatrix();
  for(int i = 0; i < screenCur->numText; ++i)
  {
    screenCur->text[i]->draw(screenCur->text[i], NULL);
  }
  //  blink(0); // перересуем соответствующим цветом, то что должно мигать
}

//----------------------------------------------------------------------------------------------------------------------
void setScreen(ScreenDescript *screen)
{
  screenCur = screen;
  resetCounter = 0;
}
//----------------------------------------------------------------------------------------------------------------------
void screenSecondCallback()
{
  if(useCountdown)
  {
    if(decreaseTime(&sCountdown))
    {
      clearScreen();
      setScreen(&screenCountdownFinish);
      useCountdown = 0;
      playSound(&countDownSound, 1);
    }

    return; // Дальше можно ничего не делать
  }
  if(pomidoroCountDown()) // Проверим помидорный таймер
  {
    clearScreen();
    setScreen(&screenPomidoro);
    playSound(&countDownSound, 0);
  }

  if(counterForScreens > 3)
  {
    counterForScreens = 0;
    nextScreenMode();
  }
  ++counterForScreens;
  checkAlarms();
}

//----------------------------------------------------------------------------------------------------------------------
void clearScreen()
{
  clearMatrix();
}

//----------------------------------------------------------------------------------------------------------------------
void nextScreenMode()
{
  //  printf("Next main screen: cur: %p, next: %p\n", screenCur, screenCur->nextMode);
//  static uint8_t resetCounter = 0;
  switch(screenCur->type)
  {
  // В основном режиме, листаем показания
  case stateTime:
    screenCur = screenCur->nextMode;
    break;
   // По умолчанию, возвращаемся к показу времени
  default:
    if(++resetCounter > 4)
    {
      if(screenCur->autoReset) // Если это не запрещено
      {
        clearScreen();
        resetCounter = 0;
        screenCur = &screenMain1;
      }
    }
    break;
  }
}

//----------------------------------------------------------------------------------------------------------------------
void blink(uint8_t change)
{
  if(!screenCur->blink) // Если нет мигания
    return;
  static uint8_t blinkStep = 0;
  static uint8_t color;
  if(change)
  {
    color = (!blinkStep)?screenCur->blink->colorFont:screenCur->blink->colorBack;
    blinkStep = !blinkStep;
  }
  //  screenCur->blink->colorFont = color;
//    printf("%lu: Blink, color( %d ) \n", HAL_GetTick(), color);
  screenCur->blink->draw(screenCur->blink, &color);
}


//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void sleepOn()
{
  printf("Sleep On\n");
  setScreen(&screenSleep); // Переключимся на экран сна
  alarmSetState(&alarmSleep, 1); //включим сон
  bellTimeOff = -1;
  stopSound();
}

//----------------------------------------------------------------------------------------------------------------------
void alarmOff()
{
  printf("Alarm Off\n");
  setScreen(&screenMain1); // Переключимся на основное время
  alarmSetState(&alarmSleep, 0); //отключим сон
  bellTimeOff = -1;
  stopSound();
}

//----------------------------------------------------------------------------------------------------------------------
void alarmOn(Alarm *alrm)
{
  printf("Alarm On\n");
  setScreen(&screenClock);
  alarmSleep.alarmTime = alrm->alarmTime;
  addTime(&alarmSleep.alarmTime, SLEEP_TIME);
  bellTimeOff = BELL_TIME_OFF;
  playSound(&clockSound, 1);
  clearScreen();
}

//----------------------------------------------------------------------------------------------------------------------
void checkAlarms()
{
//  printf("time %02d:%02d:%02d\n", sTime.Hours, sTime.Minutes, sTime.Seconds);
//
//  printf("alrm1 %02d:%02d:%02d %d\n", alarm1.alarmTime.Hours,
//      alarm1.alarmTime.Minutes, alarm1.alarmTime.Seconds, alarm1.on);
  if(pomidoroIsWork)
  {

  }

  if(alaramIsOn(&alarm1))
  {
    alarmOn(&alarm1);
  }
  if(alaramIsOn(&alarm2))
  {
    alarmOn(&alarm2);
  }
  if(alaramIsOn(&alarm3))
  {
    alarmOn(&alarm3);
  }
  if(alaramIsOn(&alarmSleep))
  {
    alarmOn(&alarmSleep);
  }

  if(bellTimeOff > 0) // Через BELL_TIME_OFF выключить звонок
  {
    --bellTimeOff;
//    printf("Bell sing %ld sec\n", bellTimeOff);
  }
  else if(0 == bellTimeOff)
  {
    alarmOff();
  }
}

//----------------------------------------------------------------------------------------------------------------------
void setBrightness()
{

}

//----------------------------------------------------------------------------------------------------------------------
void initScreen()
{
  setScreen(&screenMain1);

  //   printf("screenMain1: %p\n", &screenMain1);
  //   printf("screenMain2: %p\n", &screenMain2);
  //   printf("screenMain3: %p\n", &screenMain3);
  //   printf("screenMain4: %p\n", &screenMain4);
}

//----------------------------------------------------------------------------------------------------------------------
//---------------------------- Нажатие средней кнопки ------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void saveTime(void *dataPtr)
{
  setTime(&sTimeEdit);
  setScreen(screenCur->backState);
}

//----------------------------------------------------------------------------------------------------------------------
void saveDate(void *dataPtr)
{
  checkDate(&sDateEdit);
  setDate(&sDateEdit);
  getDate(&sDate);
  saveDateBKP(&sDateEdit);
  setScreen(screenCur->backState);
}

//----------------------------------------------------------------------------------------------------------------------
void saveAlarm(void *dataPtr)
{
  switch (screenCur->backState->type)
  {
    case stateMenuAlarm1:
      alarm1 = alarmEdit;
      break;
    case stateMenuAlarm2:
      alarm2 = alarmEdit;
      break;
    case stateMenuAlarm3:
      alarm3 = alarmEdit;
      break;
    default:
      break;
  }

  saveAlarmsBKP();
  setScreen(screenCur->backState);
}

//----------------------------------------------------------------------------------------------------------------------
void inBrightness(void *dataPtr) ///< Вход в редактирование яркости
{
  clearMatrix();
  screenBrightnessEdit.backState = screenCur;
  setScreen(&screenBrightnessEdit);
  numEdit = &brightCur;

  GPIO_Press_Pin = 0;
  buttonReceiverBrightEdit();
}

//----------------------------------------------------------------------------------------------------------------------
void inCountdownEdit(void *dataPtr) ///< Вход в редактирование яркости
{
  clearMatrix();
  screenCountdownEdit.backState = screenCur;
  setScreen(&screenCountdownEdit);
  editTime = &sCountdownEdit;

  GPIO_Press_Pin = 0;
  buttonReceiverCountdownEdit();
}

//----------------------------------------------------------------------------------------------------------------------
void countdownStartStop(void *dataPtr)
{
  if(timeIsZero(&sCountdown)) // Если не установлен счётчик, то ничего не включаем.
  {
//    sCountdown = sCountdownEdit;
    useCountdown = 0;
    return;
  }
//  sCountdownEdit = sCountdown;
  useCountdown = !useCountdown;
  printf("Save count (%02d:%02d:%02d), start: %d\n", sCountdown.Hours, sCountdown.Minutes, sCountdown.Seconds, useCountdown);
}

//----------------------------------------------------------------------------------------------------------------------
void pomidoroStartStop(void *dataPtr)
{
  startStopPomidoror();
}

//----------------------------------------------------------------------------------------------------------------------
void pomidoroReset(void *dataPtr)
{
  resetPomidoro();
}

//----------------------------------------------------------------------------------------------------------------------
void countdownFinish(void *dataPtr)
{
  setScreen(&screenCountdown);
  sCountdown = sCountdownEdit;
  stopSound();
}

//----------------------------------------------------------------------------------------------------------------------
void saveCountdown(void *dataPtr)
{
  setScreen(screenCur->backState);
  sCountdown = sCountdownEdit;
  clearScreen();
}

//----------------------------------------------------------------------------------------------------------------------
void saveBrightness(void *dataPtr)
{
  uint8_t idx = getBrightnessIndex();
  setScreen(screenCur->backState);
  clearScreen();
  brightnessAll[idx] = brightCur;
  printf("Save brightness\n");
  saveBrightnessBKP();
}

//----------------------------------------------------------------------------------------------------------------------
void savePomidoroWork(void *dataPtr)
{
  setScreen(screenCur->backState);
  sPomidoroWork = sPomidoroEdit;
  clearScreen();
  savePomidoroBKP();
}

//----------------------------------------------------------------------------------------------------------------------
void savePomidoroSmallRest(void *dataPtr)
{
  setScreen(screenCur->backState);
  sPomidoroSmallRest = sPomidoroEdit;
  clearScreen();
  savePomidoroBKP();
}

//----------------------------------------------------------------------------------------------------------------------
void savePomidoroBigRest(void *dataPtr)
{
  setScreen(screenCur->backState);
//  printf("Pom edit %d:%d:%d\n", sPomidoroEdit.Hours, sPomidoroEdit.Minutes, sPomidoroEdit.Seconds);
  sPomidoroBigRest = sPomidoroEdit;
//  printf("Pom work %d:%d:%d\n", sPomidoroWork.Hours, sPomidoroWork.Minutes, sPomidoroWork.Seconds);
  clearScreen();
  savePomidoroBKP();
}

//----------------------------------------------------------------------------------------------------------------------
void savePomidoroNumInDay(void *dataPtr)
{
  setScreen(screenCur->backState);
//  sPomidoroBigRest = sPomidoroEdit;
  clearScreen();
  savePomidoroBKP();
}

//----------------------------------------------------------------------------------------------------------------------
void savePomidoroNumInSeries(void *dataPtr)
{
  setScreen(screenCur->backState);
//  sPomidoroBigRest = sPomidoroEdit;
  clearScreen();
  savePomidoroBKP();
}

//----------------------------------------------------------------------------------------------------------------------
void midStub(void *dataPtr) ///< Заглушка
{
}

//----------------------------------------------------------------------------------------------------------------------
void selectMenuTime(void *dataPtr) ///< Редактрование текущего времени (выбор в меню)
{
  screenEditTime.backState = screenCur;
  screenCur = &screenEditTime;
  clearScreen();
  GPIO_Press_Pin = 0;
  getTime(&sTimeEdit);
  sTimeEdit.Seconds = 0;
  buttonReceiverTimeEdit();
}

//----------------------------------------------------------------------------------------------------------------------
void selectMenuAlarm(void *dataPtr) ///< Редактрование текущего времени (выбор в меню)
{
  screenEditAlarm.backState = screenCur;
  setScreen(&screenEditAlarm);
  switch (screenCur->backState->type)
  {
    case stateMenuAlarm1:
      alarmEdit = alarm1;
      break;
    case stateMenuAlarm2:
      alarmEdit = alarm2;
      break;
    case stateMenuAlarm3:
      alarmEdit = alarm3;
      break;
    default:
      break;
  }
  clearScreen();
  GPIO_Press_Pin = 0;
//  getTime(&sTimeEdit);
//  sTimeEdit.Seconds = 0;
  buttonReceiverAlarmEdit();
}

//----------------------------------------------------------------------------------------------------------------------
void selectMenuDate(void *dataPtr) ///< Редактрование даты
{
  screenEditDate.backState = screenCur;
  setScreen(&screenEditDate);
  clearScreen();
  GPIO_Press_Pin = 0;
  getDate(&sDateEdit);
  buttonReceiverDateEdit();
}

//----------------------------------------------------------------------------------------------------------------------
void selectMenuPomidoroWork(void *dataPtr)
{
  clearMatrix();
  screenPomidoroWorkEdit.backState = screenCur;
  setScreen(&screenPomidoroWorkEdit);
  sPomidoroEdit = sPomidoroWork;
  editTime = &sPomidoroEdit;

  GPIO_Press_Pin = 0;
  buttonReceiverCountdownEdit();
}

//----------------------------------------------------------------------------------------------------------------------
void selectMenuPomidoroSmallRest(void *dataPtr)
{
  clearMatrix();
  screenPomidoroSmallRestEdit.backState = screenCur;
  setScreen(&screenPomidoroSmallRestEdit);
  sPomidoroEdit = sPomidoroSmallRest;
  editTime = &sPomidoroEdit;

  GPIO_Press_Pin = 0;
  buttonReceiverCountdownEdit();
}

//----------------------------------------------------------------------------------------------------------------------
void selectMenuPomidoroBigRest(void *dataPtr)
{
  clearMatrix();
  screenPomidoroBigRestEdit.backState = screenCur;
  setScreen(&screenPomidoroBigRestEdit);
  sPomidoroEdit = sPomidoroBigRest;
  editTime = &sPomidoroEdit;

  GPIO_Press_Pin = 0;
  buttonReceiverCountdownEdit();
}

//----------------------------------------------------------------------------------------------------------------------
void selectMenuPomidoroNumInDay(void *dataPtr)
{
  clearMatrix();
  screenPomidoroNumInDayEdit.backState = screenCur;
  setScreen(&screenPomidoroNumInDayEdit);
  numEdit = &numPomidoros;

  GPIO_Press_Pin = 0;
  buttonReceiverNumEdit();
}

//----------------------------------------------------------------------------------------------------------------------
void selectMenuPomidoroNumInSeries(void *dataPtr)
{
  clearMatrix();
  screenPomidoroNumInSeriesEdit.backState = screenCur;
  setScreen(&screenPomidoroNumInSeriesEdit);
  numEdit = &numInSeries;

  GPIO_Press_Pin = 0;
  buttonReceiverNumEdit();
}

//----------------------------------------------------------------------------------------------------------------------
void showMenu(void *dataPtr)
{
//  menu = 0;
  setScreen(&screenMenuTime);
}

//----------------------------------------------------------------------------------------------------------------------
void timerStartStop(void *dataPtr)
{

}

