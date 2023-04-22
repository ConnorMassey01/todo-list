#include "../headers/fileManager.h"

//private methods
Project FileManager::loadProject(std::string pathToProject){
    std::ifstream projectFile(pathToProject);
    if(projectFile.is_open()){
        projectFile.close();
    }
    else{
        throw std::invalid_argument("Could not open file: " + pathToProject);
    }
    return Project();
}
std::vector<std::string> FileManager::getProjectPaths(){
    std::vector<std::string> projectPaths;
    std::ifstream projectPathFile(this->configurationFilePath);
    if(projectPathFile.is_open()){
        std::string path;
        while(std::getline(projectPathFile, path)){
            std::cout << path << std::endl;
            projectPaths.push_back(path);
        }
        projectPathFile.close();
    }
    else{
        std::cout << "Could not open file" << std::endl;
    }
    return projectPaths;
}
//public methods
FileManager::FileManager(){
    this->configurationFilePath = "projects\\project-list.txt";
    //get all of the path
    std::vector<std::string> projectPaths = this->getProjectPaths();
    //load all of the projects
    for(int i = 0; i < projectPaths.size(); i++){
        try{
            Project project = this->loadProject(projectPaths[i]);
            this->projects.push_back(project);
        }
        catch (std::invalid_argument error){
            std::cout << error.what() << std::endl;
        }
    }
}

FileManager::~FileManager(){
    std::cout << "File manager destructor" << std::endl;
}

void FileManager::saveProject(Project project){
    //create a text document to store the project

    //add path to file to the configuration file
}