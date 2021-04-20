#include <iostream>
#include <windows.h>
#include <cmath>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>
#include <map>
#include <algorithm>

using namespace std;

#define _CRT_SECURE_NO_WARNINGS

vector<vector<uint32_t>>& multiplyMatr(vector<vector<uint32_t>>& A, vector<vector<uint32_t>>& B);
void splitByDelimeter(string line, vector<uint32_t>& initialState);

class Automate {
	
	public:
		vector<uint32_t> initialState	= vector<uint32_t>();
		vector<uint32_t> inputValues	= vector<uint32_t>();

		void initializeMatr(ifstream* file, uint32_t rows, uint32_t columns, vector<vector<uint32_t>>& matr) {

			string str;
			cout << "HEy" << endl;
			for (uint32_t i = 0; i < rows; ++i) {
				char* next_token1 = NULL;
				getline((*file), str);
				char* s = new char[str.size() + 1];
				strncpy_s(s, str.size() + 1, str.c_str(), str.size() + 1);
				char* p = strtok_s(s, " ", &next_token1);
				//char* buf = strtok(str, " .,!?\n");
				matr.push_back(vector<uint32_t>());
				//int j = 0;
				for (int j = 0; j < columns; ++j) {
					matr[i].push_back(stoi(p));
					cout << stoi(p) << endl;
					p = strtok_s(NULL, " ", &next_token1);
				}
			}
		}
		void initializeMatr(ifstream* file, uint32_t rows, uint32_t columns, vector<uint32_t>& matr) {

			string str;
			for (uint32_t i = 0; i < rows; ++i) {
				char* next_token1 = NULL;
				
				getline((*file), str);
				cout << str << endl;
				cout << "HEy" << endl;
				char* s = new char[str.size() + 1];
				strncpy_s(s, str.size() + 1, str.c_str(), str.size() + 1);
				char* p = strtok_s(s, " ", &next_token1);
				//char* buf = strtok(str, " .,!?\n");
				//matr.push_back(vector<uint32_t>());
				//int j = 0;
				for (int j = 0; j < columns; ++j) {
					matr.push_back(stoi(p));
					//cout << stoi(p) << endl;
					p = strtok_s(NULL, " ", &next_token1);
				}
			}
		}
		auto getInitialState() {
			string initialStateStr;
			cout << "Initial state: ";
			getchar();
			getline(cin, initialStateStr);
			splitByDelimeter(initialStateStr, initialState);
		}
		auto getInput() {
			string inputValuesStr;
			cout << "Input: ";
			getchar();
			getline(cin, inputValuesStr);
			splitByDelimeter(inputValuesStr, inputValues);
		}


};

class LinearAutomate: public Automate{
private:
	
