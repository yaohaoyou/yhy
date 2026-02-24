//  P3805 【模板】manacher
#include<bits/stdc++.h>
using namespace std;
constexpr int maxn=1.1e7+10;
string s1,s;
int p[maxn<<1];
int n,ans;
int main(){
    cin>>s1;
    n=s1.length();
    s1=' '+s1;
    s='?';
    for(int i=1;i<=n;i++){s+='#';s+=s1[i];}
    int r=0,mid=0;
    s+='#';
    // cout<<s<<'\n';
    for(int i=1;i<s.length();i++){
        p[i]=i>r?1:min(p[(mid<<1)-i],r-i+1);
        while(s[i+p[i]]==s[i-p[i]]) p[i]++;
        if(i+p[i]>r){r=i+p[i]-1;mid=i;}
        // printf("%d %d\n",i,p[i]);
        ans=max(ans,p[i]);
    }
    printf("%d\n",ans-1);
}