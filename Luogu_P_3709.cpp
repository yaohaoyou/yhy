#include<bits/stdc++.h>
#define eb emplace_back
using namespace std;
constexpr int maxn=5e5+10,maxB=750;
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
    int p[maxB][maxB],pnum[maxB][maxB],bl[maxB],br[maxB],id[maxn],bas[maxn];
    int pos[maxn];
    vector<int> v[maxn];
    void init(){
        for(int i=1;i<=n;i++)
            id[i]=(i-1)/B+1;
        for(int i=1;i<=n;i++){
            pos[i]=v[a[i]].size();
            v[a[i]].eb(i);
        }
        for(int i=1;i<=id[n];i++){
            bl[i]=(i-1)*B+1;
            br[i]=min(i*B,n);
        }
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
        int idl=id[l],idr=id[r],lstl=l,lstr=r,ans=0,res;
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
        while(id[l]==idl){if(a[l]==p[idl+1][idr-1])max1++;l++;}
        while(id[r]==idr){if(a[r]==p[idl+1][idr-1])max1++;r--;}
        l=lstl;r=lstr;
        while(id[l]==idl){
            int p=pos[l];
            if(p+max1<v[a[l]].size()&&v[a[l]][p+max1]<=r){
                p+=max1;
                while(p+1<v[a[l]].size()&&v[a[l]][p+1]<=r)  p++;
                max1=p-pos[l]+1;
            }
            l++;
        }
        l=lstl;r=lstr;
        while(id[r]==idr){
            int p=pos[r];
            if(p-max1>=0&&v[a[r]][p-max1]>=l){
                p-=max1;
                while(p-1>=0&&v[a[r]][p-1]>=l)  p--;
                max1=pos[r]-p+1;
            }
            r--;
        }
        return max1;
    }
}
using namespace Block_array;
int main(){
    int lstans=0;
    scanf("%d%d",&n,&q);
    B=maxB-10;
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    discrete();
    init();
    while(q--){
        int l,r;
        scanf("%d%d",&l,&r);
        lstans=0;
        l=l^lstans,r=r^lstans;
        if(l>r) swap(l,r);
        lstans=query(l,r);
        printf("%d\n",-lstans);
    }
}