#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;
//struct Company gom ten cong ty, ma so thue, dia chi cong ty
struct Company {
    string name;
    string profit_tax;
    string address;
};
// ham doc danh sach cong ty tu file
vector<Company> readCompanyList(string file_name){
    vector <Company> comp; // tao mot vector comp kieu company 
    ifstream input_file(file_name); //doc file
    string l; // tao chuoi string l 
    while (getline(input_file,l)){ // doc tung dong cho den khi het file
        stringstream ss(l); // dung stringstream de tach cac truong trong dong
        Company c; // Tao bien c kieu Company de luu thong tin tung cong ty
        getline(ss,c.name,'|'); // doc ten cong ty toi dau gach
        getline(ss,c.profit_tax,'|'); // doc ma so thue toi dau gach
        getline(ss,c.address); // doc dia chi den het dong
        comp.push_back(c); // them thong tin cua cong ty vua doc vao vector c
    };
    return comp; // tra ve vector chua danh sach cac cong ty
}
// ham chuyen ten cong ty tu string sang dang so nguyen
long long hashString(string company_name){
    const int p = 31;
    const int m = 2000;
    string tmp_string;
    if (company_name.size() > 20){ // neu ten dai hon 20 ki tu thi chi lay 20 ki tu cuoi
        tmp_string = company_name.substr(company_name.size() - 20);
    }else{ // neu ten be hon hoac bang 20 ki tu thi lay ten do
        tmp_string = company_name;
    }
    long long hash = 0; // luu gia tri bam
    long long pow = 1; // luy thua cua p
    for (int i =0; i< tmp_string.size();i++){
        hash = (hash + (long long)(tmp_string[i] * pow))% m; // tinh gia tri bam
        pow = (p * pow) % m;
    }
    return hash; // tra ve gia tri bam
}
// struct HashTable dung cho phuong phap Linear Probing
struct HashTable {
    vector<Company> table; // vector table kieu company de luu cac cong ty
    vector<bool> occupied; // vector kieu bool de danh dau o nao da bi chiem
    int size;
    HashTable(int size2){
        size = size2; // gan kich thuoc
        table.resize(size2); // khoi tao vector table
        occupied.resize(size2, false); // khoi tao vector occupied
    }
};
// Ham tao bang bam tu danh sach cac cong ty                                                                                                    
HashTable* createHashTable(vector<Company> list_company){
    int size = 2000; // kich thuoc cua bang bam
    HashTable *hashtable = new HashTable(size); // tao bang bam moi bang pointer
    for (int i =0; i < list_company.size();i++){
        long long hash = hashString(list_company[i].name); // chi so bam
        while(hashtable->occupied[hash]){ // vong lap neu vi tri da bi chiem
            hash = (hash + 1) %size; // Dung phuong phap Linear Probing de tim vi tri
        }
        hashtable->table[hash] = list_company[i]; // Gan cong ty vao vi tri khong bi chiem
        hashtable->occupied[hash] = true; // danh dau o do da bi chiem
    }
    return hashtable; // tra ve bang bam
}
// ham them vao bang bam
void insert(HashTable* hash_table, Company company){
    long long hash = hashString(company.name); // chi so bam
    while (hash_table->occupied[hash]){ // vong lap neu vi tri da bi chiem
        hash = (hash + 1) % (hash_table -> size); //Dung phuong phap Linear Probing de tim vi tri
    }
    hash_table ->table [hash] = company; // Gan cong ty vao vi tri khong bi chiem
    hash_table -> occupied[hash] = true; // danh dau o do da bi chiem
}
// Ham tim kiem trong bang bam
Company* search(HashTable* hash_table, string company_name){
    long long hash = hashString(company_name); // chi so bam
    int begin = hash; // vi tri bat dau bam
    while(hash_table ->occupied[hash]){ // vong lap neu vi tri da bi chiem
        if (hash_table->table[hash].name == company_name){ // kiem tra coi ten co trung khop khong
            return &(hash_table->table[hash]); // neu co thi tra ve con tro  tro toi cong ty
        }
    }
    hash = (hash + 1) % (hash_table ->size); // Dung phuong phap Linear Probing de kiem tra tiep
    if (hash == begin){ // neu vi tri bam quay lai ban dau
        return NULL; // tra ve NULL do k tim duoc cong ty
    }
    return NULL;
}
