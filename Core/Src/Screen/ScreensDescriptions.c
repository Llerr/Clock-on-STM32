/*
 * ScreensDescriptions.c
 *
 *  Created on: 11 сент. 2021 г.
 *      Author: lex
 */

#include <Arial_7x10.h>
#include <buttons.h>
#include <Font_5x8.h>
#include <stddef.h>
#include <stm32_ub_font.h>
#include <Screen/Screens.h>
#include <Screen/ScreensDescriptions.h>
#include <Screen/ScreensDrawing.h>

ScreenDescript *screenCur = NULL;
ScreenDescript *screenPrev = NULL;

char *weekText[]=
{
    "    Sunday ",
    "    Monday ",
    "  Tuesday ",
    "Wednesday",
    "  Thursday",
    "    Friday ",
    "   Saturday",
};


//Понедельник - Monday - Mon или Mo
//Вторник - Tuesday - Tue или Tu
//Среда - Wednesday - Wed или We
//Четверг - Thursday - Thu или Th
//Пятница - Friday - Fri или Fr
//Суббота - Saturday - Sat или Sa
//Воскресенье - Sunday - Sun или Su


char *menuText[] =
{
    "Time        ",
    "Date        ",
    "Alarms >    ",
    "Brightness >"
};



//----------------------------------------------------------------------------------------------------------------------
//---------------------------------- Данные ----------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//                                     1+13*2
TextSets textBlinkTime =   {txtTime,       27,     -5,  WHITE,  BLACK, &pDigital_7_28, drawBlink,        ":"}; // Двоеточие для мигания

TextSets textHour        = {txtTime,        1,     -5,  WHITE,  BLACK, &pDigital_7_28, drawHour,         NULL}; // Время
TextSets textMinute      = {txtTime,        27+4,  -5,  WHITE,  BLACK, &pDigital_7_28, drawMinute,       NULL}; // Время
TextSets textBellOn      = {txtTime,        57,    1,   WHITE,  BLACK, &pDigital_7_28, drawBellOn,       NULL}; // Время
TextSets textDateAdd     = {txtDate,        0,     19,  YELLOW, BLACK, &pArial_13,     drawDateAdd,      NULL}; // Дата дополнительным полем
TextSets textTemperature = {txtTemperature, 0,     19,  YELLOW, BLACK, &pArial_13,     drawTemperature,  NULL}; // температура
TextSets textHumidity    = {txtHumidity,    0,     19,  YELLOW, BLACK, &pArial_13,     drawHumidity,     NULL}; // Влажность
TextSets textPressure    = {txtPressure,    0,     19,  YELLOW, BLACK, &pArial_13,     drawPressure,     NULL}; // Давление
TextSets textClock       = {txtClock,       18,    19,  YELLOW, BLACK, &pArial_13,     drawClock,        NULL}; // Будильник
TextSets textSleep       = {txtSleep,       20,    19,  YELLOW, BLACK, &pArial_13,     drawSleep,        NULL}; // Досыпание

TextSets textDate        = {txtTimer,       0,     0,  WHITE, BLACK, &pTimes_18,     drawDate,         NULL}; // Дата
TextSets textWeekDay     = {txtTimer,       1,    18, YELLOW, BLACK, &pArial_13,     drawWeekDay,      NULL}; // День недели

TextSets textAlarm            = {txtTime,        0,       -5, WHITE,  BLACK, &pDigital_7_28, drawAlarm,         NULL}; // Время
TextSets textAlarmDays        = {txtAlarmDays,   0,       23, YELLOW, BLACK, &Arial_7x10,    drawAlarmDays,     NULL}; // Список дней недели
TextSets textAlarmOffDays     = {txtAlarmDays,   0+7*5,   23, YELLOW, BLACK, &Arial_7x10,    drawAlarmOffDays,  NULL}; // Список дней недели
TextSets textAlarmOn          = {txtAlarmDays,   0+7*7+1, 23, YELLOW, BLACK, &Arial_7x10,    drawAlarmOn,       NULL}; // Список дней недели
TextSets textAlarmDaysEdit    = {txtAlarmDays,   0,       23, YELLOW, BLACK, &Arial_7x10,    drawEdit,          editTextDays}; // Список дней недели для редактирования
TextSets textAlarmOffDaysEdit = {txtAlarmDays,   0,       23, YELLOW, BLACK, &Arial_7x10,    drawEdit,          editTextOffDays}; // Список дней недели для редактирования
TextSets textAlarmOnEdit      = {txtAlarmDays,   0,       23, YELLOW, BLACK, &Arial_7x10,    drawEdit,          editTextAlarmOn}; // Список дней недели для редактирования
TextSets textBlinkDays        = {txtAlarmDays,   0,       23, GREEN,  BLACK, &Arial_7x10,    drawBlink,         blinkText}; // Рабочий день недели, для мигания
TextSets textBlinkOffDays     = {txtAlarmDays,   0+7*5,   23, RED,    BLACK, &Arial_7x10,    drawBlink,         blinkText}; // Выходной день недели, для мигания
TextSets textBlinkAlarmOn     = {txtAlarmDays,   0+7*7+1, 23, WHITE,  BLACK, &Arial_7x10,    drawBlink,         blinkText}; // Одиночный будильник, для мигания

