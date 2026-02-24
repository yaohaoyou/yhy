#include<bits/stdc++.h>
#define ull unsigned long long
using namespace std;
const int maxn=1e6+10,base=31;
int n,p[maxn];
ull hsh[maxn],bs[maxn];
string s;
unordered_map<ull,bool> mp;
inline ull Hash(int l,int r){return hsh[r]-hsh[l-1]*bs[r-l+1];}
inline bool check(int x){
    mp.clear();
    for(int i=1;i<=n;i++){
        if(p[i]<x)  continue;
        if(mp[Hash(i-x+1,i)])    return true;
        mp[Hash(i-x+1,i)]=true;
    }
    return false;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin>>n>>s;
    s='|'+s+'#';
    bs[0]=1;
    for(int i=1;i<=n;i++){
        hsh[i]=hsh[i-1]*base+(s[i]-'a');
        bs[i]=bs[i-1]*base;
    }
    for(int i=1,mid=0,r=0;i<=n;i++){
        p[i]=i>r?1:min(p[(mid<<1)-i],r-i+1);
        while(s[i+p[i]]==s[i-p[i]]) p[i]++;
        if(i+p[i]>r){r=i+p[i]-1;mid=i;}
    }
    int l=1,r=n,ans=0;
    while(l<=r){
        int mid=(l+r)>>1;
        if(check(mid)){ans=mid;l=mid+1;}
        else    r=mid-1;
    }
    printf("%d\n",ans);
}