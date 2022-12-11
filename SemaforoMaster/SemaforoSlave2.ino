#include <Wire.h>                               

int r = 10;
int a = 7;
int v = 4;

byte I2C;                                 

void setup() 
{
    pinMode(r, OUTPUT);   
    pinMode(a, OUTPUT);
    pinMode(v, OUTPUT);
    digitalWrite(r, HIGH);                 
    Wire.begin(2);                                
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