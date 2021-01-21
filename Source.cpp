#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <thread>
#include <mutex>
#include <regex>
#include "AlgebraicAction.h"
#include "DataFileInputter.h"
#include "DataDirectoryInputter.h"
#include "DataFileOutputter.h"
//#define DEBUG

template<class T>
static T calculateIt(AlgebraicAction<T>* anyActionPointer, const std::vector<T>& numbers) {
	std::unique_ptr<AlgebraicAction<T>> actionSmartPointer(anyActionPointer);
	return actionSmartPointer->getResultOfAlgebraicAction(numbers);
}

template<class T>
static T getResultOfAction(const std::pair< short, std::vector<T> >& dataPair) {
	T actionResult;
	switch (dataPair.first) {
		case 1: {
			return calculateIt(new Addition<T>, dataPair.second);
		} case 2: {
			return calculateIt(new Multiplication<T>, dataPair.second);
		} case 3: {
			return calculateIt(new SquaresAddition<T>, dataPair.second);
		} default: {
			return 0;
		}
	}
}

int main() {
#ifdef DEBUG
	std::string directoryName = "C:\\Users\\User\\Desktop\\filesd";
#else

	std::string directoryName;
	std::cin >> directoryName;

#endif // DEBUG
	
	std::mutex mtx;

	try {
		DataDirectoryInputter DDI(directoryName);
		DataFileInputter<double> DFI;
		DataFileOutputter<double> DFO;

		std::vector<std::string> filesPathes = DDI.getFilesVectorFromDirectory(std::regex("(in_)([1-9])([\\d]*)(.dat)"));
		for (const auto& filePath : filesPathes) {
			std::thread t([&]() {
				auto dataPair = DFI.getDataFromFile(filePath);
				double actionResult = getResultOfAction(dataPair);
				{
					std::lock_guard<std::mutex> guard(mtx);
					DFO.outputData(actionResult, "out.dat");
				}
			});

			t.join();
		}

	} catch(const std::exception& e){
		std::cerr << e.what() << std::endl;
	} catch (...) {
		std::cerr << "SOMETHING WRONG" << std::endl;
	}
}