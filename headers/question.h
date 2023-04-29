#pragma once
#include "task.h"
#include <string>

class Question {
private:
    std::string message;
    std::string answer;
    int linkedTaskId;
public:
    Question();
    Question(std::string message, int linkedTaskId);
    Question(std::string message, std::string answer, int linkedTaskId);
    ~Question();

    void setMessage(std::string message);
    std::string getMessage();

    void setAnswer(std::string answer);
    std::string getAnswer();

    void setLinkedTaskId(int linkedTaskId);
    int getLinkedTaskId();

    void printQuestion();

};