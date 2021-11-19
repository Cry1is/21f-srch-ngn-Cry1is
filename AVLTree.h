//
// Created by Zachary on 11/17/2021.
//

#ifndef INC_21F_SRCH_NGN_CRY1IS_AVLTREE_H
#define INC_21F_SRCH_NGN_CRY1IS_AVLTREE_H

#include <algorithm>
#include <iostream>

using namespace std;

template<class K, class V> class AVLTree;

template<class K, class V> ostream& operator<<(ostream&, const AVLTree<K,V>&);

template<class K, class V>
struct Node {
    K first;
    V second;
    Node<K,V>* parent,* left,* right;
    Node(K& first, V& second) {
        this->first = first;
        this->second = second;
        parent = left = right = nullptr;
    }

    friend class AVLTree<K,V>;
};

template<class K, class V>
class AVLTree {
private:
    Node<K,V>* head;

    void copy(Node<K,V>*, Node<K,V>*);
    void destruct(Node<K,V>*);
    void balance(Node<K,V>*);
    void LL(Node<K,V>*);
    void LR(Node<K,V>*);
    void RR(Node<K,V>*);
    void RL(Node<K,V>*);
    int height(Node<K,V>*);
    void replace(Node<K,V>*);
    Node<K,V>* look(K&, Node<K,V>*);
    void out(ostream&,Node<K,V>*,int) const;
public:
    AVLTree();
    AVLTree(const AVLTree<K,V>&);
    ~AVLTree();

    AVLTree<K,V>& operator=(const AVLTree<K,V>&);

    void clear();

    V& insert(Node<K,V>*);
    V& insert(K&, V&);

    void remove(K&);

    Node<K,V>* find(K&);

    friend ostream& operator<< <>(ostream&, const AVLTree<K,V>&);
};

template<class K, class V>
AVLTree<K,V>::AVLTree() {
    head = nullptr;
}

template<class K, class V>
AVLTree<K,V>::AVLTree(const AVLTree<K,V>& other) {
    copy(head, other.head);
}

template<class K, class V>
AVLTree<K,V>::~AVLTree() {
    clear();
}

template<class K, class V>
AVLTree<K,V>& AVLTree<K,V>::operator=(const AVLTree<K,V>& other) {
    clear();
    copy(head, other.head);
}

template<class K, class V>
void AVLTree<K,V>::clear() {
    destruct(head);
}

template<class K, class V>
V& AVLTree<K,V>::insert(K& key, V& val) {
    bool exit = false;
    Node<K,V>* temp = head;
    if (!head) {
        head = new Node<K, V>(key, val);
        return head->second;
    }
    while (!exit) {
        if (key < temp->first) {
            exit = !temp->left;
            if (exit) {
                temp->left = new Node<K, V>(key, val);
                temp->left->parent = temp;
            }
            temp = (temp->left) ? temp->left : temp;
        }
        else if (key > temp->first) {
            exit = !temp->right;
            if (exit) {
                temp->right = new Node<K, V>(key, val);
                temp->right->parent = temp;
            }
            temp = (temp->right) ? temp->right : temp;
        }
        else
            return temp->second;
    }
    balance(temp);
    return temp->second;
}

template<class K, class V>
void AVLTree<K,V>::remove(K& key) {
    replace(find(key));
}

template<class K, class V>
Node<K,V>* AVLTree<K,V>::find(K& key) {
    return look(key, head);
}

template<class K, class V>
ostream& operator<<(ostream& fout, const AVLTree<K,V>& tree) {
    tree.out(fout, tree.head, 0);
    return fout;
}

template<class K, class V>
void AVLTree<K,V>::copy(Node<K,V>* node, Node<K,V>* other) {
    if (!node && other)
        node = new Node<K, V>(other->first, other->second);
    if (other->left) {
        node->left = new Node<K, V>(other->left->first, other->left->second);
        node->left->parent = node;
        copy(node->left,other->left);
    }
    if (other->right) {
        node->right = new Node<K, V>(other->right->first, other->right->second);
        node->right->parent = node;
        copy(node->right,other->right);
    }
}

template<class K, class V>
void AVLTree<K,V>::destruct(Node<K,V>* node) {
    if (!node)
        return;
    destruct(node->left);
    destruct(node->right);
    delete node;
}

