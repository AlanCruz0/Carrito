#include <Wire.h>

byte I2C="20";

void setup()
{
    Wire.begin();
    Serial.begin(115200);
}

void loop()
{
    Wire.beginTransmission(1);
    Wire.write(I2C);
    Wire.endTransmission();
    Serial.println("Finalizo el envio");
    delay(1000);
}
