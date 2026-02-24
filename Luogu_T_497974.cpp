#include<bits/stdc++.h>
using namespace std;
int n;
int s1,s2;
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){int x;cin>>x;s1+=x;}
    for(int i=1;i<=n;i++){int x;cin>>x;s2+=x;}
    printf("%d\n",(s1+s2+1)/2);
}