TextSets textTimer       = {txtTimer,       0,     0, YELLOW, BLACK, &pComic_16,     drawTimer,        NULL};
TextSets textCountDown   = {txtCountdown,   0,     0, YELLOW, BLACK, &pTimes_18,     drawCountdown,    NULL};
TextSets textBrightness  = {txtBrightness, 16,     0, YELLOW, BLACK, &pTimes_18,     drawBrightness,   NULL}; // Яркость экрана
TextSets textIllum       = {txtIllum,      16,    16,    RED, BLACK, &pComic_16,     drawIllumination, NULL}; // Внешняя освещённость

TextSets textPomidoroWork           = {txtPomidoroWork,   0,    0, GREEN,  BLACK, &pTimes_18,     drawPomidoro,     NULL}; // Текст со временем помидора
TextSets textPomidoroRest           = {txtPomidoroRest,   0,    0,   RED,  BLACK, &pTimes_18,     drawPomidoro,     NULL}; // Текст со временем помидора
TextSets textPomidoroInfo           = {txtPomidoroInfo,   0,   16, WHITE,  BLACK, &pTimes_18,     drawPomidoroInfo, NULL}; // Текст со временем помидора
TextSets textPomidoroWorkInf        = {txtPomidoroInfo,  15,   19, WHITE,  BLACK, &pArial_13,     drawText,         "work"};          // Пояснительная надпись
TextSets textPomidoroSmallRestInf   = {txtPomidoroInfo,   6,   19, WHITE,  BLACK, &pArial_13,     drawText,         "small rest"};    // Пояснительная надпись
TextSets textPomidoroBigRestInf     = {txtPomidoroInfo,   6,   19, WHITE,  BLACK, &pArial_13,     drawText,         "big rest"};      // Пояснительная надпись
TextSets textPomidoroNumInDayInf    = {txtPomidoroInfo,   6,   19, WHITE,  BLACK, &pArial_10,     drawText,         "Num in day "};   // Пояснительная надпись
TextSets textPomidoroNumINSeriesInf = {txtPomidoroInfo,   0,   19, WHITE,  BLACK, &pArial_10,     drawText,         "Series length"}; // Пояснительная надпись

TextSets textCntDownInf     = {txtCountdownInfo,   2, 19,    WHITE, BLACK, &pArial_13,     drawText,    "Countdown"}; // Пояснительная надпись
TextSets textCntDownFinish  = {txtCountdownFinish, 2, 17,      RED, BLACK, &pTimes_18,     drawBlink32,    "FINISH"}; // надпись о завершении отсчёта

/// Пункты меню, выделенные и нет.
TextSets textMenuTime        = {txtMenu,    0,  0, GREEN, BLACK,       &pArial_10, drawMenu, "Time       "};
TextSets textMenuTimeSel     = {txtMenuSel, 0,  0, WHITE, BLACK,       &pArial_10, drawMenu, "Time       "};
TextSets textMenuDate        = {txtMenu,    0, 11, GREEN, BLACK,       &pArial_10, drawMenu, "Date       "};
TextSets textMenuDateSel     = {txtMenuSel, 0, 11, WHITE, BLACK,       &pArial_10, drawMenu, "Date       "};
TextSets textMenuAlr         = {txtMenu,    0, 22, GREEN, BLACK,       &pArial_10, drawMenu, "Alarms >   "};
TextSets textMenuAlrSel      = {txtMenuSel, 0, 22, WHITE, BLACK,       &pArial_10, drawMenu, "Alarms >   "};
TextSets textMenuBright      = {txtMenu,    0,  0, GREEN, BLACK,       &pArial_10, drawMenu, "Brightness "};
TextSets textMenuBrightSel   = {txtMenuSel, 0,  0, WHITE, BLACK,       &pArial_10, drawMenu, "Brightness "};
TextSets textMenuPomidoro    = {txtMenu,    0, 11, GREEN, TRANSPARENT, &pArial_10, drawMenu, "Pomidoro>  "};
TextSets textMenuPomidoroSel = {txtMenuSel, 0, 11, WHITE, TRANSPARENT, &pArial_10, drawMenu, "Pomidoro>  "};
TextSets textMenuDebug       = {txtMenu,    0, 22, GREEN, TRANSPARENT, &pArial_10, drawMenu, "Debug >  "};
TextSets textMenuDebugSel    = {txtMenuSel, 0, 22, WHITE, TRANSPARENT, &pArial_10, drawMenu, "Debug >  "};

