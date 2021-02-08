#include<arduino.h>
#include<ESP8266WiFi.h>
#include<WiFiClient.h>
#include<ESP8266WiFiMulti.h>
#include<ESPAsyncWebServer.h>
#include"mess_server.h"
#include <FS.h> 


ESP8266WiFiMulti WiFiMulti;

IPAddress local_IP(192, 168, 178, 66);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 0, 0);
IPAddress primaryDNS(8, 8, 8, 8);
IPAddress secondaryDNS(8, 8, 4, 4);

AsyncWebServer server(80);

const char* ssid = "*****";
const char* password = "****";


int mess_server::brerechnung_proz(Kalibrierung& kalibrierung, kali_dat& dat){
  dat = kalibrierung.laden();
  Serial.print("dat.trocken=");
  Serial.println(dat.trocken);
  Serial.print("dat.nass=");
  Serial.println(dat.nass);
  int akt_wert= dat.trocken-analogRead(A0);
  Serial.print("aktueller wert:= ");
  Serial.println(akt_wert);
  Serial.println((akt_wert*20)/dat.nass);
  return (akt_wert*20)/dat.nass;
}

void mess_server::server_init( Kalibrierung& kalibrierung, kali_dat& dat){
  if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) {
        Serial.println("STA Failed to configure");
      }
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    // Print local IP address and start web server
    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    server.begin();

  server.on("/on_test", HTTP_GET, [](AsyncWebServerRequest *request){
      request->send_P(200, "text/plain", "Online");
    });
  server.on("/Kali_nass", HTTP_GET, [](AsyncWebServerRequest *request){
      dat = kalibrierung.laden();
      dat.nass=dat.trocken-analogRead(A0);
      Serial.print("dat.nass nach rechnung: )");
      Serial.println(dat.nass);
      kalibrierung.speichern(dat);
      request->send_P(200, "text/plain", "Gespeichert");
      Serial.println("nass gespeichert auf abrfage");
    });
  server.on("/Kali_trocken", HTTP_GET, [](AsyncWebServerRequest *request){
      dat = kalibrierung.laden();
      dat.trocken=analogRead(A0);
      kalibrierung.speichern(dat);
      request->send_P(200, "text/plain", "Gespeichert");
      Serial.println("Trocken gespeichert auf abrfage");
    });
  server.on("/abfrage", HTTP_GET, [](AsyncWebServerRequest *request){
      int help=berechnung_proz(kalibrierung, dat);
      
      //I know its not clean but for now its working
      switch (help){
        case 0 : request->send_P(200, "text/plain", "0");
        break;
        case 1 : request->send_P(200, "text/plain", "5");
        break;
        case 2 : request->send_P(200, "text/plain", "10");
        break;
        case 3 : request->send_P(200, "text/plain", "15");
        break;
        case 4 : request->send_P(200, "text/plain", "20");
        break;
        case 5 : request->send_P(200, "text/plain", "25");
        break;
        case 6 : request->send_P(200, "text/plain", "30");
        break;
        case 7 : request->send_P(200, "text/plain", "35");
        break;
        case 8 : request->send_P(200, "text/plain", "40");
        break;
        case 9 : request->send_P(200, "text/plain", "45");
        break;
        case 10 : request->send_P(200, "text/plain", "50");
        break;
        case 11 : request->send_P(200, "text/plain", "55");
        break;
        case 12 : request->send_P(200, "text/plain", "60");
        break;
        case 13 : request->send_P(200, "text/plain", "65");
        break;
        case 14 : request->send_P(200, "text/plain", "70");
        break;
        case 15 : request->send_P(200, "text/plain", "75");
        break;
        case 16 : request->send_P(200, "text/plain", "80");
        break;
        case 17 : request->send_P(200, "text/plain", "85");
        break;
        case 18 : request->send_P(200, "text/plain", "90");
        break;
        case 19 : request->send_P(200, "text/plain", "95");
        break;
        case 20 : request->send_P(200, "text/plain", "100");
        break;
      }
    });
  server.begin();
}
