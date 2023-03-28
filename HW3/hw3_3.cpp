//Multilevel Feedback Queue (RR+FCFS)
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
    int queue = 0; //0=rr, 1=fcfs
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
    vector<process> queue_fcfs;
    p_list.resize(process_num);
    queue.resize(0);
    queue_fcfs.resize(0);

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
    int arrive = 0;
    process last;
    int just_now=0;
    while(done!=process_num){
        //cout<<"-------------------------\n";
        //cout<<"cur time: "<< cur_time<<endl;
        //check arrived
        arrive=0;
        for(auto p : p_list){
            if( p.arrive == cur_time){
                //cout<<"arrived: "<<p.pid<<endl;
                queue.push_back(p);
                arrive = 1;
           }
        }
        if(turn_flag==1){
            //cout<<"turn: "<<last.pid<<" fcfs length: "<<sizeof(queue_fcfs)<<endl;
            last.queue=1;
            queue_fcfs.push_back(last);
            turn_flag=0;
            just_now=1;
        }
        if(arrive == 1 &&last.queue == 1 &&just_now==0){// if was running fcfs 
            //cout<<"was running fcfs and new arrived\n";
            //cout<<"origin fcfs queue:\n";
            for(auto p : queue_fcfs){
            //cout<<p.pid<<" ";
            }
            queue_fcfs.push_back(queue_fcfs[0]);
            queue_fcfs.erase(queue_fcfs.begin());
        }
        just_now=0;
        //cout<<"fcfs queue: "<<endl;
        for(auto p : queue_fcfs){
            //cout<<p.pid<<" ";
        }
        //cout<<endl;
        if(size(queue)==0){//rr queue empty-> use fcfs queue
            //cout<<"fcfs\n";
            if(size(queue_fcfs)==0){//fcfs also empty
                cur_time+=1;
            }
            else{ //fcfs not null
                queue_fcfs[0].remain-=1;
                queue_fcfs[0].counter+=1;
                last = queue_fcfs[0];
                cur_time+=1;
                if(queue_fcfs[0].remain==0){ // min done
                    done+=1;
                    queue_fcfs[0].turnaround_time = cur_time-queue_fcfs[0].arrive;
                    queue_fcfs[0].waiting_time = queue_fcfs[0].turnaround_time - queue_fcfs[0].burst;
                    p_list[queue_fcfs[0].pid] = queue_fcfs[0];
                    queue_fcfs.erase(queue_fcfs.begin());
                }
            }
            
        }
        else{ //first in queue: queue[0]
            //cout<<"rr\n";
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