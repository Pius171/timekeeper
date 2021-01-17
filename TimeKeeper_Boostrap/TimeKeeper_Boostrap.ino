/**

   Written and Verified by the owner of Pius Electronics
   Ndukwu Pius Onyema

   This code is open for fair use.
   If you are using it for commercial purpose, then it's mandatory to give credits

   Tutorial Video Link :-

*/
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WebServer.h>
#include <FS.h>
#include <LittleFS.h>
#include <Wire.h>
#include <RTClib.h>
#include <PolledTimeout.h>

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

RTC_DS3231 rtc;
//Variables
int i = 0;
int statusCode;
long PreviousTime = 0;
String st;
String content;


// Actual period
String mon1; String mon2; String mon3; String mon4; String mon5; String mon6; String mon7; String mon8; String mon9; String mon10; String mon11; String mon12; String mon13;
String tue1; String tue2; String tue3; String tue4; String tue5; String tue6; String tue7; String tue8; String tue9; String tue10; String tue11; String tue12; String tue13;
String wed1; String wed2; String wed3; String wed4; String wed5; String wed6; String wed7; String wed8; String wed9; String wed10; String wed11; String wed12; String wed13;
String thu1; String thu2; String thu3; String thu4; String thu5; String thu6; String thu7; String thu8; String thu9; String thu10; String thu11; String thu12; String thu13;
String fri1; String fri2; String fri3; String fri4; String fri5; String fri6; String fri7; String fri8; String fri9; String fri10; String fri11; String fri12; String fri13;
String psw;

const int BELL_PIN=12;
//Establishing Local server at port 80 whenever required
ESP8266WebServer server(80);



void setup()
{

  Serial.begin(115200); //Initialising if(DEBUG)Serial Monitor
  Wire.begin(4, 5);
#ifndef ESP8266
  while (!Serial); // wait for serial port to connect. Needed for native USB
#endif

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
   
  }

  if (! rtc.lostPower()) {
    Serial.println("RTC is NOT running, let's set the time!");
    // When time needs to be set on a new device, or after a power loss, the
    // following line sets the RTC to the date & time this sketch was compiled
   // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }

  

  // mount LITTLEFS
  if (!LittleFS.begin()) {
    Serial.println("LittleFS mount failed");
    return;
  }
  listDir("/");
  mon1 = readFile("/Mon1.txt");  mon2 = readFile("/Mon2.txt"); mon3 = readFile("Mon3.txt"); mon4 = readFile("/Mon4.txt");  mon5 = readFile("/Mon5.txt");  mon6 = readFile("/Mon6.txt");  mon7 = readFile("/Mon7.txt");  mon8 = readFile("/Mon8.txt");  mon9 = readFile("/Mon9.txt");  mon10 = readFile("/Mon10.txt");  mon11 = readFile("/Mon11.txt");  mon12 = readFile("/Mon12.txt"); mon13 = readFile("/Mon13.txt");
  tue1 = readFile("/Tue1.txt");  tue2 = readFile("/Tue2.txt"); tue3 = readFile("Mon3.txt"); tue4 = readFile("/Tue4.txt");  tue5 = readFile("/Tue5.txt");  tue6 = readFile("/Tue6.txt");  tue7 = readFile("/Tue7.txt");  tue8 = readFile("/Tue8.txt");  tue9 = readFile("/Tue9.txt");  tue10 = readFile("/Tue10.txt");  tue11 = readFile("/Tue11.txt");  tue12 = readFile("/Tue12.txt"); tue13 = readFile("/Tue13.txt");
  wed1 = readFile("/Wed1.txt");  wed2 = readFile("/Wed2.txt"); wed3 = readFile("Mon3.txt"); wed4 = readFile("/Wed4.txt");  wed5 = readFile("/Wed5.txt");  wed6 = readFile("/Wed6.txt");  wed7 = readFile("/Wed7.txt");  wed8 = readFile("/Wed8.txt");  wed9 = readFile("/Wed9.txt");  wed10 = readFile("/Wed10.txt");  wed11 = readFile("/Wed11.txt");  wed12 = readFile("/Wed12.txt"); wed13 = readFile("/Wed13.txt");
  thu1 = readFile("/Thu1.txt");  thu2 = readFile("/Thu2.txt"); thu3 = readFile("Mon3.txt"); thu4 = readFile("/Thu4.txt");  thu5 = readFile("/Thu5.txt");  thu6 = readFile("/Thu6.txt");  thu7 = readFile("/Thu7.txt");  thu8 = readFile("/Thu8.txt");  thu9 = readFile("/Thu9.txt");  thu10 = readFile("/Thu10.txt");  thu11 = readFile("/Thu11.txt");  thu12 = readFile("/Thu12.txt"); thu13 = readFile("/Thu13.txt");
  fri1 = readFile("/Fri1.txt");  fri2 = readFile("/Fri2.txt"); fri3 = readFile("Mon3.txt"); fri4 = readFile("/Fri4.txt");  fri5 = readFile("/Fri5.txt");  fri6 = readFile("/Fri6.txt");  fri7 = readFile("/Fri7.txt");  fri8 = readFile("/Fri8.txt");  fri9 = readFile("/Fri9.txt");  fri10 = readFile("/Fri10.txt");  fri11 = readFile("/Fri11.txt");  fri12 = readFile("/Fri12.txt"); fri13 = readFile("/Fri13.txt");
  psw = readFile("/pass.txt");



  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(BELL_PIN,OUTPUT);

  digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(BELL_PIN,LOW); // turn buzzer on
  WiFi.softAP("TimeKeeper", psw);
  createWebServer();
  // Start the server
  server.begin();
  Serial.println("Server started");

  Serial.println();
  Serial.println("Waiting.");






}
void loop() {
  alarm();
  server.handleClient();
}


