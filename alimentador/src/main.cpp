#include <Arduino.h>
#include <Servo.h>
#include "buzzer.hpp"
#include "led.hpp"
#include "notas.hpp"
#include "sensor.hpp"

const byte led1[] = {LED1_R, LED1_G, LED1_B};

void setup()
{
  pinMode(TRIG_PIN, OUTPUT); // pino TRIG do sensor (gatilho de emissão da onda sonora)
  pinMode(ECHO_PIN, INPUT); // pino ECHO do sensor (sinalizador de estado)
  pinMode(BUZZER_PIN, OUTPUT);

  for(byte pin : led1){ // Seta pinos do led
    pinMode(pin, OUTPUT);
  }
  
  Serial.begin(9600); // Inicializa comunicação serial a 9600bps
  Serial.println("Sistema iniciado"); 
  
  checaProximidadeInicial(led1);

  delay(200);
}


void loop()
{
  checaProximidade(led1);

  delay(100);
}