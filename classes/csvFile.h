#ifndef POO_CSVFILE_H
#define POO_CSVFILE_H

#include <iostream>
#include <vector>

using namespace std;

class csvFile {
private:
    string fileName;
    char fieldDelimiter;
    vector<vector<string>> fileContent;
    string csvRowToString(vector<string> input);
public:
    csvFile();
    csvFile(string fileName, char fieldDelimiter);

    void setFilename(string fileName);
    string getFileName();

    void setFieldDelimiter(char fieldDelimiter);
    char getFieldDelimiter();

    void setFileContent(vector<vector<string>> fileContent);
    vector<vector<string>> getFileContent();
    ~csvFile();
};


#endif //POO_CSVFILE_H
