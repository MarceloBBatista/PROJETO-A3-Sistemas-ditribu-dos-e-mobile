#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <DHT.h>
#include <time.h>
#include <ESP32Servo.h>
#include <BlynkSimpleEsp32.h>
#define BLYNK_TEMPLATE_ID "TMPL2_mFNoo3P"
#define BLYNK_TEMPLATE_NAME "PROJETO A3"
#define BLYNK_AUTH_TOKEN "CtaxeTGj0XUXKpF9PwgtgzgEnRLkjP79"
#define BLYNK_PRINT Serial

char auth[] = BLYNK_AUTH_TOKEN;

const char *ssid = "Redmi Note 9 Pro";
const char *password = "mg092258";

BlynkTimer timer;

WebServer server(80);
DHT dht(4, DHT11);
const int buzzerPin = 13; // Pino do buzzer
const int ledrdPin = 21;  // Pino digital conectado ao LED
const int ledPin = 22;    // Pino do LED de movimento
const int pirPin = 23;    // Pino do sensor de movimento
const int greenPin = 25;  // Pino do LED verde (RGB)
const int bluePin = 26;   // Pino do LED azul (RGB)
const int redPin = 33;    // Pino do LED vermelho (RGB)
const int ldrPin = 35;    // Pino analógico conectado ao LDR
const int buttonPin = 18; // Pino botão físico

volatile bool sensorAtivo = true;

int servoPin = 32; // Pino de controle PWM do servo motor
Servo s;           // Objeto para o servo motor

String Alarm_Casa;
//int flag=0;
void notifyOnTheft()
{
  int isTheftAlert = digitalRead(pirPin);
  Serial.println(isTheftAlert);
  if (isTheftAlert==1) {
    Serial.println("YOUR HOME IS BEING INVADERED");
    // Blynk.email("email", "Alert", "Theft Alert in Home");
    //Blynk.notify("Alert : YOUR HOME IS BEING INVADERED");
    Blynk.logEvent("theft_alert","YOUR HOME IS BEING INVADERED");
//    flag=1;
  }
  else if (isTheftAlert==0)
  {
   // flag=0;
  }
}

void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit
  String l = getLuz_Ace_Ap();
  String al = getAlarm_Casa();
  float ll = ValorLDRproLED();
 if (ll >= 2000)
    {                                // O valor vai de 0 a 4095 (ajuste esse valor conforme necessário)
        Blynk.virtualWrite(V4, 0); // Desliga o LED
    }
    else
    {
        Blynk.virtualWrite(V4, 1); // Liga o LED
    }
  
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
    Blynk.virtualWrite(V0, t);
    Blynk.virtualWrite(V1, h);
    Blynk.virtualWrite(V2, l);
    Blynk.virtualWrite(V3, al);
    //Blynk.virtualWrite(V4, ll);
    
    Serial.print("Led: ");
    Serial.print(ll);
    Serial.print("  Alarme :");
    Serial.print(al);
    Serial.print("  Luz : ");
    Serial.print(l);
    Serial.print("  Temperature : ");
    Serial.print(t);
    Serial.print("    Humidity : ");
    Serial.println(h);
}

float readDHTTemperature()
{
    // As leituras do sensor também podem levar até 2 segundos
    // Leia a temperatura como Celsius (o padrão)
    float t = dht.readTemperature();
    if (isnan(t))
    {
        Serial.println("Falha ao ler do sensor DHT!");
        return -1;
    }
    else
    {
        Serial.println(t);
        return t;
    }
}

float readDHTHumidity()
{
    // As leituras do sensor também podem levar até 2 segundos
    float h = dht.readHumidity();
    if (isnan(h))
    {
        Serial.println("Falha ao ler do sensor DHT!");
        return -1;
    }
    else
    {
        Serial.println(h);
        return h;
    }
}

String currentTime;
String Luz_Ace_Ap;

