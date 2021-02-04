# ESP32Robot

This repository is dedicated to the development of a new mobile robot for Labs proposed for student in the French engineering school [INSA Lyon](www.insa-lyon.fr). In a COVID context the objective is to propose to our student automatic control lab which can be taught both in class and remotely in the event of confinement. The constraint is to be able to illustrate the basic automatic control principles on a simple system, without the need for software requiring a significant computing capacity.  During the lab, Matlab/Simulink:registered:  can be used to do the corrector synthesis, but the students can access it remotely using a VPN.

Given the specifications, our choice is directed to an ESP32 controller. This makes it possible to embed a web server and that the students can realize the entire Lab using only an internet browser.  

## Contibutors

- Romain DELPOUX (Romain.Delpoux at insa-lyon.fr), Assistant Professor, INSA de Lyon, Laboratoire Ampère UMR CNRS 5005.

- Florian Bianco (Florian.Bianco at univ-lyon1.fr), Teacher, IUT GEII Lyon.
- Pascal Bevilacqua (pascal.bevilacqua at insa-lyon.fr), Engineer, INSA de Lyon, Laboratoire Ampère UMR CNRS 5005.

## System description

The system is composed this system is composed of 

- [Dual half bridge](https://store.digilentinc.com/pmod-dhb1-dual-h-bridge/)

<img src="https://raw.githubusercontent.com/rdelpoux/ESP32Robot/main/img/Pmod_DHB1.png" alt="Dual-brige " style="zoom:50%;" />



- [Two motors with encoders](https://store.digilentinc.com/dc-motor-gearbox-1-53-gear-ratio-custom-6v-motor-designed-for-digilent-robot-kits/)

<img src="https://raw.githubusercontent.com/rdelpoux/ESP32Robot/main/img/moteur-reducteur-avec-encodeur.png" alt="motor" style="zoom:80%;" />



- [Motor hubs](https://www.lextronic.fr/moyeux-pour-moteurs-pololu-30809.html)

![moyeux](https://raw.githubusercontent.com/rdelpoux/ESP32Robot/main/img/moyeux-pour-moteurs-pololu.jpg)

- [60 mm wheels](https://www.lextronic.fr/paire-de-roues-diametre-60-mm-30817.html)

![wheel](https://raw.githubusercontent.com/rdelpoux/ESP32Robot/main/img/paire-de-roues-diametre-60-mm.jpg)

- [Motor support](https://www.lextronic.fr/support-pour-moteurs-30627.html)

![support](https://raw.githubusercontent.com/rdelpoux/ESP32Robot/main/img/support-pour-moteurs.jpg)

- [Free wheel](https://www.manomano.fr/catalogue/p/litzee-transfert-a-billes-roulettes-pour-meubles-roulettes-transfert-a-rouleaux-unites-de-transfert-a-billes-fer-galvanise-avec-boules-en-nylon-pour-transmission-meubles-fauteuil-roulant-6-pieces-28320695?g=1&referer_id=689880&cq_src=google_ads&cq_cmp=11057446537&cq_con=110150695580&cq_term=&cq_med=pla&cq_plac=&cq_net=g&cq_pos=&cq_plt=gp&cq_plt=gp&gclid=Cj0KCQiA0-6ABhDMARIsAFVdQv8q6O9rFnHw9-YfIDL3XiyYXy5AE14RHB-vroiU9LCYbMjPGpgr8QIaAvA5EALw_wcB#/)

  <img src="https://raw.githubusercontent.com/rdelpoux/ESP32Robot/main/img/free-wheel.jpg" alt="free-wheel " style="zoom:30%;" />

  

  



