#pragma once
#include <Arduino.h>
#include "led.hpp"
#include "buzzer.hpp"

#define TRIG_PIN 8
#define ECHO_PIN 7 
#define VELOCIDADE_SOM 0.0343 // Velocidade média do som no ar em cm/microssegundo 
#define EPSILON 0.4 // Tolerância para evitar que o sistema reacione
#define LIMITE_ATIVACAO 30 // Quão próximo (em cm) algo ou alguém deve estar para o sistema ser acionado 

/// @brief gera um ciclo de emissão de sinal do sensor e calcula a distância do objeto mais próximo
/// @return distância do objeto mais próximo ao sensor
float sensorCiclo(void){
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  
  digitalWrite(TRIG_PIN, HIGH); // Emite sinal 
  delayMicroseconds(10);
  
  digitalWrite(TRIG_PIN, LOW);
  float duracao = pulseIn(ECHO_PIN, HIGH); // Guarda o tempo que levou para o sinal ir e voltar
  
  return (duracao * VELOCIDADE_SOM)/2;
}

void geraRotina(const byte led[]){
  writeCorLed(led, corDetectado);
  Serial.println("Animal detectado!");
  tocaMelodia(1);
  delay(400);
  
  writeCorLed(led, corAlimentando);
  Serial.println("Despejando alimento...");
  delay(2000);
  
  writeCorLed(led, corComendo);
  Serial.println("Comendo/aguardando a retirada");

  delay(4000);
}

void mensagemAguardando(float distancia){
  if (distancia > 334.0){
    Serial.println("Fora de alcance");
  } else {
    Serial.print("Distancia: ");
    Serial.print(distancia, 0);
    Serial.println("cm");
  }
}

/// @brief checa se há um objeto dentro do limite de ativação e gera a rotina (mudança de cores do LED, melodia do buzzer e saída de texto)
/// @param led pinos do led na ordem RGB
void checaProximidade(const byte led[]){
  static bool fora = false;
  static int intensidade = 100;
  float distancia = sensorCiclo();
 
  if (distancia > 0 && distancia <= LIMITE_ATIVACAO && fora){ // Se menor ou igual a 30cm, aciona o sistema
    geraRotina(led);
    
    distancia = sensorCiclo();
    while (distancia < LIMITE_ATIVACAO + EPSILON){
    distancia = sensorCiclo();
    delay(100);
  }
    fora = false;
  }
  
  if (distancia > LIMITE_ATIVACAO + EPSILON){ 
    fora = true; 
    Serial.print("milis: ");
    Serial.println(millis());
    pulsaLed(led, corAguardando, intensidade);
    mensagemAguardando(distancia);
  }
}


/// @brief gera uma mensagem de aviso caso haja objeto próximo na inicialização do programa e muda a cor do LED para laranja
/// @param led vetor com os pinos do led na ordem RGB
void checaProximidadeInicial(const byte led[]){
  float distanciaInicial = sensorCiclo();
  bool saiu = false;

  if(distanciaInicial <= LIMITE_ATIVACAO){
    Serial.println("Objeto proximo detectado. Retire para concluir inicializacao");
    writeCorLed(led, corAlerta);

    while(!saiu){
      distanciaInicial = sensorCiclo();
      
      if(distanciaInicial > LIMITE_ATIVACAO + EPSILON){
        saiu = true;
        writeCorLed(led, corAguardando);
      }
    }
  }
}