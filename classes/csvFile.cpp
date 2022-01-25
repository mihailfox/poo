#include <fstream>
#include <iostream>
#include <vector>
#include <stdexcept>
#include <string>
#include <sstream>
#include "csvFile.h"

csvFile::csvFile() = default;

csvFile::csvFile(string fileName, char fieldDelimiter) {
    if(fileName.empty() || isalpha(fieldDelimiter) || isdigit(fieldDelimiter)) {
        throw invalid_argument("Received an invalid argument!");
    }

    this->fileName = fileName;
    this->fieldDelimiter = fieldDelimiter;
}

void csvFile::setFilename(string fileName) {
    if(fileName.empty()) {
        cout << "File name can not be empty!" << endl;
        return;
    }

    this->fileName = fileName;
}

string csvFile::getFileName() {
    return this->fileName;
}

void csvFile::setFieldDelimiter(char fieldDelimiter) {
    this->fieldDelimiter = fieldDelimiter;
}

char csvFile::getFieldDelimiter() {
    return this->fieldDelimiter;
}

void csvFile::setFileContent(vector<vector<string>> fileContent) {
    string line;
    fstream file (this->fileName, ios::out);

    try {
        if (file.is_open()) {
            for (int i = 0; i < fileContent.size(); ++i) {
                file << csvRowToString(fileContent[i]);

            }
        }
    }
    catch (exception &ex)
    {
        throw ex;
    }

    file.close();
}

vector<vector<string>> csvFile::getFileContent() {
    vector<vector<string>> content;
    vector<string> row;
    string line;
    string field;

    fstream file (this->fileName, ios::in);

    try {
        if(file.is_open()) {
            while (getline(file, line)) {
                row.clear();

                stringstream str(line);

                while (getline(str,field,this->fieldDelimiter)) {
                    row.push_back(field);
                }

                content.push_back(row);
            }
        }
    }
    catch (exception &ex) {
        throw ex;
    }

    file.close();

    return content;
}

string csvFile::csvRowToString(vector<string> input) {
    stringstream line;
    for (int i = 0; i < input.size(); ++i) {
        line << input[i];
        if (i != input.size() - 1) {
           line << this->fieldDelimiter;
        }

    }
    line << endl;
    return line.str();
}

csvFile::~csvFile() {
    fileName.clear();
    fileContent.clear();
}
