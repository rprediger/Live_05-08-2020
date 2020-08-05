#define LED_VERMELHO   12
#define LED_VERDE      11
#define LED_AMARELO    10
#define LED_AZUL       9

#define BOTAO_1     7
#define BOTAO_2     6

// Exemplo 1 - acionar led com btn precionado

void setup()
{
  // Inicialização das saidas
  pinMode(LED_VERMELHO, OUTPUT);
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_AMARELO, OUTPUT);
  pinMode(LED_AZUL, OUTPUT);
  
  // Inicialização das entradas
  pinMode(BOTAO_1, INPUT);
  pinMode(BOTAO_2, INPUT);

  // Inicialização da porta serial
  Serial.begin(9600);

  Serial.println("Fim de inicializacao");
}

void loop()
{
  // Exemplo 1
  if (digitalRead(BOTAO_1) == true)
  {
    digitalWrite(LED_VERMELHO, true);
  }
  else
  {
    digitalWrite(LED_VERMELHO, false);
  }

  if (digitalRead(BOTAO_2) == true)
  {
    digitalWrite(LED_VERDE, false);
  }
  
}
