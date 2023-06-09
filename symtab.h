#pragma once

#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<string>
#include<vector>
#include<sstream>
#include<stack>
#include<fstream>
#include<utility>
#include<cctype>
#include<map>
#include "Token.h"

using namespace std;
//������TOKENʱ���ж��Ƿ��Ǳ�ʶ��������Ǳ�ʶ����������ʲô�����أ�������������ȷ��������Ϣ��Ӧ������ṹ

typedef struct TYPnode* PTYnode; //���ͱ���Ķ���
typedef struct Rnode* PTRnode; //�ṹ�����Ķ���
typedef struct LENnode* PTLnode; //���ȱ���Ķ���
typedef struct Cnode* PTCnode; //��������Ķ���
typedef struct Vnode* PTVnode; //��������Ķ���
typedef struct Pnode* PTPnode; //��������Ķ���
typedef struct Fnode* PTFnode; //��������Ķ���
typedef struct AInode* PTAInode; //�������Ķ���
typedef struct SYNnode* PTSYNnode; //���ű���Ķ���
typedef struct INVnode* PTINVnode; //�м��������Ķ���
typedef struct Qnode* PTQnode; //��Ԫʽ���Ķ���

struct DAGNode {
	int _id;
	string _operator;
	vector<string> _mark;
	int lchild;
	int rchild;
	DAGNode() {
		_id = 0;
		_operator = "";
		lchild = -1;
		rchild = -1;
	}
};

typedef struct LENnode {
	int Len;//���ȴ�С
	PTLnode LNext;//ָ����һ���ڽӵ�
}LENNode;

typedef struct Cnode {
	double Len;    //������С
	PTCnode CNext;//ָ����һ���ڽӵ�
}CNode;

typedef struct Vnode {
	int Vdeep;    //���ڲ���
	int Vstart;    //�洢�Ŀ�ʼ��Ԫ
	PTVnode VNext;//ָ����һ���ڽӵ�
}VNode;

typedef struct Pnode {
	string Pname;  //������
	PTYnode Ptype;//��������
	string PCat;//��������
	PTVnode Pvar;   //�����ķ���
	PTPnode PNext;//ָ����һ���ڽӵ�
}PNode;

typedef struct Fnode {
	int deep;//��������
	int F_off;//�ù���������������ʼ��Ԫ��Ըù���ֵ����ͷλ��
	int FN; //��������
	PTSYNnode entry;                                 ///////////////////////////ywf///�Ǹ�entry
	PTPnode	Paral;//ָ�������
	PTFnode FNext;//ָ����һ���ڽӵ�
}FNode;
//����Ϊ����������Ϣ��

typedef struct Rnode {
	string Id;//�ṹ����
	int Off;//����
	PTYnode IdType;//id�ĳɷ�����
	PTRnode RNext;//ָ����һ���ڽӵ�
}RNode;

typedef struct AInode {
	int SubScr;  //�±�   �±��ӦС��//c�����Զ����0
	int SuperScr;  //�ϱ�
	PTYnode AType;//�����������ͣ�ָ�����ͱ�
	int UnitLen;   //һ�����鵥Ԫ�ĳ���
	PTAInode ANext;//ָ����һ��������ڽӵ�
}AINode;

typedef struct TYPnode {
	char type;//����
	PTAInode PTAinfl;      //ָ�������ͷָ��
	PTRnode PTRinfl;//ָ��ṹ��ͷָ��  ;����һ�����ͱ��ͷ�ڵ㣬���治��type��ֻ��һ�������ͷָ���һ���ṹ��ͷָ�룬������ͷָ�������ҵ��������ݽṹ
	PTYnode TNext;//ָ����һ���ڽӵ�
}TYPNode;

typedef struct SYNnode {
	string TName;//��ʶ��Դ��
	PTYnode Type; //��token��ʶ������,ָ�����ͱ����ͱ�ǰ�����Ѿ�������ˣ���Ӧ�Ż�������i,b,......
	string TCat;      //��token����
	union {
		PTLnode Lform;//ָ��������Ϣ��
		PTCnode Cform;
		PTVnode Vform;
		PTFnode Fform;
	};
	char AInformation;                //�ñ�ʶ���Ļ�Ծ��Ϣ
	PTSYNnode SNext;//ָ����һ���ڽӵ�
}SYNNode;

