#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <thread>
#include <mutex>
#include "AlgebraicAction.h"
#include "DataFileInputter.h"
#include "DataDirectoryInputter.h"
#include "DataFileOutputter.h"
#define DEBUG

template<class T>
static T calculateIt(AlgebraicAction<T>* anyActionPointer, const std::vector<T>& numbers) {
	std::unique_ptr<AlgebraicAction<T>> actionSmartPointer(anyActionPointer);
	return actionSmartPointer->calculate(numbers);
}

template<class T>
static T doAlgebraicAction(const std::pair< short, std::vector<T> >& dataPair) {
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

	std::cout << "AC was made" << std::endl;
}


namespace fs = std::filesystem;

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

		std::vector<fs::path> files = DDI.getFilesVector();
		for (const auto& file : files) {
			std::thread t([&]() {
				auto dataPair = DFI.getDataFromFile(file.string());
				double actionResult = doAlgebraicAction(dataPair);
				{
					std::lock_guard<std::mutex> guard(mtx);
					DFO.outputData(actionResult);
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
