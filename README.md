# Lab : FreeRTOS - Mobile Robot ESP32

<img src="https://raw.githubusercontent.com/rdelpoux/ESP32Robot/main/img/MobileRobile.jpg" alt="Dual-brige " width="400" />

This repository is dedicated to Practical Work supports intended for students of the Multi-Task and Real Time course proposed to 5th year student in the electrical engineering department at  [INSA Lyon](www.insa-lyon.fr). 

## Content

- [Contributors](#Contributors)
- [Lab objective](#objective)
- [Session 1](#session1)
- [Session 2](#session2)
- [Session 3](#session3)
- [Session 4](#session4)
- [Sources](#sources)
- [License](#license)

## Contributors <a name="contributors"></a>

- Romain Delpoux (romain.delpoux at insa-lyon.fr), Associate Professor, INSA de Lyon, Laboratoire Ampère UMR CNRS 5005.
- Arnaud Lelevé (arnaud.leleve at  insa-lyon.fr), Associate Professor, INSA de Lyon, Laboratoire Ampère UMR CNRS 5005.
- Minh Tu Pham (minh-tu.pham at insa-lyon.fr), Associate Professor, INSA de Lyon, Laboratoire Ampère UMR CNRS 5005.
- Pascal Bevilacqua (pascal.bevilacqua at insa-lyon.fr), Engineer, INSA de Lyon, Laboratoire Ampère UMR CNRS 5005.

## Lab objective <a name="objective"></a>

The Lab is divided into 3 sessions of 4 hours and a bonus

1. Getting to know the system and the control environment (4h)
2. Real-time programmation (4h)
3. Robot speed control and robot trajectory tracking (4h)
4. Automatic code generation

At the end of this project, students should be able to :

- Drive a DC motor with encoder
- Understand difference between open and closed loop systems.
- Understand how a real-time system works  (Tasks, Priorities, ...) 
- Identify a linear system 
- Simulate a linear system and compare with experimental data 
- Design and implement a control law (Simulation + Experimentation)
- Enjoy !!!

## Session 1 <a name="session1"></a>

The objective of this first session is to discover the system. At the end of the session, the student should have 

- Learned about the Arduino programming environment for ESP32.
- Run both motors (forward, backward).
- Used encoders.
- Understand the open-loop behavior of the Robot
- Used Wi-Fi server

### System description

For system description goto : [System description page](/SystemDescription.md)

### Getting Started with the ESP32 Development Board

- [Preparing the ESP32 Board in Arduino IDE](https://randomnerdtutorials.com/getting-started-with-esp32/)

There’s an add-on for the Arduino IDE allows you to program the ESP32 using the Arduino IDE and its programming language. Follow one of the  next tutorials to prepare your Arduino IDE:

- [**Windows** instructions – Installing the ESP32 Board in Arduino IDE](https://randomnerdtutorials.com/installing-the-esp32-board-in-arduino-ide-windows-instructions/)
- [**Mac and Linux** instructions – Installing the ESP32 Board in Arduino IDE](https://randomnerdtutorials.com/installing-the-esp32-board-in-arduino-ide-mac-and-linux-instructions/)

### DC motor with encoder

The tutorial to drive the DC motor can be found here : [DC Motor with encoder](/Motorwithencoder.md)

### Motor control over Wi-fi

To drive the system over Wi-Fi : [download the code](/Programmes/RobotoverWIFI.zip). 

The code is based on [ESP32 Access Point (AP) for Web Server tutorial](https://randomnerdtutorials.com/esp32-access-point-ap-web-server/). To use the code : 

- Make sure that you have change the **ssid** in the code

```c
const char* ssid     = "robotX";
```

- In your smartphone open your Wi-Fi settings and tap the **robotX** network.
- Open your web browser and type the IP address 192.168.4.1. The web server page should.

### ESP32 FreeRTOS

- [FreeRTOS](http://tvaira.free.fr/esp32/esp32-freertos.html)

## Session 2 <a name="session2"></a>
The objective of this lab is to become familiar with the real-time multi-tasking mechanisms offered by FreeRTOS on an ESP32 microcontroller.
- Instructions are given here :  [Real-time](Realtime.md)

## Session 3 <a name="session3"></a>

The objective of the lab is to implement a speed control so that the robot moves straight ahead. 

- Instructions are given here : [Closed Loop Control](Closedloopcontrol.md)

## Session 4 <a name="session2"></a>

To implement different control laws on the robot we propose here a solution for automatic code generation :

- [Automatic code generation](AutomaticCodeGeneration.md)

## Sources <a name="sources"></a>

- [https://randomnerdtutorials.com](https://randomnerdtutorials.com)
- [ESP32 + FreeRTOS](http://tvaira.free.fr/esp32/esp32-freertos.html)

## License <a name="license"></a>

The proposed materials on this repository are free of charge to use and is openly distributed, but note that

1.  Copyright owned by Romain Delpoux.
2.  The algorithms, or forks of the algorithms may not be re-distributed as a part of a commercial product unless agreed upon with the copyright owner. 
4. This work is distributed in the hope that it will be useful, but without any warranty, without event the implied warranty of merchantability or fitness for a particular purpose.







