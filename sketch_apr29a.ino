#include <Wire.h> //libreria per collegamenti con l2c
#include <LiquidCrystal_I2C.h> // libreria per display
LiquidCrystal_I2C lcd(0x27,16,2);  //address per liquid,colonne e righe
#include <ESP32Servo.h> //libreria per motore (sbarra)
#include <WiFi.h>
#include <HTTPClient.h>
const char* ssid     = "";
const char* password = "";


const char* serverName = "http://yourip/sensordata/post-esp-data.php";
String sensorLocation="NY";
String apiKeyValue="tPmAT5Ab3j7F9";
Servo myservo1; // motore

int IR1 = 4; // pin sensore andata
int IR2 = 5; // pin sensore ritorno

int posti = 2;           //posti
int flag1 = 0; // per sensore 1 giro andata (si alza quando passo)
int flag2 = 0; // per sensore 2 giro di ritorno (si alza quando passo)
void setup() {
   
  lcd.init(); // inizializzo display
  lcd.backlight(); //retroilluminazione
//   input per i sensori
pinMode(IR1, INPUT);
pinMode(IR2, INPUT);


  
myservo1.attach(2); // motore su pin 2
myservo1.write(100); // angolo rotazione (se 0 va a terra)
// messaggio iniziale 

lcd.setCursor (0,0); // posizione scritta
lcd.print("     ARDUINO    "); //stampa video
lcd.setCursor (0,1); 
lcd.print(" SYSTEMA PARK ");
delay (2000); //attesa del programma
lcd.clear();  //pulisci display

Serial.begin(115200);
   

    //connesione wifi

    Serial.println();
    Serial.println();
    Serial.print("Connessione a  ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connesso");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());


}

void loop() {
  // put your main code here, to run repeatedly:
  //giro andata,passaggio sul sensore1
  if(digitalRead (IR1) == LOW && flag1==0){ // se S1 rileva auto e flag1 è basso
if(posti>0){
  flag1=1; // sensore 1 ha rilevato auto e la fa passare
if(flag2==0){ // sto per passare dal sensore due (ancora non l'ho "toccato"), quindi sono entrato e diminuisco posti e abbasso sbarra
  myservo1.write(0); posti = posti-1; // alza sbarra e decrementa
  }
}
else{ 
lcd.setCursor (0,0);
lcd.print("    Scusa :(    ");  
lcd.setCursor (0,1);
lcd.print("  Park Pieno  "); 
delay (3000);
lcd.clear(); 
}
}
// leggo pin sensore 2, se basso e flag2 0, alza flag 2 e se flag1 è basso abbassa rotore e aumenta posto
//qui sto uscendo
if(digitalRead (IR2) == LOW && flag2==0){flag2=1; // passo dal sensore 2,si alza
if(flag1==0){myservo1.write(0); posti = posti+1;} // sto per passare al sensore 1, alzo sbarra e aumento posti
}
//quando rilevo entrambi, ruota e resetto
if(flag1==1 && flag2==1){
delay (1000);
myservo1.write(100); // ruota si abbassa
flag1=0, flag2=0;
}
// scritte sul display,che ti informa sui posti

lcd.setCursor (0,0);
lcd.print("    CIAO!    ");
lcd.setCursor (0,1);
lcd.print("Slot Left: ");
lcd.print(posti);

//controllo stato wifi
  if(WiFi.status()== WL_CONNECTED){
    HTTPClient http;
    
    // inizializzo inserendo url
    http.begin(serverName);
    
    // Specifico header
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    
    // richiesta http
    String httpRequestData = "api_key=" + apiKeyValue
                          + "&location=" + sensorLocation + "&posti=" + String(posti)+ "";
    Serial.print("httpRequestData: ");
    Serial.println(httpRequestData);
    
    
 // risposta http
    int httpResponseCode = http.POST(httpRequestData);
     
   
  if (httpResponseCode>0) {// -1 se errato
      Serial.print("HTTP codice stato: ");
      Serial.println(httpResponseCode);
    }
    else {
      Serial.print("codice errore: ");
      Serial.println(httpResponseCode);
    }
    // libero
    http.end();
  }
  else {
    Serial.println("WiFi disconnesso");
  }
  
  //invia nuovamente richiesta http tra 15 secondi
  //delay(15000);  

}
