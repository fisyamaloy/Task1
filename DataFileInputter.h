#pragma once
#include <iostream>
#include "IDataIOputters.h"

template<class T>
struct DataFileInputter : IDataFileInputter<T> {

	std::pair<short, std::vector<T>> getDataFromFile(const fs::path& file) const override {
		std::ifstream fin(file);
		if (!fin.is_open()) {
			throw std::exception("File open error");
		}

		short actionNumber;
		fin >> actionNumber;

		std::vector<T> numbers;
		
		T tempNum;
		while (fin >> tempNum) {
			numbers.emplace_back(tempNum);
		}

		fin.close();

		return std::make_pair(actionNumber, numbers);
	}
};

