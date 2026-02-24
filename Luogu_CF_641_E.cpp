#include<bits/stdc++.h>
#define eb emplace_back
using namespace std;
const int maxn=1e5+10;
vector<int> T,X;
int q;
int a[maxn];
struct ques{
    int opt,t,x,id,ans;
}Q[maxn];
void discrete(){
    sort(T.begin(),T.end());
    T.erase(unique(T.begin(),T.end()),T.end());
    sort(X.begin(),X.end());
    X.erase(unique(X.begin(),X.end()),X.end());
}
vector<int> id[maxn];
int tlen;
namespace BIT{
    int tr[maxn];
    inline int lowbit(int x){return x&-x;}
    inline void add(int x,int s){while(x<=tlen){tr[x]+=s;x+=lowbit(x);}}
    inline int que(int x){int res=0;while(x){res+=tr[x];x-=lowbit(x);}return res;}
}
int main(){
    scanf("%d",&q);
    for(int i=1;i<=q;i++){
        scanf("%d%d%d",&Q[i].opt,&Q[i].t,&Q[i].x);
        T.eb(Q[i].t);X.eb(Q[i].x);
        Q[i].id=i;
    }
    discrete();
    tlen=T.size();
    for(int i=1;i<=q;i++){
        Q[i].x=lower_bound(X.begin(),X.end(),Q[i].x)-X.begin()+1;
        id[Q[i].x].eb(i);
    }
    for(int l=1;l<=X.size();l++){
        for(int i:id[l]){
            Q[i].t=lower_bound(T.begin(),T.end(),Q[i].t)-T.begin()+1;
            if(Q[i].opt==1) BIT::add(Q[i].t,1);
            else if(Q[i].opt==2)    BIT::add(Q[i].t,-1);
            else    Q[i].ans=BIT::que(Q[i].t);
        }
        for(int i:id[l]){
            if(Q[i].opt==1) BIT::add(Q[i].t,-1);
            else if(Q[i].opt==2)    BIT::add(Q[i].t,1);
        }
    }
    sort(Q+1,Q+q+1,[&](ques x,ques y){return x.id<y.id;});
    for(int i=1;i<=q;i++)
        if(Q[i].opt==3) printf("%d\n",Q[i].ans);
}