# Jobsheet 1.1.

JARINGAN SENSOR NIRKABEL MENGGUNAKAN ESP-NOW



## Anggota Kelompok

- [Hanif Nugraha Ramadhan]
- [M Rafif Hasani]


## A. Memperoleh MAC Address ESP32 Receiver
1. Buka Arduino IDE
2. Kemudian ketikkan script program berikut di Arduino IDE
3. Upload program tersebut ke ESP32.
4. Setelah program berhasil diupload, buka serial monitor.
5. Catat Mac Address ESP32.


# Analisa
Dalam koding ini berfungsi untuk mengetahui MAC Address yang terdapat di ESP32
```
#include "WiFi.h" //library yang digunakan hanya WiFi.h
void setup(){
Serial.begin(115200);
WiFi.mode(WIFI_MODE_STA); //mengaktifkan mode WiFi Station
Serial.println(WiFi.macAddress()); //print MAC Address di Serial Monirot
}
void loop(){ 
}
```


# Kesimpulan
MAC Address diperlukan untuk identifikasi perangkat ESP32 dalam protokol komunikasi ESP-NOW, dengan MAC Address kita bisa mengirim data ke ESP32 lainnya melalui protokol ESP-NOW


# Dokumentasi
![MAC ADDRESS](https://user-images.githubusercontent.com/118155742/210126557-2fee30cf-cfcf-4cdf-b783-71a9ca477aa7.png)




## B. ESP-NOW One-Way Point-to-Point Communication
## Transmitter
```
//library yang dibutuhkan
#include <esp_now.h>
#include <WiFi.h>

// MAC Address Koordinator ESP
uint8_t broadcastAddress[] = {0x78, 0x21, 0x84, 0xBB, 0x45, 0xB8}; //78:21:84:BB:45:B8

//Struktur yang digunakan untuk transfer data, harus sama antara transmitter dan receiver
typedef struct struct_message {
  char a[32];
  int b;
  float c;
  bool d;
} struct_message;

// membuat struktur dengan nama myData
struct_message myData;

// membuat interface peer
esp_now_peer_info_t peerInfo;

// memberikan feedback apabila data berhasil dikirimkan
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}
 
void setup() {
  // inisialisasi Serial Monitor
  Serial.begin(115200);
 
  // membuat sebagai mode WiFi station
  WiFi.mode(WIFI_STA);

  // inisialisasi ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // mendapatkan status dari paket yang dikirim
  esp_now_register_send_cb(OnDataSent);
  
  // Register peer
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  
  // menambah peer        
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
}
 
void loop() {
  //memberikan data yang akan dikirim
  strcpy(myData.a, "THIS IS A CHAR");
  myData.b = random(1,20);
  myData.c = 1.2;
  myData.d = false;
  
  // mengirim data melalui ESP-NOW
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
   
  if (result == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data");
  }
  delay(2000);
}
```

## Receiver
```
//library yang digunakan
#include <esp_now.h> 
#include <WiFi.h>

// Struktur pesan yang akan dikirim, struktur harus sama 
typedef struct struct_message {
char a[32]; 
int b; 
float c; 
bool d;
} struct_message;

// membuat variabel struktur menjadi myData 
struct_message myData;

// fungsi callback yang akan dieksekusi ketika ada pesan diterima
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) { 
memcpy(&myData, incomingData, sizeof(myData));
Serial.print("Bytes received: ");
Serial.println(len);
Serial.print("Char: ");
Serial.println(myData.a);
Serial.print("Int: ");
Serial.println(myData.b);
Serial.print("Float: ");
Serial.println(myData.c);
Serial.print("Bool: ");
Serial.println(myData.d);
Serial.println(); 
}
void setup() {
// Initialize Serial Monitor 
Serial.begin(115200);
// Set ESP32 sebagai station 
WiFi.mode(WIFI_STA);
// Init ESP-NOW
if (esp_now_init() != ESP_OK) {
Serial.println("Error initializing ESP-NOW"); 
return;
}
// Fungsi akses register cb untuk proses penerimaan data 
esp_now_register_recv_cb(OnDataRecv);
}
void loop() { 
}
```
# Kesimpulan
Dalam pratikum ini dibuktikan bahwa komunikasi berjalan satu arah dimana ESP32 sender akan mengirimkan data ke ESP32 Koordinator dan diuji coba pula dengan jarak yang tidak terlalu jauh dan kondisi LOSS komunikasi ESP berjalan dengan baik tanpa mengalami gagal pengiriman.


# Dokumentasi
![rx]()
![tx]()
![rx tx]()

## C. One-Way, One-to-Many Communication

A. Mengirim Pesan yang Sama Ke Beberapa Board ESP32

Koding 

 ## Transmitter
 ```
 
 //Library yang dibutuhkan
#include <esp_now.h>
#include <WiFi.h>

//MAC Address tujuan yang akan dikirim, terdapat beberapa MAC Address karena pratikum ini mencoba untuk mengirim di beberapa Board
// REPLACE WITH YOUR ESP RECEIVER'S MAC ADDRESS
uint8_t broadcastAddress1[] = {0x24, 0x6F, 0x28, 0x02, 0xC3, 0x1C}; //24:6F:28:02:C3:1C
uint8_t broadcastAddress2[] = {0x24, 0x0A, 0xC4, 0XC6, 0x06, 0x54}; //24:0A:C4:C6:06:54
uint8_t broadcastAddress3[] = {0x8C, 0xCE, 0x4E, 0xC8, 0x29, 0x1B}; //8C:CE:4E:C8:29:1B

//Membuat struktur data yang akan dikirimkan, data dalam struktur ini ada 2 variabel dan dapat ditambah sesuai dengan keinginan.
typedef struct test_struct {
  int x;
  int y;
} test_struct;

//Membuat struktur data dengan nama myData
test_struct myData;

//Membuat variabel dengan tipe esp_now_peer_info_t untuk mengumpulkan informasi tentang peer
esp_now_peer_info_t peerInfo;

//Berfungsi ketika eksekusi data yang dikirimkan. Dalam fungsi ini ketika pesan berhahsil terkirim maka akan tampil jawaban di serial monitor pengirim.
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  char macStr[18];
  Serial.print("Packet to: ");
  // Copies the sender mac address to a string
  snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
           mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
  Serial.print(macStr);
  Serial.print(" send status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}
 
void setup() {
  Serial.begin(115200); //Inisialisasi serial monitor untuk keperluan debugging
 
  WiFi.mode(WIFI_STA); //Inisialisasi perangkat ESP32 sebagai WiFi Station
 
  //Inisialisasi ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  //Ketika inisialisasi ESP-Now sukses maka akan diarahkan ke fungsi OnDataSent yang telah dibuat diatas.
  esp_now_register_send_cb(OnDataSent);
   
  //Menambahkan peer
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  //Regrister perangkat EPS lain yang pertama 
  memcpy(peerInfo.peer_addr, broadcastAddress1, 6);
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
  //Regrister perangkat EPS lain yang kedua
  memcpy(peerInfo.peer_addr, broadcastAddress2, 6);
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
  //Regrister perangkat EPS lain yang ketiga
  memcpy(peerInfo.peer_addr, broadcastAddress3, 6);
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
}
 
void loop() {
  //Data yang akan dikirimkan berupa data random mulai dari 0-20
  test.x = random(0,20);
  test.y = random(0,20);
 
  //Mengirimkan data ke beberapa board
  esp_err_t result = esp_now_send(0, (uint8_t *) &test, sizeof(test_struct));
   
  //Fungsi untuk mengecek data di atas apakah sudah terkirim
  if (result == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data");
  }
  delay(2000); //Jeda loop selama 2 detik
}

## Receiver 
```
//Menambahkan library yang digunakan
#include <esp_now.h> 
#include <WiFi.h>

//Struktur untuk menerima data, harus sama dengan transmitter
typedef struct test_struct {
int x; 
int y;
} test_struct;

//Membuat struktur data dengan nama myData 
test_struct myData;

//Membuat fungsi callback yang memberitahu data yang diterima
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) { 
memcpy(&myData, incomingData, sizeof(myData));
Serial.print("Bytes received: ");
Serial.println(len);
Serial.print("x: ");
Serial.println(myData.x);
Serial.print("y: ");
Serial.println(myData.y);
Serial.println(); 
}
void setup() {
//Inisialisasi serial monitor untuk debugging
Serial.begin(115200);

//Membuat ESP32 sebagai WiFi Station
WiFi.mode(WIFI_STA);

//Inisialisasi ESP-NOW
if (esp_now_init() != ESP_OK) {
  Serial.println("Error initializing ESP-NOW"); 
return;
}

//Ketika ESP-Now berhasil maka akan menerima data dari transmitter
esp_now_register_recv_cb(OnDataRecv); 
}
void loop() { 
}





