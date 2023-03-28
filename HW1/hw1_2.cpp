#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <iostream>


using namespace std;
int main()
{
    cout<<"Main Process ID : "<<getpid()<<endl;
    pid_t pid;
    pid = fork();//f1
    
    if(pid == 0){
        cout<<"Fork 1. I'm the child "<<getpid()<<", my parent is "<<getppid()<<"."<<endl;
        pid = fork();//f2
        if(pid>0)
            wait(NULL);
        else if(pid==0){
             cout<<"Fork 2. I'm the child "<<getpid()<<", my parent is "<<getppid()<<"."<<endl;
            pid = fork();//f3
            if(pid==0){
                 cout<<"Fork 3. I'm the child "<<getpid()<<", my parent is "<<getppid()<<"."<<endl;
            }
            if(pid>0)
                wait(NULL);
        }
    }
    else if(pid>0){
        wait(NULL);

        pid = fork();//f4
        if(pid==0){
             cout<<"Fork 4. I'm the child "<<getpid()<<", my parent is "<<getppid()<<"."<<endl;
        }
        else if(pid>0){
            wait(NULL);
            pid = fork();//f6
            if(pid==0){
                 cout<<"Fork 6. I'm the child "<<getpid()<<", my parent is "<<getppid()<<"."<<endl;
            }
            else if(pid>0)
                wait(NULL);
            
        }
        else{
        printf("Error!");
        }
        
        pid = fork();//f5
	    if(pid==0){
             cout<<"Fork 5. I'm the child "<<getpid()<<", my parent is "<<getppid()<<"."<<endl;
            if(pid>0){
                wait(NULL);
            }
   	    }
 }
    else{
        printf("Error!");
    }
    if(pid>0) {
        wait(NULL);
    }
    return 0;
}
