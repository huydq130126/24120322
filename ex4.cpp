#include <iostream>
using namespace std;

// Ham de quy giai bai toan Thap Ha Noi
void towerOfHanoi(int n, char from_rod, char to_rod, char aux_rod) {
	if (n == 1) {
		cout << "Move disk 1 from " << from_rod << " to " << to_rod << endl; // Neu n = 1 thi ta chuyen tu coc nguon sang coc dich 
		return;
	}
	towerOfHanoi(n - 1, from_rod, aux_rod, to_rod);  // Chuyen n - 1 dia tu coc nguon sang coc trung gian
	cout << "Move disk " << n << " from " << from_rod << " to " << to_rod << endl; // Chuyen dia lon nhat tu coc nguon sang coc dich
	towerOfHanoi(n - 1, aux_rod, to_rod, from_rod); // Chuyen n - 1 dia tu coc trung gian sang coc dich

}

int main() {
	cout << "Nhap so luong dia: ";
	int n; cin >> n; // So luong dia
	towerOfHanoi(n, 'A', 'C', 'B');
	return 0;
}