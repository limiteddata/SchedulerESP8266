#include <ESP8266WiFi.h>
#include <SchedulerESP8266.h>

/*
Example using lambda functions to call multiple function with different 
parameters and capture outside variables in the task function
*/

const char *ssid     = "";
const char *password = "";

Scheduler scheduler;

void sum(int a, int b){
  Serial.println(a+b);
}
void sayHi(String a){
  Serial.println("Hi "+a);
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while ( WiFi.status() != WL_CONNECTED ) {
    delay (500);
    Serial.print (".");
  }
  scheduler.begin();
  
  bool days[7] = {true, true, true, true, true, true, true};

  String _name = "";
  int _a = 11;
  int _b = 21;
  
  ScheduleTask task = ScheduleTask("Task1", days, 1605310201,  
    [=](){    
        sayHi(_name);
        sum(_a,_b);
    });
  scheduler.add(task);

  scheduler.Remove(0);
  //or remove at timestamp
  //scheduler.RemoveAt(1605310201);
}

void loop() {
  scheduler.update();
}
/*
Result:
Task Task1 at 1605222480 has been added!
Hi 
32
Task Task1 was compleated at 1605222480
*/
