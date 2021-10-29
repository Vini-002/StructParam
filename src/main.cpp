#include <Arduino.h>

#include <FreeRTOS.h>
#include <FreeRTOS/task.h>

/* Struct of Parameters to blink */
typedef struct BlinkData
{
  const char *name;    // Task name
  int pin;             // LED pin number
  int offtime;         // OFF time of the LED
  TaskHandle_t handle; // Task Handle
} BlinkData;           // Struct name

/* Parameters to blink: {ID, pin, offtime, repeats, TaskHandle} */
BlinkData blinks[] = {
  {"Blink 1", 27, 1200, NULL},
  {"Blink 2", 14, 800, NULL},
  {"Blink 3", 12, 600, NULL},
  {"Blink 4", 13, 400, NULL}
};

/* Prototype */
void vTaskBlink(void *vParameters);

void setup() {
  Serial.begin(115200);

  for (int i = 0; i < 4; i++)
  {
    vTaskDelay(200);
    xTaskCreate(vTaskBlink, blinks[i].name, configMINIMAL_STACK_SIZE, (void *) &blinks[i], 1, &blinks[i].handle);
  }
}

void loop() {
  vTaskDelay(1000);
}

void vTaskBlink(void *pvParameters)
{
  BlinkData *data = (BlinkData *) pvParameters;

  /* Debugging information */
  Serial.println(data->name);
  Serial.println(data->offtime);

  pinMode(data->pin, OUTPUT);
  for (;;)
  {
    digitalWrite(data->pin, HIGH);
    vTaskDelay(pdMS_TO_TICKS(200));
    digitalWrite(data->pin, LOW);
    vTaskDelay(pdMS_TO_TICKS(data->offtime));
  }
}