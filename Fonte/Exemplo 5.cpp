#include <Arduino.h>

#define LED_VERMELHO 12
#define LED_VERDE 11
#define LED_AMARELO 10
#define LED_AZUL 9

#define BOTAO_1 7
#define BOTAO_2 6

// Exemplo 5 função de indicação pelos LED's atravez de um contador
struct Botao
{
    int Pinagem;
    bool Estado_Botao;
    bool Borda_Subida;  //Identifica a ocorrencia de uma borda de subida
    bool Borda_Descida; //Identifica a ocorrencia de uma borda de descida
};

// Variaveis Globais
struct Botao Btn_1, Btn_2;
int Contador;

// Funções Auxiliares
struct Botao Atualiza_Estado_Botao(struct Botao Btn)
{
    // Atualiza propriedades do botão 1
    Btn.Borda_Descida = false;
    Btn.Borda_Subida = false;

    if (digitalRead(Btn.Pinagem) != Btn.Estado_Botao)
    {
        if (Btn.Estado_Botao == true)
        {
            Btn.Borda_Descida = true;
        }
        else
        {
            Btn.Borda_Subida = true;
        }
        Btn.Estado_Botao = digitalRead(Btn.Pinagem);
    }

    return Btn;
}

void Indicador_LEDs(int Valor)
{
    switch (Valor)
    {
    case 1:
        digitalWrite(LED_VERMELHO, true);
        digitalWrite(LED_VERDE, false);
        digitalWrite(LED_AMARELO, false);
        digitalWrite(LED_AZUL, false);
        break;
    case 2:
        digitalWrite(LED_VERMELHO, false);
        digitalWrite(LED_VERDE, true);
        digitalWrite(LED_AMARELO, false);
        digitalWrite(LED_AZUL, false);
        break;
    case 3:
        digitalWrite(LED_VERMELHO, false);
        digitalWrite(LED_VERDE, false);
        digitalWrite(LED_AMARELO, true);
        digitalWrite(LED_AZUL, false);
        break;
    case 4:
        digitalWrite(LED_VERMELHO, false);
        digitalWrite(LED_VERDE, false);
        digitalWrite(LED_AMARELO, false);
        digitalWrite(LED_AZUL, true);
        break;
    case 5:
        digitalWrite(LED_VERMELHO, true);
        digitalWrite(LED_VERDE, true);
        digitalWrite(LED_AMARELO, true);
        digitalWrite(LED_AZUL, true);
        break;

    default:
        if (Valor > 5)
        {
            digitalWrite(LED_VERMELHO, true);
            digitalWrite(LED_VERDE, true);
            digitalWrite(LED_AMARELO, true);
            digitalWrite(LED_AZUL, true);
        }
        else
        {
            digitalWrite(LED_VERMELHO, false);
            digitalWrite(LED_VERDE, false);
            digitalWrite(LED_AMARELO, false);
            digitalWrite(LED_AZUL, false);
        }
        break;
    }
}

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
    Btn_1.Pinagem = BOTAO_1;
    Btn_2.Pinagem = BOTAO_2;

    // Inicialização da porta serial
    Serial.begin(9600);

    // Inicializa as demais variaveis
    Contador = 0;

    Serial.println("Fim de inicializacao");
}

void loop()
{
    // Exemplo 5
    Btn_1 = Atualiza_Estado_Botao(Btn_1);
    Btn_2 = Atualiza_Estado_Botao(Btn_2);

    if (Btn_1.Borda_Descida == true)
    {
        Contador++;
        Serial.print("Contador: ");
        Serial.println(Contador);
    }
    
    if (Btn_2.Borda_Descida == true)
    {
        Contador--;
        Serial.print("Contador: ");
        Serial.println(Contador);
    }

    Indicador_LEDs(Contador);
}
