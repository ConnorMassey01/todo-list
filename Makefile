all:
	g++ src\date.cpp src\task.cpp src\question.cpp src\project.cpp src\fileManager.cpp main.cpp -o main && main.exe