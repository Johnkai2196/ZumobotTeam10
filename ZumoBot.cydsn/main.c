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
#include <stdlib.h>
#include "FreeRTOS.h"
#include "task.h"
#include "Motor.h"
#include "Ultra.h"
#include "Nunchuk.h"
#include "Reflectance.h"
#include "Gyro.h"
#include "Accel_magnet.h"
#include "LSM303D.h"
#include "IR.h"
#include "Beep.h"
#include "mqtt_sender.h"
#include <time.h>
#include <sys/time.h>
#include "serial1.h"
#include <unistd.h>
/**
 * @file    main.c
 * @brief   
 * @details  ** Enable global interrupt since Zumo library uses interrupts. **<br>&nbsp;&nbsp;&nbsp;CyGlobalIntEnable;<br>
*/

#if 0
//motor code assignment 1
    void zmain(void)
{
    motor_start();              // enable motor controller
    motor_forward(0,0);         // set speed to zero to stop motors

    vTaskDelay(3000);
    
    motor_forward(100,3200);     // moving forward
    motor_turn(200,50,349);     // turn
    motor_forward(100,2385);     // moving forward
    motor_turn(200,50,349);     // turn
    motor_forward(100,2600);     // moving forward
    motor_turn(255,10,240);     // turn
    motor_turn(255,213,1096);     // turn
    motor_forward(100,430);     // moving forward
     
    motor_forward(0,0);         // stop motors

    motor_stop();               // disable motor controller
    
    while(true)
    {
        vTaskDelay(100);  // sleep (in an infinite loop)
    }
}
#endif

#if 0
//motor code assignment 2
    void zmain(void)
{   
    Ultra_Start();              // Ultra Sonic Start function
    motor_start();              // enable motor controller
    motor_forward(0,0);         // set speed to zero to stop motors
    int d=0;
    vTaskDelay(3000);

       
    
    while(true) {
        d = Ultra_GetDistance();
        // Print the detected distance (centimeters)
        printf("distance = %d\r\n", d);    
        motor_forward(100,0);     // moving forward    
        if(d<=10){
        motor_backward(100,600); // moving backward
       
        motor_turn(10,-100,300);     // turn
    
    }
        vTaskDelay(200);
        
    }
 
  
}
#endif 
void tank_mode_left(uint8_t speed, uint32_t delay) {
    SetMotors(1, 0, speed, speed, delay);
}
void tank_mode_right(uint8_t speed, uint32_t delay) {
    SetMotors(0, 1, speed, speed, delay);
}
#if 0
//motor code assignment 3
    void zmain(void)
{
    Ultra_Start();              // Ultra Sonic Start function
    motor_start();              // enable motor controller
    motor_forward(0,0);         // set speed to zero to stop motors
    int d=0;
    int dec=0;
    int decider=0;
    vTaskDelay(3000);


    while(true) {
        d = Ultra_GetDistance();
        // Print the detected distance (centimeters)
        printf("distance = %d\r\n", d);
             motor_forward(100,0);     // moving forward
        if(d<=10){
        motor_backward(100,600); // moving backward
        
        dec=rand() % 111+60;
        decider=rand() % 2+1;// decide what direction will turn
        printf("motor = %d\r\n", dec);
        if(decider==1){
        tank_mode_left(dec,360);// turn left tank
        }else{
        tank_mode_right(dec,360); // turn right tank
        }   
        }
        vTaskDelay(200);

    }

}
#endif

#define PRESSED 0
#define ON 1
#define OFF 0
#if 0
//week 4 assignment 1
void zmain(void)
{
    struct sensors_ dig;
    uint32_t count =0;
    IR_Start();
    
    reflectance_start();
    
    
    motor_start();
  motor_forward(0, 0);
  printf("\n\n\n!!!BOOT!!!\n\n\n");
    reflectance_set_threshold(9000, 9000, 11000, 11000, 9000, 9000); // set center sensor threshold to 11000 and others to 9000
    reflectance_digital(&dig);
    
    while(SW1_Read() != PRESSED) //while value is not 0
    BatteryLed_Write(ON); // Turns led on
    vTaskDelay(1000); // sleep (in an infinite loop)
    BatteryLed_Write(OFF); // Turns led off
    
    reflectance_digital(&dig);
   
    while(count<1){
        reflectance_digital(&dig);
        motor_forward(50,0);
        if (dig.L3 && dig.R3){
        while(dig.L3 && dig.R3){
            reflectance_digital(&dig);
            if(!(dig.L3 && dig.R3)){
            count++;}  
    }}}
    motor_forward(0,0);
    printf("Count; %u\n", count);
    IR_wait();
      reflectance_digital(&dig);
     while(!(count==5)){
        reflectance_digital(&dig);
        motor_forward(50,0);
        if (dig.L3 && dig.R3){
        while(dig.L3 && dig.R3){
            reflectance_digital(&dig);
            if(!(dig.L3 && dig.R3)){
            count++;
            }  
    }}}
      printf("Count; %u\n", count);
    motor_forward(0,0);
    motor_stop();
    
    
    
    while(true)
    {
        vTaskDelay(100); // sleep (in an infinite loop)
    }
}
#endif 

