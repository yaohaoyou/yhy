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
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
const int L=128,maxn=150;
vector<char> ch;
int n;
int buc[maxn];
int ask(string s){int x;printf("? %s\n",s.c_str());fflush(stdout);scanf("%d",&x);return x;}
string divide(int l,int r){
    string res="";
    if(l==r){for(int i=1;i<=buc[l];i++)res+=ch[l];return res;}
    int mid=(l+r)>>1;
    string s=divide(l,mid),t=divide(mid+1,r);
    int i=0,j=0;
    while(i<s.length()||j<t.length()){
        // debug("j = %d\n",j);
        if(i==s.length()) res+=t[j++];
        else if(j==t.length())    res+=s[i++];
        else{
            string as=res+s[i]+t.substr(j,t.length()-j);
            if(ask(as)==n-as.length())  res+=s[i++];
            else    res+=t[j++];
        }
    }
    return res;
}
int main(){
    for(char c='a';c<='z';c++)  ch.eb(c);
    for(char c='A';c<='Z';c++)  ch.eb(c);
    for(char c='0';c<='9';c++)  ch.eb(c);
    for(int i=0;i<ch.size();i++){
        char c=ch[i];
        string s="";for(int i=1;i<=L;i++)s+=c;
        buc[i]=L-ask(s);n+=buc[i];
    }
    string ans=divide(0,ch.size()-1);
    printf("! %s\n",ans.c_str());fflush(stdout);
    // while(1);
}