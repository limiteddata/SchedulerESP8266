#include <ESP8266WiFi.h>
#include <SchedulerESP8266.h>

/*
 * This is a timed based scheduler (NTP)
 * to wich you can attach a void function
 * that's called when the timestamp matches the current time
 */

const char *ssid     = "";
const char *password = "";

Scheduler scheduler;

// This function get's called when the task is due
void task(){
  Serial.println("I'm doing this task");
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while ( WiFi.status() != WL_CONNECTED ) {
    delay (500);
    Serial.print (".");
  }

  scheduler.begin();

  /*You can set in what day of the week the task can be done in this order:
    Su Mo Tu We Th Fr Sa*/
  bool taskWeek[7] = {false, true, true, true, true, true, false};

  scheduler.add(ScheduleTask("Task1 (repeatable only in working days)", taskWeek, 1604127570 ,task));
  /*
  Result:
  I'm doing this task
  Task1 (repeatable only in working days) was compleated at 1604127570
  */
  scheduler.add(ScheduleTask("Task2 (repeatable every day)",1604128239 ,task));
  /*
  Result:
  I'm doing this task
  Task2 (repeatable every day) was compleated at 1604128239
  */
  scheduler.add(ScheduleTask(1604128405 ,task));
  /*  
  Result:
  I'm doing this task
  Unknown was compleated at 1604128405
 */
  // in this case the task gets called only once
  scheduler.add(ScheduleTask("Task3 (nonrepeatable)", 1604130753 ,task,false));
  /* 
  Result:
  I'm doing this task
  Task3 (nonrepeatable) was compleated at 1604130753
   */
}

void loop() {
  scheduler.update();
}
