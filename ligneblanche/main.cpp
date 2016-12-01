#include "nboard.h"

unsigned char state(1);
unsigned char core(1);
float speed(1);
int i=0;

PwmOut RWM1(PB_5); //droite
PwmOut RWM2(PB_4); //gauche

IHM ihm;

float lire_capteur(int n_capteur)
{
    BusMux = n_capteur;
    return AnaIn.read();
}

void tout_droit()
{
    BusMux=7;
    RWM1.write(AnaIn.read());
    RWM2.write(AnaIn.read());
    if((lire_capteur(2)<float(0.45)&&lire_capteur(3)>float(0.45)))state=GAUCHE;
    if((lire_capteur(2)>float(0.45)&&lire_capteur(3)<float(0.45)))state=DROITE;
    if(!BPP)state=STOP;
    
    
}

void babord_capitaine()
{
    BusMux=7;
    RWM1.write(AnaIn.read());
    RWM2.write(float(0.4)*float(AnaIn.read()));
    if((lire_capteur(2)>float(0.45)&&lire_capteur(3)>float(0.45)))state=TOUT_DROIT;
    if(!BPP)state=STOP;
}

void tribord_capitaine()
{
    BusMux=7;
    RWM1.write(float(0.4)*float(AnaIn.read()));
    RWM2.write(AnaIn.read());
    if((lire_capteur(2)>float(0.45)&&lire_capteur(3)>float(0.45)))state=TOUT_DROIT;
    if(!BPP)state=STOP;
}

int main() 
{
    BusMux=7;
    RWM1.period(0.00005);
    RWM2.period(0.00005);
    
    
     while(jack) {
                BusMux=7;
                ihm.LCD_gotoxy(0,0);
                ihm.LCD_printf("pot=%f",AnaIn.read());
                BusLed=0X00;
                for(i=0; i<6; i++) {
                    if(lire_capteur(i)>float(0.5))BusLed[i]=1;
                }
            }
            BusMux=7;
    while(core) 
    {
        BusLed=0X00;
        BusMux=7;
         for(i=0;i<6;i++)
        {
            if(lire_capteur(i)>float(0.5))BusLed[i]=1;
        }
        switch(state)
        {
            case TOUT_DROIT:
                tout_droit();
                break;
            case GAUCHE:
                babord_capitaine();
                break;
            case DROITE:
                tribord_capitaine();
                break;
            case STOP:
                RWM1.write(0);
                RWM2.write(0);
                core=0;
         }       
    }
    while(1)
    {
    }
}
