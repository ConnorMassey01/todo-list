#include <iostream>
#include "headers/task.h"
#include "headers/question.h"
#include "headers/project.h"
#include "headers/projectLoader.h"

void testTaskClass(){
   Task parentTask = Task("Parent", 0, 7);
   parentTask.addProgressNote("Note on progress");
   parentTask.startTask();
   parentTask.finishTask();
   parentTask.printTask();

   Task childTask = Task("Child", 1, 4);
   Task otherChildTask = Task("Other child", 1, 4);
   Task grandchildTask = Task("Grandchild", 1, 4);
   childTask.addProgressNote("This is my message to add");

   parentTask.addSubTask(&childTask);
   parentTask.addSubTask(&otherChildTask);
   childTask.addSubTask(&grandchildTask);
   parentTask.printTaskTree(0);
   grandchildTask.printParents();

   parentTask.removeSubTask(&childTask);
   parentTask.printTaskTree(0);
   childTask.printParents();
   grandchildTask.printParents();
}

void testQuestionClass(){
   Task exampleTask = Task("Example Task", 0, 3);
   Question myQuestion("Example Question", &exampleTask);
   myQuestion.printQuestion();
   myQuestion.setAnswer("This is the answer");
   myQuestion.printQuestion();
}

void testProjectClass(){
   Task exampleTask = Task("Example Task", 0, 3);
   Question myQuestion = Question("Example Question", &exampleTask);
   std::vector<Task*> tasks;
   tasks.push_back(&exampleTask);
   std::vector<Question*> questions;
   questions.push_back(&myQuestion);
   Project exampleProject("Example Project", "storage/exampleProject.bin", tasks, questions);
   exampleProject.printProject();
}

void testProjectLoader(){
   //create an example project
   Project project = Project("Example Project", "storage\\example.bin");
   Task exampleTask = Task("Example Task", 0, 3);
   Task childTask = Task("Child", 1, 4);
   Task grandchildTask = Task("Grandchild", 2, 6);
   Task secondChildTask = Task("Second child", 3, 3);
   Task secondExampleTask = Task("Second Example", 4, 2);
   Task secondExampleChildTask = Task("Second example child", 5, 3);
   exampleTask.addSubTask(&childTask);
   childTask.addSubTask(&grandchildTask);
   exampleTask.addSubTask(&secondChildTask);
   secondExampleTask.addSubTask(&secondExampleChildTask);
   project.addTask(&exampleTask);
   project.addTask(&secondExampleTask);
   Question myQuestion = Question("Example Question", &exampleTask);
   project.addQuestion(&myQuestion);

   //print the project
   project.printProject();

   //save the project
   project.save();

   ProjectLoader projectLoader = ProjectLoader();
   //load all projects
   std::vector<Project> projects = projectLoader.getProjects();
   //print all of the projects
   for(int i = 0; i < projects.size(); i++){
      std::cout << "\n";
      projects[i].printProject();
   }
   std::cout << "\n";
}

int main() {
   //testTaskClass();
   //testQuestionClass();
   //testProjectClass();
   testProjectLoader();
   return 0;
}