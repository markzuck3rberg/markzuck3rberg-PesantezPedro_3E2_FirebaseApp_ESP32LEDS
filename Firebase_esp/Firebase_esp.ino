#include <Firebase_ESP_Client.h>
#include <WiFi.h>
#include <addons/TokenHelper.h>
#include <ArduinoJson.h>
#define FIREBASE_USE_PSRAM

//Conectar a una red WiFi 
const char* WIFI_SSID = "celu";//el nombre de la red
const char* WIFI_PASSWORD = "123456789";//la contraseña de la red
//Recursos de Firebase
const char* API_KEY = "AIzaSyDpBrLvIICoOXisTpgs8K02mUxwzgLJ_Mo";
const char* FIREBASE_PROJECT_ID = "fir-99428";
//CONFIGURAR UN EMAIL Y CONTRASEÑA EN AUTHENTICATION de Firebase
const char* USER_EMAIL = "markzuckerberg@esp.com";
const char* USER_PASSWORD = "123456";

//Define Firebase Data object
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

const int LED1 = 23;
const int LED2 = 22;
const int LED3 = 21;

//Funcion para configuara WiFi
void setupWiFi() {
  Serial.print("Connecting to Wi-Fi");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
}

void setupFirebase() {
  config.api_key = API_KEY;
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;
  config.token_status_callback = tokenStatusCallback;  // Ver addons/TokenHelper.h
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

void setup() {
  Serial.begin(115200);
  Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);//Verificamos la version
  setupWiFi();//Llamamos la funcion de configuración wifi
  setupFirebase();//Llamamos la funcion de configuración Firebase
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
}

void loop(){
    String path = "controlLED";//RUTA DE COLECCION
    FirebaseJson json;

  if (Firebase.Firestore.getDocument(&fbdo, FIREBASE_PROJECT_ID, "", path.c_str(), "")) {

    StaticJsonDocument<1024> doc;
    DeserializationError error = deserializeJson(doc, fbdo.payload().c_str());

    if (!error) {
      for (JsonObject document : doc["documents"].as<JsonArray>()) {
        const char* document_name = document["name"];//PARAMETRO NOMBRE //Serial.print(document_name);
        const bool state = document["fields"]["encender"]["booleanValue"]; //PARAMETRO DE CAMPOS A REVISAR
        Serial.print(":");
        if (strstr(document_name, "LED1") != nullptr) {//COMPARAR NOMBRE CON RESULTADO ESPERADO LED1
          state? Serial.print("Control 1 On"): Serial.print("Control 1 OFF");
          if(state==true){
            digitalWrite(LED1,1);
          }
          else{
            digitalWrite(LED1,0);
          }
        }
        if (strstr(document_name, "LED2") != nullptr) {
          state? Serial.print("Control 2 On"): Serial.print("Control 2 OFF");
          if(state==true){
            digitalWrite(LED2,1);
          }
          else{
            digitalWrite(LED2,0);
          }
        }
        if (strstr(document_name, "LED3") != nullptr) {
          state ? Serial.print("Control 3 On"): Serial.print("Control 3 OFF");
          if(state==true){
            digitalWrite(LED3,1);
          }
          else{
            digitalWrite(LED3,0);
          }
        }
          delay(500); // Esperar 500 MILIS antes de la próxima lectura
      }
    }
	}
}
