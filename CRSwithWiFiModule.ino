//Make sure to subscribe Technomekanics:)
String ssid     = "Simulator Wifi";  // SSID to connect to
String password = ""; // Our virtual wifi has no password 
String host     = "api.thingspeak.com"; // Open Weather Map API
const int httpPort   = 80;
String uri     = "/update?api_key=LUGP6TV6XN9SYTKC&field1=";

const int ledPin = 13;   //the number of the LED pin
const int ldrPin = A1;  //the number of the LDR pin

int v_GasSen = 0;


int setupESP8266(void) {
  // Start our ESP8266 Serial Communication
  Serial.begin(115200);   // Serial connection over USB to computer
  Serial.println("AT");   // Serial connection on Tx / Rx port to ESP8266
  delay(10);        // Wait a little for the ESP to respond
  if (!Serial.find("OK")) return 1;
    
  // Connect to 123D Circuits Simulator Wifi
  Serial.println("AT+CWJAP=\"" + ssid + "\",\"" + password + "\"");
  delay(10);        // Wait a little for the ESP to respond
  if (!Serial.find("OK")) return 2;
  
  // Open TCP connection to the host:
  Serial.println("AT+CIPSTART=\"TCP\",\"" + host + "\"," + httpPort);
  delay(50);        // Wait a little for the ESP to respond
  if (!Serial.find("OK")) return 3;
  
  return 0;
}

void anydata(void) {
  
  int temp = map(analogRead(A0),20,358,-40,125);
  
  // Construct our HTTP call
  String httpPacket = "GET " + uri + String(temp) + " HTTP/1.1\r\nHost: " + host + "\r\n\r\n";
  int length = httpPacket.length();
  
  // Send our message length
  Serial.print("AT+CIPSEND=");
  Serial.println(length);
  delay(10); // Wait a little for the ESP to respond if (!Serial.find(">")) return -1;

  // Send our http request
  Serial.print(httpPacket);
  delay(10); // Wait a little for the ESP to respond
  if (!Serial.find("SEND OK\r\n")) return;
  
  
}


void setup() {
  
  setupESP8266();
  pinMode(A2, INPUT);
  pinMode(7, OUTPUT);
  
  pinMode(ledPin, OUTPUT);  //initialize the LED pin as an output
  pinMode(ldrPin, INPUT);   //initialize the LDR pin as an input
  
  
               
}

void loop() {
  
 anydata();
  
  delay(10000);
   
  v_GasSen = analogRead(A2);
  if (v_GasSen >= 250) 
  {
    tone(7, 523, 1000); // play tone 60 (C5 = 523 Hz)
  }
  delay(10);
  
  int ldrStatus = analogRead(ldrPin);   //read the status of the LDR value

  //check if the LDR status is <= 300
  //if it is, the LED is HIGH

  if (ldrStatus <=300) 
  {
    digitalWrite(ledPin, HIGH);           //turn LED on
    Serial.println("LDR is DARK, LED is ON");
   }
  else 
  {
    digitalWrite(ledPin, LOW);          //turn LED off
    Serial.println("LDR is LIGHT, LED is OFF");
	}
}