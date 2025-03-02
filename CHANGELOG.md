# Changelog


## (unreleased)

### Other

* Fix PIC18F interrupt priority execution. [lcgamboa]

* Docs examples updated. [lcgamboa]

* Support to PIC18F67J60 added (without ethernet controller) [lcgamboa]

* Fix PIC16F TRISx mirror value at reset. [lcgamboa]

* Fix PIC18F4580 AN0 pin number. [lcgamboa]

* Fix PIC18F4580  number of CCPs to 1. [lcgamboa]

* Fix ack bit in mssp I2C master mode. [lcgamboa]

* Disable port/tris mirror for PIC16F886 and PIC16F877. [lcgamboa]

* Clang format. [lcgamboa]

* Fix serial file descriptor check. [lcgamboa]


## v0.9.0 (2023-07-29)

### Fix

* Fix missing second cycle for MOVFF PIC18F instruction. [lcgamboa]

### Other

* Add supoort to PIC16F819, PIC16F1827 and PIC16F1847. [lcgamboa]

* Fix typo in TRISB of PIC16FE. [lcgamboa]

* Fix serial baudrate error calc. [lcgamboa]

* Fix PIC16F688 adc. [lcgamboa]

* Support to PIC16F688 added. [lcgamboa]

* Fix initial pin value after reset. [lcgamboa]

* Revert the previus commit. [lcgamboa]

* Function disable_debug added to all PICs. [lcgamboa]

* Support to PIC16F1516 and PIC18F24Q10 added. [lcgamboa]

* Support to PIC16F1829 added. [lcgamboa]

* Fix typo. [lcgamboa]


## v0.8.12 (2023-01-18)

### New

* Support to PIC16F887 added. [lcgamboa]

### Fix

* Ioupdated updated only when value is changed. [lcgamboa]

* Repeated start (RSEN bit) bug and ACK bits fixed for MSSP I2C master mode. [lcgamboa]

* Fix PIC16F877 PORTB interrupt on change. [lcgamboa]

* PIC16F1887 ADC and ANSEL fixed. [lcgamboa]

### Other

* Support to PIC16F886 and PIC18F26K80 added. [lcgamboa]

* Fix SPI Master mode to read on rissing edge. [lcgamboa]

* Fix multiple bytes read in I2C master mode os MSSP. [lcgamboa]

* Support to read data in MSSP SPI master mode added. [lcgamboa]

* Increase uart precision and add BAUDCON register in some PICs. [lcgamboa]

* Add support to use BAUDCTL and SPBRGH in PIC18F887. [lcgamboa]

* Add support to PIC18F4580 and fix missing SSPADD register in PIC16F887. [lcgamboa]

* Revert lto flag to mac compatibility. [lcgamboa]

* Fix makefile. [lcgamboa]

* Makefile updated. [lcgamboa]

* Fix missing ioupdated. [lcgamboa]

* Use gcc-ar for compatibility with flatpak-builder. [lcgamboa]

* Merge pull request #5 from hsorbo/hsorbo/gh-actions-build. [lcgamboa]

* Build picsim on macOS and Linux using github actions. [Håvard Sørbø]

* Remove duplicated example file. [lcgamboa]

* Merge pull request #3 from hsorbo/hsorbo/macos-build. [lcgamboa]

* Make picsim build on macos using xcode-tools. [Håvard Sørbø]

* Support to run multiple instances added. [lcgamboa]

* Avoid use mod operator. [lcgamboa]

* Add support to set microcontroller VCC to use with ADC. [lcgamboa]

* Fix PIC16F18855 PDIP peripherals pin map. [lcgamboa]

* Basic support to PIC16F18855 ADC. [lcgamboa]

* Fix P16E ANSELx and enable ADC for PIC16F18855. [lcgamboa]

* Remove -flto to remove mingw bugs. [lcgamboa]

* Support to open collector pins simulation added. [lcgamboa]

* Fix PIC16F887 adc reference selection. [lcgamboa]

* Makefile updated. [lcgamboa]

* Makefile updated. [lcgamboa]

* Makefile updated. [lcgamboa]

* Ioupdated flag implemented. [lcgamboa]

* Bitbang serial functions renamed. [lcgamboa]


## v0.8.9 (2021-07-25)

### Changes

* Support to use VREF in ADC added. [lcgamboa]

### Fix

* Fix bitbang UART to work without a real serial port connection. [lcgamboa]

* Not defined PIE2 bug fixed for PIC16F628A. [lcgamboa]

* Misplaced break in instruction SUBLW fixed. [lcgamboa]

### Other

* Makefiles updated. [lcgamboa]

* P16F and P18F suport to capture using TIMER1. [lcgamboa]


## v0.8.7 (2021-04-25)

### New

* Inital support to PIC18F67J94. [lcgamboa]

