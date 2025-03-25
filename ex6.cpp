#include <iostream>
#include <vector>
using namespace std;

int solutions = 0; //Khoi tao bien dem so cach dat quan hau
// Ham kiem tra xem quan hau co the dat o vi tri (row,col)
bool isSafe(vector<vector<int>>& board, int row, int col, int N) {
	for (int i = 0; i < row; i++) {
		if (board[i][col] == 1) { // Kiem tra cot thang
			return false;
		}
		if (col - (row - i) >= 0 && board[i][col - (row - i)] == 1) {
			return false; // Kiem tra duong cheo trai 
		}
		if (col + (row - i) < N && board[i][col + (row - i)] == 1) {
			return false; // Kiem tra duong cheo phai 
		}
	}
	return true; 
} 
//Ham de quy dung de dat hau
void solveNQueens(vector<vector<int>>& board, int row, int N) {
	if (row == N) { // Neu tim duoc cach dat hau => tang solutions
		solutions++; 
		return;
	}
	for (int col = 0; col < N; col++) {
		if (isSafe(board, row, col, N)) {
			board[row][col] = 1; // Dat hau
			solveNQueens(board, row + 1, N); // goi de quy de giai hang tiep theo
			board[row][col] =0; // Quay lui neu gap sai xot, xoa quan hau
		}
	}
}

int main() {
	int n; // Kich thuoc ban co
	cout << "Nhap kich thuoc cua ban co (so cot hoac hang) :  ";
	cin >> n;
	vector<vector<int>>board(n, vector<int>(n, 0));
	solveNQueens(board, 0, n);
	cout << solutions << endl;
	return 0;
}