#include <iostream>
#include "headers/task.h"

void testTaskClass(){
   std::shared_ptr<Task> myTask(new Task("Task 1", 0, 7));
   std::shared_ptr<Task> myChildTask(new Task("Child task", 1, 4));
   Task::addSubtaskToParent(myChildTask, myTask);
   myChildTask->addProgressNote("This is my message to add");
   myTask->printTask();
   std::cout << "\n-------------------\n\n";
   myChildTask->printTask();
}


int main() {
   testTaskClass();

   return 0;
}