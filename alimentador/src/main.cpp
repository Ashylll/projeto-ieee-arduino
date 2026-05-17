#include <Arduino.h>
#include "buzzer.hpp"
#include "led.hpp"
#include "notas.hpp"

// Configuração dos pinos do Arduino
#define TRIG_PIN 8
#define ECHO_PIN 7 

#define VELOCIDADE_SOM 0.0343 // Velocidade média do som no ar em cm/microssegundo 
#define EPSILON 0.4 // Tolerância para evitar que o sistema reacione
#define LIMITE_ATIVACAO 30 // Quão próximo (em cm) algo ou alguém deve estar para o sistema ser acionado 

const byte led1[] = {LED1_R, LED1_G, LED1_B};

float sensorCiclo(){
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  
  digitalWrite(TRIG_PIN, HIGH); // Emite sinal 
  delayMicroseconds(10);
  
  digitalWrite(TRIG_PIN, LOW);
  float duracao = pulseIn(ECHO_PIN, HIGH); // Guarda o tempo que levou para o sinal ir e voltar
  
  return (duracao * VELOCIDADE_SOM)/2;
}

void setup()
{
  pinMode(TRIG_PIN, OUTPUT); // pino TRIG do sensor (gatilho de emissão da onda sonora)
  pinMode(ECHO_PIN, INPUT); // pino ECHO do sensor (sinalizador de estado)
  pinMode(BUZZER_PIN, OUTPUT);

  for(byte pin : led1){
    pinMode(pin, OUTPUT);
  }
  
 
  Serial.begin(9600); // Inicializa comunicação serial a 9600bps
  Serial.println("Sistema iniciado"); 
  writeCorLed(led1, corAguardando);
  
  float distanciaInicial = sensorCiclo();
  bool saiu = false;

  if(distanciaInicial <= LIMITE_ATIVACAO){
    Serial.println("Retire-se");
    
    while(!saiu){
      distanciaInicial = sensorCiclo();
      
      if(distanciaInicial > LIMITE_ATIVACAO + EPSILON){
        saiu = true;
      }
    }
  }
  
  delay(200);
}

bool fora = false;
float distancia;
void loop()
{
  
  distancia = sensorCiclo();
 
  if (distancia > 0 && distancia <= LIMITE_ATIVACAO && fora){ // Se menor ou igual a 30cm, liga o LED
    writeCorLed(led1, corDetectado);
    Serial.println("Animal detectado!");
    tocaMelodia(1);
    delay(400);
    

    
    writeCorLed(led1, corAlimentando);
    Serial.println("Despejando alimento...");
    delay(2000);
    fora = false;
    
    writeCorLed(led1, corComendo);
    Serial.println("Comendo/aguardando a retirada");
    delay(4000);
    
  }
 
  if (distancia > LIMITE_ATIVACAO + EPSILON){ 
    fora = true; 
    writeCorLed(led1, corAguardando);
    
    if (distancia > 334.0){
    	Serial.println("Fora de alcance");
  	} else {
    	Serial.print("Distancia: ");
  		Serial.print(distancia, 0);
  		Serial.println("cm");
  	}
  }
  
  delay(100);
}