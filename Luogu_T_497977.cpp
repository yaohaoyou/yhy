#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+10;
int n,t;
set<int> st;
int main(){
    scanf("%d%d",&n,&t);
    int xx=1;
    for(int i=1;i<=t;i++)xx*=10;t=xx;
    for(int i=1;i<=n;i++){
        int x;scanf("%d",&x);
        st.insert(x%t);
    }
    printf("%d\n",st.size());
}