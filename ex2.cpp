#include <iostream>
using namespace std;

// Ham de quy de tinh giai thua
int factorial(int n) {
	if (n == 0 || n == 1) {  // 0! = 1; 1! = 1 => return 1
		return 1;
	}
	return n * factorial(n - 1); // n! = n * (n - 1)!
}

int main() {
	int n;
	cin >> n; // Nhap n!
	if (n < 0) {
		cout << "Math Error!";
		return 0;
	}
	int kq = factorial(n);
	cout << kq << endl;
	return 0;
}