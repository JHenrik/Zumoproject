/**
* @mainpage ZumoBot Project
* @brief    You can make your own ZumoBot with various sensors.
* @details  <br><br>
    <p>
    <B>General</B><br>
    You will use Pololu Zumo Shields for your robot project with CY8CKIT-059(PSoC 5LP) from Cypress semiconductor.This 
    library has basic methods of various sensors and communications so that you can make what you want with them. <br> 
    <br><br>
    </p>
    
    <p>
    <B>Sensors</B><br>
    &nbsp;Included: <br>
        &nbsp;&nbsp;&nbsp;&nbsp;LSM303D: Accelerometer & Magnetometer<br>
        &nbsp;&nbsp;&nbsp;&nbsp;L3GD20H: Gyroscope<br>
        &nbsp;&nbsp;&nbsp;&nbsp;Reflectance sensor<br>
        &nbsp;&nbsp;&nbsp;&nbsp;Motors
    &nbsp;Wii nunchuck<br>
    &nbsp;TSOP-2236: IR Receiver<br>
    &nbsp;HC-SR04: Ultrasonic sensor<br>
    &nbsp;APDS-9301: Ambient light sensor<br>
    &nbsp;IR LED <br><br><br>
    </p>
    
    <p>
    <B>Communication</B><br>
    I2C, UART, Serial<br>
    </p>
*/

#include <project.h>
#include <stdio.h>
#include "Systick.h"
#include "Motor.h"
#include "Ultra.h"
#include "Nunchuk.h"
#include "Reflectance.h"
#include "I2C_made.h"
#include "Gyro.h"
#include "Accel_magnet.h"
#include "IR.h"
#include "Ambient.h"
#include "Beep.h"
#include "Tune.h"
#include <time.h>
#include <sys/time.h>
#include <stdbool.h>
#include <stdlib.h>
int rread(void);

/**
 * @file    main.c
 * @brief   
 * @details  ** Enable global interrupt since Zumo library uses interrupts. **<br>&nbsp;&nbsp;&nbsp;CyGlobalIntEnable;<br>
*/

/*Definitions*/

int drive();
void zumo();
void drivetoline();


void startTune() // play some nostalgic music from 2000
{
    Tune(140,100);
    Tune(280,329.63);//E
    Tune(140,292.66);//D
    Tune(280,185.00);//F#
    Tune(280,207.65);//G#
    Tune(140,277.18);//C#
    Tune(140,246.94);//B
    Tune(280,146.83);//D
    Tune(280,164.81);//E
    Tune(140,246.94);//B
    Tune(140,220.00);//A
    Tune(280,138.59);//C#
    Tune(280,164.81);//E
    Tune(360,220.00);//A
    CyDelay(10);
    
}



 

#if 1
//battery level//
int main()
{
    

    CyGlobalIntEnable; 
    UART_1_Start();
    Systick_Start();    
    ADC_Battery_Start();
 
    int16 adcresult =0;
    float volts = 0.0;
    const float batteryVoltage = 1.5;
    const int VinRange = 5;
    const int codeRange = 4095;
    
//    startTune();
    printf("\nBoot\n");
    drivetoline();
    
    printf("end of drivetoline\n");
    IR_Start();
    
    IR_flush();
    printf("Flush\n");
    IR_wait();
    printf("Signal\n");
    
    
    drive();
//  zumo();
    

    
    //BatteryLed_Write(1); // Switch led on 
    //BatteryLed_Write(0); // Switch led off 
    //uint8 button;
    //button = SW1_Read(); // read SW1 on pSoC board
    // SW1_Read() returns zero when button is pressed
    // SW1_Read() returns one when button is not pressed
    
    /*motor_start();
        motor_forward(200,1500);
        
        MotorDirLeft_Write(0);      // set LeftMotor forward mode
        MotorDirRight_Write(1);     // set RightMotor forward mode
        PWM_WriteCompare1(100); 
        PWM_WriteCompare2(100); 
        CyDelay(750);
        
        motor_forward(200,1250);
        
        MotorDirLeft_Write(0);      // set LeftMotor forward mode
        MotorDirRight_Write(1);     // set RightMotor forward mode
        PWM_WriteCompare1(100); 
        PWM_WriteCompare2(100); 
        CyDelay(720);
       
        motor_forward(200,1400);
        
        MotorDirLeft_Write(0);      // set LeftMotor forward mode
        MotorDirRight_Write(1);     // set RightMotor forward mode
        PWM_WriteCompare1(100); 
        PWM_WriteCompare2(100); 
        CyDelay(900);
        
        motor_forward(200,400);
        
        MotorDirLeft_Write(0);      // set LeftMotor forward mode
        MotorDirRight_Write(0);     // set RightMotor forward mode
        PWM_WriteCompare1(120); 
        PWM_WriteCompare2(55); 
        CyDelay(2500);
        
        motor_forward(200,500);
        
        
//        
//        motor_forward(100,1000);
        
        motor_stop();*/
    
    /*1. Battery check*/

    
    for(;;)
    {
        //ens();
        ADC_Battery_StartConvert();
        if(ADC_Battery_IsEndConversion(ADC_Battery_WAIT_FOR_RESULT)) {   // wait for get ADC converted value
            adcresult = ADC_Battery_GetResult16(); // get the ADC value (0 - 4095)
            // convert value to Volts
            // you need to implement the conversion
            volts = ((float)(adcresult * VinRange) / codeRange) * batteryVoltage;
            
          return volts;
            // Print both ADC results and converted value
            printf("%d %f\r\n",adcresult, volts);
            
                if(volts <4)
       {
          BatteryLed_Write(1);
       }
       else
       {
            BatteryLed_Write(0);
       }
            
            /*2. Play a Tune*/            
            //startTune();
        }
        CyDelay(500);
        
    }
    
    
    
    
    /*3. Motor Check*/
    
    //Right motor speed
    
    
    //Left motor speed
    
    
    //Straight line forward movement
    
    
    /*4. Complete a course without sensors*/
    
    
    /*5. Sensor values check*/
    
    
    /*6. Motion based on sensor values*/
    
    
    /*7. Automated PID line follower*/
    
 }   
