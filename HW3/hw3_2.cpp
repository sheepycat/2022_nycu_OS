//Round-Robin(RR)
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
    int counter = 0;
};

int main(){
    int process_num;
    int cur_time = 0;
    int done = 0;
    int first = 1;
    int time_q;
    int turn_flag = 0;


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
    cin >>time_q;

    process last;
    while(done!=process_num){
        //check arrived
        for(auto p : p_list){
            if( p.arrive == cur_time){
                queue.push_back(p);
           }
        }
        if(turn_flag==1){
            queue.push_back(last);
            turn_flag=0;
        }
        if(size(queue)==0){//queue empty
            cur_time+=1;
        }
        else{ //first in queue: queue[0]
            queue[0].remain-=1;
            queue[0].counter+=1;
            cur_time+=1;
            if(queue[0].remain==0){ // min done
                done+=1;
                queue[0].turnaround_time = cur_time-queue[0].arrive;
                queue[0].waiting_time = queue[0].turnaround_time - queue[0].burst;
                p_list[queue[0].pid] = queue[0];
                queue.erase(queue.begin());
            }
            else{//min not done: back to queue when counter=time_q
                if(queue[0].counter==time_q){
                    turn_flag=1;
                    queue[0].counter=0;
                    last = queue[0];
                    queue.erase(queue.begin());
                }
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