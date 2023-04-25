#include "../headers/task.h"
#include "../headers/question.h"
#include <iostream>

//private methods

//public methods

Question::Question(){
    this->message = "";
    this->answer = "";
    this->linkedTask = nullptr;
}

Question::Question(std::string message, Task* linkedTask){
    this->message = message;
    this->answer = "";
    this->linkedTask = linkedTask;
}

Question::~Question(){
    std::cout << "Question destructor" << "\n";
}

void Question::setMessage(std::string message){
    this->message = message;
}
std::string Question::getMessage(){
    return this->message;
}

void Question::setAnswer(std::string answer){
    this->answer = answer;
}
std::string Question::getAnswer(){
    return this->answer;
}

void Question::setLinkedTask(Task* linkedTask){
    this->linkedTask = linkedTask;
}
Task* Question::getLinkedTask(){
    return this->linkedTask;
}

void Question::printQuestion(){
    std::cout << "--- Question ---" << "\n";
    std::cout << "Q: " << this->message << "\n";
    std::cout << "A: " << this->answer << "\n";
    if(this->linkedTask != nullptr){
        std::cout << "Task: " << this->linkedTask->getTitle() << "\n";
    }
    
}