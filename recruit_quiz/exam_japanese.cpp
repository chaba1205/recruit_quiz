#include"exam_japanese.h"
#include"utility.h"
#include<random>
using namespace std;

/*
�����̓ǂݎ������쐬����
*/
QuestionList CreateKanjiExam()
{
	static const struct {
		const char* kanji;//����
		const char* reading;//�ǂ�
		const char* meaning;//�Ӗ�
	}data[] = {
		{"�s��","������","�l�������W�܂��ĕ�炷�Ƃ���A��"},
		{"���","�Ȃ���","(�����Ƌ��Ɂj��ӂ���������"},
			{"���E","��������","���������̌��ʁA���������Ȃ邱��"},
		{"�}��","�͂�ꂢ","�{��}�\�̂͂��߂ɁA�g������񑩎����ӏ������ɂ�������"},
		{"���","�₭���傤","�񑩂��Č��߂邱�ƁA�_��"},
	  };
	constexpr int quizCount = 5;
	QuestionList questions;
	questions.reserve(quizCount);
	const vector<int>indices = CreateRandomIndices(size(data));
	random_device rd;

	//���̎�ނ�I��
	int type = uniform_int_distribution<>(0, 1)(rd);
	if (type == 0) {
		//�����̓ǂ݂𓚂�����
		for (int i = 0; i < quizCount; i++) {
			const auto& e = data[indices[i]];
			questions.push_back({
				"�u" + string(e.kanji) + "�v�̓ǂ݂��Ђ炪�Ȃœ�����",
				e.reading });
		}
	}
	else {
		//�������n�������������
		for (int i = 0; i < quizCount; i++) {
			//�Ԉ�����ԍ��������_���ɑI��
			const int correctIndex = indices[i];
			vector<int>answers = CreateWrongIndices(size(data), correctIndex);
			//�����_���Ȉʒu�𐳂����ԍ��ŏ㏑��
			const int correctNo = uniform_int_distribution<>(1, 3)(rd);
			answers[correctNo - 1] = correctIndex;

			//��蕶���쐬
			string s = "�u" + string(data[correctIndex].meaning) +
				"�v���Ӗ�����n��̔ԍ���I��";
			for (int j = 0; j < 3; j++) {
				s += "\n" + to_string(j + 1) + ":" + data[answers[j]].kanji;
			}

			questions.push_back({ s,to_string(correctNo) });
		}
	}//if type
	return questions;
}

/**
*�����ǂ݂ňӖ��̈قȂ銿���̖����쐬����
*/
QuestionList CreateHomophoneExam()
{
	const struct {
		const char* reading;//�ǂ�
		struct {
			const char* kanji;//����
			const char* meaning;//�Ӗ�
		}words[3];
	}data[] = {
		{"����",{
			{"����","�������s���Ƃ��A���ԁB"},
		{"���@","�������s���̂ɂ悢�@��"}}},
		{"��������",{
			{"�z��","���ۂɂ͌o�����Ă��Ȃ����������܂��`������"},
			{"�n��","�V�������̂����グ�邱��"}}},
		{"�ق��傤",{
			{"�ۏ�","�ԈႢ���Ȃ��m���ł���Ɩ񑩂��邱��"},
			{"�ۏ�","������n�ʂȂǂ��ێ������悤�ɕی삵��邱��"},
			{"�⏞","���������ď�������"}}},
			{"����܂�",{
				{"�ӂ�","���s�ɂ��ċ��������߂�"},
				{"���","�Ԉ�������f������"}}},
				{"�����߂�",{
					{"�[�߂�","���╨��n���ׂ��Ƃ���ɓn��"},
						{"���߂�","����Ă��镨���𗎂������ĉ��₩�ȏ�Ԃɂ���"},
						{"�C�߂�","�s����l�i�𐳂�������A�w���Z�|�Ȃǂ��w��Őg�ɂ���"}}},
	};

	constexpr int quizCount = 5;
	QuestionList questions;
	questions.reserve(quizCount);
	const vector<int>indices = CreateRandomIndices(size(data));
	random_device rd;

	for (int i = 0; i < quizCount; i++) {
		const auto& e = data[indices[i]];

		//�v�f�����v�Z
		int count = 0;
		for (; count < size(e.words); count++) {
			if (!e.words[count].kanji) {
				break;
			}
		}

		//�������ԍ���I��
		const int correctNo = uniform_int_distribution<>(1, count)(rd);

		//��蕶���쐬
		const vector<int>answers = CreateRandomIndices(count);
		string s = "�u" + string(e.words[answers[correctNo - 1]].kanji) +
			"�v�̈Ӗ��Ƃ��Đ������ԍ���I��";
		for (int j = 0; j < count; j++) {
			s += "\n" + to_string(j + 1) + ":" + e.words[answers[j]].meaning;
		}
		questions.push_back({ s,to_string(correctNo) });
	}
	return questions;
}

