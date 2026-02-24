#pragma GCC optimize(2,3,"Ofast")
#include<bits/stdc++.h>
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
const int maxn=1e5+10,B=1500;
int n;
char s[maxn],t[maxn];
bitset<maxn> a,q,lst,qry;
int main(){
    scanf("%d%s",&n,s);
    int sum=count(s,s+n,'1');
    for(int i=1;i<=B&&i<=n;i++){
        int ans=0;
        for(int j=0;j<n;j++){
            t[j]=s[j];
            if(t[j]=='?')   t[j]=j>=i?t[j-i]:'0';
            if(t[j]=='1')   ans++;
        }
        printf("%d\n",ans);
    }
    for(int i=0;i<n;i++)   a.set(i,s[i]=='1'),q.set(i,s[i]=='?');
    for(int i=B+1;i<=n;i++){
        lst=a;
        qry.reset();
        for(int l=i-1,r;l<n;l=r+1){
            r=min(n-1,l+i-1);
            lst<<=i;lst&=q;qry|=lst;
            lst=qry|a;
        }
        printf("%d\n",lst.count());
    }
}