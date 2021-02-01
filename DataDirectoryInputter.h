#pragma once
#include "IDataIOputters.h"

struct DataDirectoryInputter : IDataDirectoryInputter {
    DataDirectoryInputter(const fs::path& directory) : directory(directory) {
        if (!fs::exists(directory) || !fs::is_directory(directory)) {
            throw std::exception("Invalid directory path");
        }
    }

    std::vector<fs::path> getFilesVector() const noexcept override {
        std::vector<fs::path> incommingFiles;
        
        for (const auto& it : fs::directory_iterator(directory)) {
            fs::path currentFile = it.path();

            if (currentFile.extension() == ".dat") {
                std::string fileName = currentFile.filename().replace_extension("").string();

                if (fileNameIsValid(fileName)) {
                    incommingFiles.push_back(currentFile);
                }
            }
        }

        return incommingFiles;
    }

private:
    fs::path directory;

    bool fileNameIsValid(const std::string fileName) const noexcept {
        if (fileName.substr(0, 3) == "in_") {
            std::string numerical = fileName.substr(3);

            for (const char symb : numerical) {
                if (!std::isdigit(symb)) {
                    return false;
                }
            }

            return true;
        }

        return false;
    }
};

