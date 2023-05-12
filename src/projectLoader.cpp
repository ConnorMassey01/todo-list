#include "../headers/projectLoader.h"

//public methods
ProjectLoader::ProjectLoader(){
    //get all of the path
    std::vector<std::string> projectPaths = this->getProjectPaths();
    //load all of the projects
    for(int i = 0; i < projectPaths.size(); i++){
        this->projects.push_back(new Project(projectPaths[i]));
    }
}

ProjectLoader::~ProjectLoader(){
    if(verbose) std::cout << "Project loader destructor\n";
    for(int i = 0; i < this->projects.size(); i++){
        if(verbose) std::cout << "----- Delete project " << i << ": " << this->projects[i]->getTitle() << " -----\n";
        delete this->projects[i]; //calls the projects destructor
    }
    this->projects.clear();
}

std::vector<Project*> ProjectLoader::getProjects(){
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