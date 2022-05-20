/* 
 *  Projeto: Easy Light (controle de lampadas com ESP32 via MQTT com App MQTT Dash)
 *  Autores: Karin e Ricardo
 *  Data: Maio e Junho de 2021
 */
 
#include <WiFi.h> // Importa a Biblioteca WiFi
#include <PubSubClient.h> // Importa a Biblioteca PubSubClient
 
//defines:
//defines de id mqtt e tópicos para publicação e subscribe
#define TOPICO_SUBSCRIBE "EasyLight_v1"     //tópico MQTT de escuta
#define TOPICO_PUBLISH   "EasyLight_v1p"    //tópico MQTT de envio de informações para Broker
                                                   //IMPORTANTE: recomendamos fortemente alterar os nomes
                                                   //            desses tópicos. Caso contrário, há grandes
                                                   //            chances de você controlar e monitorar o NodeMCU
                                                   //            de outra pessoa.
#define ID_MQTT  "EasyLight"     //id mqtt (para identificação de sessão)
                               //IMPORTANTE: este deve ser único no broker (ou seja, 
                               //            se um client MQTT tentar entrar com o mesmo 
                               //            id de outro já conectado ao broker, o broker 
                               //            irá fechar a conexão de um deles).
                                
 
//defines - mapeamento de pinos para os módulos Reles
#define Rele1    13
#define Rele2    12
#define Rele3    14
#define Rele4    27
#define Rele5    26
#define Rele6    25
#define Rele7    33
#define Rele8    32
 
 
// WIFI
const char* SSID = "Home13564440"; // SSID / nome da rede WI-FI que deseja se conectar
const char* PASSWORD = "ricardo494"; // Senha da rede WI-FI que deseja se conectar
  
// MQTT
//const char* BROKER_MQTT = "iot.eclipse.org"; //URL do broker MQTT que se deseja utilizar
const char* BROKER_MQTT = "test.mosquitto.org";
int BROKER_PORT = 1883; // Porta do Broker MQTT
 
 
//Variáveis e objetos globais
WiFiClient espClient; // Cria o objeto espClient
PubSubClient MQTT(espClient); // Instancia o Cliente MQTT passando o objeto espClient
char EstadoSaida = '0';  //variável que armazena o estado atual da saída
  
//Prototypes
void initSerial();
void initWiFi();
void initMQTT();
void reconectWiFi(); 
void mqtt_callback(char* topic, byte* payload, unsigned int length);
void VerificaConexoesWiFIEMQTT(void);
void InitOutput(void);
 
/* 
 *  Implementações das funções
 */
void setup() 
{
    //inicializações:
    InitOutput();
    initSerial();
    initWiFi();
    initMQTT();
}
  
//Função: inicializa comunicação serial com baudrate 115200 (para fins de monitorar no terminal serial 
//        o que está acontecendo.
//Parâmetros: nenhum
//Retorno: nenhum
void initSerial() 
{
    Serial.begin(115200);
}
 
//Função: inicializa e conecta-se na rede WI-FI desejada
//Parâmetros: nenhum
//Retorno: nenhum
void initWiFi() 
{
    delay(10);
    Serial.println("------Conexao WI-FI------");
    Serial.print("Conectando-se na rede: ");
    Serial.println(SSID);
    Serial.println("Aguarde");
     
    reconectWiFi();
}
  
//Função: inicializa parâmetros de conexão MQTT(endereço do 
//        broker, porta e seta função de callback)
//Parâmetros: nenhum
//Retorno: nenhum
void initMQTT() 
{
    MQTT.setServer(BROKER_MQTT, BROKER_PORT);   //informa qual broker e porta deve ser conectado
    MQTT.setCallback(mqtt_callback);            //atribui função de callback (função chamada quando qualquer informação de um dos tópicos subescritos chega)
}
  
