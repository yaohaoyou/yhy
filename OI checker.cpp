#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <dirent.h>
#include<windows.h>
using namespace std;
string folderPath;
bool compileAndRun(const std::string& sourceFile, const std::string& executableFile) {
    std::string compileCmd = "g++ " + sourceFile + " -o " + executableFile + " -std=c++20 -O2 -w";
    if (system(compileCmd.c_str()) != 0) {
        std::cerr << "编译失败: " << sourceFile << std::endl;
        return false;
    }
    std::string runCmd = executableFile;
    system(runCmd.c_str()); 
    return true;
}

bool compareFiles(const std::string& outputFile, const std::string& expectedFile) {
	string FC="fc "+outputFile+" "+expectedFile; 
	return !system(FC.c_str());
}

int main() {
    DIR *dir;
    struct dirent *ent;
    folderPath = "./";
    if ((dir = opendir(folderPath.c_str())) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            std::string fileName = ent->d_name;
            if(fileName=="OI checker.cpp")	continue;
            string bsName=fileName.substr(0,fileName.size()-4);
            if (fileName.size() > 4 && fileName.substr(fileName.size() - 4) == ".cpp") {
                std::string baseName = fileName.substr(0, fileName.size() - 4);
                std::string executableFile = bsName + ".exe";
                std::string outputFile = baseName + ".out";
                std::string expectedFile = baseName + ".ans";

                std::cout << "正在处理: " << bsName << std::endl;

                if (compileAndRun(fileName, executableFile)) {
                    if (compareFiles(outputFile, expectedFile)) {
                        std::cout << "测试 " << bsName << " 通过!" << std::endl;
                    } else {
                        std::cout << "测试 " << bsName << " 失败!" << std::endl;
                    }
                }
                std::cout << std::endl;
            }
        }
        closedir(dir);
    }
    return EXIT_SUCCESS;
}