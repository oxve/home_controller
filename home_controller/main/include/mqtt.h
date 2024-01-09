#ifndef __MQTT_H__
#define __MQTT_H__

#include "mqtt_client.h"

#define QOS_AT_MOST_ONCE 0
#define QOS_AT_LEAST_ONCE 1
#define QOS_EXACTLY_ONCE 2

void mqtt_connect(void);

void mqtt_publish(const char* topic, const char* data, int qos);

// void mqtt_subscribe(const char* topic, int qos, void (*callback)(const char*));

#endif
