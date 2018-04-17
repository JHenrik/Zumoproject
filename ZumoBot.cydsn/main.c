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
int rread(void);

/**
 * @file    main.c
 * @brief   
 * @details  ** Enable global interrupt since Zumo library uses interrupts. **<br>&nbsp;&nbsp;&nbsp;CyGlobalIntEnable;<br>
*/

/*Definitions*/

#define minSpeed 0
#define maxSpeed 255
float constSpeed(float speed, int min, int max);

void startTune()
{
    
    Tune(140,153);
    CyDelay(10);
    
}


int sens();

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
    
        if(volts <4)
       {
          BatteryLed_Write(1);
       }
       else
       {
            BatteryLed_Write(0);
       }
    
    printf("\nBoot\n");

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
        sens();
        ADC_Battery_StartConvert();
        if(ADC_Battery_IsEndConversion(ADC_Battery_WAIT_FOR_RESULT)) {   // wait for get ADC converted value
            adcresult = ADC_Battery_GetResult16(); // get the ADC value (0 - 4095)
            // convert value to Volts
            // you need to implement the conversion
            volts = ((float)(adcresult * VinRange) / codeRange) * batteryVoltage;
            
          return volts;
            // Print both ADC results and converted value
            printf("%d %f\r\n",adcresult, volts);
            
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
int main()
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
    
    // print received IR pulses and their lengths
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
int sens()
{
    //int speed = 225;
    bool BL = true;
    struct sensors_ ref;
    struct sensors_ dig;
    
    //Different rates of blackline
//    float l3=0, l2=0, l1=0, r1=0, r2=0, r3=0;
//    
//    l3 = ref.l3;  
//    l2 = ref.l2;
//    l1 = ref.l1;    
//    r1 = ref.r1;    
//    r2 = ref.r2;   
//    r3 = ref.r3;
//    
//    int FullL = 15000;
//    int halfL = 9000;
//    
    float Speed = 200;
   
    
    Systick_Start();

    CyGlobalIntEnable; 
    UART_1_Start();
  
    reflectance_start();
    reflectance_set_threshold(8000, 7000, 9000, 9000, 9000, 9000); // set center sensor threshold to 11000 and others to 9000
    

    for(;;)
    {
        // read raw sensor values
        reflectance_read(&ref);
        printf("%5d %5d %5d %5d %5d %5d\r\n", ref.l3, ref.l2, ref.l1, ref.r1, ref.r2, ref.r3);       // print out each period of reflectance sensors
        
        // read digital values that are based on threshold. 0 = white, 1 = black
        // when blackness value is over threshold the sensors reads 1, otherwise 0
        reflectance_digital(&dig);      //print out 0 or 1 according to results of reflectance period
        printf("%5d %5d %5d %5d %5d %5d \r\n", dig.l3, dig.l2, dig.l1, dig.r1, dig.r2, dig.r3);        //print out 0 or 1 according to results of reflectance period
        CyDelay(0);
        
        
        motor_start();
        
        if(ref.l1 > 15000 && ref.r1 > 15000)
        {
        motor_forward(Speed*1.275,0);
        }
        else if(ref.l1 >= 15000)
        {
            motor_turn((Speed*1.275)/3,Speed*1.275,0);
            BL = false;
        }
//        else if (ref.l1 >= 15000 && ref.l2 >= 15000)
//        {
//            motor_turn((Speed*1.275)/5,Speed,0);
//            BL = false;
//        }
        else if(ref.l2 >= 15000)
        {
            motor_turn((Speed*1.225)/4,Speed*1.225,0);
            BL = false;
        }
        else if(ref.l3 >= 15000)
        {
            motor_turn(Speed/7.5,Speed,0);
            BL = false;
        }
        else if(ref.l3 <=15000 && dig.l3 == 1)
        {
            MotorDirLeft_Write(1);      
            MotorDirRight_Write(0);     
            PWM_WriteCompare1(Speed); 
            PWM_WriteCompare2(Speed);
            CyDelay(0);
        }
        else if(ref.r1 >= 15000)
        {
            motor_turn(Speed*1.275,(Speed*1.275)/3,0);
            BL = true;
        }
//        else if (ref.r1 >= 15000 && ref.r2 >= 15000)
//        {
//            motor_turn(Speed,(Speed*1.275)/5,0);
//        }
        else if(ref.r2 >= 15000)
        {
            motor_turn(Speed*1.225,(Speed*1.225)/4,0);
            BL = true;
        }
        else if(ref.r3 >= 15000)
        {
            motor_turn(Speed,Speed/7.5,0);
            BL = true;
        }
        else if(ref.r3 <=15000 && dig.r3 == 1)
        {
            MotorDirLeft_Write(0);      
            MotorDirRight_Write(1);     
            PWM_WriteCompare1(Speed); 
            PWM_WriteCompare2(Speed);
            CyDelay(0);
        }
         else if(dig.l3==0 && dig.l2==0 && dig.l1==0 && dig.r1==0 && dig.r2==0 && dig.r3==0)
        {
            if(BL == true) // turn 
            {
                motor_turn(Speed/Speed,Speed*1.275,0);
            }
            else if(BL == false) // turn right
            {
                motor_turn(Speed,Speed/Speed*1.275,0); 
            }
        }
            if(dig.l2==1 && dig.l1==1 && dig.r1==1 && dig.r2==1)
            {
            motor_stop();
            
            }
        
        
        
    }
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
