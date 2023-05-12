#include "../headers/task.h"
#include "../headers/question.h"
#include <iostream>

//private methods

//public methods

Question::Question(){
    this->message = "";
    this->answer = "";
}

Question::Question(std::string message, int linkedTaskId){
    this->message = message;
    this->answer = "";
    this->linkedTaskId = linkedTaskId;
}

Question::Question(std::string message, std::string answer, int linkedTaskId){
    this->message = message;
    this->answer = answer;
    this->linkedTaskId = linkedTaskId;
}

Question::~Question(){
    if(verbose) std::cout << "Question destructor" << "\n";
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

void Question::setLinkedTaskId(int linkedTaskId){
    this->linkedTaskId = linkedTaskId;
}
int Question::getLinkedTaskId(){
    return this->linkedTaskId;
}

void Question::printQuestion(){
    std::cout << "--- Question ---" << "\n";
    std::cout << "Q: " << this->message << "\n";
    std::cout << "A: " << this->answer << "\n";
    std::cout << "Task id: " << this->linkedTaskId << "\n\n";
}