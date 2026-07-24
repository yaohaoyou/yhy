#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define fi first
#define se second
#define debug(...) 
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
const int maxn=2e5+10;
int n,m;
char s[maxn],t[maxn];
unordered_map<string,int> mp;
queue<string> q;
string rev(string x,int l,int r){for(int i=l,j=r;i<j;i++,j--)swap(x[i],x[j]);return x;}
bool check(string x){for(int i=0;i+m-1<n;i++){bool flag=true;for(int j=1;j<=m;j++)flag&=(x[i+j-1]==t[j]);if(flag)return false;}return true;}
void maker(){
    int T=0;
    for(n=1;n<=15;n++){
        for(int i=0;i<(1<<n);i++){
            for(m=1;m<=3;m++){
                for(int k=0;k<(1<<m);k++){
                    for(int j=1;j<=n;j++)printf("%d",bool(i&(1<<j-1)));puts("");
                    for(int j=1;j<=m;j++)printf("%d",bool(k&(1<<j-1)));puts("");
                    T++;
                }
            }
        }
    }
    debug("T = %d\n",T);
    exit(0);
}
void baoli(){
    mp.clear();while(!q.empty())q.pop();
    string ss="";for(int i=1;i<=n;i++)ss+=s[i];
    if(check(ss))return puts("0"),void();
    mp[ss]=0;q.ep(ss);
    while(!q.empty()){
        string x=q.front();int mx=mp[x];q.pop();
        for(int i=0;i<n;i++)for(int j=i+1;j<n;j++){
            string y=rev(x,i,j);
            if(mp.find(y)==mp.end()){
                if(check(y))    return printf("%d\n",mx+1),void();
                mp[y]=mx+1;q.ep(y);
            }
        }
    }
    puts("-1");
}
void matt(int _cases){
    // if(_cases%100==0)debug("%d\n",_cases);
    // maker();
    scanf("%s%s",s+1,t+1);n=strlen(s+1);m=strlen(t+1);
    // if(_cases==29617){
    //     printf("%d %d\n",n,m);
    //     for(int i=1;i<=n;i++)printf("%c",s[i]);puts("");
    //     for(int i=1;i<=m;i++)printf("%c",t[i]);puts("");
    //     exit(0);
    // }
    {string ss="";for(int i=1;i<=n;i++)ss+=s[i];if(check(ss))return puts("0"),void();}
    // return baoli();
    if(m==1){
        for(int i=1;i<=n;i++)if(s[i]==t[1])return puts("-1"),void();
        puts("0");
        return;
    }
    if(m==2){
        if(t[1]^t[2]){
            int ans=0;
            for(int i=n;i;i--){
                if(s[i]^t[1])   continue;
                int j=i;while(j&&s[j]==t[1])j--;j++;
                ans+=bool(i^n);
                i=j;
            }
            debug("#1\n");
            printf("%d\n",ans);
            return;
        }
        debug("#2\n");
        int ans=0,c1=count(s+1,s+n+1,t[1]),c2=n-c1;
        if(c2<c1-1) return puts("-1"),void();
        for(int i=1;i<=n;i++){
            if(s[i]^t[1])   continue;
            int j=i;while(j<=n&&s[j]==t[1])j++;j--;
            ans+=j-i;
            i=j;
        }
        printf("%d\n",ans);
        return;
    }
    if(m==3){
        if(t[1]==t[2]&&t[2]==t[3]){
            int ans=0,c1=count(s+1,s+n+1,t[1]),c2=n-c1;
            if(c2<(c1+1)/2-1) return puts("-1"),void();
            int cnt[2]={0,0};
            vector<int> v;
            for(int i=1;i<=n;i++)if(s[i]^t[1])v.eb(i);
            if(v[0]<=2) cnt[v[0]-1]++;
            if(v.back()>=n-1)   cnt[n-v.back()]++;
            for(int i=1;i<v.size();i++)if(v[i]-v[i-1]-1<=1)cnt[v[i]-v[i-1]-1]++;
            debug("#3\n");
            for(int i=1;i<=n;i++){
                if(s[i]^t[1])   continue;
                int j=i;while(j<=n&&s[j]==t[1])j++;j--;
                int x=j-i+1;i=j;if(x<3)continue;
                while(x>=3){
                    if(x==3){
                        if(cnt[1]) cnt[1]--,x--;
                        else if(cnt[0])  cnt[0]--,x-=2;
                        else assert(0);
                    }
                    else{
                        if(cnt[0])  cnt[0]--,x-=2;
                        else if(cnt[1]) cnt[1]--,x--;
                        else assert(0);
                    }
                    ans++;
                }
                if(x==1)    cnt[1]++;
            }
            printf("%d\n",ans);
            return;
        }
        if(t[1]==t[3]){
            int ans=0;
            for(int i=1;i+m-1<=n;i++){
                bool flag=true;for(int j=1;j<=m;j++)flag&=(s[i+j-1]==t[j]);
                ans+=flag;
            }
            debug("#4\n");
            printf("%d\n",(ans+1)>>1);
            return;
        }
        if(t[1]^t[2])   reverse(t+1,t+m+1),reverse(s+1,s+n+1);
        int ans=0;
        for(int i=n;i;i--){
            if(s[i]^t[1])   continue;
            int j=i;while(j&&s[j]==t[1])j--;j++;
            ans+=bool((i^n)&&(i^j));
            i=j;
        }
        debug("#5\n");
        printf("%d\n",ans);
        return;
    }
}
int main(){freopen("shin.in","r",stdin);freopen("shin.out","w",stdout);int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}