/**********************************
*������������NFA����DFA���Ӽ������㷨
***********************************/

#include<cstdio>
#include<fstream>
#include<iostream>
#include<bitset>
#include<vector>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<queue>
#include<set>
#define MAX_NFA_STATES 10//NFA�����״̬��
#define MAX_ALPHABET_SIZE 10//��ĸ������ߴ�
using namespace std;
//NFA״̬����
class NFAstate{
	public:
        int transitions[MAX_ALPHABET_SIZE][MAX_NFA_STATES];
        NFAstate()
        {
            for (int i = 0; i < MAX_ALPHABET_SIZE; i++)
                for (int j = 0; j < MAX_NFA_STATES; j++)
                    transitions[i][j] = -1;
        }
}*NFAstates;
// DFA״̬����
struct DFAstate
{
        bool finalState;
        bitset<MAX_NFA_STATES> constituentNFAstates;
        bitset<MAX_NFA_STATES> transitions[MAX_ALPHABET_SIZE];
        int symbolicTransitions[MAX_ALPHABET_SIZE];
};
set<int> NFA_finalStates;//����̬����
vector<int> DFA_finalStates;
vector<DFAstate*> DFAstates;
queue<int> incompleteDFAstates;
int N, M; // N -> ״̬��, M -> ������ĸ��Ĵ�С
// �ҳ�NFA״̬"state" ��epsilon closure ����������"closure"
void epsilonClosure(int state, bitset<MAX_NFA_STATES> &closure)
{
    for (int i = 0; i < N && NFAstates[state].transitions[0][i] != -1; i++)
        if (closure[NFAstates[state].transitions[0][i]] == 0)
        {
            closure[NFAstates[state].transitions[0][i]] = 1;
            epsilonClosure(NFAstates[state].transitions[0][i], closure);
        }
}
// �ҳ�NFA״̬��"state" ��epsilon closure ����������"closure"
void epsilonClosure(bitset<MAX_NFA_STATES> state,
        bitset<MAX_NFA_STATES> &closure)
{
    for (int i = 0; i < N; i++)
        if (state[i] == 1)
            epsilonClosure(i, closure);
}
//�ܹ���״̬X����ͨ�����A��ת�������NFA״̬��Y
void NFAmove(int X, int A, bitset<MAX_NFA_STATES> &Y)
{
    for (int i = 0; i < N && NFAstates[X].transitions[A][i] != -1; i++)
        Y[NFAstates[X].transitions[A][i]] = 1;
}
//�ܹ���״̬��X����ͨ�����A��ת�������NFA״̬��Y
void NFAmove(bitset<MAX_NFA_STATES> X, int A, bitset<MAX_NFA_STATES> &Y)
{
    for (int i = 0; i < N; i++)
        if (X[i] == 1)
            NFAmove(i, A, Y);
}
int main()
{
    int i, j, X, Y, A, T, F, D;
    //���ļ��ж�ȡNFA
    ifstream fin("NFA.txt");
    fin >> N >> M;
    NFAstates = new NFAstate[N];
    fin >> F;
    for (i = 0; i < F; i++)
    {
        fin >> X;
        NFA_finalStates.insert(X);
    }
    fin >> T;
    while (T--)
    {
        fin >> X >> A >> Y;
        for (i = 0; i < Y; i++)
        {
            fin >> j;
            NFAstates[X].transitions[A][i] = j;
        }
    }
    fin.close();
    // ������ʵ�DFA
    D = 1;
    DFAstates.push_back(new DFAstate);
    DFAstates[0]->constituentNFAstates[0] = 1;
    epsilonClosure(0, DFAstates[0]->constituentNFAstates);
    for (j = 0; j < N; j++)
        if (DFAstates[0]->constituentNFAstates[j] == 1 && NFA_finalStates.find(
                j) != NFA_finalStates.end())
        {
            DFAstates[0]->finalState = true;
            DFA_finalStates.push_back(0);
            break;
        }
    incompleteDFAstates.push(0);
    while (!incompleteDFAstates.empty())
    {
        X = incompleteDFAstates.front();
        incompleteDFAstates.pop();
        for (i = 1; i <= M; i++)
        {
            NFAmove(DFAstates[X]->constituentNFAstates, i,
                    DFAstates[X]->transitions[i]);
            epsilonClosure(DFAstates[X]->transitions[i],
                    DFAstates[X]->transitions[i]);
            for (j = 0; j < D; j++)
                if (DFAstates[X]->transitions[i]
                        == DFAstates[j]->constituentNFAstates)
                {
                    DFAstates[X]->symbolicTransitions[i] = j;
                    break;
                }
            if (j == D)
            {
                DFAstates[X]->symbolicTransitions[i] = D;
                DFAstates.push_back(new DFAstate);
                DFAstates[D]->constituentNFAstates
                        = DFAstates[X]->transitions[i];
                for (j = 0; j < N; j++)
                    if (DFAstates[D]->constituentNFAstates[j] == 1
                            && NFA_finalStates.find(j) != NFA_finalStates.end())
                    {
                        DFAstates[D]->finalState = true;
                        DFA_finalStates.push_back(D);
                        break;
                    }
                incompleteDFAstates.push(D);
                D++;
            }
        }
    }
    // ���DFA
    ofstream fout("DFA.txt");
    fout << D << " " << M << "\n" << DFA_finalStates.size();
    for (vector<int>::iterator it = DFA_finalStates.begin(); it
            != DFA_finalStates.end(); it++)
        fout << " " << *it;
    fout << "\n";
    for (i = 0; i < D; i++)
    {
        for (j = 1; j <= M; j++)
            fout << i << " " << j << " "
                    << DFAstates[i]->symbolicTransitions[j] << "\n";
    }
    fout.close();
    return 0;
}