TextSets textMenuPomWork         = {txtMenu,    0,  0,  GREEN, BLACK,       &pArial_10, drawMenu, "Time work  "};
TextSets textMenuPomWorkSel      = {txtMenuSel, 0,  0,  WHITE, BLACK,       &pArial_10, drawMenu, "Time work  "};
TextSets textMenuPomSmallRest    = {txtMenu,    0, 11,  GREEN, BLACK,       &pArial_10, drawMenu, "Small Rest "};
TextSets textMenuPomSmallRestSel = {txtMenuSel, 0, 11,  WHITE, BLACK,       &pArial_10, drawMenu, "Small Rest "};
TextSets textMenuPomBigRest      = {txtMenu,    0, 22,  GREEN, BLACK,       &pArial_10, drawMenu, "Big rest   "};
TextSets textMenuPomBigRestSel   = {txtMenuSel, 0, 22,  WHITE, BLACK,       &pArial_10, drawMenu, "Big rest   "};
TextSets textMenuPomNum          = {txtMenu,    0,  0,  GREEN, BLACK,       &pArial_10, drawMenu, "Num in day "}; // amount
TextSets textMenuPomNumSel       = {txtMenuSel, 0,  0,  WHITE, BLACK,       &pArial_10, drawMenu, "Num in day "};
TextSets textMenuPomSeries       = {txtMenu,    0, 11,  GREEN, BLACK,       &pArial_10, drawMenu, "Series length"};
TextSets textMenuPomSeriesSel    = {txtMenuSel, 0, 11,  WHITE, BLACK,       &pArial_10, drawMenu, "Series length"};

TextSets textDebugAHT10    = {txtAHT10, 0, 0,   WHITE, BLACK, &Font_5x8, drawAHT10, "AHT10"};

TextSets textDebugBMP280   = {txtBMP280, 0, 0,   WHITE, BLACK, &Font_5x8, drawBMP280, "BMP280"};

//TextSets textMenuAlrm0    = {txtMenu,    0, 0,  GREEN, BLACK, &pArial_13, drawMenu, "Alarm 1     "};
//TextSets textMenuAlrm0Sel = {txtMenuSel, 0, 0,  WHITE, BLACK, &pArial_13, drawMenu, "Alarm 1     "};
//TextSets textMenuAlrm1    = {txtMenu,    0, 11, GREEN, BLACK, &pArial_13, drawMenu, "Alarm 2     "};
//TextSets textMenuAlrm1Sel = {txtMenuSel, 0, 11, WHITE, BLACK, &pArial_13, drawMenu, "Alarm 2     "};
//TextSets textMenuAlrm2    = {txtMenu,    0, 22, GREEN, BLACK, &pArial_13, drawMenu, "Alarm 3     "};
//TextSets textMenuAlrm2Sel = {txtMenuSel, 0, 22, WHITE, BLACK, &pArial_13, drawMenu, "Alarm 3     "};


TextSets textTimeEdit      = {txtTimeEdit, 1, -5, WHITE,  BLACK, &pDigital_7_28, drawEdit,  editText};  // Текст для редактирования
TextSets textBlinkTimeEdit = {txtTimeEdit, 1, -5, WHITE,  BLACK, &pDigital_7_28, drawBlink, blinkText}; // Время

TextSets textEditBright32   = {txtEditBright32,  16, 0,  YELLOW, BLACK, &pTimes_18, drawEdit32,    editText};
TextSets textEdit32         = {txtEdit32,         0, 0,  YELLOW, BLACK, &pTimes_18, drawEdit32,    editText};
TextSets textBlink32        = {txtBlink32,        0, 0,  YELLOW, BLACK, &pTimes_18, drawBlink32,   blinkText};


//TextSets *texts = {textTime, textTemperature};
//----------------------------------------------------------------------------------------------------------------------
//-------------------- Э К Р А Н Ы -------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
ScreenDescript screenClock =
{
    stateClock,
    &textBlinkTime, //blink
    0,               //автосброс режима

    &screenClock, // Лево
    &screenClock, // Право
    &screenClock,
    &screenClock,
    &screenClock,

    &screenClock, // кнопка set

    sleepOn,      // Краткое нажатие
    alarmOff,     // Длинное нажатие
    buttonReceiverMenu, // Обработчик кнопок в этом пункте
    3,
    {&textHour, &textMinute, &textClock}
};

//----------------------------------------------------------------------------------------------------------------------
ScreenDescript screenSleep =
{
    stateSleep,
    &textBlinkTime, //blink
    0,               //автосброс режима

    &screenSleep, // Лево
    &screenSleep, // Право
    &screenSleep,
    &screenSleep,
    &screenSleep,

    &screenSleep, // кнопка set

    midStub,      // Краткое нажатие
    alarmOff,     // Длинное нажатие
    buttonReceiverMenu, // Обработчик кнопок в этом пункте
    3,
    {&textHour, &textMinute, &textSleep}
};


//----------------------------------------------------------------------------------------------------------------------
ScreenDescript screenMain1 =
{
    stateTime,
    &textBlinkTime,
    0,               //автосброс режима

    &screenMain2,      // следующий экран режима
    &screenMain4,
    &screenDate,
    &screenBrightness,
    &screenMain1,

    &screenMenuTime, // кнопка set

    midStub,      // Краткое нажатие
    selectMenuTime,
    buttonReceiverMenu, // Обработчик кнопок в этом пункте
    4,
    {&textHour, &textMinute, &textTemperature, &textBellOn}
};

