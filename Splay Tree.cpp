
#include <iostream>
#include <bits/stdc++.h>
using namespace std;
#define A 1000000001

struct node {
    long long key;
    node* left;
    node* right;
    node* parent;
};

struct splayTree {
    node* root = nullptr;
    long long s = 0;

    node* newNode(long long key) {
        node* tmp = new node;
        tmp->key = key;
        tmp->left = tmp->right = tmp->parent = nullptr;
        return tmp;
    }

    void rightRotate(node* x) {
        cout << "rightRotate" << endl;
        node* y = x->left;
        x->left = y->right;
        y->right = x;
        if (x->parent) {
            if (x == x->parent->left) {
                x->parent->left = y;
                y->parent = x->parent;

            } else {
                x->parent->right = y;
                y->parent = x->parent;
            }
        } else {
            root = y;
            y->parent = nullptr;
        }
        x->parent = y;
    }

    void leftRotate(node* x) {
        if (x != root) { }
        node* y = x->right;
        x->right = y->left;
        y->left = x;
        if (x->parent) {
            if (x == x->parent->left) {
                x->parent->left = y;
                y->parent = x->parent;
            } else {
                x->parent->right = y;
                y->parent = x->parent;
            }
        } else {
            root = y;
            y->parent = nullptr;
        }
        x->parent = y;
    }

    node* splay(node* x, long long key) {
        cout << "splay" << endl;
        while (x->parent != nullptr) {
            if (x->parent->parent == nullptr) {
                if (x == x->parent->left) {
                    cout << "zig" << endl;
                    rightRotate(x->parent); //zig
                } else {
                    cout << "zag" << endl;
                    cout << "x->parent3 " << x->parent->key << endl;
                    leftRotate(x->parent); //zag
                }
            }
            else if (x == x->parent->left and x->parent == x->parent->parent->left) { //zig-zig
                cout << "zig-zig" << endl;
                rightRotate(x->parent->parent);
                rightRotate(x->parent);
            } 
            else if (x == x->parent->right and x->parent == x->parent->parent->right) { //zag-zag
                cout << "zag-zag" << endl;
                leftRotate(x->parent->parent);
                leftRotate(x->parent);
            }
            else if (x == x->parent->right and x->parent == x->parent->parent->left) { //zig-zag
                cout << "zig-zag" << endl;
                leftRotate(x->parent);
                rightRotate(x->parent);
            }
            else if (x == x->parent->left and x->parent == x->parent->parent->right) { //zag-zig
                cout << "zag-zig" << endl;
                cout << "x->parent1 " << x->parent->key << endl;
                rightRotate(x->parent);
                cout << "x->parent2 " << x->parent->key << endl;
                leftRotate(x->parent);
            }
            else { 
                cout << "?" << endl;
                break; 
            }
        }
        return root;
    }

    void insert(long long _key) {
        cout << "insert" << endl;
        long long key; 
        key = fooMod(_key);
        
        node* temp = newNode(key);
        if (root) { 
            node* tmp_root = root;
            cout << "Root is " << tmp_root->key << endl;

            while (tmp_root) {
                if (tmp_root->key > key) {
                    if (tmp_root->left) {
                        cout << "1 -" << tmp_root->key << endl;
                        cout << "tmp_root->left->key -" << tmp_root->left->key << endl;
                        tmp_root = tmp_root->left;
                    } else {
                        cout << "2 -" << tmp_root->key << endl;
                        tmp_root->left = temp;
                        temp->parent = tmp_root;
                        root = splay(temp, key);
                        break;
                    }
                }
                else if (tmp_root->key < key) {
                    if (tmp_root->right) {
                        cout << "3 -" << tmp_root->key << endl;
                        tmp_root = tmp_root->right;
                    } else {
                        cout << "4 -" << tmp_root->key << endl;
                        tmp_root->right = temp;
                        temp->parent = tmp_root;
                        root = splay(temp, key);
                        break;    
                    }
                } else { break; }
            }
        } else { root = temp; }
    }

    void printInorder(node* node) 
    {
        if (node == NULL)
            return;
        printInorder(node->left);
        cout << node->key << " ";
        printInorder(node->right);
    }

    node* findNode (long long _key) {
        long long key; 
        key = fooMod(_key);

        if (!root) { return nullptr; }
        node* temp_root = root;

        while (temp_root) {
            if (temp_root->key == key) {
                this->splay(temp_root, key);
                return temp_root;
            }
            else if (temp_root->key > key) {
                if (temp_root->left) { temp_root = temp_root->left; }
                else {
                    this->splay(temp_root, key); 
                    return nullptr; 
                }
            }
            else if (temp_root->key < key) {
                if (temp_root->right) { temp_root = temp_root->right; }
                else {
                    this->splay(temp_root, key); 
                    return nullptr;
                }                
            }
        } 
        return nullptr;
    }

    void delNode (long long _key) {
        long long key; 
        key = fooMod(_key);
        
        node* temp = this->findNode(_key);
        if (temp == nullptr) { return; }

        if (temp->left and temp->right) {
            node* new_node = temp->left;
            while (new_node) {
                if (new_node->right) { new_node = new_node->right; }
                else { break; }
            }
            if (new_node->left) { 
                if (new_node->parent != temp) { 
                    new_node->parent->right = new_node->left; 
                    new_node->left->parent = new_node->parent;
                } else { 
                    temp->left = new_node->left;
                    new_node->left->parent = temp; 
                }
            } else { 
                if (new_node->parent != temp) { 
                    new_node->parent->right = nullptr; 
                } else { temp->left = nullptr; }
            }
            temp->key = new_node->key;
            delete new_node;
            return;
        }

        else if (temp->left or temp->right) {
            node* new_node = nullptr; 
            if (temp->left) { new_node = temp->left; }
            else { new_node = temp->right; }

            if (temp->parent) {
                if (temp == temp->parent->left) {
                    temp->parent->left = new_node;
                    new_node->parent = temp->parent->left;
                } else {
                    temp->parent->right = new_node;
                    new_node->parent = temp->parent->right;
                }
            } 

            if (root == temp) {
                new_node->parent = nullptr;
                delete temp; 
                root = new_node;
            }
        }  

        else {
            if (temp->parent) {
                if (temp == temp->parent->left) { temp->parent->left = nullptr; }
                else if (temp == temp->parent->right) { temp->parent->right = nullptr; }
            }
            delete temp; 
            root = nullptr; 
        }
    }

    long long fooMod(long long x) {
        long long f;
        f = ((x % A) + (this->s % A)) % A;
        return f;
    }

    void searchNode(node* node, long long l, long long r) {
        if (!node) { return; }
        if (node->key >= l and node->key <= r) { 
            this->s += node->key;
            if (node->left and node->left->key >= l and node->left->key <= r) { searchNode(node->left, l, r); }
            if (node->right and node->right->key >= l and node->right->key <= r) { searchNode(node->right, l, r); }
        } else {
            if (node->left) { searchNode(node->left, l, r); }
            if (node->right) { searchNode(node->right, l, r); }
        }
    }

    void findSum(long long l, long long r) {
        if (!root) { return; }
        long long L = fooMod(l);
        long long R = fooMod(r);
        this->s = 0;
        searchNode(root, L, R);
        cout << this->s << endl;
    }
};

int main() {
    using namespace std;

    splayTree tree;

    return 0;
}