	// uint8_t phiTable[] = new uint8_t [pow(2, n+1)];
	// uint8_t psiTable[] = new uint8_t [pow(2, n+1)];
	uint32_t q, m, n, k;
	vector<vector<uint32_t>> matrA = vector<vector<uint32_t>>();
	vector<vector<uint32_t>> matrB = vector<vector<uint32_t>>();
	vector<vector<uint32_t>> matrC = vector<vector<uint32_t>>();
	vector<vector<uint32_t>> matrD = vector<vector<uint32_t>>();
	vector<uint32_t>& hFunc() {
		//uint32_t x_n = transientOutputFunc(next, xVector, 0);
		auto tmp = vector<vector<uint32_t>>();
		tmp.push_back(initialState);
		auto s_mult_matr_A = multiplyMatr(tmp, this->matrA);
		tmp.clear();
		tmp.push_back(inputValues);
		auto x_mult_matr_C = multiplyMatr(tmp, this->matrC);
		vector<uint32_t> res = vector<uint32_t>();
		addMatr(s_mult_matr_A[0], x_mult_matr_C[0], res);
		//return xVector;
		for (int i = 0; i < res.size(); i++) {
			cout << res[i] << " ";
		}
		cout << endl;
		return res;
	}
	void fFunc() {
		auto &res_H = hFunc();
		auto tmp = vector<vector<uint32_t>>();
		tmp.push_back(initialState);
		auto s_mult_matr_B = multiplyMatr(tmp, this->matrB);
		tmp.clear();
		tmp.push_back(inputValues);
		auto x_mult_matr_D = multiplyMatr(tmp, this->matrD);
		vector<uint32_t> res = vector<uint32_t>();
		addMatr(s_mult_matr_B[0], x_mult_matr_D[0], res);
		for (int i = 0; i < res.size(); i++) {
			cout << res[i] << " ";
		}
		cout << endl;
		initialState = res_H;
	}

public: 
	LinearAutomate(string path) {
		// open file
		ifstream myfile(path);
		if (myfile.is_open())
		{
			getInitialState();
			getInput();
			string line;
			getline(myfile, line);
			this->q = stoi(line);
			
			getline(myfile, line);
			this->n = stoi(line);
			getline(myfile, line);
			this->m = stoi(line);
			getline(myfile, line);
			this->k = stoi(line);
			cout << "Q: " << this->q << " " << this->m << " " << this->n << " " << this->k << endl;
			this->initializeMatr(&myfile, n, n, matrA);
			cout << "Size:" << matrA.size() << endl;
			for (int i = 0; i < matrA.size(); i++) {
				for (int j = 0; j < matrA[i].size(); j++) cout << matrA[i][j] << " ";
				cout << endl;
			}
			this->initializeMatr(&myfile, m, n, matrB);
			cout << "Size:" << matrB.size() << endl;
			for (int i = 0; i < matrB.size(); i++) {
				for (int j = 0; j < matrB[i].size(); j++) cout << matrB[i][j] << " ";
				cout << endl;
			}
			this->initializeMatr(&myfile, n, k, matrC);
			for (int i = 0; i < matrC.size(); i++) {
				for (int j = 0; j < matrC[i].size(); j++) cout << matrC[i][j] << " ";
				cout << endl;
			}
			this->initializeMatr(&myfile, m, k, matrD);
			for (int i = 0; i < matrD.size(); i++) {
				for (int j = 0; j < matrD[i].size(); j++) cout << matrD[i][j] << " ";
				cout << endl;
			}

			myfile.close();
			
			vector<vector<uint32_t>> &multRes = multiplyMatr(matrA, matrC);
			cout << "Mult: " << endl;
			cout << multRes.size() << endl;
			for (int i = 0; i < multRes.size(); i++) {
				for (int j = 0; j < multRes[i].size(); j++) cout << multRes[i][j] << " ";
				cout << endl;
			}
		}
		
		// sleep(100);
	}
	uint32_t multMod(uint32_t op1, uint32_t op2) {
		cout << op1 * op2 << endl;
		return (op1 * op2) % q;
	}

	uint32_t addMod(uint32_t op1, uint32_t op2) {
		cout << op1 + op2 << endl;
		return (op1 + op2) % q;
	}

	vector<vector<uint32_t>>& multiplyMatr(vector<vector<uint32_t>>& A, vector<vector<uint32_t>>& B) {
		static vector<vector<uint32_t>> result = vector<vector<uint32_t>>(A.size(), vector<uint32_t>(B[0].size(), 0));
		/*for (i = 0; i < A.size(); i++)
			result[i] = (float*)calloc(k, sizeof(float));*/
		uint32_t temp = 0;
		for (int i = 0; i < A.size(); i++) {
			//result.push_back(vector<uint32_t>(A[i].size()));
			temp = 0;
			for (int j = 0; j < A[i].size(); j++) {
				/*result[i].push_back(0);*/
				for (int l = 0; l < B[i].size(); l++) {
					temp = addMod(multMod(A[i][j], B[j][l]), result[i][l]);
					cout << "temp: " << temp << " " << A[i][j] << " " << B[j][l] << endl;
					result[i][l] = temp;
				}
			}
			//result[i].push_back(temp);
		}
		cout << "Size:" << result.size() << result[0][0] << " " << result[0][1] << " " << result[0][2] << endl;
		cout << "Size:" << result[0].size() << result[1][0] << " " << result[1][1] << " " << result[1][2] << endl;
		return result;
	}
	void addMatr(vector<uint32_t>& A, vector<uint32_t>& B, vector<uint32_t>& res) {
		for (int i = 0; i < A.size(); ++i) {
			res.push_back(A[i] + B[i]);
		}
	}
	void nextState() {
		getInput();
		this->fFunc();
	}
};


