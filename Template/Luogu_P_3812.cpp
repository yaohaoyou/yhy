//  P3812 【模板】线性基
#include<bits/stdc++.h>
#define ull unsigned long long
using namespace std;
const int maxn=52;
int n;
ull p[maxn];
void insert(ull x){
    for(int i=51;i>=0;i--){
        if(!(x>>i)) continue;
        if(!p[i]){
            p[i]^=x;
            break;
        }
        x^=p[i];
    }
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++){
        ull x;
        cin>>x;
        insert(x);
    }
    ull ans=0;
    for(int i=63;i>=0;i--)  ans=max(ans,ans^p[i]);
    cout<<ans;
}