* Support to bitbang uart added. [lcgamboa]

* Initial suppport to PIC18F46J50. [lcgamboa]

* PIC18Fx7K40 second usart support. [lcgamboa]

* Support to multiple serial. [lcgamboa]

* Microcontroller dynamic register. [lcgamboa]

### Fix

* Missing LATE on 28 pins device bug removed. [lcgamboa]

* Serial bitbang tx bug fixed. [lcgamboa]

* PIC18F CCP1 PWM output bug fixed. [lcgamboa]

* Missing ADC channels added in PIC16F1788. [lcgamboa]

* Missing first PIC in list bug fixed. [lcgamboa]

* Correct name of PIC in register macro. [lcgamboa]


## v0.8.1 (2020-06-17)

### New

* PIC16E PPS output support added. [lcgamboa]

* PIC18Fx7K40 PPS output support added. [lcgamboa]

* PIC16F18324 WDT and EEPROM support. [lcgamboa]

* Doxygen docs. [lcgamboa]

* PIC18F4XK40 eeprom support. [lcgamboa]

* PIC16F18324 added. [lcgamboa]

* PIC18FX7K40 IOC and NVM support. [lcgamboa]

* PIC18FX7K40 WDT support. [lcgamboa]

* PIC18FX7K40 MSSP support. [lcgamboa]

* P16E watchdog support. [lcgamboa]

* PIC18Fx7K40 initial support of timers and interrupt. [lcgamboa]

* PIC18Fx7K40 basic adc implemented. [lcgamboa]

* Support to new PIC18F. [lcgamboa]

* Support to PIC18F47K40 and PIC18F27K40 improved. [lcgamboa]

* MSSP BF flags SPI added. [lcgamboa]

### Changes

* Shadow stack moved out of RAM. [lcgamboa]

### Fix

* PIC16F18324 ADC and WDT fixed. [lcgamboa]

* P18 TOSU write bug fixed. [lcgamboa]

* WDT time error bug fixed. [lcgamboa]

* P16E hex config read bug fixed. [lcgamboa]

* SPI BF status flag bug fixed. [lcgamboa]

* PIC18Fx7K40 access bank bug fixed. [lcgamboa]

* PIC18Fx7K40 serial RX bug fixed. [lcgamboa]

* Sleep don't disable on reset bug fixed. [lcgamboa]

* Shadow registers bug fixed. [lcgamboa]

* P18 MULLW bug fixed. [lcgamboa]

* Set hw dir P18 and P16E bug fixed. [lcgamboa]

* MSSP I2C mode fixed. [lcgamboa]

* Mssp i2c master bug fixed. [lcgamboa]

* Ansel change bug fixed. [lcgamboa]

* Indf bank bug fixed. [lcgamboa]

* Hexfile for 16e bug fixed. [lcgamboa]


## v0.8.0 (2020-06-11)

### Other

* P16E and P18 LATX write bug  fixed. [lcgamboa]

* Makefiles updated. [lcgamboa]

* P16E timer2 fix missing 64 prescaler. [lcgamboa]

* P16E interrup bank bug fixed. [lcgamboa]

* P16e status banking. [lcgamboa]

* P16E status banking bug fixed and ADC null chanell bug fixed. [lcgamboa]

* P16E on change PORTB interrupt. [lcgamboa]

* P16E inital support to INT and PORTB INT. [lcgamboa]

* P16E MSSP inital support. [lcgamboa]

* Eeprom read ihx bug fix. [lcgamboa]

* Eeprom save and load error bug fixed. [lcgamboa]

* Adc and eeprom P16E fixes. [lcgamboa]

* Makefile updated. [lcgamboa]

* ANSEL bug fixed. [lcgamboa]

* PIC16F18855 QFN pinout added. [lcgamboa]

* Modularization of periferics. [lcgamboa]

* P16 periferic modularization. [lcgamboa]

* Pin name bug fixed. [lcgamboa]

* New pic18f27k40 initial support added. [lcgamboa]

* Modularization and support to new pics 16f1939 16f1788 16f1789. [lcgamboa]

* Makefile.js updated. [lcgamboa]

* Set a pin with 0 bug fixed. [lcgamboa]

* Set a pin with 0 bug fixed. [lcgamboa]

* Set pin with 0 bug fixed. [lcgamboa]

* Serialbaud initialization bug fixed. [lcgamboa]

* Mclr pin value added to pic struct. [lcgamboa]

* Pic_getMCLRE function added. [lcgamboa]

* Port latch bug fixed. [lcgamboa]

* Serial rx bug fix. [lcgamboa]

* Pic18f4550 PBADEN configuration bit support added. [lcgamboa]

* Pic18f4550 PBADEN configuration bit support added. [lcgamboa]

* Cpaint putbitmap bug fixed. [lcgamboa]

* Header files moved to include dir. [root]