class ShiftRegister: public Automate{
private:
	uint8_t n;
	uint32_t x;
	vector<vector<uint32_t>> tables;
	//vector<uint8_t> ksiTable;
	uint32_t size;
	vector<uint32_t> initialState;
	vector<pair<uint32_t, uint32_t>> transientOutputTable = vector<pair<uint32_t, uint32_t>>();
	vector <vector<uint32_t>> accessMatrix = vector<vector<uint32_t>>();
	vector <vector<uint32_t>> resultLinked = vector<vector<uint32_t>>();
	vector <bool> inProgressDFS = vector<bool>();
	vector <uint32_t> visited = vector<uint32_t>();
	vector <vector <uint32_t>> stronglyLinkedComponents = vector<vector<uint32_t>>();
	vector<uint32_t> stack = vector<uint32_t>();
	vector<uint32_t> marked = vector<uint32_t>();
	vector<vector<uint32_t>> result = vector<vector<uint32_t>>();
	void fillTable(ifstream* file, vector<uint32_t>& fillingTable) {
		string line;
		for (int i = 0; i < size; i++) {
			getline(*file, line);
			fillingTable.push_back(stoi(line));
		}
		//return fillingTable;
	}
	uint32_t transientOutputFunc(uint32_t newState, vector<uint32_t> previousState, uint32_t mode) {
		int index = 0;
		previousState.push_back(newState);
		for (int i = 0; i < previousState.size(); i++) index = ((index << 1) | previousState[i]) & 0x7F;
		//cout << "Number:" <<  index << endl;
		
		return tables[mode][index];
	}

	auto& hFunc(vector<uint32_t>& xVector, uint32_t next) {
		uint32_t x_n = transientOutputFunc(next, xVector, 0);
		/*for (int i = 0; i < xVector.size(); i++) {
			cout << xVector[i] << " ";
		}*/
		//return xVector;
		return x_n;

	}

