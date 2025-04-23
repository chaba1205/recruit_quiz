#include<iostream>
using namespace std;

int main()
{
	cout << "[リクルート試験対策クイズ]\n";
	cout << "13x(-5)の答えは？\n";

	int answer;
	cin >> answer;
	if (answer == 13 * -5) {
		cout << "正解\n";
	}
	else {
		cout << "間違い！正解は" << 13 * -5 << "\n";
	}
}