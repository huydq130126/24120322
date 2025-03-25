#include <iostream>
using namespace std;
// Ham de quy sinh chuoi nhi phan
void generateBinaryStrings(int n, string str) {
	if (n == 0) {  // dieu kien dung: khi dien du n ki tu
		cout << str << endl; // In ra chuoi ki tu
		return;
	}
	generateBinaryStrings(n - 1, str + "0"); // Goi de quy them "0" vao chuoi
	generateBinaryStrings(n - 1, str + "1"); // Goi de quy them "1" vao chuoi
}

int main() {
	int n; cin >> n; // Nhap do dai chuoi nhi phan
	generateBinaryStrings(n, ""); // Goi ham de quy bat dau voi chuoi rong 
	return 0;
}