typedef struct INVnode {
	string IName;//�м������
	string IType;//�м������
	PTINVnode INVNext;//ָ����һ���ڽӵ�
	char AInformation;                //�ñ�ʶ���Ļ�Ծ��Ϣ
}INVNode;

typedef struct Qnode {   //��Ԫʽ�ڵ�
	string Operater;
	string Obj1;
	//char Information1; //������1�Ļ�Ծ��Ϣ
	string Obj2;
	//char Information2; //������2�Ļ�Ծ��Ϣ
	string result;
	//char Information3;  //�����Ԫ�Ļ�Ծ��Ϣ
	char Position;     //����Ԫʽ�ڵ��ڻ��������λ����Ϣ begin end midprocess
	PTQnode QNext;//ָ����һ���ڽӵ�
}QNode;

class SymTable
{
public:
	friend class Syntax;      //��Ԫ�����﷨�������ֿ��Ե�����������еĳ�Ա
	SymTable();
	~SymTable();
	string token_to_str(TokenType&);
	void Init(string*, string*, string*, string*);
	void MidCode(int k);
	void ADDQNode(string op, string ob1, string ob2, string re);//������Ԫʽ�ڵ�
	string ADDInvNode(string type);//�����м�����ڵ�
	string JudgeIType(string n1, string n2);//�����������ֵ����ű���Ѱ���м����������
	string TopPop();//ȡ������ջ�����Ų��ҵ���ջ��
	void JudgePush(TokenType t1);
	void ErrorJudge1(TokenType t1);  //�ض���
	void ErrorJudge2(string str);  //δ����
	/////////////ywf
	void happily();
	void insert(string token);
	PTQnode fanz(PTQnode head);
	void exc(string str, int i);
	//int numcge(string s, int i);
	PTSYNnode screat();
	void pcreat();
	void lcreat();
	void fcreat();
	void ccreat();
	void vcreat();
	void OutPutfhb();
	void OutPutMid();
	void DividMid();//���ֻ�����
private:
	string* keymap;
	string* Imap;        //��ʶ����I
	string* Cmap;        //��������C
	string* Fmap;
	int off_set = 5;
	PTSYNnode SYNHead;//���ű�
	PTLnode	LHead;  //���ȱ�
	PTFnode FHead;	//������
	PTCnode	CHead;//������
	PTVnode	VHead;//������
	PTINVnode INVHead;//�м������
	int NumInvNode;//�м��������
	PTQnode Qhead;  //��Ԫʽͷָ��
	stack<string>Smean;//����Ķ�ջ

		//////////////////////////�������ָ��
	//int off_set = 5;
	PTYnode THead;   //���ͱ�ͷ
	PTSYNnode nodes;//���ű�
	PTPnode nodep;	//������
	PTLnode	nodel;  //���ȱ�
	PTFnode nodef;	//������
	PTCnode	nodec;//������
	PTVnode	nodev;//������

	vector<DAGNode> m_dag;
	map<string, int> m_map;
	map<string, int> m_ope;
protected:
	DAGNode& Find_cur(int id) {
		for (auto it = m_dag.begin(); it != m_dag.end(); it++) {
			if (it->_id == id) {
				return (*it);
			}
		}
	}

	void Erase(string str) { //������нڵ�
		if (!m_map.count(str))return;
		int tmp = m_map.find(str)->second;
		if (Find_cur(tmp)._mark[0] != str) {
			for (auto it = Find_cur(tmp)._mark.begin(); it != Find_cur(tmp)._mark.end(); it++) {
				if ((*it) == str) {
					Find_cur(tmp)._mark.erase(it);
					break;
				}
			}
		}
	}