	vector<uint32_t> genVectorFromNum(uint32_t num) {
		vector<uint32_t> tmp = vector<uint32_t>();
		for (int i = 0; i < n; i++) {
			tmp.push_back(num % 2);
			num /= 2;
		}
		reverse(tmp.begin(), tmp.end());
		//for (int i = 0; i < tmp.size(); i++) {
		//	cout << tmp[i];
		//}
	
		return tmp;
	}
	void transientOutputTableInit() {
		//for (int i = 0; i < tables[0].size(); i++) {
		//	cout << tables[0][i] << " ";
		//}
		cout << endl;
		for (int state = 0; state < pow(2, n); state++) {
			accessMatrix.push_back(vector <uint32_t>(size / 2, 0));
			/*auto input_0 = (state << 1) & 0xF;
			auto input_1 = ((state << 1) | 1) & 0xF;*/
			auto input_0 = 0;
			auto input_1 = 1;
			/*auto input_0 = (state << 1 | 0) & 0x7F;
			auto input_1 = ((state << 1) | 1) & 0x7F;*/
			//transientOutputTable.push_back(make_pair(tables[0][input_0], tables[0][input_1]));
			//cout <<  << endl;
			/*auto index_1 = 
			cout << index_1 << endl;*/
			/*cout << "input_0 " << hFunc(genVectorFromNum(state), input_0) << endl;
			cout << "input_1 " << hFunc(genVectorFromNum(state), input_1) << endl;*/
			//cout << "POP " << (((state << 1) | hFunc(genVectorFromNum(state), input_0)) & (size / 2 - 1)) << " " << (((state << 1) | hFunc(genVectorFromNum(state), input_1)) & (size / 2 - 1)) << endl;
			cout << "size tmp: " << genVectorFromNum(state).size() << endl;
			auto tmp_vector = genVectorFromNum(state);
			
			accessMatrix[state][(((state << 1) | hFunc(tmp_vector, input_0)) & (size / 2 - 1))] = 1;
			accessMatrix[state][(((state << 1) | hFunc(tmp_vector, input_1)) & (size / 2 - 1))] = 1;
			/*accessMatrix[state][(((state << 1) | tables[0][input_0]) & (size / 2 - 1))] = 1;
			accessMatrix[state][(((state << 1) | tables[0][input_1]) & (size / 2 - 1))] = 1;*/
			/*accessMatrix[state][(((state << 1) | tables[0][input_0]))] = 1;
			accessMatrix[state][(((state << 1) | tables[0][input_1]))] = 1;*/
			resultLinked.push_back(vector<uint32_t>());
			inProgressDFS.push_back(false);

			//accessMatrix[(state << 1) | tables[0][input_1] ] = 1;

			//cout << state << " " << transientOutputTable[state].first << " " << transientOutputTable[state].second << endl;
		}
		auto res = depthFisrtSearch(string ("simple"));
		//for (int i = 0; i < accessMatrix.size(); i++) {
		//	for (int j = 0; j < accessMatrix[i].size(); j++) {
		//		cout << accessMatrix[i][j] << " ";
		//	}
		//	cout << endl;
		//}
		cout << "FINAL: " << endl;
		if (res.size() == 1)
			cout << "Automate is linked\n";
		else
			cout << "Automate is not linked\n";
		cout << "linked: " << endl;
		sort(res.begin(), res.end());

		for (int i = 0; i < res.size(); i++) {
			sort(res[i].begin(), res[i].end());
			for (int j = 0; j < res[i].size(); j++) {
				cout << res[i][j] << " ";
			}
			cout << endl;
		}
		marked.clear();
		stack.clear();
		result.clear();
		result.shrink_to_fit();
		auto strongLinkedList = depthFisrtSearch(string("strong"));
		
		
		if (strongLinkedList.size() == 1) {
			cout << "Automate is strongly linked\n";
		}
		else
			cout << "Automate is not strongly linked\n";
		cout << "Strongly linked: " << endl;
		for (int i = 0; i < strongLinkedList.size(); i++) {
			sort(strongLinkedList[i].begin(), strongLinkedList[i].end());
			for (int j = 0; j < strongLinkedList[i].size(); j++) {
				cout << strongLinkedList[i][j] << " ";
			}
			cout << endl;
		}

	}
	void depthFirstSearchOld() {
		
		/*for (int i = 0; i < size/2; i++) {
			accessMatrix.push_back(vector <uint32_t>(size/2));
			accessMatrix[i][transientOutputTable[i].first] = 1;
			accessMatrix[i][transientOutputTable[i].second] = 1;

		}*/
		for (int i = 0; i < accessMatrix.size(); i++) {
			for (int j = 0; j < accessMatrix[i].size(); j++) {
				cout << accessMatrix[i][j] << " ";
			}
			cout << endl;
		}
		for (int i = 0; i < accessMatrix.size(); i++) {
			//if (resultLinked.size() >= startPos || resultLinked.size() == 0) {
			//resultLinked.push_back(vector<uint32_t>());
			//}
			recSearch(i, "Strong");
			sort(visited.begin(), visited.end());
			for (int j = 0; j < visited.size(); j++) {
				cout << visited[j] << " ";
			}
			cout << endl;
			resultLinked[i] = visited;
			sort(resultLinked[i].begin(), resultLinked[i].end());
			visited.clear();
		}
		findStronlguLinked(resultLinked);
		cout << "******************************************\n";
		for (int i = 0; i < stronglyLinkedComponents.size(); i++) {

			for (int j = 0; j < stronglyLinkedComponents[i].size(); j++) {
				cout << stronglyLinkedComponents[i][j] << " ";
			}
			cout << endl;
		}
		cout << "******************************************\n";

		/*cout << "recSearhc results:" << endl;
		for (int i = 0; i < resultLinked.size(); i++) {
			for (int j = 0; j < resultLinked[i].size(); j++) {
				cout << resultLinked[i][j] << " ";
			}
			cout << endl;
		}*/
		bool strongLinkedFlag = 0;
		for (int i = 0; i < resultLinked.size(); i++) {
			if (resultLinked[i].size() == size) {
				
				cout << "Automate is strongly linked" << endl;
				strongLinkedFlag = true;
				break;
			}
		}
		if (!strongLinkedFlag) {
			cout << "Automate is not strongly linked" << endl;
			for (int i = 0; i < resultLinked.size(); i++) {
				//recSearch(i, "Strong");
				//resultLinked[i] = visited;
				//sort(resultLinked[i].begin(), resultLinked[i].end());
				/*for (int j = 0; j < resultLinked[i].size(); j++) {
					cout << resultLinked[i][j] << " ";
				}*/
				cout << endl;
			}
		}
		cout << "SIze:" << size << endl;
		/*for (int i = 0; i < accessMatrix.size(); i++) {
			result.push_back(vector<uint32_t>());
			for (int j = 0; j < accessMatrix[i].size(); j++){
				if (accessMatrix[i][j] != 0 && find(resultLinked[i].begin(), resultLinked[i].end(), j) != resultLinked[i].end()) {
					resultLinked[i].push_back(j);
					if (j != i){
						curPos = j;

					}
					

				}
			}
		}*/
	}
	void printVector(vector<vector<uint32_t>> table) {
		for (int i = 0; i < table.size(); i++) {
			for (int j = 0; j < table[i].size(); j++) {
				cout << table[i][j] << " ";
			}
			cout << endl;
		}
	}
	void findStronlguLinked(vector<vector<uint32_t>> resultLinked) {
		vector<bool> marked = vector<bool>(size, false);
		
		bool flag = true;
		for (int i = 0; i < resultLinked.size(); i++) {
			for (int j = 0; j < resultLinked.size(); j++) {
				if ((i != j) && (resultLinked[i].size() == resultLinked[j].size())) {
					for (int k = 0; k < resultLinked[i].size(); k++) {
						if (resultLinked[i][k] == resultLinked[j][k])
							true;
						else {
							flag = false;
							
							break;
						}
					}
					if (flag == true){
						stronglyLinkedComponents.push_back(resultLinked[i]);
					}
				}
			}
			if (!flag)
			{
				stronglyLinkedComponents.push_back(vector<uint32_t>(1, i));
			}
		}
		
	}

