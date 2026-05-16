// Variáveis para os botões e os LEDs ligados aos pinos do arduíno
int botao1 = 7;
int botao2 = 3;
int led1 = 13;
int led2 = 12;

// Configura as entradas e as saídas
void setup() {
  pinMode(botao1, INPUT); // Pinos 7 e 3 recebem energia
  pinMode(botao2, INPUT);
  pinMode(led1, OUTPUT); // Pinos 13 e 12 enviam energia
  pinMode(led2, OUTPUT);
}

// Loop para realizar infinitas leituras
void loop() {
  // Verifica se o botão está pressionado
  if (digitalRead(botao1) == HIGH) {  
    digitalWrite(led1, HIGH); // Acende a lâmpada
    digitalWrite(led2, LOW); // Apaga a outra lâmpada
  }
  
  // Lógica inversa para o segundo botão
  if (digitalRead(botao2) == HIGH) { 
    digitalWrite(led1, LOW);
    digitalWrite(led2, HIGH);
  }
  
  delay(50); // Evita "bounce" dos botões
}