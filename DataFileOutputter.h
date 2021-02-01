#pragma once
#include <exception>
#include "IDataIOputters.h"

template<class T>
struct DataFileOutputter : IDataFileOutputter<T> {

	void outputData(const T& data, const fs::path& file = fs::current_path() / "out.dat") const {
		
		if (!fs::exists(file.parent_path()) || !fs::is_directory(file.parent_path())) {
			throw std::exception("Invalid directory output");
		}

		std::ofstream fout(file, std::ios::app);
		fout << data << std::endl;
		fout.close();
	}
};