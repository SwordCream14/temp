#pragma once
#include "symtab.h"
#include "Scan.h"
#include <iostream>


class Syntax                                   //�ݹ��ӳ������
{
private:
	TokenType Token;                        //����Token
	Scan sExam;                             //ɨ��������
	SymTable st;
public:
	//Syntax(SemRecord* p1, int* p2, double* p3, int* p4);
	Syntax() {
		st.Init(sExam.keymap, sExam.Imap, sExam.Cmap, sExam.Fmap);
	}
	void Parse();

protected:
	void ERR_EXI();
	void PROGRAM();                          //������
	void FUN_BODY();                         //������
	void VARIABLE();                         //����˵��
	void ID_SEQUENCE(string str);                      //��ʶ����
	void TYPE();                             //���Ͷ���
	void EVA_SENTENCE();                     //��ֵ���
	void EXPRESSION();                       //���ʽ
	void ITEM();                             //��
	void DIVISOR();                          //����
	void IF_CONDITION();                     //if����
	void ELSE_CONDITION();                   //else����
	void WHILE_LOOP();                       //whileѭ��
	void RELATION_SEQUENCE();                //��ϵʽ�б�
	void STATEMENT();                        //�������
//    int map(int code);
};


void Syntax::ERR_EXI() {
	cout << "error!" << endl;
	exit(0);
}

void Syntax::Parse()
{
	string filename;                             //�ļ�����

	printf("please input file name:");             //�����ļ���
	cin >> filename;
	if (!sExam.openfile(filename))                 //���ļ�
		return;
	Token = sExam.Read();                                    //read(w)
	PROGRAM();
	//cout << "\n\n�﷨��������� ";
	printf("\n\nOK!\n\n");
	st.MidCode(0);
	//cout << "���ɵ���Ԫʽ�������黮�֣�\n";
	st.DividMid();
	//cout << "DAG�Ż������Ԫʽ��\n";
	st.SetUp();
	st.DividMid();
	//st.OutPutMid();
	//cout << "��Ծ��Ϣ:\n";
	st.happily();
	st.OutPutfhb();
};

//����
void Syntax::PROGRAM() {
	if (Token.code == 'K' && Token.value == 2) {
		st.insert(st.token_to_str(Token));
		Token = sExam.Read();
		if (Token.code == 'I') {
			st.insert(st.token_to_str(Token));
			st.JudgePush(Token);
			Token = sExam.Read();
			if (Token.code == 'P' && Token.value == 3) {
				Token = sExam.Read();
				if (Token.code == 'P' && Token.value == 4) {
					Token = sExam.Read();
					st.MidCode(1);
					if (Token.code == 'P' && Token.value == 15) {
						Token = sExam.Read();
						FUN_BODY();
						if (Token.code == 'P' && Token.value == 16) {

							return;
						}
						else ERR_EXI();
					}
					else ERR_EXI();
				}
				else ERR_EXI();
			}
			else ERR_EXI();
		}
		else ERR_EXI();
	}
	else ERR_EXI();
}

//������
void Syntax::FUN_BODY() {
	if (Token.code == 'K' && Token.value == 12) {
		IF_CONDITION();
		FUN_BODY();
	}
	else if (Token.code == 'K' && Token.value == 5) {
		WHILE_LOOP();
		FUN_BODY();
	}
	else if (Token.code == 'K') {
		VARIABLE();
		FUN_BODY();
	}
	else if (Token.code == 'I') {
		EVA_SENTENCE();
		FUN_BODY();
	}
	return;
}

//��������
void Syntax::VARIABLE()
{
	string str = st.token_to_str(Token);
	TYPE();
	ID_SEQUENCE(str);
	if (Token.code == 'P' && Token.value == 13) {
		Token = sExam.Read();
	}
	else
		ERR_EXI();
};

void Syntax::ID_SEQUENCE(string str)
{
	if (Token.code == 'P' && Token.value == 12)                                 //��ʶ��
	{
		Token = sExam.Read();
		ID_SEQUENCE(str);
	}
	else if (Token.code == 'P' && Token.value == 11) {

		Token = sExam.Read();
		EXPRESSION();
		st.MidCode(6);
		ID_SEQUENCE(str);
	}
	else if (Token.code == 'I') {     //����һ����ʶ���Ͱ���д��ջ�У������һ�����ǵȺŶ��ǷֺŻ��߶��ž�pop
		// st.insert(str);
		st.insert(st.token_to_str(Token));
		st.JudgePush(Token);  //�����һ�����ǵȺž�pop
		Token = sExam.Read();
		if (Token.code == 'P' && (Token.value == 13 || Token.value == 12))st.Smean.pop();//�����ʶ����߽ӵ��ǷֺŻ��߶���
		ID_SEQUENCE(str);
	}
};