//----------------------------------------------------------------------------------------------------------------------
ScreenDescript screenMain2 =
{
    stateTime,
    &textBlinkTime, //blink
    0,               //автосброс режима

    &screenMain3,    // следующий экран режима
    &screenMain1,
    &screenDate,
    &screenBrightness,
    &screenMain2,

    &screenMenuTime, // кнопка set

    midStub,      // Краткое нажатие
    selectMenuTime,     // Длинное нажатие
    buttonReceiverMenu, // Обработчик кнопок в этом пункте
    4,
    {&textHour, &textMinute, &textHumidity, &textBellOn}
};

//----------------------------------------------------------------------------------------------------------------------
ScreenDescript screenMain3 =
{
    stateTime,
    &textBlinkTime, //Текст для мигания
    0,               //автосброс режима

    &screenMain4,    // следующий экран режима
    &screenMain2,
    &screenDate,
    &screenBrightness,
    &screenMain3,

    &screenMenuTime, // кнопка set

    midStub,      // Краткое нажатие
    selectMenuTime,     // Длинное нажатие
    buttonReceiverMenu, // Обработчик кнопок в этом пункте
    4,
    {&textHour, &textMinute, &textPressure, &textBellOn}
};

//----------------------------------------------------------------------------------------------------------------------
ScreenDescript screenMain4 =
{
    stateTime,
    &textBlinkTime, //blink
    0,               //автосброс режима

//    &screenClock, // Лево
    &screenMain1,       // следующий экран режима  (Лево)
    &screenMain3,       // предыдущий экран режима (Право)
    &screenDate,        // следующий режим         (вверх)
    &screenBrightness,  // предыдущий режим        (вниз)
    &screenMain4,

    &screenMenuTime, // кнопка set

    midStub,      // Краткое нажатие
    selectMenuTime,     // Длинное нажатие
    buttonReceiverMenu, // Обработчик кнопок в этом пункте
    4,
    {&textHour, &textMinute, &textDateAdd, &textBellOn}
};

//----------------------------------------------------------------------------------------------------------------------
ScreenDescript screenBrightness =
{
    stateBrightness,
    NULL, //blink
    1,               //автосброс режима

    &screenBrightness,  // следующий экран режима
    &screenBrightness,  // предыдущий экран режима
    &screenMain1,       // следующий режим
    &screenCountdown,   // предыдущий режим
    &screenMain1,       // режим, при долгом нажатии влево. (выход из меню, из редактирования)

    &screenMenuTime, // кнопка set

    midStub,            // Краткое нажатие средней кнопки
    inBrightness,       // Долгое нажатие средней кнопки
    buttonReceiverMenu, // Обработчик кнопок в этом пункте
    2,
    {&textBrightness, &textIllum}
};

//----------------------------------------screenCountdown------------------------------------------------------------------------------
ScreenDescript screenCountdown =
{
    stateCountDown,
    NULL, //blink
    1,               //автосброс режима

    &screenCountdown,   // следующий экран режима
    &screenCountdown,   // предыдущий экран режима
    &screenBrightness,  // следующий режим
    &screenPomidoro,    // предыдущий режим
    &screenMain1,

    &screenMenuTime, // кнопка set

    countdownStartStop,   // Краткое нажатие средней кнопки
    inCountdownEdit,              // Длинное нажатие средней кнопки
    buttonReceiverMenu, // Обработчик кнопок в этом пункте
    2,
    {&textCountDown, &textCntDownInf}
};

//----------------------------------------screenPomidoro------------------------------------------------------------------------------
ScreenDescript screenPomidoro =
{
    statePomidoro,
    NULL, //blink
    1,               //автосброс режима

    &screenPomidoro,    // следующий экран режима
    &screenPomidoro,    // предыдущий экран режима
    &screenCountdown,  // следующий режим
    &screenDate,        // предыдущий режим
    &screenMain1,       // режим, при долгом нажатии влево. (выход из меню, из редактирования)

    &screenMenuTime,    // кнопка set

    pomidoroStartStop,  // Краткое нажатие средней кнопки
    pomidoroReset,      // Длинное нажатие средней кнопки
    buttonReceiverMenu, // Обработчик кнопок в этом пункте
    2,
    {&textPomidoroRest, &textPomidoroInfo}
};

//----------------------------------------------------------------------------------------------------------------------
ScreenDescript screenDate =
{
    stateDate,
    NULL, //blink
    1,               //автосброс режима

    &screenDate,       // следующий экран режима
    &screenDate,       // предыдущий экран режима
    &screenPomidoro,   // следующий режим
    &screenMain1,      // предыдущий режим
    &screenMain1,

    &screenMenuTime,   // кнопка set

    midStub,           // Краткое нажатие средней кнопки
    selectMenuDate,           // Длинное нажатие средней кнопки

    buttonReceiverMenu, // Обработчик кнопок в этом пункте
    2,
    {&textDate, &textWeekDay}
};

//----------------------------------------------------------------------------------------------------------------------
ScreenDescript screenCountdownFinish =
{
    stateCountDownFinish,
    &textCntDownFinish, //blink
    0,               //автосброс режима

    &screenCountdownFinish,   // следующий экран режима
    &screenCountdown,   // предыдущий экран режима
    &screenCountdown,   // следующий режим
    &screenCountdown,   // предыдущий режим
    &screenMain1,

    &screenMenuTime, // кнопка set

    countdownFinish,   // Краткое нажатие средней кнопки
    inCountdownEdit,              // Длинное нажатие средней кнопки
    buttonReceiverMenu, // Обработчик кнопок в этом пункте
    1,
    {&textCountDown}
};

