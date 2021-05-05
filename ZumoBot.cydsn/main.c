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
// *********Functions  for tank turning************ 
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
#define READY "Group_10/ready "
#define START "Group_10/start "
#define OBSTACLE "Group_10/obstacle "
#define STOP "Group_10/stop "
#define TIME "Group_10/time "
#define MISS "Group_10/miss "
#define LINE "Group_10/line "
//project 1



#if 1
void zmain(void)
{
    Ultra_Start();              // Ultra Sonic Start function
    motor_start();              // enable motor controller
    motor_forward(0,0);         // set speed to zero to stop motors
    int dis=0;                  // the distance
    int decider=0;              // decide
    int turn;                   // turns
    struct sensors_ dig;        // sensor
    uint32_t count =0;          // count line
    uint32_t startTime =0;      // start time
    IR_Start();                 // start IR
    uint32_t movementTime =0;   // movement time
    int timepress;              // physical button time
    reflectance_start();        // start the sensor
    
printf("\n\n\n!!!BOOT!!!\n\n\n");   //clear programming buffer
reflectance_set_threshold(9000,     // set center sensor threshold to 11000 and others to 9000
 9000, 11000, 11000, 9000, 9000);   // read digital values that are based on threshold. 0 = white, 1 = black
reflectance_digital(&dig);          // when blackness value is over threshold the sensors reads 1, otherwise 0
                               
                                
while (SW1_Read() != PRESSED) // while value is not 0
BatteryLed_Write(ON);         // Turns led on
vTaskDelay(1000);             // sleep (in an infinite loop)
BatteryLed_Write(OFF);        // Turns led off

reflectance_digital(&dig);

//LINE UP CODE
while (count < 1) {                 //while the count is below 1
  reflectance_digital(&dig);
  motor_forward(50, 0);             // moves forward
  if (dig.L3 && dig.R3) {           //If the dig L3 and R3 senses anything, do the code below
    while (dig.L3 && dig.R3) {      //while the dig L3 and R3 senses anything, do the code below
        
      reflectance_digital(&dig);
      if (!(dig.L3 && dig.R3)) {    //if the dig L3 and R3  does not sense anything, do the code below
        count++;                    //add count 1
        print_mqtt(READY, "zumo");  // when robot is on the line
      }
    }
  }
}

motor_forward(0, 0);                 // stop
IR_wait();                           // waits for the button press of IR
startTime = xTaskGetTickCount();     // get the time when on position
print_mqtt(START, "%d", startTime);  // print start time

// THE DODGING CODE
while (count < 2) {
  turn = rand() % 111 + 60;           // random turn of degrees
  movementTime = xTaskGetTickCount(); // counts tick
  dis = Ultra_GetDistance();          // sensor getting distance
  reflectance_digital(&dig);          // Prints the detected distance (centimeters)
  motor_forward(100, 0);              // moving forward

  if (dis <= 10) {
    motor_backward(100, 200);         // moving backward
    decider = rand() % 2 + 1;         // decide what direction will turn
    if (decider == 1) {
      tank_mode_left(turn, 370);      // turn left tank
      print_mqtt(OBSTACLE, "%d",
      xTaskGetTickCount());           // if there is an obstacle: print the time
                                      
    } else {
      tank_mode_right(turn, 375);  // turn right tank
      print_mqtt(OBSTACLE, "%d", xTaskGetTickCount());
    }
  } else if ((dig.L3 && dig.L2) ||
             (dig.R3 && dig.R2)) { // if the sensor senses the dig L3 and L2 or
                                   // senses R3 and R2
    motor_backward(100, 200);      // moving backward

    decider = rand() % 2 +
              1;                   // decide what direction will turn made two cause for funnys
    if (decider == 1) {
      tank_mode_left(turn, 370);   // turn left tank
      print_mqtt(OBSTACLE, "%d", xTaskGetTickCount());
    } else {
      tank_mode_right(turn, 375);   // turn right tank
      print_mqtt(OBSTACLE, "%d", xTaskGetTickCount());
    }
  }

// STOP CODE
if (SW1_Read() == PRESSED) { // when the buttos is press
  BatteryLed_Write(ON);      // Turns led on
  motor_start(0, 0);
  motor_stop();
  timepress = movementTime - startTime; // reduce the stop time and start time
  print_mqtt(STOP, "%d",
             movementTime); // Stop time (when the user button is pressed robot
                            // stops and sends stop time stamp)
  print_mqtt(TIME, "%d",
             timepress); // Run time (from start to finish, number of
                         // milliseconds between start and stop)
  while (true) {
    vTaskDelay(100); // when robot is done
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
// when blackness value is over threshold the sensors reads 1, otherwise 0
  reflectance_digital(&dig);

  while (SW1_Read() != PRESSED) // while value is not 0
    BatteryLed_Write(ON);       // Turns led on
  vTaskDelay(1000);             // sleep (in an infinite loop)
  BatteryLed_Write(OFF);        // Turns led off

  reflectance_digital(&dig);

//LINE UP CODE
  while (count < 1) { //while the count is below 1
    reflectance_digital(&dig);
    motor_forward(50, 0); // moves forward to line
    if (dig.L3 && dig.R3) { // if the dig L3 & R3 detect anything, it will do the code below. 
      while (dig.L3 && dig.R3) { //while dig L3 & R3 detect anything, it will do the code below. 
        reflectance_digital(&dig);
        if (!(dig.L3 && dig.R3)) { //if the dig L3 and R3 does not senses anything increase count and print ready
          count++; // increases the count by one
          print_mqtt(READY, "line"); // the robot is in a ready position
        }
      }
    }
  }

motor_forward(0, 0);
IR_wait();                      // waits for the button press
starTime = xTaskGetTickCount(); // counts from the time when robot was booted
print_mqtt(START, "%d", starTime); // start time
reflectance_digital(&dig);
motor_forward(255, 10);

// COURSE CODE
while (count < 2) {    // while the count is below 2, continue
  xTaskGetTickCount(); // counts the seconds when robot is moving
  reflectance_digital(&dig);
  summa = dig.L3 + dig.R3 + dig.L2 + dig.R2 + dig.L1 + dig.R1; // add to summa
  if (summa ==
      6) { // if all dig together is equal to 6 it will peform the code below
    while (dig.L3 && dig.R3) {
      motor_forward(170, 0);
      reflectance_digital(&dig);
      if (!(dig.L3 && dig.R3)) { // if the dig L3 and R3 does not senses
                                 // anything increase count
        count++;
      }
    }
  } else if (dig.L1 && dig.R1) {
    motor_forward(255, 10);
  } else if ((dig.L2 || dig.L3) && dig.L3) {
    if (!dig.L1 && !dig.R1) {
      print_mqtt(MISS, "%d",
                 xTaskGetTickCount()); // prints when the line is 'miss'
    }
    motor_turn(0, 255, 25);
  } else if ((dig.R2 || dig.R3) && dig.R3) {
    if (!dig.L1 && !dig.R1) {
      print_mqtt(MISS, "%d", xTaskGetTickCount());
    }
    motor_turn(255, 0, 25);
  } else if (dig.R2 && dig.R1) {
    motor_turn(240, 0, 25);
  } else if (dig.L2 && dig.L1) {
    motor_turn(0, 240, 25);
  }
}
// ALIGNMENT CODE
while (count < 3) {
  endTime = xTaskGetTickCount(); // end time is to count the whole course from
                                 // booting to the end
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
      print_mqtt(MISS, "%d", xTaskGetTickCount());
    }
    motor_turn(100, 0, 25);
  } else if (!dig.R1) {
    if (!dig.L1 && !dig.R1) {
      print_mqtt(MISS, "%d", xTaskGetTickCount());
    }
    motor_turn(0, 100, 25);
  }
}

motor_forward(0, 0);
motor_stop();

stopTime = endTime - starTime;
print_mqtt(STOP, "%d", endTime);
print_mqtt(TIME, "%d", stopTime);
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
  int summa,x=0,y=0,d,decider,rDirection=0,lDirection=0,sDirection=0,round=0,result,nano;            // to count all dig together
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
          print_mqtt(READY, "line");
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
        if (dig.L2&&dig.L1){
        if (!(dig.R3||dig.L3)) { //if the dig L3 and R3 does not senses anything increase count and print ready
         
          x++;
          print_mqtt(READY, "x %d  %d",x,y);

        }
      }}
    
    }

        if(lDirection==1){ //if the direction is straight
      while (dig.L3 || dig.R3) {
        reflectance_digital(&dig);
        
        if (!dig.R3&&!dig.L3&&dig.L1) { //if the dig L3 and R3 does not senses anything increase count and print ready
          y--;
          print_mqtt(READY, "%d and y-- %d",x,y);

        }
      }

    }
            if(rDirection==1){ //if the direction is straight
      while (dig.L3 || dig.R3) {
        reflectance_digital(&dig);
        if (!dig.R3&&!dig.L3&&dig.L1&&dig.R1) { //if the dig L3 and R3 does not senses anything increase count and print ready

         y++;
        

          print_mqtt(READY, "%d and y++ %d",x,y);
   
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
         
            }
        }
       
}    

