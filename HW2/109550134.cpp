#include <iostream>
#include <thread>
#include <unistd.h>
using namespace std;

# define t_num 4 // number of child threads
# define MAX 500
# define slice (MAX/t_num) // data for each child thread

int matA[MAX][MAX];
int matB[MAX][MAX];
int matC[MAX][MAX]; // Result of Addition
int matD[MAX][MAX]; // Result of Multiplication

void Addition(int r1, int r2){ //
    // Addition -> matC
    for (int i = r1; i <= r2; i++) { // each child thread compute (r1~r2) row's result of matC
        for (int j = 0; j < MAX; j++){
            matC[i][j] = matA[i][j] + matB[i][j];
        }   
    }
}
void Multiplication(int r1, int r2){
    // Multiplication -> matD
    for (int i = r1; i <= r2; i++) { // each child thread compute (r1~r2) row's result of matD
        for (int j = 0; j < MAX; j++) {
            matD[i][j] = 0;
            for (int k = 0; k < MAX; k++) {
                matD[i][j] += matA[i][k] * matB[k][j];
            }
        }
    }
}

// child threading function
void* child_thread(void* data){
    int input = ( intptr_t) data;
    
    
    int r1 = slice*input;
    int r2 = (input == t_num-1)? (MAX-1):(slice*(input+1)-1);
    Addition(r1, r2);
    Multiplication(r1, r2);
    pthread_exit(NULL); // exit child thread 
}

// main fuction
int main(void){

    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            cin >> matA[i][j];
        }
    }
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            cin >> matB[i][j];
        }
    }

    pthread_t thread[t_num] ;   // define thread 
    int data[t_num];
    for(int j=0; j<t_num; j++){
        data[j] = j;
        pthread_create(&thread[j],NULL,child_thread,(void *)( intptr_t)data[j]);   // create a child thread
    }
    
    for(int t=0; t<t_num; t++){
        pthread_join(thread[t],NULL);// output "Master" during child thread outputing "Child"
    }

    long long sum_C = 0;
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++)
            sum_C +=  matC[i][j];     
    }
    cout << sum_C << endl;
    long long sum_D = 0;
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++)
            sum_D += matD[i][j];
    }
    cout << sum_D << endl;
    return 0;
}
