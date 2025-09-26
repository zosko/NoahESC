# NoahESC
- Atmega8 based ESC.

### Features
- [X] PWM
- [X] 30Amps
- [X] 2 - 4S battery
- [X] Low cost

## Scheme
![Scheme](images/scheme.png)

## Boards Preview
Board|PCB
---------|---------
<img src="images/board.png" alt="Board" width="500"/>|<img src="images/pcb.png" alt="View 1" width="500"/>

### Flashing
Atmega8 must be flashed via ICSP microcontroller pins. 

**Arduino UNO as ISP programmer**
- `avrdude -c stk500v1 -p m8 -P /dev/tty.usbmodem14401 -b 19200 -U flash:w:firmware.hex:i`
- `avrdude -c stk500v1 -p m8 -P /dev/tty.usbmodem14401 -b 19200 -U lfuse:w:0x3f:m -U hfuse:w:0xca:m`

**USBasp**
- `avrdude -c usbasp -p m8 -U flash:w:firmware.hex:i`
- `avrdude -c usbasp -p m8 -U lfuse:w:0x3f:m -U hfuse:w:0xca:m`

**Download**: [Firmware](firmware.hex)

## PCB Design

![PCBWay_logo](images/pcbway_logo.png)

**Huge thanks to [PCBWay](https://pcbway.com) for sponsoring this project!**

PCBWay is a leading provider of high-quality printed circuit boards (PCBs), offering reliable and affordable solutions for both hobbyists and professionals. Their services include rapid prototyping, PCB assembly, instant online quotations, expert design verification, and a streamlined ordering experience.

Their comprehensive range of services includes:
- PCB prototyping
- Assembly services
- Instant online quotations
- Expert design verification
- A streamlined, user-friendly ordering system