void Syntax::TYPE()///////////////////////////////////////////////////////
{
	if (Token.code == 'K') {
		switch (Token.value)
		{
		case 1:st.insert(st.token_to_str(Token)); Token = sExam.Read(); break;                                         //integer
		case 4: st.insert(st.token_to_str(Token)); Token = sExam.Read(); break; //real
		case 15:st.insert(st.token_to_str(Token)); Token = sExam.Read(); break; //////////////////////////////////////
		case 16: st.insert(st.token_to_str(Token)); Token = sExam.Read(); break;                 //bool////////////////////////////////
		default:		ERR_EXI();
		}
	}
};


void Syntax::EVA_SENTENCE()
{
	if (Token.code == 'I')                                 //��ʶ��
	{
		st.JudgePush(Token);
		Token = sExam.Read();
		if (Token.code == 'P' && Token.value == 11)                           //:=
		{
			Token = sExam.Read();
			EXPRESSION();
			st.MidCode(6);
			if (Token.code == 'P' && Token.value == 13) {
				Token = sExam.Read();
			}
			else
				ERR_EXI();
		}
		else
			ERR_EXI();
	}
	else
		ERR_EXI();
};

//void Syntax::COM_SENTENCE()
//{
//	if (Token.code == 8)                                //begin
//	{
//		Token = sExam.Read();
//		SEN_SEQUENCE();
//		if (Token.code == 9)                            //end
//			Token = sExam.Read();
//		else
//			ERR_EXI();
//	}
//	else
//		ERR_EXI();
//};

void Syntax::EXPRESSION() {
	ITEM();
	while (Token.code == 'P' && (Token.value == 8 || Token.value == 1)) {
		int flag = Token.value;
		Token = sExam.Read();
		ITEM();
		if (flag == 8)st.MidCode(2);                        /////////////////+
		else st.MidCode(3);//   -
	}
}

void Syntax::ITEM() {
	DIVISOR();
	while (Token.code == 'P' && (Token.value == 2 || Token.value == 9)) {
		int flag = Token.value;
		Token = sExam.Read();
		DIVISOR();
		if (flag == 9)st.MidCode(4);                        /////////////////*
		else st.MidCode(5);//
	}
}

void Syntax::DIVISOR() {
	if (Token.code == 'I' || Token.code == 'C' || Token.code == 'F') {
		st.JudgePush(Token);
		Token = sExam.Read();
		return;
	}
	else if (Token.code == 'P' && Token.value == 3) {
		Token = sExam.Read();
		EXPRESSION();
		if (Token.code == 'P' && Token.value == 4) {
			Token = sExam.Read();
			return;
		}
		else
			ERR_EXI();
	}
	else
		ERR_EXI();
}

void Syntax::IF_CONDITION() {
	if (Token.code == 'K' && Token.value == 12) {
		Token = sExam.Read();
		if (Token.code == 'P' && Token.value == 3) {
			Token = sExam.Read();
			EXPRESSION();
			RELATION_SEQUENCE();
			if (Token.code == 'P' && Token.value == 4) {
				st.MidCode(7);
				Token = sExam.Read();
				STATEMENT();
				ELSE_CONDITION();
				st.MidCode(12);
			}
			else
				ERR_EXI();
		}
		else
			ERR_EXI();
	}
	else
		ERR_EXI();
}

void Syntax::ELSE_CONDITION() {
	if (Token.code == 'K' && Token.value == 14) {
		st.MidCode(8);
		Token = sExam.Read();
		STATEMENT();
	}
}

void Syntax::WHILE_LOOP() {
	if (Token.code == 'K' && Token.value == 5) {
		st.MidCode(9);
		Token = sExam.Read();
		if (Token.code == 'P' && Token.value == 3) {
			Token = sExam.Read();
			EXPRESSION();
			RELATION_SEQUENCE();
			if (Token.code == 'P' && Token.value == 4) {
				st.MidCode(10);
				Token = sExam.Read();
				STATEMENT();
				st.MidCode(11);
			}
			else
				ERR_EXI();
		}
		else
			ERR_EXI();
	}
	else
		ERR_EXI();
}

void Syntax::STATEMENT() {
	if (Token.code == 'K' && Token.value == 12) {
		Token = sExam.Read();
		IF_CONDITION();
	}
	else if (Token.code == 'I') {
		EVA_SENTENCE();
	}
	else if (Token.code == 'K' && Token.value == 5) {
		Token = sExam.Read();
		WHILE_LOOP();
	}
	else if (Token.code == 'P' && Token.value == 15) {
		Token = sExam.Read();
		FUN_BODY();
		if (Token.code == 'P' && Token.value == 16) {
			Token = sExam.Read();
			return;
		}
		else
			ERR_EXI();
	}
	else
		ERR_EXI();
}

void Syntax::RELATION_SEQUENCE() {
	if (Token.code == 'P') {
		switch (Token.value) {
		case(5):Token = sExam.Read(); EXPRESSION(); st.MidCode(17); break;
		case(6):Token = sExam.Read(); EXPRESSION(); st.MidCode(15);  break;
		case(7):Token = sExam.Read(); EXPRESSION(); st.MidCode(14);  break;
		case(10):Token = sExam.Read(); EXPRESSION(); st.MidCode(13);  break;
		case(17):Token = sExam.Read(); EXPRESSION(); st.MidCode(16); break;
		default:return;
		}
	}
}





