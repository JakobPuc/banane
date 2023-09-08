#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>

uint8_t broadcastAddress[] = {0x98, 0xF4, 0xAB, 0x01, 0xC9, 0x68};


typedef struct struct_message {
  int a;
  int b;
  int c;
  int d;
} struct_message;

struct_message myData;

esp_now_peer_info_t peerInfo;

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_register_send_cb(OnDataSent);

  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }

  pinMode(34,PULLDOWN);
  pinMode(17,PULLDOWN);
  pinMode(33,INPUT);
  pinMode(39,INPUT);
  pinMode(35,INPUT);
  pinMode(32,INPUT);
  Serial.print("Jebi se");
}

void loop() {

  myData.a = analogRead(33);
  myData.b = analogRead(39);
  myData.c = analogRead(35);
  myData.d = analogRead(32);



  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
  //Serial.printf("%d %d %d %d\n", a,b,c,d);

  if (result == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data");
  }
   
  delay(100);
}
