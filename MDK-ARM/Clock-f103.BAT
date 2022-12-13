SET PATH=C:\Keil_v5\ARM\ARMCC\Bin;C:\Program Files (x86)\Common Files\Oracle\Java\javapath;C:\WINDOWS\system32;C:\WINDOWS;C:\WINDOWS\System32\Wbem;C:\WINDOWS\System32\WindowsPowerShell\v1.0\;C:\WINDOWS\System32\OpenSSH\;C:\Program Files\Intel\WiFi\bin\;C:\Program Files\Common Files\Intel\WirelessCommon\;C:\Program Files (x86)\STMicroelectronics\STM32 ST-LINK Utility\ST-LINK Utility;c:\Program Files (x86)\Microsoft SQL Server\100\Tools\Binn\;c:\Program Files\Microsoft SQL Server\100\Tools\Binn\;c:\Program Files\Microsoft SQL Server\100\DTS\Binn\;C:\Program Files\OpenVPN\bin;C:\Program Files\MATLAB\R2018a\runtime\win64;C:\Program Files\MATLAB\R2018a\bin;C:\Program Files (x86)\MATLAB\MATLAB Compiler Runtime\v81\runtime\win32;C:\Program Files\Git\cmd;C:\Program Files\TortoiseGit\bin;C:\Users\Сергей\AppData\Local\Microsoft\WindowsApps;C:\Program Files\Intel\WiFi\bin\;C:\Program Files\Common Files\Intel\WirelessCommon\;C:\Users\Сергей\AppData\Local\GitHubDesktop\bin;C:\Users\Сергей\AppData\Local\Microsoft\WindowsApps;;C:\Users\Сергей\AppData\Local\Programs\Microsoft VS Code\bin
SET CPU_TYPE=STM32F103C8
SET CPU_VENDOR=STMicroelectronics
SET UV2_TARGET=Clock-f103
SET CPU_CLOCK=0x007A1200
"C:\Keil_v5\ARM\ARMCC\Bin\ArmAsm" --Via "clock-f103\startup_stm32f103xb._ia"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "clock-f103\ds18b20.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "clock-f103\main.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "clock-f103\stm32f1xx_it.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "clock-f103\stm32f1xx_hal_msp.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "clock-f103\smooth.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "clock-f103\system_stm32f1xx.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "clock-f103\stm32f1xx_hal_gpio_ex.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "clock-f103\stm32f1xx_hal_rtc.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "clock-f103\stm32f1xx_hal_rtc_ex.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "clock-f103\stm32f1xx_hal.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "clock-f103\stm32f1xx_hal_rcc.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "clock-f103\stm32f1xx_hal_rcc_ex.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "clock-f103\stm32f1xx_hal_gpio.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "clock-f103\stm32f1xx_hal_dma.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "clock-f103\stm32f1xx_hal_cortex.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "clock-f103\stm32f1xx_hal_pwr.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "clock-f103\stm32f1xx_hal_flash.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "clock-f103\stm32f1xx_hal_flash_ex.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "clock-f103\stm32f1xx_hal_exti.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "clock-f103\stm32f1xx_hal_tim.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "clock-f103\stm32f1xx_hal_tim_ex.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "clock-f103\stm32f1xx_hal_uart.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmLink" --Via "Clock-f103\Clock-f103.lnp"
"C:\Keil_v5\ARM\ARMCC\Bin\fromelf.exe" "Clock-f103\Clock-f103.axf" --i32combined --output "Clock-f103\Clock-f103.hex"

pause