void handleRoot()
{
    char msg[4600];

    snprintf(msg, 4600,
             "<html>\
\
<head>\
    <meta http-equiv='refresh' content='600' />\
    <meta charset='UTF-8'>\
    <meta name='viewport' content='width=device-width, initial-scale=1'>\
    <link rel='stylesheet' href='https://cdnjs.cloudflare.com/ajax/libs/font-awesome/6.4.0/css/all.min.css'>\
    <link href='https://cdn.jsdelivr.net/npm/bootstrap@5.2.3/dist/css/bootstrap.min.css' rel='stylesheet'\
        integrity='sha384-rbsA2VBKQhggwzxH7pPCaAqO46MgnOM80zW1RWuH61DGLwZJEdK2Kadq2F9CUG65' crossorigin='anonymous'>\
    <title>ESP32 Control</title>\
    <style>\
        html {\
            font-family: Arial;\
            display: inline-block;\
            margin: 0px auto;\
            text-align: center;\
        }\
\
        body {\
            background: #1b1c1e;\
        }\
\
        h2 {\
            color: #fff;\
            font-size: 3.0rem;\
        }\
\
        p {\
            font-size: 3.0rem;\
        }\
\
        .units {\
            font-size: 1.2rem;\
        }\
\
        .dht-labels {\
            font-size: 1.5rem;\
            vertical-align: middle;\
            padding-bottom: 15px;\
        }\
\
        .pointer {\
            cursor: pointer;\
        }\
    </style>\
</head>\
\
<body>\
    <h2 class='m-2 text-center'>Controle ESP32</h2>\
    <div class='container-fluid'>\
        <div class='row d-flex align-items-stretch'>\
            <div class='p-2 my-2 col-sm-4 col-md-6 col-lg-4'>\
                <div class='bg-body rounded' style='min-height: 320px;'>\
                    <p>\
                        <i class='fas fa-thermometer-half' style='color:#FF0000;'></i>\
                        <span class='m-2 dht-labels'>Temperatura:</span><br>\
                        <span>%.2f</span>\
                        <sup class='units'>&deg;C</sup>\
                    </p>\
                    <p>\
                        <i class='fas fa-tint' style='color:#1E90FF;'></i>\
                        <span class='m-2 dht-labels'>Umidade:</span><br>\
                        <span>%.2f</span>\
                        <sup class='units'>&percnt;</sup>\
                    </p>\
                </div>\
            </div>\
            <div class='p-2 my-2 col-sm-4 col-md-6 col-lg-4'>\
                <div class='bg-body rounded' style='min-height: 320px;'>\
                    <p>\
                        <i class='far fa-lightbulb' style='color:#FFD700;'></i>\
                        <span class='m-2 dht-labels'>Status Luz:</span><br>\
                        <span>%s</span>\
                    </p>\
                </div>\
            </div>\
            <div class='p-2 my-2 col-sm-4 col-md-6 col-lg-4'>\
                <div class='bg-body rounded' style='min-height: 320px;'>\
                    <p>\
                        <i class='fa-solid fa-house' style='color:#008B8B;'></i>\
                        <span class='m-2 dht-labels'>Sensor Alarme:</span><br>\
                        <span>%s</span><br>\
                        <i class='my-5 fa-solid fa-bell' style='color: #FFFF00;'></i>\
                    </p>\
                </div>\
            </div>\
            <div class='p-2 my-2 col-sm-4 col-md-6 col-lg-4 mx-auto'>\
                <div class='bg-body rounded' style='min-height: 150px;'>\
                    <p class='py-5'>\
                        <i class='far fa-clock' style='color:#000;'></i>\
                        <span class='m-2 dht-labels'>Última Atualização:</span>\
                        <span>%s</span>\
                    </p>\
                </div>\
            </div>\
        </div>\
        <div class='container-fluid'>\
            <div class='row justify-content-center'>\
                <div class='p-2 my-2 bg-body rounded col-md-6 col-lg-4 pointer' id='minhaDiv'>\
                    <p>\
                        <i class='fas fa-sync' style='color:#000;'></i>\
                        <span class='dht-labels'>Atualizar</span>\
                    </p>\
                </div>\
            </div>\
        </div>\
    </div>\
\
    <script src='https://cdn.jsdelivr.net/npm/bootstrap@5.2.3/dist/js/bootstrap.bundle.min.js'\
        integrity='sha384-kenU1KFdBIe4zVF0s0G1M5b4hcpxyD9F7jL+jjXkk+Q2h455rYXK/7HAuoJl+0I4'\
        crossorigin='anonymous'></script>\
    <script>\
        document.getElementById('minhaDiv').addEventListener('click', function () {\
            location.reload();\
        });\
    </script>\
</body>\
\
</html>",
             readDHTTemperature(), readDHTHumidity(), Luz_Ace_Ap.c_str(), Alarm_Casa.c_str(), currentTime.c_str());
    server.send(200, "text/html", msg);
}

