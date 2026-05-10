#include "../config.h"

//DEF
struct Stepper stepperRight;
struct Stepper stepperLeft;

uint8_t internMoveDir = STAND;

void pStep(struct Stepper* _stepper);
void nStep(struct Stepper* _stepper);
void step(struct Stepper* _stepper);
//---

ISR(TIMER0_COMPA_vect) {
    switch (internMoveDir) {
        case STAND:
            break;

        case FORWARD:
            nStep(&stepperRight);
            pStep(&stepperLeft);
            break;

        case BACKWARD:
            pStep(&stepperRight);
            nStep(&stepperLeft);
            break;

        case ROTATE_CW:
            pStep(&stepperRight);
            pStep(&stepperLeft);
            break;

        case ROTATE_CCW:
            nStep(&stepperRight);
            nStep(&stepperLeft);
            break;
    }
}

void initStepper(void) {
    //Timer inizialisieren
    OCR0A = 249; //Timer0 zählt bis 249
    TCCR0A = 1<<WGM01; //Timer0 geht nach 249 auf 0
    TCCR0B = (1<<CS01) | (1<<CS00); //PS 64
    TIMSK0 |= 1<<OCIE0A; //Interrupt wenn 249 erreicht wird
    sei();

    //Initialisierung der pins ect.
    stepperRight = (struct Stepper) {
        .pins = {PD4, PD5, PD6, PD7},

        .port = &PORTD,
        .stepCounter = 0
    };
    
    //Pins auf ausgang setzen + startposition
    *(stepperRight.port) |= (1<<stepperRight.aIn1) | (1<<stepperRight.aIn2) |
                            (1<<stepperRight.bIn1) | (1<<stepperRight.bIn2);

    *(stepperRight.port) |= (1<<stepperRight.aIn1) | (1<<stepperRight.bIn2);
    
    //Wie bein stepperRight
    stepperLeft = (struct Stepper) {
        .pins = {PB0, PB1, PB2, PB3},

        .port = &PORTB,
        .stepCounter = 0
    };

    *(stepperLeft.port) |= (1<<stepperLeft.aIn1) | (1<<stepperLeft.aIn2) |
                           (1<<stepperLeft.bIn1) | (1<<stepperLeft.bIn2);

    *(stepperLeft.port) |= (1<<stepperLeft.aIn1) | (1<<stepperLeft.bIn2);

}

void stepperSetDir(uint8_t _dir) {
    switch (_dir) {
        case STAND:
        case FORWARD:
        case BACKWARD:
        case ROTATE_CW:
        case ROTATE_CCW:
            internMoveDir = _dir;
            break;
        
        default: //Falscher input
            internMoveDir = STAND;
            break;
    }
}

void pStep(struct Stepper* _stepper) {
    if(++(_stepper->stepCounter) >= 4)
        _stepper->stepCounter = 0;

    step(_stepper);
}

void nStep(struct Stepper* _stepper) {
    if(--(_stepper->stepCounter) >= 4)
        _stepper->stepCounter = 3;

    step(_stepper);
}

void step(struct Stepper* _stepper) {
    switch (_stepper->stepCounter) {
        case 0:
            *(_stepper->port) |= 1<<_stepper->bIn1;
            *(_stepper->port) &= ~(1<<_stepper->bIn2);
            break;

         case 1:
            *(_stepper->port) |= 1<<_stepper->aIn2;
            *(_stepper->port) &= ~(1<<_stepper->aIn1);
            break;

        case 2:
            *(_stepper->port) |= 1<<_stepper->bIn2;
            *(_stepper->port) &= ~(1<<_stepper->bIn1);
            break;

        case 3:
            *(_stepper->port) |= 1<<_stepper->aIn1;
            *(_stepper->port) &= ~(1<<_stepper->aIn2);
            break; 
    }
}
