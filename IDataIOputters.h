#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <regex>

// ��������� ����� �� �����.
template<class T>
struct IDataFileInputter {
    virtual std::pair<short, std::vector<T>> getDataFromFile(const std::string& filePath) const = 0;
};

// ��������� ��� ������ � ���������.
struct IDataDirectoryInputter {
    // ���� ���� ������ � �������� �� ����������� ���������.
    virtual std::vector<std::string> getFilesVectorFromDirectory(const std::regex& regular) const = 0;
};

// ��������� ��� ������ � ����.
template<class T>
struct IDataFileOutputter {
    virtual void outputData(const T& data, const std::string& path) const = 0;
};