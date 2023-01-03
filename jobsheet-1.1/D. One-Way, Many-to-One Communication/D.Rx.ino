//Library yang digunakan
#include <esp_now.h> 
#include <WiFi.h>

//Struktur data yang akan dikirimkan
typedef struct test_struct {
int x; 
int y;
} test_struct;

//membuat struktur data menjadi variabel test
test_struct test;

//fungsi untuk memberikan respon apabila data berhasil diterima
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) { 
memcpy(&test, incomingData, sizeof(test));
Serial.print("Bytes received: ");
Serial.println(len);
Serial.print("x: ");
Serial.println(test.x);
Serial.print("y: ");
Serial.println(test.y);
Serial.println(); 
}
void setup() {
//Inisialisasi Serial monitor untuk debugging 
Serial.begin(115200);

//Inisialisasi ESP sebagai WiFi Station
WiFi.mode(WIFI_STA);

//Inisialisasi ESP-NOW
if (esp_now_init() != ESP_OK) {
  Serial.println("Error initializing ESP-NOW"); 
return;
}
//register ke fungsi callback OnDataRecv() untuk memberitahukan bahwa data telah diterima
esp_now_register_recv_cb(OnDataRecv); 
}
void loop() { 
}
