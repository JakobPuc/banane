#include <esp_now.h>
#include <WiFi.h>

// Structure example to receive data
// Must match the sender structure
typedef struct struct_message {
    int a;
    int b;
    int c;
    int d;
} struct_message;

// Create a struct_message called myData
struct_message myData;

// callback function that will be executed when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.printf("%d %d %d %d", myData.a, myData.b, myData.c, myData.d);
  Serial.println();
}
 
void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);

  pinMode(2,OUTPUT);
  pinMode(0,OUTPUT);

  digitalWrite(0,HIGH);
  digitalWrite(2,LOW);

  
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
  esp_now_register_recv_cb(OnDataRecv);
}
 
void loop() {
  /*if(myData.a > -11){
    digitalWrite(2,HIGH);
    digitalWrite(0,LOW);
  }
  else if (myData.a < -11)
  {
    digitalWrite(0,HIGH);
    digitalWrite(2,LOW);
  }
  else{
    digitalWrite(2,LOW);
    digitalWrite(0,LOW);
  }*/
}