//Função: função de callback 
//        esta função é chamada toda vez que uma informação de 
//        um dos tópicos subescritos chega)
//Parâmetros: nenhum
//Retorno: nenhum
void mqtt_callback(char* topic, byte* payload, unsigned int length) 
{
    
    //armazena msg recebida em uma sring
    payload[length] = '\0';
    String strMSG = String((char*)payload);
  
    Serial.print("Mensagem recebida: ");
    Serial.println(strMSG);
    
    String msg = strMSG;
    
    //toma ação dependendo da string recebida:
    //verifica se deve colocar nivel alto de tensão na saída rele1:
    //IMPORTANTE: o Led já contido na placa é acionado com lógica invertida (ou seja,
    //enviar HIGH para o output faz o Led apagar / enviar LOW faz o Led acender)
    if (msg.equals("Rele1_on"))
    {
        digitalWrite(Rele1, LOW);
        EstadoSaida = '1';
    }
 
    //verifica se deve colocar nivel alto de tensão na saída Rele1:
    if (msg.equals("Rele1_off"))
    {
        digitalWrite(Rele1, HIGH);
        EstadoSaida = '0';
    }
    //Rele2
     if (msg.equals("Rele2_on"))
    {
        digitalWrite(Rele2, LOW);
        EstadoSaida = '1';
    }
 
    //verifica se deve colocar nivel alto de tensão na saída Rele2:
    if (msg.equals("Rele2_off"))
    {
        digitalWrite(Rele2, HIGH);
        EstadoSaida = '0';
    }
    //Rele3
     if (msg.equals("Rele3_on"))
    {
        digitalWrite(Rele3, LOW);
        EstadoSaida = '1';
    }
 
    //verifica se deve colocar nivel alto de tensão na saída Rele3:
    if (msg.equals("Rele3_off"))
    {
        digitalWrite(Rele3, HIGH);
        EstadoSaida = '0';
    }
    //Rele4
     if (msg.equals("Rele4_on"))
    {
        digitalWrite(Rele4, LOW);
        EstadoSaida = '1';
    }
 
    //verifica se deve colocar nivel alto de tensão na saída Rele4:
    if (msg.equals("Rele4_off"))
    {
        digitalWrite(Rele4, HIGH);
        EstadoSaida = '0';
    }
     //Rele5
     if (msg.equals("Rele5_on"))
    {
        digitalWrite(Rele5, LOW);
        EstadoSaida = '1';
    }
 
    //verifica se deve colocar nivel alto de tensão na saída Rele5:
    if (msg.equals("Rele5_off"))
    {
        digitalWrite(Rele5, HIGH);
        EstadoSaida = '0';
    }
     //Rele6
     if (msg.equals("Rele6_on"))
    {
        digitalWrite(Rele6, LOW);
        EstadoSaida = '1';
    }
 
    //verifica se deve colocar nivel alto de tensão na saída Rele6:
    if (msg.equals("Rele6_off"))
    {
        digitalWrite(Rele6, HIGH);
        EstadoSaida = '0';
    }
     //Rele7
     if (msg.equals("Rele7_on"))
    {
        digitalWrite(Rele7, LOW);
        EstadoSaida = '1';
    }
 
    //verifica se deve colocar nivel alto de tensão na saída Rele7:
    if (msg.equals("Rele7_off"))
    {
        digitalWrite(Rele7, HIGH);
        EstadoSaida = '0';
    }
     //Rele8
     if (msg.equals("Rele8_on"))
    {
        digitalWrite(Rele8, LOW);
        EstadoSaida = '1';
    }
 
    //verifica se deve colocar nivel alto de tensão na saída Rele8:
    if (msg.equals("Rele8_off"))
    {
        digitalWrite(Rele8, HIGH);
        EstadoSaida = '0';
    }
}
  
