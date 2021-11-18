#include <p18f4620.h>
#include "Main.h"
#include "Fan_Support.h"
#include "stdio.h"

extern char FAN;
extern char duty_cycle;


int get_RPM()
{
    int RPS = TMR3L / 2; // read the count. Since there are 2 pulses per rev then RPS = count /2
    TMR3L = 0; // clear out the count
    return (RPS * 60); // return RPM = 60 * RPS 
}

void Toggle_Fan()
{
    if (FAN == 0)
        Turn_On_Fan();
    else
        Turn_Off_Fan();
}

void Turn_Off_Fan()
{
    FAN = 0;
    FAN_EN = 0;
    FAN_LED = 0;
}

void Turn_On_Fan()
{
    FAN = 1;
    do_update_pwm(duty_cycle);
    FAN_EN = 1;
    FAN_LED = 1;
}

void Increase_Speed()
{
    if (duty_cycle == 100)
    {
        Wait_Half_Sec();
        Do_Beep();
        do_update_pwm(duty_cycle);
    }
    else
    {
        duty_cycle = duty_cycle + 5;
        do_update_pwm(duty_cycle);
    }
}

void Decrease_Speed()
{
    if (duty_cycle == 0)
    {
        Wait_Half_Sec();
        Do_Beep();
        do_update_pwm(duty_cycle);
    }
    else
    {
        duty_cycle = duty_cycle - 5;
        do_update_pwm(duty_cycle);
    }
}

void do_update_pwm(char duty_cycle) 
{ 
    float dc_f; 
    int dc_I; 
    PR2 = 0b00000100 ; // set the frequency for 25 Khz 
    T2CON = 0b00000111 ; // 
    dc_f = ( 4.0 * duty_cycle / 20.0) ; // calculate factor of duty cycle versus a 25 Khz signal 
    dc_I = (int) dc_f; // get the integer part 
    if (dc_I > duty_cycle) dc_I++; // round up function 
    CCP1CON = ((dc_I & 0x03) << 4) | 0b00001100; 
    CCPR1L = (dc_I) >> 2; 
}

void Set_DC_RGB(int t)
{
    t = t/10;
    if (t > 7) t = 7;
    PORTD = (t<<5) + 7;
}

void Set_RPM_RGB(int rpm)
{
    if (rpm == 0)
    {
        PORTAbits.RA3 = 0;
        PORTAbits.RA4 = 0;
    }
    if (rpm > 0 && rpm < 1800)
    {
        PORTAbits.RA3 = 1;
        PORTAbits.RA4 = 0;
    }
    if (rpm >= 1800 && rpm < 2700)
    {
        PORTAbits.RA3 = 1;
        PORTAbits.RA4 = 1;
    }
    if (rpm >= 2700)
    {
        PORTAbits.RA3 = 0;
        PORTAbits.RA4 = 1;
    }
}



