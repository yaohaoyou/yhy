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
#define YES return puts("Yes"),void()
#define NO return puts("No"),void()
using namespace std;
const int maxn = 2e5 + 5;
int n, a[maxn], b[maxn], buk[maxn];
void data(){
    n=4e4;
    printf("%d\n",n);
    if(rand()%3){
        vector<int> ans;ans.clear();
        while(ans.size()<n){
            int x=rand()%2+1;
            ans.eb(x);
            if(x==2)    continue;
            int k=rand()%1000+2;
            while(k--)  ans.eb(2);
        }
        for(int i=1;i<=n;i++)   a[i]=ans[i-1];
        memc(b,a);
        if(rand()&1){
            for(int i=1;i<n;i++)if(b[i]==1){swap(b[i],b[i+1]);break;}
        }
        for(int i=1;i<=n;i++)   printf("%d ",a[i]);puts("");
        for(int i=1;i<=n;i++)   printf("%d ",b[i]);puts("");
    }
    else{
        for(int i=1;i<=n;i++)   a[i]=rand()%2+1;
        for(int i=1;i<=n;i++)   printf("%d ",a[i]);puts("");
        random_shuffle(a+1,a+n+1);
        for(int i=1;i<=n;i++)   printf("%d ",a[i]);puts("");
    }
}
void solve() {
	// cin >> n; for(int i = 1; i <= n; i++) cin >> a[i];for(int i = 1; i <= n; i++) cin >> b[i];
    return data();
    memset(buk,0,sizeof(buk));
    for(int i = 1; i <= n; i++) buk[a[i]]++; for(int i = 1; i <= n; i++) buk[b[i]]--;
    for(int i = 1; i <= n; i++) if(buk[a[i]]) return cout << "No\n", void();//���ַ����Ƿ����
    int cnt = 0;
    for(int i = 1; i <= n; i++) cnt += (a[i] & 1 ^ 1);
    if(cnt >= 1){
        bool f = 0, f1 = 0;
        for(int i = 1; i < n - 1; i++){
            int x = 0;
            x += a[i] & 1;
            x += a[i + 1] & 1;
            x += a[i + 2] & 1;
            if(x == 2) f = 1;
        }
        for(int i = 1; i < n - 1; i++){
            int x = 0;
            x += b[i] & 1;
            x += b[i + 1] & 1;
            x += b[i + 2] & 1;
            if(x == 2) f1 = 1;
        }
        if(f && f1){//���1
            if(cnt >= 3) return cout << "Yes\n", void();
            int x; for(int i = n; i >= 1; i--) if(a[i] & 1 ^ 1) x = i;
            for(int i = 1; i <= n; i++){
                if((b[i] & 1 ^ 1) && b[i] != a[x]) return cout << "No\n", void();
                else if((b[i] & 1 ^ 1)) break;
            }
            cout << "Yes\n";
            return;
        }
        for(int i = 1; i <= n; i++){
            if(a[i] & 1){
                if(a[i] != b[i]) return cout << "No\n", void();
                continue;
            }
            int p = i; while(p < n && (a[p + 1] & 1 ^ 1)) p++;
            if(p - i + 1 < 3){
                for(int j = i; j <= p; j++) if(a[j] != b[j]) return cout << "No\n", void();
            }else{
                for(int j = i; j <= p; j++) buk[a[j]]++;
                for(int j = i; j <= p; j++) buk[b[j]]--;
                for(int j = i; j <= p; j++) if(buk[a[j]]) return cout << "No\n", void();
            }
            i = p;
        }
        cout << "Yes\n";
    }
    else{//����û��ż�������
        for(int i = 1; i <= n; i++) if(a[i] != b[i]) return cout << "No\n", void();
        cout << "Yes\n";
    }
}
int main(){srand(time(0));int T=5;printf("%d\n",T);while(T--)solve();}