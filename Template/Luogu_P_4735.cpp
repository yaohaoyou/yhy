//  P4735 最大异或和 可持久化 01Trie
#include<bits/stdc++.h>
using namespace std;
const int maxn=6e5+10;
int n,q;
namespace Trie{
    int tot;
    int nex[maxn*24+10][2],rt[maxn],cnt[maxn*24+10];
    void insert(int x,int id){
        rt[id]=++tot;
        int p=rt[id],q=rt[id-1];
        for(int i=24;~i;i--){
            cnt[p]=cnt[q]+1;
            nex[p][0]=nex[q][0];nex[p][1]=nex[q][1];
            if(x&(1<<i)){
                nex[p][1]=++tot;
                p=nex[p][1];q=nex[q][1];
            }
            else{
                nex[p][0]=++tot;
                p=nex[p][0];q=nex[q][0];
            }
        }
        cnt[p]=cnt[q]+1;
    }
    int query(int l,int r,int x){
        // printf("%d %d %d\n",l,r,x);
        int p=rt[l],q=rt[r],ans=0;
        for(int i=24;~i;i--){
            if(x&(1<<i)){
                if(cnt[nex[p][0]]^cnt[nex[q][0]]){
                    p=nex[p][0];q=nex[q][0];
                    ans|=(1<<i);
                }
                else{p=nex[p][1];q=nex[q][1];}
            }
            else{
                // if(i==2)    printf("**%d %d\n",cnt[nex[p][1]],cnt[nex[q][1]]);
                if(cnt[nex[p][1]]^cnt[nex[q][1]]){
                    p=nex[p][1];q=nex[q][1];
                    ans|=(1<<i);
                }
                else{p=nex[p][0];q=nex[q][0];}
            }
        }
        return ans;
    }
}
using namespace Trie;
int s[maxn];
int main(){
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++){
        int x;
        scanf("%d",&x);
        s[i]=s[i-1]^x;
        insert(s[i],i);
    }
    while(q--){
        char ch[10];
        int l,r,x;
        scanf("%s",ch);
        if(ch[0]=='A'){
            scanf("%d",&x);
            n++;s[n]=s[n-1]^x;
            insert(s[n],n);
        }
        else{
            scanf("%d%d%d",&l,&r,&x);
            l--;r--;
            if(!l)  printf("%d\n",max(s[n]^x,query(0,r,s[n]^x)));
            else    printf("%d\n",query(l-1,r,s[n]^x));
        }
    }
}