

<p align="center" >
 <img  src="https://github.com/Luan-Nijou/Edge-CP4/assets/126830016/9388d8fb-3b04-4aa3-b0e4-e833a1d74c1a"/>
</p>
<p align="center">
 
  <img src="http://img.shields.io/static/v1?label=License&message=MIT&color=green&style=for-the-badge"/>
  <img src="http://img.shields.io/static/v1?label=STATUS&message=EM%20DESENVOLVIMENTO&color=RED&style=for-the-badge"/>
 
</p>


### Tópicos 

:small_blue_diamond: [Acesso ao projeto](#-acesso-ao-projeto)

:small_blue_diamond: [Descrição do projeto](#-descrição-do-projeto)

:small_blue_diamond: [Layout da Arquitetura](#-layout-da-arquitetura)

:small_blue_diamond: [Componentes](componentes)

:small_blue_diamond: [Replicar](#-replicar)  

:small_blue_diamond: [Linguagem Usada](#-linguagem-usada)

:small_blue_diamond: [Desenvolvedores](#-desenvolvedores)

:small_blue_diamond: [Licença](#-licença)



## 📁 Acesso ao projeto

 [Acesso do código fonte da simulação.](https://github.com/Luan-Nijou/Edge-CP4/blob/main/Code.ino)

## 📝 Descrição do projeto 

<p align="justify">
  Desenvolver um sistema de monitoramento remoto para a Vinheria, com o intuito de proporcionar aos proprietários acesso contínuo e em tempo real aos dados dos sensores de luminosidade, temperatura e umidade. A implementação desse sistema visa oferecer uma solução mais eficiente e conveniente em comparação ao modelo anterior.
</p> 

## 🧰 Layout da Arquitetura 


**Fisíco**
![Sistema Vinharia arquitetura](https://github.com/Luan-Nijou/Edge-CP4/assets/126830016/8d56f3d3-52ee-466f-9ecb-6359155e6c58)

**Internet**

![Internet dashboard vinharia](https://github.com/Luan-Nijou/Edge-CP4/assets/126830016/3c7c3833-01d4-4010-a75c-89a93effb916)

## ⚙️ Componentes

<p align="justify">
> ESP32 - O ESP32 é um microcontrolador de baixo custo e baixo consumo de energia desenvolvido pela Espressif Systems. Ele é amplamente utilizado na indústria de IoT (Internet das Coisas) devido às suas capacidades avançadas de conectividade e flexibilidade. 
<p/>
<p align="justify">
> LDR - O LDR, ou "Light Dependent Resistor", é um componente eletrônico sensível à luz. Também conhecido como fotoresistor, sua resistência elétrica varia de acordo com a intensidade da luz incidente sobre ele. Quando exposto à luz, a resistência do LDR diminui, e quando em ambiente escuro, sua resistência aumenta.
<p/>
<p align="justify">
> DHT11 - O DHT11 é um sensor de temperatura e umidade digital muito utilizado em projetos de eletrônica e automação.
<p/>
<p align="justify">
> LCD - As telas LCD desempenham um papel importante na interface homem-máquina (HMI) para dispositivos conectados.São usados para exibir informações relevantes ao usuário, como dados de sensores, status de dispositivos e mensagens.
<p/>
  

## 📝 Replicar 

<p align="justify">
Para replicar ou/e modificar do seu modo:

 1. Possuir em seu dispositivo o [Arduino IDE](https://www.arduino.cc/en/software) e uma conta na [tago.io](https://tago.io), e [aqui um video](https://www.youtube.com/watch?v=leKi6Tt3DXI) para enteder o basico da tago.

 2. Possuir o hardware, que será: Um ESP32, um LDR, Cabos jumpers, 3 LED's e opcional: uma protoboard(para melhor visualização e fixação dos itens).

 3. Para configuração do IDE, usar como BOARD o ESP32 DEV MODULE(Basta entrar em TOOLS -> BOARD -> ESP32 -> ESP32 DEV MODULE, se não tiver, baixar a biblioteca do esp32), colocar na PORT a que funcionar, e instalar as bibliotecas necessárias: 
-LiquidCrystal I2C
-DHT sensor library
-Adafruit Unified Sensor
-ESP32
 
 4. Para as ligações do hardware, sugiro observar e montar de acordo com esse site [site](https://wokwi.com/projects/377032518166226945). OBS: O LDR pode ser usado sozinho, apenas ligando um resistor no GND e em uma das pernas do LDR, e colocar um fio na outra perna e ligar no D4 do ESP32; Enquanto o DHT11 e o DHT22 são ligados da mesma forma.

 5. Depois, faça as configurações principais do código, como: Colocar o nome e a senha corretamente, e o token do device que foi criado na tago, e montar suas actions e dashboards.
<p/>

## 💻 Linguagem Usada

<img src="https://www.alura.com.br/artigos/assets/formacao-linguagem-c-plus-plus/img-01.png" width=50/>


## 💻 Desenvolvedores 


| [<img src="https://i.imgur.com/ZIv3QYz.jpg" width=150 height= 150><br><sub>Luan Nijou</sub>](https://github.com/Luan-Nijou) | [<img src="https://i.imgur.com/p8nq4Xu.jpg" width=150 height= 150><br><sub>Pedro Henrique Alves Guariente</sub>](https://github.com/predowss) | [<img src="https://i.imgur.com/qiQoCcq.jpg" width=150 height= 150><br><sub>David de Medeiros Pacheco Junior</sub>](https://github.com/daviddpacheco) | [<img src="https://i.imgur.com/noeh6xz.jpg" width=150 height= 150><br><sub>Kaique Maia Reis Silva</sub>](https://github.com/kaiquemaiaa) | [<img src="" width=150 height= 150><br><sub>Orlando Akio Morii Cardoso</sub>](https://github.com/AkioMorii) | 
| :---: | :---: | :---: | :---: | :---: | 


[<img src="https://github.com/Luan-Nijou/Edge-CP4/assets/126830016/585d5c6d-5592-4578-8787-5011106120a5" width=150 height= 150><br><sub>Kauê Pastori Teixeira</sub>](https://github.com/Kautx) 
| :---: 



## Licença 

The [MIT License]() (MIT)

Copyright :copyright: 2023 - VinhariaAgnelo
