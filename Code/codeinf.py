from atcoder.dsu import DSU
from collections import defaultdict
import sys
sys.setrecursionlimit(3 * 10**5)



def solve():
    n, m = map(int, input().split())
    p = list(map(lambda x: int(x) - 1, input().split()))
    uf = DSU(n)
    for i in range(m):
        x, y = map(lambda x: int(x) - 1, input().split())
        uf.merge(x, y)

    group = [uf.leader(i) for i in range(n)]
    rem = [[] for i in range(n)]
    G2 = [defaultdict(int) for i in range(n)]
    for i in range(n - 1, -1, -1):
        rem[group[i]].append(i)
        if i != 0:
            x, y = group[p[i - 1]], group[p[i]]
            G2[x][y] += 1
            G2[y][x] += 1

    use = [0] * n
    now = [0] * n
    trail = []
    
    def find(g):
        if len(G2[g]) < 300:
            mn = n
            for u, c in G2[g].items():
                if c > 0:
                    mn = min(mn, rem[u][-1])
            return mn
        while now[g] != n:
            g2 = group[now[g]]
            if use[now[g]] == 0 and g2 in G2[g] and G2[g][g2] > 0:
                return now[g]
            now[g] += 1
        return n

    def Eulerian(g):
        tmp = rem[g].pop()
        use[tmp] = 1
        while True:
            nxt = find(g)
            if nxt == n:
                break
            ng = group[nxt]
            G2[g][ng] -= 1
            G2[ng][g] -= 1
            Eulerian(ng)
        trail.append(tmp)

    Eulerian(group[p[0]])
    print(*[i + 1 for i in trail[::-1]])


for _ in range(int(input())):
    solve()