## E. Two-Way Communication
# Koding

```
#include <esp_now.h>
#include <WiFi.h>
#include <DHT.h>
#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
// REPLACE WITH THE MAC Address of your receiver
uint8_t broadcastAddress[] = {0x78, 0x21, 0x84, 0xBB, 0x3A, 0x94};
// Define variables
float temperature;
float humidity;
// Define variables to store incoming readings
float incomingTemp;
float incomingHum;
// Variable to store if sending data was successful
String success;
//Structure example to send data
//Must match the receiver structure
typedef struct struct_message {
 float temp;
 float hum;
} struct_message;
// Create a struct_message sensors reading
struct_message DHTReadings;
// Create a struct_message to hold incoming sensor readings
struct_message incomingReadings;
esp_now_peer_info_t peerInfo;
// Callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
 Serial.print("\r\nLast Packet Send Status:\t");
 Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
 if (status ==0){
 success = "Delivery Success :)";
 }
 else{
 success = "Delivery Fail :(";
 }
}
// Callback when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
 memcpy(&incomingReadings, incomingData, sizeof(incomingReadings));
 Serial.print("Bytes received: ");
 Serial.println(len);
 incomingTemp = incomingReadings.temp;
 incomingHum = incomingReadings.hum;
}
void setup() {
 // Init Serial Monitor
 Serial.begin(115200);
 // Init DHT
 dht.begin();
 // Set device as a Wi-Fi Station
 WiFi.mode(WIFI_STA);
 // Init ESP-NOW
 if (esp_now_init() != ESP_OK) {
 Serial.println("Error initializing ESP-NOW");
 return;
 }
 // Once ESPNow is successfully Init, we will register for Send CB to
 // get the status of Trasnmitted packet
 esp_now_register_send_cb(OnDataSent);

 // Register peer
 memcpy(peerInfo.peer_addr, broadcastAddress, 6);
 peerInfo.channel = 0;
 peerInfo.encrypt = false;

 // Add peer
 if (esp_now_add_peer(&peerInfo) != ESP_OK){
 Serial.println("Failed to add peer");
 return;
 }
 // Register for a callback function that will be called when data is received
 esp_now_register_recv_cb(OnDataRecv);
}
void loop() {
 delay(2000);
 getReadings();
 // Set values to send
 DHTReadings.temp = temperature;
 DHTReadings.hum = humidity;
 // Send message via ESP-NOW
 esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &DHTReadings,
sizeof(DHTReadings));

 if (result == ESP_OK) {
 Serial.println("Sent with success");
 }
 else {
 Serial.println("Error sending the data");
 }

 delay(1000);
}
void getReadings(){
 float t = dht.readTemperature();
 float h = dht.readHumidity();
 float f = dht.readTemperature(true);
 if (isnan(h) || isnan(t) || isnan(f)) {
 Serial.println(F("Failed to read from DHT sensor!"));
 return;
 }
 Serial.print(F("Humidity: "));
 Serial.print(h);
 Serial.print(F("% Temperature: "));
 Serial.print(t);
 Serial.print(F("°C "));
}
```


# Kesimpulan


# Dokumentasi
## Receive
![500000](https://user-images.githubusercontent.com/118155742/210127901-444d1674-53e9-433c-8b2d-fafd67f2d557.jpg)

## Transmitter
![test](https://user-images.githubusercontent.com/118155742/210127905-9a06ed43-51f1-4c68-a107-5ef8157ab890.jpg)
