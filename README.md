Please visit https://github.com/limiteddata/SchedulerESP8266 for latest code and documentation.

**SchedulerESP8266**

This is a library created for the esp8266 using NTPClient to create a time based scheduled events.

To use the library you need to create a Scheduler object (ex Scheduler scheduler), then call in the setup function scheduler.begin(); and in the loop function scheduler.update();.

To add a new schedule you can add them in the setup like this:

```.cpp

bool days[7] = {false, true, true, true, true, true, false};

scheduler.add(ScheduleTask("Task1 (repeatable only in working days)", days, 1604127570 ,task));


scheduler.add(ScheduleTask("Task3 (nonrepeatable)", 1604130753 ,task,false));


/* using lambda functions to call multiple functions*/
String _name = "";
int _a = 11;
int _b = 21;

ScheduleTask task = ScheduleTask("Task1", days, 1605310201,  
  [=](){    
      sayHi(_name);
      sum(_a,_b);
  });
scheduler.add(task);

```
