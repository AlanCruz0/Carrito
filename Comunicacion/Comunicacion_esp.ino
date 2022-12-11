#include <Wire.h>

byte distanciaValor;

void setup()
{
    Wire.begin(1);
    Serial.begin(115200);
    Wire.onReceive(receiveEvent);
}

void loop()
{
    delay(1000);
    Serial.println("Despues del delay");
}

void receiveEvent(int Press)
{
    distanciaValor = Wire.read();
    Serial.println(distanciaValor);
}
