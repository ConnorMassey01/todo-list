all:
	g++ src\date.cpp src\task.cpp src\question.cpp src\project.cpp src\projectLoader.cpp main.cpp -o main && main.exe;

tests:
	g++ src\date.cpp src\projectLoader.cpp src\task.cpp src\question.cpp src\project.cpp  tests.cpp -o tests && tests.exe;