#endif

#if 0
// button
int main()
{
    CyGlobalIntEnable; 
    UART_1_Start();
    Systick_Start();
    
    printf("\nBoot\n");

    //BatteryLed_Write(1); // Switch led on 
    BatteryLed_Write(0); // Switch led off 
    
    //uint8 button;
    //button = SW1_Read(); // read SW1 on pSoC board
    // SW1_Read() returns zero when button is pressed
    // SW1_Read() returns one when button is not pressed
    
    bool led = false;
    
    for(;;)
    {
        // toggle led state when button is pressed
        if(SW1_Read() == 0) {
            led = !led;
            BatteryLed_Write(led);
            ShieldLed_Write(led);
            if(led) printf("Led is ON\n");
            else printf("Led is OFF\n");
            Beep(1000, 150);
            while(SW1_Read() == 0) CyDelay(10); // wait while button is being pressed
        }        
    }
 }   
#endif


#if 0
//ultrasonic sensor//
int main1()
{
    CyGlobalIntEnable; 
    UART_1_Start();
    Systick_Start();
    Ultra_Start();                          // Ultra Sonic Start function
    while(1) {
        int d = Ultra_GetDistance();
        //If you want to print out the value  
        printf("distance = %d\r\n", d);
        CyDelay(200);
    }
}   
#endif


#if 0
//IR receiver//
int signal()
{
    CyGlobalIntEnable; 
    UART_1_Start();
    IR_Start();
    
    uint32_t IR_val; 
    
    printf("\n\nIR test\n");
    
    IR_flush(); // clear IR receive buffer
    printf("Buffer cleared\n");
    
    IR_wait(); // wait for IR command
    printf("IR command received\n");
    
//     print received IR pulses and their lengths
    for(;;)
    {
        if(IR_get(&IR_val)) {
            int l = IR_val & IR_SIGNAL_MASK; // get pulse length
            int b = 0;
            if((IR_val & IR_SIGNAL_HIGH) != 0) b = 1; // get pulse state (0/1)
            printf("%d %d\r\n",b, l);
            //printf("%d %lu\r\n",IR_val & IR_SIGNAL_HIGH ? 1 : 0, (unsigned long) (IR_val & IR_SIGNAL_MASK));
        }
        
    }
}
#endif


#if 1
//reflectance//
    
void drivetoline()
{
    
    struct sensors_ dig;
    Systick_Start();
    CyGlobalIntEnable; 
    UART_1_Start();
    reflectance_start();
    reflectance_set_threshold(8000, 7000, 9000, 9000, 9000, 9000);
    CyDelay(2);
    uint8_t stopped =0;
    
    motor_start();
    while(stopped==0)
    {
        
        motor_forward(50,0);
        //printf("moving to line\n");
    reflectance_digital(&dig);
        if(dig.l3==1 && dig.l2==1 && dig.l1==1 && dig.r1==1 && dig.r2==1 && dig.r3==1)
        {
            motor_stop();
            stopped =1;
            
        }
    }
    
 }
