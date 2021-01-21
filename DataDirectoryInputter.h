#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <regex>
#include <io.h>
#include <Windows.h>
#include "IDataIOputters.h"

struct DataDirectoryInputter : IDataDirectoryInputter {
    DataDirectoryInputter(std::string& directoryName) : directoryName(directoryName) {
        if (!directoryExists()) {
            throw std::exception("Invalid directory path");
        }
    }

    std::vector<std::string> getFilesVectorFromDirectory(const std::regex& regular) const override {
        std::vector<std::string> fileNames;
        _finddata_t info;
        intptr_t handle = _findfirst((directoryName + "\\*.*").c_str(), &info);
        if (handle == -1) {
            return fileNames;
        }

        do {
            if (info.attrib & _A_SUBDIR) {
                continue;
            }
            std::string fullFilePath = directoryName + "\\" + info.name;
            
            if (fileNameIsCorrect(info.name, regular)) {
                fileNames.push_back(fullFilePath);
            }

        } while (_findnext(handle, &info) == 0);

        _findclose(handle);
        return fileNames;
    }

private:
    std::string directoryName;
    
    bool directoryExists() {
        DWORD ftyp = GetFileAttributesA(directoryName.c_str());
        if (ftyp == INVALID_FILE_ATTRIBUTES)
            return false;

        if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
            return true;

        return false;
    }

    bool fileNameIsCorrect(const std::string fileName, const std::regex& regular) const {
        return std::regex_match(fileName.c_str(), regular);
    }
};