#pragma once 
#include <Arduino.h> 
/*

  LED RGB é um dispositivo de feedback visual que indica os estados de operação do alimentador. 
  São eles:
    - Aguardando: em espera da proximação de uma entidade
    - Detectado: breve momento em que se detecta o animal
    - Alimentando: logo após Detectado, dispensa comida no alimentador
    - Comendo: enquanto ainda observar o animal após alimentá-lo 
  Cada estado emite uma cor diferente a fim de distingui-los 

    Cada LED é um vetor de três números inteiros, guardando os número dos pinos conectados no Arduino na ordem RGB:
    Cauda RED = led[0], cauda GREEN = led[1], cauda BLUE = led[2]
*/

#define LED1_R 11
#define LED1_G 6
#define LED1_B 5

// Cores para estados do led
const byte corAguardando[3] = {60, 120, 240}; // Azul
const byte corDetectado[3] = {255, 255, 0}; // Amarelo
const byte corAlimentando[3] = {124, 255, 0}; // Verde
const byte corComendo[3] = {255, 12, 183}; // Roxo

const byte corAlerta[3] = {255, 100, 0}; // Laranja
const byte corErro[3] = {255, 0 , 0}; // Vermelho

/// @brief altera a cor de um LED
/// @param pinosLed pinos do LED na ordem RGB
/// @param cor vetor de inteiros da cor no padrão RGB: {[0,255], [0,255], [0,255]}
void writeCorLed(const byte pinosLed[3], const byte cor[3]) {
  analogWrite(pinosLed[0], cor[0]);
  analogWrite(pinosLed[1], cor[1]);
  analogWrite(pinosLed[2], cor[2]);
}

/// @brief calcula o MDC (máximo divisor comum) entre dois números por algoritmo de Euclides
/// @param m numero 1
/// @param n numero 2
/// @return MDC
int mdc(int m, int n){ 
  int resto;

  resto = m % n;
  while (resto != 0) {
	  m = n;
	  n = resto;
	  resto = m % n;
  }

    return n;
}

/// @brief aumenta ou diminui a intensidade do brilho do LED RGB e gera saída de texto informativo
/// @param pinosLed pinos do LED na ordem RGB
/// @param cor vetor de inteiros da cor (com divisor comum maior que 1) no padrão RGB: {[0,255], [0,255], [0,255]}
/// @param intensidade intensidade do brilho do LED 
/// @details varia os valores de 0 à cor correspondente. Deve ser utilizado um loop externo para gerar o efeito visual desejado
/// @pre os valores da cor em RGB não devem ser primos entre si (divisor comum deve ser maior que 1)
/// @return false se os valores da cor são primos entre si; true se possuem divisor comum
bool pulsaLed(const byte pinosLed[3], const byte cor[3], int &intensidade){ 
  static bool subindo = false;

  int divisor = mdc(mdc(cor[0], cor[1]), cor[2]);
  if (divisor == 1){
    return false;
  }
  int passoR = cor[0]/divisor;
  int passoG = cor[1]/divisor;
  int passoB = cor[2]/divisor;

  if (subindo){
    intensidade++;

    if (intensidade >= divisor ) {
      subindo = false;
    }

  } else {
    intensidade--;
    if (intensidade <= 0){
      subindo = true;
    }
  }

  int redAtual = passoR * intensidade;
  int greenAtual = passoG * intensidade;
  int blueAtual = passoB * intensidade;

  analogWrite(pinosLed[0], redAtual);
  analogWrite(pinosLed[1], greenAtual);
  analogWrite(pinosLed[2], blueAtual);

  Serial.print("RGB: {");
  Serial.print(redAtual);
  Serial.print(", ");
  Serial.print(greenAtual);
  Serial.print(", ");
  Serial.print(blueAtual);
  Serial.println("}");

  return true;
}

