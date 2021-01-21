#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <exception>
#include "IDataIOputters.h"

template<class T>
struct DataFileOutputter : IDataFileOutputter<T> {
	void outputData(const T& data, const std::string& path) const {
		std::ofstream fout(path, std::ios::app);
		fout << data << std::endl;
		fout.close();
	}
};