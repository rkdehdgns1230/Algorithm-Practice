#include <iostream>
#include <vector>
#include <string>

#define MAX 129 // 2 ^ 7 + 1

using namespace std;

int n, m;
int ch[11] = { 0 };
string strX, strY;

vector<string> subSet;

/*
	function name : DFS
	brief : This function makes subset of sequence X
	if X's length is m, this function makes 2^m subsets
	argument : 
	idx means the index of string
	XorY true = X, false = Y
	return : void
*/
void DFS(int idx, bool XorY) {
	if (XorY) {
		// X is shorter than Y
		if (idx == n) {
			string str;
			for (int i = 0; i < n; i++) {
				if (ch[i] == 1)
					str += strX[i];
			}
			// push subset to subSet vector
			subSet.push_back(str);
			cout << str << endl;
			return;
		}
		else {
			// case1: ch[idx] = 1
			ch[idx] = 1;
			DFS(idx + 1, XorY);
			// case2: ch[idx] = 0
			ch[idx] = 0;
			DFS(idx + 1, XorY);
			return;
		}
	}
	else {
		// Y is shorter than X
		if (idx == m) {
			string str;
			for (int i = 0; i < m; i++) {
				if (ch[i] == 1)
					str += strY[i];
			}
			// push subset to subSet vector
			subSet.push_back(str);
			cout << str << endl;
			return;
		}
		else {
			// case1: ch[idx] = 1
			ch[idx] = 1;
			DFS(idx + 1, XorY);
			// case2: ch[idx] = 0
			ch[idx] = 0;
			DFS(idx + 1, XorY);
			return;
		}
	}
}
/*
	function name : getLCS
	brief : This function find the LCS of two sequences (X and Y)
	first calculate the maxLength(length of LCS) and
	find the LCS with maxLength and finally print the result(LCSs)
	return : void
*/
void getLCS(bool XorY) {
	int maxLength = 0;
	vector<string> result;
	string sequence;
	// select the string
	if (XorY) sequence = strY;
	else sequence = strX;

	// get the length of LCS
	for (int i = 0; i < subSet.size(); i++) {
		string str = subSet[i];
		int idx = 0;
		// compare ith subset with strY (sequence Y)
		for (int j = 0; j < sequence.size(); j++) {
			if (sequence[j] == str[idx])
				idx++;
		}
		if (idx == str.length() && str.length() > maxLength) {
			maxLength = idx;
		}
	}
	// find the LCS with maxLength(length of LCS)
	for (int i = 0; i < subSet.size(); i++) {
		// skip the other case (not the LCS)
		if (subSet[i].length() != maxLength) continue;
		string str = subSet[i];
		int idx = 0;
		for (int j = 0; j < sequence.size(); j++) {
			if (sequence[j] == str[idx])
				idx++;
		}
		if (idx == str.length()) {
			result.push_back(str);
		}
	}

	cout << "max length : " << maxLength << endl;
	cout << "LCS : \n";
	for (int i = 0; i < result.size(); i++) {
		cout << result[i] << "\n";
	}

	return;
}

int main() {
	bool XorY;
	cin >> strX >> strY;
	// get the length of strX and strY
	n = strX.length();
	m = strY.length();

	// set the XorY(select the sequence to find subset)
	if (n > m) 
		XorY = false; // we will find the subset of Y
	else 
		XorY = true; // we will find the subset of X

	cout << "### subset of X ###" << endl;
	DFS(0, XorY);
	cout << "number of subset : " << subSet.size() << endl;

	getLCS(XorY);
	cout << "### end of program ###" << endl;
	return 0;
}