#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;




struct  NODE {
    int key;
    NODE * p_next;
};

struct Stack {
    NODE * top;
};
// ham kiem tra stack rong hay khong
bool isEmpty (Stack &s){
    return s.top == NULL;
}
// ham khoi tao stack
Stack* InitializeStack(){
    Stack * s = new Stack();
    s->top = NULL; // cho node dau tro den null
    return s;
}   
// ham push phan tu vao stack
void push (Stack &s, int key){
    NODE * p = new NODE();
    p->key = key; 
    p->p_next = s.top;  // lien ket node moi vao dau stack
    s.top = p; // cap nhat node dau stack
}
// ham pop lay phan tu tren cung stack
int pop (Stack &s){
    if (isEmpty(s)){
        return -1; // neu stack rong tra ve -1
    }
    NODE * p = s.top; // lay node dau
    int val = p->key; // luu gia tri node dau
    s.top = s.top->p_next; // cap nhat node dau thanh node tiep theo
    delete p; // xoa node dau
    return val; // tra ve gia tri da pop
}

int size (Stack s){
    if(isEmpty(s)){
        return 0; // neu stack rong thi tra ve 0
    }
    NODE * p = s.top; // lay node dau
    int count = 0; // khoi tao bien count 
    while (p){ // dem node trong stack
        p= p->p_next;
        count ++;
    }
    return count; // tra ve so luong node trong stack
}


// ham dao nguoc stack va in ra
void Reverse (NODE *p, ostream &output_file){
    if (p == NULL){
        return;
    }
    Reverse(p->p_next, output_file); // de quy di qua node tiep theo
    output_file << p->key << " "; // in gia tri cua node hien tai ra file
}

// ham in stack ra file
void printStack (Stack &s,ostream &output_file){
    if (isEmpty(s)){
        output_file << "EMPTY" << endl; // neu stack rong thi in EMPTY
        return;
    }
    NODE * p = s.top;
    Reverse(p,output_file); // in ra stack dao nguoc

    output_file << endl;
}


int main(){

    ifstream file_in ("input.txt"); // mo file doc
    ofstream file_out ("output.txt"); // mo file ghi 
    if(!file_in.is_open() || !file_out.is_open()){ // neu khong mo duoc thi tra ve 1
        return 1;
    }

    Stack *s = NULL; // khoi tao con tro stack
    string line;
    while (getline(file_in, line)) {  // doc tung dong trong file
        stringstream ss(line); // chuyen dong thanh stream
        string word;
        ss >> word; // doc cac tu

        if (word == "init") { // khoi tao stack khi nhap vao init 
            s = InitializeStack();// khoi tao stack s
            printStack(*s, file_out); // in stack sau khi khoi tao
        } 
        else if (word == "push") { // them phan tu vao stack khi nhap push
            int num;
            ss >> num; // doc gia tri can push
            if (s != NULL) {
                push(*s, num); // push 
                printStack(*s, file_out); // in stack sau khi push
            }
        } 
        else if (word == "pop") { // xoa phan tu tren cung neu nhap vao pop 
            if (s != NULL) {
                pop(*s); // pop 
                printStack(*s, file_out); // in stack sau khi pop
            }
        }
    }
    file_in.close();
    file_out.close();
    return 0;

}