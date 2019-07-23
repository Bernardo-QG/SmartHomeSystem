#include <ESP8266WiFi.h>
#include <Servo.h>

// Replace with your network credentials
const char* ssid     = /*"INFINITUM502D04" */"Martin_Garcia_H";
const char* password = /*"23D581E62F" */"M4451072841g4582873H";

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

// Auxiliar variables to store the current output state
String output16State = "off";
String output5State = "off";
String output4State = "off";
String output3State = "off";
String output2State = "off";
String output1State = "off";
String output0State = "off";
String output14State = "off";
String output12State = "off";

// Assign output variables to GPIO pins
const int output16 = 16; //cuarto 1
const int output5 = 5;   //cuarto 2
const int output4 = 4;
const int output3 = 3;  
const int output2 = 2;//cuarto 3
const int output1 = 1;   //cuarto 4
const int output0 = 0;
const int output14 = 14;
const int output12 = 12;
Servo servo_4;
Servo servo_2;

IPAddress ip(192, 168, 1, 64);
IPAddress gateway(192, 168, 1, 254);
IPAddress subnet(255, 255, 255, 0);

void setup() {
  Serial.begin(115200);
  // Initialize the output variables as outputs
  pinMode(output16, OUTPUT);
  pinMode(output5, OUTPUT);
  pinMode(output4, OUTPUT);
  pinMode(output3, OUTPUT);
  pinMode(output1, OUTPUT);
  pinMode(output0, OUTPUT);
  pinMode(output14, OUTPUT);
  pinMode(output12, OUTPUT);
  // Set outputs to LOW
  digitalWrite(output16, LOW);
  digitalWrite(output5, LOW);
  digitalWrite(output4, LOW);
  digitalWrite(output3, LOW);
  digitalWrite(output1, LOW);
  digitalWrite(output0, LOW);
  digitalWrite(output14, LOW);
  digitalWrite(output12, LOW);
  
  //motor
  servo_4.attach(4);
  servo_2.attach(2);
  servo_4.write(0);
  servo_2.write(0);
  delay(2000);

  // Connect to Wi-Fi network with SSID and password
  delay(10);
  Serial.println();
  WiFi.config(ip, gateway, subnet);
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
}

