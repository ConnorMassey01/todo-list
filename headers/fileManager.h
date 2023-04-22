#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "project.h"

class FileManager {
private:
    std::string configurationFilePath;
    std::vector<Project> projects;
    //Load project
    Project loadProject(std::string pathToProject);
    std::vector<std::string> getProjectPaths();
    
public:
    FileManager();
    ~FileManager();

    void saveProject(Project project);

    std::vector<Project> getProjects();

};