	void Add_Edge(Qnode node) { //��ӱ߼����
		if (node.Operater == "=") {
			if (m_map.count(node.Obj1)) {
				Erase(node.result);
				DAGNode tmp = Find_cur(m_map.find(node.Obj1)->second);
				tmp._mark.push_back(node.result);
				if (tmp._mark[0][0] == 't' && node.result[0] != 't') {
					auto it = tmp._mark.end();
					it--;
					swap(Find_cur(m_map.find(node.Obj1)->second)._mark[0], *(it));
				}
				m_map.insert(make_pair(node.result, tmp._id));
			}
			else {
				DAGNode tmp;
				tmp._id = m_dag.size();
				tmp._mark.push_back(node.Obj1);
				tmp._mark.push_back(node.result);
				//cout << node.result << endl;
				//cout << node.Obj1 << "   " << node.result << endl;
				Erase(node.result);
				m_dag.push_back(tmp);
				m_map.insert(make_pair(node.Obj1, tmp._id));
				m_map.insert(make_pair(node.result, tmp._id));
			}
		}
		else if (m_ope.count(node.Operater)) {
			if (!m_map.count(node.Obj1)) {
				DAGNode tmp;
				tmp._id = m_dag.size();
				//cout << tmp._id<<"   ";
				tmp._mark.push_back(node.Obj1);
				m_dag.push_back(tmp);
				m_map.insert(make_pair(node.Obj1, tmp._id));
			}
			if (!m_map.count(node.Obj2)) {
				DAGNode tmp;
				tmp._id = m_dag.size();
				//cout << tmp._id << endl;
				tmp._mark.push_back(node.Obj2);
				m_dag.push_back(tmp);
				m_map.insert(make_pair(node.Obj2, tmp._id));
			}
			if (isdigit(node.Obj1[0]) && isdigit(node.Obj2[0])) {
				float obj1 = stof(node.Obj1);
				float obj2 = stof(node.Obj2);
				if (node.Operater == "+")
					obj1 += obj2;
				else if (node.Operater == "-")
					obj1 -= obj2;
				else if (node.Operater == "*")
					obj1 *= obj2;
				else if (node.Operater == "/")
					obj1 /= obj2;
				else if (node.Operater == "==")
					obj1 = (obj1 == obj2);
				else if (node.Operater == "<=")
					obj1 = (obj1 <= obj2);
				else if (node.Operater == ">=")
					obj1 = (obj1 >= obj2);
				else if (node.Operater == "<")
					obj1 = (obj1 < obj2);
				else if (node.Operater == ">")
					obj1 = (obj1 > obj2);
				string str = to_string(obj1);
				if (m_map.count(str)) {
					Erase(node.result);
					DAGNode tmp = Find_cur(m_map.find(str)->second);
					tmp._mark.push_back(node.result);
					if (tmp._mark[0][0] == 't' && node.result[0] != 't') {
						auto it = tmp._mark.end();
						it--;
						swap(Find_cur(m_map.find(node.Obj1)->second)._mark[0], *(it));
					}
					m_map.insert(make_pair(node.result, tmp._id));
				}
				else {
					DAGNode tmp;
					tmp._id = m_dag.size();
					tmp._mark.push_back(str);
					tmp._mark.push_back(node.result);
					Erase(node.result);
					m_dag.push_back(tmp);
					m_map.insert(make_pair(str, tmp._id));
					m_map.insert(make_pair(node.result, tmp._id));
				}
			}
			else {
				bool flag = false;
				for (auto it = m_dag.begin(); it != m_dag.end(); it++) {
					if (m_map.count(node.Obj1) && m_map.count(node.Obj2)) {
						if ((*it)._operator == node.Operater && (*it).lchild == m_map.find(node.Obj1)->second &&
							(*it).rchild == m_map.find(node.Obj2)->second && (*it).lchild != -1 && (*it).rchild != -1) {
							Erase(node.result);
							it->_mark.push_back(node.result);
							if (it->_mark[0][0] == 't' && node.result[0] != 't') {
								auto it2 = it->_mark.end();
								it2--;
								swap(Find_cur(m_map.find(node.Obj1)->second)._mark[0], *(it2));
							}
							m_map.insert(make_pair(node.result, it->_id));
							flag = true;
							break;
						}
					}
				}
				if (!flag) {
					//cout << 1 << endl;
					DAGNode tmp;
					tmp._id = m_dag.size();
					tmp._operator = node.Operater;
					tmp.lchild = m_map.find(node.Obj1)->second;
					tmp.rchild = m_map.find(node.Obj2)->second;
					//cout << tmp.lchild << "   " << tmp.rchild << endl;
					tmp._mark.push_back(node.result);
					Erase(node.result);
					m_dag.push_back(tmp);
					m_map.insert(make_pair(node.result, tmp._id));

				}
			}
		}
	}
public:
	void SetUp() { //����DAGͼ�������Ż�
		Qnode* pq = NULL;
		if (Qhead->QNext) {
			pq = Qhead->QNext;
		}
		Qnode* pq_replace_head = new Qnode();
		Qnode* pq_replace_it = pq_replace_head;
		while (pq != NULL) {
			m_dag.clear();
			m_map.clear();
			Qnode tmpq;
			while (pq && (pq->Position != 'b' && pq->Position != 'e' && pq->Position != 'm')) {
				Qnode* p = new Qnode();
				pq_replace_it->QNext = p;
				pq_replace_it = pq_replace_it->QNext;
				pq_replace_it->QNext = NULL;
				pq_replace_it->Obj1 = pq->Obj1;
				pq_replace_it->Obj2 = pq->Obj2;
				pq_replace_it->Operater = pq->Operater;
				pq_replace_it->result = pq->result;
				pq = pq->QNext;
			}
			if (!m_ope.count(pq->Operater)) {
				Qnode* p = new Qnode();
				pq_replace_it->QNext = p;
				pq_replace_it = pq_replace_it->QNext;
				pq_replace_it->QNext = NULL;
				pq_replace_it->Obj1 = pq->Obj1;
				pq_replace_it->Obj2 = pq->Obj2;
				pq_replace_it->Operater = pq->Operater;
				pq_replace_it->result = pq->result;
				pq = pq->QNext;
				continue;
			}
			//Qnode* pq_replace_per = Qhead;
			if (pq->Position == 'b') {
				//while (pq_replace_per->QNext != pq) {
				//	pq_replace_per = pq_replace_per->QNext;
				//}
				Add_Edge(*pq);
				pq = pq->QNext;
			}
			while (pq && pq->Position != 'b') {
				if (!m_ope.count(pq->Operater)) {
					tmpq.Obj1 = pq->Obj1;
					tmpq.Obj2 = pq->Obj2;
					tmpq.Operater = pq->Operater;
					tmpq.result = pq->result;
					pq = pq->QNext;
					continue;
				}
				Add_Edge(*pq);
				pq = pq->QNext;
			}
			for (auto it = m_dag.begin(); it != m_dag.end(); it++) {
				if (it->lchild == -1 && it->rchild == -1 && it->_mark.size() > 1) {
					auto it2 = it->_mark.begin();
					it2++;
					for (; it2 != it->_mark.end(); it2++) {
						if ((*it2)[0] != 't') {
							Qnode* p = new Qnode();
							pq_replace_it->QNext = p;
							pq_replace_it = pq_replace_it->QNext;
							pq_replace_it->QNext = NULL;
							pq_replace_it->Operater = "=";
							pq_replace_it->result = (*it2);
							pq_replace_it->Obj1 = it->_mark[0];
							pq_replace_it->Obj2 = "_";
						}
					}
				}
				else if (it->lchild != -1 && it->rchild != -1) {
					Qnode* p = new Qnode();
					pq_replace_it->QNext = p;
					pq_replace_it = pq_replace_it->QNext;
					pq_replace_it->QNext = NULL;
					pq_replace_it->Operater = it->_operator;
					pq_replace_it->Obj1 = Find_cur(it->lchild)._mark[0];
					//cout << it->_operator << "  " << Find_cur(it->rchild)._id << endl;
					pq_replace_it->Obj2 = Find_cur(it->rchild)._mark[0];
					//cout << pq_replace_it->Obj1 << "  " << pq_replace_it->Obj2 <<"  "<< pq_replace_it->result << endl;
					pq_replace_it->result = it->_mark[0];
					if (it->_mark.size() > 1) {
						auto it2 = it->_mark.begin();
						it2++;
						for (; it2 != it->_mark.end(); it2++) {
							if ((*it2)[0] != 't') {
								Qnode* p = new Qnode();
								pq_replace_it->QNext = p;
								pq_replace_it = pq_replace_it->QNext;
								pq_replace_it->QNext = NULL;
								pq_replace_it->Operater = "=";
								pq_replace_it->result = (*it2);
								pq_replace_it->Obj1 = it->_mark[0];
								pq_replace_it->Obj2 = "_";

							}
						}
					}
				}
			}
			if (tmpq.Operater != "") {
				Qnode* p = new Qnode();
				pq_replace_it->QNext = p;
				pq_replace_it = pq_replace_it->QNext;
				pq_replace_it->QNext = NULL;
				pq_replace_it->Operater = tmpq.Operater;
				pq_replace_it->result = tmpq.result;
				pq_replace_it->Obj1 = tmpq.Obj1;
				pq_replace_it->Obj2 = tmpq.Obj2;
			}
		}
		Qhead = pq_replace_head;
	}
};