/*
* �΋`����쐬����
*/
QuestionList CreateAntonymExam()
{
	const struct {
		const char* kanji[2];
	}data[] = {
		{"�Ӑ}�i���Ɓj","����(�����j"},{"���v�i����悤�j","����(�����j"},
		{"�̈�(����)","�ߎ�(������)"},{"�B��(�����܂�)","����(�߂���傤)"},
		{"�ْ�(���񂿂傤)","�o��(������)"},{"�ߑa(����)","�ߖ�(���݂�)"},
		{"�h�](�����Ă�)","���J(������)"},{"����(���傤��)","���Y(��������)"},
		{"�ْ[(������)","����(�����Ƃ�)"},{"���h(���񂯂�)","�y��(�����ׂ�)"},
	};

	constexpr int quizCount = 5;
	QuestionList questions;
	questions.reserve(quizCount);
	const vector<int>indices = CreateRandomIndices(size(data));
	random_device rd;

	for (int i = 0; i < quizCount; i++) {
		//�Ԉ�����ԍ��������_���ɑI��
		const int correctIndex = indices[i];
		vector<int>answers = CreateWrongIndices(size(data), correctIndex);

		//�����_���Ȉʒu�𐳂����ԍ��ŏ㏑��
		const int correctNo = uniform_int_distribution<>(1, 4)(rd);
		answers[correctNo - 1] = correctIndex;

		//��蕶���쐬
		const int object = uniform_int_distribution<>(0, 1)(rd);
		const int other = (object + 1) % 2;
		string s = "�u" + string(data[correctIndex].kanji[object]) +
			"�v�̑΋`��Ƃ��Đ������ԍ���I��";
		for (int j = 0; j < 4; j++) {
			s += "\n" + to_string(j + 1) + ":" + data[answers[j]].kanji[other];
		}
		questions.push_back({ s,to_string(correctNo) });
	}
	return questions;
}

/*
���p��̈Ӗ��𓚂�������쐬����
*/
QuestionList CreateIdiomExam()
{
	static const struct {
		const char* idiom;//���p��
		const char* meaning;//�Ӗ�
	}data[] = {
		{"�C�̂����Ȃ�","�C�Â���������Ȃ�"},
		{"�Ր��ɐG���","�S���犴�ӂ���"},
		{"������������","���_���񕜂���"},
		{"���t�����","�؋��ƂȂ錾�t�𕷂��o��"},
		{"�f�i�ʂ��j�ɓB","�����ڂ��Ȃ�"},
	};

	constexpr int quizCount = 5;
	QuestionList questions;
	questions.reserve(quizCount);
	const vector<int>indices = CreateRandomIndices(size(data));
	random_device rd;

	for (int i = 0; i < quizCount; i++) {
		//�Ԉ�����ԍ��������_���ɑI��
		const int correctIndex = indices[i];
		vector<int>answers = CreateWrongIndices(size(data), correctIndex);

		//�����_���Ȉʒu�𐳂����ԍ��ŏ㏑��
		const int correctNo = uniform_int_distribution<>(1, 3)(rd);
		answers[correctNo - 1] = correctIndex;

		//��蕶���쐬
		string s = "�u" + string(data[correctIndex].idiom) + "�v�Ӗ��Ƃ��Đ������ԍ���I��";
		for (int j = 0; j < 3; j++) {
			s += "\n" + to_string(j + 1) + ":" + data[answers[j]].meaning;
		}
		questions.push_back({ s,to_string(correctNo) });
	}
	return questions;
}

/**
*�ދ`��̖����쐬����
*/
QuestionList CreateSynonymExam()
{
	const struct {
		int count;//�v�f��
		const char* kanji[4];//�ދ`��̔z��
	}data[] = {
		{2,"����i���イ�����j","�����i��������j"},
		{3,"����i�悤�����j","��܁i�悤���j","�����i���������j"},
		{4,"���i�������傤�j","�܏Ձi�������傤�j","���c�i���傤���j"},
		{5,"���Q�i�΂���j","���o�i��������j","�o�F�i��������傭�j"},
		{6,"�n�m�i���キ���j","�ʋŁi�����傤�j","�m���i�����j","���ʁi�������j"},
	};

	constexpr int quizCount = 5;
	QuestionList questions;
	questions.reserve(quizCount);
	const vector<int>indices = CreateRandomIndices(size(data));
	random_device rd;

	for (int i = 0; i < quizCount; i++) {

		//�Ԉ�����ԍ��������_���ɑI��
		const int correctIndex = indices[i];
		vector<int>answers = CreateWrongIndices(size(data), correctIndex);

		//�����_���Ȉʒu�𐳂����ԍ��ŏ㏑��
		const int correctNo = uniform_int_distribution<>(1, 4)(rd);
		answers[correctNo - 1] = correctIndex;

		//�o�肷��ދ`���I��
		const auto& e = data[indices[i]];
		const int object = uniform_int_distribution<>(0, e.count - 1)(rd);
		//�����쐬
		string s = "�u" + string(data[correctIndex].kanji[object]) +
			"�v�̗ދ`��Ƃ��Đ������ԍ���I��";
		for (int j = 0; j < 4; j++) {
			if (j == correctNo - 1) {
				//�o�肷���u�ȊO�v�̗ދ`��𐳉��Ƃ��đI��
				int other = uniform_int_distribution<>(0, e.count - 2)(rd);
				if (other >= object) {
					other++;
				}
				s += "\n" + to_string(j + 1) + ":" + e.kanji[other];
			}
			else {
				//�듚�I��
				const auto& f = data[answers[j]];
				const int k = uniform_int_distribution<>(0, f.count - 1)(rd);
				s += "\n" + to_string(j + 1) + ":" + f.kanji[k];
			}
		}
		questions.push_back({ s,to_string(correctNo) });
	}

	return questions;
}