//----------------------------------------------- Fuctions used for WiFi credentials saving and connecting to it which you do not need to change




void createWebServer()
{

  server.on("/", []() {


    //html
    File file1 = LittleFS.open("/home.html", "r");
    if (!file1) {
      Serial.println("Failed to open file3 for reading");

    }
    else {
      server.streamFile(file1, "text/html");
    }



  });


  server.on("/home", []() {
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
  server.on("/contact", []() {
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
    File bootstrapCSS = LittleFS.open("//bootstrap.min.css", "r");
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
  server.on("/Update", []() {

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

  server.on("/delete", []() {
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

  server.on("/help", []() {
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
    DynamicJsonDocument periods(2048);
    //    serializeJson();
    JsonObject obj = periods.as<JsonObject>();

    periods["Mon1"] = mon1; periods["Mon2"] = mon2; periods["Mon3"] = mon3; periods["Mon4"] = mon4; periods["Mon5"] = mon5; periods["Mon6"] = mon6; periods["Mon7"] = mon7; periods["Mon8"] = mon8; periods["Mon9"] = mon9; periods["Mon10"] = mon10; periods["Mon11"] = mon11; periods["Mon12"] = mon12; periods["Mon13"] = mon13;
    periods["Tue1"] = tue1; periods["Tue2"] = tue2; periods["Tue3"] = tue3; periods["Tue4"] = tue4; periods["Tue5"] = tue5; periods["Tue6"] = tue6; periods["Tue7"] = tue7; periods["Tue8"] = tue8; periods["Tue9"] = tue9; periods["Tue10"] = tue10; periods["Tue11"] = tue11; periods["Tue12"] = tue12; periods["Tue13"] = tue13;
    periods["Wed1"] = wed1; periods["Wed2"] = wed2; periods["Wed3"] = wed3; periods["Wed4"] = wed4; periods["Wed5"] = wed5; periods["Wed6"] = wed6; periods["Wed7"] = wed7; periods["Wed8"] = wed8; periods["Wed9"] = wed9; periods["Wed10"] = wed10; periods["Wed11"] = wed11; periods["Wed12"] = wed12; periods["Wed13"] = wed13;
    periods["Thu1"] = thu1; periods["Thu2"] = thu2; periods["Thu3"] = thu3; periods["Thu4"] = thu4; periods["Thu5"] = thu5; periods["Thu6"] = thu6; periods["Thu7"] = thu7; periods["Thu8"] = thu8; periods["Thu9"] = thu9; periods["Thu10"] = thu10; periods["Thu11"] = thu11; periods["Thu12"] = thu12; periods["Thu13"] = thu13;
    periods["Fri1"] = fri1; periods["Fri2"] = fri2; periods["Fri3"] = fri3; periods["Fri4"] = fri4; periods["Fri5"] = fri5; periods["Fri6"] = fri6; periods["Fri7"] = fri7; periods["Fri8"] = fri8; periods["Fri9"] = fri9; periods["Fri10"] = fri10; periods["Fri11"] = fri11; periods["Fri12"] = fri12; periods["Fri13"] = fri13;
    serializeJsonPretty(periods, Serial);

    String output;
    serializeJson(periods, output);
    Serial.print(output);
    server.send(200, "application/json", output);

  });



  //deleting periods
  server.on("/delMon1", [] () {
    deleteFile("/Mon1.txt");
    mon1 = "";
  });

  server.on("/delMon2", [] () {
    deleteFile("/Mon2.txt");
    mon2 = "";
  });

  server.on("/delMon3", [] () {
    deleteFile("/Mon3.txt");
    mon3 = "";
  });

  server.on("/delMon4", [] () {
    deleteFile("/Mon4.txt");
    mon4 = "";
  });

  server.on("/delMon5", [] () {
    deleteFile("/Mon5.txt");
    mon5 = "";
  });

  server.on("/delMon6", [] () {
    deleteFile("/Mon6.txt");
    mon6 = "";
  });

  server.on("/delMon7", [] () {
    deleteFile("/Mon7.txt");
    mon7 = "";
  });
  server.on("/delMon8", [] () {
    deleteFile("/Mon8.txt");
    mon8 = "";
  });

  server.on("/delMon9", [] () {
    deleteFile("/Mon9.txt");
    mon9 = "";
  });

  server.on("/delMon10", [] () {
    deleteFile("/Mon10.txt");
    mon10 = "";
  });
  server.on("/delMon11", [] () {
    deleteFile("/Mon11.txt");
    mon11 = "";
  });

  server.on("/delMon12", [] () {
    deleteFile("/Mon12.txt");
    mon12 = "";
  });

  server.on("/delMon13", [] () {
    deleteFile("/Mon13.txt");
    mon13 = "";
  });

  // delete tuesday
  server.on("/delTue1", [] () {
    deleteFile("/Tue1.txt");
    tue1 = "";
  });

  server.on("/delTue2", [] () {
    deleteFile("/Tue2.txt");
    tue2 = "";
  });

  server.on("/delTue3", [] () {
    deleteFile("/Tue3.txt");
    tue3 = "";
  });

  server.on("/delTue4", [] () {
    deleteFile("/Tue4.txt");
    tue4 = "";
  });

  server.on("/delTue5", [] () {
    deleteFile("/Tue5.txt");
    tue5 = "";
  });

  server.on("/delTue6", [] () {
    deleteFile("/Tue6.txt");
    tue6 = "";
  });

  server.on("/delTue7", [] () {
    deleteFile("/Tue7.txt");
    tue7 = "";
  });
  server.on("/delTue8", [] () {
    deleteFile("/Tue8.txt");
    tue8 = "";
  });

  server.on("/delTue9", [] () {
    deleteFile("/Tue9.txt");
    tue9 = "";
  });

  server.on("/delTue10", [] () {
    deleteFile("/Tue10.txt");
    tue10 = "";
  });
  server.on("/delTue11", [] () {
    deleteFile("/Tue11.txt");
    tue11 = "";
  });

  server.on("/delTue12", [] () {
    deleteFile("/Tue12.txt");
    tue12 = "";
  });

  server.on("/delTue13", [] () {
    deleteFile("/Tue13.txt");
    tue13 = "";
  });
  // delete wednesday
  server.on("/delWed1", [] () {
    deleteFile("/Wed1.txt");
    wed1 = "";
  });

  server.on("/delWed2", [] () {
    deleteFile("/Wed2.txt");
    wed2 = "";
  });

  server.on("/delWed3", [] () {
    deleteFile("/Wed3.txt");
    wed3 = "";
  });

  server.on("/delWed4", [] () {
    deleteFile("/Wed4.txt");
    wed4 = "";
  });

  server.on("/delWed5", [] () {
    deleteFile("/Wed5.txt");
    wed5 = "";
  });

  server.on("/delWed6", [] () {
    deleteFile("/Wed6.txt");
    wed6 = "";
  });

  server.on("/delWed7", [] () {
    deleteFile("/Wed7.txt");
    wed7 = "";
  });

  server.on("/delWed8", [] () {
    deleteFile("/Wed8.txt");
    wed7 = "";
  });

  server.on("/delWed9", [] () {
    deleteFile("/Wed9.txt");
    wed8 = "";
  });

  server.on("/delWed10", [] () {
    deleteFile("/Wed10.txt");
    wed9 = "";
  });
  server.on("/delWed11", [] () {
    deleteFile("/Wed11.txt");
    wed11 = "";
  });

  server.on("/delWed12", [] () {
    deleteFile("/Wed12.txt");
    wed12 = "";
  });

  server.on("/delWed13", [] () {
    deleteFile("/Wed13.txt");
    wed13 = "";
  });

  // delete thursday
  server.on("/delThu1", [] () {
    deleteFile("/Thu1.txt");
    thu1 = "";
  });

  server.on("/delThu2", [] () {
    deleteFile("/Thu2.txt");
    thu2 = "";
  });

  server.on("/delThu3", [] () {
    deleteFile("/Thu3.txt");
    thu3 = "";
  });

  server.on("/delThu4", [] () {
    deleteFile("/Thu4.txt");
    thu4 = "";
  });

  server.on("/delThu5", [] () {
    deleteFile("/Thu5.txt");
    thu5 = "";
  });



  server.on("/delThu6", [] () {
    deleteFile("/Thu6.txt");
    thu6 = "";
  });

  server.on("/delThu7", [] () {
    deleteFile("/Thu7.txt");
    thu7 = "";
  });

  server.on("/delThu8", [] () {
    deleteFile("/Thu8.txt");
    thu8 = "";
  });

  server.on("/delThu9", [] () {
    deleteFile("/Thu9.txt");
    thu9 = "";
  });

  server.on("/delThu10", [] () {
    deleteFile("/Thu10.txt");
    thu10 = "";
  });
  server.on("/delThu11", [] () {
    deleteFile("/Thu11.txt");
    thu11 = "";
  });

  server.on("/delThu12", [] () {
    deleteFile("/Thu12.txt");
    thu12 = "";
  });

  server.on("/delThu13", [] () {
    deleteFile("/Thu13.txt");
    thu13 = "";
  });
  // delete Friday
  server.on("/delFri1", [] () {
    deleteFile("/Fri1.txt");
    fri1 = "";
  });

  server.on("/delFri2", [] () {
    deleteFile("/Fri2.txt");
    fri2 = "";
  });

  server.on("/delFri3", [] () {
    deleteFile("/Fri3.txt");
    fri3 = "";
  });

  server.on("/delFri4", [] () {
    deleteFile("/Fri4.txt");
    fri4 = "";
  });

  server.on("/delFri5", [] () {
    deleteFile("/Fri5.txt");
    fri5 = "";
  });

  server.on("/delFri6", [] () {
    deleteFile("/Fri6.txt");
    fri6 = "";
  });

  server.on("/delFri7", [] () {
    deleteFile("/Fri7.txt");
    fri7 = "";
  });

  server.on("/delFri8", [] () {
    deleteFile("/Fri8.txt");
    fri8 = "";
  });

  server.on("/delFri9", [] () {
    deleteFile("/Fri9.txt");
    fri9 = "";
  });

  server.on("/delFri10", [] () {
    deleteFile("/Fri10.txt");
    fri10 = "";
  });
  server.on("/delFri11", [] () {
    deleteFile("/Fri11.txt");
    fri11 = "";
  });

  server.on("/delFri12", [] () {
    deleteFile("/Fri12.txt");
    fri12 = "";
  });

  server.on("/delFri13", [] () {
    deleteFile("/Fri13.txt");
    fri13 = "";
  });


  // updating time
  server.on("/setting", []() {
    String Mon1 =  server.arg("Mon1"); String Mon2 =  server.arg("Mon2"); String Mon3 =  server.arg("Mon3"); String Mon4 =  server.arg("Mon4"); String Mon5 =  server.arg("Mon5"); String Mon6 =  server.arg("Mon6"); String Mon7 =  server.arg("Mon7"); String Mon8 =  server.arg("Mon8"); String Mon9 =  server.arg("Mon9"); String Mon10 =  server.arg("Mon10"); String Mon11 =  server.arg("Mon11"); String Mon12 =  server.arg("Mon12"); String Mon13 =  server.arg("Mon13");
    String Tue1 =  server.arg("Tue1"); String Tue2 =  server.arg("Tue2"); String Tue3 =  server.arg("Tue3"); String Tue4 =  server.arg("Tue4"); String Tue5 =  server.arg("Tue5"); String Tue6 =  server.arg("Tue6"); String Tue7 =  server.arg("Tue7"); String Tue8 =  server.arg("Tue8"); String Tue9 =  server.arg("Tue9"); String Tue10 =  server.arg("Tue10"); String Tue11 =  server.arg("Tue11"); String Tue12 =  server.arg("Tue12"); String Tue13 =  server.arg("Tue13");
    String Wed1 =  server.arg("Wed1"); String Wed2 =  server.arg("Wed2"); String Wed3 =  server.arg("Wed3"); String Wed4 =  server.arg("Wed4"); String Wed5 =  server.arg("Wed5"); String Wed6 =  server.arg("Wed6"); String Wed7 =  server.arg("Wed7"); String Wed8 =  server.arg("Wed8"); String Wed9 =  server.arg("Wed9"); String Wed10 =  server.arg("Wed10"); String Wed11 =  server.arg("Wed11"); String Wed12 =  server.arg("Wed12"); String Wed13 =  server.arg("Wed13");
    String Thu1 =  server.arg("Thu1"); String Thu2 =  server.arg("Thu2"); String Thu3 =  server.arg("Thu3"); String Thu4 =  server.arg("Thu4"); String Thu5 =  server.arg("Thu5"); String Thu6 =  server.arg("Thu6"); String Thu7 =  server.arg("Thu7"); String Thu8 =  server.arg("Thu8"); String Thu9 =  server.arg("Thu9"); String Thu10 =  server.arg("Thu10"); String Thu11 =  server.arg("Thu11"); String Thu12 =  server.arg("Thu12"); String Thu13 =  server.arg("Thu13");
    String Fri1 =  server.arg("Fri1"); String Fri2 =  server.arg("Fri2"); String Fri3 =  server.arg("Fri3"); String Fri4 =  server.arg("Fri4"); String Fri5 =  server.arg("Fri5"); String Fri6 =  server.arg("Fri6"); String Fri7 =  server.arg("Fri7"); String Fri8 =  server.arg("Fri8"); String Fri9 =  server.arg("Fri9"); String Fri10 =  server.arg("Fri10"); String Fri11 =  server.arg("Fri11"); String Fri12 =  server.arg("Fri12"); String Fri13 =  server.arg("Fri13");
    String pass = server.arg("pass");
    Serial.print("Mon1=");
    Serial.println(Mon1) ;
    Serial.print("Mon2=");
    Serial.println(Mon2);

    if (pass.length() > 0) {
      Serial.println(pass);
      writeFile("/pass.txt", pass);
      psw = pass;
    }

    if (Mon1.length() > 0) {
      Serial.println(Mon1);
      writeFile("/Mon1.txt", Mon1);
      mon1 = Mon1;
    }

    if (Mon2.length() > 0) {
      Serial.println(Mon2);
      writeFile("/Mon2.txt", Mon2);
      mon2 = Mon2;
    }

    if (Mon3.length() > 0) {
      Serial.println(Mon3);
      writeFile("/Mon3.txt", Mon3);
      mon3 = Mon3;
    }

    if (Mon4.length() > 0) {
      Serial.println(Mon4);
      writeFile("/Mon4.txt", Mon4);
      mon4 = Mon4;
    }

    if (Mon5.length() > 0) {
      Serial.println(Mon5);
      writeFile("/Mon5.txt", Mon5);
      mon5 = Mon5;
    }

    if (Mon6.length() > 0) {
      Serial.println(Mon6);
      writeFile("/Mon6.txt", Mon6);
      mon6 = Mon6;
    }

    if (Mon7.length() > 0) {
      Serial.println(Mon7);
      writeFile("/Mon7.txt", Mon7);
      mon7 = Mon7;
    }

    if (Mon8.length() > 0) {
      Serial.println(Mon8);
      writeFile("/Mon8.txt", Mon8);
      mon8 = Mon8;
    }

    if (Mon9.length() > 0) {
      Serial.println(Mon9);
      writeFile("/Mon9.txt", Mon9);
      mon9 = Mon9;
    }

    if (Mon10.length() > 0) {
      Serial.println(Mon10);
      writeFile("/Mon10.txt", Mon10);
      mon10 = Mon10;
    }

    if (Mon11.length() > 0) {
      Serial.println(Mon11);
      writeFile("/Mon11.txt", Mon11);
      mon11 = Mon11;
    }

    if (Mon12.length() > 0) {
      Serial.println(Mon12);
      writeFile("/Mon12.txt", Mon12);
      mon12 = Mon12;
    }

    if (Mon13.length() > 0) {
      Serial.println(Mon13);
      writeFile("/Mon13.txt", Mon13);
      mon13 = Mon13;
    }

    // Tuesdays
    if (Tue1.length() > 0) {
      Serial.println(Tue1);
      writeFile("/Tue1.txt", Tue1);
      tue1 = Tue1;
    }

    if (Tue2.length() > 0) {
      Serial.println(Tue2);
      writeFile("/Tue2.txt", Tue2);
      tue2 = Tue2;
    }

    if (Tue3.length() > 0) {
      Serial.println(Tue3);
      writeFile("/Tue3.txt", Tue3);
      tue3 = Tue3;
    }

    if (Tue4.length() > 0) {
      Serial.println(Tue4);
      writeFile("/Tue4.txt", Tue4);
      tue4 = Tue4;
    }

    if (Tue5.length() > 0) {
      Serial.println(Tue5);
      writeFile("/Tue5.txt", Tue5);
      tue5 = Tue5;
    }

    if (Tue6.length() > 0) {
      Serial.println(Tue6);
      writeFile("/Tue6.txt", Tue6);
      tue6 = Tue6;
    }

    if (Tue7.length() > 0) {
      Serial.println(Tue7);
      writeFile("/Tue7.txt", Tue7);
      tue7 = Tue7;
    }

    if (Tue8.length() > 0) {
      Serial.println(Tue8);
      writeFile("/Tue8.txt", Tue8);
      tue8 = Tue8;
    }

    if (Tue9.length() > 0) {
      Serial.println(Tue9);
      writeFile("/Tue9.txt", Tue9);
      tue9 = Tue9;
    }

    if (Tue10.length() > 0) {
      Serial.println(Tue10);
      writeFile("/Tue10.txt", Tue10);
      tue10 = Tue10;
    }

    if (Tue11.length() > 0) {
      Serial.println(Tue11);
      writeFile("/Tue11.txt", Tue11);
      tue11 = Tue11;
    }

    if (Tue12.length() > 0) {
      Serial.println(Tue12);
      writeFile("/Tue12.txt", Tue12);
      tue12 = Tue12;
    }

    if (Tue13.length() > 0) {
      Serial.println(Tue13);
      writeFile("/Tue13.txt", Tue13);
      tue13 = Tue13;
    }

    // Wednesdays
    if (Wed1.length() > 0) {
      Serial.println(Wed1);
      writeFile("/Wed1.txt", Wed1);
      wed1 = Wed1;
    }

    if (Wed2.length() > 0) {
      Serial.println(Wed2);
      writeFile("/Wed2.txt", Wed2);
      wed2 = Wed2;
    }

    if (Wed3.length() > 0) {
      Serial.println(Wed3);
      writeFile("/Wed3.txt", Wed3);
      wed3 = Wed3;
    }

    if (Wed4.length() > 0) {
      Serial.println(Wed4);
      writeFile("/Wed4.txt", Wed4);
      wed4 = Wed4;
    }

    if (Wed5.length() > 0) {
      Serial.println(Wed5);
      writeFile("/Wed5.txt", Wed5);
      wed5 = Wed5;
    }

    if (Wed6.length() > 0) {
      Serial.println(Wed6);
      writeFile("/Wed6.txt", Wed6);
      wed6 = Wed6;
    }

    if (Wed7.length() > 0) {
      Serial.println(Wed7);
      writeFile("/Wed7.txt", Wed7);
      wed7 = Wed7;
    }

    if (Wed8.length() > 0) {
      Serial.println(Wed8);
      writeFile("/Wed8.txt", Wed8);
      wed8 = Wed8;
    }

    if (Wed9.length() > 0) {
      Serial.println(Wed9);
      writeFile("/Wed9.txt", Wed9);
      wed9 = Wed9;
    }

    if (Wed10.length() > 0) {
      Serial.println(Wed10);
      writeFile("/Wed10.txt", Wed10);
      wed10 = Wed10;
    }

    if (Wed11.length() > 0) {
      Serial.println(Wed11);
      writeFile("/Wed11.txt", Wed11);
      wed11 = Wed11;
    }

    if (Wed12.length() > 0) {
      Serial.println(Wed12);
      writeFile("/Wed12.txt", Wed12);
      wed12 = Wed12;
    }

    if (Wed13.length() > 0) {
      Serial.println(Wed13);
      writeFile("/Wed13.txt", Wed13);
      wed13 = Wed13;
    }

    //Thursadays
    if (Thu1.length() > 0) {
      Serial.println(Thu1);
      writeFile("/Thu1.txt", Thu1);
      thu1 = Thu1;
    }

    if (Thu2.length() > 0) {
      Serial.println(Thu2);
      writeFile("/Thu2.txt", Thu2);
      thu2 = Thu2;
    }

    if (Thu3.length() > 0) {
      Serial.println(Thu3);
      writeFile("/Thu3.txt", Thu3);
      thu3 = Thu3;
    }

    if (Thu4.length() > 0) {
      Serial.println(Thu4);
      writeFile("/Thu4.txt", Thu4);
      thu4 = Thu4;
    }

    if (Thu5.length() > 0) {
      Serial.println(Thu5);
      writeFile("/Thu5.txt", Thu5);
      thu5 = Thu5;
    }

    if (Thu6.length() > 0) {
      Serial.println(Thu6);
      writeFile("/Thu6.txt", Thu6);
      thu6 = Thu6;
    }

    if (Thu7.length() > 0) {
      Serial.println(Thu7);
      writeFile("/Thu7.txt", Thu7);
      thu7 = Thu7;
    }

    if (Thu8.length() > 0) {
      Serial.println(Thu8);
      writeFile("/Thu8.txt", Thu8);
      thu8 = Thu8;
    }

    if (Thu9.length() > 0) {
      Serial.println(Thu9);
      writeFile("/Thu9.txt", Thu9);
      thu9 = Thu9;
    }

    if (Thu10.length() > 0) {
      Serial.println(Thu10);
      writeFile("/Thu10.txt", Thu10);
      thu10 = Thu10;
    }

    if (Thu11.length() > 0) {
      Serial.println(Thu11);
      writeFile("/Thu11.txt", Thu11);
      thu11 = Thu11;
    }

    if (Thu12.length() > 0) {
      Serial.println(Thu12);
      writeFile("/Thu12.txt", Thu12);
      thu12 = Thu12;
    }

    if (Thu13.length() > 0) {
      Serial.println(Thu13);
      writeFile("/Thu13.txt", Thu13);
      thu13 = Thu13;
    }
    //Friday
    if (Fri1.length() > 0) {
      Serial.println(Fri1);
      writeFile("/Fri1.txt", Fri1);
      fri1 = Fri1;
    }

    if (Fri2.length() > 0) {
      Serial.println(Fri2);
      writeFile("/Fri2.txt", Fri2);
      fri2 = Fri2;
    }

    if (Fri3.length() > 0) {
      Serial.println(Fri3);
      writeFile("/Fri3.txt", Fri3);
      fri3 = Fri3;
    }

    if (Fri4.length() > 0) {
      Serial.println(Fri4);
      writeFile("/Fri4.txt", Fri4);
      fri4 = Fri4;
    }

    if (Fri5.length() > 0) {
      Serial.println(Fri5);
      writeFile("/Fri5.txt", Fri5);
      fri5 = Fri5;
    }

    if (Fri6.length() > 0) {
      Serial.println(Fri6);
      writeFile("/Fri6.txt", Fri6);
      fri6 = Fri6;
    }

    if (Fri7.length() > 0) {
      Serial.println(Fri7);
      writeFile("/Fri7.txt", Fri7);
      fri7 = Fri7;
    }

    if (Fri8.length() > 0) {
      Serial.println(Fri8);
      writeFile("/Fri8.txt", Fri8);
      fri8 = Fri8;
    }

    if (Fri9.length() > 0) {
      Serial.println(Fri9);
      writeFile("/Fri9.txt", Fri9);
      fri9 = Fri9;
    }

    if (Fri10.length() > 0) {
      Serial.println(Fri10);
      writeFile("/Fri10.txt", Fri10);
      fri10 = Fri10;
    }

    if (Fri11.length() > 0) {
      Serial.println(Fri11);
      writeFile("/Fri11.txt", Fri11);
      fri11 = Fri11;
    }

    if (Fri12.length() > 0) {
      Serial.println(Fri12);
      writeFile("/Fri12.txt", Fri12);
      fri12 = Fri12;
    }

    if (Fri13.length() > 0) {
      Serial.println(Fri13);
      writeFile("/Fri13.txt", Fri13);
      fri13 = Fri13;
    }


    //      else {
    //        content = "{\"Error\":\"404 not found\"}";
    //        statusCode = 404;
    //        Serial.println("Sending 404");
    //      }
    content = "{\"Success\":\"saved to File System... you will be redirected to the home page\"}";
    statusCode = 200;

    server.sendHeader("Access-Control-Allow-Origin", "*");
    server.send(statusCode, "application/json", content);
    File Home = LittleFS.open("/home.html", "r");
    if (!Home) {
      Serial.println("Failed to open Home page for reading");

    }
    else {
      server.streamFile(Home, "text/html");
      Home.close();
    }

  });

}
void ringBell(){
  digitalWrite(BELL_PIN,HIGH);
  delay(2000);
  digitalWrite(BELL_PIN,LOW);
  delay(2000);
  return;
}
void alarm() {


  DateTime now = rtc.now();
  char buf1[] = "hh:mm";
  char sec[]="ss";

  unsigned long CurrentTime = millis();
 String Time=now.toString(buf1);
  while (CurrentTime - PreviousTime > 1000) {
    PreviousTime = CurrentTime;
    Serial.println(now.toString(buf1));
    Serial.println(now.toString(sec));
  }
  if(Time== mon1){
    Serial.println("!!!!!!ALARM!!!!!!");
    ringBell();
  }
}
