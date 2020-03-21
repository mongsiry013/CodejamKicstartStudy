import sys

def solved(N, P):
    SR = list(map(int, input().split()))
    SR.sort()

    sum = 0
    for i in range(P-1):
        sum += SR[i]
    ans = SR[P-1]*(P-1) - sum

    for i in range(P,N):
        sum = sum - SR[i-P] + SR[i-1]
        total = SR[i]*(P-1)
        ans = min(ans, total-sum)

    return ans

for t in range(1, int(input())+1):
    N, P = map(int, input().split())
    print("Case #{}: {} ".format(t, solved(N, P)))
