#include <iostream>
using namespace std;


//Ham tinh so fibonacci thu n bang de quy
int fibonacci(int n) {
	if (n == 0) return 0;  // Tra vê 0 neu n =  0, do F(0) = 0;
	if (n == 1) return 1;  // Tra ve 1 neu n = 1, do F(1) =1;
	return fibonacci(n - 1) + fibonacci(n - 2); // do F(n) = F(n-1) + F(n-2)
}

int main() {
	int n; cin >> n; // Nhap so luong so fibonacci can in
	for (int i = 0; i < n; i++) { // Duyet n phan tu de in ra mang fibonacci
		cout << fibonacci(i) << " ";
	}
	return 0;
}