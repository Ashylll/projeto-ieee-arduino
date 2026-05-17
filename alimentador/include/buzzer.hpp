#pragma once 
#include "notas.hpp"

/*

  Buzzer é um dispositivo que recebe OUTPUT do Arduino, emitindo uma sequência de frequências quando demandado
  Sempre que há detecção de entidade próxima e o alimento é despejado, o buzzer deve ser acionado 

*/

#define BUZZER_PIN 4
#define TAMANHO_MELODIA(m) (sizeof(m) / sizeof(m[0]) / 2)

static int melJigglypuff[] = {D5,-4, A5,8, FS5,8, D5,8, E5,-4};
static int melDoisBeeps[] = {A5,16, 0,16, A5,16, 0,16};
static int melSucesso[] = {C5,16, D5,16, E5,16, F5,8, 0,16, F5,16, F5,4};

/// @brief comanda o buzzer a tocar certa melodia
/// @param melodia vetor de notas musicais e seus respectivos tempos
/// @param numNotas número de notas totais na melodia 
void tocaMelodia(int melodia[], int numNotas){
  int tempo = 144;
  int wholenote = (60000 * 4) / tempo;
  int divider = 0, noteDuration = 0;
  for (int thisNote = 0; thisNote < numNotas * 2; thisNote += 2) {

    divider = melodia[thisNote + 1];
    if (divider > 0) { 
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5; 
    }

    tone(BUZZER_PIN, melodia[thisNote], noteDuration * 0.9);
    delay(noteDuration);
    noTone(BUZZER_PIN);
  }
}

/// @brief comanda o buzzer a tocar uma melodia numerada do catálogo interno
///
/// - (1) Jigglypuff - curto
///
/// - (2) Dois Beeps
/// 
/// - (3) Sucesso
/// @param numeroMusica número inteiro que representa a melodia escolhida
void tocaMelodia(byte numeroMusica){
  switch (numeroMusica){
    case 1: tocaMelodia(melJigglypuff, TAMANHO_MELODIA(melJigglypuff)); break;
    case 2: tocaMelodia(melDoisBeeps, TAMANHO_MELODIA(melDoisBeeps)); break;
    case 3: tocaMelodia(melSucesso, TAMANHO_MELODIA(melSucesso)); break;
    default: tocaMelodia(melJigglypuff, TAMANHO_MELODIA(melJigglypuff));
  }
}