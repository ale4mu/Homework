#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int main(){
    int a[1000],N,i,k;
    memset(a,1,sizeof(a));
    cin>>N;
    for(i=1;i<=N;i++){
        cin>>k;
        a[k]++;
    }
    for(i=1;i<=1000;i++){
        if(a[i]>=1)
            cout<<i<<"";
    }
    return 0;
}