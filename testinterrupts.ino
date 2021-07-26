#include <Arduino.h>

#define PIN_KEY1                    36             // BUTTON_REC_ID, KEY 1 
#define PIN_KEY2                    13             // KEY 2
#define PIN_KEY3                    19             // KEY 3  //creates interrupt
#define PIN_KEY4                    23             // PIN_PLAY KEY 4  
#define PIN_KEY5                    18             // PIN_VOL_UP KEY 5  
#define PIN_KEY6                    5              // PIN_VOL_DOWN KEY 6  //creates interrupt


const byte interruptPin = PIN_KEY5 ;
 
unsigned long lastDetection = 0;
unsigned long debounceTime = 250;
 
SemaphoreHandle_t syncSemaphore;
 
void IRAM_ATTR handleInterrupt() {
    xSemaphoreGiveFromISR(syncSemaphore, NULL);
} 




void setup() {
  Serial.begin(115200);
 
  syncSemaphore = xSemaphoreCreateBinary();
 
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), handleInterrupt, FALLING);
}

void loop() {
  xSemaphoreTake(syncSemaphore, portMAX_DELAY);
 
  if(millis() - lastDetection > debounceTime){
 
    Serial.println("Shake detected");
    lastDetection = millis();
  }
}