//----------------------------------------------------------------------------------------------------------------------
ScreenDescript screenCountdownEdit =
{
    stateCountDownEdit,
    &textBlink32, //blink
    0,               //автосброс режима

    &screenCountdownEdit,  // следующий экран режима
    &screenCountdownEdit,  // предыдущий экран режима
    &screenCountdownEdit,  // следующий режим
    &screenCountdownEdit,  // предыдущий режим
    &screenMain1,

    &screenCountdownEdit, // кнопка set

    saveCountdown,               // Краткое нажатие средней кнопки
    midStub,                     // Длинное нажатие средней кнопки
    buttonReceiverCountdownEdit, // Обработчик кнопок в этом пункте
    2,
    {&textEdit32, &textCntDownInf}
};

//----------------------------------------------------------------------------------------------------------------------
ScreenDescript screenBrightnessEdit =
{
    stateBrightnessEdit,
    &textBlink32, //blink
    0,               //автосброс режима

    &screenBrightnessEdit,    // следующий экран режима
    &screenBrightnessEdit,    // предыдущий экран режима
    &screenBrightnessEdit,    // следующий режим
    &screenBrightnessEdit,    // предыдущий режим
    &screenBrightness,        // режим, при долгом нажатии влево. (выход из меню, из редактирования)

    &screenBrightnessEdit, // кнопка set (В режиме редактирования не используется)

    saveBrightness,           // Краткое нажатие средней кнопки
    showMenu,                 // Долгое нажатие средней кнопки
    buttonReceiverBrightEdit, // Обработчик кнопок в этом пункте
    2,
    {&textEditBright32, &textIllum}
};

//----------------------------------------------------------------------------------------------------------------------
ScreenDescript screenPomidoroWorkEdit =
{
    stateCountDownEdit,
    &textBlink32, //blink
    0,               //автосброс режима

    &screenPomidoroWorkEdit,  // следующий экран режима
    &screenPomidoroWorkEdit,  // предыдущий экран режима
    &screenPomidoroWorkEdit,  // следующий режим
    &screenPomidoroWorkEdit,  // предыдущий режим
    &screenMenuPomidoro,

    &screenPomidoroWorkEdit, // кнопка set

    savePomidoroWork,            // Краткое нажатие средней кнопки
    midStub,                     // Длинное нажатие средней кнопки
    buttonReceiverCountdownEdit, // Обработчик кнопок в этом пункте
    2,
    {&textEdit32, &textPomidoroWorkInf}
};

//----------------------------------------------------------------------------------------------------------------------
ScreenDescript screenPomidoroSmallRestEdit =
{
    stateCountDownEdit,
    &textBlink32, //blink
    0,               //автосброс режима

    &screenPomidoroSmallRestEdit,  // следующий экран режима
    &screenPomidoroSmallRestEdit,  // предыдущий экран режима
    &screenPomidoroSmallRestEdit,  // следующий режим
    &screenPomidoroSmallRestEdit,  // предыдущий режим
    &screenMenuPomidoro,

    &screenPomidoroSmallRestEdit, // кнопка set

    savePomidoroSmallRest,       // Краткое нажатие средней кнопки
    midStub,                     // Длинное нажатие средней кнопки
    buttonReceiverCountdownEdit, // Обработчик кнопок в этом пункте
    2,
    {&textEdit32, &textPomidoroSmallRestInf}
};

//----------------------------------------------------------------------------------------------------------------------
ScreenDescript screenPomidoroBigRestEdit =
{
    stateCountDownEdit,
    &textBlink32, //blink
    0,               //автосброс режима

    &screenPomidoroBigRestEdit,  // следующий экран режима
    &screenPomidoroBigRestEdit,  // предыдущий экран режима
    &screenPomidoroBigRestEdit,  // следующий режим
    &screenPomidoroBigRestEdit,  // предыдущий режим
    &screenMenuPomidoro,

    &screenPomidoroBigRestEdit, // кнопка set

    savePomidoroBigRest,         // Краткое нажатие средней кнопки
    midStub,                     // Длинное нажатие средней кнопки
    buttonReceiverCountdownEdit, // Обработчик кнопок в этом пункте
    2,
    {&textEdit32, &textPomidoroBigRestInf}
};

//----------------------------------------------------------------------------------------------------------------------
ScreenDescript screenPomidoroNumInDayEdit =
{
    stateCountDownEdit,
    &textBlink32, //blink
    0,               //автосброс режима

    &screenPomidoroNumInDayEdit,  // следующий экран режима
    &screenPomidoroNumInDayEdit,  // предыдущий экран режима
    &screenPomidoroNumInDayEdit,  // следующий режим
    &screenPomidoroNumInDayEdit,  // предыдущий режим
    &screenMenuPomidoro,

    &screenPomidoroNumInDayEdit, // кнопка set

    savePomidoroNumInDay,         // Краткое нажатие средней кнопки
    midStub,                     // Длинное нажатие средней кнопки
    buttonReceiverNumEdit,       // Обработчик кнопок в этом пункте
    2,
    {&textEditBright32, &textPomidoroNumInDayInf}
};

