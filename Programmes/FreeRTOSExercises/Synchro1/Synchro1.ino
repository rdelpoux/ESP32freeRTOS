// Programme IF4_TP_S2_Q21b

// périodes des tâches en ms
int task1_period = 10;
int task2_period = 20;

int nb_iterations = 10000;

// pins sondées à l'oscillo
// mettre la masse sur la pin la broche la + externe, voie 1 (tâche 1) sur la broche voisine et voie 2 sur la broche la + éloignée
uint8_t oscillo1     = 19;
uint8_t oscillo2     = 5;

// priorité des tâches 1 et 2
int task1_prio = 1;
int task2_prio = 10;

// variables globales représentant les tâches 1 et 2
TaskHandle_t Task1, Task2;

// Variable globale pour accéder à un sémaphore binaire
SemaphoreHandle_t semaphore = NULL;

/******************************
 * code de la tâche 1
 * ****************************
 */
void vTask1( void *pvParameters )
{
  bool etat = LOW;
  int i = 0;
  TickType_t xLastWakeTime;  
  
  Serial.printf("vTask1 / core %d started\n", xPortGetCoreID());
  
  // boucle infinie
  for( ;; )
  {
    //mémorise l'heure actuelle
    xLastWakeTime = xTaskGetTickCount();

    //simule du travail
    for( i = 0; i<nb_iterations; i++ ) {
      if (etat == HIGH)
        etat = LOW;
      else
        etat = HIGH;
      digitalWrite(oscillo1, etat);     
    }
  
    // libère le sémaphore pour démarrer la tâche 2
    xSemaphoreGive( semaphore );
    
    
    //endort la tâche pour qu'elle se réveille dans task1_period ms depuis dernier réveil
    vTaskDelayUntil( &xLastWakeTime, pdMS_TO_TICKS( task1_period ) ); 
  }

  // si la tâche devait se terminer d'elle même, alors finir avec:
  // vTaskDelete( NULL );
}


/******************************
 * code de la tâche 2
 * ****************************
 */
void vTask2( void *pvParameters )
{
  bool etat = LOW;
  int i;
  

  Serial.printf("vTask2 / core %d started\n", xPortGetCoreID());
  
  // boucle infinie
  for( ;; )
  {
    /* See if we can obtain the semaphore.  If the semaphore is not
        available wait 10 ticks to see if it becomes free. */
    if (xSemaphoreTake( semaphore, ( TickType_t ) 10 ) == pdTRUE ) {
  
      //simule du travail
      for( i = 0; i<nb_iterations; i++ ) {
        if (etat == HIGH)
          etat = LOW;
        else
          etat = HIGH;
        digitalWrite(oscillo2, etat);      
      }
      
      
    }    
  }

  // si la tâche devait se terminer d'elle même, alors finir avec:
  // vTaskDelete( NULL );
}


/**
 * Appelée au démarrage du programme pour initialiser la liaison série et créer les tâches
 */
void setup()
{
  // initialisation de la communication série via USB PC
  Serial.begin(115200);
  while (!Serial);
  Serial.println("Start");

  // declare 2 sorties TOR, celles accessibles à côté de la prise USB
  pinMode(oscillo1, OUTPUT);
  pinMode(oscillo2, OUTPUT);

  //création d'un sémaphore binaire
  semaphore = xSemaphoreCreateBinary();

  //blocage d'emblée
  xSemaphoreTake( semaphore, ( TickType_t ) 10 );
  
  /* créé 1 tâche en forçant l'allocation au noyau 0 
   *  cf https://randomnerdtutorials.com/esp32-dual-core-arduino-ide/
  
   *  vTask1,     Function to implement the task 
      "Task1",    Name of the task 
      10000,      Stack size in words 
      NULL,       Task input parameter 
      task1_prio, Priority of the task 
      &Task1,     Task handle. 
      0);         Core where the task should run 
  */  
  xTaskCreatePinnedToCore( vTask1, "Task1", 10000, NULL, task1_prio, &Task1, 0);
  xTaskCreatePinnedToCore( vTask2, "Task2", 10000, NULL, task2_prio, &Task2, 1); 
   

  /* boucle infinie pour empêcher loop() d'être lancé sous forme d'1 3e tâche sur le core 1, priorité 1, cf http://tvaira.free.fr/esp32/esp32-freertos.html */
  for( ;; ) {
    delay(1);
    }
}




// fonction appelée par défaut et en boucle indéfiniment par l'OS
void loop()
{
}
