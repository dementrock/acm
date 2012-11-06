#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>

#define MAXP 100000

using namespace std;

struct primepair {
  int prime;
  int exp;
};

struct num {
  primepair factors[50];
  int numfactors;
};

bool isprime[MAXP+1];
int primes[MAXP+1], cntprimes;
map<int, int> ansfactors;

void initprimes(void) { // tested
  cntprimes = 0;
  memset(isprime, true, sizeof(isprime));
  primes[++cntprimes] = 2;
  for (int i = 3; i <= MAXP; i += 2) if (isprime[i]) {
    primes[++cntprimes] = i;
    for (int j = i + i; j <= MAXP; j += i) {
      isprime[j] = false;
    }
  }
}

num tonum(int x) {
  num numx;
  numx.numfactors = 0;
  for (int i = 1; i <= cntprimes; ++i) if (x % primes[i] == 0) {
    ++numx.numfactors;
    numx.factors[numx.numfactors].prime = primes[i];
    numx.factors[numx.numfactors].exp = 0;
    while (x % primes[i] == 0) {
      x /= primes[i];
      ++numx.factors[numx.numfactors].exp;
    }
    if (x <= 1) {
      break;
    }
  }
  if (x != 1) {
    ++numx.numfactors;
    numx.factors[numx.numfactors].prime = x;
    numx.factors[numx.numfactors].exp = 1;
  }
  return numx;
}

void process(int nom, int denom) {
  num numnom = tonum(nom);
  num numdenom = tonum(denom);
  for (int i = 1; i <= numnom.numfactors; ++i) {
    ansfactors[numnom.factors[i].prime] += numnom.factors[i].exp;
  }
  for (int i = 1; i <= numdenom.numfactors; ++i) {
    ansfactors[numdenom.factors[i].prime] -= numdenom.factors[i].exp;
  }
}

int main() {
  int nom, denom;
  map<int, int>::iterator iter;
  initprimes();
  while (scanf("%d/%d", &nom, &denom) != EOF) {
    process(nom, denom);
  }
  nom = denom = 1;
  for (iter = ansfactors.begin(); iter != ansfactors.end(); ++iter) {
    if (iter->second > 0) {
      for (int i = 1; i <= iter->second; ++i) {
        nom *= iter->first;
      }
    } else if (iter->second < 0) {
      for (int i = 1; i <= -iter->second; ++i) {
        denom *= iter-> first;
      }
    }
  }
  cout << nom << "/" << denom << endl;
  return 0;
}

