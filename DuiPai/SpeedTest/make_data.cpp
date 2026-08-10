#include <bits/stdc++.h>
using namespace std;
constexpr int R=10,V=1e2+10;
inline int rnd(){return 1ll*rand()*rand()%R+1;}
int fa[R];
inline int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
int main() {
	timeb t;
    ftime(&t);
    srand(time(0));
    srand(t.millitm+rand()*rand()%rand()+rand()^rand()<<11);
	int n=rand()%10+1,m=rand()%10+1;
	printf("%d %d\n",n,m);
	for(int i=1;i<=n;i++,puts(""))for(int j=1;j<=m;j++){
		int x=rand()%3;
		if(x<2)putchar(x+'0');else putchar('?');
	}
} 
