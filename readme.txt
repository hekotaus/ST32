This set of files defines functions at the layer between STM32 HAL/non-HAL and device-specific functions.
Currently used by Stepper board and Console board.

When using the functions, create the file hwversion.h in your project directory. The file should define the STM32 macros and STM32?? family.
Optionally, te STM32 processor model, board and revision can be defined (not used by this library)

The example of the file is below:

"hwversion.h"
#ifndef _HW_VERSION_H_
#define _HW_VERSION_H_

#define STM32
#define STM32H7
//#define NUCLEO_H503RB

//#define GALVO_REV REV_0
//#define IO_REV REV_B

// target CPU on the multiprocessor board
//#define CPU CPU2

// Define, if used with bootloader
//#define BOOT_LOADER

#endif