#define PRESSED 0
#define ON 1
#define OFF 0
#if 0
//week 4 assignment 2
void zmain(void)
{
    struct sensors_ dig;
    uint32_t count =0;
    IR_Start();
    
    reflectance_start();
    
    motor_start();
    motor_forward(0,0);
      printf("\n\n\n!!!BOOT!!!\n\n\n");
    reflectance_set_threshold(14000, 9000, 11000, 11000, 9000, 14000); // set center sensor threshold to 11000 and others to 9000
    reflectance_digital(&dig);
    
    while(SW1_Read() != PRESSED) //while value is not 0
    BatteryLed_Write(ON); // Turns led on
    vTaskDelay(1000); // sleep (in an infinite loop)
    BatteryLed_Write(OFF); // Turns led off
    
    reflectance_digital(&dig);
   
    while(count<1){
        reflectance_digital(&dig);
        motor_forward(50,0);
        if (dig.L3 && dig.R3){
        while(dig.L3 && dig.R3){
            reflectance_digital(&dig);
            if(!(dig.L3 && dig.R3)){
            count++;}  
    }}}
    
    motor_forward(0,0);
    printf("Count; %u\n", count);
    IR_wait();
      reflectance_digital(&dig);
     while(count<2){
        reflectance_digital(&dig);
        motor_forward(50,0);
        if(dig.R2&&dig.R1&&dig.L2&&dig.L1){
              motor_forward(50,0);
        }
        else if (dig.R2&&dig.R1){
            motor_turn(255,0,0);
        }
        else if(dig.L2&&dig.L1){
         motor_turn(0,255,0);

        }
      while(dig.L3 && dig.R3){
            reflectance_digital(&dig);
            if(!(dig.L3 && dig.R3)){
            count++;
           
            }  
        }
    
}
      printf("Count; %u\n", count);
    motor_forward(0,0);
    motor_stop();
    
    
    
    while(true)
    {
        vTaskDelay(100); // sleep (in an infinite loop)
    }
}
#endif 
#define PRESSED 0
#define ON 1
#define OFF 0

#if 0
//week 4 assignment 3
void zmain(void)
{
    struct sensors_ dig;
    uint32_t count =0;
    uint32_t kaany =0;
    IR_Start();
    
    reflectance_start();
    
    motor_start();
    motor_forward(0,0);
      printf("\n\n\n!!!BOOT!!!\n\n\n");
    reflectance_set_threshold(14000, 9000, 11000, 11000, 9000, 14000); // set center sensor threshold to 11000 and others to 9000
    reflectance_digital(&dig);
    
    while(SW1_Read() != PRESSED) //while value is not 0
    BatteryLed_Write(ON); // Turns led on
    vTaskDelay(1000); // sleep (in an infinite loop)
    BatteryLed_Write(OFF); // Turns led off
    
    reflectance_digital(&dig);
   
    while(count<1){
        reflectance_digital(&dig);
        motor_forward(50,0);
        if (dig.L3 && dig.R3){
        while(dig.L3 && dig.R3){
            reflectance_digital(&dig);
            if(!(dig.L3 && dig.R3)){
            count++;}  
    }}}
    
    motor_forward(0,0);
    printf("Count; %u\n", count);
    IR_wait();
     reflectance_digital(&dig);
     while(count<5){
        reflectance_digital(&dig);
        motor_forward(50,0);
      while(dig.L3 && dig.R3){
            reflectance_digital(&dig);
            if(!(dig.L3 && dig.R3)){
            count++;
                if(count==2)
            {
             vTaskDelay(500);
            while(dig.L1){
            reflectance_digital(&dig);
            tank_mode_left(10,0);// turn left tank
            }
            while(!(dig.L1&&dig.R1&&dig.R2)){
            reflectance_digital(&dig);
            tank_mode_left(10,0);// turn left tank
      
            }
            }else if (count==3){
             vTaskDelay(500);
            while(dig.R1==1){
            reflectance_digital(&dig);
            tank_mode_right(10,0);// turn left tank
            }
            while(!(dig.L1&&dig.R1&&dig.L2)){
            reflectance_digital(&dig);
            tank_mode_right(10,0);// turn left tank
            
            
            }
            }else if(count==4){ 
            vTaskDelay(500);
            while(dig.R1){
            reflectance_digital(&dig);
            tank_mode_right(10,0);// turn left tank
            }
            while(!(dig.L1&&dig.R1&&dig.L2)){
            reflectance_digital(&dig);
            tank_mode_right(10,0);// turn left tank
            
            
            }}
            }}
        
        
        
}
      printf("Count; %u\n", count);
    motor_forward(0,0);
    motor_stop();
    
    
    
    while(true)
    {
        vTaskDelay(100); // sleep (in an infinite loop)
    }
}
#endif 
#define PRESSED 0
#define RELEASED 1
#define ON 1
#define OFF 0
#define BUTTON_T "Group_10/Button"
#define LAP_T "Group_10/Lap"
#if 0
//week 5 assignment 1
void zmain(void)
{
    uint32_t startTime   =0;
    uint32_t stopTime    =0;
  int timepress;
    int min,sec,milli;
    stopTime=xTaskGetTickCount();
    printf("n\n\n !!!BOOT!!!\n\n\n");//clear programming buffer
    while(true){
        //while button is not press
        while(SW1_Read()== RELEASED)
        //StartTime get every tic
        startTime=xTaskGetTickCount();
        //reduce from startTime - stopTime
        timepress= startTime-stopTime;
        //while button is press
        while(SW1_Read()== PRESSED)
        //stopTime equal startTime
        stopTime=startTime;
        //count the millisecond to min
        min=timepress*0.000016667; 
        //millisecond to sec
        sec=(timepress/1000)-(min*60);
        //reduce to covert to millisecond evert second pass
        milli=timepress-((timepress/1000)*1000);
        //print 
        print_mqtt(BUTTON_T,"Time of press is: %d minutes %d seconds %d milliseconds. %d full milliseconds",min,sec,milli,timepress);

        
    }
    
}
#endif 


