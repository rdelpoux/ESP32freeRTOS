# Closed loop control


This session is evaluated and you need to provide a report on moodle at the end of the session 

[Rendu TP 3](https://moodle.insa-lyon.fr/course/view.php?id=72#section-6)


Download the files for the lab : [download the code](/Programmes/ControlRobotESP_AP.zip).

Plug the WIFI key into your computer.

Edit the program "ControlRobotESP_AP.ino"
Modify line 27 of this program by renaming the variable ssid. This variable is the name of your robot and you have to choose a more specific name to avoid communication problems with other robots. For example, replace "robot1" with "robots_names", where the names are your initials and those of your coworker.


Run the program "ControlRobotESP_AP.ino" and connect to your robot via wifi communication.

Start MATLAB and run the program "SimuESP32.slx".

Double click on button "ESP32 APP". In the new window, clik on the red button "Connect".


## Required work 

### Modelling and identification

- From a step response between the input voltage to the speed of the robot, identify a linear model of the system around a voltage u=3V. Justify this operating point
- Validate this model by comparing the measurements and the simulation of the model

### Control law in real-time

The objective is to propose a speed control of the robot. 

- Based on the identified model, choose a control law, which meets with the following specifications: a null steady-state error in closed loop when input is a 10 rad/s spet signal, settling time in close loop lower or equal to the settling time in open loop, no saturation of the control signal. 
 
- Design this control law with a method of your choice

- Using Matlab/Simulink, propose a simulation scheme and test the proposed control law.

- Use the arduino IDE to implement a discretized version of your control law and check the performance in close loop

- Record the experimental data of the system, plot them on Simulink and discuss compliance with the specifications

- Add a periodic task in parallel to the control law task and analyze the close loop performances according to the duration of the task.


