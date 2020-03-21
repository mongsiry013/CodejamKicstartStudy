문제 링크 : [2019_Round_A_1_Training](https://codingcompetitions.withgoogle.com/kickstart/round/0000000000050e01/00000000000698d6)

# 문제 설명

- N명 중 skill rate가 같은 P명을 선발
- 한시간당 한명만 점수를 높일 수 있다.
- 선발시간은 최소 시간을 구한다.

즉  
```
N= 4, P=3
3 1 9 100
```
일 경우  
```
3 1 9
```
를 뽑아서
```
9 9 9
```
3->9 로 만드는데 6시간
1->9 로 만드는데 8시간

14이 답이다.



# 조건
- Limits
  - Time: 15 seconds per test set.
  - Memory limit: 1 GB.
  - 1 ≤ T ≤ 100.
  - 1 ≤ Si ≤ 10000, for all i.
  - 2 ≤ P ≤ N.

- Test set 1 (Visible)  
2 ≤ N ≤ 1000.  

- Test set 2 (Hidden)  
2 ≤ N ≤ 10**5.
O(N)이나 O(NlogN)

# 풀이
- 구간합(Sum of Interval)사용
- 정렬한 이유는 기준 실력 아래 선수들에게 요구되는 시간을 구하기 편하게 하기 위해서이다.
n= 6, p =4
1 2 3 4 5 5 => 4(기준시간) * 3 - (1 + 2 + 3) = 6
|     |

1 2 3 4 5 5 => 5(기준시간) * 3 - (2 + 3 + 4) = 6
  |     |

1 2 3 4 5 5 => 5(기준시간) * 3 - (3 + 4 + 5) = 3
    |     |

``` python
import sys

def solved(N, P):
    SR = list(map(int, input().split()))
    SR.sort()

    # 첫번째 총합
    sum = 0
    for i in range(P-1):
        sum += SR[i]
    ans = SR[P-1] * (P-1) - sum

    for i in range(P,N):
        sum = sum - SR[i-P] + SR[i-1] # 각 구간별 총합을 구하는 식
        total = SR[i] * (P-1) # 총 팀원의 실력 합
        ans = min(ans, total-sum)

    return ans

for t in range(1, int(input())+1):
    N, P = map(int, input().split())
    print("Case #{}: {} ".format(t, solved(N, P)))
```



# 풀이 코드
[`코드만 보기`](./solution.py)
