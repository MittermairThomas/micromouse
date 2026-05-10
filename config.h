#ifndef CONFIG_H
#define CONFIG_H

//---DEFINES---
#define F_CPU    16000000UL
#define BAUTRATE 9600UL

//---INCLUDES---
#include "headers/hmc5883l.h"
#include "headers/vl53l1x.h"
#include "headers/stepper.h"
#include "headers/error.h"
#include "headers/maze.h"
#include "headers/twi.h"

#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdint.h>

#endif
