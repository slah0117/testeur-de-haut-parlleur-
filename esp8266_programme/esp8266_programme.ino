#include <addons/TokenHelper.h>


#include <addons/RTDBHelper.h>

#define WIFI_SSID "R"
#define WIFI_PASSWORD "12345678"
#define API_KEY "AIzaSyBPS0uJZSiYN5CWblZxQnRnpy15gxctMY4"
#define DATABASE_URL "esp01-8afe9-default-rtdb.europe-west1.firebasedatabase.app" //<databaseName>.firebaseio.com or <databaseName>.<region>.firebasedatabase.app
#define USER_EMAIL "bezslah@gmail.com"
#define USER_PASSWORD "25423017"
FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;

unsigned long count = 0;
String che;
String nam;
String n;
String a;
String b;
String c;
String z;
String k="2";


int cnt=10;
void setup()
{

  Serial.begin(115200);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
 // Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    //Serial.print(".");
    delay(300);
  }
  

  
  config.api_key = API_KEY;

  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;

  config.database_url = DATABASE_URL;

  
  config.token_status_callback = tokenStatusCallback; // see addons/TokenHelper.h

  

  Firebase.begin(&config, &auth);

 
  Firebase.reconnectWiFi(true);

  Firebase.setDoubleDigits(5);

 
}

void loop()
{

  // Firebase.ready() should be called repeatedly to handle authentication tasks.
 
    if (Firebase.ready() && (millis() - sendDataPrevMillis > 15000 || sendDataPrevMillis == 0)){
if(Serial.available()!=0)
{
  sendDataPrevMillis = millis();
String  nam = Serial.readString(); 
delay(10);
    
Serial.printf("%s",n= Firebase.getBool(fbdo,nam ) ? fbdo.to<bool>() ? "truee" : "false" : "errer"); 
 nam ="";
//int longueur=nam.length(); //On calcul la longueur
  //    nam.setCharAt(longueur-1,'2');
     

if ( n== "truee")
 { 


 
n="";
   
     while (1){
  c = Serial.readString();
    if (c !=0)
    break ;
    } 
     Serial.print("ook");
    c.trim();


if (c=="ook") {
delay(10);
while (1){
z = Serial.readString();
if (z !=0)
 break ;
 } 
 Serial.print("ook");
      Serial.printf("%s", Firebase.setBool(fbdo,z , true) ? "ook" : "err");
      z="";
      c="";
  while (1){
  a = Serial.readString();
    if (a !=0)
    break ;
    } 
    Serial.print("ook");
    delay(10);
    while (1){
  b = Serial.readString();
    if (b !=0)
    break ;
    } 
    Serial.print("ook");
    

 Serial.printf("%s", Firebase.setString(fbdo, a , b) ? "ook" : "err");
 
   FirebaseJson json;
a="";
b="";
 cnt=0;  

  }
  if (c=="non") 
  {
    delay(10);
     while (1){
 z = Serial.readString();
    if (z !=0)
    break ;
    } 
    Serial.print("ook");
    Serial.printf("%s", Firebase.setBool(fbdo,z, false) ? "ook" : "err");
     z="";
      c="";
       while (1){
  a = Serial.readString();
    if (a !=0)
    break ;
    } 
    Serial.print("ook");
    delay(10);
    while (1){
  b = Serial.readString();
   if (b !=0)
    break ;
    } 
    Serial.print("ook");
    

 Serial.printf("%s", Firebase.setString(fbdo, a , b) ? "ook" : "err");
 a="";
b="";
   FirebaseJson json;
 


 }
 }
 
    }}}
  
  
  
  
    
  
