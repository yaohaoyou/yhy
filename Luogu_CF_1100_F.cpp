#include<bits/stdc++.h>
using namespace std;
const int maxn=5e5+10,logV=20;
int n,q;
int a[maxn],p[maxn][logV+10],pos[maxn][logV+10];
inline void ins(int id,int x){
    memcpy(pos[id],pos[id-1],sizeof(pos[id]));
    memcpy(p[id],p[id-1],sizeof(p[id]));
    int cx=id;
    for(int i=logV;~i;i--){
        if(!(x&(1<<i))) continue;
        if(!p[cx][i])   return p[cx][i]=x,pos[cx][i]=id,void();
        else if(pos[cx][i]<id){swap(pos[cx][i],id);swap(p[cx][i],x);}
        x^=p[cx][i];
    }
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    scanf("%d",&q);
    for(int i=1;i<=n;i++)
        ins(i,a[i]);
    while(q--){
        int l,r,res=0;
        scanf("%d%d",&l,&r);
        for(int i=logV;~i;i--){
            if(!p[r][i])   continue;
            if(res&(1<<i))  continue;
            if(pos[r][i]>=l)    res^=p[r][i];
        }
        printf("%d\n",res);
    }
}