#include "../headers/project.h"

#define CONFIG_FILE_PATH "storage\\project-list.txt"

Project::Project(){
    this->title = "";
    this->pathToConfig = "";
}
Project::Project(std::string pathToConfig){
    //load project from configuration file
    this->pathToConfig = pathToConfig;
    this->load();
}
Project::Project(std::string title, std::string pathToConfig){
    this->title = title;
    this->pathToConfig = pathToConfig;
}
Project::Project(std::string title, std::string pathToConfig, std::vector<Task*> tasks, std::vector<Question*> questions){
    this->title = title;
    this->pathToConfig = pathToConfig;
    this->tasks = tasks;
    this->questions = questions;
}
Project::~Project(){
    std::cout << "Project destructor for: " << this->title << "\n";
}

void Project::setTitle(std::string title){
    this->title = title;
}
std::string Project::getTitle(){
    return this->title;
}

void Project::setPathToConfig(std::string pathToConfig){
    this->pathToConfig = pathToConfig;
}
std::string Project::getPathToConfig(){
    return this->pathToConfig;
}

void Project::setTasks(std::vector<Task*> tasks){
    this->tasks = tasks;
}
void Project::addTask(Task* task){
    this->tasks.push_back(task);
}
std::vector<Task*> Project::getTasks(){
    return this->tasks;
}


void Project::setQuestions(std::vector<Question*> questions){
    this->questions = questions;
}
void Project::addQuestion(Question* question){
    this->questions.push_back(question);
}
std::vector<Question*> Project::getQuestions(){
    return this->questions;
}