void zumo()
{
    CyGlobalIntEnable; 
    UART_1_Start();
    Systick_Start();
    Ultra_Start();                          // Ultra Sonic Start function
    while(1) {
        int d = Ultra_GetDistance();
        //If you want to print out the value  
        printf("distance = %d\r\n", d);
        CyDelay(200);
    }
    
}
int drive()
{
  
    bool BL = true;
    struct sensors_ ref;
    struct sensors_ dig;
    float Speed = 230;
   
    
    Systick_Start();

    CyGlobalIntEnable; 
    UART_1_Start();
  
    reflectance_start();
    reflectance_set_threshold(9000, 9000, 9000, 9000, 9000, 9000); // set center sensor threshold to 11000 and others to 9000
    CyDelay(1);
    
    int blacklinecount = 0;
    motor_forward(200,1000);
    while(blacklinecount < 4)
    {
       
        // read raw sensor values
        reflectance_read(&ref);
        //printf("%5d %5d %5d %5d %5d %5d\r\n", ref.l3, ref.l2, ref.l1, ref.r1, ref.r2, ref.r3);       // print out each period of reflectance sensors
        
        // read digital values that are based on threshold. 0 = white, 1 = black
        // when blackness value is over threshold the sensors reads 1, otherwise 0
        reflectance_digital(&dig);      //print out 0 or 1 according to results of reflectance period
        //printf("%5d %5d %5d %5d %5d %5d \r\n", dig.l3, dig.l2, dig.l1, dig.r1, dig.r2, dig.r3);        //print out 0 or 1 according to results of reflectance period
        CyDelay(0);
        
        
        motor_start();
       
        if(ref.l1 > 15000 && ref.r1 > 15000) // if the blackline covers both middle sensors 
        {
            motor_forward(255,0); //forward with full speed
        }
        else if(ref.l1 >= 15000) // if the blackline cover the left 1st sensor
        {
            motor_turn(255/3,255,0); // turn with a radius 1:3 to left
            BL = false;
        }

        else if(ref.l2 >= 15000) // if the blackline covers the left 2nd sensor
        {
            motor_turn(255/4,255,0); // turn with a radius of 1:4 to left
            BL = false;
        }
        else if(ref.l3 >= 15000) // if the blackline covers the left 3rd sensor
        {
            MotorDirLeft_Write(1);      //left motor goes backwards
            MotorDirRight_Write(0);     //right motor goes forwards
            PWM_WriteCompare1(255/4);     //full speed
            PWM_WriteCompare2(255); 
            
//            motor_turn(Speed/7.5,Speed,0); // turn with a radius of 1:7.5 to left
            BL = false;
        }
        else if(ref.l3 <=15000 && dig.l3 == 1) // if the blackline covers 1/2 of the left 3rd sensor
        {
            //make a turn on point 
            MotorDirLeft_Write(1);      //left motor goes backwards
            MotorDirRight_Write(0);     //right motor goes forwards
            PWM_WriteCompare1(255);     //full speed
            PWM_WriteCompare2(255);     //full speed
        }
        else if(ref.r1 >= 15000 ) // if the blackline cover the right 1st sensor
        {
            motor_turn(255,255/3,0);    // turn with a radius of 3:1
            BL = true;
        }

        else if(ref.r2 >= 15000) // if the blackline cover the right 2nd sensor
        {
            motor_turn(255,255/4,0);    // turn with a radius of 4:1
            BL = true;
        }
        else if(ref.r3 >= 15000) // if the blackline cover the right 3rd sensor
        {
            MotorDirLeft_Write(0);      //left goes forward     
            MotorDirRight_Write(1);     //right goes backwards     
            PWM_WriteCompare1(255);     //full speed
            PWM_WriteCompare2(255/4);   
            
//            motor_turn(Speed,Speed/7.5,0);  // turn with a radius of 7.5:1
            BL = true;
        }
        else if(ref.r3 <=15000 && dig.r3 == 1) // if the blackline covers 1/2 of the right 3rd sensor
        {
            //make a turn on point 
            MotorDirLeft_Write(0);      //left goes forward     
            MotorDirRight_Write(1);     //right goes backwards     
            PWM_WriteCompare1(255);     //full speed
            PWM_WriteCompare2(255);     //full speed
        }
         else if(dig.l3==0 && dig.l2==0 && dig.l1==0 && dig.r1==0 && dig.r2==0 && dig.r3==0)
        {
            if(BL == true)  
            {
                motor_turn(Speed/Speed,Speed,0);
            }
            else if(BL == false) 
            {
                motor_turn(Speed,Speed/Speed,0); 
            }
        }
        if(dig.l3==1 && dig.l2==1 && dig.l1==1 && dig.r1==1 && dig.r2==1 && dig.r3==1)
        {
            blacklinecount++;
            
            if(blacklinecount > 3)
            {
                motor_stop();
            }
            CyDelay(50);
            }
    }
   exit(0);
}   

#endif


#if 0
//motor//
int main()
{
    CyGlobalIntEnable; 
    UART_1_Start();

    motor_start();              // motor start

    motor_forward(100,2000);     // moving forward
    motor_turn(200,50,2000);     // turn
    motor_turn(50,200,2000);     // turn
    motor_backward(100,2000);    // moving backward
       
    motor_stop();               // motor stop
    
    for(;;)
    {

    }
}
#endif


/* [] END OF FILE */
