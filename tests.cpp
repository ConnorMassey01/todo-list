#include <iostream>
#include "headers/task.h"
#include "headers/question.h"
#include "headers/project.h"
#include "headers/projectLoader.h"
#include "headers/userInputHandler.h"

void testTaskClass(){
   Task* parentTask = new Task("Parent", 0, 7);
   parentTask->addProgressNote("Note on progress");
   parentTask->startTask();
   parentTask->finishTask();
   parentTask->printTask();

   Task* childTask = new Task("Child", 1, 4);
   Task* otherChildTask = new Task("Other child", 1, 4);
   Task* grandchildTask = new Task("Grandchild", 1, 4);
   childTask->addProgressNote("This is my message to add");

   parentTask->addSubTask(childTask);
   parentTask->addSubTask(otherChildTask);
   childTask->addSubTask(grandchildTask);

   parentTask->printTaskTree(0);
   grandchildTask->printParents();

   parentTask->removeSubTask(childTask);
   grandchildTask = nullptr;
   childTask = nullptr;
   parentTask->printTaskTree(0);

   delete parentTask;

}

void testQuestionClass(){
   Task* exampleTask = new Task("Example Task", 0, 3);
   Question* myQuestion = new Question("Example Question", exampleTask->getId());
   myQuestion->printQuestion();
   myQuestion->setAnswer("This is the answer");
   myQuestion->printQuestion();
   delete exampleTask;
   delete myQuestion;
}

void testProjectClass(){
   Task* exampleTask = new Task("Example Task", 0, 9);
   Task* exampleChildTask = new Task("Example Child Task", 1, 3);
   exampleTask->addSubTask(exampleChildTask);
   std::vector<Task*> tasks;
   tasks.push_back(exampleTask);

   std::vector<Question*> questions;
   Question* myQuestion = new Question("Example Question", exampleTask->getId());
   myQuestion->setAnswer("This is my answer");
   questions.push_back(myQuestion);

   Project* exampleProject = new Project("Second Example Project", "storage\\exampleProject.bin", tasks, questions);
   exampleProject->printProject();
   //save the project to storage at the location provided in the constructor
   exampleProject->save();
   //free the memory
   delete exampleProject;
}

void testProjectLoader(){
   //load all projects
   ProjectLoader projectLoader = ProjectLoader();
   std::cout << "Projects loaded\n";
   std::vector<Project*> projects = projectLoader.getProjects();
   //print all of the projects
   for(int i = 0; i < projects.size(); i++){
      std::cout << "\n";
      projects[i]->printProject();
   }
   std::cout << "\n";
}

void testUserInputHandler(){
   UserInputHandler userInputHandler = UserInputHandler();
   userInputHandler.start();
}

int main() {
   //testTaskClass();
   //testQuestionClass();
   //testProjectClass();
   //testProjectLoader();
   testUserInputHandler();
   return 0;
}