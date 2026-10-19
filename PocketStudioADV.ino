// Pocket Studio ADV v0.2 - groovebox inicial para M5Stack Cardputer ADV
// Arduino IDE + biblioteca M5Cardputer (M5Unified/M5GFX como dependencias).
#include <M5Cardputer.h>
#include "Config.h"
#include "InputManager.h"
#include "AudioEngine.h"
#include "UserInterface.h"

AudioEngine audio;
InputManager input;
UserInterface ui(audio);

void setup() {
  Serial.begin(115200);
  auto cfg = M5.config();
  M5Cardputer.begin(cfg, true);
  delay(100);

  audio.begin();
  ui.begin();

  Serial.println();
  Serial.println("Pocket Studio ADV v" PS_VERSION_STR);
  Serial.printf("Chip: %s | CPU: %u MHz\n", ESP.getChipModel(), (unsigned)getCpuFrequencyMhz());
  Serial.printf("Heap livre: %u bytes | PSRAM: %s\n",
                (unsigned)ESP.getFreeHeap(), psramFound() ? "sim" : "nao");
  Serial.printf("Audio speaker enabled: %s\n", audio.ready() ? "sim" : "nao");
}

void loop() {
  M5Cardputer.update();

  KeyEvent ev;
  if (input.poll(ev)) ui.handle(ev);

  audio.update();
  ui.update(millis());
  delay(1);
}
