#include "../headers/task.h"
#include "../headers/date.h"
#include <iostream>

//private methods

//public methods

Task::Task(){
    //does nothing
}

Task::Task(const std::string &title, int id, int daysUntilDueDate){
    this->title = title;
    this->id = id;
    this->status = Status::Backlog;
    this->parentTask = nullptr; 
    //set the date created
    this->dateCreated = Date::getDate(0);
    //set the due date
    this->dueDate = Date::getDate(daysUntilDueDate);
}

Task::~Task(){
    std::cout << "Task Destructor for " << this->title << std::endl;
}

void Task:: setTitle(std::string title){
    this->title = title;
}
std::string Task::getTitle(){
    return this->title;
}
int Task::getId(){
    return this->id;
}
void Task::setParentTask(Task* parentTask){
    this->parentTask = parentTask;
}
Task* Task::getParentTask(){
    return this->parentTask;
}
void Task::addSubTask(Task* subTaskToAdd){
    this->subTasks.push_back(subTaskToAdd);
    subTaskToAdd->parentTask = this;
}
void Task::removeSubTask(Task* subTaskToRemove){
    for(int i = 0; i < this->subTasks.size(); i++){
        if(this->subTasks[i]->id == subTaskToRemove->getId()){
            this->subTasks.erase(this->subTasks.begin() + i);
            break;
        }
    }
    subTaskToRemove->parentTask = nullptr;
}
std::vector<Task*> Task:: getSubTasks(){
    return this->subTasks;
}
void Task::addProgressNote(std::string note){
    //get current date
    std::string date = Date::getDate(0);
    ProgressNote newNote = {note, date};
    
    this->progressNotes.push_back(newNote);
}
std::vector<ProgressNote> Task::getProgressNotes(){
    return this->progressNotes;
}
void Task::startTask(){
    this->status = Status::InProgress;
    this->dateStarted = Date::getDate(0);
}
void Task::finishTask(){
    this->status = Status::Done;
    this->dateFinished = Date::getDate(0);
}
Status Task::getStatus(){
    return this->status;
}
std::string Task::getDueDate(){
    return this->dueDate;
}
void Task::setDueDate(std::string date){
    this->dueDate = date;
}
std::string Task::getDateCreated(){
    return this->dateCreated;
}
std::string Task::getDateStarted(){
    return this->dateStarted;
}
std::string Task::getDateFinished(){
    return this->dateFinished;
}

void Task::printTask(){
    std::cout << "Title: " << this->title << std:: endl;
    //print the id
    std::cout << "ID: " << this->id << std::endl;
    //print the parent task
    std::cout << "Parent task: ";
    if(this->parentTask == nullptr){
        std::cout << "None" << std::endl;
    }
    else{
        std::cout << this->parentTask->title  << std::endl;
    }
    //print the sub tasks
    if(this->subTasks.size() > 0){
        std::cout << "----- Sub tasks -----" << std::endl;
        for(int i = 0; i < this->subTasks.size(); i++){
            std::cout << this->subTasks[i]->title << std::endl;
        }    
        std::cout << "---------------------" << std::endl;
    }
    else{
        std::cout << "No sub tasks" << std::endl;
    }

    //print the progress notes
    if(this->progressNotes.size() > 0){
        std::cout << "----- Progress notes -----" << std::endl;
        for(int i = 0; i < this->progressNotes.size(); i++){
            std::cout << this->progressNotes[i].note << " - Date: " << this->progressNotes[i].date << std::endl;
        }    
        std::cout << "--------------------------" << std::endl;
    }
    else{
        std::cout << "No progress notes" << std::endl;
    }
    //print the status
    if(this->status == Status::Backlog){
        std::cout << "Status: Backlog" << std::endl;
    }
    else if(this->status == Status::InProgress){
        std::cout << "Status: In progress" << std::endl;
    }
    else{
        std::cout << "Status: Done" << std::endl;
    }
    //print the due date
    std::cout << "Due Date: " << this->dueDate << std::endl;
    //print the date created
    std::cout << "Date Created: " << this->dateCreated << std::endl;
    //print the date started
    std::cout << "Date Started: " << this->dateStarted << std::endl;
    //print the date finished
    std::cout << "Date Finished: " << this->dateFinished << std::endl;
}

void Task::printTaskTree(int level){
    if(level == 0){
        std::cout << "----- Task tree starting at " << this->title << " -----" << std::endl;
    }
    for(int i = 0; i < level; i++){
        if(i % 2 == 0){
            std::cout << "|";
        }
        std::cout << " ";
    }
    std::cout << this->title << std::endl;
    for(int i = 0; i < this->subTasks.size(); i++){
        subTasks[i]->printTaskTree(level + 2);
    }
}
void Task::printParents(){
    std::cout << "----- Parents of " << this->title << " -----" << std::endl;
    Task* currentTask = this->parentTask;
    while(currentTask != nullptr){
        std::cout << currentTask->title << std::endl;
        currentTask = currentTask->parentTask;
    }
}
