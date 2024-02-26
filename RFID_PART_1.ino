#include <SPI.h>
#include <MFRC522.h>
#include<WiFi.h>

String URL = "http://192.168.132.158/rfid/test.php";

const char* ssid = "LOGIN WIR"; 
const char* password = "12345678"; 

#define RST_PIN   22
#define SS_PIN    5 

String Data;
int idcard = 30;
int akses = 1;

MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(115200);
  connectWiFi();
  SPI.begin();
  mfrc522.PCD_Init();
  delay(4);
  Serial.println("Tempel kartu anda");
  //mfrc522.PCD_DumpVersionToSerial();
  //Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));
  Serial.println();
}

void loop() {
  if(WiFi.status() != WL_CONNECTED) {
    connectWiFi();
  }
  if(!mfrc522.PICC_IsNewCardPresent()){
    return;
  }
  if(!mfrc522.PICC_ReadCardSerial()){
    return;
  }
  Serial.print("UID tag : ");
  //String content = "";
  //byte letter;
  //mfrc522.PICC_DumpToSerial(&(mfrc522.uid));

  /**if (rfid.uid.uidByte[0] != nuidPICC[0] || 
    rfid.uid.uidByte[1] != nuidPICC[1] || 
    rfid.uid.uidByte[2] != nuidPICC[2] || 
    rfid.c:\Users\MyPC One Pro H5\Downloads\rfid\RFID\RFID.cppuid.uidByte[3] != nuidPICC[3] ) {
    Serial.println(F("Terdeteksi Kartu Baru"));**/

  /**for (byte i = 0; i < 4; i++) 
  {
    //nuidPICC[i] = rfid.uid.uidByte[i];
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    //Serial.print(rfid.uid.uidByte[i], DEC);
    //Serial.print(" ");
    Serial.println(mfrc522.uid.uidByte[i], HEX);
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }**/
  String id;
  id = String(mfrc522.uid.uidByte[0]) + String(mfrc522.uid.uidByte[1]) + String(mfrc522.uid.uidByte[2]) + String(mfrc522.uid.uidByte[3]);
  Serial.println(id);
  if (id == "414140242")
  {
    Serial.println("Hello World!");
  } else{
    Serial.println("Denied");
  }

  Serial.println("");
  delay(2000);
}
    //else Serial.println(F("Kartu Sudah Terdeteksi Sebelumnya"));
    //  rfid.PICC_HaltA();
    //  rfid.PCD_StopCrypto1();
void connectWiFi() {
  WiFi.mode(WIFI_OFF);
  delay(1000);
  //This line hides the viewing of ESP as wifi hotspot
  WiFi.mode(WIFI_STA);
  
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi");
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
    
  Serial.print("connected to : "); Serial.println(ssid);
  Serial.print("IP address: "); Serial.println(WiFi.localIP());
}
