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
void sumo();
void sumomaneuver(int direction, uint32 delay);
void drivetoline();
void BatteryStatus();



void startTune() // play theme 
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
/* ========= Used for Sumo Wrestling ==============*/
    //Move the robot to the middle of the ring
    motor_start();
    motor_forward(150,550);
    motor_forward(0,0);
    //printf("In the ring \n");
    
    sumo(); //Start the sumo function
    
// ================================================= //
 
    
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
void sumo()
{
    CyGlobalIntEnable; 
    UART_1_Start();
    Systick_Start();
    Ultra_Start();  // Ultra Sonic Start function
    
    //Start the sensors
    struct sensors_ ref;
    struct sensors_ dig;
    reflectance_start();
    //Setting the sensor threshold values
    reflectance_set_threshold(20000, 20000, 20000, 20000, 20000, 20000); 
    
    bool Edge = false;    //Edge boolean. Checks if we hit an edge or not
    int d;                //Variable for the distance
    int dir_Coefficient;  //Variable for the turn direction
    
    //Loop that runs the sumo wrestling   
    for(;;) 
    {
        d = Ultra_GetDistance();      //check the distance value of objects
        
        BatteryStatus();   //Check the battery level
        
        //Always update the sensor values
        reflectance_read(&ref);
        reflectance_digital(&dig);    
        int inRing = 0; //variable used to exit the while loop once an edge has been detected
        
        //Check if any sensor has detected the black lines of an edge
        if (dig.l3==1 || dig.l2==1 || dig.l1==1 || dig.r1==1 || dig.r2==1 || dig.r3==1)
        {
            Edge = true;  //set edge detected to true
           
            //Stop the Robot, reverse and move back to center of ring
            motor_stop();
            
            motor_start();
            motor_backward(200, 150);
            motor_backward(0, 0);
            
            MotorDirLeft_Write(1);      
            MotorDirRight_Write(0);     
            PWM_WriteCompare1(255); 
            PWM_WriteCompare2(255);
            CyDelay(250);
            
            motor_forward(170, 150);
            motor_forward(0, 0);
       
            
        }
                
        //If no edge has been detected                
        if(Edge == false && inRing == 0)
        {

            //If any sensor detects the black lines of an edge            
            if (dig.l3==1 || dig.l2==1 || dig.l1==1 || dig.r1==1 || dig.r2==1 || dig.r3==1)
            {
                Edge = true;
                
                //Stop the Robot, reverse and move back to center of ring
                motor_stop();
            
                motor_start();
                motor_backward(200, 150);
                motor_backward(0, 0);
                
                MotorDirLeft_Write(0);      
                MotorDirRight_Write(1);     
                PWM_WriteCompare1(255); 
                PWM_WriteCompare2(255);
                CyDelay(250);
                
                motor_forward(170, 150);
                motor_forward(0, 0);
           
                inRing = 1;
            }
            
            //If Robot is still in the ring
            if (dig.l3==0 && dig.l2==0 && dig.l1==0 && dig.r1==0 && dig.r2==0 && dig.r3==0)
            {
                //Check if the distance is more than 50
                if (d > 50)
                {
                    //generate a random number between 0-4 and assign to a variable
                    dir_Coefficient = rand() % 5;     
                    
                    sumomaneuver (dir_Coefficient, 60); //Parse the variable to maneuver function

                }
                
                //Loop that Checks if the distance is equal to or less than 50 and that no sensors detect an edge
                while (d <= 50 && !(dig.l3==1 || dig.l2==1 || dig.l1==1 || dig.r1==1 || dig.r2==1 || dig.r3==1))
                {
                    //Drive the Robot forward at maximum speed
                    motor_forward(255, 1);

                    //Update the sensor values and distance
                    d = Ultra_GetDistance();
                    reflectance_digital(&dig);
                
                }
                
            }            
            
        }
        
        //Reset the condition variables
        inRing = 0;
        Edge = false;
            
    }
}        

void sumomaneuver  (int direction, uint32 delay)
{
    //Start the motor
    motor_start();
    
    //Switch statement that performs different maneuver 
    //based on random number generated by the Sumo Function
	switch (direction)
	{
        //1 = move forward
		case 1:
			motor_forward(170, delay);
            motor_forward(0, 0);
			
			break;
            
        //2 = move backward
		case 2:
			motor_backward(70, delay);
            motor_backward(0, 0);
			
			break;
            
        //3 = move Right
        case 3:

            MotorDirLeft_Write(0);      
            MotorDirRight_Write(1);     
            PWM_WriteCompare1(255); 
            PWM_WriteCompare2(255);
            CyDelay(delay);
			
			break;
            
		//4 = move Left
        case 4:
            
            MotorDirLeft_Write(1);      
            MotorDirRight_Write(0);     
            PWM_WriteCompare1(255); 
            PWM_WriteCompare2(255);
            CyDelay(delay);
			
			break;
            
        //0 = stop
		case 0:
			motor_stop();
            
			break;
            
	}

}

void BatteryStatus()
{
    ADC_Battery_Start();
    
    int16 adcresult =0;
    float volts = 0.0;
    const float batteryVoltage = 1.5;
    const int VinRange = 5;
    const int codeRange = 4095;

    /*1. Battery check*/    
        
    ADC_Battery_StartConvert();
    if(ADC_Battery_IsEndConversion(ADC_Battery_WAIT_FOR_RESULT)) 
    {
        // wait for get ADC converted value
        adcresult = ADC_Battery_GetResult16(); // get the ADC value (0 - 4095)
        // convert value to Volts
        // you need to implement the conversion
        volts = ((float)(adcresult * VinRange) / codeRange) * batteryVoltage;
        
        //return volts;
        // Print both ADC results and converted value
        printf("%d %f\r\n",adcresult, volts);
        
        if(volts < 4)
        {
            BatteryLed_Write(1);
        }
        else
        {
            BatteryLed_Write(0);
        }
            
        
    }
        
        //CyDelay(500);
        
    
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
        BatteryStatus(); // check the battery status
        reflectance_read(&ref);
        //printf("%5d %5d %5d %5d %5d %5d\r\n", ref.l3, ref.l2, ref.l1, ref.r1, ref.r2, ref.r3);       
        
        
        reflectance_digital(&dig);
        //printf("%5d %5d %5d %5d %5d %5d \r\n", dig.l3, dig.l2, dig.l1, dig.r1, dig.r2, dig.r3);       
        
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
