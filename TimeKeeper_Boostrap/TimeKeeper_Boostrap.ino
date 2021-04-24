/**

   Written and Verified by the owner of Pius Electronics
   Ndukwu Pius Onyema

   This code is open for fair use.
   If you are using it for commercial purpose, then it's mandatory to give credits

   Tutorial Video Link :-

*/
#include <Wire.h>
#include <RTClib.h>
#include <DNSServer.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WebServer.h>
#include <FS.h>
#include <LittleFS.h>
#include <ArduinoJson.h>

void listDir(const String dirname) {
  Serial.print("Listing directory: %s\n");
  Serial.println(dirname);

  Dir root = LittleFS.openDir(dirname);

  while (root.next()) {
    File file = root.openFile("r");
    Serial.print("  FILE: ");
    Serial.print(root.fileName());
    Serial.print("  SIZE: ");
    Serial.print(file.size());

    file.close();
  }
}



String readFile(String path) {
  String DoC = "";
  Serial.print("Reading file: %s\n");
  Serial.println(path);

  File file = LittleFS.open(path, "r");
  if (!file) {
    Serial.println("Failed to open file for reading");
    return DoC;
  }

  Serial.print("Read from file: ");
  while (file.available()) {

    DoC += file.readString();
    Serial.print(DoC);
    //delay(500);
  }

  file.close();

  return DoC;
}

void writeFile(String path, String message) {
  Serial.print("Writing file: %s\n");
  Serial.println(path);

  File file = LittleFS.open(path, "w");
  if (!file) {
    Serial.println("Failed to open file for writing");
    return;
  }
  if (file.print(message)) {
   
    Serial.println("File written");
  } else {
    Serial.println("Write failed");
  }
  delay(2000); // Make sure the CREATE and LASTWRITE times are different
  file.close();
}

void deleteFile(String path) {
  Serial.print("Deleting file: %s\n");
  Serial.println(path);
  if (LittleFS.remove(path)) {
    Serial.println("File deleted");

  } else {
    Serial.println("Delete failed");

  }

}

RTC_DS1307 rtc;
DynamicJsonDocument periods(2048);
//Variables
int i = 0;
int statusCode;
long PreviousTime = 0;
String Clock="";
bool flag = true;
String st;
String content;


// Actual period
String mon1; String mon2; String mon3; String mon4; String mon5; String mon6; String mon7; String mon8; String mon9; String mon10; String mon11; String mon12; String mon13;
String tue1; String tue2; String tue3; String tue4; String tue5; String tue6; String tue7; String tue8; String tue9; String tue10; String tue11; String tue12; String tue13;
String wed1; String wed2; String wed3; String wed4; String wed5; String wed6; String wed7; String wed8; String wed9; String wed10; String wed11; String wed12; String wed13;
String thu1; String thu2; String thu3; String thu4; String thu5; String thu6; String thu7; String thu8; String thu9; String thu10; String thu11; String thu12; String thu13;
String fri1; String fri2; String fri3; String fri4; String fri5; String fri6; String fri7; String fri8; String fri9; String fri10; String fri11; String fri12; String fri13;
String psw;

const int BELL_PIN = 14;

//Establishing Local server at port 80 whenever required
const byte DNS_PORT = 53;
IPAddress apIP(192, 168, 1, 1);
DNSServer dnsServer;
ESP8266WebServer server(80);

WiFiClient client;

    

void setup()
{

  Serial.begin(115200); //Initialising if(DEBUG)Serial Monitor
  
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));

Wire.begin(4,5);


  // modify TTL associated  with the domain name (in seconds)
  // default is 60 seconds
  dnsServer.setTTL(300);
  // set which return code will be used for all other domains (e.g. sending
  // ServerFailure instead of NonExistentDomain will reduce number of queries
  // sent by clients)
  // default is DNSReplyCode::NonExistentDomain
  dnsServer.setErrorReplyCode(DNSReplyCode::ServerFailure);

  // start DNS server for a specific domain name
  dnsServer.start(DNS_PORT, "www.timekeeper.com", apIP);
 


  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
   

  }
  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running, let's set the time!");
    // When time needs to be set on a new device, or after a power loss, the
    // following line sets the RTC to the date & time this sketch was compiled
    //rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2021, 1, 21, 23, 18, 0));
  }



  // mount LITTLEFS
  if (!LittleFS.begin()) {
    Serial.println("LittleFS mount failed");
    return;
  }
  listDir("/"); 
