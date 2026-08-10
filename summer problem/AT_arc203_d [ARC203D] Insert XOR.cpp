#include<bits/stdc++.h>
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
const int maxn=2e5+10;
int n,q;
int a[maxn];
set<pii> st;
inline int calc(){
    bool flag=true;
    for(int i=1;i<n;i++)if(a[i]^a[i+1]){flag=false;break;}
    if(flag)    return a[1]?n:2;
    int ret=0;
    for(int i=1;i<=n;i++){
        int j=i;while(j<=n&&a[j]==a[i])j++;j--;
        if(!a[i]&&j>i)  ret+=3;
        i=j;
    }
    if(a[n-1]||a[n]){ret++;ret+=!a[n];}
    if(!a[1]&&!a[2])    ret--;
    else ret+=!a[1];
    return max(2,ret);
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    for(int i=1;i<=n;i++){
        int j=i;while(j<=n&&a[i]==a[j])j++;j--;
        if(!a[i]&&j>i)  st.ep(i,j);i=j;
    }
    int sum=0;for(int i=1;i<=n;i++)sum+=a[i];
    scanf("%d",&q);
    while(q--){
        int x;scanf("%d",&x);
        sum-=a[x];a[x]^=1;sum+=a[x];
        if(!sum){st.clear();st.ep(1,n);puts("2");continue;}
        if(sum==n){st.clear();printf("%d\n",n);continue;}
        if(a[x]){  // 0 -> 1
            bool in00=false;
            auto it=st.lower_bound(pii(x+1,0));
            if(it!=st.begin()){
                it--;
                if(it->se>=x){
                    int l=it->fi,r=it->se;
                    // printf("[%d,%d]\n",l,r);
                    st.erase(it);
                    if(l<x-1)   st.ep(l,x-1);
                    if(x+1<r)   st.ep(x+1,r);
                }
            }
        }
        else{  // 1 -> 0
            bool flag=false;
            int l;
            if(x>1&&!a[x-1]){
                auto it=st.lower_bound(pii(x,0));
                if(it!=st.begin()&&(--it)->se>=x-1){l=it->fi;st.erase(it);st.ep(l,x);}
                else    st.ep(l=x-1,x);
                flag=true;
            }
            if(x<n&&!a[x+1]){
                auto it=st.lower_bound(pii(x+2,0));
                if(it!=st.begin()&&(--it)->se>=x+1){
                    int r=it->se;st.erase(it);
                    if(flag)    st.erase(pii(l,x)),st.ep(l,r);
                    else    st.ep(x,r);
                }
                else{
                    if(flag)    st.erase(pii(l,x)),st.ep(l,x+1);
                    else    st.ep(x,x+1);
                }
            }
        }
        // for(auto [i,j]:st)  printf("[%d,%d]\n",i,j);
        int ans=st.size()*3;
        if(a[n-1]||a[n]){ans++;ans+=!a[n];}
        if(!a[1]&&!a[2])    ans--;
        else ans+=!a[1];
        printf("%d\n",max(ans,2));
    }
}