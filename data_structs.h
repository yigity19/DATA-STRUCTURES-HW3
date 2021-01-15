/* @Author
Student Name: Yunus Emre Yiğit
Student ID : 150190107
Date: 13.01.2021 */

#ifndef DATA_STRUCTS_H
#define DATA_STRUCTS_H
#include <string>
using namespace std;

struct Subtask{
    string name;
    int duration;
    Subtask* next;
};

struct Stack{
    Subtask* head;
    void init();
    void close();
    void push(Subtask* in);
    Subtask* pop();
    bool isEmpty();
};

struct Process{
    string name;
    int arrival_time;
    int deadline;
    int task_count;
    int priority;
    Stack task_stack;
    Process* next;
};

struct Queue{
    Process* head;
    Process* tail;
    void init();
    void close();
    void enqueue(Process* in);
    Process* dequeue();
    bool isEmpty();
    void print();
    Process* front();
};

struct MultiQueue{
    Queue queues[3];
    void init();
    void close();
    void enqueue(Process* in);
    Process* dequeue(int priority);
    bool isEmpty();
    void print();
    Process* front(int priority);
};

#endif