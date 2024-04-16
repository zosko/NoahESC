## [warning] - In Development

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
Atmega8 must be flashed via ICSP microcontroller pins. I have use Arduino UNO as ISP programmer
- `avrdude -c stk500v1 -p m8 -P /dev/tty.usbmodem14401 -b 19200 -U flash:w:firmware.hex:i`
- `avrdude -c stk500v1 -p m8 -P /dev/tty.usbmodem14401 -b 19200 -U lfuse:w:0x3f:m -U hfuse:w:0xca:m`

**Download**: [Firmware](firmware.hex)

## PCB Design

For PCB design i will use services from SeeedFusion. 

Seeed Fusion PCB Assembly Service offers one-stop prototyping for PCB manufacture, PCB assembly and as a result they produce superior quality PCBs and Fast Turnkey PCBA from 7 working days. When you prototype with Seeed Fusion, they can definitely provide Free DFA and Free functional tests for you! 

Check out their website to know about their manufacturing capabilities and service.
https://www.seeedstudio.com/pcb-assembly.html

## Reasons to choose Seeed Studio
- They provide PCB services at extremely low pricing and with excellent quality.
- Their offer is structured in such a way that everyone may have these boards at a reasonable price.
- They have a highly knowledgeable crew that leads their clients to avail deals and guides them about the costs and rates of different services.
- A four-layer board with a comparable feature costs $5 for 10 pieces and is made in four days.
- SMT stencil with size (10cm x 13cm) is available for $8.00 per piece.
