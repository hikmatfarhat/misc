#pragma once
#include <string>
#include <vector>


template <typename T>
class Matrix {
private:
	T* p;
	int rows, cols;
public:
	Matrix(int n, int m) :rows(n), cols(m) {
		/* not the most efficient way
		   but it is easy and most of the time
		   we do it once */
		p = new T[n*m]();
	}
	T* operator[](int i) {
		return &p[i*cols];
	}
	int getRows() {
		return rows;
	}
	int getCols() {
		return cols;
	}
};

template <typename T>
std::set<T>& merge(std::set<T>& ls, const std::set<T>& rs) {
	for (auto itr = rs.begin(); itr != rs.end(); itr++) {
		ls.insert(*itr);
	}
	return ls;
}

std::string printSet(std::set<std::string> ss) {
	std::string result = "{";
	for (auto itr = ss.begin(); itr != ss.end(); itr++){
		auto tmp = itr; 
		tmp++;
		if (itr == ss.begin()) {
			result = result + *itr;
			continue;
		}
		if (tmp == ss.end())
			result = result + ","+*itr + "}";
		else
			result = result + "," + *itr;

	}
	if (ss.size() == 0)result = result + "}";
	return result;

}




std::set<std::string> cartesian(std::set<std::string>& s1,
								std::set<std::string>& s2) {
	std::set<std::string> result;
	for (auto i1 = s1.begin(); i1 != s1.end(); i1++) {
		for (auto i2 = s2.begin(); i2 != s2.end(); i2++) {
			result.insert(*i1 + *i2);
		}
	}
	return result;
}