if(y==0&&lDirection==1){
    vTaskDelay(500);
      while(dig.R1){
            reflectance_digital(&dig);
            tank_mode_right(10,0);// turn left tank
            }
            while(!(dig.L1&&dig.R1&&dig.L2)){
            reflectance_digital(&dig);
            tank_mode_right(10,0);// turn left tank
            }
 sDirection=0;
          lDirection=0;
            round=0;
}
  if(!dig.L1){
   reflectance_digital(&dig); 
 tank_mode_right(10,0);// turn left tank
} if(!dig.R1){
    reflectance_digital(&dig);
tank_mode_left(9,0);// turn left tank
}
nano=dig.R2+dig.R3;
result=dig.L1 + dig.R1;
if((x==12 && y==3)||(sDirection==0&&result==0)){    
        lDirection=1;
        sDirection=1; 
    print_mqtt(READY, "1");
        while(!dig.L1){
            reflectance_digital(&dig);
            tank_mode_left(10,0);// turn left tank
            }
           while(!(dig.L1&&dig.R1&&dig.L2)){
            reflectance_digital(&dig);
            result=dig.L1 + dig.R1;
            tank_mode_left(150,0);// turn left tank
           
         }           
    
        

} 

else if (result==0&&rDirection==1){ //on the border
        print_mqtt(READY, "2");
 
           while(!(dig.L1&&dig.R1&&dig.L2)){
            reflectance_digital(&dig);
            result=dig.L1 + dig.R1;
            tank_mode_left(150,0);// turn left tank
             
         }
         sDirection=0;
         lDirection=0;
        }
          
}
}
#endif


/* [] END OF FILE */
