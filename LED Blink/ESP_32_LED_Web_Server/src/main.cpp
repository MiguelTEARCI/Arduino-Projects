#include <WiFi.h>
#include <Adafruit_NeoPixel.h>

// 🔹 Definição do nome e senha do Wi-Fi que o ESP32 vai criar
const char* ssid = "ESP32_RGB";
const char* password = "12345678";

// 🔹 Configuração do servidor web
WiFiServer server(80);

// 🔹 Configuração do LED RGB embutido
#define LED_PIN     5   // Pino do LED embutido
#define LED_COUNT   1   // Apenas um LED

Adafruit_NeoPixel led(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

// 🔹 Variável para armazenar os pedidos HTTP
String header;

void setup() {
    Serial.begin(115200);
    
    // Inicializa o LED RGB
    led.begin();
    led.show(); // Garante que o LED comece apagado

    // 🔹 Configura o ESP32 como Access Point (AP)
    WiFi.softAP(ssid, password);
    
    Serial.println("Wi-Fi Criado!");
    Serial.print("IP do Servidor: ");
    Serial.println(WiFi.softAPIP());

    server.begin(); // Inicia o servidor web
}

// 🔹 Função para definir a cor do LED
void setColor(uint8_t red, uint8_t green, uint8_t blue) {
    led.setPixelColor(0, led.Color(red, green, blue));
    led.show();
}

void loop() {
    WiFiClient client = server.available(); // Espera por clientes

    if (client) {
        Serial.println("Novo Cliente Conectado.");
        String currentLine = "";

        while (client.connected()) {
            if (client.available()) {
                char c = client.read();
                Serial.write(c);
                header += c;
                
                if (c == '\n') {
                    if (currentLine.length() == 0) {
                        // 🔹 Envia resposta HTTP
                        client.println("HTTP/1.1 200 OK");
                        client.println("Content-type:text/html");
                        client.println("Connection: close");
                        client.println();

                        // 🔹 Verifica os comandos do cliente
                        if (header.indexOf("GET /vermelho") >= 0) {
                            Serial.println("LED VERMELHO");
                            setColor(255, 0, 0);
                        } else if (header.indexOf("GET /verde") >= 0) {
                            Serial.println("LED VERDE");
                            setColor(0, 255, 0);
                        } else if (header.indexOf("GET /azul") >= 0) {
                            Serial.println("LED AZUL");
                            setColor(0, 0, 255);
                        } else if (header.indexOf("GET /desligar") >= 0) {
                            Serial.println("LED DESLIGADO");
                            setColor(0, 0, 0);
                        }

                        // 🔹 Criação da página HTML
                        client.println("<!DOCTYPE html><html>");
                        client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
                        client.println("<style>body { font-family: Arial; text-align: center; margin: 50px;}");
                        client.println(".button { padding: 20px; font-size: 20px; margin: 5px; border: none; cursor: pointer;}");
                        client.println(".red { background-color: red; color: white; }");
                        client.println(".green { background-color: green; color: white; }");
                        client.println(".blue { background-color: blue; color: white; }");
                        client.println(".off { background-color: gray; color: white; }</style></head>");
                        client.println("<body><h1>Controle do LED RGB</h1>");
                        
                        client.println("<p><a href=\"/vermelho\"><button class=\"button red\">Vermelho</button></a></p>");
                        client.println("<p><a href=\"/verde\"><button class=\"button green\">Verde</button></a></p>");
                        client.println("<p><a href=\"/azul\"><button class=\"button blue\">Azul</button></a></p>");
                        client.println("<p><a href=\"/desligar\"><button class=\"button off\">Desligar</button></a></p>");
                        
                        client.println("</body></html>");
                        client.println();

                        break; // Sai do loop
                    } else {
                        currentLine = "";
                    }
                } else if (c != '\r') {
                    currentLine += c;
                }
            }
        }

        // 🔹 Limpa e encerra a conexão com o cliente
        header = "";
        client.stop();
        Serial.println("Cliente Desconectado.\n");
    }
}
 