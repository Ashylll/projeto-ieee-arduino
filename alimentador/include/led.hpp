#pragma once 

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
const byte corAguardando[3] = {61, 210, 242}; // Azul
const byte corDetectado[3] = {255, 255, 0}; // Amarelo
const byte corAlimentando[3] = {124, 255, 0}; // Verde
const byte corComendo[3] = {255, 12, 183}; // Roxo

const byte corAlerta[3] = {255, 100, 0}; // Laranja
const byte corErro[3] = {255, 0 , 0}; // Vermelho

/// @brief altera a cor de um LED
/// @param pinosLed pinos do LED na ordem RGB
/// @param cor vetor de inteiros da cor no padrão RGB {0-255, 0-255, 0-255}
void writeCorLed(const byte pinosLed[], const byte cor[]) {
  analogWrite(pinosLed[0], cor[0]);
  analogWrite(pinosLed[1], cor[1]);
  analogWrite(pinosLed[2], cor[2]);
}