#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "IDataIOputters.h"

template<class T>
struct DataFileInputter : IDataFileInputter<T> {

	std::pair<short, std::vector<T>> getDataFromFile(const std::string& filePath) const override {
		std::ifstream fin(filePath);
		if (!fin.is_open()) {
			throw std::exception("File open error");
		}

		short actionNumber;
		std::vector<T> numbers;

		fin >> actionNumber;
		T tempNum;
		while (fin >> tempNum) {
			numbers.emplace_back(tempNum);
		}

		fin.close();

		return std::make_pair(actionNumber, numbers);
	}
};

