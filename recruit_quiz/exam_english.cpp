#include"exam_english.h"
#include"utility.h"
#include<random>
using namespace std;

/*
英単語の問題を作成する
*/
QuestionList CreateEnglishWordExam()
{
	const struct {
		const char* word;//英単語
		const char* reading;//読み
		const char* meaning;//意味
	}data[] = {
		{"state","ステート","状態"},
		{"business","ビジネス","事業、仕事"},
		{"abstract","アブストラクト","抽象的な"},
		{"concrete","コンクリート","具体的な"},
		{"digital","デジタル","数字で情報を伝える"},
		{"analogue","アナログ","類似している、類似物"},
		{"exchange","エクスチェンジ","交換、両替、偽替"},
		{"infrastructure","インフラストラクチャ","下部構造、基盤となる施設や設備"},
		{"knowledge","ナレッジ","知識"},
		{"credit","クレジット","信用"},
	};

	constexpr int quizCount = 5;
	QuestionList questions;
	questions.reserve(quizCount);
	const vector<int>indices = CreateRandomIndices(size(data));
	random_device rd;

	//ランダムに問題を選ぶ
	const int type = uniform_int_distribution<>(0, 3)(rd);
	switch (type) {
	case 0://意味から英単語を答える
		for (int i = 0; i < quizCount; i++) {
			const auto& e = data[indices[i]];
			questions.push_back({
				"「" + string(e.meaning) + "」を意味する英単語を答えよ",
				e.word });
		}
		break;

	case 1://読みから英単語を答える
		for (int i = 0; i < quizCount; i++) {
			const auto& e = data[indices[i]];
			questions.push_back({
				"カタカナ読み「" + string(e.reading) + "」に対応する英単語を答えよ",
				e.word });
		}
		break;

	case 2://英単語から「読み」を答える
		for (int i = 0; i < quizCount; i++) {
			const auto& e = data[indices[i]];
			questions.push_back({
				string(e.word)+"の読みをカタカナで答えよ",
				e.reading });
		}
		break;

	case 3://英単語の意味を答える
		for (int i = 0; i < quizCount; i++) {
			//間違った番号をランダムに選ぶ
			const int correctIndex = indices[i];
			vector<int> answers = CreateWrongIndices(size(data), correctIndex);

			//ランダムな位置を正しい番号で上書き
			const int correctNo = std::uniform_int_distribution<>(1, 3)(rd);
			answers[correctNo - 1] = correctIndex;

			//問題文を作成
			string s = "「" + string(data[correctIndex].word) +
				"」の意味として正しい番号を選べ\n";
			s += std::string(" 1:") + data[answers[0]].meaning + "\n";
			s += std::string(" 2:") + data[answers[1]].meaning + "\n";
			s += std::string(" 3:") + data[answers[2]].meaning;

			questions.push_back({ s,to_string(correctNo) });
		}
		break;

	}//switch(type)

	return questions;
}

/*
英語の定型文の問題を作成する
*/
QuestionList CreateEnglishPhraseExam()
{
	const struct {
		const char* phrase;//定型文の形
		const char* meaning;//定型文の意味
		const char* example;//英語の例文
		const char* translation;//例文の日本語訳
		int blankCount;			//穴の候補の数
		int blankOptions[3];	//穴の候補になる単語の位置
	}data[] = {
		{"too[A]to[B]","とても[A]なので[B]できない",
		"The tea was too hot to drink.","お茶が熱すぎて飲めなかった。",
		2,{3,5}},
		{"be looking forward to [A]","[A]を楽しみにする",
		"I'm looking forward to seening you","あなたに会うのを楽しみにしています。",
		3,{1,2,3}},
		{"according to[A]","[A]によると",
		"Acoording to the weather forcast,today is rain.","天気予報によると、今日は雨だ。",
		2,{0,1}},
		{"as soon as [A]","[A]するとすぐに",
		"As soon as I arrive, Iwill call you.","着地したらすぐに電話します。",
		3,{0,1,2}},
		{"be not supposed to[A]","[A]してはいけないことになっている",
		"You arenot supposed toenter this room.","この部屋に入ってはいけません。",
		3,{2,3,4}},
	};

	constexpr int quizCount = 5;
	QuestionList questions;
	questions.reserve(quizCount);
	const vector<int> indices = CreateRandomIndices(size(data));
	random_device rd;

	//問題の種類をランダムに選ぶ
	int type = uniform_int_distribution<>(0, 2)(rd);
	switch (type) {
	case 0://空欄に入る単語を答える
		for (int i = 0; i < quizCount; i++) {
			const auto& e = data[indices[i]];

			//例文を単語に分解
			vector<string>words;
			const char* start = e.example;
			for (const char* p = e.example; *p; p++) {
				if (*p == ' ') {
					words.push_back(string(start, p));
					start = p + 1;
				}
			}
			words.push_back(string(start));

			//穴にする単語の位置を選ぶ
			int n = uniform_int_distribution<>(0, e.blankCount - 1)(rd);
			int blankIndex = e.blankOptions[n];

			//穴にする位置の単語を答えとする
			string a = words[blankIndex];

			//穴にする位置の単語を「空欄」に置き換える
			words[blankIndex] = "[?]";

			//単語を文に復元
			string s = words[0];
			for (int j = 1; j < words.size(); j++) {
				s += " " + words[j];
			}

			//問題文と答えを追加
			questions.push_back({
				"[?]に適切な語を入れて英文を完成させよ\n" + string(e.translation) + "\n" + s,
				a });
		}
		break;

	case 1://定型文の意味を答える
		for (int i = 0; i < quizCount; i++) {
			//間違った番号をランダムに選ぶ
			const int correctIndex = indices[i];
			vector<int>answers = CreateWrongIndices(size(data), correctIndex);

			//ランダムな位置を正しい番号で上書き
			const int correctNo = std::uniform_int_distribution<>(1, 3)(rd);
			answers[correctNo - 1] = correctIndex;

			//問題文を作成
			string s = "「" + string(data[correctIndex].phrase) +
				"」の意味として正しい番号を選べ\n";
			s += std::string(" 1:") + data[answers[0]].meaning + "\n";
			s += std::string(" 2:") + data[answers[1]].meaning + "\n";
			s += std::string(" 3:") + data[answers[2]].meaning;

			questions.push_back({ s,to_string(correctNo) });
		}
		break;

	case 2://意味の合う定型文を答える
		for (int i = 0; i < quizCount; i++) {
			//間違った番号をランダムに選ぶ
			const int correctIndex = indices[i];
			vector<int>answers = CreateWrongIndices(size(data), correctIndex);

			//ランダムな位置を正しい番号で上書き
			const int correctNo = std::uniform_int_distribution<>(1, 3)(rd);
			answers[correctNo - 1] = correctIndex;

			//問題文を作成
			string s = "「" + string(data[correctIndex].meaning) + "」に対応する定型文を選べ\n";
			"」の意味として正しい番号を選べ\n";
			s += std::string(" 1:") + data[answers[0]].phrase + "\n";
			s += std::string(" 2:") + data[answers[1]].phrase + "\n";
			s += std::string(" 3:") + data[answers[2]].phrase;

			questions.push_back({ s,to_string(correctNo) });

		}
		break;
	}//switch(type)

	return questions;
}