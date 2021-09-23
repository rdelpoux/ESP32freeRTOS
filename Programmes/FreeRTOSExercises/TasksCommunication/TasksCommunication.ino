// Programme IF4_TP_S2_Q21b
 
#define TAILLE_MAX    5

// param oscillations
int nb_iterations = 10;
int half_period_ms = 5;

// pins sondées à l'oscillo
// mettre la masse sur la pin la broche la + externe, voie 1 (tâche 1) sur la broche voisine et voie 2 sur la broche la + éloignée
uint8_t oscillo1     = 19;
uint8_t oscillo2     = 5;

// priorité des tâches 1 et 2
int task1_prio = 20;
int task2_prio = 10;


// variables globales représentant les tâches 1 et 2
TaskHandle_t Task1, Task2;

QueueHandle_t xQueue;

/**
 * simule du travail en alternant la sortie fournie en paramètre
 */
void alternate(uint8_t output, int half_period_ms) {
  int i, etat = LOW;
  for( i = 0; i<nb_iterations; i++ ) {
    if (etat == HIGH)
      etat = LOW;
    else
      etat = HIGH;
    digitalWrite(output, etat); 
    delay(half_period_ms)  ;  
  }
}
  
 
/******************************
 * code de la tâche 1
 * ****************************
 */
void vTask1( void *pvParameters )
{
  TickType_t xLastWakeTime;
  int valueToSend=1;
  int status;
  
  Serial.printf("task1 / core %d started\n", xPortGetCoreID());

  for (;;) {
    xLastWakeTime = xTaskGetTickCount();
    
    // génération périodique 
    valueToSend *= 2;
    status = xQueueSendToBack( xQueue, &valueToSend, 0 );
    if( status == pdPASS ) {
      Serial.printf("task1: a envoyé %d\n", valueToSend);
      alternate(oscillo1, half_period_ms);    
    }
    else
      Serial.printf("task1: PAS PU ENVOYER %d\n",  valueToSend);

     vTaskDelayUntil( &xLastWakeTime, pdMS_TO_TICKS( 500 ) );
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
  int receivedValue;
  int status;
  
  Serial.printf("task2 / core %d started\n", xPortGetCoreID());
  
  // boucle infinie
  for (;;) {

    Serial.printf("task2: %d données en attente\n", uxQueueMessagesWaiting( xQueue ));

    status = xQueueReceive( xQueue, &receivedValue, pdMS_TO_TICKS( 100 ) );
    if( status == pdPASS ) {
      Serial.printf("task2: reçu %d\n", receivedValue);
      // simule du boulot     
      alternate(oscillo2, half_period_ms); 
    }
    else
      Serial.printf("task2: RIEN EU A LIRE\n");
    
     
    vTaskDelay( pdMS_TO_TICKS( 10 ) );     
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

  xQueue = xQueueCreate( TAILLE_MAX, sizeof( int ) );
  
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
