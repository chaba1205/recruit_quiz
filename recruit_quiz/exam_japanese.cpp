#include"exam_japanese.h"
#include"utility.h"
#include<random>
using namespace std;

/*
漢字の読み取り問題を作成する
*/
QuestionList CreateKanjiExam()
{
	static const struct {
		const char* kanji;//漢字
		const char* reading;//読み
		const char* meaning;//意味
	}data[] = {
		{"市井","しせい","人が多く集まって暮らすところ、町"},
		{"捺印","なついん","(署名と共に）印鑑を押すこと"},
			{"相殺","そうさい","足し引きの結果、差が無くなること"},
		{"凡例","はんれい","本や図表のはじめに、使い方や約束事を箇条書きにしたもの"},
		{"約定","やくじょう","約束して決めること、契約"},
	  };
	constexpr int quizCount = 5;
	QuestionList questions;
	questions.reserve(quizCount);
	const vector<int>indices = CreateRandomIndices(size(data));
	random_device rd;

	//問題の種類を選ぶ
	int type = uniform_int_distribution<>(0, 1)(rd);
	if (type == 0) {
		//漢字の読みを答える問題
		for (int i = 0; i < quizCount; i++) {
			const auto& e = data[indices[i]];
			questions.push_back({
				"「" + string(e.kanji) + "」の読みをひらがなで答えよ",
				e.reading });
		}
	}
	else {
		//正しい熟語をこたえる問題
		for (int i = 0; i < quizCount; i++) {
			//間違った番号をランダムに選ぶ
			const int correctIndex = indices[i];
			vector<int>answers = CreateWrongIndices(size(data), correctIndex);
			//ランダムな位置を正しい番号で上書き
			const int correctNo = uniform_int_distribution<>(1, 3)(rd);
			answers[correctNo - 1] = correctIndex;

			//問題文を作成
			string s = "「" + string(data[correctIndex].meaning) +
				"」を意味する熟語の番号を選べ";
			for (int j = 0; j < 3; j++) {
				s += "\n" + to_string(j + 1) + ":" + data[answers[j]].kanji;
			}

			questions.push_back({ s,to_string(correctNo) });
		}
	}//if type
	return questions;
}

/**
*同じ読みで意味の異なる漢字の問題を作成する
*/
QuestionList CreateHomophoneExam()
{
	const struct {
		const char* reading;//読み
		struct {
			const char* kanji;//漢字
			const char* meaning;//意味
		}words[3];
	}data[] = {
		{"じき",{
			{"時期","何かを行うとき、期間。"},
		{"時機","物事を行うのによい機会"}}},
		{"そうぞう",{
			{"想像","実際には経験していない事柄をおまい描くこと"},
			{"創造","新しいものを作る上げること"}}},
		{"ほしょう",{
			{"保証","間違いがなく確かであると約束すること"},
			{"保障","権利や地位などが維持されるように保護し守ること"},
			{"補償","損失を補って償うこと"}}},
			{"あやまる",{
				{"謝る","失敗について許しを求める"},
				{"誤る","間違った判断をする"}}},
				{"おさめる",{
					{"納める","金や物を渡すべきところに渡す"},
						{"治める","乱れている物事を落ち着いて穏やかな状態にする"},
						{"修める","行いや人格を正しくする、学問や技芸などを学んで身につける"}}},
	};

	constexpr int quizCount = 5;
	QuestionList questions;
	questions.reserve(quizCount);
	const vector<int>indices = CreateRandomIndices(size(data));
	random_device rd;

	for (int i = 0; i < quizCount; i++) {
		const auto& e = data[indices[i]];

		//要素数を計算
		int count = 0;
		for (; count < size(e.words); count++) {
			if (!e.words[count].kanji) {
				break;
			}
		}

		//正しい番号を選択
		const int correctNo = uniform_int_distribution<>(1, count)(rd);

		//問題文を作成
		const vector<int>answers = CreateRandomIndices(count);
		string s = "「" + string(e.words[answers[correctNo - 1]].kanji) +
			"」の意味として正しい番号を選べ";
		for (int j = 0; j < count; j++) {
			s += "\n" + to_string(j + 1) + ":" + e.words[answers[j]].meaning;
		}
		questions.push_back({ s,to_string(correctNo) });
	}
	return questions;
}

