#include "log_server.h"
#include "custom_log.h"
#include "ntp_client.h"
#include "functions.h"
#include "config.h"
#include "P1.h"

void setup() {
  Serial.begin(115200);
  REMOTE_LOG_INFO("Start ESP32");
  ChangeNeoPixels_info();
  infoLedFadeIn(white, 500); // Smooth startup indication
  serialWait();
  functions_setup();
  delay(200);

  ESP_Server_setup();
  initializeLogServer();
  initializeNTP();
  ota_setup();
  P1_setup();
}

void loop() {
  ethernet_loop();
  P1_loop();
  yield(); // Prevent watchdog reset - allows ESP32 to handle WiFi/background tasks
}
