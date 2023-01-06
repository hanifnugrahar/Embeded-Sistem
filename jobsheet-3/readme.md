# Jobsheet 3
Topologi Jaringan Lokal dan Wifi

## Anggota Kelompok
- Hanif Nugraha Ramadhan [4.31.20.0.10]
- Muhammad Rafif Hasani  [4.31.20.0.16]

## ANALISA

A. ESP32 Wi-Fi Modes dan Wifi-Scan

Pada ESP32, terdapat 3 mode akses untuk Wifi, yaitu WIFI_STA (station mode : ESP32 sebagai client yang terkoneksi ke access point), WIFI_AP (access point mode : ESP32 berperan sebagai access point), WIFI_STA_AP (access point and station : ESP32 dapat terkoneksi dengan access point yang lain). Pada percobaan kali ini, ESP32 digunakan sebagai client. Untuk menjadikan ESP32 sebagai client, mode pada program yang digunakan yaitu WIFI_STA

```c
void setup() {
 Serial.begin(115200);
 WiFi.mode(WIFI_STA); // mode akses station
 WiFi.disconnect(); // untuk memutus koneksi dengan access point sebelumnya
 delay(100);
 Serial.println("Setup done");
}
```
![image](https://user-images.githubusercontent.com/118667288/210914639-c2eaa0db-3fc6-44ad-90a5-2c2fc243719c.png)


B. Menghubungkan ESP32 dengan Jaringan WiFi

Pada percobaan kali ini, ESP32 digunakan sebagai client dan terhubung ke suatu jaringan WiFi. Seperti pada percobaan A. ESP32 Wi-Fi Modes dan Wifi-Scan, untuk percobaan kedua program ditambahkan informasi mengenai jaringan yang akan disambung.

```c
#include <WiFi.h>
const char* ssid = "ka"; // SSID atau nama jaringan WiFi yang akan disambungkan
const char* password = "123456788"; // password WiFi
void initWiFi() {
 WiFi.mode(WIFI_STA); // perintah untuk mode akses client
 WiFi.begin(ssid, password); // perintah untuk connect berdasarkan informasi SSID dan password yang sudah diberikan
 Serial.print("Connecting to WiFi ..");
 while (WiFi.status() != WL_CONNECTED) {
 Serial.print('.');
 delay(1000);
 }
Serial.println(WiFi.localIP());
}
```
![image](https://user-images.githubusercontent.com/118667288/210914918-d1d72905-b24f-4888-8a23-524d9105e958.png)

C. Menghubungkan Kembali (Re-connect) ESP32 dengan Jaringan Wi-Fi

Melanjutkan dari percobaan sebelumnya, pada percobaan kali ini ESP32 digunakan sebagai client dan terhubung ke suatu jaringan WiFi. Seperti pada percobaan B. Menghubungkan ESP32 dengan Jaringan WiFi, untuk percobaan ketiga program ditambahkan perintah untuk melakukan rekoneksi ketika jaringan terputus. Pada percobaan B ketika jaringan terputus maka ESP32 tidak akan melakukan rekoneksi karena belum terdapat perintah untuk rekoneksi, untuk percobaan ini ditambahkan perintah untuk melakukan rekoneksi.

```c
void loop() {
 unsigned long currentMillis = millis();
 // if WiFi is down, try reconnecting every CHECK_WIFI_TIME seconds
 if ((WiFi.status() != WL_CONNECTED) && (currentMillis - previousMillis >=interval)) {
   Serial.print(millis());
   Serial.println("Reconnecting to WiFi...");
   WiFi.disconnect();
   WiFi.reconnect();
   previousMillis = currentMillis;
 }
 ```
 ![image](https://user-images.githubusercontent.com/118667288/210915219-c9919d70-f1bf-4fa1-a60d-2cc2d3bff3e7.png)

D. Mengganti Hostname ESP32
Melanjutkan dari percobaan sebelumnya, pada percobaan ini hanya ditambahkan perintah untuk mengubah hostname atau nama ESP32 yang terlihat pada jaringan. Dari program sebelumnya hanya ditambahkan baris perintah untuk informasi nama hostname dan baris perintah inisialisasi.

```c
const char* ssid = "ka";
const char* password = "123456788";
String hostname = "ESP32 Node Temperature"; // informasi nama hostname yang akan digunakan
void initWiFi() {
WiFi.mode(WIFI_STA);
WiFi.config(INADDR_NONE, INADDR_NONE, INADDR_NONE, INADDR_NONE);
WiFi.setHostname(hostname.c_str()); // inisialisasi hostname
WiFi.begin(ssid, password);
Serial.print("Connecting to WiFi ..");
while (WiFi.status() != WL_CONNECTED) {
Serial.print('.');
delay(1000);
}
Serial.println(WiFi.localIP());
}
```
![image](https://user-images.githubusercontent.com/118667288/210915312-31640fff-f6b8-4185-95f1-047dfdf9a73a.png)

E. Mengirim Data Sensor ke Database

Pada percobaan kali ini, dilakukan percobaa mengirim data sendor ke database melalui jaringan WiFi. Metode penyambungan ke jaringan WiFi menggunakan seperti pada percobaan sebelumnya. Namun pada percobaan ini ditambahkan sensor untuk dikirimkan ke database.

```c
#include <WiFi.h> // library untuk menggunakan WiFi
#include <ESPAsyncWebServer.h> // library untuk web server
#include <Adafruit_Sensor.h> // library untuk mengirim data sensor
#include <DHT.h> // library untuk membaca sensor
```
![image](https://user-images.githubusercontent.com/118667288/210915481-9f399163-d145-44b3-9143-a99c93bcfb3a.png)

## HASIL PERCOBAAN

A.	ESP32 Wi-Fi Modes dan Wifi-Scan
<details>
  <summary>Program (click to open)</summary>

```c
#include "WiFi.h"
void setup() {
  Serial.begin(115200);
  // Set WiFi to station mode and disconnect from an AP if it was previously connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  Serial.println("Setup done");
}
void loop() {
  Serial.println("scan start");
  // WiFi.scanNetworks will return the number of networks found
  int n = WiFi.scanNetworks();
  Serial.println("scan done");
  if (n == 0) {
  Serial.println("no networks found");
  } else {
    Serial.print(n);
    Serial.println(" networks found");
    for (int i = 0; i < n; ++i) {
      // Print SSID and RSSI for each network found
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));
      Serial.print(")");
      Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN)?" ":"*");
      delay(10);
      }
  }
  Serial.println("");
  // Wait a bit before scanning again
  delay(5000);
}
```
</details>
 
 
*Serial Monitor*
![js3.1](https://raw.githubusercontent.com/llaurensius/pratikum-sistemembeded-2223/main/jobsheet-3/js3.1/3.1.jpg)

B. Menghubungkan ESP32 dengan Jaringan WiFi
<details>
  <summary>Program (click to open)</summary>
 
 ```c
    #include <WiFi.h>
    // Replace with your network credentials (STATION)
    const char* ssid = "ka";
    const char* password = "123456788";
    void initWiFi() {
      WiFi.mode(WIFI_STA);
      WiFi.begin(ssid, password);
      Serial.print("Connecting to WiFi ..");
      while (WiFi.status() != WL_CONNECTED) {
      Serial.print('.');
      delay(1000);
      }
    Serial.println(WiFi.localIP());
    }
    void setup() {
      Serial.begin(115200);
      initWiFi();
      Serial.print("RRSI: ");
      Serial.println(WiFi.RSSI());
      }
    void loop() {
     // put your main code here, to run repeatedly:
    }
```
</details>
 
 
*Serial Monitor*
![js3.2](https://raw.githubusercontent.com/llaurensius/pratikum-sistemembeded-2223/main/jobsheet-3/js3.2/3.2.jpg)

C.	Menghubungkan Kembali (Re-connect) ESP32 dengan Jaringan Wi-Fi
<details>
  <summary>Program (click to open)</summary>
 
```c
#include <WiFi.h>

// Replace with your network credentials (STATION)
const char* ssid = "ka";
const char* password = "123456788";

unsigned long previousMillis = 0;
unsigned long interval = 30000;

void initWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());
}

void setup() {
  Serial.begin(115200);
  initWiFi();
  Serial.print("RSSI: ");
  Serial.println(WiFi.RSSI());
}

void loop() {
  unsigned long currentMillis = millis();
  // if WiFi is down, try reconnecting every CHECK_WIFI_TIME seconds
  if ((WiFi.status() != WL_CONNECTED) && (currentMillis - previousMillis >=interval)) {
    Serial.print(millis());
    Serial.println("Reconnecting to WiFi...");
    WiFi.disconnect();
    WiFi.reconnect();
    previousMillis = currentMillis;
  }
}
```
</details>
 
*Serial Monitor*
![js3.3](https://raw.githubusercontent.com/llaurensius/pratikum-sistemembeded-2223/main/jobsheet-3/js3.3/js3.3.jpg)

D.	Mengganti Hostname ESP32
<details>
  <summary>Program (click to open)</summary>
 
```c
#include <WiFi.h>
// Replace with your network credentials (STATION)
const char* ssid = "ka";
const char* password = "123456788";
String hostname = "ESP32 Node Temperature";
void initWiFi() {
 WiFi.mode(WIFI_STA);
 WiFi.config(INADDR_NONE, INADDR_NONE, INADDR_NONE, INADDR_NONE);
 WiFi.setHostname(hostname.c_str()); //define hostname
 //wifi_station_set_hostname( hostname.c_str() );
 WiFi.begin(ssid, password);
 Serial.print("Connecting to WiFi ..");
 while (WiFi.status() != WL_CONNECTED) {
 Serial.print('.');
 delay(1000);
 }
 Serial.println(WiFi.localIP());
}
void setup() {
 Serial.begin(115200);
 initWiFi();
 Serial.print("RRSI: ");
 Serial.println(WiFi.RSSI());
}
void loop() {
 // put your main code here, to run repeatedly:
}
```
</details>
 
*Hasil*<br /><br />
![js3.4](https://raw.githubusercontent.com/llaurensius/pratikum-sistemembeded-2223/main/jobsheet-3/js3.4/js3.4.jpg)

E.	Mengirim Data Sensor ke Database<br /><br />
<details>
  <summary>Program (click to open)</summary>
 
```c
// Import required libraries
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
// Replace with your network credentials
const char* ssid = "ka";
const char* password = "123456788";
#define DHTPIN 32 // Digital pin connected to the DHT sensor
// Uncomment the type of sensor in use:
#define DHTTYPE DHT11 // DHT 11
DHT dht(DHTPIN, DHTTYPE);
// Create AsyncWebServer object on port 80
AsyncWebServer server(80);
String readDHTTemperature() {
 // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
 // Read temperature as Celsius (the default)
 float t = dht.readTemperature();
 // Read temperature as Fahrenheit (isFahrenheit = true)
 //float t = dht.readTemperature(true);
 // Check if any reads failed and exit early (to try again).
 if (isnan(t)) {
 Serial.println("Failed to read from DHT sensor!");
 return "--";
 }
 else {
 Serial.println(t);
 return String(t);
}
}
String readDHTHumidity() {
 // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
 float h = dht.readHumidity();
 if (isnan(h)) {
 Serial.println("Failed to read from DHT sensor!");
 return "--";
 }
 else {
 Serial.println(h);
 return String(h);
 }
}
```
```html
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
 <meta name="viewport" content="width=device-width, initial-scale=1">
 <link rel="stylesheet" href="https://use.fontawesome.com/releases/v5.7.2/css/all.css"
 integrity="sha384-
 fnmOCqbTlWIlj8LyTjo7mOUStjsKC4pOpQbqyi7RrhN7udi9RwhKkMHpvLbHG9Sr"
 crossorigin="anonymous">
  <style>
   html {
   font-family: Arial;
   display: inline-block;
   margin: 0px auto;
   text-align: center;
   }
   h2 { font-size: 3.0rem; }
   p { font-size: 3.0rem; }
   .units { font-size: 1.2rem; }
   .dht-labels{
   font-size: 1.5rem;
   vertical-align:middle;
   padding-bottom: 15px;
   }
  </style>
</head>
<body>
 <h2>ESP32 DHT Server</h2>
 <p>
 <i class="fas fa-thermometer-half" style="color:#059e8a;"></i>
 <span class="dht-labels">Temperature</span>
 <span id="temperature">%TEMPERATURE%</span>
 <sup class="units">&deg;C</sup>
 </p>
 <p>
 <i class="fas fa-tint" style="color:#00add6;"></i>
 <span class="dht-labels">Humidity</span>
 <span id="humidity">%HUMIDITY%</span>
 <sup class="units">&percnt;</sup>
 </p>
</body>
<script>
 setInterval(function ( ) {
 var xhttp = new XMLHttpRequest();
 xhttp.onreadystatechange = function() {
 if (this.readyState == 4 && this.status == 200) {
 document.getElementById("temperature").innerHTML = this.responseText;
 }
 };
 xhttp.open("GET", "/temperature", true);
 xhttp.send();
 }, 10000 ) ;
 setInterval(function ( ) {
 var xhttp = new XMLHttpRequest();
 xhttp.onreadystatechange = function() {
 if (this.readyState == 4 && this.status == 200) {
 document.getElementById("humidity").innerHTML = this.responseText;
 }
 };
 xhttp.open("GET", "/humidity", true);
 xhttp.send();
 }, 10000 ) ;
</script>
</html>)rawliteral";
```
```c
// Replaces placeholder with DHT values
String processor(const String& var){
 //Serial.println(var);
 if(var == "TEMPERATURE"){
 return readDHTTemperature();
 }
 else if(var == "HUMIDITY"){
 return readDHTHumidity();
 }
 return String();
}
void setup(){
 // Serial port for debugging purposes
 Serial.begin(115200);
 dht.begin();

 // Connect to Wi-Fi
 WiFi.begin(ssid, password);
 while (WiFi.status() != WL_CONNECTED) {
 delay(1000);
 Serial.println("Connecting to WiFi..");
 }
 // Print ESP32 Local IP Address
 Serial.println(WiFi.localIP());
 // Route for root / web page
 server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
 request->send_P(200, "text/html", index_html, processor);
 });
 server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest *request){
 request->send_P(200, "text/plain", readDHTTemperature().c_str());
 });
 server.on("/humidity", HTTP_GET, [](AsyncWebServerRequest *request){
 request->send_P(200, "text/plain", readDHTHumidity().c_str());
 });
 // Start server
 server.begin();
}
void loop(){

}
```
</details>
 

## Kesimpulan
Melalui percobaan ini dapat disimpulkan bawha:

1. ESP32 dapat dihubungkan melalui WiFi dan memiliki 3 mode akses yaitu yaitu WIFI_STA (station mode : ESP32 sebagai client yang terkoneksi ke access point), WIFI_AP (access point mode : ESP32 berperan sebagai access point), WIFI_STA_AP (access point and station : ESP32 dapat terkoneksi dengan access point yang lain).
2. Data-data informasi dapat dikirimkan ke web server melalui WiFi.
3. Kelemahan menggunakan WiFi adalah ESP32 hanya bisa diakses melalui jaringan WiFi yang sama
 
## Tugas
 
 ![image](https://user-images.githubusercontent.com/118667288/210915688-f7bffe0c-b673-4123-ac8c-6a7943e13a1c.png)
 ```
 ```c
 #include <Arduino.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>
#include "SPIFFS.h"

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

// Search for parameter in HTTP POST request
const char* PARAM_INPUT_1 = "ssid";
const char* PARAM_INPUT_2 = "pass";
const char* PARAM_INPUT_3 = "ip";
const char* PARAM_INPUT_4 = "gateway";


//Variables to save values from HTML form
String ssid;
String pass;
String ip;
String gateway;

// File paths to save input values permanently
const char* ssidPath = "/ssid.txt";
const char* passPath = "/pass.txt";
const char* ipPath = "/ip.txt";
const char* gatewayPath = "/gateway.txt";

IPAddress localIP;
//IPAddress localIP(192, 168, 1, 200); // hardcoded

// Set your Gateway IP address
IPAddress localGateway;
//IPAddress localGateway(192, 168, 1, 1); //hardcoded
IPAddress subnet(255, 255, 0, 0);

// Timer variables
unsigned long previousMillis = 0;
const long interval = 10000;  // interval to wait for Wi-Fi connection (milliseconds)

// Set LED GPIO
const int ledPin = 2;
// Stores LED state

String ledState;

// Initialize SPIFFS
void initSPIFFS() {
  if (!SPIFFS.begin(true)) {
    Serial.println("An error has occurred while mounting SPIFFS");
  }
  Serial.println("SPIFFS mounted successfully");
}

// Read File from SPIFFS
String readFile(fs::FS &fs, const char * path){
  Serial.printf("Reading file: %s\r\n", path);

  File file = fs.open(path);
  if(!file || file.isDirectory()){
    Serial.println("- failed to open file for reading");
    return String();
  }
  
  String fileContent;
  while(file.available()){
    fileContent = file.readStringUntil('\n');
    break;     
  }
  return fileContent;
}

// Write file to SPIFFS
void writeFile(fs::FS &fs, const char * path, const char * message){
  Serial.printf("Writing file: %s\r\n", path);

  File file = fs.open(path, FILE_WRITE);
  if(!file){
    Serial.println("- failed to open file for writing");
    return;
  }
  if(file.print(message)){
    Serial.println("- file written");
  } else {
    Serial.println("- frite failed");
  }
}

// Initialize WiFi
bool initWiFi() {
  if(ssid=="" || ip==""){
    Serial.println("Undefined SSID or IP address.");
    return false;
  }

  WiFi.mode(WIFI_STA);
  localIP.fromString(ip.c_str());
  localGateway.fromString(gateway.c_str());


  if (!WiFi.config(localIP, localGateway, subnet)){
    Serial.println("STA Failed to configure");
    return false;
  }
  WiFi.begin(ssid.c_str(), pass.c_str());
  Serial.println("Connecting to WiFi...");

  unsigned long currentMillis = millis();
  previousMillis = currentMillis;

  while(WiFi.status() != WL_CONNECTED) {
    currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
      Serial.println("Failed to connect.");
      return false;
    }
  }

  Serial.println(WiFi.localIP());
  return true;
}

// Replaces placeholder with LED state value
String processor(const String& var) {
  if(var == "STATE") {
    if(digitalRead(ledPin)) {
      ledState = "ON";
    }
    else {
      ledState = "OFF";
    }
    return ledState;
  }
  return String();
}

void setup() {
  // Serial port for debugging purposes
  Serial.begin(115200);

  initSPIFFS();

  // Set GPIO 2 as an OUTPUT
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  
  // Load values saved in SPIFFS
  ssid = readFile(SPIFFS, ssidPath);
  pass = readFile(SPIFFS, passPath);
  ip = readFile(SPIFFS, ipPath);
  gateway = readFile (SPIFFS, gatewayPath);
  Serial.println(ssid);
  Serial.println(pass);
  Serial.println(ip);
  Serial.println(gateway);

  if(initWiFi()) {
    // Route for root / web page
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
      request->send(SPIFFS, "/index.html", "text/html", false, processor);
    });
    server.serveStatic("/", SPIFFS, "/");
    
    // Route to set GPIO state to HIGH
    server.on("/on", HTTP_GET, [](AsyncWebServerRequest *request) {
      digitalWrite(ledPin, HIGH);
      request->send(SPIFFS, "/index.html", "text/html", false, processor);
    });

    // Route to set GPIO state to LOW
    server.on("/off", HTTP_GET, [](AsyncWebServerRequest *request) {
      digitalWrite(ledPin, LOW);
      request->send(SPIFFS, "/index.html", "text/html", false, processor);
    });
    server.begin();
  }
  else {
    // Connect to Wi-Fi network with SSID and password
    Serial.println("Setting AP (Access Point)");
    // NULL sets an open Access Point
    WiFi.softAP("ESP-WIFI-MANAGER", NULL);

    IPAddress IP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(IP); 

    // Web Server Root URL
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
      request->send(SPIFFS, "/wifimanager.html", "text/html");
    });
    
    server.serveStatic("/", SPIFFS, "/");
    
    server.on("/", HTTP_POST, [](AsyncWebServerRequest *request) {
      int params = request->params();
      for(int i=0;i<params;i++){
        AsyncWebParameter* p = request->getParam(i);
        if(p->isPost()){
          // HTTP POST ssid value
          if (p->name() == PARAM_INPUT_1) {
            ssid = p->value().c_str();
            Serial.print("SSID set to: ");
            Serial.println(ssid);
            // Write file to save value
            writeFile(SPIFFS, ssidPath, ssid.c_str());
          }
          // HTTP POST pass value
          if (p->name() == PARAM_INPUT_2) {
            pass = p->value().c_str();
            Serial.print("Password set to: ");
            Serial.println(pass);
            // Write file to save value
            writeFile(SPIFFS, passPath, pass.c_str());
          }
          // HTTP POST ip value
          if (p->name() == PARAM_INPUT_3) {
            ip = p->value().c_str();
            Serial.print("IP Address set to: ");
            Serial.println(ip);
            // Write file to save value
            writeFile(SPIFFS, ipPath, ip.c_str());
          }
          // HTTP POST gateway value
          if (p->name() == PARAM_INPUT_4) {
            gateway = p->value().c_str();
            Serial.print("Gateway set to: ");
            Serial.println(gateway);
            // Write file to save value
            writeFile(SPIFFS, gatewayPath, gateway.c_str());
          }
          //Serial.printf("POST[%s]: %s\n", p->name().c_str(), p->value().c_str());
        }
      }
      request->send(200, "text/plain", "Done. ESP will restart, connect to your router and go to IP address: " + ip);
      delay(3000);
      ESP.restart();
    });
    server.begin();
  }
}

void loop() {

}
 ``` 
 ![image](https://user-images.githubusercontent.com/118667288/210915805-02f67678-ec5b-4230-b18f-cd073c253b27.png)
 

 ![image](https://user-images.githubusercontent.com/118667288/210915837-a409fd80-4606-4b6c-8285-aa951892c225.png)
```
 
 ## AP MODE
 
 
 ![image](https://user-images.githubusercontent.com/118667288/210916044-2d483aed-6882-45e3-a6fd-b4e3970fd6f2.png)
```
 
 ## STATION MODE


 ![image](https://user-images.githubusercontent.com/118667288/210916099-c5ac27e3-5597-4228-9d74-11c3f611b9b3.png)
 ```

