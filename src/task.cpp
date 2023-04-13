#include "../headers/task.h"
#include <iostream>

std::string Task::getDate(int offset){
    std::time_t t = std::time(0);  
    std::tm* now = std::localtime(&t);
    int year = now->tm_year;
    int month = now->tm_mon;
    int day = now->tm_mday;
    //set the date created
    this->dateCreated = MONTHS[month] + " " + std::to_string(day);
    //set the due date
    day = day + offset;
    while(day > DAYS_PER_MONTH[month]){
        //account for leap year
        if(year % 4 == 0 && month == 1){
            day--;
        }
        day = day - DAYS_PER_MONTH[month];
        month = month + 1;
        if (month == 12){
            month = 0;
            year++;
        }
    }
    return MONTHS[month] + " " + std::to_string(day);
}

Task::Task(){
    //does nothing
}

Task::Task(const std::string &title, int id, int daysUntilDueDate){
    this->title = title;
    this->id = id;
    this->status = Status::Backlog;
    //get current date
    std::time_t t = std::time(0);  
    std::tm* now = std::localtime(&t);
    int year = now->tm_year;
    int month = now->tm_mon;
    int day = now->tm_mday;
    //set the date created
    this->dateCreated = this->getDate(0);
    //set the due date
    this->dueDate = this->getDate(daysUntilDueDate);
}

Task::~Task(){
    std::cout << "Task Destructor\n";
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
void Task::setParentTask(std::shared_ptr<Task> parentTask){
    this->parentTask = parentTask;
}
std::shared_ptr<Task> Task::getParentTask(){
    return this->parentTask;
}
void Task::addSubTask(std::shared_ptr<Task> subTask){
    this->subTasks.push_back(subTask);
}
std::vector<std::shared_ptr<Task>> Task:: getSubTasks(){
    return this->subTasks;
}
void Task::addProgressNote(std::string note){
    //get current date
    std::string date = this->getDate(0);
    ProgressNote newNote = {note, date};
    
    this->progressNotes.push_back(newNote);
}
std::vector<ProgressNote> Task::getProgressNotes(){
    return this->progressNotes;
}
void Task::startTask(){
    this->status = Status::InProgress;
    this->dateStarted = this->getDate(0);
}
void Task::finishTask(){
    this->status = Status::Done;
    this->dateFinished = this->getDate(0);
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

void Task::addSubtaskToParent(std::shared_ptr<Task> subTask, std::shared_ptr<Task> parentTask){
    subTask->setParentTask(parentTask);
    parentTask->addSubTask(subTask);
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