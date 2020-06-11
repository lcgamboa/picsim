
# PICsim - PIC Simulator

PICsim emulates some PIC microcontroller and periferics such as USART and timers, the simulator architecture permit easy implementation of external elements in c language.
It can be used as a standalone simulator (picsim executable) or as a library in other programs (As in [PICSimLab](https://github.com/lcgamboa/picsimlab)).



## Pic supported hardware:

* ADC
* Interrupts
* WTD
* TMR0
* TMR1
* TMR2
* USART
* CCP1 ->PWM (8bits) and Comparator
* CCP2 ->PWM (8bits) and Comparator
* CCP3 ->PWM (8bits) and Comparator
* EEPROM
* IO PORTS

![PICsim Hardware Support](docs/support.png?raw=true "PICsim Hardware support")


[Online Documentation](https://lcgamboa.github.io/picsim/)

[Changelog](./CHANGELOG.md)


[TODO list](./TODO.md)


## Utils:


- com0com	- For serial emulation in windows  http://com0com.sourceforge.net/ 

- tty0tty 	- For serial emulation in linux    https://github.com/lcgamboa/tty0tty 

- gputils	- For assemble examples            http://gputils.sourceforge.net/

- sdcc		- For compile examples             http://sdcc.sourceforge.net/

- PICSimLab       - Simulator that use PICsim       https://github.com/lcgamboa/picsimlab

