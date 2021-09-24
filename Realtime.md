# Introduction to FreeRTOS

## Introduction

The objective of this lab is to become familiar with the real-time multi-tasking mechanisms offered by FreeRTOS on an ESP32 microcontroller. 

At the end of this session you should be familiar with the following concepts: 

- Tasks
- Priorities
- Periodic tasks
- Semaphore
- Mutex 
- Interrupt
- ...

This sessions is evaluated you must file a report on moodle at the end of the session (Answer to questions and oscilloscope screenshots are provided only. No code should appear in the report):

[Rendu TP 2](https://moodle.insa-lyon.fr/mod/assign/view.php?id=157986)

The answers of the different questions will be added to the report of the lab session 1.

This session is based on the work proposed by Thierry Vaira [tvaira@free.fr](mailto:tvaira@free.fr) :

- [ESP32 + FreeRTOS](http://tvaira.free.fr/esp32/esp32-freertos.html)

This page is well detailed, you are encouraged to consult it.

The freeRTOS site is also well documented: 

- https://www.freertos.org/RTOS.html

## Required functions : 

### Include following header files : 

```c
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "sdkconfig.h"
```

### Tasks

```c
/* Task to be created. */ 
void vTaskCode( void * pvParameters ) 
{    
    /* The parameter value is expected to be 1 as 1 is passed in the    
    pvParameters value in the call to xTaskCreate() below.*/
    configASSERT( ( ( uint32_t ) pvParameters ) == 1 ); // infinite loop     
    for( ;; )    
    {        
        /* Task code goes here. */    
    } 
}
```

Create task:

```c
xTaskCreate(
    vATaskFunction, /* Task function. */
    "vATaskFunction", /* name of task. */
    10000, /* Stack size of task */
    NULL, /* parameter of the task */
    1, /* priority of the task */
    NULL); /* Task handle to keep track of created task */
```

Create task executed on defined core:

```c
xTaskCreatePinnedToCore(
    vATaskFunction, /* Task function. */
    "vATaskFunction", /* name of task. */
    10000, /* Stack size of task */
    NULL, /* parameter of the task */
    1, /* priority of the task */
    NULL,/* Task handle to keep track of created task */
	xCoreID);/*Specify the core*/ 
```

### vTaskDelay

```c
void vTaskDelay( const TickType_t xTicksToDelay );
```

The `pdMS_TO_TICKS() ` macro can be used to convert a time specified in milliseconds to a number of ticks :

```c
vTaskDelay( pdMS_TO_TICKS( 500 ) );
```

### vTaskDelayUntil

```c
void vTaskDelayUntil( TickType_t *pxPreviousWakeTime,                     
						const TickType_t xTimeIncrement );
```

**Example usage:**    

```c
// Perform an action every 10 ticks. 
void vTaskFunction( void * pvParameters ) 
{ 
    TickType_t xLastWakeTime; 
    const TickType_t xFrequency = 10;      
    // Initialise the xLastWakeTime variable with the current time.     
    xLastWakeTime = xTaskGetTickCount();      
    for( ;; )     
    {         
        // Wait for the next cycle.         
        vTaskDelayUntil( &xLastWakeTime, xFrequency );          
        // Perform action here.     
    } 
}   
```



## 1. Launching competing tasks

The objective of this section is to understand the different mechanisms when two tasks are executed in parallel. To do this, we will observe the execution of tasks using an oscilloscope by performing tasks that blinks a pin. 

1 . Create a task which blinks a pin and observe the result with the oscilloscope :

![probes](https://user-images.githubusercontent.com/57991923/134173253-c9426799-a8c7-4cf9-9f38-db5377b86162.jpg)

Fix the itarationNb to 1000.

```c
//simulate work
for( i = 0; i<iterationsNb; i++ ) {
  if (state == HIGH)
    state = LOW;
  else
    state = HIGH;
  digitalWrite(pinToOscillo, state);   
```

2. Two competing tasks

   Implement a program that

   - has two tasks in parallel

   - higher priority is given to the first task

   - Core ID is not fixed

   - The core used by the task can be displayed on the serial monitor using the command 

     ```c
      Serial.printf("vTask1 / core %d started\n", xPortGetCoreID());
     ```

   - Observe the behavior with the oscilloscope et comment.

3. Two tasks in competition (variant)

   - Execute both tasks on the same core.
   - Comment, how can the observed problem be avoided?

4. Periodic tasks

   - Add a delay after the simulated work of each task using the function :

     ```c
     vTaskDelay( pdMS_TO_TICKS( task1_period ) );    
     ```

   - What periods do we get for tasks 1 and 2? Explain.

   - What happens if we force the 2 tasks to run on the same core?

   - Is this a good approach?

5. Periodic tasks

   - Use now the function 

      ```c
      vTaskDelayUntil( &xLastWakeTime, pdMS_TO_TICKS( task1_period ) );
      ```

     - What periods do we get for tasks 1 and 2? Explain why.
     - What happens if we force the 2 tasks to run on the same core?
     - Gradually increase the varaiable nb_iterations in order to lengthen the working time of the 2 tasks. What happens?

## 2. Synchronization between tasks

1. Principles

   A binary semaphore can be used to synchronize 2 tasks. MUTEX are useful to protect a common resource. Another major difference between Mutex and Binary Semaphores in FreeRTOS is the priority inheritance system. When multiple tasks request to take a Mutex, the priority of the Mutex holder is momentarily set to the highest priority value among the tasks waiting for its release. This technique has the effect of preventing the priority inversion phenomena seen during the first lab session, even if it does not guarantee infallible security against these phenomena.

2. Experiment 1 

   Download and Run the program: [Synchro1.ino](/Programmes/FreeRTOSExercises/Synchro1)

   - Explain what the program does and how it does it. 

3. Experiment 2

   Download and Run the program: [Synchro2.ino](/Programmes/FreeRTOSExercises/Synchro2)

   - Explain what the program does (use the oscilloscope and a serial console).
   - What is not working correctly?
   - Remove the comments from lines 56-57, 64-65, 91-92, 99-100. Explain what happens

4. Interrupts

     - Download and Run the program: [Interrupts.ino](/Programmes/FreeRTOSExercises/Interrupts) 
     - Explain what the program does (use the oscilloscope and the serial monitor).
     - Modify the program so that it shows the movement of the left wheel on channel 1 and the right wheel on channel 2.

## 3. Communication between tasks



Download and Run the program: [TasksCommunication.ino](/Programmes/FreeRTOSExercises/TasksCommunication) 
  - Explain what the program does (use the oscilloscope and a serial console).

  - Take the example program #7 from the [ESP32+FreeRTOS](http://tvaira.free.fr/esp32/esp32-freertos.html#communication-entre-t%C3%A2ches) web page.

       Run it, modify the task parameters and comment.

## 4. Other possibilities if you still have spare time

1. Stop a task with vTaskDelete : see example n°5 of the [ESP32+FreeRTOS](http://tvaira.free.fr/esp32/esp32-freertos.html#communication-entre-t%C3%A2ches) web page  
2. Software timers Example n°9

# Final rendering

Remember to upload your PDF report to moodle 

​    [Rendu TP 2](https://moodle.insa-lyon.fr/mod/assign/view.php?id=157986)

# Sources

- [ESP32 + FreeRTOS](http://tvaira.free.fr/esp32/esp32-freertos.html)
- [FreeRTOS](https://www.freertos.org/RTOS.html)
