#include "../headers/project.h"

//private methods

//public methods

Project::Project(){
    this->title = "";
    this->pathToConfig = "";
}
Project::Project(std::string title, std::string pathToConfig){
    this->title = title;
    this->pathToConfig = pathToConfig;
}
Project::Project(std::string title, std::string pathToConfig, std::vector<Task*> tasks, std::vector<Question*> questions){
    this->title = title;
    this->pathToConfig = pathToConfig;
    this->tasks = tasks;
    this->questions = questions;
}
Project::~Project(){
    std::cout << "Project destructor for: " << this->title << std::endl;
}

void Project::setTitle(std::string title){
    this->title = title;
}
std::string Project::getTitle(){
    return this->title;
}

void Project::setPathToConfig(std::string pathToConfig){
    this->pathToConfig = pathToConfig;
}
std::string Project::getPathToConfig(){
    return this->pathToConfig;
}

void Project::setTasks(std::vector<Task*> tasks){
    this->tasks = tasks;
}
void Project::addTask(Task* task){
    this->tasks.push_back(task);
}
std::vector<Task*> Project::getTasks(){
    return this->tasks;
}


void Project::setQuestions(std::vector<Question*> questions){
    this->questions = questions;
}
void Project::addQuestion(Question* question){
    this->questions.push_back(question);
}
std::vector<Question*> Project::getQuestions(){
    return this->questions;
}

void Project::printProject(){
    std::cout << "--- Project ---" << std::endl;
    std::cout << "Title: " << this->title << std::endl;
    std::cout << "Path to config: " << this->pathToConfig << std::endl;
    std::cout << "Tasks: " << std::endl;
    for(int i = 0; i < this->tasks.size(); i++){
        std::cout << this->tasks[i]->getTitle() << std::endl;
    }
    std::cout << "Questions: " << std::endl;
    for(int i = 0; i < this->questions.size(); i++){
        this->questions[i]->printQuestion();
    }
}