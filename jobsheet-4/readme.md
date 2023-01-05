
# Jobsheet 4 
Cayenne (MQTT) + SENSOR (DHT11) + LED (ON/OFF) + BUTTON di website monitoring



## Anggota Kelompok

- Hanif Nugraha Ramadhan
- Muhammad Rafif Hasani

## Skematik
![image](https://user-images.githubusercontent.com/118155742/210129902-f24a85d2-176a-4027-9952-b82e8edb55d9.png)


## Analisa
Dalam percobaan kali ini menggunakan ESP32 yang terpasang sensor DHT11 berfungsi untuk membaca Suhu dan Temperature kemudian diteruskan oleh ESP32 melalui protokol MQTT (Cayenne) untuk agar bisa terhubung dan berkomunikasi antar mesin.

Library yang dibutuhkan adalah 
```c
#include "CayenneMQTTESP32.h" // library Cayenne untuk MQTT
#include "DHT.h" // library DHT
```

Kemudian mendefinisikan beberapa yang dibutuhkan seperti pin GPIO DHT akan disambungkan ke pin 4 di ESP32 lalu memilih tipe DHT lalu memilih pin GPIO untuk keluaran LED di pin 16.
```c
#define CAYENNE_PRINT Serial
#define DHTPIN 4     // what digital pin we're connected to
#define DHTTYPE DHT11   // DHT 11
const int ledPin = 16;
```

Lalu ESP memerlukan koneksi ke internet melalui WIFI yang ada dan autentifikasi ke Cayenne dengan memasukan username, password, dan clientID.
```c
// WiFi network info.
char ssid[] = "home-mnl";
char wifiPassword[] = "h0m3-121";

// Cayenne authentication info. This should be obtained from the Cayenne Dashboard.
char username[] = "9f1901b0-7f54-11ed-b193-d9789b2af62b";
char password[] = "15d7c1af5defe0be2d748a44ebec74251ae13b9e";
char clientID[] = "82f43c00-8749-11ed-b193-d9789b2af62b";
```

 menginisiasi DHT berada di pin GPIO berapa dan tipe DHT nya
```c
DHT dht(DHTPIN, DHTTYPE);
```

```c
// Memulai sebuah fungsi yang dijalankan sekali dengan lalu lintas data berada pada 9600 baud rate.
void setup() {
  Serial.begin(9600);
  dht.begin(); //Memulai DHT
  Cayenne.begin(username, password, clientID, ssid, wifiPassword); // mengautentifikasi ke Cayenne agar dapat terhubung
  pinMode(ledPin, OUTPUT); // menginisiasi LED berapa di pin dan berfungsi sebagai output
  digitalWrite(ledPin, LOW); // memberikan perintah led untuk nilai 'LOW'
}
```

Fungsi dibagian void loop adalah untuk membaca nilai sensor DHT 11
```c
float h, t, f; 
void loop() {
  Cayenne.loop(); // memerintahkan untuk fungsi Cayenne bekerja secara berulang-ulang

  h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

}

```

Fungsi di bawah ini adalah untuk mengirimkan data nilai sensor DHT11 dan mengambil nilai button yang berada di Cayenne
```c
//Mengirimkan data ke MQTT Cayenne dan menampilkannya di Dashboard Aplikasi Cayenne
CAYENNE_OUT(1)
{
  CAYENNE_LOG("Send data for Virtual Channel %d Suhu %f C", 1, t);
  Cayenne.celsiusWrite(1, t);
}
CAYENNE_OUT(2)
{
  CAYENNE_LOG("Send data for Virtual Channel %d Hum %f ", 2, h);
  Cayenne.virtualWrite(2, h);
}
CAYENNE_IN(3)
{
  digitalWrite(ledPin, !getValue.asInt());  // to get the value from the website
}
```


# Kesimpulan
Dalam pratikum ini disimpulkan bahwa ESP32 dapat digunakan untuk perangkat IoT yang terhubung ke internet sehingga user dapat kontrol perangkat ESP32 dalam jarah jauh dengan syarat ESP32 selalu terhubung dengan internet dan terhubung ke broker MQTT (dalam pratikum ini menggunakan Cayenne).

Pratikum ini contoh dengan membaca sensor DHT11 yang dikirimkan ke Cayenne dan Cayenne mengirimkan sebuah nilai (0/1) untuk memberikan perintah ESP32 untuk menghidupkan LED.
# Dokumentasi
## ESP32 + MQTT (Cayenne) + Sensor Temperature, Humidity (DHT11) + LED (Output)

https://user-images.githubusercontent.com/121760251/210358473-1bae9070-5118-448c-a296-1a2ef45dc1a3.mp4

# ESP Now + IOT
## Koding
```
 #include <esp_now.h>
#include <WiFi.h>
#include "DHT.h"
#define DHTPIN 4
#define DHTTYPE DHT11

uint8_t broadcastAddress[] = {0x94, 0xB5, 0x55, 0x2C, 0x47, 0xB4};
const int espNumber = 1;

typedef struct struct_message {
  int id;
  float temp;
  float hum;
} struct_message;
struct_message myData;
esp_now_peer_info_t peerInfo;

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

// Variable to hold readings
float temperature;
float humidity;

WiFiClient  client;
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  dht.begin();
  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  esp_now_register_send_cb(OnDataSent);

  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }
}

void loop() {
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  Serial.print("Temperature (ºC): ");
  Serial.print(temperature);
  Serial.print(" Humidity (%): ");
  Serial.println(humidity);

  myData.id = espNumber;
  myData.temp = temperature;
  myData.hum = humidity;
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));

  if (result == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data");
  }

  delay(1000);
}
```
