#include <p18f4620.h>
#include "Main.h"
#include "Utils.h"
#include "stdio.h"

void Do_Beep()
{
    kp = 1;
    Activate_Buzzer();
    Wait_One_Sec();
    Deactivate_Buzzer();
    kp = 0;
}

void Wait_One_Sec()
{
    for (int k = 0; k < 17000;k++);
}

void Wait_Half_Sec()
{
    for (int k = 0; k < 8500;k++);
}

void Activate_Buzzer()
{
    PR2 = 0b11111001 ;
    T2CON = 0b00000101 ;
    CCPR2L = 0b01001010 ;
    CCP2CON = 0b00111100 ;
}

void Deactivate_Buzzer()
{
    CCP2CON = 0x0;
    PORTBbits.RB3 = 0;
}

