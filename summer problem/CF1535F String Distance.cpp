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
int n,m;
unordered_map<string,vector<string>> mp;
int lcp[maxn];
vector<int> to[maxn];
struct Trie{
    int tot;
    int nex[maxn][26];
    vector<int> pas[maxn];
    void ins(string s,int id){
        reverse(s.begin(),s.end());
        int p=0;
        for(int i=0;i<m;i++){
            char c=s[i];
            pas[p].eb(id);
            int o=c-'a',&t=nex[p][o];
            if(!t)  t=++tot;
            p=t;
            to[id][m-i-1]=p;
        }
        pas[p].eb(id);
    }
    void clear(){for(int i=0;i<=tot;i++)pas[i].clear(),mems(nex[i],0);tot=0;}
    int query(int p,int l,int r){return upper_bound(pas[p].begin(),pas[p].end(),r)-lower_bound(pas[p].begin(),pas[p].end(),l);}
}T;
ll solve(vector<string> s){
    ll ret=0;int k=s.size();
    sort(s.begin(),s.end());
    for(int i=1;i<k;i++){
        lcp[i]=0;
        for(int j=0;j<m;j++)if(s[i][j]!=s[i-1][j])break;else lcp[i]++;
    }
    T.clear();
    for(int i=0;i<k;i++)    to[i].clear(),to[i].resize(m+1,0);
    for(int i=0;i<k;i++)    T.ins(s[i],i);
    vector<pii> stk;stk.clear();
    // for(auto i:s)   cout<<i<<'\n';puts("");
    ll sum=0;
    stk.eb(-1,k);
    for(int i=k-1;~i;i--){
        vector<int> en;en.clear();
        for(int j=0;j<m;j++)if(j&&s[i][j]<s[i][j-1])en.eb(j-1);en.eb(m-1);
        // printf("stk : ");for(pii j:stk)  printf("%d ",j.se);puts("");
        for(int j=stk.size()-1;j;j--){
            int l=stk[j].se,r=stk[j-1].se-1,p=stk[j].fi;
            if(p==m)    continue;
            sum+=r-l+1;
            int q=*lower_bound(en.begin(),en.end(),p);
            // k\in [l,r] [q+1,m-1] is same
            ret+=T.query(to[i][q+1],l,r);
            // printf("%d %d %d %d %d %d\n",p,q,i,l,r,T.query(to[i][q+1],l,r));
        }
        // printf("lcp[%d] = %d\n",i,lcp[i]);
        while(!stk.empty()&&stk.back().fi>=lcp[i])  stk.pop_back();
        stk.eb(lcp[i],i);
    }
    // printf("ret = %d,sum = %d\n",ret,sum);
    ret+=(sum-ret)<<1;
    return ret;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++){
        string s;
        cin>>s;m=s.length();
        string t=s;
        sort(t.begin(),t.end());
        mp[t].eb(s);
    }
    ll ans=0,pre=0;
    for(auto i:mp){
        vector<string> v=i.se;
        ans+=1ll*pre*v.size()*1337;
        pre+=v.size();
        ans+=solve(v);
    }
    cout<<ans;
}