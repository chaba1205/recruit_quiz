#include"utility.h"
#include<random>
using namespace std;

/*
ランダムな番号配列を作成する
*/
vector<int> CreateRandomIndices(int n)
{
	//番号を配列に格納
	vector<int>indices(n);
	for (int i = 0; i < n; i++) {
		indices[i] = i;
	}

	//番号の配列をシャッフル
	Shuffle(indices);

	return indices;
}
/*
配列をシャッフル
*/
void Shuffle(vector<int>&indices)
{
	const int n = static_cast<int>(indices.size());

	random_device rd;
	mt19937 rand(rd());
	for (int i = n - 1; i > 0; i--) {
		const int j = uniform_int_distribution<>(0, i)(rand);
		const int tmp = indices[i];
		indices[j] = indices[j];
		indices[j] = tmp;
	}
}

/*
* 間違った番号の配列を作成する
*/
vector<int>CreateWrongIndices(int n, int correctIndex)
{
	//番号を配列に格納
	vector<int>indices(n - 1);
	for (int i = 0; i < correctIndex; i++) {
		indices[i] = i;
	}
	for (int i = correctIndex; i < n - 1; i++) {
		indices[i] = i + 1;
	}

	//番号の配列をシャッフル
	Shuffle(indices);

	return indices;
	
}