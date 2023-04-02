#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <iterator>
#include <functional>

using std::vector;
using std::string;
using std::pair;
using std::fstream;

class STATE {
public:
	STATE() {};
	string currState;
	//Пара <алфавит:указатель на переход>
	vector<pair<string, STATE*>> nextState;
};

class NFA
{

};


class DFA
{
public:
	//DFA(NFA nfa);
	DFA() {
	};

	void init(string fileName);
	bool go(string line);

private:
	vector<string> alphabet, validStates;
	vector<pair<string, STATE*>> allStates;
	int numbStates;
	//Таблица состояний, где пара - [ символ алфавита : состояние ] 
	vector<vector<pair<string, string>>> statusTable;
	void get_all_state(string fileName)
	{
		fstream file;
		file.open(fileName);

		string tmp, tmp2, alph;
		file >> numbStates;
		file >> tmp;
		//получаем алфавит
		for (int i = 1; i < tmp.size(); i++)
		{
			if (tmp[i] != ',' and tmp[i] != ']')
				tmp2 += tmp[i];
			else {
				alphabet.push_back(tmp2);
				tmp2.clear();
			}
		}
		//Получаем имя состояния и выделяем память для структуры этого состояния
		for (int i = 0; i < numbStates; i++)
		{
			file >> tmp;
			int j = 0;
			tmp2.clear();
			while (tmp[j] != '=')
			{
				tmp2 += tmp[j];
				j++;
			}
			STATE* newState = new STATE;
			newState->currState = tmp2;
			allStates.push_back(pair<string, STATE*>{tmp2, newState});

			//выделяем из строки состояния для перерходов
			vector<pair<string, string>> tmpBox;
			tmp2.clear();
			j+=2;
			for(int i = 0; i< alphabet.size(); i++)
			{
				while (tmp[j] != ':')
				{
					tmp2 += tmp[j];
					j++;
				}
				alph = tmp2;
				tmp2.clear();
				j += 2;
				while (tmp[j] != ']')
				{
					if (tmp[j] == ',')
					{
						tmpBox.push_back(make_pair(alph, tmp2));
						tmp2.clear();
						j++;
						continue;
					}
					tmp2 += tmp[j];
					j++;
				}
				tmpBox.push_back(make_pair(alph, tmp2));
				j += 2;
				tmp2.clear();
			}
			statusTable.push_back(tmpBox);
		}

		fill_states();

		//Сохраняем допустимые состояния
		file >> tmp;
		int i = 1;
		while (true)
		{
			if (tmp[i] == ']')
			{
				validStates.push_back(tmp2);
				tmp2.clear();
				break;
			}
			if (tmp[i] == ',')
			{
				validStates.push_back(tmp2);
				tmp2.clear();
				i++;
				continue;
			}
			else if (tmp[i] != ',')
			{
				tmp2 += tmp[i];
				i++;
			}
		}
	}

	void fill_states()
	{
		//Проходим по статус тейблу и для каждого состояния присваиваем соответсвующей структуре адрес нужного состояния
		for (int i = 0; i < allStates.size(); i++)
		{
			STATE* cur = allStates[i].second;
			for (int j = 0; j < statusTable[i].size(); j++)
			{
				STATE* next = _find(statusTable[i][j].second);
				cur->nextState.push_back(make_pair(statusTable[i][j].first, next));
			}
		}
		return;
	}

	STATE* _find(string state)
	{
		for (int i = 0; i < allStates.size(); i++)
		{
			if (allStates[i].first == state)
				return allStates[i].second;

		}
	}
	
};