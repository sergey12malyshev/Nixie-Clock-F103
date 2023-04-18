# Nixie-Clock-F103
Nixie Clock project stm32f103 + ds18b20 + ИН-14

Hardware-software project of a clock on nixies indicators with an temperature display

Программно-аппаратный проект часов на газоразрядных индикаторах с функцией показа температуры

<img src="https://github.com/sergey12malyshev/Nixie-Clock-F103//raw/master/pictures/1677171791876.jpg" width=30% height=35%> <img src="https://github.com/sergey12malyshev/Nixie-Clock-F103//raw/master/pictures/1677174372862.jpg" width=30% height=35%> <img src="https://github.com/sergey12malyshev/Nixie-Clock-F103//raw/master/pictures/1670937612155.jpg" width=30% height=30%> 

## Инструментарий
### Компилятор
*Keil uVision v5.30* 

### Редактор кода
*VS Code* файл Nixie-Clock-F103.code-workspace

### Статический анализатор кода
Cppcheck 2.10 https://cppcheck.sourceforge.io/

Запустить RunStaticAnalysisCODE.cmd

Возможен вывод результата анализа в файл

## Сборка 
Запустить **BuildRun.cmd**

## Прошивка ПО
Запустить **programFlash.bat**

## UART/CLI
Для PuTTY запустить **PuTTYstart.cmd**

При включении в UART происходит выдача версии ПО и статус инициализации ds18b20. Во время работы происходит выдача в UART температуры
в максимальном разрешении если установлен макрос DEBUG

UART PIN: PA10 - RX, PA9 - TX

## WDT
Активирован сторожевой таймер со временем сброса ~5 секунд

TODO: Есть ли влияние WDT на батарейку? Пин VBAT питает схему тактирования LSE. WDT тактируется от LSI, который иммеет питание от VDD. Значит влияние WDT на потребление от VBAT отсутствует.

## Аппаратная часть
- МК - STM32F103C8T6 (ARM Cortex-M3; 72 МГц; FLASH 64 кБ; ОЗУ 20 кБ)
- Дешифратор - К155ИД1
- Индикаторы - ИН-14
- Датчик температуры - ds18b20
- Повышающий преобразователь - MC34063

## Управление
- Кнопка 1 - Настройка минут
- Кнопка 2 - Показ температуры на 2 сек.
- Кнопка 3 - Настройка часов

Внимание!! При генерации кода в CubeMX стирается комментирование в функции инициализации MX_RTC_Init. Для сохранения времени при потере питания необходимо закомментировать установку времени и даты.

## Характеристики питания ИН-14 в устройстве:
Напряжение анода: 172 В

Ток анода: I = 7,2 В / 13 кОм = 0,55 мА

Ток запятой: I = 0,73 В / 10 кОм = 0,07 мА

Динамическая индикация

## Code Style
https://habr.com/ru/post/325678/

## Полезная информация
https://narodstream.ru/stm-urok-92-datchik-temperatury-ds18b20-chast-3/ - работа с ds18b20

https://habr.com/ru/post/431868/

https://cxem.net/mc/mc187.php - аппаратная основа (питание, дешифрация)

https://rudatasheet.ru/tubes/in-14/
