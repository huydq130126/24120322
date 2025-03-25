	#include <iostream>
	using namespace std;

	// Ham kiem tra xem mang da duoc sap xep hay chua, su dung de quy
	bool isSorted(int arr[], int n) {
		// Neu chi con 1 hoac 0 phan tu => mang da duoc sap xep
		if (n == 1 || n == 0) { 
			return true;
		}
		// Neu phan tu thu nhat lon hon phan tu thu hai => mang chua duoc sap xep
		if (arr[0] > arr[1]) {
			return false;
		}
		// Goi de quy ham isSorted de kiem tra phan con lai cua mang
		return isSorted(arr + 1, n - 1);
	}

	int main() {
		int arr[] = { 1,2,3,4,5 }; // Mang mau 
		int n = sizeof(arr) / sizeof(arr[0]); // So luong phan tu
		if (isSorted(arr, n)) {
			cout << "The array is sorted." << endl;
		}
		else {
			cout << "The array is NOT sorted." << endl;
		}
		return 0;
	}