	vector<vector<uint32_t>> depthFisrtSearch(string mode) {
		cout << "2 entry\n";
		bool flag;
		stack = vector<uint32_t>();
		marked = vector<uint32_t>();
		result = vector<vector<uint32_t>>();
		for (int i = 0; i < pow(2, n); i++) {
			flag = false;
			flag = findSmthg(result, i);
			/*for (int j = 0; j < result.size(); j++) {
				if (find(result[j].begin(), result[j].end(), i) != result[j].end()) {
					flag = true;
					break;
				}
			}*/
			if (flag) {
				continue;
			}
			else {
				marked.push_back(i);
				stack.push_back(i);
				while (stack.size() != 0) {
					for (int k = 0; k < accessMatrix[i].size(); k++) {
						if ((((accessMatrix[i][k] == 1 || accessMatrix[k][i] == 1) && mode == "simple") or (accessMatrix[i][k] == 1 && mode == "strong")) && i != k){
							flag = false;
							flag = findSmthg(result, k);
							if (flag || find(marked.begin(), marked.end(), k) != marked.end()) continue;
							else {
								marked.push_back(k);
								stack.push_back(k);
								anotherRecDFS(k, mode, marked, stack, result);
								stack.pop_back();

							}
							/*for (int l = 0; l < result.size(); l++) {
								if (find(result[i]))
							}*/
						}
					}
					stack.pop_back();
				}
				if (mode == "strong") {
					vector<uint32_t> markedNew	= vector<uint32_t>();
					vector<uint32_t> stackNew	= vector<uint32_t>();
					vector<vector<uint32_t>> resultNew	= vector<vector<uint32_t>>();
					vector<uint32_t> markedCopy = vector<uint32_t>(marked);
					for (int j = 1; j < marked.size(); j++) {
						anotherRecDFS(marked[j], string("strong"), markedNew, stackNew, resultNew);
						if (find(markedNew.begin(), markedNew.end(), marked[0]) == markedNew.end())
							markedCopy.erase(find(markedCopy.begin(), markedCopy.end(), marked[j]));
						
						markedNew = vector<uint32_t>();
						stackNew = vector<uint32_t>();
						resultNew = vector<vector<uint32_t>>();
					}
					marked = vector<uint32_t>(markedCopy);
				}
				result.push_back(marked);
				marked = vector<uint32_t>();
			}
		}
		return result;
	}

