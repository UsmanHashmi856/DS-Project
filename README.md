Swift Task Flow – Task Management System
Project Overview

Swift Task Flow is a console-based To-Do List and Task Management application developed using C++. The project demonstrates the practical implementation of fundamental Data Structures by utilizing Linked Lists, Binary Search Trees (BST), and Priority Queues to organize and manage tasks efficiently.

The application allows users to create, update, delete, search, and organize tasks based on their due dates and priorities. It also supports file handling to save task records and restore them when the application is launched again.

Objectives
Implement fundamental data structures in a practical application.
Manage tasks dynamically using Linked Lists.
Organize tasks according to due dates using Binary Search Trees.
Prioritize tasks using Priority Queues.
Implement persistent storage through file handling.
Demonstrate searching, insertion, deletion, and updating operations.
Technologies Used
Programming Language: C++
Data Structures: Linked List, Binary Search Tree, Priority Queue
File Handling: C++ File Streams (fstream)
Libraries: iostream, string, fstream
Development Environment: Visual Studio / VS Code / Dev-C++
Key Features
1. Task Management
Add new tasks with unique IDs.
Store task titles and descriptions.
Assign priorities from 1 (Low) to 5 (High).
Set due dates in YYMMDD format.
Track task completion status.
2. Linked List – Task Storage
Uses a singly Linked List as the primary storage structure.
Dynamically allocates memory for new tasks.
Supports insertion, searching, and deletion.
Maintains task records without requiring a fixed-size storage array.
3. Binary Search Tree – Due Date Organization
Uses a Binary Search Tree to organize tasks by due date.
Implements recursive insertion.
Uses Inorder Traversal to display tasks in ascending due-date order.
Rebuilds the BST whenever task information changes.
4. Priority Queue – Priority Management
Uses an array-based Priority Queue to arrange tasks.
Displays higher-priority tasks first.
Uses due dates as a secondary sorting criterion when priorities are equal.
Rebuilds the queue whenever task records are modified.
5. Task Updating and Searching
Update task titles and descriptions.
Change task priorities and due dates.
Toggle tasks between completed and pending.
Search tasks using keywords in their titles.
6. File Handling
Saves task records in tasks.txt.
Loads previously saved tasks when the application starts.
Preserves task IDs, descriptions, priorities, due dates, and completion status.
Saves all current tasks when the user selects Save & Exit.
Data Structures and Concepts Implemented
Data Structure	Purpose
Singly Linked List	Primary task storage
Binary Search Tree	Sorting tasks by due date
Priority Queue	Priority-based task organization
Dynamic Memory Allocation	Creating and deleting task nodes
File Handling	Persistent task storage
How the Application Works
The application starts by loading previously saved tasks from tasks.txt.
Each task is stored as a dynamically allocated node in the Linked List.
The BST and Priority Queue are constructed using the stored task records.
Users interact with the application through a menu-driven interface.
Whenever a task is added, updated, or deleted, the auxiliary data structures are rebuilt.
On selecting Save & Exit, all task information is written to the file.
Application Menu
Add Task (Linked List)
View All Tasks (Linked List)
View by Due Date (BST)
View by Priority (Priority Queue)
Update Task
Delete Task
Search by Title
Save & Exit
How to Run

Requirements: A C++ compiler supporting C++11 or later.

Compile using GCC:

bash
g++ main.cpp -o SwiftTaskFlow -std=c++11


Run:

bash
./SwiftTaskFlow


On Windows:

bash
SwiftTaskFlow.exe


The tasks.txt file is created automatically when the user saves the tasks.

Learning Outcomes
Practical understanding of Linked Lists, BSTs, and Priority Queues.
Experience with dynamic memory allocation and pointers.
Understanding of recursive tree operations and inorder traversal.
Application of searching, sorting, insertion, and deletion.
Experience with file-based data persistence.
🔮 Future Improvements
Add a graphical user interface.
Implement automatic saving after every modification.
Add overdue task notifications.
Support filtering tasks by completion status.
Improve task sorting and searching efficiency.

Project: Swift Task Flow – Task Management System
Language: C++
Category: Data Structures (DS)
