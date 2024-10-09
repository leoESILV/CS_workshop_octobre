
//WIFI : PoleDeVinci_IFT MDP: *c.r4UV@VfPn_0
// https://github.com/leoESILV/CS_workshop_octobre/blob/main/index.html
//http://127.0.0.1:5500/index.html
#include <ESP8266WiFi.h>
#include <WiFiClient.h>

// Informations de connexion Wi-Fi
const char* ssid = "PoleDeVinci_IFT";        
const char* password = "*c.r4UV@VfPn_0";    

// connexion au serveur 
const char* host = "http://127.0.0.1:5500/index.html";  

// Délai maximum pour se connecter au Wi-Fi (en millisecondes)
unsigned long wifiTimeout = 10000;  // 10 secondes

void setup() {
  Serial.begin(115200);

  // Connexion au Wi-Fi
  Serial.println();
  Serial.println("Connexion au Wi-Fi...");
  
  WiFi.begin(ssid, password);

  unsigned long startAttemptTime = millis();  // Enregistre le temps de début de la tentative

  // Attendre la connexion au Wi-Fi avec timeout
  while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < wifiTimeout) {
    delay(1000);
    Serial.print(".");
  }

  // Vérifier si la connexion a échoué
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("");
    Serial.println("Erreur : Impossible de se connecter au Wi-Fi.");
    return;  // Arrête le reste de la fonction setup si pas connecté
  }

  // Si connecté, afficher les informations
  Serial.println("");
  Serial.println("Connecté au Wi-Fi !");
  Serial.print("Adresse IP : ");
  Serial.println(WiFi.localIP());  // Affiche l'adresse IP locale

  // Connecter l'ESP8266 au serveur GitHub Pages
  WiFiClient client;
  if (!client.connect(host, 80)) {  // Port 80 pour HTTP
    Serial.println("Échec de la connexion au serveur");
    return;
  }

  // Faire une requête HTTP GET à GitHub Pages pour récupérer la page index.html
  client.print(String("GET /mon-site/index.html HTTP/1.1\r\n") + 
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");

  // Attendre la réponse du serveur
  while (client.connected() || client.available()) {
    if (client.available()) {
      String line = client.readStringUntil('\n');
      Serial.println(line);  // Affiche la réponse du serveur dans le Moniteur Série
    }
  }
}

void loop() {
  // Rien dans la boucle, car tout est fait dans le setup pour cet exemple
}