	void anotherRecDFS(int i, string mode, vector<uint32_t>& marked, vector<uint32_t>& stack, vector<vector<uint32_t>>& result) {
		bool flag;
		for (int k = 0; k < accessMatrix[i].size(); k++) {
			if ((((accessMatrix[i][k] == 1 || accessMatrix[k][i]) && mode == "simple") or ((accessMatrix[i][k] == 1) && (mode == "strong"))) && i != k) {
				flag = false;
				flag = findSmthg(result, k);
				if (flag || find(marked.begin(), marked.end(), k) != marked.end()) continue;
				else {
					marked.push_back(k);
					stack.push_back(k);
					anotherRecDFS(k, mode, marked, stack, result);
					stack.pop_back();
				}
			}
		}
	}

	bool findSmthg(vector<vector<uint32_t>> vec, int i) {
		for (int j = 0; j < vec.size(); j++) {
			if (find(vec[j].begin(), vec[j].end(), i) != vec[j].end()) {
				return true;
			}
		}
	}
	//void findStronlguLinked_2(vector<vector<uint32_t>> resultLinked) {
	//	vector<bool> marked = vector<bool>(size, false);

	//	bool flag = true;
	//	for (int i = 0; i < resultLinked.size(); i++) {
	//		if resultLinked
	//		for (int j = 0; j < resultLinked[i].size(); j++){}
	//	}

	//}


	void recSearch(uint32_t startPos, string mode) {
		auto i = startPos;
		visited.push_back(i);
		for (uint32_t j = 0; j < accessMatrix[i].size(); j++) {
			if (mode == "Simple") {
				if ((accessMatrix[i][j] == 1 or accessMatrix[j][i] == 1) && !(find(visited.begin(), visited.end(), j) != visited.end())) {
					recSearch(j, mode);
				}
			}
			else{
				if ((accessMatrix[i][j] == 1) && !(find(visited.begin(), visited.end(), j) != visited.end()))
					recSearch(j, mode);
			}
		}
	}

	auto fFunc(vector<uint32_t>& xVector, uint32_t next) {
		return transientOutputFunc(transientOutputFunc(next, xVector, 0), xVector, 1);
	}

