#pragma once
#include "task.h"
#include <string>

class Question {
private:
    std::string message;
    std::string answer;
    Task* linkedTask;
public:
    Question();
    Question(std::string message, Task* linkedTask);
    ~Question();

    void setMessage(std::string message);
    std::string getMessage();

    void setAnswer(std::string answer);
    std::string getAnswer();

    void setLinkedTask(Task* linkedTask);
    Task* getLinkedTask();

    void printQuestion();

};