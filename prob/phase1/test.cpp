#include<iostream>
#include<string>
using namespace std;
int n=50000;
int main(){
    for(int i=0;i<n-1;i++){
        cout<<"ASML "+to_string(i+1)+" "+"b#\n";
    }
    for(int i=0;i<n-1;i++){
        cout<<"ASML "+to_string(i+1)+" "+"s#\n";
    }
}