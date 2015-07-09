/*
编译原理实验1：编程实现DFA
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
/*DFA类*/
class DFA{
public:
	DFA(){
		read();
	}
	string _states;//状态集
	char _start_state;//开始状态
	string _end_states;//结束状态集
	string _alph;//字符集
	vector<TranTable> _trans;//转移函数
	/*从文件DFA.in读入DFA信息*/
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


	/*识别字符串*/
	void ident(){
		cout << "请输入字符串：" << endl;
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
			cout << "该自动机识别此字符串" << endl;
		else
			cout << "该自动机不识别此字符串" << endl;
	}
	/*转移函数*/
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
	/*DFA语言集列表显示*/
	void traversal(char p, int N, string strass = ""){
		if (p == 'N' || N < 0) return;
		N--;
		if (_end_states.find(p) != _end_states.npos)
			cout << "该自动机识别字符串" << strass << endl;
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
	cout << "请输入N" << endl;
	cin >> N;
	dfa.traversal(dfa._start_state,N);
	dfa.write();
	system("pause");
	return 0;
}