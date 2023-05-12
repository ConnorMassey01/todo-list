#include "headers/userInputHandler.h"

int main() {
   //call command line interface manager
   UserInputHandler userInputHandler = UserInputHandler();
   userInputHandler.start();
   return 0;
}