#pragma once 
#include "notas.hpp"

/*

  Buzzer é um dispositivo que recebe OUTPUT do Arduino, emitindo uma sequência de frequências quando demandado
  Sempre que há detecção de entidade próxima e o alimento é despejado, o buzzer deve ser acionado 

  Composição da melodia:
    A melodia é um vetor de inteiros e cada nota é uma frequência, sendo o próximo valor do vetor seu tempo
    1 refere-se à semibreve, 2 à mínima, 4 à semínima, 8 à colcheia e assim por diante
    O sinal negativo representa o meio tempo (nota pontuada)

*/

#define BUZZER_PIN 4
#define TAMANHO_MELODIA(m) (sizeof(m) / sizeof(m[0]) / 2)

static int melJigglypuff[] = {NOTA_D5,-4, NOTA_A5,8, NOTA_FS5,8, NOTA_D5,8, NOTA_E5,-4};
static int melDoisBeeps[] = {NOTA_A5,16, NOTA_PAUSA,16, NOTA_A5,16, NOTA_PAUSA,16};
static int melSucesso[] = {NOTA_C5,16, NOTA_D5,16, NOTA_E5,16, NOTA_F5,8, NOTA_PAUSA,16, NOTA_F5,16, NOTA_F5,4};

/// @brief comanda o buzzer a tocar certa melodia
/// @param melodia vetor de frequências e seus respectivos tempos
/// @param numNotas número de notas totais na melodia 
/// @param tempo bpm da melodia
void tocaMelodia(int melodia[], int numNotas, int tempo){
  int semibreve = (60000 * 4) / tempo;
  int divisor = 0, notaDuracao = 0;
  for (int notaAtual = 0; notaAtual < numNotas * 2; notaAtual += 2) {

    divisor = melodia[notaAtual + 1];
    if (divisor > 0) { 
      notaDuracao = (semibreve) / divisor;
    } else if (divisor < 0) {
      notaDuracao = (semibreve) / abs(divisor);
      notaDuracao *= 1.5; 
    }

    tone(BUZZER_PIN, melodia[notaAtual], notaDuracao * 0.9);
    delay(notaDuracao);
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
/// @param numeroMusica número inteiro positivo que representa a melodia escolhida
void tocaMelodia(byte numeroMusica){
  switch (numeroMusica){
    case 1: tocaMelodia(melJigglypuff, TAMANHO_MELODIA(melJigglypuff), 144); break;
    case 2: tocaMelodia(melDoisBeeps, TAMANHO_MELODIA(melDoisBeeps), 120); break;
    case 3: tocaMelodia(melSucesso, TAMANHO_MELODIA(melSucesso), 144); break;
    default: tocaMelodia(melJigglypuff, TAMANHO_MELODIA(melJigglypuff), 144);
  }
}