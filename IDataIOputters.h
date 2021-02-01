#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

// ��������� ��� ������ � ���������.
struct IDataDirectoryInputter {
    // ���� ���� ������ � ��������.
    virtual std::vector<fs::path> getFilesVector() const noexcept = 0;
};

// ��������� ����� �� �����.
template<class T>
struct IDataFileInputter {
    virtual std::pair<short, std::vector<T>> getDataFromFile(const fs::path& file) const = 0;
};

// ��������� ��� ������ � ����.
template<class T>
struct IDataFileOutputter {
    virtual void outputData(const T& data, const fs::path& file) const = 0;
};