//  DynamicJsonDocument periods(2048);
   String input =readFile("/periods.txt");
    
  deserializeJson(periods, input);
  JsonObject obj = periods.as<JsonObject>();

  mon1 =obj["Mon1"].as<String>();;   mon2 =obj["Mon2"].as<String>();; mon3 = obj["Mon3"].as<String>();; mon4 = obj["Mon4"].as<String>();;  mon5 = obj["Mon5"].as<String>();;  mon6 = obj["Mon6"].as<String>();; mon7 = obj["Mon7"].as<String>();;  mon8 =obj["Mon8"].as<String>();;  mon9 = obj["Mon9"].as<String>();;  mon10 = obj["Mon10"].as<String>();;  mon11 =obj["Mon11"].as<String>();;  mon12 = obj["Mon12"].as<String>();; mon13 = obj["Mon13"].as<String>();;
  tue1 =obj["Tue1"].as<String>();;   tue2 =obj["Tue2"].as<String>();; tue3 = obj["Tue3"].as<String>();; tue4 = obj["Tue4"].as<String>();;  tue5 = obj["Tue5"].as<String>();;  tue6 = obj["Tue6"].as<String>();; tue7 = obj["Tue7"].as<String>();;  tue8 =obj["Tue8"].as<String>();;  tue9 = obj["Tue9"].as<String>();;  tue10 = obj["Tue10"].as<String>();;  tue11 =obj["Tue11"].as<String>();;  tue12 = obj["Tue12"].as<String>();; tue13 = obj["Tue13"].as<String>();;
  wed1 =obj["Wed1"].as<String>();;   wed2 =obj["Wed2"].as<String>();; wed3 = obj["Wed3"].as<String>();; wed4 = obj["Wed4"].as<String>();;  wed5 = obj["Wed5"].as<String>();;  wed6 = obj["Wed6"].as<String>();; wed7 = obj["Wed7"].as<String>();;  wed8 =obj["Wed8"].as<String>();;  wed9 = obj["Wed9"].as<String>();;  wed10 = obj["Wed10"].as<String>();;  wed11 =obj["Wed11"].as<String>();;  wed12 = obj["Wed12"].as<String>();; wed13 = obj["Wed13"].as<String>();;
  thu1 =obj["Thu1"].as<String>();;   thu2 =obj["Thu2"].as<String>();; thu3 = obj["Thu3"].as<String>();; thu4 = obj["Thu4"].as<String>();;  thu5 = obj["Thu5"].as<String>();;  thu6 = obj["Thu6"].as<String>();; thu7 = obj["Thu7"].as<String>();;  thu8 =obj["Thu8"].as<String>();;  thu9 = obj["Thu9"].as<String>();;  thu10 = obj["Thu10"].as<String>();;  thu11 =obj["Thu11"].as<String>();;  thu12 = obj["Thu12"].as<String>();; thu13 = obj["Thu13"].as<String>();; 
  fri1 =obj["Fri1"].as<String>();;   fri2 =obj["Fri2"].as<String>();; fri3 = obj["Fri3"].as<String>();; fri4 = obj["Fri4"].as<String>();;  fri5 = obj["Fri5"].as<String>();;  fri6 = obj["Fri6"].as<String>();; fri7 = obj["Fri7"].as<String>();;  fri8 =obj["Fri8"].as<String>();;  fri9 = obj["Fri9"].as<String>();;  fri10 = obj["Fri10"].as<String>();;  fri11 =obj["Fri11"].as<String>();;  fri12 = obj["Fri12"].as<String>();; fri13 = obj["Fri13"].as<String>();;
 
  psw =obj["Pass"].as<String>();
 Serial.print("psw:");
 Serial.println(psw);


  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(BELL_PIN, OUTPUT);

  digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(BELL_PIN, LOW); // turn buzzer on
  WiFi.softAP("TimeKeeper", (psw=="null")? "12345678" :obj["Pass"].as<String>());
  Serial.print("psw:");
 Serial.println(psw);

  createWebServer();
  // Start the server
  server.begin();
  Serial.println("Server started");

  Serial.println();
  Serial.println("Waiting.");






}
void loop() {

  alarm();
  dnsServer.processNextRequest();
  server.handleClient();
}


