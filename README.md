<!-- Please do not change this html logo with link -->
<a href="https://www.microchip.com" rel="nofollow"><img src="images/microchip.png" alt="MCHP" width="300"/></a>

# Getting Started with External High-Frequency Oscillator on AVR DB

The High Frequency Crystal Oscillator (XOSCHF) enables the use of an external crystal or an external clock signal up to 32MHz. This can be used as a clock source for the Main Clock (CLK_MAIN), the Real-Time Counter (RTC) and the 12-Bit Timer/Counter Type D (TCDn).

The Clock Failure Detection (CFD) feature can be used to detect if the output from a clock source stops and can switch the Main Clock to a different clock source to continue operation or shut down operation safely.

These examples show the following use cases for XOSCHF and CFD on the AVR DB family of microcontrollers:

* **XOSCHF with External Crystal**:
  Initialize XOSCHF for external crystal and change the main clock source to XOSCHF
* **XOSCHF with External Clock**:
  Initialize XOSCHF for external clock signal and change the main clock source to XOSCHF
* **RTC with XOSCHF**:
  Use XOSCHF as clock source for the RTC
* **TCD with XOSCHF**:
  Use XOSCHF as clock source for TCD0
* **TCD with XOSCHF and PLL**:
  Initialize the PLL with XOSCHF as clock source and use the PLL as clock source for TCD0
* **CFD on XOSCHF**:
  Initialize the CFD to monitor XOSCHF, enable the interrupt, toggle an LED if the clock source fails
* **CFD on Main Clock with NMI**:
  Initialize the CFD to monitor Main Clock with XOSCHF as clock source, enable the interrupt as a Non-Maskable Interrupt (NMI), toggle an LED with frequency derived from Main Clock

## Related Documentation

* [TB3272 - Getting Started with External High-Frequency Oscillator on AVR DB](https://microchip.com/DS90003272A) <!-- TODO: Update link once assigned -->
* [AVR128DB48 Device Page](https://www.microchip.com/wwwproducts/en/AVR128DB48)
* AVR128DB48 Curiosity Nano User Guide (link will be added once available)

## Software Used

* [Atmel Studio](https://www.microchip.com/mplab/avr-support/atmel-studio-7) 7.0.2397 or later
* Atmel Studio AVR-Dx_DFP version 1.2.56 or later
* For the MPLAB X version of these projects, please go to [this repository](https://github.com/microchip-pic-avr-examples/avr128db48-getting-started-with-xoschf-mplabx)

## Hardware Used

* [AVR128DB48 Curiosity Nano](https://www.microchip.com/DevelopmentTools/ProductDetails/PartNO/EV35L43A)
* Optional external clock source

## Setup

The AVR128DB48 Curiosity Nano comes with a 16 MHz crystal soldered on. This can be used for most of the example projects, except for the external clock and RTC examples.

* **XOSCHF with External Clock**:
  * Disconnect the crystal by cutting the two straps on the top side of the board next to the crystal (J215, J216)
  * Connect the I/O lines to the edge connector by placing solder blobs on the circular solder points marked PA0 and PA1 on the bottom side of the board (J213, J214)
  * Connect a clock source to PA0 on the edge connector
* **RTC with XOSCHF**:
  Replace the 16 MHz crystal with one running at maximum 1/4 of the CLK_MAIN frequency

## Operation

* Connect the AVR128DB48 Curiosity Nano to a computer using a USB cable
* Clone the repository or download the zip to get the source code
* Open the .atsln file with Atmel Studio
* In Solution Explorer, right-click the project you want to run and select *Set as StartUp Project*
* Press *Start Without Debugging* (CTRL+ALT+F5) to run the example

## Conclusion

After going through these examples you should have a better understanding of how to set up different use cases for the XOSCHF on AVR DB family microcontrollers.
