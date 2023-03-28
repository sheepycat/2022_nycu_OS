#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>

using namespace std;

////////// FIFO ///////////
int fifo(vector<int> s, int f, int str){
    int fault = 0;
    deque<int> frame; 
    for(int i=0; i<str; ++i){ //for all in ref
        deque<int>::iterator it = find(frame.begin(), frame.end(), s[i]);
        if(it==frame.end()) {// if not in frame (fault++)
            fault = fault+1;
            if(frame.size()==f){ // full
                frame.pop_front();
            }
            frame.push_back(s[i]);
        }
    }
    return fault;
}

////////// LRU ///////////
int lru(vector<int> s, int f, int str){
    int fault = 0;
    deque<pair<int,int>> frame; //<name, last used>
    for(int i=0; i<str; ++i){ //for all in ref
        bool find = false;
        for (int j = 0; j < frame.size(); ++j) {
            if(frame[j].first==s[i]){
                find = true;
            }
        }
        for (int j = 0; j < frame.size(); ++j) {
            frame[j].second += 1;
        }
        if(find==false) {// if not in frame (fault++)
            fault = fault+1;
            if(frame.size()==f){ // full, find lru
                int max = -1;
                deque<pair<int,int>>::iterator victim_pos;
                deque<pair<int,int>>::iterator itr = frame.begin();
                for (int j = 0; j < frame.size(); ++j) {
                    if(frame[j].second > max){
                        max = frame[j].second;
                        victim_pos = itr;
                    }
                    ++itr;
                }
                frame.erase(victim_pos);
            }
            frame.push_back(make_pair(s[i], 0));
        }
        else{ // in frame: update
            for (int j = 0; j < frame.size(); ++j) {
                if(frame[j].first==s[i]){
                    frame[j].second = 0;
                    break;
                } 
            }
        }
    }
    return fault;
}

struct page{
    int name;
    int in_time;
    int frequency;
};


////////// LFU ///////////
int lfu(vector<int> s, int f, int str){
    int fault = 0;
    deque<page> frame; //<name, last used>
    for(int i=0; i<str; ++i){ //for all in ref
        bool find = false;
        for (int j = 0; j < frame.size(); ++j) {
            if(frame[j].name==s[i]){
                find = true;
            }
        }
        for (int j = 0; j < frame.size(); ++j) {
            frame[j].in_time += 1;
        }
        if(find==false) {// if not in frame (fault++)
            fault = fault+1;
            if(frame.size()==f){ // full, find lfu
                int min = 1000;

                deque<page>::iterator victim_pos;
                deque<page>::iterator itr = frame.begin();
                for (int j = 0; j < frame.size(); ++j) {
                    if(frame[j].frequency < min){
                        min = frame[j].frequency;
                        victim_pos = itr;
                    }
                    ++itr;
                }
                frame.erase(victim_pos);
            }
            page add;
            add.frequency=1;
            add.name=s[i];
            add.in_time=0;
            frame.push_back(add);
        }
        else{ // in frame: update
            for (int j = 0; j < frame.size(); ++j) {
                if(frame[j].name==s[i]){
                    frame[j].frequency = frame[j].frequency+1;
                    break;
                } 
            }
        }
    }
    return fault;
}

int main(){

    int frame, str, temp;
    vector<int> string;
    string.resize(0);
    
    cin >> frame >> str;
    for(int i=0; i<str; ++i){
        cin >> temp;
        string.push_back(temp);
    }

    ////////// FIFO ///////////
    cout << fifo(string, frame, str) << endl;
    ////////// LRU ///////////
    cout << lru(string, frame, str) << endl;
    ////////// LFU ///////////
    cout << lfu(string, frame, str) << endl;
    return 0;
}