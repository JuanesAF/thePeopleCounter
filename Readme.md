# People counter!

This project uses the Curiosity Nano Development board PIC16F15244 to count the number of people inside a closed place.



## Related Documentation
- [PIC16F15244 Product Page](https://www.microchip.com/wwwproducts/en/PIC16F15244)
- [Datasheet PIC16F15244](http://ww1.microchip.com/downloads/en/DeviceDoc/PIC16F15213-14-23-24-43-44-Data-Sheet-DS40002195B.pdf)
- [PIC16F15244 Curiosity Nano Evaluation Kit Page](https://www.microchip.com/developmenttools/ProductDetails/EV09Z19A)
- [Board documentation](http://ww1.microchip.com/downloads/en/DeviceDoc/PIC16F15244-Curiosity-Nano-Hardware-User-Guide-DS50003045A.pdf)
- [Manual de usuario XC8 compiler](http://ww1.microchip.com/downloads/en/devicedoc/50002053g.pdf)
- [Fundamentals of the C Programming Language](https://microchipdeveloper.com/tls2101:start)
- [PIC16F15244 Code Examples on GitHub](https://github.com/microchip-pic-avr-examples?q=pic16f1524)
- [PIC16F15244 Curiosity Nano Schematics](https://ww1.microchip.com/downloads/en/DeviceDoc/PIC16F15244_Curiosity_Nano_Schematics.pdf)



## Software Used

- [MPLAB® X IDE 5.40 or newer](http://www.microchip.com/mplab/mplab-x-ide)
- [MPLAB® XC8 2.20 or a newer compiler](https://www.microchip.com/development-tools/pic-and-dspic-downloads-archive)
- [ MPLAB® Code Configurator (MCC) 3.95.0 or newer ](https://www.microchip.com/mplab/mplab-code-configurator)
- [ MPLAB® Forum XC8](https://www.microchip.com/forums/f249.aspx)
- [Microchip Packs Repository](https://packs.download.microchip.com/)

## Hardware Used
The Microchip PIC16F15244 Curiosity Nano evalutation kit is a hardware platform to evaluate PIC microcontrollers. The evaluation kit comes with a fully integrated programmer and debugger that provides seamless integration with Microchip MPLAB X. The kit provides access to the features of the PIC16F15244 enabling easy integration of the device in a custom design. The kit features variable voltage, a virtual serial port, and a DGI interface for easy development and debugging.
- PIC16F15244 Curiosity Nano [(EV09Z19A)](https://www.microchip.com/Developmenttools/ProductDetails/EV09Z19A)
- Micro-USB to USB 2.0 cable
- LCD Display 16x2
- Push button
- Potentiometer 10k
- Resistance 330
- Jumpers
- adapter 5v 1A
- Protoboard

![Curiosity Nano](https://external-content.duckduckgo.com/iu/?u=https://www.microchip.com/images/default-source/design-centers/8-bit-mcus/pic-device-selection/ev09z19a_pic16f15244-curiosity-nano-board-front-transparent.png?sfvrsn=8337e3b9_0&f=1&nofb=1)

![enter image description here](https://external-content.duckduckgo.com/iu/?u=http://www.hobbytronics.co.uk/image/cache/data/dealextreme/lcd-blue-16x2-500x500.jpg&f=1&nofb=1)

![enter image description here](https://external-content.duckduckgo.com/iu/?u=https://emartee.com/Images/websites/emartee.com/products/thumbnails/big/41797.jpg&f=1&nofb=1)

![enter image description here](https://external-content.duckduckgo.com/iu/?u=https://www.vapeitalia.it/media/catalog/product/cache/1/image/363x/5cfc8b4d9849831add20660d2bfd8996/c/a/cavo-micro-usb-15mt-cf737-matsuyama.jpg&f=1&nofb=1)
![enter image description here](https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcSQHClGVUAKXOtd89kzGMdwYVQi_2_lnk5IHA&usqp=CAU)
## Setup
1. Connect the PIC16f15244 Curiosity Nano board to a PC using the Micro-USB to USB 2.0 cable.
2. If not already on your system, download and install MPLABX IDE version 5.40 (or newer).
3. If not already on your system, download and install the XC8 C-Compiler version 2.20 (or newer).
4. Open the 'contador.X' project .

Connection diagram 
<a href="https://ibb.co/6JzYJ0w"><img src="https://i.ibb.co/YTm2TBQ/Conexion.png" alt="Conexion" border="0"></a>

## How to use
The device uses buttons to emulate the functions of 2 infrared sensors that would be located on the threshold of the entrance door.
The system counts the number of people entering and leaving the site and displays it on an LCD screen. In the event that a person enters the site, first the button connected to pin RB7 and then the button connected to pin RB5 of the Curiosity Nano must be shut off (without leaving it pressed), and in the event that a person leaves, the process is reversed, first the RB5 button is shut off and then the RB7 button.

The system allows you to set the maximum capacity, holding the button connected to the RA4 pin for 3 seconds, you can enter the "Configuration" section where you can navigate between 2 options, "Sum" and "Subtraction" by pressing the button once, to select one of the 2, press the same button for 5 seconds, then you have the option to change the maximum capacity of 10 in 10, to confirm and exit the menu, press the button again for 5 seconds.


Each option is displayed on the LCD. 