void setup(void)
{
    Serial.begin(115200);
    dht.begin();
    s.attach(servoPin);
    s.write(0);                 // Inicia motor posição zero
    pinMode(redPin, OUTPUT);    // Configura o pino do LED vermelho como saída
    pinMode(greenPin, OUTPUT);  // Configura o pino do LED verde como saída
    pinMode(bluePin, OUTPUT);   // Configura o pino do LED azul como saída
    pinMode(pirPin, INPUT);     // Configura o pino do sensor de movimento como entrada
    pinMode(ledPin, OUTPUT);    // Configura o pino do LED de movimento como saída
    pinMode(buzzerPin, OUTPUT); // Configura o pino do buzzer como saída
    pinMode(ledrdPin, OUTPUT);  // Define o pino do LED como saída
    pinMode(ldrPin, INPUT);
    pinMode(buttonPin, INPUT_PULLUP); // Define botão como entrada
    attachInterrupt(digitalPinToInterrupt(buttonPin), Ativosensor, RISING);

    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    Serial.println("");

    // Wait for connection
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    Blynk.begin(auth, ssid, password);
    
    configTime(0, 0, "pool.ntp.org");
    setenv("TZ", "GMT+3", 1);
    tzset();

    if (MDNS.begin("esp32"))
    {
        Serial.println("Resposta MDNS iniciada");
    }
    server.on("/", handleRoot);

    timer.setInterval(5000L, notifyOnTheft);
    timer.setInterval(100L, sendSensor);
    
    server.begin();
    Serial.println("Servidor HTTP iniciado!");
}

void controlServo(float readDHTTemperature)
{
    if (readDHTTemperature >= 24) // Verifica se a temperatura é alta e a umidade é baixa
    {
        s.write(0); // Gira o servo motor para a posição 0 graus
        delay(1000);
        s.write(180); // Gira o servo motor para a posição 180 graus
        delay(1000);
    }
    else if (readDHTTemperature <= 10) // Verifica se a temperatura é baixa e a umidade é alta
    {
        s.write(0); // Gira o servo motor para a posição 0 graus
        delay(1000);
        s.write(60); // Gira o servo motor para a posição 60 graus
        delay(1000);
    }
    else // Caso contrário (temperatura e umidade ambiente)
    {
        s.write(0); // Gira o servo motor para a posição 0 graus
        delay(1000);
        s.write(90); // Gira o servo motor para a posição 90 graus
        delay(1000);
    }
}

void controlLed(float readDHTTemperature)
{
    if (readDHTTemperature >= 24) // Verifica se a temperatura é alta
    {
        Serial.println("Temperatura Alta");
        digitalWrite(redPin, HIGH);  // Acende o LED vermelho
        digitalWrite(greenPin, LOW); // Desliga o LED verde
        digitalWrite(bluePin, LOW);  // Desliga o LED azul
    }
    else if (readDHTTemperature <= 10) // Verifica se a temperatura é baixa
    {
        Serial.println("Temperatura Baixa");
        digitalWrite(redPin, LOW);   // Desliga o LED vermelho
        digitalWrite(greenPin, LOW); // Desliga o LED verde
        digitalWrite(bluePin, HIGH); // Acende o LED azul
    }
    else // Caso contrário (temperatura ambiente)
    {
        Serial.println("Temperatura Ambiente");
        digitalWrite(redPin, LOW);    // Desliga o LED vermelho
        digitalWrite(greenPin, HIGH); // Acende o LED verde
        digitalWrite(bluePin, LOW);   // Desliga o LED azul
    }
}