	uint32_t makeNumFromVector(vector<uint32_t> vec) {
		uint32_t num = 0;
		for (int i = 0; i < vec.size(); i++) {
			num = (num << 1) | vec[i];
		}
		return num;
	}

	auto equalPrep() {

		vector<vector<uint32_t>> equalArray = vector<vector<uint32_t>>();
		vector<uint32_t> stateInfo = vector<uint32_t>();
		for (int i = 0; i < pow(2, n); i++) {
			auto state = genVectorFromNum(i);
			for (int j = 0; j < 2; j++) {
				auto tmp = vector<uint32_t>(state);
				auto x_n = hFunc(tmp, j);
				tmp.erase(tmp.begin());
				tmp.push_back(x_n);
				stateInfo.push_back(makeNumFromVector(tmp));
				tmp = vector<uint32_t>(state);
				stateInfo.push_back(fFunc(tmp, j));
			}
			equalArray.push_back(stateInfo);
			stateInfo = vector<uint32_t>();
		}
		return equalArray;
	}

	auto equalSearch(vector<vector<uint32_t>> equalArray) {

		auto equalClasses = vector<vector<uint32_t>>();
		auto equalClass = vector<uint32_t>();
		bool flag;
		for (int i = 0; i < equalArray.size(); i++) {
			flag = false;
			flag = findSmthg(equalClasses, i);
			if (flag) continue;
			else {
				equalClass.push_back(i);
				for (int j = i + 1; j < equalArray.size(); j++) {
					if ((equalArray[i][1] == equalArray[j][1]) && (equalArray[i][3] == equalArray[j][3])) {
						equalClass.push_back(j);
					}
				}
				equalClasses.push_back(equalClass);
				equalClass = vector<uint32_t>();
			}
		}
		return equalClasses;
	}

	auto findClass(vector<vector<uint32_t>> classes, uint32_t item) {
		for (int i = 0; i < classes.size(); i++) {
			if (find(classes[i].begin(), classes[i].end(), item) != classes[i].end())
				return i;
		}
	}

	auto equalSearchFinal(vector<vector<uint32_t>> equalArray, vector<vector<uint32_t>> equalClasses) {

		auto newClasses = vector<vector<uint32_t>>();
		auto newClass = vector<uint32_t>();
		bool flag;
		for (int i = 0; i < equalClasses.size(); i++){
			vector<uint32_t> item = equalClasses[i];
			for (int j = 0; j < item.size(); j++){
				flag = false;
				flag = findSmthg(newClasses, item[j]);
				if (flag) continue;
				else {
					newClass.push_back(item[j]);
					auto class_0 = findClass(equalClasses, equalArray[item[j]][0]);
					auto class_1 = findClass(equalClasses, equalArray[item[j]][2]);
					for (int k = j + 1; k < item.size(); k++) {
						if ((findClass(equalClasses, equalArray[item[k]][0]) == class_0) && (findClass(equalClasses, equalArray[item[k]][2]) == class_1)) {
							newClass.push_back(item[k]);
						}
					}
					newClasses.push_back(newClass);
					newClass = vector<uint32_t>();
				}
			}
		}
		return newClasses;
	}


	public:
		ShiftRegister(string path) {
			ifstream myfile(path);
						if (myfile.is_open()) {
				cout << "OPEN" << endl;
				string line;
				getline(myfile, line);
				n = stoi(line);
				size = pow(2, n + 1);
				getline(myfile, line);
				//vector<uint8_t> phiTable;
				tables.push_back(vector<uint32_t>());
				tables.push_back(vector<uint32_t>());
				//fillTable(&myfile, tables[0]);
				//fillTable(&myfile, tables[1]);
				
				initializeMatr(&myfile, 1, size, tables[0]);
				cout << "First line read\n";
				getline(myfile, line);
				
				initializeMatr(&myfile, 1, size, tables[1]);
				cout << tables[0].size() << endl;
				/*for (int i = 0; i < size; ++i) {
					cout << tables[0][i] << " " << tables[1][i] << endl;
				}*/
				//vector<uint8_t> ksiTable;
				
				
			}
		}