//----------------------------------------------------------------------------------------------------------------------
ScreenDescript screenPomidoroNumInSeriesEdit =
{
    stateCountDownEdit,
    &textBlink32, //blink
    0,               //автосброс режима

    &screenPomidoroNumInSeriesEdit,  // следующий экран режима
    &screenPomidoroNumInSeriesEdit,  // предыдущий экран режима
    &screenPomidoroNumInSeriesEdit,  // следующий режим
    &screenPomidoroNumInSeriesEdit,  // предыдущий режим
    &screenMenuPomidoro,

    &screenPomidoroNumInSeriesEdit, // кнопка set

    savePomidoroNumInSeries,         // Краткое нажатие средней кнопки
    midStub,                     // Длинное нажатие средней кнопки
    buttonReceiverNumEdit,       // Обработчик кнопок в этом пункте
    2,
    {&textEditBright32, &textPomidoroNumINSeriesInf}
};


//----------------------------------------------------------------------------------------------------------------------
//---------------------------- M E N U ---------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
ScreenDescript screenMenuTime =
{
    stateMenuTime,
    NULL, //blink
    1,               //автосброс режима

    &screenMenuTime,  // Право
    &screenMain1,  // Лево
    &screenMenuTime,  // вверх
    &screenMenuDate,  // вниз
    &screenMain1,  // Долгое нажатие влево

    &screenMain1, // кнопка set

    selectMenuTime,      // Краткое нажатие центр
    midStub,             // Долгое нажатие средней кнопки
    buttonReceiverMenu, // Обработчик кнопок в этом пункте
    3,
    {&textMenuTimeSel, &textMenuDate, &textMenuAlr}
};

//----------------------------------------------------------------------------------------------------------------------
ScreenDescript screenMenuDate =
{
    stateMenuDate,
    NULL, //blink
    1,               //автосброс режима

    &screenMenuDate,  // Право
    &screenMenuDate,  // Лево
    &screenMenuTime,  // вверх
    &screenMenuAlarm, // вниз
    &screenMain1,

    &screenMain1, // кнопка set

    selectMenuDate,   // Краткое нажатие средней кнопки
    midStub,          // Долгое нажатие средней кнопки
    buttonReceiverMenu, // Обработчик кнопок в этом пункте
    3,
    {&textMenuTime, &textMenuDateSel, &textMenuAlr}
};

//----------------------------------------------------------------------------------------------------------------------
ScreenDescript screenMenuAlarm =
{
    stateMenuAlarm,
    NULL, //blink
    1,               //автосброс режима

    &screenMenuAlr0,      // Право
    &screenMenuAlarm,     // Лево
    &screenMenuDate,      // вверх
    &screenMenuBrightness,// вниз
    &screenMain1,

    &screenMain1, // кнопка set

    midStub,      // Краткое нажатие средней кнопки
    midStub,      // Долгое нажатие средней кнопки
    buttonReceiverMenu, // Обработчик кнопок в этом пункте
    3,
    {&textMenuTime, &textMenuDate, &textMenuAlrSel}
};

//----------------------------------------------------------------------------------------------------------------------
ScreenDescript screenMenuBrightness =
{
    stateMenuBrightness,
    NULL, //blink
    1,               //автосброс режима

    &screenMenuBrightness,  // Право
    &screenMenuBrightness,  // Лево
    &screenMenuAlarm,       // вверх
    &screenMenuPomidoro,    // вниз
    &screenMain1,       //Долгое нажатие влево

    &screenMain1, // кнопка set

    inBrightness,      // Краткое нажатие средней кнопки
    midStub,           // Долгое нажатие средней кнопки
    buttonReceiverMenu, // Обработчик кнопок в этом пункте
    3,
    {&textMenuBrightSel, &textMenuPomidoro, &textMenuDebug}
};

//----------------------------------------------------------------------------------------------------------------------
ScreenDescript screenMenuPomidoro =
{
    stateMenuBrightness,
    NULL, //blink
    1,               //автосброс режима

    &screenMenuPomidoroWork,  // Право
    &screenMenuPomidoro,      // Лево
    &screenMenuBrightness,    // вверх
    &screenMenuDebug,         // вниз
    &screenMain1,             //Долгое нажатие влево

    &screenMain1,       // кнопка set

    midStub,            // Краткое нажатие средней кнопки
    midStub,            // Долгое нажатие средней кнопки
    buttonReceiverMenu, // Обработчик кнопок в этом пункте
    3,
    {&textMenuBright, &textMenuPomidoroSel, &textMenuDebug}
};

