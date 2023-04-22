#include <iostream>
#include "headers/task.h"
#include "headers/question.h"
#include "headers/project.h"
#include "headers/fileManager.h"

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
   Task exampleTask("Example Task", 0, 3);
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
   Project exampleProject("Example Project", "projects/exampleProject.txt", tasks, questions);
   exampleProject.printProject();
}


int main() {
   //testTaskClass();
   //testQuestionClass();
   testProjectClass();
   //open file with paths to project configurations
   std::cout << "File Manager" << std::endl;
   FileManager fileManager = FileManager();
   //load all projects

   //call command line interface manager

   return 0;
}