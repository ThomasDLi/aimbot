// Load Wi-Fi library
#include <WiFi.h>
#include <Stepper.h>
#define STEPS 100
Stepper stepper(STEPS, 12, 14, 27, 26);

// Replace with your network credentials
const char* ssid     = "gun-control";
const char* password = "123456789";

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

// Auxiliar variables to store the current output state
String dir = "";

// Assign output variables to GPIO pins
const int output26 = 26;
const int output27 = 27;

void setup() {
  Serial.begin(115200);
  // Initialize the output variables as outputs
  stepper.setSpeed(30);
  // Connect to Wi-Fi network with SSID and password
  Serial.print("Setting AP (Access Point)…");
  // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
  
  server.begin();
}

void loop(){
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        //Serial.write(c);                    // print it out the serial monitor
        header += c;
        Serial.write(c);
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            // turns the GPIOs on and off
            if (header.indexOf("GET /up HTTP/1.1") >= 0) {
              Serial.println("up");
              dir = "on";
              digitalWrite(output26, HIGH);
            } else if (header.indexOf("GET /down HTTP/1.1") >= 0) {
              Serial.println("down");
              dir = "off";
              digitalWrite(output26, LOW);
            } else if (header.indexOf("GET /left HTTP/1.1") >= 0) {
              Serial.println("left");
              dir = "on";
              stepper.step(50); 
            } else if (header.indexOf("GET /right HTTP/1.1") >= 0) {
              Serial.println("right");
              dir = "off";
              digitalWrite(output27, LOW);
            
              stepper.step(-50);
            }
            client.print("<html><p>ya</p></html>");
            client.println();
            // The HTTP response ends with another blank line
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
