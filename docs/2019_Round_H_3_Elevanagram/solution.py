from collections import deque as dq
from collections import defaultdict as dd
from collections import Counter as ct
from functools import lru_cache as lc
from heapq import heappush as hpush, heappop as hpop, heapify as hfy
from bisect import bisect_left, bisect_right
import itertools as it
import math
import sys
sys.setrecursionlimit(10 ** 9)
####################################################################

@lc(None)
def recur(idx, r, diff) :
    global D
    if idx == len(D) :
        if r != 0 :
            return False
        elif len(D) % 2 == 0 and diff != 0 :
            return False
        elif len(D) % 2 == 1 and diff != 1 :
            return False
        else :
            return True
    
    if recur(idx+1, (r + D[idx]) % 11, diff + 1) :
        return True
    elif recur(idx+1, (r - D[idx]) % 11, diff - 1) :
        return True
    else :
        return False

def solve() :
    global D
    A = [0] + list(map(int, input().split()))
    D = []
    for i in range(len(A)):
        if A[i] > 20 :
            A[i] = 20 if A[i] % 2 == 0 else 19
        D += [i] * A[i]
            
    ret = recur(0, 0, 0)
    recur.cache_clear()
    if ret :
        return "YES"
    else :
        return "NO"

t = int(input())
for i in range(t):
    print("Case #", i+1, ": ", solve(), sep="")
