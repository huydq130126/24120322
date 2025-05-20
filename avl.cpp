#include <iostream>
using namespace std;

struct NODE{
    int key;
    NODE* p_left;
    NODE* p_right;
    int height;
};
//1. Khoi tao node moi
NODE* createNode(int data){
    NODE* p = new NODE;
    p->key = data;
    p->p_left = p->p_right = nullptr;
    p->height = 0;
    return p;
}

// ham lay chieu cao cua node
int Height(NODE* pRoot){
    if (pRoot != nullptr){
        return pRoot->height;
    }
    else{
        return -1;
    }
}

// Ham cap nhat chieu cao cua node
void updateHeight(NODE* pRoot){
    // neu cay khong rong
    if (pRoot != nullptr) {
        // lay chieu cao cay con ben trai
        int left = Height(pRoot->p_left);
        // lay chieu cao cay con ben phai
        int right = Height(pRoot->p_right);
        // cap nhat lai chieu cao
        pRoot->height = 1 + max(left, right);
    }
}

// Ham tinh chi so can bang
int calBalance(NODE*pRoot){
    // neu cay khong rong
    if (pRoot!= nullptr){
        // tinh chi so can bang
        int balance = Height(pRoot->p_left) - Height(pRoot->p_right);
        return balance;
    }
    else{
        return 0;
    }
}

// Ham quay phai
NODE* rightRotation(NODE* y){
    NODE* x = y->p_left;
    NODE* B = x->p_right;
    x->p_right = y;
    y->p_left = B;
    updateHeight(y);
    updateHeight(x);
    return x;
}

// Ham quay trai
NODE* leftRotation(NODE* x) {
    NODE* y = x->p_right;
    NODE* B = y->p_left;
    y->p_left = x;
    x->p_right = B;
    updateHeight(x);
    updateHeight(y);
    return y;
}

// Ham chen node vao AVL
void Insert(NODE* &pRoot, int x) {
    // neu cay rong thi chen node moi vao cay
    if (!pRoot) {
        pRoot = createNode(x);
        return;
    }
    // neu x < node dang xet thi ta insert vao cay ben trai
    if (x < pRoot->key){
        Insert(pRoot->p_left, x);
    }
    // neu lon hon thi insert vao cay ben phai
    else if (x > pRoot->key){
        Insert(pRoot->p_right, x);
    }
    // Neu x == pRoot->key thi khong them de tranh gay loi
    else{
        return; 
    }
    // cap nhat chieu cao cua node goc
    updateHeight(pRoot);
    // tinh chi so can bang
    int balanceIdx = calBalance(pRoot);

    // Xoay Left Left
    if (balanceIdx > 1 && x < pRoot->p_left->key){
        pRoot = rightRotation(pRoot);
    }
    // Xoay Right Right
    else if (balanceIdx < -1 && x > pRoot->p_right->key){
        pRoot = rightRotation(pRoot);
    }
    // Xoay Left Right
    else if (balanceIdx > 1 && x > pRoot->p_left->key) {
        pRoot->p_left = leftRotation(pRoot->p_left);
        pRoot = rightRotation(pRoot);
    }
    // Xoay Right Left
    else if (balanceIdx < -1 && x < pRoot->p_right->key) {
        pRoot->p_right = rightRotation(pRoot->p_right);
        pRoot = leftRotation(pRoot);
    }
}

// ham xoa node tu cay AVL
void Remove(NODE* &pRoot, int x) {
    // neu cay rong thi khong xoa
    if (!pRoot) return;
    // neu x be hon node hien tai thi tim o node ben trai
    if (x < pRoot->key){
        Remove(pRoot->p_left, x);
    }
    // neu x lon hon node hien tai thi tim o node ben phai
    else if (x > pRoot->key){
        Remove(pRoot->p_right, x);
    }
    // neu da tim thay node can xoa
    else {
        if (!pRoot->p_left || !pRoot->p_right) {
            NODE* tmp;
            if (pRoot->p_left != nullptr) {
            tmp = pRoot->p_left;
            } else {
            tmp = pRoot->p_right;
            }
            delete pRoot;
            pRoot = tmp;
        } else {
            // Tim node trai nhat ben phai
            NODE* root = pRoot;
            NODE* child = pRoot->p_right;
            while (child->p_left) {
                root = child;
                child = child->p_left;
            }
            pRoot->key = child->key;
            // Xoa node
            if (root == pRoot)
                Remove(root->p_right, child->key);
            else
                Remove(root->p_left, child->key);
        }
    }
    // Neu cay rong thi khong can cap nhat gi ca
    if (!pRoot) return;
    // Cap nhat lai chieu cao cua node hien tai
    updateHeight(pRoot);
    // Tinh chi so can bang cua node hien tai
    int balanceIdx = calBalance(pRoot);

    // Xoay Left Left
    if (balanceIdx > 1 && calBalance(pRoot->p_left) >= 0)
        pRoot = rightRotation(pRoot);
    // Xoay Left Right
    else if (balanceIdx > 1 && calBalance(pRoot->p_left) < 0) {
        pRoot->p_left = leftRotation(pRoot->p_left);
        pRoot = rightRotation(pRoot);
    }
    // Xoay Right Right
    else if (balanceIdx < -1 && calBalance(pRoot->p_right) <= 0)
        pRoot = leftRotation(pRoot);
    // Xoay Right Left
    else if (balanceIdx < -1 && calBalance(pRoot->p_right) > 0) {
        pRoot->p_right = rightRotation(pRoot->p_right);
        pRoot = leftRotation(pRoot);
    }
}

// Ham kiem tra cay co phai AVL khong
bool isAVL(NODE* pRoot) {
    //neu cay rong hoac da duyet xong
    if (!pRoot) {
        return true;
    }
    int balanceIdx = calBalance(pRoot);
    if (balanceIdx < -1 || balanceIdx > 1) {
        return false;
    }
    return isAVL(pRoot->p_left) && isAVL(pRoot->p_right);
}