#if 0
//week 5 assignment 2
    void zmain(void)
{
    Ultra_Start();              // Ultra Sonic Start function
    motor_start();              // enable motor controller
    motor_forward(0,0);         // set speed to zero to stop motors
    int d=0;
    int decider=0;
    vTaskDelay(3000);

    printf("n\n\n !!!BOOT!!!\n\n\n");//clear programming buffer
    while(true) {
        d = Ultra_GetDistance();
        // Print the detected distance (centimeters)
             motor_forward(100,0);     // moving forward
        if(d<=10){
        motor_backward(100,600); // moving backward
        
        decider=rand() % 2+1;// decide what direction will turn
        if(decider==1){
            tank_mode_left(60,370);// turn left tank
        print_mqtt(BUTTON_T,"/turn Left");
        }else{
            tank_mode_right(60,375);// turn right tank
        print_mqtt(BUTTON_T,"/turn Right");
        }   
        }
        vTaskDelay(200);

    }

}
#endif
#if 0
//week 5 assignment 3
 void zmain(void)
{
    struct sensors_ dig;
    uint32_t count =0;
    IR_Start();
    uint32_t startTime   =0;
    uint32_t stopTime    =0;
    int min,sec,milli,timepress;

    reflectance_start();
    
    
    motor_start();
    motor_forward(0, 0);
    printf("\n\n\n!!!BOOT!!!\n\n\n");
    reflectance_set_threshold(9000, 9000, 11000, 11000, 9000, 9000); // set center sensor threshold to 11000 and others to 9000
    reflectance_digital(&dig);
    
    while(SW1_Read() != PRESSED) //while value is not 0
    BatteryLed_Write(ON); // Turns led on
    vTaskDelay(1000); // sleep (in an infinite loop)
    BatteryLed_Write(OFF); // Turns led off
    
    reflectance_digital(&dig);
   
    while(count<1){
        reflectance_digital(&dig);
        motor_forward(50,0);
        if (dig.L3 && dig.R3){
        while(dig.L3 && dig.R3){
            reflectance_digital(&dig);
            if(!(dig.L3 && dig.R3)){
            count++;}  
    }}}
    
    motor_forward(0,0);
    IR_wait();
    reflectance_digital(&dig);
    stopTime=xTaskGetTickCount();
  while(count<2){
        reflectance_digital(&dig);
        motor_forward(50,0);
        if (dig.L3 && dig.R3){
        while(dig.L3 && dig.R3){
            reflectance_digital(&dig);
            startTime=xTaskGetTickCount();
            timepress= startTime-stopTime;
            if(!(dig.L3 && dig.R3)){
            count++;
        //stopTime equal startTime
        stopTime=startTime;
        //millisecond to sec
        sec=(timepress/1000);
        //reduce to covert to millisecond evert second pass
        milli=timepress-((timepress/1000)*1000);
        //print 
        print_mqtt(BUTTON_T,"Time of press is:%d seconds %d milliseconds. %d full milliseconds",sec,milli,timepress);

            }
        }
       }
}
    motor_forward(0,0);
    motor_stop();
       while(true)
    {
        vTaskDelay(100); // sleep (in an infinite loop)
    }
}  
#endif
#define PRESSED 0
#define RELEASED 1
#define ON 1
#define OFF 0
#define BUTTON_T "Group_10/Button"
#define LAP_T "Group_10/Lap"
//zumo roboto show time is on
#if 0
void zmain(void)
{
    Ultra_Start();              // Ultra Sonic Start function
    motor_start();              // enable motor controller
    motor_forward(0,0);         // set speed to zero to stop motors
    int dis=0;                  // the distance
    int decider=0;              // decidde
    int turn;                   // turns
    struct sensors_ dig;        // sensor
    uint32_t count =0;          // count line
    uint32_t startTime =0;      // start time
    IR_Start();                 // start IR
    uint32_t movementTime =0;   // movement time
    int timepress;              // when pres
    reflectance_start();        // start the sensor
    
printf("\n\n\n!!!BOOT!!!\n\n\n"); //clear programming buffer
reflectance_set_threshold(
    9000, 9000, 11000, 11000, 9000,
    9000); // set center sensor threshold to 11000 and others to 9000
// read digital values that are based on threshold. 0 = white, 1 = black
// when blackness value is over threshold the sensors reads 1, otherwise 0
reflectance_digital(&dig);

while (SW1_Read() != PRESSED) // while value is not 0
  BatteryLed_Write(ON);       // Turns led on
vTaskDelay(1000);             // sleep (in an infinite loop)
BatteryLed_Write(OFF);        // Turns led off


reflectance_digital(&dig);

while (count < 1) { //while the count is below 1
  reflectance_digital(&dig);
  motor_forward(50, 0); // moves forward
  if (dig.L3 && dig.R3) { //If the dig L3 and R3 senses anything to the this
    while (dig.L3 && dig.R3) {  //while the dig L3 and R3 senses anything to the code below
        
      reflectance_digital(&dig);
      if (!(dig.L3 && dig.R3)) { //if the dig L3 and R3  does not senses anything to the code below
        count++; //add count 1
        print_mqtt(BUTTON_T, "Ready zumo"); // when the robots in line
      }
    }
  }
}

motor_forward(0, 0); //stop
IR_wait(); //waits for the button press of ir
startTime = xTaskGetTickCount(); //get the time when on position
print_mqtt(BUTTON_T, "Start %d", startTime);//print start time
    
while (count < 2) {
  turn=rand() % 111+60; // random turn of decgress
  movementTime=xTaskGetTickCount(); //coounts tick
  dis = Ultra_GetDistance(); // sensor getting distance
  reflectance_digital(&dig); // Print the detected distance (centimeters)
  motor_forward(100, 0); // moving forward

  if (dis <= 10) {
    motor_backward(100, 200); // moving backward
    decider = rand() % 2 + 1; // decide what direction will turn
    if (decider == 1) {
      tank_mode_left(turn, 370); // turn left tank
      print_mqtt(BUTTON_T, "/obstacle %d", xTaskGetTickCount());// if their is a obstacle prints the time and prints it
    } else {
      tank_mode_right(turn, 375); // turn right tank
      print_mqtt(BUTTON_T, "/obstacle %d", xTaskGetTickCount());
    }
  } else if ((dig.L3 && dig.L2) || (dig.R3 && dig.R2)) { // if the sensor senses the dig L3 and L2 or senses R3 and R2
    motor_backward(100, 200); // moving backward

    decider = rand() % 2 + 1; // decide what direction will turn made two cause for funnys
    if (decider == 1) {
      tank_mode_left(turn, 370); // turn left tank
      print_mqtt(BUTTON_T, "/obstacle %d", xTaskGetTickCount());
    } else {
      tank_mode_right(turn, 375); // turn right tank
      print_mqtt(BUTTON_T, "/obstacle %d", xTaskGetTickCount());
    }
  }
        
if (SW1_Read() == PRESSED) { //when the buttos is press
  BatteryLed_Write(ON); // Turns led on
  motor_start(0, 0);
  motor_stop();
  timepress = movementTime - startTime; //reduce the stop time and start time
  print_mqtt(BUTTON_T, "/stop %d", movementTime); //Stop time (when the user button is pressed robot stops and sends stop time stamp)
  print_mqtt(BUTTON_T, "/time %d", timepress);//Run time (from start to finish, number of milliseconds between start and stop)
  while (true) {
    vTaskDelay(100);
  }
}

    }
  
}
#endif

