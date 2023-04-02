#include "Header.h"

using namespace std;

void DFA::init(string fileName)
{
	get_all_state(fileName);
	return;
}

bool DFA::go(string line)
{
	string symb;
	STATE* current = allStates[0].second;
	for (int i = 0; i < line.size(); i++)
	{
		symb = line[i];
		for (int j = 0; j < current->nextState.size(); j++)
		{
			if (current->nextState[j].first == symb)
			{
				current = current->nextState[j].second;
				break;
			}
			else if (j == current->nextState.size() - 1)
			{
				cout << endl << "The symbol " << symb << " is not included in the alphabet set!" << endl;
				return false;
			}
		}
	}
	for (int i = 0; i < validStates.size(); i++)
	{
		if (current->currState == validStates[i])
			return true;
		if (i == validStates.size() - 1)
			return false;
	}
	return true;
}

//void DFA::fill_DFA(string fileName)
//{
//	fstream file;
//	file.open(fileName);
//	if (!file.is_open())
//	{
//		cout << "Can`t open source file!" << endl;
//		return;
//	}
//	
//	string tmp;
//	file >> numbStates;
//	file >> tmp;
//	while (tmp != "\n")
//	{
//		alphabet.push_back(tmp);
//		file >> tmp;
//	}
//
//	Node state;
//	for (int i = 0; i < numbStates; i++)
//	{
//		file >> tmp;
//		if (i == 0)
//		{
//			pars_State(tmp, state);
//			states.push_back(state);
//		}
//		else
//		{
//			pars_State(tmp, state);
//			states.push_back(state);
//		}
//	}
//	file >> tmp;
//	string validState;
//	for (int i = 1; i < tmp.size()-1; i++)
//	{
//		if (tmp[i] != ',')
//			validState += tmp[i];
//		else {
//			acceptableStates.push_back(validState);
//			validState.clear();
//		}
//	}
//	return;
//}
//
//void DFA::pars_State(string str, Node& node)
//{
//	string state, alph;
//	state.reserve(10);
//	int i = 0;
//	//получаем символ состояния
//	while (true)
//	{
//		if (str[i] != '=')
//		{
//			state += str[i];
//			i++;
//		}
//		else {
//			node.currState = state;
//			state.clear();
//			i+=2;
//			break;
//		}
//	}
//	while (true)
//	{
//		//Получаем описание состояния
//		if (str[i] == '}')
//			break;
//		if (str[i] != ':')
//		{
//			state += str[i];
//			i++;
//		}
//		else {
//			//Получаем все состояния в которые можем перейти
//			vector<string>::iterator beg = alphabet.begin(),	
//				en = alphabet.end();
//			en = find(beg, en, state);
//			if (en == alphabet.end())
//			{
//				cout << "ERROR!";
//				return;
//			}
//			
//			i+=2;
//			alph = state;
//			state.clear();
//			while (true)
//			{
//				if (str[i] == ']')
//				{
//					i+=2;
//					node.nextState.push_back(make_pair(alph, state));
//					state.clear();
//					break;
//				}
//				if (str[i] != ',')
//					state += str[i];
//				else {
//					node.nextState.push_back(make_pair(alph, state));
//					state.clear();
//				}
//				i++;
//			}
//		}
//	}
//}