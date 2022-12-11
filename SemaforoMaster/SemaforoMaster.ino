#include <Wire.h> 

int v = 11;
int a = 12;
int r = 13;

String readString;                                                         
int opcion;                                            
byte I2C;          

void setup() 
{
    pinMode(v, OUTPUT);
    pinMode(a, OUTPUT);
    pinMode(r, OUTPUT);
    Wire.begin();                                                                        
    Serial.begin(9600);    
    Serial.println("ESCRIBA SEMAFORO O INTERMITENTE");
    digitalWrite(r, HIGH);
}

void loop() 
{
    while (Serial.available()) 
    {
        delay(2);                                                    
        char c = Serial.read();                                       
        readString += c;                                            
    }

    if (readString == "inter")
    {
        I2C = 1;
        opcion = 1;
    }
    else if (readString == "semaforo")
    {
        I2C = 0;
        opcion = 2; 
    }

    if (readString.length() >0)                                           
    {
        Serial.println(readString);                                         
        readString="";                                                         
    }

    switch (opcion)
    {
        case 1:
            
            inter();
            Wire.beginTransmission(1);  
            Wire.write(I2C);                                                   
            Wire.endTransmission();
            
            Wire.beginTransmission(2);                                                                         
            Wire.write(I2C);                                                  
            Wire.endTransmission();
            
            Wire.beginTransmission(3);                                                                         
            Wire.write(I2C); 
            Wire.endTransmission();
            opcion = 0;
            break;

        case 2: 

            semaforo();
            Wire.beginTransmission(1);                                                                         
            Wire.write(I2C);                                                  
            Wire.endTransmission();
            delay(2000);
            Wire.beginTransmission(2);                                                                         
            Wire.write(I2C);                                                  
            Wire.endTransmission();
            delay(2000);
            Wire.beginTransmission(3);                                                                         
            Wire.write(I2C);                                                  
            Wire.endTransmission(); 
            opcion = 0;                                                
            break;

        default:                                
            break;              
    }
}

void inter()
{
    for (int i=0; i < 4; i++)
    {
        digitalWrite(r, HIGH);
        digitalWrite(a, HIGH);
        digitalWrite(v, LOW);
        delay(500);
        digitalWrite(r, LOW);
        digitalWrite(a, LOW);
        digitalWrite(v, LOW);
        delay(500);
    }
}

void semaforo()
{
    for (int i=0; i<4; i++)
    {
        digitalWrite(v, HIGH);
        delay(500);
        digitalWrite(v, LOW);
        digitalWrite(a, HIGH);
        delay(500);
        digitalWrite(a, LOW);
        digitalWrite(r, HIGH);
        delay(500);
        digitalWrite(r, LOW);
        delay(500);
    }
}