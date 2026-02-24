#include<bits/stdc++.h>
#define eb emplace_back
using namespace std;
string s;
int n;
int ans;
vector<int> v;
int main(){
    cin>>s;
    for(int i=0;i+5<s.length();i++)
        if(s.substr(i,6)=="friend") v.eb(i);
    ans=v.size();
    for(int i=0;i<(int)v.size()-1;i++){
        int r=v[i]+5,l=v[i+1];
        if(l-r<4){ans--;i++;}
    }
    printf("%d\n",ans);
}