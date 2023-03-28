//Shortest Remaining Time First
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct process{
    int arrive;
    int burst;
    int turnaround_time;
    int waiting_time;
    int remain;
    int pid;
};


int main(){
    int process_num;
    int cur_time = 0;
    int done = 0;
    int first = 1;


    cin >> process_num;
    vector<process> p_list;
    vector<process> queue;
    p_list.resize(process_num);
    queue.resize(0);

    for(int i=0; i<process_num; ++i){
        int temp;
        cin >> temp;
        p_list[i].arrive = temp;
        p_list[i].pid = i;
    }
    for(int i=0; i<process_num; ++i){
        int temp;
        cin >> temp;
        p_list[i].burst = temp;
        p_list[i].remain = temp;
    }  
    while(done!=process_num){
        //check arrived
        for(auto p : p_list){
            if( p.arrive == cur_time){
                queue.push_back(p);
           }
        }
        //find min
        if(size(queue)==0){//queue empty
            cur_time+=1;
        }
        else{//sth in queue
            int min=0;
            int counter = 0;
            int remain = 999;
            for(auto p : queue){
                if(p.remain<remain){
                   min = counter;
                    remain = p.remain;
                }
                counter+=1;
            }
            //now start min
            queue[min].remain-=1;
            
            cur_time+=1;

            if(queue[min].remain==0){ // min done
                done+=1;
                queue[min].turnaround_time = cur_time-queue[min].arrive;
                queue[min].waiting_time = queue[min].turnaround_time - queue[min].burst;
                p_list[queue[min].pid] = queue[min];
                queue.erase(queue.begin()+min);
            }
            
        }
    }
    int total_wait = 0;
    int total_turn = 0;
    for(auto p : p_list){
        total_wait += p.waiting_time;
        total_turn += p.turnaround_time;
        cout<<p.waiting_time<<" "<<p.turnaround_time<<endl;
    }
    cout<<total_wait<<endl;
    cout<<total_turn<<endl;

    return 0;
}