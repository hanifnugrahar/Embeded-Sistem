
# Jobsheet 2 
PROTOKOL KOMUNIKASI DAN SENSOR

# Anggota Kelompok

- Hanif Nugraha Ramadhan [4.31.20.0.10]
- Muhammad Rafif Hasani  [4.31.20.0.16]


# 1. ESP32 CAPASITIVE TOUCH SENSOR
## PROGRAM
## A-capasitivetouchsensor - Hanya membaca sentuhan yang dilakukan dan menampilkan di serial monitor
```
// ESP32 Touch Test
// Just test touch pin - Touch0 is T0 which is on GPIO 4. 
void setup() {
Serial.begin(115200);
delay(1000); // give me time to bring up serial monitor 
Serial.println("ESP32 Touch Test");
}
void loop() {
Serial.println(touchRead(4));  // menampilkan nilai dari sentuhan yang ada di pin GPIO 4
delay(1000);
}
```


## A-capasitivetouchsensorled1 - Jika disentuh maka LED akan menyala ketika disentuh dan tidak menyala jika tidak disentuh
```
// menginisiasi pin GPIO yang akan dipakai
const int touchPin = 4; //Pin GPIO yang mendeteksi sentuhan
const int ledPin = 16; //Pin GPIO yang akan menyalan LED sebagai keluaran

// change with your threshold value
const int threshold = 20;
// variable for storing the touch pin value 
int touchValue;

void setup(){
  Serial.begin(115200);
  delay(1000); // give me time to bring up serial monitor
  // Inisiasi LED sebagai keluaran
  pinMode (ledPin, OUTPUT);
}

void loop(){
  // membaca sensor sentuhan
  touchValue = touchRead(touchPin);
  Serial.print(touchValue);
  // mengecek apakah ada nilai dari sentuhan
  // jika ada maka LED akan menyala
  if(touchValue < threshold){
    // turn LED on
    digitalWrite(ledPin, HIGH);
    Serial.println(" - LED on");
  }
  else{
    // turn LED off
    digitalWrite(ledPin, LOW);
    Serial.println(" - LED off");
  }
  delay(500);
}
```


## A-capasitivetouchsensorled2 - LED Running
```
// menginisiasi pin GPIO yang akan dipakai
const int touchPin = 4; 
const int ledPin1 = 16;
const int ledPin2 = 18;
const int ledPin3 = 19;

// change with your threshold value
const int threshold = 20;
// variable for storing the touch pin value 
int touchValue;

void setup(){
  Serial.begin(115200);
  delay(1000); // give me time to bring up serial monitor
  // menginisiasi pin GPIO LED sebagai keluaran
  pinMode (ledPin1, OUTPUT);
  pinMode (ledPin2, OUTPUT);
  pinMode (ledPin3, OUTPUT);
}

void loop(){
  // membaca nilai sentuhan
  touchValue = touchRead(touchPin);
  Serial.print(touchValue);
  // mengecek dengan logika IF ELSE dan akan menyalan LED jika terdapat sentuhan
  if(touchValue < threshold){
    // turn LED on
    Serial.println(" - LED on");
    digitalWrite(ledPin1, HIGH);
    delay(500);
    digitalWrite(ledPin1, LOW);
    digitalWrite(ledPin2, HIGH);
    delay(500);
    digitalWrite(ledPin2, LOW);
    digitalWrite(ledPin3, HIGH);
    delay(500);
    digitalWrite(ledPin3, LOW);
       
  }
  else{
    // turn LED off
    digitalWrite(ledPin1, LOW);
digitalWrite(ledPin2, LOW);
digitalWrite(ledPin3, LOW);
    Serial.println(" - LED off");
  }
  delay(500);
}
```
## KESIMPULAN
Pratikum ini memberikan kesimpulan bahwa dalam pemanfaatan ESP32 sebagai mikrokontroller dapat membaca sensor berupa sentuhan kemudian dari sentuhan itu dapat diberikan output dalam contoh ini akan menghidupkan LED dan membuat LED running dari kiri ke kanan.


## DOKUMENTASI

