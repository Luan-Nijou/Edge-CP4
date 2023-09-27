/*
Sites: 
https://www.blogdarobotica.com/2022/12/23/como-utilizar-o-display-lcd-16x02-com-modulo-i2c-na-esp32/

*/
/*
library:
LiquidCrystal_I2C.h

*/

#include "Arduino.h" // Inclui a biblioteca principal do Arduino
#include "WiFi.h" // Inclui a biblioteca para comunicação WiFi
#include <HTTPClient.h> // Inclui a biblioteca para fazer requisições HTTP
#include <Wire.h> // Inclui a biblioteca para comunicação I2C
#include <LiquidCrystal_I2C.h> // Inclui a biblioteca para controle de display LCD
#include "DHT.h" // Inclui a biblioteca para leitura do sensor DHT

HTTPClient client; // Instancia um objeto HTTPClient para fazer requisições HTTP

char nomeWifi[] = "..."; // Nome da rede Wi-Fi
char senhaWifi[] = "..."; // Senha da rede Wi-Fi

char serverAddress[] = "https://api.tago.io/data"; // Define o endereço do servidor onde serão enviados os dados
char contentHeader[] = "application/json"; // Define o cabeçalho do conteúdo da requisição (JSON)
char tokenHeader[] = "9ddbd0f5-c517-450d-aa1c-397ef0f3a38c"; // Define o token de autenticação do dispositivo

DHT dht(15, DHT11); // Inicializa o sensor DHT no pino 15 (DHT11)

LiquidCrystal_I2C lcd(0x27, 16, 2); // Inicializa o display LCD

#define LDR_PIN 4 // Define o pino para o sensor de luminosidade
#define GREEN_LED_PIN 19 // Define o pino para o LED verde
#define YELLOW_LED_PIN 18 // Define o pino para o LED amarelo
#define RED_LED_PIN 5 // Define o pino para o LED vermelho
#define BUZZER_PIN 2 // Define o pino para o buzzer

int luminosity = 0; // Variável para armazenar a leitura da luminosidade
char luminosityP[] = ""; // String para armazenar a mensagem relacionada à luminosidade

int humi = 0; // Variável para armazenar a umidade
int temp = 0; // Variável para armazenar a temperatura

int MODO_OK = 870; // Valor de luminosidade para estado OK
int MODO_ALERTA = 950; // Valor de luminosidade para estado de alerta
int humi_OK = 50; // Valor de umidade para estado OK
int humi_ALERTA = 70; // Valor de umidade para estado de alerta
int temp_OK = 10; // Valor de temperatura para estado OK
int temp_ALERTA = 15; // Valor de temperatura para estado de alerta

int systemState = 0; // Variável para armazenar o estado do sistema (0: OK, 1: Alerta, 2: Problema)

void setup() {
  lcd.init(); // Inicializa o display LCD
  lcd.clear(); // Limpa o display
  lcd.backlight(); // Liga a luz de fundo do display

  dht.begin(); // Inicializa o sensor DHT

  pinMode(GREEN_LED_PIN, OUTPUT); // Define o pino do LED verde como saída
  pinMode(YELLOW_LED_PIN, OUTPUT); // Define o pino do LED amarelo como saída
  pinMode(RED_LED_PIN, OUTPUT); // Define o pino do LED vermelho como saída
  pinMode(BUZZER_PIN, OUTPUT); // Define o pino do buzzer como saída

  Serial.begin(9600); // Inicializa a comunicação serial com baud rate de 9600
  init_wifi(); // Inicializa a conexão WiFi
}

void Temp_Rod() {
  if (temp < temp_OK) { // Verifica se a temperatura está abaixo do limite OK
    lcd.clear(); // Limpa o display
    lcd.setCursor(0, 0); // Define a posição do cursor
    lcd.print("Temp. Baixa "); // Exibe mensagem de temperatura baixa
    lcd.setCursor(0, 1); // Define a posição do cursor
    lcd.print("Temp. = "); // Exibe "Temp. = "
    lcd.println(temp); // Exibe o valor da temperatura
    tone(BUZZER_PIN, 1000, 3000); // Ativa o buzzer com frequência de 1000 Hz por 3 segundos
    digitalWrite(YELLOW_LED_PIN, HIGH); // Acende o LED amarelo
  } else if (temp < temp_ALERTA) { // Verifica se a temperatura está abaixo do limite de alerta
    lcd.clear(); // Limpa o display
    lcd.setCursor(0, 0); // Define a posição do cursor
    lcd.print("Temp. OK "); // Exibe mensagem de temperatura OK
    lcd.setCursor(0, 1); // Define a posição do cursor
    lcd.print("Temp. = "); // Exibe "Temp. = "
    lcd.println(temp); // Exibe o valor da temperatura
  } else {
    lcd.clear(); // Limpa o display
    lcd.setCursor(0, 0); // Define a posição do cursor
    lcd.print("Temp. ALTA "); // Exibe mensagem de temperatura alta
    lcd.setCursor(0, 1); // Define a posição do cursor
    lcd.print("Temp. = "); // Exibe "Temp. = "
    lcd.println(temp); // Exibe o valor da temperatura
    tone(BUZZER_PIN, 1000, 3000); // Ativa o buzzer com frequência de 1000 Hz por 3 segundos
    digitalWrite(RED_LED_PIN, HIGH); // Acende o LED vermelho
  }
}

