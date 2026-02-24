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
const int maxn=1e5+10;
int n,m;
char s[maxn];
int a[maxn];
unordered_set<int> st;
void matt(){
    st.clear();
    scanf("%d%d",&n,&m);
    scanf("%s",s+1);
    for(int i=1;i<=m;i++)   scanf("%d",&a[i]),st.ep(a[i]);
    int p=1;
    for(int i=1;i<=n;i++){
        if(s[i]=='A')   p++,st.ep(p);
        else{
            p++;while(st.find(p)!=st.end()) p++;
            st.ep(p);p++;while(st.find(p)!=st.end()) p++;
        }
    }
    printf("%d\n",st.size());
    vector<int> v;
    for(int i:st)   v.eb(i);
    sort(v.begin(),v.end());
    for(int i:v)    printf("%d ",i);
    puts("");
}
int main(){int T;scanf("%d",&T);while(T--)matt();}