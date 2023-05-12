#include "../headers/task.h"
#include "../headers/question.h"
#include "../headers/project.h"
#include "../headers/projectLoader.h"
#include "../headers/userInputHandler.h"

UserInputHandler::UserInputHandler(){
    //load all projects
    this->projectLoader = new ProjectLoader();
    this->projects = projectLoader->getProjects();
}

UserInputHandler::~UserInputHandler(){
    if(verbose) std::cout << "userInputHandler Destructor";
    delete this->projectLoader;
}

void UserInputHandler::printHeader(const std::string& message){
    std::cout << "\n\n----- " + message + " -----\n\n";
}

void UserInputHandler::printStartMessage(){
    std::cout << "\nWelcome to the TODO-LIST command line interface\n\n";
    std::cout << "If you are unfamiliar with the tool, run <help commands> to see the list of commands. Otherwise, open a project and get to work!\n\n";
}

void UserInputHandler::printHelpMessage(const std::string &subject){
    if(subject == "commands"){
        std::cout << "\n----- List of Commands -----\n\n";
        std::cout << "- list projects\n";
        std::cout << "- create project\n";
        std::cout << "- open <project name>\n";
        std::cout << "- display project <project name>\n";

        std::cout << "- create task\n";
        std::cout << "- start <task name>\n";
        std::cout << "- finish <task name>\n";
        std::cout << "- update <task name>\n";
        std::cout << "- display task <task name>\n";

        std::cout << "- exit\n\n";

        std::cout << "For help with any of these commands run --help <command name>\n\n";
    }
    else{
        std::cout << "Subject: " + subject + " not found.\n";
    }
}

void UserInputHandler::handleCommand(const std::string &command){
    if(command == "help"){
        std::string subject;
        std::cin >> subject;
        this->printHelpMessage(subject);
    }
    else{
        std::cout << "Command: " + command + " can't be identified.\n";
    }
}

void UserInputHandler::start(){
    this->printStartMessage();

    //infinite loop of waiting for user input and responding
    while(true){
        std::string input;
        std::cin >> input; 
        if(input == "exit") break;
        this->handleCommand(input);
    }
    this->printHeader("Project List");
    for(int i = 0; i < projects.size(); i++){
        std::cout << this->projects[i]->getTitle() << '\n';
    }
}