void Humi_Rod() {
  if (humi < humi_OK) { // Verifica se a umidade está abaixo do limite OK
    lcd.clear(); // Limpa o display
    lcd.setCursor(0, 0); // Define a posição do cursor
    lcd.print("Umid. Baixa "); // Exibe mensagem de umidade baixa
    lcd.setCursor(0, 1); // Define a posição do cursor
    lcd.print("Umid. = "); // Exibe "Umid. = "
    lcd.println(humi); // Exibe o valor da umidade
    tone(BUZZER_PIN, 1000, 3000); // Ativa o buzzer com frequência de 1000 Hz por 3 segundos
    digitalWrite(YELLOW_LED_PIN, HIGH); // Acende o LED amarelo
  } else if (humi < humi_ALERTA) { // Verifica se a umidade está abaixo do limite de alerta
    lcd.clear(); // Limpa o display
    lcd.setCursor(0, 0); // Define a posição do cursor
    lcd.print("Umid. OK "); // Exibe mensagem de umidade OK
    lcd.setCursor(0, 1); // Define a posição do cursor
    lcd.print("Umid. = "); // Exibe "Umid. = "
    lcd.println(humi); // Exibe o valor da umidade
  } else {
    lcd.clear(); // Limpa o display
    lcd.setCursor(0, 0); // Define a posição do cursor
    lcd.print("Umid. ALTA "); // Exibe mensagem de umidade alta
    lcd.setCursor(0, 1); // Define a posição do cursor
    lcd.print("Umid. ="); // Exibe "Umid. = "
    lcd.println(humi); // Exibe o valor da umidade
    tone(BUZZER_PIN, 1000, 3000); // Ativa o buzzer com frequência de 1000 Hz por 3 segundos
    digitalWrite(RED_LED_PIN, HIGH); // Acende o LED vermelho
  }
}

void init_wifi() {
  Serial.println("Conectando WiFi"); // Imprime mensagem no monitor serial
  Serial.print("Wifi: "); // Imprime "Wifi: "
  Serial.println(nomeWifi); // Imprime o nome da rede Wi-Fi
  WiFi.begin(nomeWifi, senhaWifi); // Tenta conectar à rede Wi-Fi com o nome e senha especificados

  while (WiFi.status() != WL_CONNECTED) { // Aguarda até que a conexão seja estabelecida
    Serial.print("."); // Imprime um ponto a cada segundo
    delay(1000); // Aguarda 1 segundo
  }

  Serial.println("WiFi Conectado"); // Imprime "WiFi Conectado"
  Serial.print("Meu IP eh: "); // Imprime "Meu IP eh: "
  Serial.println(WiFi.localIP()); // Imprime o endereço IP local atribuído
}

void send_infos() {
  int statusCode = 0; // Variável para armazenar o código de status da requisição HTTP
  char postData[500]; // String para armazenar os dados a serem enviados no formato JSON

  // Construa o JSON com os dados a serem enviados
  snprintf(postData, sizeof(postData), "{\n"
                                      "\t\"variable\": \"temperature\",\n"
                                      "\t\"value\": %.2f,\n"
                                      "\t\"unit\": \"ºC\"\n"
                                      "}\n"
                                      "{\n"
                                      "\t\"variable\": \"humidity\",\n"
                                      "\t\"value\": %d,\n"
                                      "\t\"unit\": \"%\"\n"
                                      "}\n"
                                      "{\n"
                                      "\t\"variable\": \"luminosity\",\n"
                                      "\t\"value\": %d\n"
                                      "}\n",
           temp, humi, luminosity);

  client.begin(serverAddress); // Inicia a comunicação com o servidor especificado
  client.addHeader("Content-Type", contentHeader); // Adiciona o cabeçalho de conteúdo da requisição
  client.addHeader("Device-Token", tokenHeader); // Adiciona o token de autenticação do dispositivo

  statusCode = client.POST(postData); // Envia a requisição HTTP POST com os dados formatados em JSON

  delay(2000); // Aguarda 2 segundos

  // Leia o código de status e o corpo da resposta
  Serial.print("Status code: "); // Imprime "Status code: "
  Serial.println(statusCode); // Imprime o código de status retornado pelo servidor
  Serial.println("End of POST to TagoIO"); // Imprime "End of POST to TagoIO"
  Serial.println(); // Imprime uma linha em branco
}

