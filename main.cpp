#include <iostream>
#include "headers/task.h"
#include "headers/question.h"
#include "headers/project.h"
#include "headers/projectLoader.h"

int main() {
   //load all projects
   ProjectLoader projectLoader = ProjectLoader();
   std::vector<Project*> projects = projectLoader.getProjects();
   for(int i = 0; i < projects.size(); i++){
      projects[i]->printProject();
   }
   //call command line interface manager

   return 0;
}