// DS-ToDo: Simple Task Manager
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

/* ------------------- Task Definition ------------------- */
struct Task {
    int id;
    string title;
    string description;
    int priority;   // 1 (low) to 5 (high)
    string dueDate; // yymmdd
    bool completed;
    Task* next;

    Task(int _id=0,string t="",string d="",int p=1,string dd=""):
        id(_id), title(t), description(d), priority(p), dueDate(dd),
        completed(false), next(nullptr) {}
};

/* ------------------- Linked List (Main Storage) ------------------- */
class LinkedList {
    Task* head;
public:
    LinkedList(): head(nullptr) {}
    ~LinkedList() {
        Task* cur=head;
        while(cur){ Task* nxt=cur->next; delete cur; cur=nxt; }
    }

    void push(Task* t) {
        if(!head) head=t;
        else {
            Task* cur=head;
            while(cur->next) cur=cur->next;
            cur->next=t;
        }
    }

    Task* findById(int id) {
        Task* cur=head;
        while(cur){
            if(cur->id==id) return cur;
            cur=cur->next;
        }
        return nullptr;
    }

    void remove(Task* t) {
        if(!head) return;
        if(head==t){
            head=head->next;
            delete t;
            return;
        }
        Task* cur=head;
        while(cur->next && cur->next!=t) cur=cur->next;
        if(cur->next){
            cur->next=t->next;
            delete t;
        }
    }

    Task* getHead(){ return head; }
};

/* ------------------- BST for Sorting by Due Date ------------------- */
struct BSTNode {
    Task* task;
    BSTNode *left,*right;
    BSTNode(Task* t): task(t), left(nullptr), right(nullptr) {}
};

class BST {
    BSTNode* root;

    BSTNode* insertRec(BSTNode* node, Task* t){
        if(!node) return new BSTNode(t);
        if(t->dueDate < node->task->dueDate)
            node->left = insertRec(node->left,t);
        else
            node->right = insertRec(node->right,t);
        return node;
    }

    void inorderRec(BSTNode* node){
        if(!node) return;
        inorderRec(node->left);
        show(node->task);
        inorderRec(node->right);
    }

    void freeRec(BSTNode* node){
        if(!node) return;
        freeRec(node->left);
        freeRec(node->right);
        delete node;
    }

    static void show(Task* t){
        cout << "["<<t->id<<"] " << t->title
             << " (P"<<t->priority<<", due:"<<t->dueDate
             << ", " << (t->completed?"Completed":"Pending") << ")\n";
        if(!t->description.empty())
            cout<<"    "<<t->description<<"\n";
    }

public:
    BST(): root(nullptr) {}
    ~BST(){ freeRec(root); }

    void insert(Task* t){ root=insertRec(root,t); }
    void clear(){ freeRec(root); root=nullptr; }
    void inorder(){ inorderRec(root); }
};

/* ------------------- Priority Queue (Sorting by Priority) ------------------- */
struct PriorityQueue {
    Task* arr[200];
    int size;
    PriorityQueue(): size(0) {}

    void push(Task* t){
        int i=size-1;
        while(i>=0 &&
             (arr[i]->priority < t->priority ||
             (arr[i]->priority == t->priority && arr[i]->dueDate > t->dueDate))){
            arr[i+1]=arr[i]; i--;
        }
        arr[i+1]=t;
        size++;
    }

    void rebuild(LinkedList& list){
        size=0;
        Task* cur=list.getHead();
        while(cur){
            push(cur);
            cur=cur->next;
        }
    }

    void display(){
        for(int i=0;i<size;i++){
            Task* t=arr[i];
            cout << "["<<t->id<<"] " << t->title
                 << " (P"<<t->priority<<", due:"<<t->dueDate
                 << ", " << (t->completed?"Completed":"Pending") << ")\n";
            if(!t->description.empty())
                cout<<"    "<<t->description<<"\n";
        }
    }
};

/* ------------------- Task Manager ------------------- */
class TaskManager {
    LinkedList list;
    BST bst;
    PriorityQueue pq;
    int nextId;

public:
    TaskManager(): nextId(1) { loadFromFile(); }

    void rebuildAll(){
        bst.clear();
        Task* cur=list.getHead();
        while(cur){ bst.insert(cur); cur=cur->next; }
        pq.rebuild(list);
    }

    /* Add Task */
    void addTask(){
        string t,d,due;
        int p;
        cout<<"Title: "; getline(cin,t);
        cout<<"Description: "; getline(cin,d);
        cout<<"Priority (1-5): "; cin>>p; cin.ignore();
        cout<<"Due date (yymmdd): "; getline(cin,due);

        Task* task=new Task(nextId++,t,d,p,due);
        list.push(task);
        rebuildAll();

        cout<<"Task added ID: "<<task->id<<"\n";
    }

