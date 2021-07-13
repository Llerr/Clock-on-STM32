# Clock-on-STM32
Проект часов на stm32f103ret
Используются датчики
1. Температура и влажность AHT10
2. Температура и давление BMP280
3. Освещённость MAX44009

Папка Data содержит ресурсы которые добалены в проект, её содержимое не нужно для сборки.

Управление.
кнопки джойстика вправо/влево/вверх/вниз используются для переключения экранов, навигации в меню, редактирования.
Центральная кнопка, выбор в меню, подтверждение редактирования, запуск/остановка таймера.
Долгое нажатие кнопки влево завершает редактирование без сохранения.
Кнопка set открывает/закрывает меню.
кнопка reset заведена на пин reset микроконтроллера.