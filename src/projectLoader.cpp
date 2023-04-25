#include "../headers/projectLoader.h"


//public methods
ProjectLoader::ProjectLoader(){
    //get all of the path
    std::vector<std::string> projectPaths = this->getProjectPaths();
    //load all of the projects
    for(int i = 0; i < projectPaths.size(); i++){
        this->projects.push_back(Project(projectPaths[i]));
    }
}

ProjectLoader::~ProjectLoader(){
    std::cout << "Project loader destructor\n";
}

std::vector<Project> ProjectLoader::getProjects(){
    return this->projects;
}

std::vector<std::string> ProjectLoader::getProjectPaths(){
    std::vector<std::string> projectPaths;
    std::ifstream projectPathFile(CONFIG_FILE_PATH);
    if(projectPathFile.is_open()){
        std::string path;
        while(std::getline(projectPathFile, path)){
            projectPaths.push_back(path);
        }
        projectPathFile.close();
    }
    else{
        std::cout << "Could not open file\n";
    }
    return projectPaths;
}