* Default open value bug fixed. [lcgamboa]

* Empty hexfile bug fixed. [lcgamboa]

* SPI master simple support implemented. [lcgamboa]

* Pin types support to VCC and VSS. [lcgamboa]

* Set signed char as default. [lcgamboa]

* Initialization of open pin values. [Luis Claudio Gambôa Lopes]

* Merge branch 'master' of https://github.com/lcgamboa/picsim. [Luis Claudio Gambôa Lopes]

* Var initialization bug fix. [Luis Claudio Gambôa Lopes]

* Var initialization bug fix. [Luis Claudio Gambôa Lopes]

* Set pointer to NULL on delete. [lcgamboa]

* PIC18F4550 CCP count fixed. [lcgamboa]

* _pic pointer argument removed. [lcgamboa]

* INT0 legacy interrupt code support. [lcgamboa]

* Serial RCIF clear bug fix. [lcgamboa]

* Code optimization. [lcgamboa]

* Makefile fix. [lcgamboa]

* Pic_erase_flash implemented. [lcgamboa]

* Hexfile errors in return. [lcgamboa]

* TXREG overrun bug fix. [lcgamboa]

* Functions print argument removed. Now use pic->print. [lcgamboa]

* Serial code improvement. [lcgamboa]

* Load hex function prototype added. [lcgamboa]

* GetPinName function added. [lcgamboa]

* File clean. [lcgamboa]

* File rearrangement. [lcgamboa]

* Readme update. [lcgamboa]

* Readme update. [lcgamboa]

* Readme update. [lcgamboa]

* Readme update. [lcgamboa]

* PIC16F18855 PORT access bug fix. [lcgamboa]

* PIC16F18855 initial peripheral support. [lcgamboa]

* PIC16F enhanced initial support. [lcgamboa]

* Printf debug info bug fix. [lcgamboa]

* TOS access bug fix. [lcgamboa]

* TOS access bug fix. [lcgamboa]

* Fix family mismatch bug. [lcgamboa]

* Intial support to p16 enhanced. [lcgamboa]

* Inital support to 16F enhanced. [lcgamboa]

* Fix error printing. [lcgamboa]

* Support to PIC18F45k50 and PIC16F1619 added. [lcgamboa]

* Analog pins configuration bug fix. [Luis Claudio Gamboa Lopes]

* PIC16F84A and PIC18F4520 support added. [Luis Claudio Gamboa Lopes]

* Update year in files headers. [Luis Claudio Gamboa Lopes]

* PIC18F interrupt bugfix, CCP implentation. [Luis Claudio Gamboa Lopes]

* P18f subwfb bug fix and FSR to string conversion implemented. [Luis Claudio Gamboa Lopes]

* TOS write operation support implemented. [Luis Claudio Gamboa Lopes]

* Memory boundary bug fix. [Luis Claudio Gamboa Lopes]

* WDT period propierty added. [Luis Claudio Gamboa Lopes]

* Pic18f jump 64k boundary bug fix. [Luis Claudio Gamboa Lopes]

* Readme update. [Luis Claudio Gamboa Lopes]

* PORTB INT RBIF bug fix. [Luis Claudio Gamboa Lopes]


## v0.6.0 (2015-10-28)

### Other

* Crosscompiler Makefile. [Luis Claudio Gamboa Lopes]

* Picsimlab removed of repository. [Luis Claudio Gamboa Lopes]

* Default open pin value bug fix. [Luis Claudio Gamboa Lopes]

* Mplabx debuuger support implemented. [Luis Claudio Gamboa Lopes]

* Mplabx debuuger support implemented. [Luis Claudio Gamboa Lopes]

* Write_hex function bugfix. [Luis Claudio Gamboa Lopes]

* Buzzer bug fix. [Luis Claudio Gamboa Lopes]

* Animated cooler implemented. [Luis Claudio Gamboa Lopes]

* Default pin open value set and get implemented. [Luis Claudio Gamboa Lopes]

* Locale converted to utf8. [Luis Claudio Gamboa Lopes]

* Serial baud rate emulation support and Temp display. [Luis Claudio Gamboa Lopes]

* Pic16f eeprom hexfile bugfix. [Luis Claudio Gamboa Lopes]

* Reload las hex file implemented. [Luis Claudio Gamboa Lopes]

* Lcd cursor support added. [Luis Claudio Gamboa Lopes]

* Serial tris verification. [Luis Claudio Gamboa Lopes]

* LCD full fontset support. [Luis Claudio Gamboa Lopes]

* Board files rearrangement. [Luis Claudio Gamboa Lopes]

* CCP compare support to P16F. [Luis Claudio Gamboa Lopes]

* CCP compare support to P16F. [Luis Claudio Gamboa Lopes]

* Initial release version 5.0. [Luis Claudio Gamboa Lopes]


