# Nixie-Clock-F103
Nixie Clock project stm32f103 + ds18b20
(Программный проект часов на ГРИ ИН-14 и МК stm32f103)

<img src="https://github.com/sergey12malyshev/Nixie-Clock-F103//raw/master/pictures/1670937612205.jpg" width=25% height=25%> 
<img src="https://github.com/sergey12malyshev/Nixie-Clock-F103//raw/master/pictures/1670937612194.jpg" width=25% height=25%> 
<img src="https://github.com/sergey12malyshev/Nixie-Clock-F103//raw/master/pictures/1670937612155.jpg" width=25% height=25%> 

## Инструментарий
*Keil uVision v5* + *VS Code*

## RTOS
Суперцикл

## Сборка
Запустить **Clock-f103.BAT**

## Прошивка ПО
Запустить **programFlash.bat**

## Управление
- Кнопка 1 - Настройка минут
- Кнопка 2 - Показ температуры на 2 сек.
- Кнопка 3 - Настройка часов

Внимание!! При генерации кода в CubeMX стирается коментирование в инициалзации  MX_RTC_Init. Для сохранения времени при потере питания необходимо закомментировать установку времени и даты.

## Характеристики питания ИН-14:
Напряжение анода: 172 В

Ток анода: I = 7,2 В / 13 кОм = 0,55 мА

Ток запятой: I = 0,73 В / 10 кОм = 0,07 мА

Динамическая индикация

## Полезная информация
https://narodstream.ru/stm-urok-92-datchik-temperatury-ds18b20-chast-3/ - работа с ds18b20

https://habr.com/ru/post/431868/

https://cxem.net/mc/mc187.php - аппаратная основа (питание, дешифрация)

https://rudatasheet.ru/tubes/in-14/