		void printTransientOutputTable() {
			cout << "here" << endl;
			transientOutputTableInit();

		}

		void setInitialState(vector<uint32_t>& initialState) {
			this->initialState = initialState;
		}
		void nextState() {
			
			cout << "Enter x: ";
			cin >> this->x;
			cout << endl;
			auto x_n = this->hFunc(initialState, x);
			
			cout << endl;
			this->output();
			initialState.erase(initialState.begin());
			initialState.push_back(x_n);
			for (int i = 0; i < initialState.size(); i++) {
				cout << initialState[i] << " ";
			}
			//return vec;
			
		}
		void output() {
			cout << "Output: " << this->fFunc(initialState, this->x) << endl;
		}
		void makeItNice() {

		}

		void makeEqualClasses() {
			auto equalArray = equalPrep();
			auto classes = equalSearch(equalArray);
			bool flag = false;
			bool cycleExit = false;
			while ((classes.size() != pow(2, n)) && (!flag)) {
				auto oldClasses = vector<vector<uint32_t>>(classes);
				classes = equalSearchFinal(equalArray, classes);
				std::sort(classes.begin(), classes.end());
				std::sort(oldClasses.begin(), oldClasses.end());
				//std::vector<vector<uint32_t>> v3;
				//std::set_intersection(classes.begin(), classes.end(), oldClasses.begin(), oldClasses.end(), std::back_inserter(v3));
				cycleExit = false;
				bool equal = true;
				if (classes.size() == oldClasses.size()) {

					for (int i = 0; i < classes.size(); i++) {
						std::sort(classes[i].begin(), classes[i].end());
						std::sort(oldClasses[i].begin(), oldClasses[i].end());
						if (classes[i].size() == oldClasses[i].size()) {
							for (int j = 0; j < classes[i].size(); j++) {
								if (classes[i][j] != oldClasses[i][j]) {
									cycleExit = true;
									equal = false;
									break;
								}
							}
						}
						else {
							equal = false;
						}
						if (cycleExit) break;
					}
				}
				else {
					equal = false;
				}
				if (equal)
					flag = true;
			}
			cout << "Equal classes:\n";
			printVector(classes);
		}
		//void testStronglyLinked() {
		//	vector<vector<uint32_t>> testAccessMatrix = vector<vector<uint32_t>>(4);
		//	testAccessMatrix.push_back(vector<uint32_t>({}))
		//}
	

};




int main(int argc, char* argv[]) {
	if (argc > 1) {
		string path = string(argv[1]);
		cout << path << endl;
		string automateType;
		cout << "Enter automate type: ";
		cin >> automateType;
		cout << endl;
		if (automateType == "SR") {
			cout << "Init Begin" << endl;
			ShiftRegister obj = ShiftRegister(path);
			cout << "Init Success" << endl;
			obj.printTransientOutputTable();
			obj.makeEqualClasses();
			/*while (1) {
				obj.nextState();
			}*/
		}
		else if (automateType == "Linear") {
			LinearAutomate obj = LinearAutomate(path);
			while (1) {
				obj.nextState();
			}
		}
	}
	return 0;
}
void splitByDelimeter(string line, vector<uint32_t> &initialState) {
	char* next_token1 = NULL;
	char* s = new char[line.size() + 1];
	strncpy_s(s, line.size() + 1, line.c_str(), line.size() + 1);
	char* p = strtok_s(s, " ", &next_token1);
	//char* buf = strtok(str, " .,!?\n");
	//int j = 0;
	while(p != NULL) {
		initialState.push_back(stoi(p));
		cout << stoi(p) << endl;
		p = strtok_s(NULL, " ", &next_token1);
	}
}