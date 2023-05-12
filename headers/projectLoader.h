#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "project.h"
#include "verbose.h"
#define CONFIG_FILE_PATH "storage\\project-list.txt"

class ProjectLoader {
private:
    std::vector<Project*> projects;
    std::vector<std::string> getProjectPaths();
    
public:
    ProjectLoader();
    ~ProjectLoader();

    std::vector<Project*> getProjects();

};