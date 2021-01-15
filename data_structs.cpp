/* @Author
Student Name: Yunus Emre Yiğit
Student ID : 150190107
Date: 13.01.2021 */

#include <iostream>
#include <string>
#include "data_structs.h"

using namespace std;

void Stack::init(){
    head = NULL;
}

void Stack::push(Subtask* init){
    Subtask* in = new Subtask;
    in->name = init->name;
    in->duration = init->duration;
    in->next = NULL;
    if (head == NULL)
        head = in;
    else{
        in->next = head;
        head = in;
    }
}

Subtask* Stack::pop(){   
        Subtask* todelete = head; 
        Subtask* temp = new Subtask;
        temp->name = head->name;
        temp->duration = head->duration;
        temp->next = NULL;
        head = head->next;
        //cout<<"       "<<temp->name <<" " <<temp->duration <<" deleted"<<endl;
        delete todelete;
        return temp;
}

void Stack::close(){
    while(head){
        pop();
    }
}


void Queue::init(){
    //head->task_stack.init();
    //tail->task_stack.init();
    head = NULL;
    tail = NULL;

}

void Queue::enqueue(Process* init){
    Process* in = new Process;
    in->name = init->name;
    in->arrival_time = init->arrival_time;
    in->deadline = init->deadline;
    in->priority = init->priority;
    in->task_count = init->task_count;
    in->task_stack = init->task_stack;
    in->next = NULL;
    if (head == NULL){
        head = in;
        tail = in;
    }
    else{
        tail->next = in;
        tail = in;
    }
}

Process* Queue::dequeue(){
    if(head  == NULL){
        cout<<"QUEUE IS EMPTY"<<endl;
        return NULL;
    }
    else{
        Process* temp = head;
        Process* toreturn = new Process;//head;
        toreturn->name = temp->name;
        toreturn->arrival_time = temp->arrival_time;
        toreturn->deadline = temp->deadline;
        toreturn->priority = temp->priority;
        toreturn->task_count = temp->task_count;
        toreturn->task_stack = temp->task_stack;
        toreturn->next = NULL;
        head = head->next;
        //temp->task_stack.close();
        //TORETURNU NEW İLE OLUŞTUR 
        //cout<<tureturn->name<<" deleted"<<endl;
        delete temp;
        return toreturn;
    }
}

bool Queue::isEmpty(){
    if (head == NULL)
        return true;
    else return false;
}

Process* Queue::front(){
    return head;
}

void Queue::close(){
    while(head){
        dequeue();
    }
    head = NULL;
    tail = NULL;
}

void Queue::print(){
    Process* temp = head;
    for(;temp;temp = temp->next){
            cout<<temp->name<<" "<<temp->priority<<endl;
            cout<<temp->arrival_time<<" "<<temp->task_count<<endl;
            Subtask* st = temp->task_stack.head;
            for(;st;st = st->next)
                cout<<st->name<<" "<<st->duration<<endl;
     }
}

//MULTIQUEUE FUNCTS

void MultiQueue::init(){
    for (int i = 0; i < 3; i++){
        queues[i].init();
    }
}

void MultiQueue::close(){
    for (int i = 0; i < 3; i++){
        queues[i].close();
    }
}

void MultiQueue::enqueue(Process* in){
    if(in->priority == 1)
        queues[0].enqueue(in);
    else if(in->priority == 2)
        queues[1].enqueue(in);
    else
        queues[2].enqueue(in);
}


Process* MultiQueue::dequeue(int priority){
    if(priority == 1)
        return queues[0].dequeue();
    else if(priority == 2)
        return queues[1].dequeue();
    else
        return queues[2].dequeue();
}

Process* MultiQueue::front(int priority){
    if(priority == 1)
        return queues[0].front();
    else if(priority == 2)
        return queues[1].front();
    else
        return queues[2].front();
}

void MultiQueue::print(){
    for (int i = 0; i < 3; i++){
        Process* temp = queues[i].head;
        for(;temp;temp = temp->next){
            cout<<temp->name<<" "<<temp->priority<<endl;
            cout<<temp->arrival_time<<" "<<temp->task_count<<endl;
            Subtask* st = temp->task_stack.head;
            for(;st;st = st->next)
                cout<<st->name<<" "<<st->duration<<endl;
            
        }  
    }
}