// P5091 【模板】扩展欧拉定理
#include<bits/stdc++.h>
using namespace std;
int a,mod,b,phimod;
bool flag;
int getint(){
    char x=getchar();
    while(!isdigit(x))  x=getchar();
    int res=0;
    while(x!='\n'&&x!=EOF&&x!='\r'){
        res=1ll*res*10%phimod+x-48;
        if(res>phimod){res-phimod;flag=1;}
        x=getchar();
    }
    return res;
}
int qpow(int x,int y){
    int res=1;
    while(y){
        if(y&1) res=1ll*res*x%mod;
        x=1ll*x*x%mod;
        y>>=1;
    }
    return res;
}
int main(){
    scanf("%d%d",&a,&mod);
    int m=mod;
    phimod=mod;
    for(int i=2;i*i<=mod;i++){
        if(mod%i==0){
            phimod=phimod/i*(i-1);
            while(mod%i==0) mod/=i;
        }
    }
    if(mod>1) phimod=phimod/mod*(mod-1);
    mod=m;
    b=getint();
    b+=flag*phimod;
    // b+=phimod;
    printf("%d",qpow(a,b));
}