#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define fi first
#define se second
using namespace std;
const int maxn=55;
int n;
string s;
bool f[5][20];
map<char,int> A,B;
int main(){
    // freopen("poker.in","r",stdin);freopen("poker.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    A['D']=0;A['C']=1;A['H']=2;A['S']=3;
    B['A']=0;B['2']=1;B['3']=2;B['4']=3;B['5']=4;B['6']=5;B['7']=6;B['8']=7;B['9']=8;B['T']=9;B['J']=10;B['Q']=11;B['K']=12;
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>s;
        int x=A[s[0]],y=B[s[1]];
        f[x][y]=true;
    }
    int ans=0;
    for(int i=0;i<4;i++)
        for(int j=0;j<13;j++)
            ans+=(!f[i][j]);
    printf("%d\n",ans);
}
