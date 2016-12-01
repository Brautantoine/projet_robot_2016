#include "mbed.h"
#include <BusOut.h>
#include <IHM.h>
#include <PwmOut.h>



/*DigitalOut Led0(PB_3);
DigitalOut Led1(PA_7);
DigitalOut Led2(PA_6);
DigitalOut Led3(PA_5);*/
BusOut BusLed(PB_3,PA_7,PA_6,PA_5,PA_3,PA_1,PA_0,PA_2);
    //LED 0
DigitalIn BP0(PA_9, PullUp);
DigitalIn BP1(PA_10, PullUp);
DigitalIn BP2(PB_0, PullUp);
DigitalIn BPP(PB_7, PullUp);
DigitalIn jack(PB_6, PullUp);

    //BP0
    
BusOut BusMux (PA_8,PF_1,PF_0);

AnalogIn AnaIn(PB_1);
    
#define Ana0 000;
#define Ana1 001;
#define Ana2 010;
#define Ana3 011;
#define Ana4 100;
#define Ana5 101;
#define AIn 110;
#define vpot 111;

#define TOUT_DROIT 1
#define GAUCHE 2
#define DROITE 3
#define STOP 4