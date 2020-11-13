#include <ScheduleTaskESP8266.h>
#include <Arduino.h>
#include <vector>
#include <NTPClient.h>
#include <WiFiUdp.h>


/*  * * * * * * * * * * * * * * * * * * * * * * * * * * *
https://github.com/limiteddata/SchedulerESP8266
Library created by limiteddata
Contact: limiteddata09@gmail.com
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

class Scheduler
{
private:
    int lastCurrentDay = -1;
public:
    std::vector<ScheduleTask> schedules;
    Scheduler();
    void update();
    void begin();
    void setUTC(int utc);
    void add(ScheduleTask &task);
    void Remove(int index);
    void RemoveAt(int Timestamp);
};
