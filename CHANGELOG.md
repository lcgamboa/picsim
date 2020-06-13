# Changelog


## (unreleased)

### New

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


