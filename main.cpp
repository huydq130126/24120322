#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <queue>
#include <stack>
using namespace std;

// Chuyen ma tran ke sang danh sach ke
vector<vector<int>> convertMatrixToList(const string& filename){
    ifstream fileIn(filename);
    if (!fileIn.is_open()){
        cerr << "CANNOT OPEN FILE." << endl;
        return {};
    }
    int n; 
    if (!(fileIn >> n)) {
        cerr << "INVALID FILE FORMAT." << endl;
        return {};
    }
    vector<vector<int>> list(n); // Tao danh sach ke voi n dinh
    for (int i = 0; i < n; i++) {
        for (int j = 0, x; j < n; j++) {
            if (!(fileIn >> x)) { // Doc gia tri x tu file, neu khong doc duoc thi bao loi
                cerr << "INVALID FILE FORMAT." << endl;
                return {};
            }
            if (x != 0) list[i].push_back(j);// Neu x khac 0, tuc la co canh tu i den j, them j vao danh sach ke cua i
        }
    }
    return list;
}
// Chuyen danh sach ke sang ma tran ke 
vector<vector<int>> convertListToMatrix(const string& filename){
    ifstream fileIn(filename);
    if(!fileIn.is_open()){
        cout << "CANNOT OPEN FILE" << endl;
        return {};
    }
    int n; fileIn >> n;
    vector<vector<int>> Matrix(n,vector<int>(n,0)); // Tao ma tran ke n x n, khoi tao tat ca bang 0
    string l;
    getline(fileIn,l); // Doc het phan con lai cua dong so dinh
    for (int i = 0; i < n; i++) { // Duyet tung dinh
        getline(fileIn, l);
        istringstream ss(l); // Tao luong de tach cac so trong dong
        int k; int neighbours; // so luong dinh ke, va cac dinh ke
        ss >> k; // Doc so dinh ke cua dinh i
        for (int j = 0; j < k; j++) {
            ss >> neighbours;
            Matrix[i][neighbours] = 1;// Danh dau co canh tu i den neighbours trong ma tran ke
        }
    }
    return Matrix;
}
// Kiem tra do thi co huong khong
bool isDirected (const vector<vector<int>> & adjMatrix){
    int n = adjMatrix.size();
    for (int i = 0; i<n;i++){
        for(int j = 0; j<n;j++){
            // neu co canh chi di mot chieu, do thi la co huong
            if (adjMatrix[i][j] != adjMatrix[j][i]){
                return true;
            }
        }
    }
    return false;
}
// Dem so dinh
int countVertices(const vector<vector<int>>& adjMatrix){
    return adjMatrix.size();
}
// Dem so canh
int countEdges(const vector<vector<int>>& adjMatrix){
    int n = adjMatrix.size();
    int count = 0;
    bool d = isDirected(adjMatrix); // Kiem tra do thi co huong hay khong
    for (int i = 0; i <n ;i ++){
        for (int j =0 ;j <n;j++){
            count += adjMatrix[i][j]; // dem so canh
        }
    }
    if (!d){// Neu la do thi vo huong
        count /= 2; // Moi canh bi dem 2 lan (i->j va j->i), nen chia 2
    }
    return count;
}
// Tim cac dinh co lap
vector<int> getIsolatedVertices(const vector<vector<int>>& adjMatrix){
    int n = adjMatrix.size();
    vector<int> IsolatedVertices;// Tao vector de luu cac dinh co lap
    for (int i = 0; i <n ;i++){
        bool isolated = true; // Mac dinh i la co lap
        for (int j = 0; j <n;j++){
            // Neu co canh tu i den j hoac tu j den i thi i khong co lap
            if (adjMatrix[i][j] == 1 || adjMatrix[j][i] ==1){
                isolated = false; // Dinh i khong co lap va dung
                break;
        }
        if (isolated) {// Neu i van la co lap
            IsolatedVertices.push_back(i); // Them i vao danh sach dinh co lap
        }
    }
    return IsolatedVertices;
    }
}
// Kiem tra do thi day du
bool isCompleteGraph(const vector<vector<int>>& adjMatrix){
    int n = adjMatrix.size();
    for (int i = 0; i<n;i++){
        for (int j = 0; j < n;j++ ){
            if (i != j && adjMatrix[i][j] == 0){
                return false;
            }
        }
    }
    return true;
}