#if 0
// speed race
void zmain(void) {

  uint32_t endTime = 0;  //end time
  uint32_t starTime = 0; //start time
  uint32_t stopTime = 0; //stop time
  struct sensors_ dig;   // sensor
  uint32_t count = 0;    // line counter
  int summa;            // to count all dig together
  IR_Start();           // start the ir button

  reflectance_start(); // start the sensor

  motor_start();       // enable motor controller
  motor_forward(0, 0); // set speed to zero to stop motors
  printf("\n\n\n!!!BOOT!!!\n\n\n"); //clear programming buffer
  reflectance_set_threshold(
      14000, 9000, 11000, 11000, 9000,
      14000); // set center sensor threshold to 11000 and others to 9000
  reflectance_digital(&dig);

  while (SW1_Read() != PRESSED) // while value is not 0
    BatteryLed_Write(ON);       // Turns led on
  vTaskDelay(1000);             // sleep (in an infinite loop)
  BatteryLed_Write(OFF);        // Turns led off

  reflectance_digital(&dig);

  while (count < 1) { //while the count is below 1
    reflectance_digital(&dig);
    motor_forward(50, 0); // moves forward to line
    if (dig.L3 && dig.R3) { // if 
      while (dig.L3 && dig.R3) {
        reflectance_digital(&dig);
        if (!(dig.L3 && dig.R3)) { //if the dig L3 and R3 does not senses anything increase count and print ready
          count++;
          print_mqtt(BUTTON_T, "Ready line");
        }
      }
    }
  }

  motor_forward(0, 0);
  IR_wait();    //waits for the button press
  starTime = xTaskGetTickCount(); //counts the boot 
  print_mqtt(BUTTON_T, "/Start %d", starTime); //
  reflectance_digital(&dig);
  motor_forward(255, 10);
  while (count < 2) { //while the count is below 2
    xTaskGetTickCount();
    reflectance_digital(&dig);
    summa = dig.L3 + dig.R3 + dig.L2 + dig.R2 + dig.L1 + dig.R1; //add to summa 
    if (summa == 6) { //if all dig together is equal to 6 it will peform the code below
      while (dig.L3 && dig.R3) {    //if 
        motor_forward(170, 0);
        reflectance_digital(&dig);
        if (!(dig.L3 && dig.R3)) {  //if the dig L3 and R3 does not senses anything increase count
          count++;
        }
      }
    }
else if (dig.L1 && dig.R1) {
  motor_forward(255, 10);
}
else if ((dig.L2 || dig.L3) && dig.L3) {
  if (!dig.L1 && !dig.R1) {
    print_mqtt(BUTTON_T, "/miss %d", xTaskGetTickCount());
  }
  motor_turn(0, 255, 25);
}
else if ((dig.R2 || dig.R3) && dig.R3) {
  if (!dig.L1 && !dig.R1) {
    print_mqtt(BUTTON_T, "/miss %d", xTaskGetTickCount());
  }
  motor_turn(255, 0, 25);
}
else if (dig.R2 && dig.R1) {
  motor_turn(240, 0, 25);
}
else if (dig.L2 && dig.L1) {
  motor_turn(0, 240, 25);
}
}
while (count < 3) {
  endTime = xTaskGetTickCount();
  reflectance_digital(&dig);
  motor_forward(50, 0);

  if (dig.L3 && dig.R3) {
    while (dig.L3 && dig.R3) {
      reflectance_digital(&dig);
      if (!(dig.L3 && dig.R3)) {
        count++;
      }
    }
  } else if (dig.L1 && dig.R1) {
    motor_forward(170, 10);
  } else if (!dig.L1) {
    if (!dig.L1 && !dig.R1) {
      print_mqtt(BUTTON_T, "/miss %d", xTaskGetTickCount());
    } 
    motor_turn(100, 0, 25);
  } else if (!dig.R1) {
    if (!dig.L1 && !dig.R1) {
      print_mqtt(BUTTON_T, "/miss %d", xTaskGetTickCount());
    }
    motor_turn(0, 100, 25);
  }
}

motor_forward(0, 0);
motor_stop();

stopTime = endTime - starTime;
print_mqtt(BUTTON_T, "/stop %d", endTime);
print_mqtt(BUTTON_T, "/time %d", stopTime);
while (true) {
  vTaskDelay(100); // sleep (in an infinite loop)
}
}
#endif

