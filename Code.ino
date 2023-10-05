/*
RM550301 - Pedro Henrique Alves Guariente

RM551462 - David de Medeiros Pacheco Junior

RM552112 - Kaique Maia Reis Silva

RM98067 - Orlando Akio Morii Cardoso

RM98920 - Luan Nijou

RM98501 - Kauê Pastori Teixeira 

*/



/*
Sites: 
https://www.blogdarobotica.com/2022/12/23/como-utilizar-o-display-lcd-16x02-com-modulo-i2c-na-esp32/

*/
/*
library:
LiquidCrystal_I2C.h

*/

#include "Arduino.h"
#include "WiFi.h"
#include <HTTPClient.h>
#include "DHT.h"

HTTPClient client;
char nomeWifi[] = "Euuu";
char senhaWifi[] = "xvqb4249";
char serverAddress[] = "https://api.tago.io/data";
char contentHeader[] = "application/json";
char tokenHeader[] = "bebbfab2-1c89-4787-88a7-56fb5e0a7d72";


DHT dht(15, DHT11);


#define LDR_PIN 34


int luminosity = 0;
char luminosityP[] = "";
  
int humi = 0;
int temp = 0;

/*
int i = 0;
long acumHumi = 0;
long acumTemp = 0;
*/

int MODO_OK = 870;
int MODO_ALERTA = 950;
int humi_OK = 50;
int humi_ALERTA = 70;
int temp_OK = 10;
int temp_ALERTA = 15;

int systemState = 0;

void setup() {
  pinMode(LDR_PIN, INPUT);
  dht.begin();
  Serial.begin(9600);
  init_wifi();
}


void init_wifi() {
  Serial.println("Conectando WiFi");
  Serial.print("Wifi: ");
  Serial.println(nomeWifi);
  WiFi.begin(nomeWifi, senhaWifi);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("WiFi Conectado");
  Serial.print("Meu IP eh: ");
  Serial.println(WiFi.localIP());
}
void send_info() {
  char anyData[100];
  char postData[500]; // Aumente o tamanho para acomodar as novas variáveis
  char anyData1[30];
  char anyData2[30];
  char bAny[30];
  int statusCode = 0;

  
  strcpy(postData, "{\n\t\"variable\": \"Temperatura\",\n\t\"value\": ");
  dtostrf(temp, 6, 2, anyData);
  strcat(postData,anyData);
  strcpy(anyData1, ",\n\t\"unit\": \"C\"\n\t}\n");
  strncat (postData, anyData1, 100);

  // Resto do código permanece o mesmo
  Serial.println(postData);
  HTTPClient client;
  client.begin(serverAddress);
  client.addHeader("Content-Type", contentHeader);
  client.addHeader("Device-Token", tokenHeader);
  statusCode = client.POST(postData);
  delay(2000);

  strcpy(postData, "{\n\t\"variable\": \"Humidade\",\n\t\"value\": ");
  dtostrf(humi, 6, 2, anyData);
  strcat(postData,anyData);
  strcpy(anyData1, ",\n\t\"unit\": \"%\"\n\t}\n");
  strncat (postData, anyData1, 100);

  Serial.println(postData);
  //HTTPClient client;
  client.begin(serverAddress);
  client.addHeader("Content-Type", contentHeader);
  client.addHeader("Device-Token", tokenHeader);
  statusCode = client.POST(postData);
  delay(2000);
  
  strcpy(postData, "{\n\t\"variable\": \"Luminosidade\",\n\t\"value\": ");
  dtostrf(luminosity, 6, 2, anyData);
  strcat(postData,anyData);
  strcpy(anyData1, ",\n\t\"unit\": \"lumem\"\n\t}\n");
  strncat (postData, anyData1, 100);

  Serial.println(postData);
  //HTTPClient client;
  client.begin(serverAddress);
  client.addHeader("Content-Type", contentHeader);
  client.addHeader("Device-Token", tokenHeader);
  statusCode = client.POST(postData);
  delay(2000);
  
  Serial.print("Status code: ");
  Serial.println(statusCode);
  Serial.println("End of POST to TagoIO");
  Serial.println();
}

void loop() {
  luminosity = analogRead(LDR_PIN);
  humi = dht.readHumidity();
  temp = dht.readTemperature();
  Serial.print("\n LDR  =  ");
  Serial.print(luminosity);
  Serial.print("\n Temperatura C =  ");
  Serial.print(temp);
  Serial.print("\n Humidade: ");
  Serial.print(humi);
  delay(2000);


  send_info(); // Envie a temperatura para o servidor TagoIO
  delay(5000);
}