https://user-images.githubusercontent.com/118155742/210125150-58dc840f-62fe-4d66-9bfc-5c341c3bf518.mp4
https://user-images.githubusercontent.com/118155742/210124792-97a59261-6ea1-417b-9615-5e0ab913d949.mp4
![image](https://user-images.githubusercontent.com/118667288/210337068-a70fb23b-e4d1-4585-b815-69f2e67aa409.png)
![image](https://user-images.githubusercontent.com/118667288/210337090-71b93c7e-7c06-42fd-8e42-bb662b11c0aa.png)



# 2. Mengakses Sensor DHT 11 (Single/WIRE BUS)

## PROGRAM

## B-DHT
```

// REQUIRES the following Arduino libraries:
// - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
// - Adafruit Unified Sensor Lib: https://github.com/adafruit/Adafruit_Sensor
#include "DHT.h"
#define DHTPIN 4 // Digital pin connected to the DHT sensor
// Uncomment whatever type you're using!
#define DHTTYPE DHT11 // DHT 11
//#define DHTTYPE DHT22 // DHT 22 (AM2302), AM2321
//#define DHTTYPE DHT21 // DHT 21 (AM2301)
DHT dht(DHTPIN, DHTTYPE);
void setup() {
 Serial.begin(9600);
 Serial.println(F("DHT11 Embedded System Test!"));
 dht.begin();
}
void loop() {
 // Wait a few seconds between measurements.
 delay(2000);
 // Reading temperature or humidity takes about 250 milliseconds!
 // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
 float h = dht.readHumidity();
 // Read temperature as Celsius (the default)
 float t = dht.readTemperature();
 // Read temperature as Fahrenheit (isFahrenheit = true)
 float f = dht.readTemperature(true);
 // Check if any reads failed and exit early (to try again).
 if (isnan(h) || isnan(t) || isnan(f)) {
 Serial.println(F("Failed to read from DHT sensor!"));
 return;
 }
 // Compute heat index in Fahrenheit (the default)
 float hif = dht.computeHeatIndex(f, h);
 // Compute heat index in Celsius (isFahreheit = false)
 float hic = dht.computeHeatIndex(t, h, false);
 
  if(t < 30){
    // turn LED on
    digitalWrite(ledPin, HIGH);
    Serial.println(" - LED on");
  }
  else{
    // turn LED off
    digitalWrite(ledPin, LOW);
    Serial.println(" - LED off");
  }
 
 Serial.print(F("Humidity: "));
 Serial.print(h);
 Serial.print(F("% Temperature: "));
 Serial.print(t);
 Serial.print(F("??C "));
 Serial.print(f);
 Serial.print(F("??F Heat index: "));
 Serial.print(hic);
 Serial.print(F("??C "));
 Serial.print(hif);
 Serial.println(F("??F"));
}

```

## B-DHTBUZZ_LED

``` 
// REQUIRES the following Arduino libraries:
// - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
// - Adafruit Unified Sensor Lib: https://github.com/adafruit/Adafruit_Sensor
#include "DHT.h"
#define DHTPIN 4 // Digital pin connected to the DHT sensor
// Uncomment whatever type you're using!
#define DHTTYPE DHT11 // DHT 11
//#define DHTTYPE DHT22 // DHT 22 (AM2302), AM2321
//#define DHTTYPE DHT21 // DHT 21 (AM2301)
DHT dht(DHTPIN, DHTTYPE);
const int ledPin = 16;

void setup() {
 Serial.begin(9600);
 Serial.println(F("DHT11 Embedded System Test!"));
 dht.begin();
   pinMode (ledPin, OUTPUT);

}
void loop() {
 // Wait a few seconds between measurements.
 delay(2000);
 // Reading temperature or humidity takes about 250 milliseconds!
 // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
 float h = dht.readHumidity();
 // Read temperature as Celsius (the default)
 float t = dht.readTemperature();
 // Read temperature as Fahrenheit (isFahrenheit = true)
 float f = dht.readTemperature(true);
 // Check if any reads failed and exit early (to try again).
 if (isnan(h) || isnan(t) || isnan(f)) {
 Serial.println(F("Failed to read from DHT sensor!"));
 return;
 }
 // Compute heat index in Fahrenheit (the default)
 float hif = dht.computeHeatIndex(f, h);
 // Compute heat index in Celsius (isFahreheit = false)
 float hic = dht.computeHeatIndex(t, h, false);
 
  if(t < 30){
    // turn LED on
    digitalWrite(ledPin, HIGH);
    Serial.println(" - LED on");
  }
  else{
    // turn LED off
    digitalWrite(ledPin, LOW);
    Serial.println(" - LED off");
  }
 
 Serial.print(F("Humidity: "));
 Serial.print(h);
 Serial.print(F("% Temperature: "));
 Serial.print(t);
 Serial.print(F("??C "));
 Serial.print(f);
 Serial.print(F("??F Heat index: "));
 Serial.print(hic);
 Serial.print(F("??C "));
 Serial.print(hif);
 Serial.println(F("??F"));
}
```

## B-DHTBUZZ_LEDRUNNING
```
/ REQUIRES the following Arduino libraries:
// - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
// - Adafruit Unified Sensor Lib: https://github.com/adafruit/Adafruit_Sensor
#include "DHT.h"
#define DHTPIN 4 // Digital pin connected to the DHT sensor
// Uncomment whatever type you're using!
#define DHTTYPE DHT11 // DHT 11
//#define DHTTYPE DHT22 // DHT 22 (AM2302), AM2321
//#define DHTTYPE DHT21 // DHT 21 (AM2301)
DHT dht(DHTPIN, DHTTYPE);
const int ledPin1 = 16;
const int ledPin2 = 18;
const int ledPin3 = 19;

void setup() {
 Serial.begin(9600);
 Serial.println(F("DHT11 Embedded System Test!"));
 dht.begin();
   pinMode (ledPin1, OUTPUT);
   pinMode (ledPin2, OUTPUT);
   pinMode (ledPin3, OUTPUT);

}
void loop() {
 // Wait a few seconds between measurements.
 delay(2000);
 // Reading temperature or humidity takes about 250 milliseconds!
 // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
 float h = dht.readHumidity();
 // Read temperature as Celsius (the default)
 float t = dht.readTemperature();
 // Read temperature as Fahrenheit (isFahrenheit = true)
 float f = dht.readTemperature(true);
 // Check if any reads failed and exit early (to try again).
 if (isnan(h) || isnan(t) || isnan(f)) {
 Serial.println(F("Failed to read from DHT sensor!"));
 return;
 }
 // Compute heat index in Fahrenheit (the default)
 float hif = dht.computeHeatIndex(f, h);
 // Compute heat index in Celsius (isFahreheit = false)
 float hic = dht.computeHeatIndex(t, h, false);
 
  if(t < 30){
Serial.println(" - LED on");
    digitalWrite(ledPin1, HIGH);
    delay(500);
    digitalWrite(ledPin1, LOW);
    digitalWrite(ledPin2, HIGH);
    delay(500);
    digitalWrite(ledPin2, LOW);
    digitalWrite(ledPin3, HIGH);
    delay(500);
    digitalWrite(ledPin3, LOW);
  }
  else{
    // turn LED off
    digitalWrite(ledPin1, LOW);
digitalWrite(ledPin2, LOW);
digitalWrite(ledPin3, LOW);
    Serial.println(" - LED off");
  }
 
 Serial.print(F("Humidity: "));
 Serial.print(h);
 Serial.print(F("% Temperature: "));
 Serial.print(t);
 Serial.print(F("??C "));
 Serial.print(f);
 Serial.print(F("??F Heat index: "));
 Serial.print(hic);
 Serial.print(F("??C "));
 Serial.print(hif);
 Serial.println(F("??F"));
}
```
## KESIMPULAN 

Sensor DHT11 berfungsi untuk membaca kelembapan dan suhu yang dapat di ESP32 untuk mengumpulkan data dan menjadikannya sebuah input untuk sebuah sistem seperti dalam contoh jika suhu dibawah 30?? C maka LED akan berjalan runnning. Sensor DHT11 memiliki delay pembacaan sekitar 2 detik sehingga pembacaan realtime dengan di serial monitor akan mengalami delay. Sensor DHT memiliki beberapa tipe dan tipe yang dipakai dalam pratikum ini adalah DHT11

## DOKUMENTASI 

B-DHT
https://user-images.githubusercontent.com/118667288/210920478-b9fef8bf-9538-4845-a22e-d1df5e2ed956.mp4

B-DHTLED_RUNNING
https://user-images.githubusercontent.com/118155742/210385152-b694ddc9-3420-4c04-ad43-1d4f44853ff2.mp4


# 3. MENGAKSES SENSOR RFID (SPI Communication)

## PROGRAM

Membaca RFID 

```
//Library yang dibutuhkan
#include <SPI.h>
#include <MFRC522.h>

//Inisialisasi pin untuk RFID Reader
#define SS_PIN    21  // ESP32 pin GIO21 
#define RST_PIN   22 // ESP32 pin GIO22

//Inisialisasi RFID module
MFRC522 rfid(SS_PIN, RST_PIN);

//MAC Address yang ada di kartu
byte keyTagUID[7] = {0x05, 0x83, 0x4B, 0x7D, 0x30, 0xD1, 0x00}; //05 83 4B 7D 30 D1 00
void setup() {
//Inisialisasi serial monitor untuk debugging
Serial.begin(9600);

//Inisialisasi SPI bus
SPI.begin();

//Inisialisasi MFRC522
rfid.PCD_Init();

//Print tulisan ketika ESP pertama kali dijalankan
Serial.println("Tap RFID/NFC Tag on reader"); 
}
void loop() {


if (rfid.PICC_IsNewCardPresent()) { // Kartu baru ditambahkan
if (rfid.PICC_ReadCardSerial()) { // NUID ID telah terbaca
MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak); //Verifikasi pencocokan kartu dengan MAC yang telah diatur 
if (rfid.uid.uidByte[0] == keyTagUID[0] &&
rfid.uid.uidByte[1] == keyTagUID[1] &&
rfid.uid.uidByte[2] == keyTagUID[2] &&
rfid.uid.uidByte[3] == keyTagUID[3] &&
rfid.uid.uidByte[4] == keyTagUID[4] &&
rfid.uid.uidByte[5] == keyTagUID[5] &&
rfid.uid.uidByte[6] == keyTagUID[6] ) { 
Serial.println("Access is granted"); //Ketika kartu yang didaftarkan sesuai maka akan memberikan jawaban 
} 
else 
{
Serial.print("Access denied for user with UID:"); //Ketika kartu yang dibaca tidak sesuai dengan yang didaftarkan maka akan ditolak

//Print MAC Address kartu
for (int i = 0; i < rfid.uid.size; i++) {
  Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " "); 
Serial.print(rfid.uid.uidByte[i], HEX);
}
Serial.println(); 
}
rfid.PICC_HaltA(); // halt PICC
rfid.PCD_StopCrypto1(); // stop encryption on PCD
}
}
```

Memberikan Akses RFID 

```
//Library yang digunakan
#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

//Inisialisasi pin untuk RFID Reader
#define SS_PIN    21  // ESP32 pin GIO21 
#define RST_PIN   22 // ESP32 pin GIO22

//Inisialisasi pin untuk LED & Servo
const int ledPin1 = 32;
const int ledPin2 = 12;
static const int servoPin = 4;

//Memberi nama Servo
Servo servo1;

//Kartu yang didaftarkan
MFRC522 rfid(SS_PIN, RST_PIN);
byte keyTagUID[4] = {0x53, 0xB5, 0xE0, 0x16}; //53 B5 E0 16

void setup() {
//Inisialisasi serial monitor untuk debugging
Serial.begin(9600);

//Mengatur LED sebagai output
pinMode (ledPin1, OUTPUT);
pinMode (ledPin2, OUTPUT);

//Inisialisasi Servo
servo1.attach(servoPin);

//Inisialisasi RFID Module
SPI.begin(); // init SPI bus
rfid.PCD_Init(); // init MFRC522
Serial.println("Tap RFID/NFC Tag on reader"); 
delay(1000);

}
void loop() {

if (rfid.PICC_IsNewCardPresent()) { //Tag baru ditambahkan
if (rfid.PICC_ReadCardSerial()) { //Kartu baru saja dibaca

//Verifikasi kartu apakah sama dengan yang didaftarkan
MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak); 
if (rfid.uid.uidByte[0] == keyTagUID[0] &&
rfid.uid.uidByte[1] == keyTagUID[1] &&
rfid.uid.uidByte[2] == keyTagUID[2] &&
rfid.uid.uidByte[3] == keyTagUID[3] ) {
  Serial.println(); 
Serial.println("Access is granted"); //Akses diberikan ketika kartu yang dibaca sama dengan yang didaftarkan
Serial.println("SERVO BERGERAK"); //Print untuk memberitahukan bahwa servo bergerak
digitalWrite(ledPin2, HIGH); //LED Hidup karena kartu yang dibaca sesuai

//Servo bergerak karena kartu yang dibaca sesuai
    for(int posDegrees = 0; posDegrees <= 180; posDegrees++) {
        servo1.write(posDegrees);
        delay(5);
    }
delay(5000);
digitalWrite(ledPin2, LOW); //LED dimatikan

//Servo bergerak kembali ke posisi awal
    for(int posDegrees = 180; posDegrees >= 0; posDegrees--) {
        servo1.write(posDegrees);
        delay(20);
    }
    
} 
else //Ketika kartu yang dibaca tidak sesuai maka tidak ada pergerakan 
{
  Serial.println();
Serial.print("Access denied for user with UID:");
for (int i = 0; i < rfid.uid.size; i++) {
  Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " "); 
Serial.print(rfid.uid.uidByte[i], HEX);
}
digitalWrite(ledPin1, HIGH);
delay(3000); 
digitalWrite(ledPin1, LOW);

}
rfid.PICC_HaltA(); // halt PICC
rfid.PCD_StopCrypto1(); // stop encryption on PCD
}
}
``` 

## KESIMPULAN 

Pratikum ini memberikan kesimpulan dalam pembacaan sensor dapat menjadi suatu input bagi keluaran perangkat lainnya, seperti dalam RFID yang membaca kartu yang benar maka akan membuat LED dan Servo bergerak sesuai dengan yang diperintahkan. Dalam pratik sesungguhnya, RFID dapat dikembangkan sebagai trigger bagi keluaran lain seperti dalam ini sensor RFID bisa menjadi trigger bagi servo dan LED

## DOKUMENTASI 

https://user-images.githubusercontent.com/118155742/210376398-4ca775cf-230d-4e57-b49d-2fe7a8d9ce94.mp4



