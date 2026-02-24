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
const int maxn=4e6+10;
int n,q;
char s[maxn];
int p[maxn];
int main(){
    scanf("%d%d%s",&n,&q,s+1);
    while(q--){
        int k;scanf("%d",&k);
        string t="~|";
        int len=0;
        ll ans=0;
        for(int i=max(1,k-n);i<=min(n,k-1);i++) t+=s[i],t+='|',t+=s[k-i],t+='|',len++;
        t+='?';
        if(0){
            t="";
            for(int i=max(1,k-n);i<=min(n,k-1);i++) t+=s[i],t+=s[k-i],len++;
            cout<<t<<'\n';
            for(int i=0;i+1<=len;i+=2){
                for(int j=i+1;j<t.length();j+=2){
                    bool flag=true;
                    for(int l=i,r=j;l<r;l++,r--)if(t[l]^t[r]){flag=false;break;}
                    if(flag){
                        ans++;
                        printf("%d %d\n",i+1,j+1);
                    }
                }
            }
            printf("%lld\n",ans);
            continue;
        }
        int r=0,mid=0;
        for(int i=0;i*2<t.length();i++){
            if(i<r) p[i]=min(r-i+1,p[(mid<<1)-i]);
            else p[i]=0;
            while(t[i+p[i]]==t[i-p[i]]) p[i]++;
            if(t[i]=='|'){
                // printf("%d : %d\n",i,(i%4==1)?p[i]/4:(p[i]+2)/4);
                // (i-r+1)/2<=len
                // r>=i+1-2len
                int l=max(1,i+1-2*len),r=p[i];
                while(r>=1&&(i-r+1)%4!=2)r--;
                while(l<=i&&(i-l+1)%4!=2)l++;
                // printf("%d %d\n",l,r);
                // printf("%d [%d,%d] %d %d\n",i,l,r,l<=r?(r-l)/4+1:0,p[i]);
                if(l<=r)    ans+=(r-l)/4+1;
            }
            if(i+p[i]-1>r)  mid=i,r=i+p[i]-1;
        }
        printf("%lld\n",ans);
    }
}