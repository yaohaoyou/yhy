#include<bits/stdc++.h>
#include "balance.h"
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
const int maxn=1e5+10;
int n,q;
int a[maxn];
bool dvd(int l,int r){
    assert((r-l+1)&1);
    if(l==r)    return true;
    int mid=(l+r)>>1;
    for(int i=l;i<=r;i++)if(i^mid&&a[i]>=a[mid])return false;
    return dvd(l,mid-1)&dvd(mid+1,r);
}
inline int calc(){
    int ans=0;
    for(int i=1;i<=n;i++){
        for(int j=i;j<=n;j++){
            if(__builtin_popcount(j-i+2)^1) continue;
            ans+=dvd(i,j);
        }
    }
    return ans;
}
ll initialize(int N, vector<int> A) {
    n=N;for(int i=1;i<=n;i++)a[i]=A[i-1];
    return calc();
}

ll update_sequence(int p, int v) {
    a[p+1]=v;return calc();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, Q;
    if (!(cin >> N >> Q)) return 0;
    vector<int> A(N);
    for (int i = 0; i < N; i++) cin >> A[i];
    vector<int> Pos(Q), Val(Q);
    for (int i = 0; i < Q; i++)     cin >> Pos[i] >> Val[i];
    cout << initialize(N, A) << "\n";
    for (int i = 0; i < Q; i++) {
        cout << update_sequence(Pos[i], Val[i]) << "\n";
    }

    return 0;
}
