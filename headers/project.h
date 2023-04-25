#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <stack>
#include <map>
#include "task.h"
#include "question.h"

class Project {
private:
    std::string title;
    std::string pathToConfig;
    std::vector<Task*> tasks;
    std::vector<Question*> questions;

    void load();
    std::vector<Task*> loadTasks(std::ifstream& projectFile);
    std::vector<Question*> loadQuestions(std::ifstream& projectFile);
    void saveFileLocation();
    void saveTask(std::ofstream& projectFile, Task* task);
    void saveQuestions(std::ofstream& projectFile);
    
public:
    Project();
    Project(std::string pathToConfig);
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

    void save();

    void printProject();
};