#if 1

//the solver  of truth
void zmain(void) 
{
	
  uint32_t endTime = 0;  //end time
  uint32_t starTime = 0; //start time
  uint32_t stopTime = 0; //stop time
  struct sensors_ dig;   // sensor
  uint32_t count = 0;    // line counter
  int summa,x=0,y=0,d,decider,rDirection=0,lDirection=0,sDirection=0,round=0;            // to count all dig together
  IR_Start();           // start the ir button
  Ultra_Start();              // Ultra Sonic Start function
  reflectance_start(); // start the sensor

  motor_start();       // enable motor controller
  motor_forward(0, 0); // set speed to zero to stop motors
  printf("\n\n\n!!!BOOT!!!\n\n\n"); //clear programming buffer
  reflectance_set_threshold(
      14000, 9000, 11000, 11000, 9000,
      14000); // set center sensor threshold to 11000 and others to 9000
  reflectance_digital(&dig);

  while (SW1_Read() != PRESSED) // while value is not 0
    BatteryLed_Write(ON);       // Turns led on
  vTaskDelay(1000);             // sleep (in an infinite loop)
  BatteryLed_Write(OFF);        // Turns led off

  reflectance_digital(&dig);

  while (count < 1) { //while the count is below 1
    reflectance_digital(&dig);
    motor_forward(50, 0); // moves forward to line
    if (dig.L3 && dig.R3) { // if 
      while (dig.L3 && dig.R3) {
        reflectance_digital(&dig);
        if (!(dig.L3 && dig.R3)) { //if the dig L3 and R3 does not senses anything increase count and print ready
          count++;
          print_mqtt(BUTTON_T, "Ready line");
        }
      }
    }
  }

  motor_forward(0, 0);
  IR_wait();    //waits for the button press
while(x<14){
    d = Ultra_GetDistance();
    motor_forward(60,0);

    reflectance_digital(&dig);
    

    if(sDirection==0){ //if the direction is straight
      while (dig.L3 || dig.R3) {
        reflectance_digital(&dig);
        if (!(dig.L3 || dig.R3)) { //if the dig L3 and R3 does not senses anything increase count and print ready
          x++;
          print_mqtt(BUTTON_T, "%d and y %d",x,y);

        }
      }
    
    }

        if(lDirection==1){ //if the direction is straight
      while (dig.L3 || dig.R3) {
        reflectance_digital(&dig);
        if (!(dig.L3 || dig.R3)) { //if the dig L3 and R3 does not senses anything increase count and print ready
          y--;
          print_mqtt(BUTTON_T, "%d and y %d",x,y);

        }
      }
    
    }
            if(rDirection==1){ //if the direction is straight
      while (dig.L3 || dig.R3) {
        reflectance_digital(&dig);
        if (!(dig.L3 || dig.R3)) { //if the dig L3 and R3 does not senses anything increase count and print ready
          y++;
          print_mqtt(BUTTON_T, "%d and y %d",x,y);
   
        }
      }
    
    }
                 if(y==3){
          while(!dig.L1&&!dig.R1){
            reflectance_digital(&dig);
            tank_mode_left(10,0);// turn left tank  
            sDirection=0;
            rDirection=0;
            }
       
        }
    if(d<7){
       
        if(round==0){
          while(dig.R1){
            reflectance_digital(&dig);
            tank_mode_right(10,0);// turn left tank
            }
            while(!(dig.L1&&dig.R1&&dig.L2)){
            reflectance_digital(&dig);
            tank_mode_right(10,0);// turn left tank
             sDirection=1;
            rDirection=1;
            round=1;
   }
        }
}    
  if(!dig.L1){
 tank_mode_right(10,0);// turn left tank
}else if(!dig.R1){
tank_mode_left(9,0);// turn left tank
}
    
}
}
#endif
#if 0
void zmain(void){
    struct sensors_ dig;
    uint32_t count =0;
    IR_Start();
    
    reflectance_start();
    
    motor_start();
    motor_forward(0,0);
      printf("\n\n\n!!!BOOT!!!\n\n\n");
    reflectance_set_threshold(14000, 9000, 11000, 11000, 9000, 14000); // set center sensor threshold to 11000 and others to 9000
    reflectance_digital(&dig);
     motor_start();
    motor_forward(0,0);
          while(count<3){
        reflectance_digital(&dig);
        motor_forward(170,10);
        if (dig.R2&&dig.R1){
            motor_turn(255,0,25);   
        }
        else if(dig.L2&&dig.L1){
         motor_turn(0,255,25);    
        } else if((dig.L2&&dig.L3)||dig.L3){
           
         motor_turn(0,255,25);  
        } else if((dig.R2&&dig.R3)||dig.R3){
         motor_turn(255,0,25);     
        }
         
           if (dig.L3 && dig.R3){
        while(dig.L3 && dig.R3){
            motor_forward(170,0);
            reflectance_digital(&dig);
            if(!(dig.L3 && dig.R3)){
            count++;} 
           
           
    }}
        
}

}
#endif 

