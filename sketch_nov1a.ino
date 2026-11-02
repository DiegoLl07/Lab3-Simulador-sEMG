#include "semg.h"   // SEMG[], N_SEMG, FS_SEMG

#define PIN_DAC 25  // GPIO25 = DAC1

uint32_t indice = 0;
uint32_t proximo_us;
uint32_t acumulador = 0;

void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.printf("Chip: %s | N_SEMG = %u | FS_SEMG = %u Hz\n", ESP.getChipModel(), (unsigned)N_SEMG, (unsigned)FS_SEMG);
                
  proximo_us = micros();
}

void loop() {
  if ((int32_t)(micros() - proximo_us) >= 0) {

    dacWrite(PIN_DAC, SEMG[indice]);

    indice++;
    if (indice >= N_SEMG) indice = 0;

    acumulador += 1000000UL;
    proximo_us += acumulador / FS_SEMG;
    acumulador %= FS_SEMG;
  }
}