# Introduction to FreeRTOS

## Introduction

The objective of this lab is to become familiar with the real-time multi-tasking mechanisms offered by FreeRTOS on an ESP32 microcontroller.

Files required in this session are available on Moodle:
https://moodle.insa-lyon.fr/mod/folder/view.php?id=157399

The answers of the different questions will be added to the report of the lab session 1.


## Launching competing tasks

For the following sections, connect 2 probes of an oscilloscope to the pins of the board (see Figure below). Connect the ground to the outermost pin (0), connect channel 1 to the neighboring pin (gray probe) and channel 2 to the farthest pin (black probe).


![probes](https://user-images.githubusercontent.com/57991923/134173253-c9426799-a8c7-4cf9-9f38-db5377b86162.jpg)

1. Two competing tasks

   1. a First try

      Run the program: IF4_TP_S2_Q21a.ino

         1.	Describe briefly what is done by the program and the result obtained on the oscilloscope. Justify this result.
         2.	Open a serial monitor. What can you notice?

   2. Two tasks in competition (variant)

      Run the program: IF4_TP_S2_Q21b.ino

        1. What is the difference with the previous program?
        2. What is the impact on the operation on the oscilloscope and the serial monitor?
        3. How can this problem be avoided?

2. Periodic tasks

   1. First approach
      Run the program: IF4_TP_S2_Q22a.ino

      1. What are the differences with the previous program?
      2. What periods do we get for tasks 1 and 2? Explain
      3. What happens if we force the 2 tasks to run on the same core?
      4. Is this a good approach?

   2. Second approach

      Run the program: IF4_TP_S2_Q22b.ino
        1.	What are the differences with the previous program?
        2.	What periods do we get for tasks 1 and 2? Explain why.
        3.	What happens if we force the 2 tasks to run on the same core?
        4.	Gradually increase the varaiable nb_iterations in order to lengthen the working time of the 2 tasks. What happens?

  3. Synchronization between tasks

       1. Principles

          A binary semaphore can be used to synchronize 2 tasks. MUTEX are useful to protect a common resource. Another major difference between Mutex and Binary Semaphores in FreeRTOS is the priority inheritance system. When multiple tasks request to take a Mutex, the priority of the Mutex holder is momentarily set to the highest priority value among the tasks waiting for its release. This technique has the effect of preventing the priority inversion phenomena seen during the first lab session, even if it does not guarantee infallible security against these phenomena.

       2. Experiment 1 

          Run the program: IF4_TP_S2_Q23b.ino

          Explain what the program does and how it does it

       3. Experiment 2

          Run the program: IF4_TP_S2_Q23c.ino

          1. Explain what the program does (use the oscilloscope and a serial console).
          2. What is not working correctly?
          3. Remove the comments from lines 56-57, 64-65, 91-92, 99-100. Explain what happens

     4. Interrupts

        Run the program: IF4_TP_S2_Q23d.ino

          1. Explain what the program does (use the oscilloscope and the serial console).
          2. Modify the program so that it shows the movement of the left wheel on channel 1 and the right wheel on channel 2.

  4. Communication between tasks

     Run the program: IF4_TP_S2_Q24a.ino
       1.	Explain what the program does (use the oscilloscope and a serial console).
       2. Take the example program #7 from the ESP32+FreeRTOS web page.

            http://tvaira.free.fr/esp32/esp32-freertos.html#communication-entre-t%C3%A2ches

            Run it, modify the task parameters and comment.

5. Other possibilities if you still have spare time

   1. Stop a task with vTaskDelete : see example n°5 of the ESP32+FreeRTOS web page  
   2. Software timers Example n°9







    

