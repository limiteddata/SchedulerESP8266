#include <ScheduleTaskESP8266.h>


/**
 * Creates a task that can call a function
 * @param Label is the name for the task default: Unknown
 * @param Days is a bool array with the size 7 (su mo tu we th fr sa) to select wich day of the week you want to do the task default: {true,true,true,true,true,true,true}
 * @param Timestamp is a unix timestamp (GMT/UTC+0) at wich the task gets called
 * @param ToDoTask is a void reference to your function you want to call
 */
ScheduleTask::ScheduleTask(String Label, bool Days[7], unsigned long Timestamp, const std::function<void()>& ToDoTask){
    this->label = Label;
    this->timestamp = Timestamp;
    for (int i = 0; i < 7; i++) this->days[i] = Days[i];
    this->toDoTask = ToDoTask;
}

/**
 * Creates a task that can call a function
 * @param Label is the name for the task default: Unknown
 * @param Days is a bool array with the size 7 (su mo tu we th fr sa) to select wich day of the week you want to do the task default: {true,true,true,true,true,true,true}
 * @param Timestamp is a unix timestamp (GMT/UTC+0) at wich the task gets called
 * @param ToDoTask is a void reference to your function you want to call
 * @param Repeat If you set it to false the task will only fire once at the month day and hour it's set. default: true
 */

ScheduleTask::ScheduleTask(String Label, unsigned long Timestamp, const std::function<void()>& ToDoTask,bool Repeat){
    this->label = Label;
    this->timestamp = Timestamp;
    this->toDoTask = ToDoTask;
    this->repeat = Repeat;
}
/**
 * Creates a task that can call a function
 * @param Label is the name for the task default: Unknown
 * @param Timestamp is a unix timestamp (GMT/UTC+0) at wich the task gets called
 * @param ToDoTask is a void reference to your function you want to call
 */
ScheduleTask::ScheduleTask(String Label, unsigned long Timestamp, const std::function<void()>& ToDoTask){
    this->label = Label;
    this->timestamp = Timestamp;
    this->toDoTask = ToDoTask;
}

/**
 * Creates a task that can call a function
 * @param Timestamp is a unix timestamp (GMT/UTC+0) at wich the task gets called
 * @param ToDoTask is a void reference to your function you want to call
 */
ScheduleTask::ScheduleTask(bool Days[7], unsigned long Timestamp, const std::function<void()>& ToDoTask){
    this->timestamp = Timestamp;
    for (int i = 0; i < 7; i++) this->days[i] = Days[i];
    this->toDoTask = ToDoTask;
}

/**
 * Creates a task that can call a function
 * @param Timestamp is a unix timestamp (GMT/UTC+0) at wich the task gets called
 * @param ToDoTask is a void reference to your function you want to call
 */
ScheduleTask::ScheduleTask(unsigned long Timestamp, const std::function<void()>& ToDoTask){
    this->timestamp = Timestamp;
    this->toDoTask = ToDoTask;
}

/**
 * Compleates the task in curent day if it's not compleated
 * @param taskCompleted get's set to true after the task is done
 */
void ScheduleTask::doTask(){
    if (!this->taskCompleted){
        this->toDoTask();
        this->taskCompleted = true;
        Serial.print("Task ");
        Serial.print(this->label);
        Serial.print(" was compleated at ");
        Serial.println(this->timestamp);
    }
}
