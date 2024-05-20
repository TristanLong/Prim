#include "iostream"
#include "fstream"
#include "vector"
using namespace std;

const int MAX = 20;

struct maTrix {
	int maTranKe[MAX][MAX];
	int soDinh;
};

void readFile(maTrix& mtk) {
	ifstream inFile("Text.txt");
	if (!inFile.is_open()) {
		cout << "\nKhong the mo tep";
		return;
	}

	inFile >> mtk.soDinh;
	for (int i = 0; i < mtk.soDinh; i++) {
		for (int j = 0; j < mtk.soDinh; j++) {
			inFile >> mtk.maTranKe[i][j];
		}
	}
	inFile.close();
}

void outputMaTrix(maTrix mtk) {
	cout << "\nMA TRAN KE: " << endl;
	for (int i = 0; i < mtk.soDinh; i++) {
		for (int j = 0; j < mtk.soDinh; j++) {
			if (mtk.maTranKe[i][j] == INT_MAX) {
				cout << "INF\t";
			}
			else {
				cout << mtk.maTranKe[i][j] << "\t";
			}
		}
		cout << endl;
	}
}

// Biểu diễn cạnh
struct edge {
	int dau, cuoi, trongSo;
};

bool used[MAX] = { false };

void prim(int u,maTrix graph) {
	vector<edge> CayKhung; 
	int TongTrongSoCayKhung = 0;
	used[u] = true; 
	while (CayKhung.size() < graph.soDinh - 1) {
		int TrongSoNhoNhat = INT_MAX;
		int x = -1, y = -1; // Lưu 2 đỉnh của cạnh có trọng số nhỏ nhất
		// Tìm cạnh có trọng số nhỏ nhất
		for (int i = 0; i < graph.soDinh; i++) {
			// Nếu đỉnh i thuộc tập V(CayKhung)
			if (used[i]) {
				// Duyệt danh sách kề của đỉnh i
				for (int dinhKe = 0; dinhKe < graph.soDinh; dinhKe++) {
					int trongSo = graph.maTranKe[i][dinhKe];
					if (!used[dinhKe] && trongSo < TrongSoNhoNhat && trongSo != -1) {
						TrongSoNhoNhat = trongSo;
						x = dinhKe;
						y = i;
					}
				}
			}
		}
		// Kiểm tra nếu tìm thấy cạnh hợp lệ
		if (x != -1 && y != -1) {
			CayKhung.push_back({ y, x, TrongSoNhoNhat });
			TongTrongSoCayKhung += TrongSoNhoNhat;
			used[x] = true; // Đưa đỉnh x vào V(CayKhung), loại x khỏi tập V
		}
		else {
			cout << "\nDo thi khong lien thong";
			return; // Không tìm thấy cạnh nào hợp lệ, dừng thuật toán
		}
	}

	cout << "\nCay khung nho nhat:" << endl;
	for (edge canh : CayKhung) {
		cout << "(" << canh.dau << "," << canh.cuoi << "): " << canh.trongSo << endl;
	}

	cout << "Tong trong so cua cay khung nho nhat: " << TongTrongSoCayKhung << endl;
}

int main() {
	maTrix graph;
	readFile(graph);
	outputMaTrix(graph);
	prim(0, graph);
}
