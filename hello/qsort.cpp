#include<iostream>
using namespace std;
void qsort(int,int);
int a[101];
int main(){
    int N,i;
    cin>>N;
    for(i=0;i<=N-1;i++){
        cin>>a[i];
    }
    qsort(0,N-1);
    for(i=0;i<=N-1;i++){
        cout<<a[i]<<" ";
    }
    return 0;
}
void qsort(int l,int r){
    int i,k,mid,t;
    i=l;k=r;
    mid=a[(i+k)/2];
    do{
        while(a[i]<mid) i++;
        while(a[k]>mid)k--;
        if(i<=k){
            t=a[i];
            a[i]=a[k];
            a[k]=t;
            i++;k--;
        }
    }while(i<=k);
    if(i<r) qsort(i,r);
    if(k>l) qsort(l,k);
}