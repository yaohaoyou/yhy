#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define fi first
#define se second
using namespace std;
const int maxn=1e5+10,ct[10]={6,2,5,5,4,5,6,3,7,6};
int n;
void solve(){
    scanf("%d",&n);
    if(n==1)    return puts("-1"),void();
    int nums=ceil(n/7.0);
    for(int i=1;i<=nums;i++){
        for(int j=(i==1)?1:0;j<10;j++){
            if(n<ct[j]) continue;
            int now=ceil((n-ct[j])/7.0);
            if(now==nums-i){
                n-=ct[j];
                printf("%d",j);
                break;
            }
        }
    }
    putchar('\n');
}
int main(){
    // freopen("sticks.in","r",stdin);freopen("sticks.out","w",stdout);
    int T;
    scanf("%d",&T);
    while(T--)solve();
}