void controlLedPIR()
{
    if (digitalRead(pirPin) == HIGH) // Verifica se o sensor de movimento foi acionado
    {
      if(!sensorAtivo){
    return;
  }
        for (int i = 0; i < 4; i++) {
            digitalWrite(ledPin, HIGH); // Acende o LED de movimento
            Serial.println("Movimento detectado!");
            tone(buzzerPin, 1000);      // Gera um tom de 1000Hz no pino do buzzer
            delay(600);
            digitalWrite(ledPin, LOW); // Desliga o LED de movimento
            noTone(buzzerPin);         // Para de gerar o tom
            delay(600);
        }
    }
    else
    {
        digitalWrite(ledPin, LOW); // Desliga o LED de movimento
        Serial.println("Movimento NÃO DETECTADO!");
        noTone(buzzerPin);         // Para de gerar o tom
    }
}

float ValorLDRproLED(){
    float ValorLDR = analogRead(ldrPin);
    if (isnan(ValorLDR)){
        Serial.print("Falha ao ler o sensor LDR");
        return -1;
    }else{
        Serial.println(ValorLDR);
        return ValorLDR;
    }
}

void LED_LDR_CONTROL(float ValorLDRproLED){
  if (ValorLDRproLED >= 2000)
    {                                // O valor vai de 0 a 4095 (ajuste esse valor conforme necessário)
        digitalWrite(ledrdPin, LOW); // Desliga o LED
    }
    else
    {
        digitalWrite(ledrdPin, HIGH); // Liga o LED
    }
}

void Ativosensor(){
  sensorAtivo = !sensorAtivo;
}

void loop(void)
{
    server.handleClient();
    currentTime = getCurrentTime();
    controlServo(readDHTTemperature());
    controlLed(readDHTTemperature());
    controlLedPIR(); // Controla o LED de movimento e o buzzer com base no sensor de movimento
    
    uint32_t freeHeap = ESP.getFreeHeap(); // Obtém o tamanho da memória livre

    Serial.print("Memória livre: ");
    Serial.print(freeHeap); // Imprime o tamanho da memória livre no monitor serial
    Serial.println(" bytes");

    Serial.println("Valor do LDR:");
    Serial.println(ValorLDRproLED()); // Imprime o valor do LDR

    LED_LDR_CONTROL(ValorLDRproLED()); // Chama a função para controlar o LED com base no valor do LDR

    Luz_Ace_Ap = getLuz_Ace_Ap();

    Alarm_Casa = getAlarm_Casa();

    if(sensorAtivo){
      controlLedPIR();
    }
    Serial.println("Valor do sensorAtivo: ");
    Serial.print(sensorAtivo);
    Serial.println("...");
    Blynk.run();
    timer.run();
    
    delay(2000); // Aguarda 2 segundos antes de repetir o loop
}

String getLuz_Ace_Ap(){

  if (ValorLDRproLED() >= 2000)
    {                                // O valor vai de 0 a 4095 (ajuste esse valor conforme necessário)
        return "Desligado";   // Liga o LED
    }
    else {
        return "Aceso";  // Desliga o LED
    }
}

String getAlarm_Casa() {
  if (digitalRead(pirPin) == HIGH) {
    return "Vulnerável";
  } else {
    return "Seguro";
  }
}

String getCurrentTime()
{
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo))
    {
        Serial.println("Falha ao obter tempo");
        return "";
    }

    char timeString[9];
    snprintf(timeString, sizeof(timeString), "%02d:%02d:%02d", timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec);

    return String(timeString);
}