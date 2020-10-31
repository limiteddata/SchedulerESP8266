#include <SchedulerESP8266.h>


WiFiUDP ntpUDP;
NTPClient ntpTime(ntpUDP);

Scheduler::Scheduler(){
}

/**
 * Initializes the NTPClient to get the time
 */
void Scheduler::begin(){
    ntpTime.begin();
}

/**
 * Sets the offset to the NTPClient and also for all the tasks, recommended to use GMT/UTC+0
 */
void Scheduler::setUTC(int utc){
    ntpTime.setTimeOffset(utc * 60 * 60);  
    for (int i = 0; i < this->schedules.size(); i++) this->schedules[i].timestamp+=utc * 60 * 60; 
}

/**
 * Updates the current time and checks all the schedules for tasks
 */
void Scheduler::update(){
    ntpTime.update();
    int currentDay = ntpTime.getDay();   
    if (this->lastCurrentDay != currentDay){
        // make all the task doable for this next day
        this->lastCurrentDay = currentDay;
        for (int i = 0; i < this->schedules.size(); i++) if (this->schedules[i].repeat) this->schedules[i].taskCompleted = false;
    }
    
    unsigned long currentTime = ntpTime.getEpochTime();   
    for (int i = 0; i < schedules.size(); i++)
    {
        // check if the current time matches the timestamp for each task
        if (this->schedules[i].repeat == true){
            if (this->schedules[i].days[currentDay] == true){
                if (currentTime % 86400L  == this->schedules[i].timestamp % 86400L){
                    this->schedules[i].doTask();
                }
            }
        }else{
            if (currentTime == this->schedules[i].timestamp && this->schedules[i].taskCompleted == false) this->schedules[i].doTask();   
        }

    }
}
