// Programme IF4_TP_S2_Q21d

// Encoder
int S1A = 25;
int S1B = 27;
int S2A = 26;
int S2B = 14;

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

// Interruption Prototypes;
void IRAM_ATTR interruptWheel1();

SemaphoreHandle_t xBinarySemaphore = NULL;

void IRAM_ATTR interruptWheel2()
{
  BaseType_t xHigherPriorityTaskWoken = pdFALSE;

  Serial.println("interruptWheel2()");
  xSemaphoreGiveFromISR( xBinarySemaphore, &xHigherPriorityTaskWoken );
  if( xHigherPriorityTaskWoken != pdFALSE )
    portYIELD_FROM_ISR();
}


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
  
  Serial.printf("vTask1 / core %d started\n", xPortGetCoreID());

  for (;;) {
    xLastWakeTime = xTaskGetTickCount();
    
    // simule du boulot périodique   
    alternate(oscillo1, half_period_ms);    
    vTaskDelayUntil( &xLastWakeTime, pdMS_TO_TICKS( 100 ) );
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
  Serial.printf("vTask2 / core %d started\n", xPortGetCoreID());
  
  // boucle infinie
  for (;;) {
    
    // attend l'interruption
    xSemaphoreTake( xBinarySemaphore, portMAX_DELAY );
    Serial.printf("vTask2 called\n");
    
    // simule du boulot     
    alternate(oscillo2, half_period_ms); 
    
    
  /*  Serial.printf("vTask2 travaille de son côté\n", xPortGetCoreID());
    delay(10);
    
    xSemaphoreTake(xMutex, portMAX_DELAY);
    Serial.printf("vTask2 a verrouillé le mutex\n", xPortGetCoreID());

    // simule du boulot
    Serial.printf("vTask2 travaille sur la ressource partagée\n", xPortGetCoreID());
    alternate(oscillo2, 10);
    Serial.printf("vTask2 a fini de travailler sur la ressource partagée\n", xPortGetCoreID());
    
    Serial.printf("vTask2 déverrouille le mutex\n", xPortGetCoreID());
    xSemaphoreGive(xMutex);
 
    */
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
  digitalWrite(oscillo2, LOW); 

  xBinarySemaphore = xSemaphoreCreateBinary();
  
  pinMode(S2A , INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(S2A), interruptWheel2, CHANGE);
 
  
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