template<class K, class V>
void AVLTree<K,V>::balance(Node<K,V>* val) {
    if (!val)
        return;
    int left = height(val->left);
    int right = height(val->right);
    if (abs(left - right) < 2)
        balance(val->parent);
    else if (left - right == 2) {
        if (height(val->left->left) > height(val->left->right))
            LL(val);
        else
            LR(val);
    }
    else if (right - left == 2) {
        if (height(val->right->right) > height(val->right->left))
            RR(val);
        else
            RL(val);
    }
}

template<class K, class V>
void AVLTree<K,V>::LL(Node<K,V>* val) {
    Node<K,V>* par = val->parent;

    bool isLeft;

    if (par)
        isLeft = par->left == val;

    Node<K,V>* k1 = val->left;
    Node<K,V>* k3 = k1->right;

    k1->right = val;
    val->parent = k1;
    val->left = k3;
    if (k3)
        k3->parent = val;

    if (par) {
        if (isLeft)
            par->left = k1;
        else
            par->right = k1;
        k1->parent = par;
    }
    else {
        head = k1;
        k1->parent = nullptr;
    }
}

template<class K, class V>
void AVLTree<K,V>::LR(Node<K,V>* val) {
    RR(val->left);
    LL(val);
}

template<class K, class V>
void AVLTree<K,V>::RR(Node<K,V>* val) {
    Node<K,V>* par = val->parent;

    bool isLeft;

    if (par)
        isLeft = par->left == val;

    Node<K,V>* k1 = val->right;
    Node<K,V>* k3 = k1->left;

    k1->left = val;
    val->parent = k1;
    val->right = k3;
    if (k3)
        k3->parent = val;

    if (par) {
        if (isLeft)
            par->left = k1;
        else
            par->right = k1;
        k1->parent = par;
    }
    else {
        head = k1;
        k1->parent = nullptr;
    }
}

template<class K, class V>
void AVLTree<K,V>::RL(Node<K,V>* val) {
    LL(val->right);
    RR(val);
}

template<class K, class V>
int AVLTree<K,V>::height(Node<K,V>* val) {
    if (!val)
        return 0;
    return 1 + max(height(val->left),height(val->right));
}

template<class K, class V>
void AVLTree<K,V>::replace(Node<K,V>* val) {
    Node<K, V> *par = val->parent;
    Node<K, V> *cur = val;
    bool isLeft;

    if (val->parent)
        isLeft = val->parent->left == val;

    if (!val->left || !val->right) {
        if (val->left)
            val = val->left;
        else if (val->right)
            val = val->right;
        else {
            if (isLeft)
                par->left = nullptr;
            else
                par->right = nullptr;
            delete val;
            balance(par);
            return;
        }

        if (isLeft) {
            par->left = val;
            val->parent = par;
        }
        else {
            par->right = val;
            val->parent = par;
        }

        balance(val);
        delete cur;
        return;
    }

    if (isLeft) {
        while (val->right) {
            val = val->right;
        }
        val->parent->right = val->left;
        if (val->left)
            val->left->parent = val->parent;
    } else {
        while (val->left) {
            val = val->left;
        }
        val->parent->left = val->right;
        if (val->right)
            val->right->parent = val->parent;
    }
    if (par) {
        if (isLeft)
            par->left = val;
        else
            par->right = val;
        val->parent = par;
    }
    else {
        head = val;
        val->parent = nullptr;
    }
    val->left = cur->left;
    val->right = cur->right;
    if (cur->left)
        cur->left->parent = val;
    if (cur->right)
        cur->right->parent = val;
    balance(val);
    delete cur;
}

template<class K, class V>
Node<K,V>* AVLTree<K,V>::look(K& key, Node<K,V>* val) {
    if (!val || key == val->first)
        return val;
    Node<K,V>* temp = look(key, val->left);
    if (!temp)
        temp = look(key, val->right);
    return temp;
}

template<class K, class V>
void AVLTree<K,V>::out(ostream& fout, Node<K,V>* itr, int space) const {
    if (!itr)
        return;

    out(fout, itr->right, space+2);

    fout << endl;

    for (int i = 0; i < space; i++)
        cout << " ";
    cout << itr->first << "\n";

    out(fout, itr->left, space+2);
}

#endif //INC_21F_SRCH_NGN_CRY1IS_AVLTREE_H
