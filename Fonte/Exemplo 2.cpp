#define LED_VERMELHO 12
#define LED_VERDE 11
#define LED_AMARELO 10
#define LED_AZUL 9

#define BOTAO_1 7
#define BOTAO_2 6

// Exemplo 2 - alternar led com btn

// Variaveis Globais
bool Estado_Anterior_Botao_1, Estado_Anterior_Botao_2;

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

    // Inicia as variaveis globais
    Estado_Anterior_Botao_1 = digitalRead(BOTAO_1);
    Estado_Anterior_Botao_2 = digitalRead(BOTAO_2);

    Serial.println("Fim de inicializacao");
}

void loop()
{
    // Exemplo 2
    if (digitalRead(BOTAO_1) != Estado_Anterior_Botao_1)
    {
        // Atualiza o estado do botao
        Estado_Anterior_Botao_1 = digitalRead(BOTAO_1);

        if (digitalRead(BOTAO_1) == true)
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
}
