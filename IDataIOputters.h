#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <regex>

// »нтерфейс ввода из файла.
template<class T>
struct IDataFileInputter {
    virtual std::pair<short, std::vector<T>> getDataFromFile(const std::string& filePath) const = 0;
};

// »нтерфейс дл€ работы с каталогом.
struct IDataDirectoryInputter {
    // —бор всех файлов в каталоге по регул€рному выражению.
    virtual std::vector<std::string> getFilesVectorFromDirectory(const std::regex& regular) const = 0;
};

// »нтерфейс дл€ вывода в файл.
template<class T>
struct IDataFileOutputter {
    virtual void outputData(const T& data, const std::string& path) const = 0;
};