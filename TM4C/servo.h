#ifndef SERVO_H_
#define SERVO_H_


#define PART_TM4C123GH6PM
#include "driverlib/pin_map.h"
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_gpio.h"
#include "inc/hw_types.h"
//#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/pin_map.h"
#include "driverlib/gpio.h"
#include "driverlib/pwm.h"

#define GPIO_PORTF_BASE         0x40025000  // GPIO Port F

//prototypes
void delayMS(int ms);
void servo_init(void);
void open(void);
void close(void);


#endif  //SERVO_H_