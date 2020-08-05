#define LED_VERMELHO   12
#define LED_VERDE      11
#define LED_AMARELO    10
#define LED_AZUL       9

#define BOTAO_1     7
#define BOTAO_2     6

// Exemplo 4 criar função para manipular os botões

struct Botao {
    int Pinagem;
    bool Estado_Botao;
    bool Borda_Subida;  //Identifica a ocorrencia de uma borda de subida
    bool Borda_Descida; //Identifica a ocorrencia de uma borda de descida
};

// Variaveis Globais
struct Botao Btn_1, Btn_2;

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

  Serial.println("Fim de inicializacao");
}

void loop()
{
    // Exemplo 4
    Btn_1 = Atualiza_Estado_Botao(Btn_1);
    Btn_2 = Atualiza_Estado_Botao(Btn_2);

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