//----------------------------------------------------------------------------------------------------------------------
ScreenDescript screenMenuDebug =
{
    stateMenuDebug,
    NULL, //blink
    1,               //автосброс режима

    &screenMenuDebugAHT10, // Право
    &screenMenuDebug,      // Лево
    &screenMenuPomidoro,   // вверх
    &screenMenuDebug,      // вниз
    &screenMain1,          //Долгое нажатие влево

    &screenMain1, // кнопка set

    midStub,            // Краткое нажатие средней кнопки
    midStub,            // Долгое нажатие средней кнопки
    buttonReceiverMenu, // Обработчик кнопок в этом пункте
    3,
    {&textMenuBright, &textMenuPomidoro, &textMenuDebugSel}
};

//----------------------------------------------------------------------------------------------------------------------
ScreenDescript screenMenuAlr0 =
{
    stateMenuAlarm1,
    NULL, //blink
    1,               //автосброс режима

    &screenMenuAlr0,    // Право
    &screenMenuAlarm,   // Лево
    &screenMenuAlr0,    // вверх
    &screenMenuAlr1,    // вниз
    &screenMenuAlarm,

    &screenMain1, // кнопка set

    selectMenuAlarm,      // Краткое нажатие средней кнопки
    midStub,     // Долгое нажатие средней кнопки
    buttonReceiverMenu, // Обработчик кнопок в этом пункте
    4,
    {&textAlarm, &textAlarmDays, &textAlarmOffDays, &textAlarmOn}
};

//----------------------------------------------------------------------------------------------------------------------
ScreenDescript screenMenuAlr1 =
{
    stateMenuAlarm2,
    NULL, //blink
    1,               //автосброс режима

    &screenMenuAlr1,    // Право
    &screenMenuAlarm,   // Лево
    &screenMenuAlr0,    // вверх
    &screenMenuAlr2,    // вниз
    &screenMenuAlarm,

    &screenMain1, // кнопка set

    selectMenuAlarm,      // Краткое нажатие средней кнопки
    midStub,      // Долгое нажатие средней кнопки
    buttonReceiverMenu, // Обработчик кнопок в этом пункте
    4,
    {&textAlarm, &textAlarmDays, &textAlarmOffDays, &textAlarmOn}
};

//----------------------------------------------------------------------------------------------------------------------
ScreenDescript screenMenuAlr2 =
{
    stateMenuAlarm3,
    NULL, //blink
    1,               //автосброс режима

    &screenMenuAlr2,   // Право
    &screenMenuAlarm,  // Лево
    &screenMenuAlr1,   // вверх
    &screenMenuAlr2,   // вниз
    &screenMenuAlarm,

    &screenMain1, // кнопка set

    selectMenuAlarm,      // Краткое нажатие средней кнопки
    midStub,      // Долгое нажатие средней кнопки
    buttonReceiverMenu, // Обработчик кнопок в этом пункте
    4,
    {&textAlarm, &textAlarmDays, &textAlarmOffDays, &textAlarmOn}
};

//----------------------------------------------------------------------------------------------------------------------
ScreenDescript screenMenuPomidoroWork =
{
    stateMenuAlarm3,
    NULL, //blink
    1,               //автосброс режима

    &screenMenuPomidoroWork,      // Право
    &screenMenuPomidoro,          // Лево
    &screenMenuPomidoroWork,      // вверх
    &screenMenuPomidoroSmallRest, // вниз
    &screenMenuPomidoro,

    &screenMain1,       // кнопка set

    selectMenuPomidoroWork, // Краткое нажатие средней кнопки
    midStub,                // Долгое нажатие средней кнопки
    buttonReceiverMenu,     // Обработчик кнопок в этом пункте
    3,
    {&textMenuPomWorkSel, &textMenuPomSmallRest, &textMenuPomBigRest}
};

//----------------------------------------------------------------------------------------------------------------------
ScreenDescript screenMenuPomidoroSmallRest =
{
    stateMenuAlarm3,
    NULL, //blink
    1,               //автосброс режима

    &screenMenuPomidoroSmallRest,   // Право
    &screenMenuPomidoro,  // Лево
    &screenMenuPomidoroWork,   // вверх
    &screenMenuPomidoroBigRest,   // вниз
    &screenMenuAlarm,

    &screenMain1, // кнопка set

    selectMenuPomidoroSmallRest, // Краткое нажатие средней кнопки
    midStub,                     // Долгое нажатие средней кнопки
    buttonReceiverMenu,          // Обработчик кнопок в этом пункте
    3,
    {&textMenuPomWork, &textMenuPomSmallRestSel, &textMenuPomBigRest}
};

//----------------------------------------------------------------------------------------------------------------------
ScreenDescript screenMenuPomidoroBigRest =
{
    stateMenuAlarm3,
    NULL, //blink
    1,               //автосброс режима

    &screenMenuPomidoroBigRest,   // Право
    &screenMenuPomidoro,  // Лево
    &screenMenuPomidoroSmallRest,   // вверх
    &screenMenuPomidorosNumInDay,   // вниз
    &screenMenuAlarm,

    &screenMain1, // кнопка set

    selectMenuPomidoroBigRest, // Краткое нажатие средней кнопки
    midStub,                   // Долгое нажатие средней кнопки
    buttonReceiverMenu,        // Обработчик кнопок в этом пункте
    3,
    {&textMenuPomWork, &textMenuPomSmallRest, &textMenuPomBigRestSel}
};