//Week test
#if 0
void zmain(void){
    
    uint32_t startTime   =0;
    uint32_t stopTime    =0;
    uint32_t elapsedTime =0;
    
    printf("n\n\n !!!BOOT!!!\n\n\n");//clear programming buffer
while(true){
if(SW1_Read()== PRESSED){
print_mqtt(BUTTON_T,"Time of press is: %d",xTaskGetTickCount());
//do all kinds of thing like calculations and prints
//wait until released
print_mqtt(LAP_T,"%d - %d = %d",stopTime,startTime,elapsedTime);

//maybe a short delay for good measure 5-50ms
vTaskDelay(500);
}

}

    while(true){
    vTaskDelay(100);
    }
    }
#endif
#if 0
// Hello World!
void zmain(void)
{
    printf("\nHello, World!\n");

    while(true)
    {
        vTaskDelay(100); // sleep (in an infinite loop)
    }
 }   
#endif

#if 0
// Name and age
void zmain(void)
{
    char name[32];
    int age;
    
    
    printf("\n\n");
    
    printf("Enter your name: ");
    //fflush(stdout);
    scanf("%s", name);
    printf("Enter your age: ");
    //fflush(stdout);
    scanf("%d", &age);
    
    printf("You are [%s], age = %d\n", name, age);

    while(true)
    {
        BatteryLed_Write(!SW1_Read());
        vTaskDelay(100);
    }
 }   
#endif


