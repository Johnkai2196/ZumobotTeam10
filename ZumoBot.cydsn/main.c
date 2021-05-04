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
 
void tank_mode_left(uint8_t speed, uint32_t delay) {
    SetMotors(1, 0, speed, speed, delay);
}
void tank_mode_right(uint8_t speed, uint32_t delay) {
    SetMotors(0, 1, speed, speed, delay);
}

#define PRESSED 0
#define RELEASED 1
#define ON 1
#define OFF 0
#define BUTTON_T "Group_10/Button"
#define LAP_T "Group_10/Lap"
//project 1

//made by jekku

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
    vTaskDelay(100); //when done
  }
}

    }
  
}
#endif

#if 0
//project 2
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

//project 3
void zmain(void) 
{
	
  uint32_t endTime = 0;  //end time
  uint32_t starTime = 0; //start time
  uint32_t stopTime = 0; //stop time
  struct sensors_ dig;   // sensor
  uint32_t count = 0;    // line counter
  int summa,x=0,y=0,d,decider,rDirection=0,lDirection=0,sDirection=0,round=0,result;            // to count all dig together
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
        else if(round==1){
        while(dig.L1){
            reflectance_digital(&dig);
            tank_mode_left(10,0);// turn left tank
            }
            while(!(dig.L1&&dig.R1&&dig.L2)){
            reflectance_digital(&dig);
            tank_mode_left(10,0);// turn left tank
            sDirection=1;
            lDirection=1;
            round=0;
            }
        }
       
}    
  if(!dig.L1){
   reflectance_digital(&dig); 
 tank_mode_right(10,0);// turn left tank
} if(!dig.R1){
    reflectance_digital(&dig);
tank_mode_left(9,0);// turn left tank
}
result=dig.L1 + dig.R1;
        if (result==0){ //on the border
           while(result==0){
            reflectance_digital(&dig);
            result=dig.L1 + dig.R1;
            tank_mode_left(150,0);// turn left tank
         }
        }
}
}
#endif


/* [] END OF FILE */
