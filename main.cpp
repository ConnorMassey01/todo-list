#include <iostream>
#include "headers/task.h"

void removeSubTask(Task &task, Task &subTask){
   task.removeSubTask(&subTask);
   subTask.setParentTask(nullptr);
}

void testTaskClass(){
   Task parentTask("Parent", 0, 7);
   Task childTask("Child", 1, 4);
   Task otherChildTask("Other child", 1, 4);
   Task grandchildTask("Grandchild", 1, 4);
   childTask.addProgressNote("This is my message to add");

   parentTask.addSubTask(&childTask);
   parentTask.addSubTask(&otherChildTask);
   childTask.addSubTask(&grandchildTask);
   parentTask.printTaskTree(0);
   grandchildTask.printParents();
   
}


int main() {
   testTaskClass();

   return 0;
}