#if 0
//battery level//
void zmain(void)
{
    ADC_Battery_Start();        

    int16 adcresult =0;
    float volts = 0.0;

    printf("\nBoot\n");

    //BatteryLed_Write(1); // Switch led on 
    BatteryLed_Write(0); // Switch led off 
    //uint8 button;
    //button = SW1_Read(); // read SW1 on pSoC board
    // SW1_Read() returns zero when button is pressed
    // SW1_Read() returns one when button is not pressed

    while(true)
    {
        char msg[80];
        ADC_Battery_StartConvert(); // start sampling
        if(ADC_Battery_IsEndConversion(ADC_Battery_WAIT_FOR_RESULT)) {   // wait for ADC converted value
            adcresult = ADC_Battery_GetResult16(); // get the ADC value (0 - 4095)
            // convert value to Volts
            // you need to implement the conversion
            
            // Print both ADC results and converted value
            printf("%d %f\r\n",adcresult, volts);
        }
        vTaskDelay(500);
    }
 }   
#endif

#if 0 

//Tick Timer Example
void zmain(void) 
{
	TickType_t Ttime = xTaskGetTickCount();
	TickType_t PreviousTtime = 0;

	while(true) 
	{
		while(SW1_Read()) vTaskDelay(1); // loop until user presses button
		Ttime = xTaskGetTickCount(); // take button press time
		/*Print out the time between button presses in seconds. int cast used to suppress warning messages*/
		printf("The amount of time between button presses is: %d.%d seconds\n", (int)(Ttime-PreviousTtime)/1000%60, (int)(Ttime-PreviousTtime)%1000);
		while(!SW1_Read())vTaskDelay(1); // loop while user is pressing the button
		PreviousTtime = Ttime; // remember previous press time
	}
	
}

#endif

#if 0
// button
void zmain(void)
{
    while(true) {
        printf("Press button within 5 seconds!\n");
	    TickType_t Ttime = xTaskGetTickCount(); // take start time
        bool timeout = false;
        while(SW1_Read() == 1) {
            if(xTaskGetTickCount() - Ttime > 5000U) { // too long time since start
                timeout = true;
                break;
            }
            vTaskDelay(10);
        }
        if(timeout) {
            printf("You didn't press the button\n");
        }
        else {
            printf("Good work\n");
            while(SW1_Read() == 0) vTaskDelay(10); // wait until button is released
        }
    }
}
#endif

#if 0
// button
void zmain(void)
{
    printf("\nBoot\n");

    //BatteryLed_Write(1); // Switch led on 
    BatteryLed_Write(0); // Switch led off 
    
    //uint8 button;
    //button = SW1_Read(); // read SW1 on pSoC board
    // SW1_Read() returns zero when button is pressed
    // SW1_Read() returns one when button is not pressed
    
    bool led = false;
    
    while(true)
    {
        // toggle led state when button is pressed
        if(SW1_Read() == 0) {
            led = !led;
            BatteryLed_Write(led);
            if(led) printf("Led is ON\n");
            else printf("Led is OFF\n");
            Beep(1000, 150);
            while(SW1_Read() == 0) vTaskDelay(10); // wait while button is being pressed
        }        
    }
 }   
#endif


#if 0
//ultrasonic sensor//
void zmain(void)
{
    Ultra_Start();                          // Ultra Sonic Start function
    
    while(true) {
        int d = Ultra_GetDistance();
        // Print the detected distance (centimeters)
        printf("distance = %d\r\n", d);
        vTaskDelay(200);
    }
}   
#endif

#if 0
//IR receiverm - how to wait for IR remote commands
void zmain(void)
{
    IR_Start();
    
    printf("\n\nIR test\n");
    
    IR_flush(); // clear IR receive buffer
    printf("Buffer cleared\n");
    
    bool led = false;
    // Toggle led when IR signal is received
    while(true)
    {
        IR_wait();  // wait for IR command
        led = !led;
        BatteryLed_Write(led);
        if(led) printf("Led is ON\n");
        else printf("Led is OFF\n");
    }    
 }   
#endif



#if 0
//IR receiver - read raw data
// RAW data is used when you know how your remote modulates data and you want to be able detect 
// which button was actually pressed. Typical remote control protocols requires a protocol specific
// state machine to decode button presses. Writing such a state machine is not trivial and requires
// that you have the specification of your remotes modulation and communication protocol    
void zmain(void)
{
    IR_Start();
    
    uint32_t IR_val; 
    
    printf("\n\nIR test\n");
    
    IR_flush(); // clear IR receive buffer
    printf("Buffer cleared\n");
    
    // print received IR pulses and their lengths
    while(true)
    {
        if(IR_get(&IR_val, portMAX_DELAY)) {
            int l = IR_val & IR_SIGNAL_MASK; // get pulse length
            int b = 0;
            if((IR_val & IR_SIGNAL_HIGH) != 0) b = 1; // get pulse state (0/1)
            printf("%d %d\r\n",b, l);
        }
    }    
 }   
#endif


