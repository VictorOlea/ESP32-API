#include <Arduino.h>
#include <WiFi.h>
#include <LiquidCrystal_I2C.h>
#include <HTTPClient.h>
#include <Arduino_JSON.h>

// Replace with your network credentials (STATION)
const char* ssid = "*****";
const char* password = "*****";

// String for storing server response
String response;
String jsonBuffer;
// JSON document
//DynamicJsonDocument doc(2048);

// set the LCD number of columns and rows
int lcdColumns = 16;
int lcdRows = 2;

LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);

// Function Wifi Conection
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
  lcd.init();
  lcd.backlight();
}

void loop() {
  /*lcd.setCursor(0,0);
  lcd.print("Local IP");
  lcd.setCursor(0,1);
  lcd.print(WiFi.localIP());
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("RRSI");
  lcd.setCursor(0,1);
  lcd.print(WiFi.RSSI());
  delay(2000);
  lcd.clear();*/

  HTTPClient http;
  //String request = "https://api.gael.cloud/general/public/monedas/USD";
  String request = "https://api.libreapi.cl/economy/indicators";
  http.begin(request.c_str());
  http.GET();
  response = http.getString();
  Serial.println(response);
  //jsonBuffer = response;
  //Serial.println(jsonBuffer);
  JSONVar myObject = JSON.parse(response);

  /*Serial.print("Json Object = ");
  Serial.println(myObject);
  Serial.print("UF: ");
  Serial.println(myObject["data"]["uf"]);
  Serial.print("IVP: ");
  Serial.println(myObject["data"]["ivp"]);
  Serial.print("Dollar: ");
  Serial.println(myObject["data"]["dollar"]);
  Serial.print("Euro: ");
  Serial.println(myObject["data"]["euro"]);
  Serial.print("ITCNM: ");
  Serial.println(myObject["data"]["itcnm"]);
  Serial.print("Onza Plata: ");
  Serial.println(myObject["data"]["ozt_silver"]);
  Serial.print("Onza Oro: ");
  Serial.println(myObject["data"]["ozt_gold"]);
  Serial.print("Libra Cobre: ");
  Serial.println(myObject["data"]["lb_copper"]);*/

  lcd.setCursor(2,0);
  lcd.print("Indicadores");
  lcd.setCursor(3,1);
  lcd.print("Economicos");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("UF");
  lcd.setCursor(0,1);
  lcd.print(myObject["data"]["uf"]);
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("IVP");
  lcd.setCursor(0,1);
  lcd.print(myObject["data"]["ivp"]);
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Dollar");
  lcd.setCursor(0,1);
  lcd.print(myObject["data"]["dollar"]);
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Euro");
  lcd.setCursor(0,1);
  lcd.print(myObject["data"]["euro"]);
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("ITCNM");
  lcd.setCursor(0,1);
  lcd.print(myObject["data"]["itcnm"]);
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Onza Plata");
  lcd.setCursor(0,1);
  lcd.print(myObject["data"]["ozt_silver"]);
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Onza Oro");
  lcd.setCursor(0,1);
  lcd.print(myObject["data"]["ozt_gold"]);
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Libra Cobre");
  lcd.setCursor(0,1);
  lcd.print(myObject["data"]["lb_copper"]);
  delay(2000);
  lcd.clear();

  /*DeserializationError error = deserializeJson(doc, response);
  if(error){
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    return;
  }
  Serial.println(doc["value"].as<char*>());*/
  http.end();
  delay(2000); // Tiempo de espera para la siguinte consulta
  }