#pragma once
#include <vector>
#include <string>
#include "task.h"
#include "question.h"

class Project {
private:
    std::string title;
    std::string pathToConfig;
    std::vector<Task*> tasks;
    std::vector<Question*> questions;
public:
    Project();
    Project(std::string title, std::string pathToConfig);
    Project(std::string title, std::string pathToConfig, std::vector<Task*> tasks, std::vector<Question*> questions);
    ~Project();

    void setTitle(std::string title);
    std::string getTitle();

    void setPathToConfig(std::string pathToConfig);
    std::string getPathToConfig();

    void setTasks(std::vector<Task*> tasks);
    void addTask(Task* task);
    std::vector<Task*> getTasks();

    void setQuestions(std::vector<Question*> questions);
    void addQuestion(Question* question);
    std::vector<Question*> getQuestions();

    void printProject();
};