//----------------------------------------------- Fuctions used for WiFi credentials saving and connecting to it which you do not need to change




void createWebServer()
{
//DynamicJsonDocument periods(2048);
  server.on("/", []() {


    //html
    File file1 = LittleFS.open("/home.html", "r");
    if (!file1) {
      Serial.println("Failed to open file3 for reading");

    }
    else {
      server.streamFile(file1, "text/html");
      Serial.println("file sent");
    }



  });


  server.on("/home.html", []() {
    //html
    File Home = LittleFS.open("/home.html", "r");
    if (!Home) {
      Serial.println("Failed to open Home page for reading");

    }
    else {
      server.streamFile(Home, "text/html");
      Home.close();
    }

  });
  server.on("/contact.html", []() {
    //contact us page
    File contact = LittleFS.open("/contact.html", "r");
    if (!contact) {
      Serial.println("Failed to open contact page for reading");

    }
    else {
      server.streamFile(contact, "text/html");
      contact.close();
    }

  });

  server.on("/bootstrap.min.css", []() {
    File bootstrapCSS = LittleFS.open("/bootstrap.min.css", "r");
    if (! bootstrapCSS) {
      Serial.println("Failed to open  bootstrapCSS for reading");

    }
    else {
      server.streamFile( bootstrapCSS, "text/css");
      bootstrapCSS.close();
    }
  });
  server.on("/bootstrap.bundle.min.js", []() {
    File bootstrapJS = LittleFS.open("/bootstrap.bundle.min.js", "r");
    if (!bootstrapJS) {
      Serial.println("Failed to open tabright for reading");

    }
    else {
      server.streamFile(bootstrapJS, "application/javascript");
      bootstrapJS.close();
    }
  });

  server.on("/styles.css", []() {
    File file11 = LittleFS.open("/styles.css", "r");
    if (!file11) {
      Serial.println("Failed to open file11 for reading");

    }
    else {
      server.streamFile(file11, "text/css");
      file11.close();
    }
  });

  server.on("/pius.png", []() {
    File pic1 = LittleFS.open("/pius.png", "r+");
    if (!pic1) {
      Serial.println("Failed to open pius.png for reading");

    }
    else {
      server.streamFile(pic1, "image/png");
      pic1.close();
    }
  });

  server.on("/favicon.ico", []() {
    File pic2 = LittleFS.open("/pius.png", "r+");
    if (!pic2) {
      Serial.println("Failed to open pius.png for reading");

    }
    else {
      server.streamFile(pic2, "image/png");
      pic2.close();
    }
  });
  server.on("/timeUpdate.html", []() {

    //html
    File file9 = LittleFS.open("/timeUpdate.html", "r");
    if (!file9) {
      Serial.println("Failed to open file9 for reading");

    }
    else {
      server.streamFile(file9, "text/html");
      file9.close();
    }


  });

  server.on("/delete.html", []() {
    //html
    File Delete = LittleFS.open("/delete.html", "r");
    if (!Delete) {
      Serial.println("Failed to open file9 for reading");

    }
    else {
      server.streamFile(Delete, "text/html");
      Delete.close();
    }

  });

  server.on("/help.html", []() {
    //html
    File help = LittleFS.open("/help.html", "r");
    if (!help) {
      Serial.println("Failed to open help page for reading");

    }
    else {
      server.streamFile(help, "text/html");
      help.close();
    }

  });

  // send periods to server
  server.on("/getPeriods", [] () {
    
    server.send(200, "application/json", readFile("/periods.txt"));

  });


server.on("/delperiod", [] () {
  String response=server.arg("plain");
   
 writeFile("/periods.txt",response);
//Serial.println(server.arg("plain"));
});
 

  // updating time
  server.on("/setting", []() {
    String Mon1 =  server.arg("Mon1"); String Mon2 =  server.arg("Mon2"); String Mon3 =  server.arg("Mon3"); String Mon4 =  server.arg("Mon4"); String Mon5 =  server.arg("Mon5"); String Mon6 =  server.arg("Mon6"); String Mon7 =  server.arg("Mon7"); String Mon8 =  server.arg("Mon8"); String Mon9 =  server.arg("Mon9"); String Mon10 =  server.arg("Mon10"); String Mon11 =  server.arg("Mon11"); String Mon12 =  server.arg("Mon12"); String Mon13 =  server.arg("Mon13");
    String Tue1 =  server.arg("Tue1"); String Tue2 =  server.arg("Tue2"); String Tue3 =  server.arg("Tue3"); String Tue4 =  server.arg("Tue4"); String Tue5 =  server.arg("Tue5"); String Tue6 =  server.arg("Tue6"); String Tue7 =  server.arg("Tue7"); String Tue8 =  server.arg("Tue8"); String Tue9 =  server.arg("Tue9"); String Tue10 =  server.arg("Tue10"); String Tue11 =  server.arg("Tue11"); String Tue12 =  server.arg("Tue12"); String Tue13 =  server.arg("Tue13");
    String Wed1 =  server.arg("Wed1"); String Wed2 =  server.arg("Wed2"); String Wed3 =  server.arg("Wed3"); String Wed4 =  server.arg("Wed4"); String Wed5 =  server.arg("Wed5"); String Wed6 =  server.arg("Wed6"); String Wed7 =  server.arg("Wed7"); String Wed8 =  server.arg("Wed8"); String Wed9 =  server.arg("Wed9"); String Wed10 =  server.arg("Wed10"); String Wed11 =  server.arg("Wed11"); String Wed12 =  server.arg("Wed12"); String Wed13 =  server.arg("Wed13");
    String Thu1 =  server.arg("Thu1"); String Thu2 =  server.arg("Thu2"); String Thu3 =  server.arg("Thu3"); String Thu4 =  server.arg("Thu4"); String Thu5 =  server.arg("Thu5"); String Thu6 =  server.arg("Thu6"); String Thu7 =  server.arg("Thu7"); String Thu8 =  server.arg("Thu8"); String Thu9 =  server.arg("Thu9"); String Thu10 =  server.arg("Thu10"); String Thu11 =  server.arg("Thu11"); String Thu12 =  server.arg("Thu12"); String Thu13 =  server.arg("Thu13");
    String Fri1 =  server.arg("Fri1"); String Fri2 =  server.arg("Fri2"); String Fri3 =  server.arg("Fri3"); String Fri4 =  server.arg("Fri4"); String Fri5 =  server.arg("Fri5"); String Fri6 =  server.arg("Fri6"); String Fri7 =  server.arg("Fri7"); String Fri8 =  server.arg("Fri8"); String Fri9 =  server.arg("Fri9"); String Fri10 =  server.arg("Fri10"); String Fri11 =  server.arg("Fri11"); String Fri12 =  server.arg("Fri12"); String Fri13 =  server.arg("Fri13");
    String pass = server.arg("pass");
   
//DynamicJsonDocument periods(2048);
    //    serializeJson();
    JsonObject obj = periods.as<JsonObject>();


    if (pass.length() > 0) {
      Serial.println(pass);
      periods["Pass"] = pass;
      psw = pass;
    }

    if (Mon1.length() > 0) {
      Serial.println(Mon1);
     periods["Mon1"] = Mon1;
      mon1 = Mon1;
    }

    if (Mon2.length() > 0) {
      Serial.println(Mon2);
      periods["Mon2"] = Mon2;
      mon2 = Mon2;
    }

    if (Mon3.length() > 0) {
      Serial.println(Mon3);
      periods["Mon3"] = Mon3;
      mon3 = Mon3;
    }

    if (Mon4.length() > 0) {
      Serial.println(Mon4);
      periods["Mon4"] = Mon4;
      mon4 = Mon4;
    }

    if (Mon5.length() > 0) {
      Serial.println(Mon5);
      periods["Mon5"] = Mon5;
      mon5 = Mon5;
    }

    if (Mon6.length() > 0) {
      Serial.println(Mon6);
     periods["Mon6"] = Mon6;
      mon6 = Mon6;
    }

    if (Mon7.length() > 0) {
      Serial.println(Mon7);
      periods["Mon7"] = Mon7;
      mon7 = Mon7;
    }

    if (Mon8.length() > 0) {
      Serial.println(Mon8);
      periods["Mon8"] = Mon8;
      mon8 = Mon8;
    }

    if (Mon9.length() > 0) {
      Serial.println(Mon9);
      periods["Mon9"] = Mon9;
      mon9 = Mon9;
    }

    if (Mon10.length() > 0) {
      Serial.println(Mon10);
      periods["Mon10"] = Mon10;
      mon10 = Mon10;
    }

    if (Mon11.length() > 0) {
      Serial.println(Mon11);
      periods["Mon11"] = Mon11;
      mon11 = Mon11;
    }

    if (Mon12.length() > 0) {
      Serial.println(Mon12);
     periods["Mon12"] = Mon12;
      mon12 = Mon12;
    }

    if (Mon13.length() > 0) {
      Serial.println(Mon13);
      periods["Mon13"] = Mon13;
      mon13 = Mon13;
    }

    // Tuesdays
    
    if (Tue1.length() > 0) {
      Serial.println(Tue1);
     periods["Tue1"] = Tue1;
      tue1 = Tue1;
    }

    if (Tue2.length() > 0) {
      Serial.println(Tue2);
      periods["Tue2"] = Tue2;
      tue2 = Tue2;
    }

    if (Tue3.length() > 0) {
      Serial.println(Tue3);
      periods["Tue3"] = Tue3;
      tue3 = Tue3;
    }

    if (Tue4.length() > 0) {
      Serial.println(Tue4);
      periods["Tue4"] = Tue4;
      tue4 = Tue4;
    }

    if (Tue5.length() > 0) {
      Serial.println(Tue5);
      periods["Tue5"] = Tue5;
      tue5 = Tue5;
    }

    if (Tue6.length() > 0) {
      Serial.println(Tue6);
     periods["Tue6"] = Tue6;
      tue6 = Tue6;
    }

    if (Tue7.length() > 0) {
      Serial.println(Tue7);
      periods["Tue7"] = Tue7;
      tue7 = Tue7;
    }

    if (Tue8.length() > 0) {
      Serial.println(Tue8);
      periods["Tue8"] = Tue8;
      tue8 = Tue8;
    }

    if (Tue9.length() > 0) {
      Serial.println(Tue9);
      periods["Tue9"] = Tue9;
      tue9 = Tue9;
    }

    if (Tue10.length() > 0) {
      Serial.println(Tue10);
      periods["Tue10"] = Tue10;
      tue10 = Tue10;
    }

    if (Tue11.length() > 0) {
      Serial.println(Tue11);
      periods["Tue11"] = Tue11;
      tue11 = Tue11;
    }

    if (Tue12.length() > 0) {
      Serial.println(Tue12);
     periods["Tue12"] = Tue12;
      tue12 = Tue12;
    }

    if (Tue13.length() > 0) {
      Serial.println(Tue13);
      periods["Tue13"] = Tue13;
      tue13 = Tue13;
    }


    // Wednesdays
   
    if (Wed1.length() > 0) {
      Serial.println(Wed1);
     periods["Wed1"] = Wed1;
      wed1 = Wed1;
    }

    if (Wed2.length() > 0) {
      Serial.println(Wed2);
      periods["Wed2"] = Wed2;
      wed2 = Wed2;
    }

    if (Wed3.length() > 0) {
      Serial.println(Wed3);
      periods["Wed3"] = Wed3;
      wed3 = Wed3;
    }

    if (Wed4.length() > 0) {
      Serial.println(Wed4);
      periods["Wed4"] = Wed4;
      wed4 = Wed4;
    }

    if (Wed5.length() > 0) {
      Serial.println(Wed5);
      periods["Wed5"] = Wed5;
      wed5 = Wed5;
    }

    if (Wed6.length() > 0) {
      Serial.println(Wed6);
     periods["Wed6"] = Wed6;
      wed6 = Wed6;
    }

    if (Wed7.length() > 0) {
      Serial.println(Wed7);
      periods["Wed7"] = Wed7;
      wed7 = Wed7;
    }

    if (Wed8.length() > 0) {
      Serial.println(Wed8);
      periods["Wed8"] = Wed8;
      wed8 = Wed8;
    }

    if (Wed9.length() > 0) {
      Serial.println(Wed9);
      periods["Wed9"] = Wed9;
      wed9 = Wed9;
    }

    if (Wed10.length() > 0) {
      Serial.println(Wed10);
      periods["Wed10"] = Wed10;
      wed10 = Wed10;
    }

    if (Wed11.length() > 0) {
      Serial.println(Wed11);
      periods["Wed11"] = Wed11;
      wed11 = Wed11;
    }

    if (Wed12.length() > 0) {
      Serial.println(Wed12);
     periods["Wed12"] = Wed12;
      wed12 = Wed12;
    }

    if (Wed13.length() > 0) {
      Serial.println(Wed13);
      periods["Wed13"] = Wed13;
      wed13 = Wed13;
    }


    //Thursadays
   
    if (Thu1.length() > 0) {
      Serial.println(Thu1);
     periods["Thu1"] = Thu1;
      thu1 = Thu1;
    }

    if (Thu2.length() > 0) {
      Serial.println(Thu2);
      periods["Thu2"] = Thu2;
      thu2 = Thu2;
    }

    if (Thu3.length() > 0) {
      Serial.println(Thu3);
      periods["Thu3"] = Thu3;
      thu3 = Thu3;
    }

    if (Thu4.length() > 0) {
      Serial.println(Thu4);
      periods["Thu4"] = Thu4;
      thu4 = Thu4;
    }

    if (Thu5.length() > 0) {
      Serial.println(Thu5);
      periods["Thu5"] = Thu5;
      thu5 = Thu5;
    }

    if (Thu6.length() > 0) {
      Serial.println(Thu6);
     periods["Thu6"] = Thu6;
      thu6 = Thu6;
    }

    if (Thu7.length() > 0) {
      Serial.println(Thu7);
      periods["Thu7"] = Thu7;
      thu7 = Thu7;
    }

    if (Thu8.length() > 0) {
      Serial.println(Thu8);
      periods["Thu8"] = Thu8;
      thu8 = Thu8;
    }

    if (Thu9.length() > 0) {
      Serial.println(Thu9);
      periods["Thu9"] = Thu9;
      thu9 = Thu9;
    }

    if (Thu10.length() > 0) {
      Serial.println(Thu10);
      periods["Thu10"] = Thu10;
      thu10 = Thu10;
    }

    if (Thu11.length() > 0) {
      Serial.println(Thu11);
      periods["Thu11"] = Thu11;
      thu11 = Thu11;
    }

    if (Thu12.length() > 0) {
      Serial.println(Thu12);
     periods["Thu12"] = Thu12;
      thu12 = Thu12;
    }

    if (Thu13.length() > 0) {
      Serial.println(Thu13);
      periods["Thu13"] = Thu13;
      thu13 = Thu13;
    }

    //Friday
    if (Fri1.length() > 0) {
      Serial.println(Fri1);
     periods["Fri1"] = Fri1;
      fri1 = Fri1;
    }

    if (Fri2.length() > 0) {
      Serial.println(Fri2);
      periods["Fri2"] = Fri2;
      fri2 = Fri2;
    }

    if (Fri3.length() > 0) {
      Serial.println(Fri3);
      periods["Fri3"] = Fri3;
      fri3 = Fri3;
    }

    if (Fri4.length() > 0) {
      Serial.println(Fri4);
      periods["Fri4"] = Fri4;
      fri4 = Fri4;
    }

    if (Fri5.length() > 0) {
      Serial.println(Fri5);
      periods["Fri5"] = Fri5;
      fri5 = Fri5;
    }

    if (Fri6.length() > 0) {
      Serial.println(Fri6);
     periods["Fri6"] = Fri6;
      fri6 = Fri6;
    }

    if (Fri7.length() > 0) {
      Serial.println(Fri7);
      periods["Fri7"] = Fri7;
      fri7 = Fri7;
    }

    if (Fri8.length() > 0) {
      Serial.println(Fri8);
      periods["Fri8"] = Fri8;
      fri8 = Fri8;
    }

    if (Fri9.length() > 0) {
      Serial.println(Fri9);
      periods["Fri9"] = Fri9;
      fri9 = Fri9;
    }

    if (Fri10.length() > 0) {
      Serial.println(Fri10);
      periods["Fri10"] = Fri10;
      fri10 = Fri10;
    }

    if (Fri11.length() > 0) {
      Serial.println(Fri11);
      periods["Fri11"] = Fri11;
      fri11 = Fri11;
    }

    if (Fri12.length() > 0) {
      Serial.println(Fri12);
     periods["Fri12"] = Fri12;
      fri12 = Fri12;
    }

    if (Fri13.length() > 0) {
      Serial.println(Fri13);
      periods["Fri13"] = Fri13;
      fri13 = Fri13;
    }

    String output;
    serializeJson(periods, output);
    Serial.print(output);
    writeFile("/periods.txt",output);
    //      else {
    //        content = "{\"Error\":\"404 not found\"}";
    //        statusCode = 404;
    //        Serial.println("Sending 404");
    //      }
    content = "<!doctype html>"
"<html lang=\"en\">"
 "<head>"
    "<meta charset=\"utf-8\">"
    "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">"
    "<meta name=\"description\" content=>"
   " <meta name=\"author\" content=\"Pius Electronics\">"
    "<meta name=\"generator\" content=>"
    "<title>Save</title>"
  "</head>"
  "<body>"
  "<p>" + Clock +
  "Saved to file system click <a href=\"home.html\">Home</a> to go back to home page </p>"
  "</body>"
 " </html>";
    statusCode = 200;

    server.sendHeader("Access-Control-Allow-Origin", "*");
    server.send(statusCode, "text/html", content);

  });

}
void ringBell(int rings) {
 // Serial.println("i have entered ringBell function");
  if (flag) {
    Serial.print("flag: ");
    Serial.println(flag);
    for (int i = 0; i < rings; i++) {
      digitalWrite(BELL_PIN, HIGH);
      Serial.println("!!!BELL ON!!!");
      delay(2000);
      digitalWrite(BELL_PIN, LOW);
      Serial.println("!!!!BELL OFF!!!!");
      delay(500);
       Serial.println("Out of loop in "+String(i)+" rings acutal ring amount= " +String(rings));
    }
   
      flag = false;
      Serial.print("flag: ");
    Serial.println(flag);
     Serial.print("existing ringBell function");
      return;

  }
}
void alarm() {


  DateTime now = rtc.now();
  char buf1[] = "hh:mm";
  char sec[] = "ss";
  char Day[] = "DDD";
  unsigned long CurrentTime = millis();
  String Time = now.toString(buf1);
  Clock=Time;
  String dayOfWeek = now.toString(Day);
  while (CurrentTime - PreviousTime > 1000) {
    PreviousTime = CurrentTime;
    Serial.println(dayOfWeek);
    Serial.println(Time);
    Serial.println(now.toString(sec));

  }
  while (dayOfWeek == "Mon") {
    if (Time == mon1) {
      
      ringBell(1);
    }

    else if (Time == mon2) {
      
      ringBell(2);
    }

    else if (Time == mon3) {
      
      ringBell(3);
    }

    else if (Time == mon4) {
      
      ringBell(4);
    }

    else  if (Time == mon5) {
      
      ringBell(5);
    }

    else if (Time == mon6) {
      
      ringBell(6);
    }

    else if (Time == mon7) {
      
      ringBell(7);
    }

    else if (Time == mon8) {
      
      ringBell(8);
    }

    else if (Time == mon9) {
      
      ringBell(9);
    }

    else if (Time == mon10) {
      
      ringBell(10);
    }

    else if (Time == mon11) {
      
      ringBell(11);
    }

    else if (Time == mon12) {
      
      ringBell(12);
    }

    else if (Time == mon13) {
      
      ringBell(13);
    }
    else {
      flag = true;
      break;
    }
    break;
  }

  while (dayOfWeek == "Tue") {
    if (Time == tue1) {
      
      ringBell(1);
    }

    else if (Time == tue2) {
      
      ringBell(2);
    }

    else if (Time == tue3) {
      
      ringBell(3);
    }

    else if (Time == tue4) {
      
      ringBell(4);
    }

    else if (Time == tue5) {
      
      ringBell(5);
    }

    else if (Time == tue6) {
      
      ringBell(6);
    }

    else if (Time == tue7) {
      
      ringBell(7);
    }

    else if (Time == tue8) {
      
      ringBell(8);
    }

    else if (Time == tue9) {
      
      ringBell(9);
    }

    else if (Time == tue10) {
      
      ringBell(10);
    }

    else if (Time == tue11) {
      
      ringBell(11);
    }

    else if (Time == tue12) {
      
      ringBell(12);
    }

    else if (Time == tue13) {
      
      ringBell(13);
    }
    else{
      flag = true;
      break;
    }
    break;
  }

  while (dayOfWeek == "Wed") {
    if (Time == wed1) {
      
      ringBell(1);
    }

   else if (Time == wed2) {
      
      ringBell(2);
    }

   else if (Time == wed3) {
      
      ringBell(3);
    }

   else if (Time == wed4) {
      
      ringBell(4);
    }

   else if (Time == wed5) {
      
      ringBell(5);
    }

   else if (Time == wed6) {
      
      ringBell(6);
    }

   else if (Time == wed7) {
      
      ringBell(7);
    }

   else if (Time == wed8) {
      
      ringBell(8);
    }

   else if (Time == wed9) {
      
      ringBell(9);
    }

   else if (Time == wed10) {
      
      ringBell(10);
    }

   else if (Time == wed11) {
      
      ringBell(11);
    }

   else if (Time == wed12) {
      
      ringBell(12);
    }

   else if (Time == wed13) {
      
      ringBell(13);
    }
   else{
    flag=true;
    break;
   }
   break;
  }

  while (dayOfWeek == "Thu") {
    if (Time == thu1) {
      
      ringBell(1);
    }

   else if (Time == thu2) {
      
      ringBell(2);
    }

    if (Time == thu3) {
      
      ringBell(3);
    }

   else if (Time == thu4) {
      
      ringBell(4);
    }

   else if (Time == thu5) {
      
      ringBell(5);
    }

   else if (Time == thu6) {
      
      ringBell(6);
    }

   else if (Time == thu7) {
      
      ringBell(7);
    }

   else if (Time == thu8) {
      
      ringBell(8);
    }

   else if (Time == thu9) {
      
      ringBell(9);
    }

   else if (Time == thu10) {
      
      ringBell(10);
    }

   else if (Time == thu11) {
      
      ringBell(11);
    }

   else if (Time == thu12) {
      
      ringBell(12);
    }

   else if (Time == thu13) {
      
      ringBell(13);
    }
    else{
      flag=true;
      break;
    }
    break;
  }

  while (dayOfWeek == "Fri") {
    if (Time == fri1) {
      
      ringBell(1);
    }

    else if (Time == fri2) {
      
      ringBell(2);
    }

    else if (Time == fri3) {
      
      ringBell(3);
    }

    else if (Time == fri4) {
      
      ringBell(4);
    }

    else if (Time == fri5) {
      
      ringBell(5);
    }

    else if (Time == fri6) {
      
      ringBell(6);
    }

    else if (Time == fri7) {
      
      ringBell(7);
    }

    else if (Time == fri8) {
      
      ringBell(8);
    }

    else if (Time == fri9) {
      
      ringBell(9);
    }

    else if (Time == fri10) {
      
      ringBell(10);
    }

    else if (Time == fri11) {
      
      ringBell(11);
    }

    else if (Time == fri12) {
      
      ringBell(12);
    }

    else if (Time == fri13) {
      
      ringBell(13);
    }
    else {
      flag = true;
      break;
    }
    break;
  }
}
