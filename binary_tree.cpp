#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct NODE {
    int key;
    NODE* p_left;
    NODE* p_right;
};

// Ham tao node moi
NODE* createNode(int data){
    NODE* p = new NODE;
    p->key = data;
    p->p_left = nullptr;
    p->p_right = nullptr;
    return p;
}
// Pre_order
vector<int> NLR(NODE* pRoot){
    // vector luu ket qua
    vector<int> p;
    // neu cay khong rong
    if (pRoot){
        // doc node goc cua cay
        p.push_back(pRoot->key);
        // doc node ben trai
        vector<int> left = NLR(pRoot->p_left);
        // doc node ben phai
        vector<int> right = NLR(pRoot->p_right);
        // Day cac cay con ben trai vao vector luu ket qua
        p.insert(p.end(), left.begin(), left.end());
        // Day cac cay con ben phai vao vector luu ket qua
        p.insert(p.end(), right.begin(), right.end());
    }
    return p;
}
//In-order
vector<int> LNR(NODE* pRoot){
    // vector luu ket qua
    vector<int> p;
    // neu cay khong rong
    if (pRoot){
        // doc node ben trai
        vector<int> left = LNR(pRoot->p_left);
        // day cac cay con ben trai vao vector luu ket qua
        p.insert(p.end(), left.begin(), left.end());
        // day node goc vao vector luu ket qua
        p.push_back(pRoot->key);
        // doc node ben phai
        vector<int> right = LNR(pRoot->p_right);
        // day cac cay con ben phai vao vector luu ket qua
        p.insert(p.end(), right.begin(), right.end());
    }
    return p;
}
//Post-order
vector<int> LRN(NODE* pRoot){
    // vector luu ket qua
    vector<int> p;
    // neu cay khong rong
    if (pRoot){
        // doc node ben trai
        vector<int> left = LRN(pRoot->p_left);
        // day cac cay con ben trai vao vector luu ket qua
        p.insert(p.end(), left.begin(), left.end());
        // doc node ben phai
        vector<int> right = LRN(pRoot->p_right);
        // day cac cay con ben phai vao vector luu ket qua
        p.insert(p.end(), right.begin(), right.end());
        // day node goc vao vector luu ket qua
        p.push_back(pRoot->key);
    }
    return p;
}
//BFS
vector<vector<int>> LevelOrder(NODE* pRoot){
    // tao mot vector hai tang de luu ket qua
    vector<vector<int>> p;
    // neu cay rong tra ve ket qua rong
    if (!pRoot){
        return p;
    }
    // tao hang doi queue
    queue<NODE*> q;
    // day node goc vao hang doi
    q.push(pRoot);
    //lap lai hang doi neu van con phan tu
    while(!q.empty()){
        // tao mot vector de luu cac node cung hang
        vector<int> tmp;
        int n = q.size();
        for(int i = 0; i<n;i++){
            // lay node dau
            NODE* pNode = q.front();
            // bo ra khoi hang doi
            q.pop();
            // bo vao vector tmp 
            tmp.push_back(pNode->key);
            // Neu co node ben trai hoac ben phai thi dua vao hang doi de duyet o tang ke tiep
            if(pNode->p_left){
                q.push(pNode->p_left);
            }
            if(pNode->p_right){
                q.push(pNode->p_right);
            }
        }
        //luu cac node o cung tang vao vector ket qua
        p.push_back(tmp);
    }
    return p;
}
// Ham dem node
int countNode(NODE* pRoot){
    // neu cay rong thi tra ve ket qua dem la 0
    if(!pRoot){
        return 0;
    }
    // neu cay khong rong thi bien dem = node goc + tong node ben trai + tong node ben phai
    int count = 1 + countNode(pRoot->p_left) + countNode(pRoot ->p_right);
    // tra ve so luong node da dem
    return count;
}
// Ham tong node
int sumNode(NODE* pRoot){
    // neu cay rong thi tong = 0
    if (!pRoot){
        return 0;
    }
    // neu cay khong rong thi tong = gia tri node goc + tong gia tri node trai + tong gia tri node phai
    int sum = pRoot->key + sumNode(pRoot->p_left) + sumNode(pRoot->p_right);
    // tra ve tong
    return sum;
}
// Ham dem chieu cao cua cay
int Height(NODE* pRoot){
    // neu ham rong thi tra ve -1 
    if (!pRoot){
        return -1;
    }
    // tinh chieu cao cay con ben trai
    int left = Height(pRoot->p_left);
    // tinh chieu cao cay con ben phai 
    int right = Height(pRoot->p_right);
    // chieu cao = 1 + max(trai, phai)
    return 1 + max(left, right);
}
//Ham dem chieu cao cua node
int heightNode(NODE* pRoot, int value){
    // neu ham rong thi tra ve -1 
    if (!pRoot) {
        return -1;
    }
    // tinh chieu cao cua node theo yeu cau
    if (pRoot->key == value){
        return Height(pRoot);
    }
    // tim node trong cay ben trai
    int left = heightNode(pRoot->p_left, value);
    // neu node da duoc tim o ben trai thi ta dung va tra ve height
    if (left!= -1){
        return left;
    }
    // neu node can tim khong nam trong cay ben trai thi ta tiep tuc tim cay ben phai
    return heightNode(pRoot->p_right, value);
}
// Ham dem bac
int Level(NODE* pRoot, NODE* p){
    // neu cay rong thi tra ve -1
    if(!pRoot){
        return -1;
    }
    // neu p la node goc thi level 0
    if (pRoot == p ){
        return 0;
    }
    // tim node ben trai va tinh level
    int left = Level(pRoot->p_left, p);
    // neu thay node thi dung ham va tra ve level + 1
    if (left != -1){
        return left + 1;
    }
    // khong thay node thi tiep tuc tim ben phai
    int right = Level(pRoot->p_right, p);
    if (right != -1){
        return right + 1;
    }
    // neu khong tim thay node thi tra ve -1
    return -1;
}
// Ham dem node la
int countLeaf(NODE* pRoot){
    // neu cay rong thi tra ve 0
    if(!pRoot){
        return 0;
    }
    // neu node hien tai la node la thi tra ve 1
    if (!pRoot->p_left && !pRoot->p_right){
        return 1;
    }
    // goi de quy dem cac node la con lai
    return countLeaf(pRoot->p_left) + countLeaf(pRoot->p_right);
}