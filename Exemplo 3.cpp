#include <Arduino.h>

#define LED_VERMELHO   12
#define LED_VERDE      11
#define LED_AMARELO    10
#define LED_AZUL       9

#define BOTAO_1     7
#define BOTAO_2     6

// Exemplo 3 utilizar estruturas para refazer o exemplo anterior

struct Botao {
    bool Estado_Botao;
    bool Borda_Subida;  //Identifica a ocorrencia de uma borda de subida
    bool Borda_Descida; //Identifica a ocorrencia de uma borda de descida
};

// Variaveis Globais
struct Botao Btn_1, Btn_2;

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
    // Exemplo 3
    // Atualiza propriedades do botão 1
    Btn_1.Borda_Descida = false;
    Btn_1.Borda_Subida = false;

    if (digitalRead(BOTAO_1) != Btn_1.Estado_Botao)
    {
        if (Btn_1.Estado_Botao == true)
        {
            Btn_1.Borda_Descida = true;
        }
        else
        {
            Btn_1.Borda_Subida = true;
        }
        Btn_1.Estado_Botao = digitalRead(BOTAO_1);
    }

    if (Btn_1.Borda_Descida == true)
    {
        // Muda o estado do LED
        if (digitalRead(LED_VERMELHO) == true)
        {
            digitalWrite(LED_VERMELHO, false);
            Serial.println("LED Vermelho desligado");
        }
        else
        {
            digitalWrite(LED_VERMELHO, true);
            Serial.println("LED Vermelho ligado");
        }
    }
    
}