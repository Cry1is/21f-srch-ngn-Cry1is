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
    int height;
    Node<K,V>* parent,* left,* right;

    Node(K& first, V& second) {
        this->first = first;
        this->second = second;
        height = 0;
        parent = left = right = nullptr;
    }

    void setLeft(Node<K,V>* left) {
        this->left = left;
        if (left) {
            left->parent = this;
            this->height = max(this->height, left->height + 1);
        }
    }

    void setRight(Node<K,V>* right) {
        this->right = right;
        if (right) {
            right->parent = this;
            this->height = max(this->height, right->height + 1);
        }
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
            if (exit)
                temp->setLeft(new Node<K, V>(key, val));
            temp = (temp->left) ? temp->left : temp;
        }
        else if (key > temp->first) {
            exit = !temp->right;
            if (exit)
                temp->setRight(new Node<K, V>(key, val));
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
        node->setLeft(new Node<K, V>(other->left->first, other->left->second));
        copy(node->left,other->left);
    }
    if (other->right) {
        node->setRight(new Node<K, V>(other->right->first, other->right->second));
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

    k1->setRight(val);
    val->setLeft(k3);

    if (par) {
        if (isLeft)
            par->setLeft(k1);
        else
            par->setRight(k1);
    }
    else {
        head = k1;
        k1->parent = nullptr;
        k1->height = max(height(k1->left), height(k1->right));
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

    k1->setLeft(val);
    val->setRight(k3);

    if (par) {
        if (isLeft)
            par->setLeft(k1);
        else
            par->setRight(k1);
    }
    else {
        head = k1;
        k1->parent = nullptr;
        k1->height = max(height(k1->left), height(k1->right));
    }
}

template<class K, class V>
void AVLTree<K,V>::RL(Node<K,V>* val) {
    LL(val->right);
    RR(val);
}

template<class K, class V>
int AVLTree<K,V>::height(Node<K,V>* val) {
    return (val) ? val->height : 0;
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

        if (isLeft)
            par->setLeft(val);
        else
            par->setRight(val);

        balance(val);
        delete cur;
        return;
    }

    if (isLeft) {
        while (val->right) {
            val = val->right;
        }
        val->parent->setRight(val->left);
    } else {
        while (val->left) {
            val = val->left;
        }
        val->parent->setLeft(val->right);
    }
    if (par) {
        if (isLeft)
            par->setLeft(val);
        else
            par->setRight(val);
    }
    else {
        head = val;
        val->height = 0;
        val->parent = nullptr;
        val->updateHeight(val);
    }
    val->setLeft(cur->left);
    val->setRight(cur->right);
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
