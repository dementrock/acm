#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;

const static int INF = 1 << 30;

template <class DType>
class Treap {
private:
    typedef struct node;
    typedef struct node *pnode;
    struct node {
        DType key;
        pnode left, right;
        int total;
        int priority;
    };
    pnode null, root;
    
    void lift_right(pnode &cur) {
        pnode tmp = cur->right;
        cur->right = tmp->left;
        tmp->left = cur;
        tmp->total = cur->total;
        cur->total = cur->left->total + cur->right->total + 1;
        cur = tmp;    
    }
    
    void lift_left(pnode &cur) {
        pnode tmp = cur->left;
        cur->left = tmp->right;
        tmp->right = cur;
        tmp->total = cur->total;
        cur->total = cur->left->total + cur->right->total + 1;
        cur = tmp;    
    }

    void insert(pnode &cur, DType key) {
        if (cur == null) {
            cur = new struct node;
            cur->key = key;
            cur->left = null;
            cur->right = null;
            cur->total = 1;
            cur->priority = rand();
        } else if (key < cur->key) {
            insert(cur->left, key);
            if (cur->left->priority > cur->priority) {
                lift_left(cur);
            }
        } else if (key > cur->key) {
            insert(cur->right, key);
            if (cur->right->priority < cur->priority) {
                lift_right(cur);
            }
        }
    }

    void del(pnode &cur, DType key) {
        if (cur != null) {
            if (key < cur->key) {
                del(cur->left, key);
            } else if (key > cur->key) {
                del(cur->right, key);
            } else {
                if (cur->left == null && cur->right == null) {
                    delete cur;
                    cur = null;
                } else {
                    if (cur->left->priority > cur->right->priority) {
                        lift_left(cur);
                    } else {
                        lift_right(cur);
                    }
                    del(cur, key);
                }
            }
        }
    }

    DType find_nearest(pnode cur, DType key) {
        if (cur == null) {
            return DType::ZERO;
        } else if (key == cur->key || key < cur->key && cur->left == null || key > cur->key && cur->right == null) {
            return cur->key;
        } else if (key < cur->key) {
            return find_nearest(cur->left, key);
        } else {
            return find_nearest(cur->right, key);
        }
    }

    void erase(pnode cur) {
        if (cur != null) {
            if (cur->left != null) {
                erase(cur->left);
            }
            if (cur->right != null) {
                erase(cur->right);
            }
            delete cur;
        }
    }

public:
    Treap(void) {
        null = new struct node;
        null->key = DType::MIN;
        null->left = null;
        null->right = null;
        null->total = 0;
        null->priority = -INF;
        root = null;
    }

    ~Treap(void) {
        erase(root);
        delete null;
    }

    void insert(DType key) {
        insert(root, key);
    }

    void del(DType key) {
        del(root, key);
    }

    DType find(DType key) {
        return find_nearest(root, key);
    }

    DType pop_find(DType key) {
        DType x = find(key);
        if (root != null) {
            del(x);
        }
        return x;
    }

    DType pop_max(void) {
        return pop_find(DType::MAX);
    }

    DType pop_min(void) {
        return pop_find(DType::MIN);
    }

};

typedef class Client;

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

Treap <Client> tree;

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