#if 0
//reflectance
void zmain(void)
{
    struct sensors_ ref;
    struct sensors_ dig;

    reflectance_start();
    reflectance_set_threshold(9000, 9000, 11000, 11000, 9000, 9000); // set center sensor threshold to 11000 and others to 9000
    

    while(true)
    {
        // read raw sensor values
        reflectance_read(&ref);
        // print out each period of reflectance sensors
        printf("%5d %5d %5d %5d %5d %5d\r\n", ref.L3, ref.L2, ref.L1, ref.R1, ref.R2, ref.R3);       
        
        // read digital values that are based on threshold. 0 = white, 1 = black
        // when blackness value is over threshold the sensors reads 1, otherwise 0
        reflectance_digital(&dig); 
        //print out 0 or 1 according to results of reflectance period
        printf("%5d %5d %5d %5d %5d %5d \r\n", dig.L3, dig.L2, dig.L1, dig.R1, dig.R2, dig.R3);        
        
        vTaskDelay(200);
    }
}   
#endif






#if 0
//motor
void zmain(void)
{
    motor_start();              // enable motor controller
    motor_forward(0,0);         // set speed to zero to stop motors

    vTaskDelay(3000);
    
    motor_forward(150,2000);     // moving forward
    motor_turn(200,50,2000);     // turn
    motor_turn(50,200,2000);     // turn
    motor_backward(100,2000);    // moving backward
     
    motor_forward(0,0);         // stop motors

    motor_stop();               // disable motor controller
    
    while(true)
    {
        vTaskDelay(100);
    }
}
#endif

#if 0
/* Example of how to use te Accelerometer!!!*/
void zmain(void)
{
    struct accData_ data;
    
    printf("Accelerometer test...\n");

    if(!LSM303D_Start()){
        printf("LSM303D failed to initialize!!! Program is Ending!!!\n");
        vTaskSuspend(NULL);
    }
    else {
        printf("Device Ok...\n");
    }
    
    while(true)
    {
        LSM303D_Read_Acc(&data);
        printf("%8d %8d %8d\n",data.accX, data.accY, data.accZ);
        vTaskDelay(50);
    }
 }   
#endif    

#if 0
// MQTT test
void zmain(void)
{
    int ctr = 0;

    printf("\nBoot\n");
    send_mqtt("Zumo01/debug", "Boot");

    //BatteryLed_Write(1); // Switch led on 
    BatteryLed_Write(0); // Switch led off 

    while(true)
    {
        printf("Ctr: %d, Button: %d\n", ctr, SW1_Read());
        print_mqtt("Zumo01/debug", "Ctr: %d, Button: %d", ctr, SW1_Read());

        vTaskDelay(1000);
        ctr++;
    }
 }   
#endif


#if 0
void zmain(void)
{    
    struct accData_ data;
    struct sensors_ ref;
    struct sensors_ dig;
    
    printf("MQTT and sensor test...\n");

    if(!LSM303D_Start()){
        printf("LSM303D failed to initialize!!! Program is Ending!!!\n");
        vTaskSuspend(NULL);
    }
    else {
        printf("Accelerometer Ok...\n");
    }
    
    int ctr = 0;
    reflectance_start();
    while(true)
    {
        LSM303D_Read_Acc(&data);
        // send data when we detect a hit and at 10 second intervals
        if(data.accX > 1500 || ++ctr > 1000) {
            printf("Acc: %8d %8d %8d\n",data.accX, data.accY, data.accZ);
            print_mqtt("Zumo01/acc", "%d,%d,%d", data.accX, data.accY, data.accZ);
            reflectance_read(&ref);
            printf("Ref: %8d %8d %8d %8d %8d %8d\n", ref.L3, ref.L2, ref.L1, ref.R1, ref.R2, ref.R3);       
            print_mqtt("Zumo01/ref", "%d,%d,%d,%d,%d,%d", ref.L3, ref.L2, ref.L1, ref.R1, ref.R2, ref.R3);
            reflectance_digital(&dig);
            printf("Dig: %8d %8d %8d %8d %8d %8d\n", dig.L3, dig.L2, dig.L1, dig.R1, dig.R2, dig.R3);
            print_mqtt("Zumo01/dig", "%d,%d,%d,%d,%d,%d", dig.L3, dig.L2, dig.L1, dig.R1, dig.R2, dig.R3);
            ctr = 0;
        }
        vTaskDelay(10);
    }
 }   

#endif

#if 0
void zmain(void)
{    
    RTC_Start(); // start real time clock
    
    RTC_TIME_DATE now;

    // set current time
    now.Hour = 12;
    now.Min = 34;
    now.Sec = 56;
    now.DayOfMonth = 25;
    now.Month = 9;
    now.Year = 2018;
    RTC_WriteTime(&now); // write the time to real time clock

    while(true)
    {
        if(SW1_Read() == 0) {
            // read the current time
            RTC_DisableInt(); /* Disable Interrupt of RTC Component */
            now = *RTC_ReadTime(); /* copy the current time to a local variable */
            RTC_EnableInt(); /* Enable Interrupt of RTC Component */

            // print the current time
            printf("%2d:%02d.%02d\n", now.Hour, now.Min, now.Sec);
            
            // wait until button is released
            while(SW1_Read() == 0) vTaskDelay(50);
        }
        vTaskDelay(50);
    }
 }   
#endif

/* [] END OF FILE */