void Project::save(){
    std::cout << "\n\n ----- Save Project to: " + this->pathToConfig << " -----\n\n";
    //try opening the text file at project.pathToConfig
    std::ofstream projectFile(this->pathToConfig, std::ios::binary);
    if(projectFile.is_open()){
        //get the size of the string
        size_t titleSize = this->title.size();
        std::cout << "Title size: " << titleSize << "\n";
        projectFile.write(reinterpret_cast<const char*>(&titleSize), sizeof(titleSize));
        //write the string to the file
        std::cout << "Title: " << this->title << "\n";
        projectFile.write(reinterpret_cast<const char*>(&this->title[0]), titleSize);

        //map out the structure of all tasks and sub-tasks. Maps parent id to children ids
        std::map<int, std::vector<int>> taskMap;
        //keep track of the total number of tasks
        int taskCount = 0;
        //initialize a stack with all tasks associated to the project
        std::stack<Task*> stack;
        for(int i = 0; i < this->tasks.size(); i++){
            stack.push(tasks[i]);
        }
        while(!stack.empty()){
            //increase the total could of tasks
            taskCount++;
            //get the task from the top of the stack
            Task* task = stack.top();
            stack.pop();
            //add any children to the stack
            std::vector<int> subTaskIds;
            std::vector<Task*> subTasks = task->getSubTasks();
            for(int i = 0; i < subTasks.size(); i++){
                stack.push(subTasks[i]);
                subTaskIds.push_back(subTasks[i]->getId());
            }
            if(!subTaskIds.empty()){
                std::cout << "Task map adding " << task->getId() << " -> ";
                for(int i = 0; i < subTaskIds.size(); i++){
                    std::cout << subTaskIds[i];
                    if(i != subTaskIds.size()-1){
                        std::cout << ", ";
                    }
                }
                std::cout << "\n";
                taskMap.insert(std::pair<int, std::vector<int>>(task->getId(), subTaskIds));
            }
        }
        //write the number of tasks in the mapping
        size_t taskMapSize = taskMap.size();
        std::cout << "Task map size: " << taskMapSize << "\n";
        projectFile.write(reinterpret_cast<const char*>(&taskMapSize), sizeof(taskMapSize));
        //write each mapping to the file
        for(auto i = taskMap.begin(); i != taskMap.end(); i++){
            //first write the key
            int key = i->first;
            projectFile.write(reinterpret_cast<const char*>(&key), sizeof(key));
            //then the number of sub-task ids
            std::vector<int> subTaskIds = i->second;
            int numberOfSubTaskIds = subTaskIds.size();
            projectFile.write(reinterpret_cast<const char*>(&numberOfSubTaskIds), sizeof(numberOfSubTaskIds));
            //then all of the subtasks
            for(int i = 0; i < numberOfSubTaskIds; i++){
                projectFile.write(reinterpret_cast<const char*>(&subTaskIds[i]), sizeof(subTaskIds[i]));
            }
        }
        //write the total number of tasks to the file
        std::cout << "Total number of tasks: " << taskCount << "\n";
        projectFile.write(reinterpret_cast<const char*>(&taskCount), sizeof(taskCount));
        //write all the tasks to the file
        for(int i = 0; i < this->tasks.size(); i++){
            this->saveTask(projectFile, this->tasks[i]);
        }
        //write all of the questions to the file
        this->saveQuestions(projectFile);
        //close the file
        projectFile.close();
    }
    else{
        std::cout << "Could not open file: " + this->pathToConfig << "\n";
        return;
    }
    this->saveFileLocation();
}
//save the task and all sub-tasks recursively
void Project::saveTask(std::ofstream& projectFile, Task* task){
    std::cout << "Saving task with id: " << task->getId() << '\n';
    //save the title
    std::string title = task->getTitle();
    size_t titleSize = title.size();
    projectFile.write(reinterpret_cast<const char*>(&titleSize), sizeof(titleSize));
    //write the string to the file
    projectFile.write(reinterpret_cast<const char*>(&title[0]), titleSize);
    //save the id
    int id = task->getId();
    projectFile.write(reinterpret_cast<const char*>(&id), sizeof(id));

    //save the number of progress notes
    std::vector<ProgressNote> progressNotes = task->getProgressNotes(); 
    size_t numberOfProgressNotes = progressNotes.size();
    projectFile.write(reinterpret_cast<const char*>(&numberOfProgressNotes), sizeof(numberOfProgressNotes));
    //save all the of progress notes
    for(int i = 0; i < numberOfProgressNotes; i++){
        std::string date = progressNotes[i].date;
        size_t dateSize = date.size();
        projectFile.write(reinterpret_cast<const char*>(&dateSize), sizeof(dateSize));
        projectFile.write(reinterpret_cast<const char*>(&date[0]), dateSize);

        std::string note = progressNotes[i].note;
        size_t noteSize = note.size();
        projectFile.write(reinterpret_cast<const char*>(&noteSize), sizeof(noteSize));
        projectFile.write(reinterpret_cast<const char*>(&note[0]), noteSize);
    }

    //save the status
    Status status = task->getStatus();
    projectFile.write(reinterpret_cast<const char*>(&status), sizeof(status));

    //save the due date
    std::string dueDate = task->getDueDate();
    size_t dueDateSize = dueDate.size();
    projectFile.write(reinterpret_cast<const char*>(&dueDateSize), sizeof(dueDateSize));
    projectFile.write(reinterpret_cast<const char*>(&dueDate[0]), dueDateSize);
    //save the date created
    std::string dateCreated = task->getDateCreated();
    size_t dateCreatedSize = dateCreated.size();
    projectFile.write(reinterpret_cast<const char*>(&dateCreatedSize), sizeof(dateCreatedSize));
    projectFile.write(reinterpret_cast<const char*>(&dateCreated[0]), dateCreatedSize);
    //save the data started
    std::string dateStarted = task->getDateStarted();
    size_t dateStartedSize = dateStarted.size();
    projectFile.write(reinterpret_cast<const char*>(&dateStartedSize), sizeof(dateStartedSize));
    projectFile.write(reinterpret_cast<const char*>(&dateStarted[0]), dateStartedSize);
    //save the date finished
    std::string dateFinished = task->getDateFinished();
    size_t dateFinishedSize = dateFinished.size();
    projectFile.write(reinterpret_cast<const char*>(&dateFinishedSize), sizeof(dateFinishedSize));
    projectFile.write(reinterpret_cast<const char*>(&dateFinished[0]), dateFinishedSize);
    //save all sub-tasks
    std::vector<Task*> subTasks = task->getSubTasks();
    for(int i = 0; i < subTasks.size(); i++){
        this->saveTask(projectFile, subTasks[i]);
    }
}

