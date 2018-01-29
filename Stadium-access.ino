#include <SPI.h>
#include <Ethernet.h>
#include <Servo.h> 

Servo microservo1;
Servo microservo2; 
int pos = 0; 
int pos1 = 0; 
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };   
byte ip[] = { 192, 168, 137, 10 };                      
byte gateway[] = { 192, 168, 137, 1 };                  
byte subnet[] = { 255, 255, 255, 0 };                  
EthernetServer server(80);                                  
String readString;

void setup() {

  Serial.begin(9600);  
   while (!Serial) {   
    ; 
  }
  pinMode(2,OUTPUT);        
  microservo1.attach(7);  
  microservo2.attach(6);
 
  Ethernet.begin(mac, ip, gateway, subnet); 
  server.begin();
  Serial.print("El Servidor es: ");
  Serial.println(Ethernet.localIP());   
}


void loop() {
  EthernetClient client = server.available();
  if (client) {
    while (client.connected()) {   
      if (client.available()) {
        char c = client.read();
     
        
        if (readString.length() < 100) {
          readString += c;
          
         }

         // si el requerimiento HTTP fue finalizado
         if (c == '\n') {          
           Serial.println(readString);
     
           client.println("HTTP/1.1 200 OK");          
           client.println("Content-Type: text/html");
           client.println();     
           client.println("<HTML>");
           client.println("<HEAD>");
           client.println("<TITLE>Controles estadio</TITLE>");
           client.println("<meta name='viewport' content='initial-scale=1', maximum-scale='1'>");
           client.println("</HEAD>");
            client.println("<style type='text/css'> body { background-image: url('https://rui39g.by3302.livefilestore.com/y4m-Xe17hZJOHuKSkllnL1s9E6dzqqIPE6ZKylbOvO7na5rHwgMzOptzz9NaxgblLLLbnr9gCukQ9huKFhif4dJCf63rl5FZaA1dAYCL6MmEBWBvUwrOVKAbpoJFAXNrFpUrrSOEjewxNvvW7R9XwjjrpN_Up2BT4S8xDtDFcD8Ch193TNuu7ab0IUQsIZuQhgWMVe14aWys4wsPMgZpNBLnQ?width=1920&height=1080&cropmode=none');} </style>");
           client.println("<Center>");
           client.println("<hr />");
           client.println("<H1><font color='white'>Bienvenidos al Santiago Bernabeu</font></H1>"); 

           client.println("<H2> <font color='white'>Luces</font color></H2>");
           client.println("</br>");
           client.println("<a class='boton_personalizado1on' href=\"/?button2on\"\">Encender</font></a>");   
           client.println("<style type='text/css'> .boton_personalizado1on {text-decoration: none; padding: 9px; font-size: 15px; color:#ffffff; background-color: #1883ba; border: 1px solid #3F7CFF;width:86px;} .boton_personalizado1on:hover{ color: #1883ba; background-color: #ffffff; }  </style>  ");        
           client.println(" | | | ");
           client.println("<a class='boton_personalizado1off' href=\"/?button2off\"\">Apagar</font></a>");   
           client.println("<style type='text/css'> .boton_personalizado1off {text-decoration: none; padding: 9px; font-size: 15px; color:#ffffff; background-color: #1883ba; border: 1px solid #3F7CFF;width:86px; }  .boton_personalizado1off:hover{ color: #1883ba; background-color: #ffffff; }</style>  ");

           client.println("</br>");
           client.println("</br>");
           client.println("<H2><font color='white'>Puerta Principal</font></H2>");
           client.println("<a class='botonabrir1' href=\"/?left\"\">Abrir</font></a>");   
           client.println("<style type='text/css'> .botonabrir1 {text-decoration: none; padding: 9px; font-size: 15px; color:#ffffff; background-color: #1883ba; border: 1px solid #3F7CFF;width:86px;} .botonabrir1:hover{ color: #1883ba; background-color: #ffffff; }  </style>  ");        
           client.println(" | | | ");
           client.println("<a class='botoncerrar1' href=\"/?right\"\">Cerrar</font></a>");   
           client.println("<style type='text/css'> .botoncerrar1 {text-decoration: none; padding: 9px; font-size: 15px; color:#ffffff; background-color: #1883ba; border: 1px solid #3F7CFF;width:86px; }  .botoncerrar1:hover{ color: #1883ba; background-color: #ffffff; }</style>  ");

           client.println("</br>");
           client.println("</br>");
           client.println("<H2><font color='white'>Puerta de Salida</font></H2>"); 
           client.println("<a class='botonabrir2' href=\"/?left1\"\">Abrir</font></a>");   
           client.println("<style type='text/css'> .botonabrir2 {text-decoration: none; padding: 9px; font-size: 15px; color:#ffffff; background-color: #1883ba; border: 1px solid #3F7CFF;width:86px;} .botonabrir2:hover{ color: #1883ba; background-color: #ffffff; }  </style>  ");        
           client.println(" | | | ");
           client.println("<a class='botoncerrar2' href=\"/?right1\"\">Cerrar</font></a>");   
           client.println("<style type='text/css'> .botoncerrar2 {text-decoration: none; padding: 9px; font-size: 15px; color:#ffffff; background-color: #1883ba; border: 1px solid #3F7CFF;width:86px; }  .botoncerrar2:hover{ color: #1883ba; background-color: #ffffff; }</style>  ");

     
           delay(1);
           //detiene el cliente servidor
           client.stop();
           
           //control del arduino si un boton es presionado
                   
           if (readString.indexOf("?button2on") >0){
               digitalWrite(2, HIGH);
           }
           if (readString.indexOf("?button2off") >0){
               digitalWrite(2, LOW);
           }
           
           
           
           if (readString.indexOf("?left") >0){
                for(pos = 0; pos < 90; pos += 3)  
                {                                  
                  microservo1.write(pos);             
                  delay(15);                     
                } 
           }
           if (readString.indexOf("?right") >0){
                for(pos = 90; pos>=1; pos-=3)    
                {                                
                  microservo1.write(pos);              
                  delay(15);                       
                } 

           }    
           if (readString.indexOf("?left1") >0){
                for(pos1 = 0; pos1 < 90; pos1 += 3)  
                {                                  
                  microservo2.write(pos1);             
                  delay(15);                     
                } 
           }
           if (readString.indexOf("?right1") >0){
                for(pos1 = 90; pos1>=1; pos1-=3)    
                {                                
                  microservo2.write(pos1);              
                  delay(15);                       
                }
           }
            // Limpia el String(Cadena de Caracteres para una nueva lectura
            readString="";  
           
         }
       }
    }
}
}
