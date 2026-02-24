#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+10;
int n;
void solve(){
    scanf("%d",&n);
    int st;
    if(n%3==1)  st=2;
    else if(n%3==2) st=0;
    else    st=1;
    printf("%d ",st);
    for(int i=2;i<=n;i++){
        if(st==2)   st=0;
        else if(st==1)  st=2;
        else    st=1;
        printf("%d ",st);
    }
    puts("");
}
int main(){
    int t;
    scanf("%d",&t);
    while(t--) solve();
}