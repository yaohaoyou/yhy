#include<bits/stdc++.h>
#define int long long
using namespace std;
const int R=1e18;
int B=60;
int n,k;
mt19937 rnd(time(0) * (unsigned long long)(new char));
inline int rndll(){return rnd();}
inline int random(int l,int r){return rndll()%(r-l+1)+l;}
void solve(int l,int r){
    l=max(l,1ll);r=min(r,n);
    if(r-l+1<=B){
        int p=random(l,r);
        cout<<p<<' '<<p<<endl;
        string s;
        cin>>s;
        if(s=="Yes")    exit(0);
        solve(l-k,r+k);
        return;
    }
    int mid=(l+r)>>1;
    cout<<l<<' '<<mid<<endl;
    string s;
    cin>>s;
    if(s=="Yes")    solve(l-k,mid+k);
    else    solve(mid+1-k,r+k);
}
main(){
    cin>>n>>k;
    B=min(B,n);
    solve(1,n);
}