//----------------------------------------------------------------------------------------------------------------------
ScreenDescript screenMenuPomidorosNumInDay =
{
    stateMenuAlarm3,
    NULL, //blink
    1,               //автосброс режима

    &screenMenuPomidorosNumInDay,    // Право
    &screenMenuPomidoro,             // Лево
    &screenMenuPomidoroBigRest,      // вверх
    &screenMenuPomidorosNumInSeries, // вниз
    &screenMenuAlarm,

    &screenMain1, // кнопка set

    selectMenuPomidoroNumInDay, // Краткое нажатие средней кнопки
    midStub,                    // Долгое нажатие средней кнопки
    buttonReceiverMenu,         // Обработчик кнопок в этом пункте
    2,
    {&textMenuPomNumSel, &textMenuPomSeries}
};

//----------------------------------------------------------------------------------------------------------------------
ScreenDescript screenMenuPomidorosNumInSeries =
{
    stateMenuAlarm3,
    NULL, //blink
    1,               //автосброс режима

    &screenMenuPomidorosNumInSeries, // Право
    &screenMenuPomidoro,             // Лево
    &screenMenuPomidorosNumInDay,    // вверх
    &screenMenuPomidorosNumInSeries, // вниз
    &screenMenuAlarm,

    &screenMain1, // кнопка set

    selectMenuPomidoroNumInSeries, // Краткое нажатие средней кнопки
    midStub,                       // Долгое нажатие средней кнопки
    buttonReceiverMenu,            // Обработчик кнопок в этом пункте
    2,
    {&textMenuPomNum, &textMenuPomSeriesSel}
};

//----------------------------------------------------------------------------------------------------------------------
ScreenDescript screenMenuDebugAHT10 =
{
    stateMenuDebug,
    NULL, //blink
    1,               //автосброс режима

    &screenMenuDebugAHT10,  // Право
    &screenMenuDebug,       // Лево
    &screenMenuDebugAHT10,  // вверх
    &screenMenuDebugBMP280,      // вниз
    &screenMain1,          //Долгое нажатие влево

    &screenMain1, // кнопка set

    midStub,           // Краткое нажатие средней кнопки
    midStub,           // Долгое нажатие средней кнопки
    buttonReceiverMenu, // Обработчик кнопок в этом пункте
    1,
    {&textDebugAHT10}
};

//----------------------------------------- 0-----------------------------------------------------------------------------
ScreenDescript screenMenuDebugBMP280 =
{
    stateMenuDebug,
    NULL, //blink
    1,               //автосброс режима

    &screenMenuDebugBMP280,  // Право
    &screenMenuDebug,        // Лево
    &screenMenuDebugAHT10,   // вверх
    &screenMenuDebugBMP280,  // вниз
    &screenMain1,            //Долгое нажатие влево

    &screenMain1, // кнопка set

    midStub,      // Краткое нажатие средней кнопки
    midStub,           // Долгое нажатие средней кнопки
    buttonReceiverMenu, // Обработчик кнопок в этом пункте
    1,
    {&textDebugBMP280}
};

//----------------------------------------------------------------------------------------------------------------------
ScreenDescript screenEditTime =
{
    stateTimeEdit,
    &textBlinkTimeEdit, //blink
    0,               //автосброс режима

    &screenEditTime,   // Право
    &screenEditTime,   // Лево
    &screenEditTime,   // вверх
    &screenEditTime,   // вниз
    &screenMenuTime,

    &screenEditTime, // кнопка set (В режиме редактирования не используется)

    saveTime,      // Краткое нажатие средней кнопки
    midStub,        // Долгое нажатие средней кнопки
    buttonReceiverTimeEdit, // Обработчик кнопок в этом пункте
    1,
    {&textTimeEdit}
};


//----------------------------------------------------------------------------------------------------------------------
ScreenDescript screenEditAlarm =
{
    stateAlarmEdit,
    &textBlinkTimeEdit, //blink
    0,               //автосброс режима

    &screenEditAlarm,    // Право
    &screenEditAlarm,    // Лево
    &screenEditAlarm,    // вверх
    &screenEditAlarm,    // вниз
    &screenMenuAlr0,

    &screenEditAlarm, // кнопка set (В режиме редактирования не используется)

    saveAlarm,      // Краткое нажатие средней кнопки
    midStub,        // Долгое нажатие средней кнопки
    buttonReceiverAlarmEdit, // Обработчик кнопок в этом пункте
    4,
    {&textTimeEdit, &textAlarmDays, &textAlarmOffDays, &textAlarmOn}
};

//----------------------------------------------------------------------------------------------------------------------
ScreenDescript screenEditDate =
{
    stateDateEdtit,
    &textBlink32, //blink
    0,               //автосброс режима

    &screenEditDate,  // Право
    &screenEditDate,  // Лево
    &screenEditDate,  // вверх
    &screenEditDate,  // вниз
    &screenMenuTime,

    &screenMenuTime, // кнопка set

    saveDate,      // Краткое нажатие средней кнопки
    midStub,      // Долгое нажатие средней кнопки
    buttonReceiverDateEdit, // Обработчик кнопок в этом пункте
    1,
    {&textEdit32}
};

