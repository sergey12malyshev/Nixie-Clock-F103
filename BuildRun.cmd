rem скрипта вызова командного файла для сборки проекта

set dir=MDK-ARM

cd %dir%
call Clock-f103.BAT

echo Build completed!
pause