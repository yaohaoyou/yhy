#include<bits/stdc++.h>
using namespace std;
const int maxn=30*100;
int n;
string s;
int a[maxn];
namespace Graph{
    const int maxm=maxn<<2;
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to,w,c;}e[maxm];
    inline void add(int u,int v,int w,int c){e[++cnt]={head[u],v,w,c};head[u]=cnt;}
    inline void addedge(int u,int v,int w,int c){c=-c;add(u,v,w,c);add(v,u,0,-c);}
}
using namespace Graph;
int S,T;
queue<int> q;
bool inque[maxn];
int lst[maxn],lsti[maxn],d[maxn],flw[maxn];
bool bfs(){
    q.push(S);inque[S]=true;
    memset(d,0x3f,sizeof(d));memset(flw,0x3f,sizeof(flw));
    d[S]=lst[T]=0;
    while(!q.empty()){
        int u=q.front();
        inque[u]=false;
        q.pop();
        for(int i=head[u];i;i=e[i].nxt){
            int t=e[i].to;
            if(e[i].w&&d[u]+e[i].c<d[t]){
                flw[t]=min(e[i].w,flw[u]);
                d[t]=d[u]+e[i].c;
                lst[t]=u;lsti[t]=i;
                if(!inque[t]){q.push(t);inque[t]=true;}
            }
        }
    }
    return lst[T];
}
void MFMC(int x){
    int cost=0;
    while(bfs()){
        cost+=(flw[T]*d[T]);
        for(int p=T;p!=S;p=lst[p]){
            e[lsti[p]].w-=flw[T];e[lsti[p]^1].w+=flw[T];
        }
    }
    printf("%d\n",x*cost);
}
int tot;
int id[30][maxn],pos[maxn];
int bas[30];
int main(){
    // ios::sync_with_stdio(false);
    // cin.tie(0);cout.tie(0);
    cin>>n>>s;s=' '+s;
    for(int i=1;i<=n;i++)   bas[s[i]-'a'+1]++;
    for(int i=1;i<=n;i++)   cin>>a[i];
    S=0;
    tot=26;
    for(int i=1;i<=26;i++)  addedge(S,i,bas[i],0);
    for(int i=1;i<=n;i++)   pos[i]=++tot;
    for(int i=1;i<=26;i++){
        char ch='a'+i-1;
        for(int j=1;j<=n/2;j++){
            id[i][j]=++tot;
            addedge(i,id[i][j],1,0);
            if(ch==s[j])    addedge(id[i][j],pos[j],1,a[j]);
            else    addedge(id[i][j],pos[j],1,0);
            if(ch==s[n-j+1])    addedge(id[i][j],pos[n-j+1],1,a[n-j+1]);
            else    addedge(id[i][j],pos[n-j+1],1,0);
        }
    }
    T=++tot;
    // printf("tot = %d\n",tot);
    for(int i=1;i<=n;i++)   addedge(pos[i],T,1,0);
    MFMC(-1);
}