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
 * Add a new ScheduleTask
 */
void Scheduler::add(ScheduleTask &task){
    this->schedules.push_back(task);
    Serial.print("Task ");
    Serial.print(task.label);
    Serial.print(" at ");
    Serial.print(task.timestamp);
    Serial.println(" has been added!");
}

/**
 * Remove the schedule at by the index
 */
void Scheduler::Remove(int index){
    Serial.print("Task ");
    Serial.print(schedules[index].label);
    Serial.print(" at ");
    Serial.print(schedules[index].timestamp);
    Serial.println(" has been removed!");
    this->schedules.erase(this->schedules.begin() + index);
}

/**
 * Remove the task at the specified timestamp
 */
void Scheduler::RemoveAt(int Timestamp){
    for (size_t i = 0; i < this->schedules.size(); i++)
    {
        if (this->schedules[i].timestamp == Timestamp){
            Serial.print("Task ");
            Serial.print(schedules[i].label);
            Serial.print(" at ");
            Serial.print(schedules[i].timestamp);
            Serial.println(" has been removed!");
            this->schedules.erase(this->schedules.begin() + i);
            break;
        }
    }
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
        for (int i = 0; i < this->schedules.size(); i++) if (this->schedules[i].repeat == true) this->schedules[i].taskCompleted = false;
    }

    unsigned long currentTime = ntpTime.getEpochTime();
    for (int i = 0; i < schedules.size(); i++)
    {
        // check if the current time matches the timestamp for each task
        if (this->schedules[i].repeat == true){
            if (this->schedules[i].days[currentDay] == true && this->schedules[i].enable == true){
                if (currentTime % 86400L  == this->schedules[i].timestamp % 86400L){
                    this->schedules[i].doTask();
                }
            }
        }else{
            if (currentTime == this->schedules[i].timestamp && this->schedules[i].taskCompleted == false && this->schedules[i].enable == true) this->schedules[i].doTask();
        }

    }
}
