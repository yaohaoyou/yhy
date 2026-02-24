#include <bits/stdc++.h>
using namespace std;
constexpr int R=10,V=1e2+10;
inline int rnd(){return 1ll*rand()*rand()%R+1;}
int fa[R];
inline int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
int main() {
	freopen("S:\\yhy\\DuiPai\\Normal\\data.in","w",stdout);
	timeb t;
    ftime(&t);
    srand(time(0));
    srand(t.millitm+rand()*rand()%rand()+rand()^rand()<<11);
	int n=rand()%5+1;
	printf("%d ",n);
	n=1<<n;
	int l=rand()%n,r=rand()%n;
	if(l>r)	swap(l,r);
	printf("%d %d\n",l,r);
} 
