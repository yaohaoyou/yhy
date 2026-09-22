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
const int maxn=110;
bool mem1;
int n;
string a,b;
bool mem2;
string XOR(string x,string y){
    string res="";
    for(int i=x.length()-1,j=y.length()-1;i>=0||j>=0;i--,j--){
        bool o=0;
        if(i>=0)    o=x[i]-'0';
        if(j>=0)    o^=(y[j]-'0');
        res+=o+'0';
    }
    while(res.size()>1&&res.back()=='0')   res.pop_back();
    reverse(res.begin(),res.end());
    return res;
}
void matt(int _cases){
    a=b="";
    cin>>n>>a;
    bool zero=count(a.begin(),a.end(),'0');
    int st=0;bool fl=false;
    for(int i=0;i<a.length();i++){
        if(a[i]=='1')   st++;
        else if(st){
            int j=i;while(j<a.length()&&a[j]=='0')j++;
            for(int k=i-min(st,j-i);b.length()<a.length()-i;k++)   b+=a[k];
            fl=true;
            break;
        }
    }
    if(fl)  cout<<XOR(a,b)<<'\n';
    else{
        if(zero&&st)    cout<<XOR(a,"0")<<'\n';
        else if(zero&&!st)  cout<<"0\n";
        else    cout<<XOR(a,"1")<<'\n';
    }
}
int main(){ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);int T;cin>>T;for(int i=1;i<=T;i++)matt(i);}