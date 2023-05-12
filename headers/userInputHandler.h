#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "projectLoader.h"
#include "project.h"
class UserInputHandler {
private:
    //----- variables -----
    ProjectLoader* projectLoader;
    std::vector<Project*> projects;
    Project* activeProject;
    //----- methods -----
    void printStartMessage();
    //print a help message for the provided subject
    void printHelpMessage(const std::string &subject);
    void printHeader(const std::string &message);

    void handleCommand(const std::string &command);

    //Project management functions
    void createProject();
    void listProjects();
    void selectProject();

public:
    UserInputHandler();
    ~UserInputHandler();

    //Function to start the program and prompt the user for input
    void start();
};