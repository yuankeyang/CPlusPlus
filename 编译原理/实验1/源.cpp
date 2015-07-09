/*
����ԭ��ʵ��1�����ʵ��DFA
*/
#include<iostream>
#include<string>
#include<vector>
#include<fstream>
using namespace std;

class TranTable{
public:
	char current;
	char next;
	char input;
	TranTable(char current, char input, char next){
		this->current = current;
		this->input = input;
		this->next = next;
	}
};
/*DFA��*/
class DFA{
public:
	DFA(){
		read();
	}
	string _states;//״̬��
	char _start_state;//��ʼ״̬
	string _end_states;//����״̬��
	string _alph;//�ַ���
	vector<TranTable> _trans;//ת�ƺ���
	/*���ļ�DFA.in����DFA��Ϣ*/
	void read(){
		char temp[10];
		fstream ff("DFA3.in", ios::in);
		ff.getline(temp, 10);
		_alph = temp;
		ff.getline(temp, 10);
		_states = temp;
		ff.getline(temp, 10);
		_start_state = temp[0];
		ff.getline(temp, 10);
		_end_states = temp;
		while (!ff.eof())
		{
			ff.getline(temp,10);
			TranTable Temp(temp[0], temp[1], temp[2]);
			_trans.push_back(Temp);
		}
	}


	/*ʶ���ַ���*/
	void ident(){
		cout << "�������ַ�����" << endl;
		string str;
		cin >> str;
		int i = 0;
		char current = _start_state;
		while (i<str.length())
		{
			current = this->move(current, str[i]);
			if (current == 'N') break;
			i++;
		}
		if (_end_states.find(current) != _end_states.npos)
			cout << "���Զ���ʶ����ַ���" << endl;
		else
			cout << "���Զ�����ʶ����ַ���" << endl;
	}
	/*ת�ƺ���*/
	char move(char c, char I){
		for (int i = 0; i < _trans.size(); i++){
			if (_trans[i].current == c && _trans[i].input == I){
				return _trans[i].next;
			}
		}
		return 'N';
	}
	void write(){
		fstream ff("DFA3.out", ios::out);
		ff << _alph << endl;
		ff << _states << endl;
		ff << _end_states << endl;
		for (int i = 0; i < _trans.size(); i++){
			ff << _trans[i].current << _trans[i].input << _trans[i].next << endl;
		}
		ff.close();
	}
	/*DFA���Լ��б���ʾ*/
	void traversal(char p, int N, string strass = ""){
		if (p == 'N' || N < 0) return;
		N--;
		if (_end_states.find(p) != _end_states.npos)
			cout << "���Զ���ʶ���ַ���" << strass << endl;
		else if (_end_states.find(p) == _end_states.npos && N < 0)
			return;
		for (int i = 0; i < _alph.length(); i++){
			string temp;
			temp = strass;
			strass += _alph[i];
			traversal(move(p, _alph[i]), N, strass);
			strass = temp;
		}
	}
};
int main(){
	DFA dfa;
	dfa.ident();
	int N;
	cout << "������N" << endl;
	cin >> N;
	dfa.traversal(dfa._start_state,N);
	dfa.write();
	system("pause");
	return 0;
}