Please visit https://github.com/limiteddata/SchedulerESP8266 for latest code and documentation.

**SchedulerESP8266**

This is a library created for the esp8266 using NTPClient to create a time based scheduled events.

To use the library you need to create a Scheduler object (ex Scheduler scheduler), then call in the setup function scheduler.begin(); and in the loop function scheduler.update();.

To add a new schedule you can add them in the setup like this:

bool days[7] = {false, true, true, true, true, true, false};
scheduler.schedules.push_back(ScheduleTask("Task1 (repeatable only in working days)", days, 1604127570 ,task));

Result:
I'm doing this task
Task1 (repeatable only in working days) was compleated at 1604127570


scheduler.schedules.push_back(ScheduleTask("Task2 (repeatable every day)",1604128239 ,task));

Result:
I'm doing this task
Task2 (repeatable every day) was compleated at 1604128239


scheduler.schedules.push_back(ScheduleTask(1604128405 ,task));

Result:
I'm doing this task
Unknown was compleated at 1604128405


// in this case the task gets called only once
scheduler.schedules.push_back(ScheduleTask("Task3 (nonrepeatable)", 1604130753 ,task,false));

Result:
I'm doing this task
Task3 (nonrepeatable) was compleated at 1604130753
