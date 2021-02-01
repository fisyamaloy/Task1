#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

// Интерфейс для работы с каталогом.
struct IDataDirectoryInputter {
    // Сбор всех файлов в каталоге.
    virtual std::vector<fs::path> getFilesVector() const noexcept = 0;
};

// Интерфейс ввода из файла.
template<class T>
struct IDataFileInputter {
    virtual std::pair<short, std::vector<T>> getDataFromFile(const fs::path& file) const = 0;
};

// Интерфейс для вывода в файл.
template<class T>
struct IDataFileOutputter {
    virtual void outputData(const T& data, const fs::path& file) const = 0;
};