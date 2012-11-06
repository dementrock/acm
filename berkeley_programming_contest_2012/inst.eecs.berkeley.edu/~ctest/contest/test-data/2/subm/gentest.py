#!/usr/bin/env python

import re, sys
import random

N = int(sys.argv[1])
M = int(sys.argv[2])
name = sys.argv[3]

infile = open(name + ".inp", "w")
outfile = open(name + ".results", "w")
random.seed(sys.argv[4])

def gcd(x, y):
    if x == 0:
        return y
    elif x > y:
        return gcd(y, x)
    else:
        return gcd(x, y%x)

primes = (2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59,
          61, 67, 71, 73, 79, 83, 89, 97)

lim = 2**31

def num1():
    n = 1
    R = []
    while True:
        x = random.choice(primes)
        if x*n >= lim:
            return n, R
        n *= x
        R.append(x)

def nums(L, N):
    L = list(L)
    random.shuffle(L)

    R = [1] * N
    k = 0
    while k < len(L):
        k0 = k

        for i in xrange(N):
            if k >= len(L):
                break
            
            if R[i] * L[k] < lim:
                R[i] *= L[k]
                k += 1

        if k == k0:
            print "Excess items"
            sys.exit(1)
            break

    return R

factors = [ primes[i % len(primes)] for i in xrange(N * M) ]

n, nf = num1()
d, df = num1()

numers = nums(factors + nf, N)
denoms = nums(factors + df, N)

for i in xrange(N):
    print >>infile, "%d/%d" % (numers[i], denoms[i])

g = gcd(n, d)
print >>outfile, "%d/%d" % (n // g, d // g)

infile.close()
outfile.close()

