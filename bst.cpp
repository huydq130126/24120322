#include <iostream>
using namespace std;


struct NODE{
    int key;
    NODE* p_left;
    NODE* p_right;
};
// Ham tim kiem node
NODE* Search(NODE* pRoot, int x){
    // neu cay rong thi tra ve null
    if (!pRoot){
        return nullptr;
    }
    // neu node hien tai la node can tim thi tra ve node do
    if(pRoot->key == x){
        return pRoot;
    }
    // neu x < gia tri cua node hien tai thi ta tim o cay ben trai
    if (x < pRoot->key){
        return Search(pRoot->p_left, x);
    }
    // neu lon hon thi ta tim o phia ben phai
    return Search(pRoot->p_right, x);
}
//Ham chen node
void Insert(NODE* &pRoot, int x){
    // neu cay rong thi ta them node moi
    if(!pRoot){
        // them node moi
        pRoot = new NODE;
        pRoot->key = x;
        pRoot->p_left = nullptr;
        pRoot->p_right = nullptr;
    }
    // neu x < node dang xet thi ta insert vao cay ben trai
    if (x < pRoot->key){
        Insert(pRoot->p_left,x);
    }
    // neu lon hon thi insert vao cay ben phai
    else if ( x > pRoot->key){
        Insert(pRoot->p_right,x);
    }
    // Neu x == pRoot->key thi khong them de tranh gay loi

}
//Ham xoa node
void Remove(NODE* &pRoot, int x){
    //neu cay rong thi khong xoa gi
    if(!pRoot){
        return;
    }
    // neu x be hon node hien tai thi tim o node ben trai
    if (x < pRoot->key){
        Remove(pRoot->p_left, x);
    }
    // neu x lon hon node hien tai thi tim o node ben phai
    else if(x > pRoot->key){
        Remove(pRoot->p_right, x);
    }
    // neu da tim thay node can xoa
    else{
        // neu node khong co node la ben trai va ben phai
        if (!pRoot->p_left && !pRoot->p_right){
            // xoa node
            delete pRoot;
            // dua con tro ve null
            pRoot = nullptr;
        }
        // neu node chi co cay con ben trai
        else if (!pRoot->p_right){
            NODE* tmp = pRoot;
            pRoot = pRoot->p_left;
            delete tmp;
        }
        // neu chi co cay con ben phai
        else if (!pRoot->p_left){
            NODE* tmp = pRoot ;
            pRoot = pRoot->p_right;
            delete tmp;
        }
        // truong hop node co cay con trai phai
        else{
            // tim node trai nhat ben cay con phai
            NODE* root = pRoot;
            NODE* child = pRoot->p_right;
            while(child->p_left){
                root = child;
                child = child ->p_left;
            }
            // Gan gia tri node child cho node pRoot
            pRoot->key = child ->key;
            // Neu child la con truc tiep cua pRoot
            if (root == pRoot){
                Remove(root->p_right,child ->key);
            }
            // neu child nam sau hon trong cay ben phai
            else{
                Remove(root->p_left, child->key);
            }
        }

    }
}
//Ham tao cay 
NODE* createTree(int a[], int n ){
    // tao node goc
    NODE* pRoot = nullptr;
    // vong lap de chen node vao cay
    for(int i = 0; i<n;i++){
        Insert(pRoot,a[i]);
    }
    return pRoot;
}
// Ham xoa cay
void removeTree(NODE* &pRoot){
    // neu cay rong thi dung
    if(!pRoot){
        return;
    }
    // xoa cay ben trai
    removeTree(pRoot->p_left);
    // xoa cay ben phai
    removeTree(pRoot->p_right);
    // xoa node goc
    delete pRoot;
    pRoot = nullptr;
}
// Ham dem chieu cao cay
int Height(NODE* pRoot){
    // neu cay rong thi tra ve -1
    if (!pRoot){
        return -1;
    }
    // tinh chieu cao cay ben trai
    int left = Height(pRoot->p_left);
    // tinh chieu cao cay ben phai
    int right = Height(pRoot->p_right);
    // tra ve chieu cao cua cay
    return 1 + max(left, right);
}
// Ham dem cac node be hon x
int countLess(NODE* pRoot, int x){
    // neu cay rong thi tra ve 0
    if (!pRoot){
        return 0;
    }
    // neu node goc nho hon x thi phai so sanh cac node o hai cay con trai phai
    if (pRoot->key < x){
        return 1 + countLess(pRoot->p_left,x) + countLess(pRoot->p_right,x);
    }
    // neu node goc lon hon x thi chi can so sanh voi cac node o cay con trai
    else{
        return countLess(pRoot->p_left,x);
    }
}
// Ham dem cac node lon hon x
int countGreater(NODE* pRoot, int x){
    // neu cay rong thi tra ve 0
    if (!pRoot){
        return 0;
    }
    // neu node goc lon hon x thi phai so sanh cac node o hai cay con trai phai
    if(pRoot->key > x){
        return 1 + countGreater(pRoot->p_left,x) + countGreater(pRoot->p_right,x);
    }
    // neu node goc nho hon x thi chi can so sanh voi cac node o cay con phai
    else {
        return countGreater(pRoot->p_right, x);
    }
}
// Ham kiem tra cay co phai BST khong
bool subIsBST(NODE* pRoot, int min, int max){
    // neu cay rong hoac duyet xong nhanh thi tra ve true
    if (!pRoot){
        return true;
    }
    // neu node goc nho hon gia tri min hoac lon hon gia tri max thi tra ve false
    if (pRoot->key <= min || pRoot ->key >= max){
        return false;
    }
    // tat ca cac node ben cay con trai deu nho hon pRoot va cac node ben cay con phai deu lon hon
    return subIsBST(pRoot->p_left,min,pRoot->key) && subIsBST(pRoot->p_right, pRoot->key, max);
    


}
// goi ham phu de kiem tra voi khoang gia tri lon nhat tu INT_MIN toi INT_MAX
bool isBST(NODE* pRoot){
    return subIsBST(pRoot, INT_MIN, INT_MAX);
}
// Ham kiem tra cay bst co day du 
bool isFullBST(NODE* pRoot){
    // neu cay rong hoac da duyet xong thi tra ve true
    if (!pRoot){
        return true;
    }
    // neu la mot node la thi tra ve true
    if (!pRoot->p_right && !pRoot->p_left){
        return true;
    }
    // neu co day du hai node con trai va phai thi return true
    if (pRoot->p_left && pRoot->p_right){
        return isFullBST(pRoot->p_left) && isFullBST(pRoot->p_right);
    }
    return false;
}