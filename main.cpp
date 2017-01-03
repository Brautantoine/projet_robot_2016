#include "nboard.h"

unsigned char state(1); //variable d etat de l automate ligne blanche
unsigned char state_P(1); //variable d etat de lautomate de pre suivie
unsigned char core(1);  //variable d arret pour l automate ligne blanche

float seuil(0.45); //seuil capteur

int i=0;

PwmOut PWMD(PB_5); //mouteur droite
PwmOut PWMG(PB_4); //moteur gauche

IHM ihm; //instance de l ihm

float lire_capteur(int n_capteur);
void tout_droit();
void A_Gauche();
void A_Droite();
void Stop_Robot();
void nouvel_etat_pre_suivie();


int main() 
{
    BusMux=7;
        /*initialisation des moteur*/
    PWMD.period(0.00005);
    PWMG.period(0.00005);
    
    /* affichage de bienvenue*/
        ihm.LCD_gotoxy(0,0);
        ihm.LCD_printf("Gr A6");
        ihm.LCD_gotoxy(1,0);
        ihm.LCD_printf("equipe BCDL");
        wait(1);
        
     while(jack) {
                        nouvel_etat_pre_suivie();
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
                A_Gauche();
                break;
            case DROITE:
                A_Droite();
                break;
            case STOP:
                            Stop_Robot();
                            break;
         }       
    }
    while(1)
    {
    }
}

float lire_capteur(int n_capteur) //fonctions de lecture des capteur (renvoie la valeur du capteur en entrée)
{
    BusMux = n_capteur;
    return AnaIn.read();
}

void tout_droit() //procedure d actualisations du moteur (1:1)
{
    BusMux=7;
    PWMD.write(AnaIn.read());
    PWMG.write(AnaIn.read());
    if((lire_capteur(2)<float(seuil)&&lire_capteur(3)>float(seuil)))state=GAUCHE;
    else if((lire_capteur(2)>float(seuil)&&lire_capteur(3)<float(seuil)))state=DROITE;
    if(!BPP)state=STOP;
    
    
}

void A_Gauche() //procedure d actualisations du moteur (0.4:1)
{
    BusMux=7;
    PWMD.write(AnaIn.read());
    PWMG.write(float(0.4)*float(AnaIn.read()));
    if((lire_capteur(2)>float(seuil)&&lire_capteur(3)>float(seuil)))state=TOUT_DROIT;
    if(!BPP)state=STOP;
}

void A_Droite() //procedure d actualisations du moteur (1:0.4)
{
    BusMux=7;
    PWMD.write(float(0.4)*float(AnaIn.read()));
    PWMG.write(AnaIn.read());
    if((lire_capteur(2)>float(seuil)&&lire_capteur(3)>float(seuil)))state=TOUT_DROIT;
    if(!BPP)state=STOP;
}

void Stop_Robot() //procedure d actualisations du moteur (0:0)
{
    PWMD.write(0);
  PWMG.write(0);
  core=0; //sortie de boucle while
}
void nouvel_etat_pre_suivie() //automate de pre suivie
{
    
    switch (state_P)
    {
        case WAIT:
            /*affichage des capteur et du vpot en tps réel*/
            BusMux=7;
      ihm.LCD_gotoxy(0,0);
      ihm.LCD_printf("pot=%f w",AnaIn.read());
      ihm.LCD_gotoxy(1,0);
        ihm.LCD_printf("equipe BCDL");
      BusLed=0X00;
      for(i=0; i<6; i++) {
                if(lire_capteur(i)>float(0.5))BusLed[i]=1;
      }
            if(!BP0)state_P=CAPT;
            else if(!BP1)state_P=MOT;
            else if(!BP2)state_P=POL;
            break;
        case CAPT:
            /*comme wait mais avec un calibrage possible*/
            BusMux=7;
      ihm.LCD_gotoxy(0,0);
      ihm.LCD_printf("pot=%f att calibrage",AnaIn.read());
          if(!BP0)seuil=AnaIn.read();
      BusLed=0X00;
      for(i=0; i<6; i++) {
                if(lire_capteur(i)>float(seuil))BusLed[i]=1;
      }
            if(!BPP)state_P=WAIT;
            break;
        case MOT:
            ihm.LCD_gotoxy(0,0);
            ihm.LCD_printf("test moteur");
            PWMD.write(0.5);
            PWMG.write(0.5);
            wait(0.5);
            PWMD.write(0);
            PWMG.write(0.5);
            wait(0.5);
            PWMD.write(0.5);
            PWMG.write(0);
            wait(0.5);
            PWMD.write(0);
            PWMG.write(0);
            while(BPP);
            state_P=WAIT;
            break;
        case POL:
                /*execute un polygones puis attend un appui sur le bp3*/
        ihm.LCD_gotoxy(0,0);
        ihm.LCD_printf("polygone");
        PWMG.write(0.4);
        PWMD.write(0.4);
        wait(1);
        PWMG.write(0.5);
        PWMD.write(0);
        wait(0.5);
        PWMG.write(0.4);
        PWMD.write(0.4);
        wait(1);
        PWMG.write(0.5);
        PWMD.write(0);
        wait(0.5);
        PWMG.write(0.4);
        PWMD.write(0.4);
        wait(1);
        PWMG.write(0.5);
        PWMD.write(0);
        wait(0.5);
        PWMG.write(0.4);
        PWMD.write(0.4);
        wait(1);
        PWMG.write(0.5);
        PWMD.write(0);
        wait(0.5);
        PWMG.write(0);
        PWMD.write(0);
                while(BPP);
                state_P=WAIT;
            break;
    }
}