// Kiem tra do thi nhi phan (BFS)
bool isBipartite(const vector<vector<int>>& adjMatrix){
    int n = adjMatrix.size();
    vector<int> color (n,-1); // vector color de to mau cac dinh, -1 la chua to mau
    for (int i = 0; i<n;i++){
        if (color[i] != -1) { // Neu dinh da duoc to mau thi bo qua
            continue;
        }
        queue<int> q; // Tao hang doi de duyet BFS
        q.push(i); color[i] = 0; // To mau dinh i la mau 0
        while(!q.empty()){
            int k = q.front(); q.pop(); // Lay dinh dau hang doi ra xet
            for (int v = 0; v <n ;v++){ // Duyet cac dinh ke voi k
                if(adjMatrix[k][v] == 1){
                    if (color[v] == -1){ // Neu dinh v chua to mau
                        color[v] =  1 - color[k]; // To mau v khac mau k
                        q.push(v); // Dua v vao hang doi de xet tiep
                    } else if(color[k] == color[v]){ // Neu v da to mau va trung mau voi k
                        return false; // Do thi khong la nhi phan
                    }
                }
            }
        }
    }
    return true;
}
// Kiem tra do thi nhi phan day du
bool isCompleteBipartite(const vector<vector<int>>& adjMatrix){
    int n = adjMatrix.size();
    vector<int> color(n,-1);// Vector color de to mau cac dinh, -1 la chua to mau
    vector<int> g[2]; // Hai tap dinh cua do thi nhi phan
    for (int i = 0; i<n;i++){
        if (color[i]!= -1){
            continue;  // Neu dinh da to mau thi bo qua
        }
        queue <int> q;
        q.push(i); 
        color[i] = 0; // To mau dinh i la mau 0
        g[0].push_back(i); // Dua i vao tap 0

        //BFS
        while(!q.empty()){
            int k = q.front(); q.pop();
            for (int v = 0; v < n; v++){
                if (adjMatrix[k][v] == 1){
                    if (color[v] == -1){
                        color[v] = 1 - color[k];
                        g[1].push_back(v);
                        q.push(v);
                    }else if(color[k] == color[v]){
                        return false;
                    }
                }
            }
        }


    }
    
    // Kiem tra moi dinh tap 0 phai noi voi moi dinh tap 1
    for (int k : g[0]){
        for(int v : g[1]){
            if (adjMatrix[k][v] == 0){
                return false; // Neu khong co canh giua hai tap thi khong day du
            }
        }
    }
    // Kiem tra khong co canh trong cung mot tap
    for (int k :g[0]){
        for (int v: g[0]){
            if (k!=v && adjMatrix[k][v] == 1){
                return false; // Neu co canh trong tap 0 thi sai
            }
        }
    }
    for(int k :g [1]){
        for(int v:g[1]){
            if(k!= v && adjMatrix[k][v] == 1){
                return false; // Neu co canh trong tap 1 thi sai
            }
        }
    }
    return true; 
}

