#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
using namespace std;
const int MAXN=2850003,MAXL=500001,INF=1<<30, DEBUG=0;

template <class DType>
class SplayTree {
private:
    typedef struct node;
    typedef struct node *pnode;
    struct node {
        pnode c[2], f;
        DType key;
    };
    pnode root, null;
    node mempool[MAXN];
    int memnum;
    pnode new_node(DType key, pnode f, int o = 0) {
        pnode e = mempool+ ++memnum;
        e->key = key;
        e->f = f;
        if (f) {
            e->f->c[o] = e;
        }
        e->c[0] = e->c[1] = null;
        return e;
    }
    void rotate(pnode x, int o) {
        pnode y = x->f;
        y->c[o] = x->c[!o];
        y->c[o]->f = y;
        x->f = y->f;
        if (y->f->c[0] == y) {
            y->f->c[0] = x;
        } else {
            y->f->c[1] = x;
        }
        y->f = x;
        x->c[!o] = y;
        if (root == y) {
            root = x;
        }
    }
    void splay(pnode x, pnode y) {
        while (x->f != y) {
            if (x == x->f->c[0]) {
                rotate(x, 0);
            } else {
                rotate(x, 1);
            }
        }
    }
public:
    void insert(DType key) {
        pnode x = root, f = null;
        int o = 0;
        for (;x != null;) {
            f = x;
            if (key < x->key) {
                x = x->c[o = 0];
            } else {
                x = x->c[o = 1];
            }
        }
        if (x == root) {
            x = root = new_node(key, f, o);
        } else {
            x = new_node(key, f, o);
        }
    }
    DType del(pnode x) {
        pnode leftmax;
        splay(x, null);
        if (x->c[0] == null) {
            root = x->c[1];
            root->f = null;
        } else {
            for (leftmax = x->c[0]; leftmax->c[1] != null; leftmax = leftmax->c[1])
                ;
            splay(leftmax, x);
            leftmax->c[1] = x->c[1];
            leftmax->c[1]->f = leftmax;
            root = leftmax;
            root->f = null;
        }
        return x->key;
    }
    DType find(DType key, int pop = 0) {
        pnode x = root;
        if (x == null) {
            return DType::ZERO;
        }
        for (;;) {
            if (key == x->key || key < x->key && x->c[0] == null || key > x->key && x->c[1] == null) {
                if (pop) {
                    return del(x);
                } else {
                    return x->key;
                }
            } else if (key < x->key) {
                x = x->c[0];
            } else {
                x = x->c[1];
            }
        }
    }
    DType pop_max() {
        return find(DType::MAX, 1);
    }
    DType pop_min() {
        return find(DType::MIN, 1);
    }
    SplayTree() {
        memnum = -1;
        null = 0;
        root = null = new_node(DType::MIN, null);
    }
};

class Client {
public:
    int id, priority;
    static Client MAX, MIN, ZERO;
    Client() : id(0), priority(0) {}
    Client(int id, int priority) : id(id), priority(priority) {}
    bool operator<(const Client &other) const {
        return priority < other.priority;
    }
    bool operator>(const Client &other) const {
        return priority > other.priority;
    }
    bool operator==(const Client &other) const {
        return priority == other.priority;
    }
};

Client Client::MAX = Client(0, INF);
Client Client::MIN = Client(0, -INF);
Client Client::ZERO = Client(0, 0);

SplayTree<Client> tree;

int main() {
    int command, id, key;
    while(scanf("%d", &command)) {
        if (!command) {
            break;
        } else if (command == 1) {
            scanf("%d%d", &id, &key);
            tree.insert(Client(id, key));
        } else if (command == 2) {
            printf("%d\n", tree.pop_max().id);
        } else if (command == 3) {
            printf("%d\n", tree.pop_min().id);
        }
    }
    return 0;
}