    /* View All */
    void viewAll(){
        cout<<"=== All Tasks ===\n";
        Task* cur=list.getHead();
        if(!cur){ cout<<"No tasks.\n"; return; }

        while(cur){
            cout<<"["<<cur->id<<"] "<<cur->title
                <<" (P"<<cur->priority<<", due:"<<cur->dueDate
                <<", "<<(cur->completed?"Completed":"Pending")<<")\n";
            if(!cur->description.empty())
                cout<<"    "<<cur->description<<"\n";
            cur=cur->next;
        }
    }

    /* View by Due Date */
    void viewByDueDate(){
        cout<<"=== Tasks by Due Date ===\n";
        bst.inorder();
    }

    /* View by Priority */
    void viewByPriority(){
        cout<<"=== Task Priority Order ===\n";
        pq.display();
    }

    /* Update */
    void updateTask(){
        int id;
        cout<<"Task ID: "; cin>>id; cin.ignore();
        Task* t=list.findById(id);
        if(!t){ cout<<"Not found.\n"; return; }

        cout<<"1.Title 2.Desc 3.Priority 4.Due 5.Toggle Complete: ";
        int op; cin>>op; cin.ignore();

        if(op==1){ string s; cout<<"New Title: "; getline(cin,s); t->title=s; }
        else if(op==2){ string s; cout<<"New Desc: "; getline(cin,s); t->description=s; }
        else if(op==3){
            int p; cout<<"New Priority: "; cin>>p; cin.ignore();
            if(p>=1&&p<=5) t->priority=p;
        }
        else if(op==4){
            string s; cout<<"New Due: "; getline(cin,s);
            t->dueDate=s;
        }
        else if(op==5) t->completed = !t->completed;

        rebuildAll();
    }

    /* Delete */
    void deleteTask(){
        int id; cout<<"Task ID: "; cin>>id; cin.ignore();
        Task* t=list.findById(id);
        if(!t){ cout<<"Not found.\n"; return; }

        list.remove(t);
        rebuildAll();
        cout<<"Task deleted.\n";
    }

    /* Search title contains substring */
    void searchByTitle(){
        string q;
        cout<<"Keyword: "; getline(cin,q);
        Task* cur=list.getHead();
        bool found=false;

        while(cur){
            if(cur->title.find(q)!=string::npos){
                cout<<"["<<cur->id<<"] "<<cur->title
                    <<" (P"<<cur->priority<<", due:"<<cur->dueDate
                    <<", "<<(cur->completed?"Completed":"Pending")<<")\n";
                if(!cur->description.empty())
                    cout<<"    "<<cur->description<<"\n";
                found=true;
            }
            cur=cur->next;
        }
        if(!found) cout<<"No matching tasks.\n";
    }

    /* File Save */
    void saveToFile(){
        ofstream out("tasks.txt");
        Task* cur=list.getHead();
        while(cur){
            out<<cur->id<<"|"<<cur->title<<"|"<<cur->description<<"|"
               <<cur->priority<<"|"<<cur->dueDate<<"|"<<cur->completed<<"\n";
            cur=cur->next;
        }
        out.close();
        cout<<"Saved.\n";
    }

    /* File Load */
    void loadFromFile(){
        ifstream in("tasks.txt");
        if(!in) return;
        while(!in.eof()){
            int id,p,comp;
            string t,d,due;
            if(!(in>>id)) break;
            in.ignore(1,'|');
            getline(in,t,'|');
            getline(in,d,'|');
            in>>p; in.ignore(1,'|');
            getline(in,due,'|');
            in>>comp;
            in.ignore(1,'\n');

            Task* task=new Task(id,t,d,p,due);
            task->completed = comp;
            list.push(task);
            if(id>=nextId) nextId=id+1;
        }
        in.close();
        rebuildAll();
    }
};

/* ------------------- MAIN MENU ------------------- */
int main(){
    TaskManager tm;
    while(true){
        cout<<"\n===== DS-ToDo MENU =====\n";
        cout<<"1. Add Task (Linked List)\n";
        cout<<"2. View All Tasks (Linked List)\n";
        cout<<"3. View by Due Date (BST)\n";
        cout<<"4. View by Priority (Priority Queue)\n";
        cout<<"5. Update Task\n";
        cout<<"6. Delete Task\n";
        cout<<"7. Search by Title\n";
        cout<<"8. Save & Exit\n";
        cout<<"Choose: ";
        int op; cin>>op; cin.ignore();

        if(op==1) tm.addTask();
        else if(op==2) tm.viewAll();
        else if(op==3) tm.viewByDueDate();
        else if(op==4) tm.viewByPriority();
        else if(op==5) tm.updateTask();
        else if(op==6) tm.deleteTask();
        else if(op==7) tm.searchByTitle();
        else if(op==8){ tm.saveToFile(); break; }
        else cout<<"Invalid.\n";
    }
    return 0;
}
