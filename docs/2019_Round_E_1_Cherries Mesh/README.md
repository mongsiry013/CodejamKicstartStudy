``` python
def find(parent, x):
    if parent[x] == x:
        return x
    parent[x] = find(parent, parent[x]) # 경로압축
    return parent[x]


def union(parent, x, y):
    if x != y:
        parent[y] = x
        return 1
    return 0


for t in range(int(input())):
    N, M = map(int, input().split())

    cnt = 0
    parent = list(range(0, N + 1))

    for _ in range(M):
        s, e = map(int, input().split())
        cnt += union(parent, find(parent, s), find(parent, e)) # 블랙으로 연결하는 행위

    print("Case #%d: %d" % (t + 1, (N - 1) * 2 - cnt*1))
    # 전체가 다 빨간색으로 연결이 되있따고 가정을 하는데 블랙으로 연결할 수 있는 것은 연결하는게 최소값이 된다.
    # 블랙의 개수를 빼는게 답이 됩니다.
```
