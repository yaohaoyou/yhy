#include<bits/stdc++.h>
using namespace std;
constexpr int maxn=1e5+10,maxB=500;
int n,q,B,siz;
int a[maxn],b[maxn];
void discrete(){
    for(int i=1;i<=n;i++)   b[i]=a[i];
    sort(b+1,b+n+1);
    siz=unique(b+1,b+n+1)-b-1;
    for(int i=1;i<=n;i++)
        a[i]=lower_bound(b+1,b+siz+1,a[i])-b;
}
namespace Block_array{
    int p[maxB][maxB],pnum[maxB][maxB],s[maxB][maxn],bl[maxB],br[maxB],id[maxn],bas[maxn];
    void init(){
        for(int i=1;i<=n;i++){
            id[i]=(i-1)/B+1;
            s[id[i]][a[i]]++;
        }
        for(int i=1;i<=id[n];i++){
            bl[i]=(i-1)*B+1;
            br[i]=min(i*B,n);
        }
        for(int i=2;i<=id[n];i++)
            for(int j=1;j<=n;j++)
                s[i][j]+=s[i-1][j];
        for(int i=1;i<=id[n];i++){
            int max1=0,idm=maxn;
            memset(bas,0,sizeof(bas));
            for(int j=i;j<=id[n];j++){
                for(int k=bl[j];k<=br[j];k++){
                    bas[a[k]]++;
                    if((bas[a[k]]>max1)||(bas[a[k]]==max1&&a[k]<idm)){
                        idm=a[k];
                        max1=bas[a[k]];
                    }
                }
                p[i][j]=idm;
                pnum[i][j]=max1;
            }
        }
        memset(bas,0,sizeof(bas));
    }
    int query(int l,int r){
        int idl=id[l],idr=id[r],ans=0,res;
        if(idr-idl<=2){
            for(int i=l;i<=r;i++){
                bas[a[i]]++;
                if((bas[a[i]]>bas[ans])||(bas[a[i]]==bas[ans]&&a[i]<ans))   ans=a[i];
            }
            res=bas[ans];
            for(int i=l;i<=r;i++)   bas[a[i]]=0;
            return res;
        }
        ans=p[idl+1][idr-1];
        int max1=pnum[idl+1][idr-1];
        for(int i=l;i<=br[idl];i++){
            if(!bas[a[i]])  bas[a[i]]=s[idr-1][a[i]]-s[idl][a[i]];
            bas[a[i]]++;
            if((bas[a[i]]>max1)||(bas[a[i]]==max1&&a[i]<ans)){ans=a[i];max1=bas[a[i]];}
        }
        for(int i=r;i>=bl[idr];i--){
            if(!bas[a[i]])  bas[a[i]]=s[idr-1][a[i]]-s[idl][a[i]];
            bas[a[i]]++;
            if((bas[a[i]]>max1)||(bas[a[i]]==max1&&a[i]<ans)){ans=a[i];max1=bas[a[i]];}
        }
        for(int i=l;i<=br[idl];i++) bas[a[i]]=0;
        for(int i=r;i>=bl[idr];i--) bas[a[i]]=0;
        return max1;
    }
}
using namespace Block_array;
int main(){
    int lstans=0;
    scanf("%d%d",&n,&q);
    B=ceil(sqrt(n));
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    discrete();
    init();
    while(q--){
        lstans=0;
        int l,r;
        scanf("%d%d",&l,&r);
        l=l^lstans,r=r^lstans;
        if(l>r) swap(l,r);
        lstans=query(l,r);
        printf("%d\n",lstans);
    }
}