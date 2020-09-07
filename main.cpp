#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include "utilities.h"

using namespace std;
vector < pair<string, string>> productions;

/* given a symbol  "symbol"
	returns a set of all symbols
	that can produce it
	*/
set<string> search(string symbol) {
	set<string> list;
	for (auto itr = productions.begin(); itr != productions.end()
		; itr++)
		if (itr->second == symbol)
			list.insert(itr->first);

	return list;

}
/* generalization of the above
   returns a set of symbols that
   can produce a set of symbols
   */
set<string> search(set<string> ss) {
	set<string> list;
	for (auto p = ss.begin(); p != ss.end(); p++) {
		list = merge(list, search(*p));
	}
	return list;
}
/* this is the heart of
   the CYK algorithm
   */
void solve(Matrix<set<string>>& m, string input) {
	for (int l = 0,i=0; i < input.length(); i++) {
		string c;
		c = input[i];
		set<string> s = search(c);
		m[i][i] = s;

	}
	for (int l = 1; l<=input.length(); l++) {
		for (int i = 0; i < input.length() - l; i++) {
			int j = i + l;
			set<string> s;
			for (int k = i; k < j; k++) {
				s = merge(s, cartesian(m[i][k], m[k + 1][j]));
			}
			m[i][j] = search(s);

		}
	}
}
int readProductions(std::string filename) {

	std::ifstream file;
	std::string pr;
	std::string left, right;
	/* read the cfg from file "cfg.txt"
	   if the grammar is CNF*/
	file.open(filename);
	
	if (file.is_open()) {
		while (file >> pr) {
			if (pr.length() > 5) {
				std::cout << "not cnf\n";
				abort();
			}
			int itr = pr.find("->");
			if (itr != 1) {
				std::cout << "more than one symbol on left\n";
				abort();
			}
			left = pr.substr(0, 1);
			right = pr.substr(itr + 2, 2);
			pair<string, string> p(left, right);
			productions.push_back(p);
		}
		file.close();
		return 0;
	}
	else return -1;

}
int main() {
	cout << "input a string\n";
	string input;
	cin >> input;
	if (readProductions("cfg3.txt")==-1) {
		std::cout << "could not read input file\n";
		exit(1);
	}
	Matrix<set<string>> table(input.length(), input.length()) ;
    solve(table, input);
	int j = input.length() - 1;
	if (table[0][j].find("S") != table[0][j].end()) {
		std::cout << "belongs to language\n";
	}
	else
		std::cout << "does not belong to language\n";

}
