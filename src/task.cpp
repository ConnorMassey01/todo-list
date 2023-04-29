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

Task::Task(const std::string &title, int id, const std::vector<ProgressNote> &progressNotes, Status status, const std::string &dueDate,
           const std::string &dateCreated, const std::string &dateStarted, const std::string &dateFinished){
    this->title = title;
    this->id = id;
    this->progressNotes = progressNotes;
    this->status = status;
    this->dueDate = dueDate;
    this->dateCreated = dateCreated;
    this->dateStarted = dateStarted;
    this->dateFinished = dateFinished;
    this->parentTask = nullptr; 
}

Task::~Task(){
    std::cout << "Task Destructor for " << this->title << "\n";
    //delete all subtasks
    for(int i = 0; i < this->subTasks.size(); i++){
        std::cout << "Deleting subTask: " << this->subTasks[i]->getTitle() << "\n";
        delete this->subTasks[i];
    }
    this->subTasks.clear();
    this->parentTask = nullptr;
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
        //find the subTask with the correct id
        if(this->subTasks[i]->id == subTaskToRemove->getId()){
            this->subTasks.erase(this->subTasks.begin() + i);
            break;
        }
    }
    //delete the subTaskToRemove
    delete subTaskToRemove;
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
    std::cout << "ID: " << this->id << "\n";
    //print the parent task
    std::cout << "Parent task: ";
    if(this->parentTask == nullptr){
        std::cout << "None\n";
    }
    else{
        std::cout << this->parentTask->title  << "\n";
    }
    //print the sub tasks
    if(this->subTasks.size() > 0){
        std::cout << "----- Sub tasks -----\n";
        for(int i = 0; i < this->subTasks.size(); i++){
            std::cout << this->subTasks[i]->title << "\n";
        }    
        std::cout << "---------------------\n";
    }
    else{
        std::cout << "No sub tasks\n";
    }

    //print the progress notes
    if(this->progressNotes.size() > 0){
        std::cout << "----- Progress notes -----\n";
        for(int i = 0; i < this->progressNotes.size(); i++){
            std::cout << this->progressNotes[i].note << " - Date: " << this->progressNotes[i].date << "\n";
        }    
        std::cout << "--------------------------\n";
    }
    else{
        std::cout << "No progress notes\n";
    }
    //print the status
    if(this->status == Status::Backlog){
        std::cout << "Status: Backlog\n";
    }
    else if(this->status == Status::InProgress){
        std::cout << "Status: In progress\n";
    }
    else{
        std::cout << "Status: Done\n";
    }
    //print the due date
    std::cout << "Due Date: " << this->dueDate << "\n";
    //print the date created
    std::cout << "Date Created: " << this->dateCreated << "\n";
    //print the date started
    std::cout << "Date Started: " << this->dateStarted << "\n";
    //print the date finished
    std::cout << "Date Finished: " << this->dateFinished << "\n\n";
}

void Task::printTaskTree(int level){
    if(level == 0){
        std::cout << "----- Task tree starting at " << this->title << " -----\n";
    }
    for(int i = 0; i < level; i++){
        if(i % 2 == 0){
            std::cout << "|";
        }
        std::cout << " ";
    }
    std::cout << this->title << "\n";
    for(int i = 0; i < this->subTasks.size(); i++){
        subTasks[i]->printTaskTree(level + 2);
    }
}
void Task::printParents(){
    std::cout << "----- Parents of " << this->title << " -----\n";
    Task* currentTask = this->parentTask;
    while(currentTask != nullptr){
        std::cout << currentTask->title << "\n";
        currentTask = currentTask->parentTask;
    }
}
