/* @Author
Student Name: Yunus Emre Yiğit
Student ID : 150190107
Date: 13.01.2021 */

#include <iostream>
#include <string>
#include <fstream>
#include "data_structs.h"

using namespace std;

int main(int argc, char* argv[]){
    ifstream file("data.txt");
    if(!(file.is_open())){
        cout<<"Program couldn't read the file";
        return 0;
    }
    
    Queue q; q.init();
    int process_num = 0;
    
    while( !file.eof() ){ 
        Process* pro = new Process;  
        pro->next = NULL;    
        file>>pro->name>>pro->priority;
        file>>pro->arrival_time>>pro->task_count;
        pro->task_stack.init();
        pro->deadline = pro->arrival_time;
        int num_task = 0;
        for(int i = 0; i < pro->task_count; i++){
            Subtask* st = new Subtask;
            st->next = NULL;
            file>>st->name>>st->duration;
            pro->task_stack.push(st);
            pro->deadline += pro->task_stack.head->duration;
            delete st;
            num_task++;
        } 
        process_num += num_task;
        q.enqueue(pro);
        delete pro;      
    }

    int sys_time = 0;
    MultiQueue multi; multi.init();
    int proceeded2 = 0;
    int lateness = 0;
    while(process_num != 0){
        bool flag = false;

        while(!q.isEmpty() && sys_time >= q.head->arrival_time){       //MultiQueue ya process ekleme
            multi.enqueue(q.dequeue());
        }

            if (multi.queues[0].head){
                sys_time += multi.queues[0].head->task_stack.head->duration;
                Subtask* st = multi.queues[0].head->task_stack.pop();
                multi.queues[0].head->task_count--;
                cout<<multi.queues[0].head->name<<" "<<st->name<<endl;
                flag = true;
            }

            else if(multi.queues[1].head && (multi.queues[2].head == NULL || proceeded2 != 2)){
                sys_time += multi.queues[1].head->task_stack.head->duration;
                Subtask* st = multi.queues[1].head->task_stack.pop();
                cout<<multi.queues[1].head->name<<" "<<st->name<<endl;
                multi.queues[1].head->task_count--;
                proceeded2++;
                if(proceeded2 > 2)
                    proceeded2 = 1;
                flag = true;
            }
                
            else if((multi.queues[2].head && multi.queues[1].head == NULL) || (multi.queues[2].head && proceeded2 == 2)){
                sys_time += multi.queues[2].head->task_stack.head->duration;
                Subtask* st = multi.queues[2].head->task_stack.pop();
                cout<<multi.queues[2].head->name<<" "<<st->name<<endl;
                multi.queues[2].head->task_count--;
                proceeded2 = 0;
                flag = true;
            }
 
                if (multi.queues[0].head && multi.queues[0].head->task_count == 0){
                    lateness += sys_time - multi.queues[0].head->deadline;
                    multi.queues[0].dequeue();
                }
                
                if (multi.queues[1].head && multi.queues[1].head->task_count == 0){
                    lateness += sys_time - multi.queues[1].head->deadline;
                    multi.queues[1].dequeue();
                }

                if (multi.queues[2].head && multi.queues[2].head->task_count == 0){
                    lateness += sys_time - multi.queues[2].head->deadline;
                    multi.queues[2].dequeue();
                }
                
            if (flag)
                process_num--;
            else{
                sys_time++;
                proceeded2 = 0;
            }
            

    }

   //multi.print();
    cout<<"Cumulative Lateness: "<<lateness<<endl;
    multi.close();
    //q.close();

    file.close();
    getchar();
    return 0;
}