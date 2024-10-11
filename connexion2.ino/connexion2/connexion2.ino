
//WIFI : PoleDeVinci_IFT MDP: *c.r4UV@VfPn_0
// https://github.com/leoESILV/CS_workshop_octobre/blob/main/index.html
//http://127.0.0.1:5500/index.html
//Adresse IP : 10.1.224.40
// DC Arduino controle - l293d

#include <ESP8266WiFi.h>  // Utilisé pour l'ESP8266
#include <WebSocketsServer.h>

const char* ssid = "PoleDeVinci_IFT";
const char* password = "*c.r4UV@VfPn_0";


//pour allumer la led 
int ledPin = 16 ;

WebSocketsServer webSocket = WebSocketsServer(80); // port 80 ( port html)

void onWebSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
  // Handle WebSocket events here
  if (type == WStype_TEXT) {
      // Message reçu
      String message = (char *)payload;
      // Traitement du message
      Serial.println("Message reçu : " + message);
      // Send a response back to the client
      webSocket.sendTXT(num, "Message reçu et traité !");
    }
  
}

void setup() {

   // initialisation de la sortie pour la led 
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  //initilasioton wifi
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to :");
  Serial.println(ssid) ;

// voir adresse IP :
 Serial.print("Utiliser cette adresse URL pour la connexion :");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
  //web socket
  Serial.println("Starting WebSocket server...");
  webSocket.begin();
  webSocket.onEvent(onWebSocketEvent);


}

void loop() {
  webSocket.loop();  // Gérer les clients WebSocket
}