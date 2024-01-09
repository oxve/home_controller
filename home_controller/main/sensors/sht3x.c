#include "sensors.h"

#include "../include/mqtt.h"
#include <sht3x.h>
#include <string.h>

#define SHT3X_ADDR 0x44
#define I2C_MASTER_SCL 22
#define I2C_MASTER_SDA 21

static sht3x_t dev;

static const char measurement_json[] = R"({
  "data": %.2f,
  "unit": "%s"
})";

void strip_whitespace(char* target) {
  char *p, *q;
  p = q = target;
  while (*p != '\0') {
    while (*q == ' ' || *q == '\n') q++;
    *p = *q;
    p++; q++;
  }
}

void sht3x_measure_task(void *pvParameters) {
  float temperature;
  float humidity;
  char payload[128];
  char topic[32];

  TickType_t last_wakeup = xTaskGetTickCount();

  // Sensor loop. In each iteration do one measurement and publish one event each for temp and humidity.
  while (1) {
    ESP_ERROR_CHECK(sht3x_measure(&dev, &temperature, &humidity));
    // printf("SHT3x Sensor: %.2f °C, %.2f %%\n", temperature, humidity);


    // TODO: Get location from device config.
    sprintf(topic, "sensor/%s", "crawlspace");

    sprintf(payload, measurement_json, temperature, "C");
    mqtt_publish(topic, payload, 0);

    sprintf(payload, measurement_json, humidity, "%");
    mqtt_publish(topic, payload, 0);

    // wait until 5 seconds are over
    vTaskDelayUntil(&last_wakeup, pdMS_TO_TICKS(SENSOR_INTERVAL_MS));
  }
}

void sensors_sht3x_init(void) {
  ESP_ERROR_CHECK(i2cdev_init());
  memset(&dev, 0, sizeof(sht3x_t));

  ESP_ERROR_CHECK(sht3x_init_desc(&dev, SHT3X_ADDR, 0, I2C_MASTER_SDA, I2C_MASTER_SCL));
  ESP_ERROR_CHECK(sht3x_init(&dev));

  xTaskCreatePinnedToCore(sht3x_measure_task, "sh301x_test", configMINIMAL_STACK_SIZE * 8, NULL, 5, NULL, APP_CPU_NUM);
}
