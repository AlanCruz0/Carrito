#include <Wire.h> 

byte I2C;
const int Trigger = 4;
const int Echo = 5;

void setup(){
    Wire.begin(1);
    Serial.begin(115200);
    Wire.onRequest(eventoRecibe);
}

void loop(){
    delay(1000);
}

void eventoRecibe ()
{
    I2C = leerDistancia(Trigger, Echo);
    Serial.println(I2C);
    Wire.write(I2C);
}

byte leerDistancia(int triggerPin, int echoPin)
{
    pinMode(triggerPin, OUTPUT);
    digitalWrite(triggerPin, LOW);
    delayMicroseconds(2);

    digitalWrite(triggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(triggerPin, LOW);
    pinMode(echoPin, INPUT);

    I2C = pulseIn(echoPin, HIGH)*0.01723;

    return I2C;
}
