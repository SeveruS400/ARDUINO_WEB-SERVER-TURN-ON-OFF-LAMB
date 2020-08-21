/*
 * You can use everywhere for turn on/off led, lamb vb.
 * You must use a ethernet shield to connect to the internet
 * 
 *    SeveruS 08/21/2020
 */
 
#include <SPI.h>
#include <Ethernet.h>


byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
IPAddress ip(192, 168, 1, 177);                        //ip address
byte gateway[] = { 192, 168, 1, 1 };                   // internet access via router
byte subnet[] = { 255, 255, 255, 0 };     
EthernetServer server(80);
String readString;

//======================================================================
void setup() {
  pinMode(2,OUTPUT);        //numbers of relays
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("Ethernet WebServer Example");
  Ethernet.begin(mac, ip);
  if (Ethernet.hardwareStatus() == EthernetNoHardware) {
    Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
    while (true) {
      delay(1);
    }
  }
  if (Ethernet.linkStatus() == LinkOFF) {
    Serial.println("Ethernet cable is not connected.");
  }
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());

}

//======================================================================
void loop() {

  EthernetClient client = server.available();
  if (client) {
    while (client.connected()) {   
      if (client.available()) {
        char c = client.read();
     
        //read char by char HTTP request
        if (readString.length() < 100) {
          //store characters to string
          readString += c;
          //Serial.print(c);
         }

         //if HTTP request has ended
         if (c == '\n') {          
           Serial.println(readString); //print to serial monitor for debuging
           //===============================================================================>>>> Creat a new html server
           client.println("HTTP/1.1 200 OK"); //send new page
           client.println("Content-Type: text/html");
           client.println();     
           client.println("<HTML>");
           client.println("<HEAD>");
           client.println("<meta name='apple-mobile-web-app-capable' content='yes' />");
           client.println("<meta name='apple-mobile-web-app-status-bar-style' content='black-translucent' />");
           client.println("<link rel='stylesheet' type='text/css' href='http://randomnerdtutorials.com/ethernetcss.css' />");
           client.println("<TITLE>ODA IŞIĞI AÇMA KAPAMA</TITLE>");
           client.println("</HEAD>");
           client.println("<BODY>");
           client.println("<H1>Random Nerd Tutorials Project</H1>");
           client.println("<hr />");
           client.println("<br />");  
           client.println("<H2>ODALAR</H2>");
           client.println("<br />");  
           client.println("<H2>ODA1</H2>");
           client.println("<a href=\"/?button1on\"\">Turn On LED</a>");                 //Button names
           client.println("<a href=\"/?button1off\"\">Turn Off LED</a><br />");   
           client.println("<br />");  
           client.println("<H2>ODA2</H2>");
           client.println("<a href=\"/?button2on\"\">Turn On LED</a>");
           client.println("<a href=\"/?button2off\"\">Turn Off LED</a><br />");   
           client.println("<br />");   
           client.println("<H2>ODA3</H2>");
           client.println("<a href=\"/?button3on\"\">Turn On LED</a>");
           client.println("<a href=\"/?button3off\"\">Turn Off LED</a><br />");   
           client.println("<br />");  
           client.println("<H2>ODA4</H2>");
           client.println("<a href=\"/?button4on\"\">Turn On LED</a>");
           client.println("<a href=\"/?button4off\"\">Turn Off LED</a><br />");   
           client.println("<br />");      
           client.println("<br />"); 
           client.println("<br />"); 
           client.println("</BODY>");
           client.println("</HTML>");
     
           delay(10);
           client.stop();
           //controls the Arduino if you press the buttons
           if (readString.indexOf("?button1on") >0){
               digitalWrite(2, HIGH);
           }
           if (readString.indexOf("?button1off") >0){
               digitalWrite(2, LOW);
           }
           
           if (readString.indexOf("?button2on") >0){
               digitalWrite(3, HIGH);
           }
           if (readString.indexOf("?button2off") >0){
               digitalWrite(3, LOW);
           }
           
           if (readString.indexOf("?button3on") >0){
               digitalWrite(4, HIGH);
           }
           if (readString.indexOf("?button3off") >0){
               digitalWrite(4, LOW);
           }
           
           if (readString.indexOf("?button4on") >0){
               digitalWrite(5, HIGH);
           }
           if (readString.indexOf("?button4off") >0){
               digitalWrite(5, LOW);
           }
          
            //clearing string for next read
            readString="";  
           
         }
       }
    }
  }
}