//Função: reconecta-se ao broker MQTT (caso ainda não esteja conectado ou em caso de a conexão cair)
//        em caso de sucesso na conexão ou reconexão, o subscribe dos tópicos é refeito.
//Parâmetros: nenhum
//Retorno: nenhum
void reconnectMQTT() 
{
    while (!MQTT.connected()) 
    {
        Serial.print("* Tentando se conectar ao Broker MQTT: ");
        Serial.println(BROKER_MQTT);
        if (MQTT.connect(ID_MQTT)) 
        {
            Serial.println("Conectado com sucesso ao broker MQTT!");
            MQTT.subscribe(TOPICO_SUBSCRIBE); 
        } 
        else
        {
            Serial.println("Falha ao reconectar no broker.");
            Serial.println("Havera nova tentatica de conexao em 2s");
            delay(2000);
        }
    }
}
  
//Função: reconecta-se ao WiFi
//Parâmetros: nenhum
//Retorno: nenhum
void reconectWiFi() 
{
    //se já está conectado a rede WI-FI, nada é feito. 
    //Caso contrário, são efetuadas tentativas de conexão
    if (WiFi.status() == WL_CONNECTED)
        return;
         
    WiFi.begin(SSID, PASSWORD); // Conecta na rede WI-FI
     
    while (WiFi.status() != WL_CONNECTED) 
    {
        delay(100);
        Serial.print(".");
    }
   
    Serial.println();
    Serial.print("Conectado com sucesso na rede: ");
    Serial.println(SSID);
    Serial.print("IP obtido: ");
    Serial.println(WiFi.localIP());
}
 
//Função: verifica o estado das conexões WiFI e ao broker MQTT. 
//        Em caso de desconexão (qualquer uma das duas), a conexão
//        é refeita.
//Parâmetros: nenhum
//Retorno: nenhum
void VerificaConexoesWiFIEMQTT(void)
{
    if (!MQTT.connected()) 
        reconnectMQTT(); //se não há conexão com o Broker, a conexão é refeita
     
     reconectWiFi(); //se não há conexão com o WiFI, a conexão é refeita
}
 
//Função: envia ao Broker o estado atual do output 
//Parâmetros: nenhum
//Retorno: nenhum
void EnviaEstadoOutputMQTT(void)
{
    //Rele 1
    if (EstadoSaida == '0')
      MQTT.publish(TOPICO_PUBLISH, "D");
 
    if (EstadoSaida == '1')
      MQTT.publish(TOPICO_PUBLISH, "L");
 
    Serial.println("- Estado da saida Rele 1 enviado ao broker!");
    delay(1000);
}
 
//Função: inicializa o output em nível lógico baixo
//Parâmetros: nenhum
//Retorno: nenhum
void InitOutput(void)
{
    //IMPORTANTE: o Led já contido na placa é acionado com lógica invertida (ou seja,
    //enviar HIGH para o output faz o Led apagar / enviar LOW faz o Led acender)
    pinMode(Rele1, OUTPUT);
    digitalWrite(Rele1, HIGH);
    pinMode(Rele2, OUTPUT);
    digitalWrite(Rele2, HIGH);
    pinMode(Rele3, OUTPUT);
    digitalWrite(Rele3, HIGH);
    pinMode(Rele4, OUTPUT);
    digitalWrite(Rele4, HIGH);
    pinMode(Rele5, OUTPUT);
    digitalWrite(Rele5, HIGH);
    pinMode(Rele6, OUTPUT);
    digitalWrite(Rele6, HIGH);
    pinMode(Rele7, OUTPUT);
    digitalWrite(Rele7, HIGH);
    pinMode(Rele8, OUTPUT);
    digitalWrite(Rele8, HIGH);
}
 
 
//programa principal
void loop() 
{   
    //garante funcionamento das conexões WiFi e ao broker MQTT
    VerificaConexoesWiFIEMQTT();
 
    //envia o status de todos os outputs para o Broker no protocolo esperado
    //EnviaEstadoOutputMQTT();
    
    //keep-alive da comunicação com broker MQTT
    MQTT.loop();

}
