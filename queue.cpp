#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

struct NODE {
    int key;
    NODE *p_next;
};
struct Queue {
    NODE *head;
    NODE *tail;
};
// ham tao node tu key
NODE* createNode(int key){
    NODE *p = new NODE();
    p->key = key;
    p->p_next = NULL;
    return p;
}
// ham khoi tao queue
Queue* initializeQueue(){
    Queue * q = new Queue();
    q->head = q->tail =  NULL;
    return q;
}
// ham kiem tra queue co rong khong
bool isEmpty (Queue q){
    return q.head == NULL;
}
// ham enqueue them g
void enqueue(Queue &q, int key){
    NODE * p = createNode(key);
    if (isEmpty(q)){
        q.head = q.tail = p; // neu queue rong, gan head va tail cho node moi
    }
    else {
        q.tail ->p_next = p; // gan node moi vao cuoi queue 
        q.tail = p; // cap nhat tail
    }
    
}
// ham dequeue xoa phan tu dau queue
int dequeue(Queue &q){
    if (isEmpty(q)){
        return -1; // neu queue rong, tra ve -1
    }
    NODE* p = q.head;
	int key = p->key;
	q.head = q.head ->p_next; // cap nhat head sau khi xoa node dau

	if (q.head == NULL) { // neu queue sau khi xoa rong, cap nhat lai head va tail
		q.tail = NULL;
	} 
	delete p; // xoa node
	return key;
}

// ham dem so phan tu cua queue
int size (Queue q){
    if (isEmpty(q)){
        return 0; //neu queue rong, tra ve 0;
    }
    NODE * p = q.head;
    int count = 0;
    while (p!=NULL){ // duyet qua tat ca cac node
        p = p->p_next; // chuyen qua node tiep theo
        count ++; // tang bien count 
    }
    return count; // tra ve count
}
// ham in queue ra file output
void PrintQueue(Queue q, ostream &output_file ) {
	if (isEmpty(q)) {
        output_file << "EMPTY" << endl; // neu queue rong, in EMPTY
		return;
	}
	NODE* p = q.head;
	while (p != NULL) {
		output_file << p->key <<" ";
		p = p->p_next;
	}
	output_file << endl;
}
int main(){
    ifstream file_in ("input.txt"); // mo file doc
    ofstream file_out ("output.txt"); // mo file ghi 
    if(!file_in.is_open() || !file_out.is_open()){ // neu khong mo duoc thi tra ve 1
        return 1;
    }

    Queue *q = NULL; // khoi tao con tro queue
    string line;
    while (getline(file_in, line)) {  // doc tung dong trong file
        stringstream ss(line); // chuyen dong thanh stream
        string word;
        ss >> word; // doc cac tu

        if (word == "init") { // khoi tao stack khi nhap vao init 
            q = initializeQueue();// khoi tao queue moi
            PrintQueue(*q, file_out); // in queue sau khi khoi tao
        } 
        else if (word == "enqueue") { // them phan tu vao cuoi queue khi nhap enqueue
            int num;
            ss >> num; // doc gia tri can enqueue
            if (q != NULL) {
                enqueue(*q, num); // enqueue
                PrintQueue(*q, file_out); // in queue sau khi enqueue
            }
        } 
        else if (word == "dequeue") { // xoa phan tu tren cung neu nhap vao dequeue
            if (q != NULL) {
                dequeue(*q); // dequeue
                PrintQueue(*q, file_out); // in queue sau khi pop
            }
        }
    }
    return 0;

}