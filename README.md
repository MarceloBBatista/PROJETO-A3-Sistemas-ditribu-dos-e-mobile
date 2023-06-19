# PROJETO A3 Sistemas ditribuidos e mobile
- Este código é um exemplo de um projeto para um microcontrolador **ESP32** que usa as bibliotecas **`WiFi`**, **`WebServer`**, **`ESPmDNS`**, **`DHT`**, **`Time`** ,**`ESP32Servo`** e **`BlynkSimpleEsp32`** para se conectar a uma rede WiFi, ler dados de sensores e controlar dispositivos como LEDs e servo motor. 
- Ele também inclui um servidor **HTTP** para exibir informações em uma página HTML gerada dinamicamente e se comunica com o **aplicativo móvel Blynk**.

## 📚 Inclusão de Bibliotecas no Arduino 
Aqui está uma imagem mostrando como incluir as bibliotecas no Arduino:
![image](https://raw.githubusercontent.com/MarceloBBatista/PROJETO-A3-Sistemas-ditribu-dos-e-mobile/main/FOTOS%20PROJETO/FOTO%201.png)
- Este código é um exemplo de inclusão de bibliotecas e definição de constantes para um microcontrolador ESP32.
- Ele inclui as bibliotecas **`WiFi`**, **`WiFiClient`**, **`WebServer`** e **`ESPmDNS`** para lidar com a conectividade WiFi e o servidor HTTP.
- Também inclui a biblioteca **`DHT`** para ler dados do sensor DHT e a biblioteca **`time`** para lidar com o horário.
- A biblioteca **`ESP32Servo`** é incluída para controlar o servo e a biblioteca **`BlynkSimpleEsp32`** é incluída para se comunicar com o aplicativo móvel Blynk.
- As constantes **`BLYNK_TEMPLATE_ID`**, **`BLYNK_TEMPLATE_NAME`** e **`BLYNK_AUTH_TOKEN`** são definidas com valores específicos para o projeto Blynk.
- As constantes ssid e password são definidas com os valores da rede WiFi à qual o microcontrolador deve se conectar.

## 📝 Definição dos Pinos utilizados na Protoboard
Aqui está uma imagem mostrando a definição dos **pinos** utilizados na protoboard:
![image](https://raw.githubusercontent.com/MarceloBBatista/PROJETO-A3-Sistemas-ditribu-dos-e-mobile/main/FOTOS%20PROJETO/FOTO%202.png)

## 📰 HTML DO PROJETO 'Parte Final'
Este código é um exemplo de uma página **HTML gerada dinamicamente** para exibir informações de um microcontrolador ESP32. 
![image](https://raw.githubusercontent.com/MarceloBBatista/PROJETO-A3-Sistemas-ditribu-dos-e-mobile/main/FOTOS%20PROJETO/FOTO%203.png)
- Ele usa a **biblioteca Bootstrap** para estilizar a página e inclui uma seção que exibe a última atualização do horário. 
- Também inclui um botão para atualizar a página. Quando o botão é clicado, um evento é acionado que recarrega a página. 
- O código usa a função **`server.send()`** para enviar a página HTML gerada como resposta a uma solicitação do cliente.

## 📑 Strings Para Suporte
Aqui está uma imagem mostrando as strings para suporte:
- Este código é um exemplo de três funções para um microcontrolador ESP32. 
![image](https://raw.githubusercontent.com/MarceloBBatista/PROJETO-A3-Sistemas-ditribu-dos-e-mobile/main/FOTOS%20PROJETO/STRINGS%20PARA%20ASSISTENCIA.png)
- A primeira função, **`getLuz_Ace_Ap()`**, verifica o valor do LDR e retorna uma string indicando se o LED está aceso ou desligado. 
- A segunda função, **`getAlarm_Casa()`**, verifica o estado do sensor de movimento e retorna uma string indicando se a casa está vulnerável ou segura. 
- A terceira função, **`getCurrentTime()`**, obtém o horário local usando a função **getLocalTime()** e formata uma string com o horário no formato **HH:MM:SS** antes de retorná-la.

## 📄 Voids
Abaixo estão algumas imagens que ilustram as funções void que implementamos em nosso projeto:
- A primeira função aciona e desliga o LED de acordo com a leitura do LDR:
![image](https://raw.githubusercontent.com/MarceloBBatista/PROJETO-A3-Sistemas-ditribu-dos-e-mobile/main/FOTOS%20PROJETO/VOID%20LDR.png)
- A segunda função controla o acionamento e desligamento do sistema de alarme:
![image](https://raw.githubusercontent.com/MarceloBBatista/PROJETO-A3-Sistemas-ditribu-dos-e-mobile/main/FOTOS%20PROJETO/VOID%20PIR.png)
- A terceira função aciona o micro servomotor com base na temperatura ambiente:
![image](https://raw.githubusercontent.com/MarceloBBatista/PROJETO-A3-Sistemas-ditribu-dos-e-mobile/main/FOTOS%20PROJETO/VOID%20SERVO.png)
- A quarta função controla o acionamento do LED RGB de acordo com a temperatura medida pelo sensor DHT:
![image](https://raw.githubusercontent.com/MarceloBBatista/PROJETO-A3-Sistemas-ditribu-dos-e-mobile/main/FOTOS%20PROJETO/VOID%20TEMP.png)

## ⚙️ Void Setup
- Este código é uma função de configuração para um microcontrolador ESP32. 
![image](https://raw.githubusercontent.com/MarceloBBatista/PROJETO-A3-Sistemas-ditribu-dos-e-mobile/main/FOTOS%20PROJETO/VOID%20SETUP%204.png)
  - Ele inicializa a comunicação serial, configura os pinos para entrada e saída de vários dispositivos (como LEDs, sensor de movimento, buzzer e botão), conecta-se a uma rede WiFi e inicia um servidor HTTP. 
  - Ele também usa a biblioteca Blynk para se comunicar com um aplicativo móvel e configura o horário usando o protocolo NTP. 
  - Além disso, ele usa o serviço MDNS para responder a solicitações de nome de host e define intervalos de tempo para notificar sobre roubo e enviar dados do sensor.

## ♾️ Void Loop
- Este código é função de loop para um microcontrolador ESP32.
![image](https://raw.githubusercontent.com/MarceloBBatista/PROJETO-A3-Sistemas-ditribu-dos-e-mobile/main/FOTOS%20PROJETO/VOID%20LOOP.png)
  - Ele lida com solicitações do cliente do servidor HTTP, obtém o horário atual e controla o servo e o LED com base na temperatura lida pelo sensor DHT. 
  - Ele também controla o LED de movimento e o buzzer com base no sensor de movimento. 
  - O código obtém o tamanho da memória livre e imprime no monitor serial, juntamente com o valor do LDR. 
  - Ele chama uma função para controlar o LED com base no valor do LDR e verifica se o alarme da casa está ativado. 
  - Se o sensor estiver ativo, ele controla o LED de movimento e o buzzer. 
  - O código também executa as funções Blynk.run() e timer.run() antes de aguardar 2 segundos e repetir o loop.

## Contribuição e Licença ©️
| [![Alexsander Máximo](https://avatars.githubusercontent.com/u/93206391?v=3&s=144)](https://github.com/AlexSan309) | [![Chrystian da Hora](https://avatars.githubusercontent.com/u/91261967?v=3&s=144)](https://github.com/ChrystiandaHora) | [![Marcelo Bezerra](https://avatars.githubusercontent.com/u/71769279?v=3&s=144)](https://github.com/MarceloBBatista) | [![Pedro Evangelista](https://avatars.githubusercontent.com/u/64512195?v=3&s=144)](https://github.com/d1zm4as) |
|---|---|---|---|
| [Alexsander Máximo](https://github.com/AlexSan309) | [Chrystian da Hora ](https://github.com/ChrystiandaHora) | [Marcelo Bezerra](https://github.com/MarceloBBatista) | [Pedro Evangelista](https://github.com/d1zm4as) |