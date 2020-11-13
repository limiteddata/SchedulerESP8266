#include <Arduino.h>

class ScheduleTask
{
public:
    std::function<void()> toDoTask;
    bool taskCompleted = false;
    String label="Unknown";
    unsigned long timestamp = false;
    bool days[7] = {true,true,true,true,true,true,true};
    bool repeat=true;
    bool enable=true;
    ScheduleTask(String Label, bool Days[7], unsigned long Timestamp, const std::function<void()>& ToDoTask);
    ScheduleTask(String Label, unsigned long Timestamp, const std::function<void()>& ToDoTask, bool Repeat);
    ScheduleTask(String Label, unsigned long Timestamp, const std::function<void()>& ToDoTask);
    ScheduleTask(bool Days[7], unsigned long Timestamp, const std::function<void()>& ToDoTask);
    ScheduleTask(unsigned long Timestamp, const std::function<void()>& ToDoTask);
    void doTask();
};
