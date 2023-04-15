# todo-list tool

## Architecture
- vector of project variables
- configuration file
    - paths to files that hold all of the data-structures within the projects folder
- data structure files (in projects folder)
    - parse object into text on exit or anything is modified if it is efficient
    - recreate objects when opening application

- class for projects
    - title
    - path to text file
    - pointer to root of tasks tree (can start as null)
    - pointer to questions class
- class for tasks
    - title
    - id
    - text colour?
    - progress notes
        - list of notes
            - text
            - Date
    - due date
    - status: backlog, in progress, done
    - children tasks
    - parent task
    - date created
    - date started
    - date finished
- questions class
    - task id
    - message
- command line interface handler class
    - handle all of the arguments passed through the command line
    - colour code output based on task?
    - auto complete input by pressing tab
- file manager class
    - create file
    - delete file
    - add to section of the file
    - remove from section of a file
    - generate report based on task object
- query class?
    - search for tasks
    - make reports on progress
    - list what is due in the next x days

## Command line interface
- Create a new project: `create project <project name>`
- Open a project: `open <project name>`
- Once a project it opened, you can add tasks and subtasks to the backlog: `add task <task name>`
    - You will then be asked to supply a parent task (if necessary) and a due date
- To move a task into the In Progress section run: `start <task name>`
- To mark a task as complete run: `finish <task name>`
- To add notes to a task run: `update <task name>`
    - You will then be able to enter a list of your notes to add
    - You can finish adding notes by entering `done` or `0`
- To search for a task run: `search <task name>`
- To get a list of tasks with upcoming due dates run: `upcoming <time span in days>`
    - If the time span is not included, all tasks will be added to the list
    - If you would like to narrow the output to a task and it's sub-tasks, run: `<task name> upcoming <time span in days>`
- To generate a report on the open project run: `report <time span in days>`
    - If the time span is not included, all tasks will be added to the report
    - Reports can be found in the report folder of this repository and will be printed to the command line
    - If you would like the report for just one task, run: `<task name> report <time span in days>`

## Project files
Used to convert a projects data structure into text

## Report files
Used to show data to the user in a visually appealing manner
