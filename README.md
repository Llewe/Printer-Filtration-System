# printer-filtration-system
This is a project to monitor and control the air filtration system for a 3D printer. The system can control the speed of
multiple fans through Home Assistant. More features will be added as the project progresses ;).

## Secrets
There is a secret file with all the passwords and usernames. This is more of a placeholder until I added a process to 
configure the secrets while setting up the NodeMCU.
```cpp
#define WIFI_SSID ""
#define WIFI_PASSWORD ""

#define MQTT_SERVER "192.x.x.x"
#define MQTT_PORT 1883
#define MQTT_USER ""
#define MQTT_PASSWORD ""
```