void loop() {
  int luminosity = analogRead(LDR_PIN); // Lê o valor da luminosidade
  humi = dht.readHumidity(); // Lê o valor da umidade do sensor DHT
  temp = dht.readTemperature(); // Lê o valor da temperatura do sensor DHT

  Serial.print("\n LDR  =  "); // Imprime "LDR  =  "
  Serial.print(luminosity); // Imprime o valor da luminosidade
  Serial.print("\n Temperatura C =  "); // Imprime "Temperatura C =  "
  Serial.print(temp); // Imprime o valor da temperatura
  Serial.print("\n Humidade: "); // Imprime "Humidade: "
  Serial.print(humi); // Imprime o valor da umidade

  delay(2000); // Aguarda 2 segundos

  if (luminosity <= MODO_OK) {
    systemState = 0;  // OK
    char luminosityP[] = "Ambiente OK"; // Define a mensagem relacionada à luminosidade
  } else if (luminosity <= MODO_ALERTA) {
    systemState = 1;  // Alerta
    char luminosityP[] = "Ambiente Meia Luz"; // Define a mensagem relacionada à luminosidade
  } else {
    systemState = 2;  // Proble
    char luminosityP[] = "Ambiente Claro"; // Define a mensagem relacionada à luminosidade
  }

  switch (systemState) {
    case 0:
      // Ambiente OK
      digitalWrite(GREEN_LED_PIN, HIGH); // Acende o LED verde
      digitalWrite(YELLOW_LED_PIN, LOW); // Apaga o LED amarelo
      digitalWrite(RED_LED_PIN, LOW); // Apaga o LED vermelho
      noTone(BUZZER_PIN); // Desliga o buzzer (caso esteja ligado)
      lcd.clear(); // Limpa o display
      lcd.setCursor(0, 0); // Define a posição do cursor
      lcd.print("Ambiente OK"); // Exibe mensagem de ambiente OK
      break;

    case 1:
      // Ambiente em Alerta
      digitalWrite(GREEN_LED_PIN, LOW); // Apaga o LED verde
      digitalWrite(YELLOW_LED_PIN, HIGH); // Acende o LED amarelo
      digitalWrite(RED_LED_PIN, LOW); // Apaga o LED vermelho
      noTone(BUZZER_PIN); // Desliga o buzzer (caso esteja ligado)
      lcd.clear(); // Limpa o display
      lcd.setCursor(0, 0); // Define a posição do cursor
      lcd.print("Ambiente a meia"); // Exibe mensagem de ambiente com meia luz
      lcd.setCursor(0, 1); // Define a posição do cursor
      lcd.print("Luz"); // Exibe "Luz"
      break;

    case 2:
      // Ambiente em Problema
      digitalWrite(GREEN_LED_PIN, LOW); // Apaga o LED verde
      digitalWrite(YELLOW_LED_PIN, LOW); // Apaga o LED amarelo
      digitalWrite(RED_LED_PIN, HIGH); // Acende o LED vermelho
      tone(BUZZER_PIN, 1000, 3000); // Ativa o buzzer com frequência de 1000 Hz por 3 segundos
      lcd.clear(); // Limpa o display
      lcd.setCursor(0, 0); // Define a posição do cursor
      lcd.print("Ambiente muito "); // Exibe mensagem de ambiente muito claro
      lcd.setCursor(0, 1); // Define a posição do cursor
      lcd.print("CLARO"); // Exibe "CLARO"
      break;

    default:
      // Estado desconhecido
      printf("Estado desconhecido"); // Imprime "Estado desconhecido"
      break;
  }
  
  Temp_Rod(); // Chama a função para verificar a temperatura
  delay(1000); // Aguarda 1 segundo
  Humi_Rod(); // Chama a função para verificar a umidade
  delay(1000); // Aguarda 1 segundo

  send_infos(); // Chama a função para enviar os dados para o servidor TagoIO
  delay(5000); // Aguarda 5 segundos
}