void Project::saveQuestions(std::ofstream& projectFile){

}

void Project::saveFileLocation(){
    //see if path is already in the file
    std::ifstream projectPathFileRead(CONFIG_FILE_PATH);
    if(projectPathFileRead.is_open()){
        //check if the path is already in the file
        std::string path;
        while(std::getline(projectPathFileRead, path)){
            if(path == this->pathToConfig){
                projectPathFileRead.close();
                return;
            }
        }
        projectPathFileRead.close();
    }
    else{
        std::cout << "Could not open file: " << CONFIG_FILE_PATH << "\n";  
    }
    //if it is not, add it
    std::ofstream projectPathFileWrite(CONFIG_FILE_PATH, std::ios::app);
    if(projectPathFileWrite.is_open()){
        projectPathFileWrite << this->pathToConfig + "\n";
        projectPathFileWrite.close();
    }
    else{
        std::cout << "Could not open file: " << CONFIG_FILE_PATH << "\n";  
    }
}

void Project::load(){
    std::cout << "\n----- Load project from: " + this->pathToConfig + "-----\n";
    std::ifstream projectFile(this->pathToConfig, std::ios::binary);
    if(projectFile.is_open()){
        //get the size of the title
        size_t titleSize;
        projectFile.read(reinterpret_cast<char*>(&titleSize), sizeof(titleSize));
        std::cout << "Project title size: " << titleSize << "\n";
        //resize the string to fit the title
        this->title.resize(titleSize);
        projectFile.read(reinterpret_cast<char*>(&this->title[0]), titleSize);
        std::cout << "Project title: " << title << "\n";
        //get the task map size
        size_t taskMapSize;
        projectFile.read(reinterpret_cast<char*>(&taskMapSize), sizeof(taskMapSize));
        std::cout << "Task map size: " << taskMapSize << "\n";

        //rebuild the map
        std::map<int, std::vector<int>> taskMap;
        for(int i = 0; i < taskMapSize; i++){
            int parentId;
            projectFile.read(reinterpret_cast<char*>(&parentId), sizeof(parentId));
            int numberOfSubTaskIds;
            projectFile.read(reinterpret_cast<char*>(&numberOfSubTaskIds), sizeof(numberOfSubTaskIds));
            std::vector<int> subTaskIds;
            for(int j = 0; j < numberOfSubTaskIds; j++){
                int subTaskId;
                projectFile.read(reinterpret_cast<char*>(&subTaskId), sizeof(subTaskId));
                subTaskIds.push_back(subTaskId);
            }
            std::cout << "Mapping for task with id: " << parentId << " -> ";
            for(int i = 0; i < subTaskIds.size(); i++){
                std::cout << subTaskIds[i];
                if(i != subTaskIds.size()-1){
                    std::cout << ", ";
                }
            }
            std::cout << "\n";
            taskMap.insert(std::pair<int, std::vector<int>>(parentId, subTaskIds));
        }
        //get tasks
        std::vector<Task*> tasks = this->loadTasks(projectFile);
        //get the questions
        //this->loadQuestions(projectFile);

        projectFile.close();
    }
    else{
        std::cout << "Error could not open file: " + this->pathToConfig;
    }
}