void loop(){
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
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
            
            // turns the GPIOs on and off luz de los cuartos
            if (header.indexOf("GET /16/on") >= 0) {
              Serial.println("GPIO 16 on");
              output16State = "on";
              digitalWrite(output16, HIGH);
            } else if (header.indexOf("GET /16/off") >= 0) {
              Serial.println("GPIO 16 off");
              output16State = "off";
              digitalWrite(output16, LOW);
            } else if (header.indexOf("GET /5/on") >= 0) {
              Serial.println("GPIO 5 on");
              output5State = "on";
              digitalWrite(output5, HIGH);
            } else if (header.indexOf("GET /5/off") >= 0) {
              Serial.println("GPIO 5 off");
              output5State = "off";
              digitalWrite(output5, LOW);
            } else if (header.indexOf("GET /4/on") >= 0) {
              Serial.println("GPIO 4 on");
              output4State = "on";
              digitalWrite(output4, HIGH);
              servo_4.write(90);
              delay(1000);
            } else if (header.indexOf("GET /4/off") >= 0) {
              Serial.println("GPIO 4 off");
              output4State = "off";
              servo_4.write(0);
              delay(1000);
              digitalWrite(output4, LOW);
            } else if (header.indexOf("GET /3/on") >= 0) {
              Serial.println("GPIO 3 on");
              output3State = "on";
              digitalWrite(output3, HIGH);
            } else if (header.indexOf("GET /3/off") >= 0) {
              Serial.println("GPIO 3 off");
              output3State = "off";
              digitalWrite(output3, LOW);
            } else if (header.indexOf("GET /1/on") >= 0) {
              Serial.println("GPIO 1 on");
              output1State = "on";
              digitalWrite(output1, HIGH);
            } else if (header.indexOf("GET /1/off") >= 0) {
              Serial.println("GPIO 1 off");
              output1State = "off";
              digitalWrite(output1, LOW);
            } else if (header.indexOf("GET /0/on") >= 0) {
              Serial.println("GPIO 0 on");
              output0State = "on";
              digitalWrite(output0, HIGH);
            } else if (header.indexOf("GET /0/off") >= 0) {
              Serial.println("GPIO 0 off");
              output0State = "off";
              digitalWrite(output0, LOW);
            } else if (header.indexOf("GET /2/on") >= 0) {
              Serial.println("GPIO 2 on");
              output2State = "on";
              digitalWrite(output2, HIGH);
              servo_2.write(90);
              delay(1000);
            } else if (header.indexOf("GET /2/off") >= 0) {
              Serial.println("GPIO 2 off");
              output2State = "off";
              servo_2.write(0);
              delay(1000);
              digitalWrite(output2, LOW);
            } else if (header.indexOf("GET /14/on") >= 0) {
              Serial.println("GPIO 14 on");
              output14State = "on";
              digitalWrite(output14, HIGH);
            } else if (header.indexOf("GET /14/off") >= 0) {
              Serial.println("GPIO 14 off");
              output14State = "off";
              digitalWrite(output14, LOW);
            } else if (header.indexOf("GET /12/on") >= 0) {
              Serial.println("GPIO 12 on");
              output12State = "on";
              digitalWrite(output12, HIGH);
            } else if (header.indexOf("GET /12/off") >= 0) {
              Serial.println("GPIO 12 off");
              output12State = "off";
              digitalWrite(output12, LOW);
            }
            
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons 
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #195B6A; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #77878A;}</style></head>");
            //se modifico y se agrego dos botones mas.
           // client.println(".button2 {background-color: #77878A;}");
           // client.println(".button2 {background-color: #77878A;}</style></head>");
            
            
            // Web Page Heading
            client.println("<body><h1>Smart Home System</h1>");

            client.println("<p>Cuarto 1 - State " + output16State + "</p>");
            if (output16State=="off") {
              client.println("<p><a href=\"/16/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/16/off\"><button class=\"button button2\">OFF</button></a></p>");
            } 
            
            // Display current state, and ON/OFF buttons for GPIO 5  
            client.println("<p>Cuarto 2 - State " + output5State + "</p>");
            // If the output5State is off, it displays the ON button       
            if (output5State=="off") {
              client.println("<p><a href=\"/5/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/5/off\"><button class=\"button button2\">OFF</button></a></p>");
            } 
               //aqui voy 
            // Display current state, and ON/OFF buttons for GPIO 4  
            client.println("<p>Cuarto 3 - State " + output3State + "</p>");
            // If the output4State is off, it displays the ON button       
            if (output3State=="off") {
              client.println("<p><a href=\"/3/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/3/off\"><button class=\"button button2\">OFF</button></a></p>");
            }

            client.println("<p>Cuarto 4 - State " + output1State + "</p>");
            if (output1State=="off") {
              client.println("<p><a href=\"/1/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/1/off\"><button class=\"button button2\">OFF</button></a></p>");
            } 

            client.println("<p>Cuarto 5 - State " + output0State + "</p>");
            if (output0State=="off") {
              client.println("<p><a href=\"/0/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/0/off\"><button class=\"button button2\">OFF</button></a></p>");
            } 

            //motor puerta
            client.println("<p>Puerta Abrir/Cerrar - State " + output4State + "</p>");
            // If the output4State is off, it displays the ON button       
            if (output4State=="off") {
              client.println("<p><a href=\"/4/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/4/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
            //garage
            client.println("<p>Puerta Abrir/Cerrar - State " + output2State + "</p>");
            // If the output4State is off, it displays the ON button       
            if (output2State=="off") {
              client.println("<p><a href=\"/2/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/2/off\"><button class=\"button button2\">OFF</button></a></p>");
            }

            // Ventiladores.
            client.println("<p>Ventilacion Cuarto 1 - State " + output14State + "</p>");
            if (output14State=="off") {
              client.println("<p><a href=\"/14/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/14/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
            client.println("<p>Ventilacion Cuarto 2 - State " + output12State + "</p>");
            if (output12State=="off") {
              client.println("<p><a href=\"/12/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/12/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
            
            client.println("</body></html>");
            
            // The HTTP response ends with another blank line
            client.println();
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
