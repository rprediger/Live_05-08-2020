#define LED_VERMELHO 12
#define LED_VERDE 11
#define LED_AMARELO 10
#define LED_AZUL 9

#define BOTAO_1 7
#define BOTAO_2 6

#define PIN_SENSOR_ANALOGICO A0
#define NUM_DADOS_LIDOS 7

// Exemplo 6 ler um sensor, fazer a media movel e mostrar nos LED´s
struct Botao
{
    int Pinagem;
    bool Estado_Botao;
    bool Borda_Subida;  //Identifica a ocorrencia de uma borda de subida
    bool Borda_Descida; //Identifica a ocorrencia de uma borda de descida
};

struct Vetor_Circular
{
    int Dados[NUM_DADOS_LIDOS];
    int P_Prox_Dado;
};

// Variaveis Globais
struct Botao Btn_1, Btn_2;
struct Vetor_Circular Buffer_Dados;

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

// função que adiciona os dados no buffer
struct Vetor_Circular Adicionar_Dado_Buffer_Circular(Vetor_Circular Buffer, int Dado)
{
    Buffer.Dados[Buffer.P_Prox_Dado] = Dado;
    Buffer.P_Prox_Dado++;
    if (Buffer.P_Prox_Dado >= NUM_DADOS_LIDOS)
    {
        Buffer.P_Prox_Dado = 0;
    }
    return Buffer;
}

// Função que calcula a média movel
int Media_Movel_Buffer_Circular(Vetor_Circular Buffer)
{
    int Acumulador = 0;
    for (int contador = 0; contador < NUM_DADOS_LIDOS; contador++)
    {
        Acumulador += Buffer.Dados[contador];
    }
    return (Acumulador / NUM_DADOS_LIDOS);
}

// Função que manipula os LED's
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
    Buffer_Dados.P_Prox_Dado = 0;

    Serial.println("Fim de inicializacao");
}

void loop()
{
    // Atualiza os botoes
    Btn_1 = Atualiza_Estado_Botao(Btn_1);
    Btn_2 = Atualiza_Estado_Botao(Btn_2);

    // Faz uma nova leitura e adiciona no buffer
    if (Btn_1.Borda_Descida == true)
    {
        int Leitura = analogRead(PIN_SENSOR_ANALOGICO);
        Buffer_Dados = Adicionar_Dado_Buffer_Circular(Buffer_Dados, Leitura);
        Serial.print("Valor sensor: ");
        Serial.println(Leitura);
    }

    // Atualiza a saida com as ultimas leituras
    if (Btn_2.Borda_Descida == true)
    {
        // Calcula a media movel
        int Media_Movel = Media_Movel_Buffer_Circular(Buffer_Dados);
        // Calcula a tensão aproximada
        int Tensao_Aproximada = map(Media_Movel, 0, 1023, 0, 5);
        // Indica a tensão atravez dos LED´s
        Indicador_LEDs(Tensao_Aproximada);

        // Apresenta os dados para o usuario
        Serial.println("Dados no Buffer: ");
        for (int contador = 0; contador < NUM_DADOS_LIDOS; contador++)
        {
            Serial.print("[");
            Serial.print(Buffer_Dados.Dados[contador]);
            Serial.print("] ");
        }
        Serial.println();
        Serial.print("Media Movel: ");
        Serial.println(Media_Movel);
        Serial.print("Tensao Aproximada: ");
        Serial.println(Tensao_Aproximada);
    }
}
