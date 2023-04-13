#pragma once
#include <string>
#include <vector>
#include <memory>
#include <ctime>
#include <iostream>

const std::string MONTHS[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
const int DAYS_PER_MONTH[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

enum Status { Backlog, InProgress, Done};

typedef struct ProgressNote {
    std::string note;
    std::string date;
} ProgressNote;

class Task {
private:
    std::string title;
    int id;
    std::shared_ptr<Task> parentTask;
    std::vector<std::shared_ptr<Task>> subTasks;
    std::vector<ProgressNote> progressNotes;
    Status status;
    std::string dueDate;
    std::string dateCreated;
    std::string dateStarted;
    std::string dateFinished;

    std::string getDate(int offset);

public:
    Task();
    Task(const std::string &title, int id, int daysUntilDueDate);
    ~Task();

    //getter and setters
    void setTitle(std::string title);
    std::string getTitle();
    int getId();
    void setParentTask(std::shared_ptr<Task> parentTask);
    std::shared_ptr<Task> getParentTask();
    void addSubTask(std::shared_ptr<Task> subTask);
    std::vector<std::shared_ptr<Task>> getSubTasks();
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

    //helper function
    static void addSubtaskToParent(std::shared_ptr<Task> subTask, std::shared_ptr<Task> parentTask);

    //printing for debugging
    void printTask();

};