std::vector<Task*> Project::loadTasks(std::ifstream& projectFile){
    std::vector<Task*> tasks;
    //get the number of tasks
    int taskCount;
    projectFile.read(reinterpret_cast<char*>(&taskCount), sizeof(taskCount));
    std::cout << "Total number of tasks: " << taskCount << "\n";
    for(int i = 0; i < taskCount; i++){
        //load the title
        std::string title;
        size_t titleSize;
        projectFile.read(reinterpret_cast<char*>(&titleSize), sizeof(titleSize));
        title.resize(titleSize);
        projectFile.read(reinterpret_cast<char*>(&title[0]), titleSize);
        //load the id
        int id;
        projectFile.read(reinterpret_cast<char*>(&id), sizeof(id));
        //load the progress notes
        std::vector<ProgressNote> progressNotes;
        size_t numberOfProgressNotes;
        projectFile.read(reinterpret_cast<char*>(&numberOfProgressNotes), sizeof(numberOfProgressNotes));
        for(int j = 0; j < numberOfProgressNotes; j++){
            std::string date;
            size_t dateSize;
            projectFile.read(reinterpret_cast<char*>(&dateSize), sizeof(dateSize));
            date.resize(dateSize);
            projectFile.read(reinterpret_cast<char*>(&date[0]), dateSize);

            std::string note = progressNotes[i].note;
            size_t noteSize = note.size();
            projectFile.read(reinterpret_cast<char*>(&noteSize), sizeof(noteSize));
            note.resize(noteSize);
            projectFile.read(reinterpret_cast<char*>(&note[0]), noteSize);
            progressNotes.push_back({note, date});
        }
        //load the status
        Status status;
        projectFile.read(reinterpret_cast<char*>(&status), sizeof(status));
        //load the due date
        std::string dueDate;
        size_t dueDateSize;
        projectFile.read(reinterpret_cast<char*>(&dueDateSize), sizeof(dueDateSize));
        dueDate.resize(dueDateSize);
        projectFile.read(reinterpret_cast<char*>(&dueDate[0]), dueDateSize);
        //load the date created
        std::string dateCreated;
        size_t dateCreatedSize;
        projectFile.read(reinterpret_cast<char*>(&dateCreatedSize), sizeof(dateCreatedSize));
        dateCreated.resize(dateCreatedSize);
        projectFile.read(reinterpret_cast<char*>(&dateCreated[0]), dateCreatedSize);
        //load the date started
        std::string dateStarted;
        size_t dateStartedSize;
        projectFile.read(reinterpret_cast<char*>(&dateStartedSize), sizeof(dateStartedSize));
        dateStarted.resize(dateStartedSize);
        projectFile.read(reinterpret_cast<char*>(&dateStarted[0]), dateStartedSize);
        //load the date finished
        std::string dateFinished;
        size_t dateFinishedSize;
        projectFile.read(reinterpret_cast<char*>(&dateFinishedSize), sizeof(dateFinishedSize));
        dateFinished.resize(dateFinishedSize);
        projectFile.read(reinterpret_cast<char*>(&dateFinished[0]), dateFinishedSize);
        //create the task
        Task task = Task(title, id, progressNotes, status, dueDate, dateCreated, dateStarted, dateFinished);
        std::cout << "\n----- Loaded task -----\n";
        task.printTask();
        tasks.push_back(&task);
    }

    return tasks;
}

std::vector<Question*> Project::loadQuestions(std::ifstream& projectFile){
    std::vector<Question*> questions;

    return questions;
}

void Project::printProject(){
    std::cout << "--- Project ---\n";
    std::cout << "Title: " << this->title << "\n";
    std::cout << "Path to config: " << this->pathToConfig << "\n";
    std::cout << "Tasks: \n";
    for(int i = 0; i < this->tasks.size(); i++){
        this->tasks[i]->printTaskTree(0);
    }
    std::cout << "Questions: \n";
    for(int i = 0; i < this->questions.size(); i++){
        this->questions[i]->printQuestion();
    }
}

