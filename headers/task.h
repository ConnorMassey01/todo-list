#pragma once
#include <string>
#include <vector>
#include <iostream>


enum Status { Backlog, InProgress, Done};

typedef struct ProgressNote {
    std::string note;
    std::string date;
} ProgressNote;

class Task {
private:
    std::string title;
    int id;
    Task* parentTask;
    std::vector<Task*> subTasks;
    std::vector<ProgressNote> progressNotes;
    Status status;
    std::string dueDate;
    std::string dateCreated;
    std::string dateStarted;
    std::string dateFinished;
public:
    Task();
    Task(const std::string &title, int id, int daysUntilDueDate);
    ~Task();

    //getter and setters
    void setTitle(std::string title);
    std::string getTitle();

    int getId();

    void setParentTask(Task* parentTask);
    Task* getParentTask();
    
    void addSubTask(Task* subTask);
    void removeSubTask(Task* subTask);
    std::vector<Task*> getSubTasks();

    void addProgressNote(std::string note);
    std::vector<ProgressNote> getProgressNotes();

    void startTask();
    void finishTask();

    Status getStatus();

    std::string getDueDate();
    void setDueDate(std::string date);

    std::string getDateCreated();
    std::string getDateStarted();
    std::string getDateFinished();

    //printing for debugging
    void printTask();
    void printTaskTree(int level);
    void printParents();

};