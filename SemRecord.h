#include <unordered_map>
#include <queue>
#include <utility>

using namespace std;


class SemSys{
protected:
	//SemRecord* SR;
	queue<int> CONS;   //������
	queue<string> RCONS;   //��ʵ����
	queue<char> CT;   //�ַ���
	queue<string> ST;   //�ַ�����
	unordered_map<string, int> KEY;   //�ؼ��ֱ�
	unordered_map<string, int> PW;   //�����
};