// Chuyen sang do thi vo huong
vector<vector<int>> convertToUndirectedGraph(const vector<vector<int>>& adjMatrix){
    int n = adjMatrix.size();
    vector<vector<int>> undirectedGraph(n, vector<int>(n,0));
    for (int i = 0;i <n;i++){
        for (int j = 0 ;j <n ;j++){
            // Neu co canh tu i den j hoac tu j den i trong do thi goc
            if (adjMatrix[i][j] == 1|| adjMatrix[j][i] == 1 ){
                undirectedGraph[i][j] = undirectedGraph[i][j] = 1; // Danh dau co canh giua i va j trong do thi vo huong
            }
        }
    }
    return undirectedGraph;
}
// Lay do thi bu
vector<vector<int>> getComplementGraph(const vector<vector<int>>& adjMatrix){
    int n = adjMatrix.size();
    vector<vector<int>> complementGraph(n,vector<int>(n,0));
    for (int i = 0; i<n;i++){
        for (int j = 0; j < n; j++){
            // Neu i khac j va giua i va j khong co canh trong do thi goc
            if (i != j && adjMatrix[i][j] == 0){
                complementGraph[i][j] = complementGraph[j][i] = 1; // Tao canh giua i va j trong do thi bu
            }
        }
    }
    return complementGraph;
}
// Dao nguoc vector
void reverseV(vector<int>& v) {
    int left = 0, right = v.size() - 1;
    while (left < right) {
        swap(v[left], v[right]);
        left++;
        right--;
    }
}
// Tim chu trinh Euler
vector<int> findEulerCycle(const vector<vector<int>>& adjMatrix){
   int n = adjMatrix.size();
    bool directed = isDirected(adjMatrix);
    vector<vector<int>> g = adjMatrix;

    // Kiem tra dieu kien ton tai chu trinh Euler
    if (directed) {
        // Do thi co huong: moi dinh co in = out
        for (int i = 0; i < n; i++) {
            int outD = 0, inD = 0;
            for (int j = 0; j < n; j++) {
                outD += g[i][j];
                inD += g[j][i];
            }
            if (outD != inD) return {};
        }
    } else {
        // Do thi vo huong: moi dinh bac chan
        for (int i = 0; i < n; i++) {
            int deg = 0;
            for (int j = 0; j < n; j++) deg += g[i][j];
            if (deg % 2 != 0) return {};
        }
    }

    // Tim dinh bat dau
    int begin = 0;
    for (int i = 0; i < n; ++i) {
        int d = 0;
        for (int j = 0; j < n; ++j){
            d += g[i][j];
        } 
        if (d) {
            begin = i;
            break;
        }
    }

    stack<int> s;
    vector<int> c;
    s.push(begin);
    while (!s.empty()) {
        int u = s.top();
        int v = 0;
        while (v < n && g[u][v] == 0){
            v++;
        } 
        if (v == n) {
            c.push_back(u);
            s.pop();
        } else {
            g[u][v]--;
            if (!directed) g[v][u]--;
            s.push(v);
        }
    }
    reverseV(c);
    return c;
}

vector<vector<int>> dfsSpanningTree(const vector<vector<int>>& adjMatrix, int start){
    int n = adjMatrix.size();
    vector<vector<int>> sT(n, vector<int>(n,0));
    vector<bool> visited(n, false);

}

void dfsTraverse( const vector<vector<int>>& adjMatrix, vector<vector<int>>& sT, vector<bool>& visited, int u) {
    int n = adjMatrix.size();
    visited[u] = true;
    for (int v = 0; v < n; v++) {
        if (adjMatrix[u][v] && !visited[v]) {
            sT[u][v] = sT[v][u] = 1;
            dfsTraverse( adjMatrix, sT, visited, v);
        }
    }
}
// DFS tao cay khung
vector<vector<int>> dfsSpanningTree(const vector<vector<int>>& adjMatrix, int start) {
    int n = adjMatrix.size();
    vector<vector<int>> sT(n, vector<int>(n, 0));
    vector<bool> visited(n, false);
    dfsTraverse( adjMatrix, sT, visited, start);
    return sT;
}
// BFS tao cay khung
vector<vector<int>> bfsSpanningTree(const vector<vector<int>>& adjMatrix, int start){
    int n = adjMatrix.size();
    vector<vector<int>> sT(n, vector<int>(n,0));
    vector<bool> visited(n, false);
    queue<int> q;
    q.push(start);
    visited[start] = true;
    while (!q.empty()){
        int u = q.front(); q.pop();
        for (int v = 0; v < n; ++v) {
            if (adjMatrix[u][v] && !visited[v]) {
                sT[u][v] = sT[v][u] = 1;
                visited[v] = true;
                q.push(v);
            }
        }
    }
    return sT;      
}

