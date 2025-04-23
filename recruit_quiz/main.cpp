#include<iostream>
#include<string>
using namespace std;

//問題文と答えを待とめる構造体
struct Question
{
	string q;//問題文
	int a;//答え
};

int main()
{
	Question questions[]{
		{"13x(-5)",13 * -5},
		{"(-21)÷(-3)",-21/-3},
		{"7-(4+2)÷2",7 - (4 + 2) / 2},
	};

	cout << "[リクルート試験対策クイズ]\n";

	for (const auto& e : questions) {
		cout << e.q << "答えは？\n";
		int answer;
		cin >> answer;
		if (answer == e.a) {
			cout << "正解\n";
		}
		else {
			cout << "間違い！正解は" << e.a << "\n";
		}
	}//for questions
}