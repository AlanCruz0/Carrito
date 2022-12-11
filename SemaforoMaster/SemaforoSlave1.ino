#include <Wire.h>                               

int v = 4;
int a = 8;
int r = 13;

byte I2C;                                 

void setup() 
{
    pinMode(v, OUTPUT);
    pinMode(a, OUTPUT);
    pinMode(r, OUTPUT);
    digitalWrite(r, HIGH);
    Wire.begin(1);                                
    Wire.onReceive(receiveEvent);

}

void loop() 
{
    delay(100);
}

void receiveEvent(int Press)
{
    I2C = Wire.read();                      
    if (I2C == 1)
    {
        inter();
    }
    else if (I2C == 0)
    {
        semaforo();
    }
}

void inter()
{
    for (int i = 0; i < 4; i++)
    {
        digitalWrite(r, HIGH);
        digitalWrite(a, HIGH);
        digitalWrite(v, HIGH);
        delay(2500);
        digitalWrite(r, LOW);
        digitalWrite(a, LOW);
        digitalWrite(v, LOW);
        delay(2500);
    }
}

void semaforo()
{
    for (int i = 0; i < 4; i++)
    {
        digitalWrite(v, HIGH);
        delay(3500);
        digitalWrite(v, LOW);
        digitalWrite(a, HIGH);
        delay(3500);
        digitalWrite(a, LOW);
        digitalWrite(r, HIGH);
        delay(3500);
        digitalWrite(r, LOW);
        delay(3500);
    }
}