// Kiem tra 2 dinh co lien thong                                                                                                                                            
bool isConnected(int u, int v, const vector<vector<int>>& adjMatrix){
    int n = adjMatrix.size();
    vector<bool> visited(n,false);
    queue <int> q;
    q.push(u);
    visited[u] = true;
    while (!q.empty()){
        int c = q.front(); q.pop();
        if(c == v) {
            return true;
        }
        for (int i = 0; i < n;i++){
            if (adjMatrix[c][i] && !visited[i]) {
                visited[i] = true;
                q.push(i);
            }
        }
    }
    return false;
}
// Dijkstra tim duong di ngan nhat
vector<int> dijkstra(int start, int end, const vector<vector<int>>& adjMatrix) {
    int n = adjMatrix.size(); // Lay so dinh cua do thi
    vector<int> d(n, INT_MAX); // Mang d luu khoang cach ngan nhat tu start den moi dinh, khoi tao la vo cuc
    vector<int> pre(n, -1); // Mang pre luu dinh truoc tren duong di ngan nhat
    vector<bool> visited(n, false); // Mang visited danh dau cac dinh da xet chua
    d[start] = 0; // Khoang cach tu start den start la 0

    // Lap n lan de tim duong di ngan nhat den moi dinh
    for (int i = 0; i < n; i++) {
        int u = -1, minD = INT_MAX; // u la dinh chua xet co khoang cach nho nhat
        // Tim dinh u chua xet va co d[u] nho nhat
        for (int i = 0; i < n; i++) {
            if (!visited[i] && d[i] < minD) {
                minD = d[i];
                u = i;
            }
        }
        if (u == -1) break; // Neu khong con dinh nao co the di duoc thi dung
        visited[u] = true; // Danh dau da xet dinh u

        // Cap nhat khoang cach den cac dinh ke voi u
        for (int v = 0; v < n; v++) {
            // Neu co canh tu u den v, chua xet v va tim duoc duong di ngan hon
            if (adjMatrix[u][v] > 0 && !visited[v] && d[v] > d[u] + adjMatrix[u][v]) {
                d[v] = d[u] + adjMatrix[u][v]; // Cap nhat khoang cach ngan nhat moi
                pre[v] = u; // Luu dinh truoc cua v tren duong di ngan nhat
            }
        }
    }
    vector<int> path; // Luu ket qua duong di ngan nhat
    if (d[end] == INT_MAX){
        return path; // Khong co duong di tu start den end
    } 
    // Truy vet duong di tu end ve start
    for (int v = end; v != -1; v = pre[v]) {
        path.push_back(v);
    }
    reverseV(path); // Dao nguoc de duong di tu start -> end
    return path;
}
// Bellman-Ford tim duong di ngan nhat
vector<int> bellmanFord(int start, int end, const vector<vector<int>>& adjMatrix) {
     int n = adjMatrix.size(); // Lay so dinh cua do thi
    vector<int> d(n, INT_MAX); // Mang d luu khoang cach ngan nhat tu start den moi dinh, khoi tao la vo cuc
    vector<int> pre(n, -1); // Mang pre luu dinh truoc tren duong di ngan nhat
    d[start] = 0; // Khoang cach tu start den start la 0

    // Lap n-1 lan de cap nhat khoang cach ngan nhat
    for (int k = 0; k < n - 1; k++) {
        for (int u = 0; u < n; u++) { // Duyet tung dinh u
            if (d[u] == INT_MAX) continue; // Neu chua co duong di tu start den u thi bo qua
            for (int v = 0; v < n; v++) { // Duyet cac dinh ke voi u
                // Neu co canh tu u den v va tim duoc duong di ngan hon
                if (adjMatrix[u][v] > 0 && d[v] > d[u] + adjMatrix[u][v]) {
                    d[v] = d[u] + adjMatrix[u][v]; // Cap nhat khoang cach ngan nhat moi
                    pre[v] = u; // Luu dinh truoc cua v tren duong di ngan nhat
                }
            }
        }
    }
    // Khong kiem tra chu trinh am

    vector<int> path; // Luu ket qua duong di ngan nhat
    if (d[end] == INT_MAX) return path; // Neu khong co duong di tu start den end thi tra ve rong

    // Truy vet duong di tu end ve start
    for (int v = end; v != -1; v = pre[v]){
        path.push_back(v);
    }
    reverseV(path); // Dao nguoc de duong di tu start -> end
    return path;
}