/*
* 対義語を作成する
*/
QuestionList CreateAntonymExam()
{
	const struct {
		const char* kanji[2];
	}data[] = {
		{"意図（いと）","恣意(しい）"},{"需要（じゅよう）","供給(供給）"},
		{"故意(こい)","過失(かしつ)"},{"曖昧(あいまい)","明瞭(めいりょう)"},
		{"緊張(きんちょう)","弛緩(しかん)"},{"過疎(かそ)","過密(かみつ)"},
		{"栄転(えいてん)","左遷(させん)"},{"消費(しょうひ)","生産(せいさん)"},
		{"異端(いたん)","正統(せいとう)"},{"尊敬(そんけい)","軽蔑(けいべつ)"},
	};

	constexpr int quizCount = 5;
	QuestionList questions;
	questions.reserve(quizCount);
	const vector<int>indices = CreateRandomIndices(size(data));
	random_device rd;

	for (int i = 0; i < quizCount; i++) {
		//間違った番号をランダムに選ぶ
		const int correctIndex = indices[i];
		vector<int>answers = CreateWrongIndices(size(data), correctIndex);

		//ランダムな位置を正しい番号で上書き
		const int correctNo = uniform_int_distribution<>(1, 4)(rd);
		answers[correctNo - 1] = correctIndex;

		//問題文を作成
		const int object = uniform_int_distribution<>(0, 1)(rd);
		const int other = (object + 1) % 2;
		string s = "「" + string(data[correctIndex].kanji[object]) +
			"」の対義語として正しい番号を選べ";
		for (int j = 0; j < 4; j++) {
			s += "\n" + to_string(j + 1) + ":" + data[answers[j]].kanji[other];
		}
		questions.push_back({ s,to_string(correctNo) });
	}
	return questions;
}

/*
慣用句の意味を答える問題を作成する
*/
QuestionList CreateIdiomExam()
{
	static const struct {
		const char* idiom;//慣用句
		const char* meaning;//意味
	}data[] = {
		{"気のおけない","気づかいがいらない"},
		{"琴線に触れる","心から感謝する"},
		{"汚名をそそぐ","名誉を回復する"},
		{"言葉を取る","証拠となる言葉を聞き出す"},
		{"糠（ぬか）に釘","効き目がない"},
	};

	constexpr int quizCount = 5;
	QuestionList questions;
	questions.reserve(quizCount);
	const vector<int>indices = CreateRandomIndices(size(data));
	random_device rd;

	for (int i = 0; i < quizCount; i++) {
		//間違った番号をランダムに選ぶ
		const int correctIndex = indices[i];
		vector<int>answers = CreateWrongIndices(size(data), correctIndex);

		//ランダムな位置を正しい番号で上書き
		const int correctNo = uniform_int_distribution<>(1, 3)(rd);
		answers[correctNo - 1] = correctIndex;

		//問題文を作成
		string s = "「" + string(data[correctIndex].idiom) + "」意味として正しい番号を選べ";
		for (int j = 0; j < 3; j++) {
			s += "\n" + to_string(j + 1) + ":" + data[answers[j]].meaning;
		}
		questions.push_back({ s,to_string(correctNo) });
	}
	return questions;
}

/**
*類義語の問題を作成する
*/
QuestionList CreateSynonymExam()
{
	const struct {
		int count;//要素数
		const char* kanji[4];//類義語の配列
	}data[] = {
		{2,"仲介（ちゅうかい）","斡旋（あっせん）"},
		{3,"夭逝（ようせい）","夭折（ようせつ）","早世（そうせい）"},
		{4,"交渉（こうしょう）","折衝（せっしょう）","協議（きょうぎ）"},
		{5,"抜群（ばつぐん）","傑出（けっしゅつ）","出色（しゅっしょく）"},
		{6,"熟知（じゅくち）","通暁（つうぎょう）","知悉（ちしつ）","精通（せいつう）"},
	};

	constexpr int quizCount = 5;
	QuestionList questions;
	questions.reserve(quizCount);
	const vector<int>indices = CreateRandomIndices(size(data));
	random_device rd;

	for (int i = 0; i < quizCount; i++) {

		//間違った番号をランダムに選ぶ
		const int correctIndex = indices[i];
		vector<int>answers = CreateWrongIndices(size(data), correctIndex);

		//ランダムな位置を正しい番号で上書き
		const int correctNo = uniform_int_distribution<>(1, 4)(rd);
		answers[correctNo - 1] = correctIndex;

		//出題する類義語を選択
		const auto& e = data[indices[i]];
		const int object = uniform_int_distribution<>(0, e.count - 1)(rd);
		//問題を作成
		string s = "「" + string(data[correctIndex].kanji[object]) +
			"」の類義語として正しい番号を選べ";
		for (int j = 0; j < 4; j++) {
			if (j == correctNo - 1) {
				//出題する語「以外」の類義語を正解として選択
				int other = uniform_int_distribution<>(0, e.count - 2)(rd);
				if (other >= object) {
					other++;
				}
				s += "\n" + to_string(j + 1) + ":" + e.kanji[other];
			}
			else {
				//誤答選択
				const auto& f = data[answers[j]];
				const int k = uniform_int_distribution<>(0, f.count - 1)(rd);
				s += "\n" + to_string(j + 1) + ":" + f.kanji[k];
			}
		}
		questions.push_back({ s,to_string(correctNo) });
	}

	return questions;
}