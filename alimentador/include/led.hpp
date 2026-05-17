#pragma once 

/*

  LED RGB é um dispositivo de feedback visual que indica os estados de operação do alimentador. 
  São eles:
    - Aguardando: em espera da proximação de uma entidade
    - Detectado: breve momento em que se detecta o animal
    - Alimentando: logo após Detectado, dispensa comida no alimentador
    - Comendo: enquanto ainda observar o animal após alimentá-lo 
    
    + Ideias (para lembrar): recarga? (tempo de espera mínimo para ser acionado novamente), vazio? (falta de alimento; não pode ser acionado),
    Comendo -> tempo mínimo de x segundos sem detecção para passar do estado?

*/

#define LED1_R 11
#define LED1_G 10
#define LED1_B 9

// Cores para estados do led
const byte corAguardando[3] = {61, 210, 242};
const byte corDetectado[3] = {255, 255, 0};
const byte corAlimentando[3] = {124, 255, 0};
const byte corComendo[3] = {255, 12, 183};

const byte corErro[3] = {255, 0 , 0};

/// @brief altera a cor de um LED
/// @param pinosLed vetor dos pinos do LED na ordem RGB
/// @param cor vetor de inteiros da cor no padrão RGB {0-255, 0-255, 0-255}
void writeCorLed(const byte pinosLed[], const byte cor[]) {
  analogWrite(pinosLed[0], cor[0]);
  analogWrite(pinosLed[1], cor[1]);
  analogWrite(pinosLed[2], cor[2]);
}