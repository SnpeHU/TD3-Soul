#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <Windows.h>

class ReadCSV {
    public:
	std::vector<std::vector<std::string>> Read(const std::string& file_path) {
		std::ifstream ifs(file_path);//	ファイルを読み込む
		if (!ifs) 
		{
			MessageBox(nullptr, TEXT("Failed to open csvfile."), TEXT("Error"), MB_OK);
			return {};
		}
		std::vector<std::vector<std::string>> data;//ファイルの内容を格納する変数
		std::string line;
		while (std::getline(ifs, line)) //ファイルから1行ずつ読み込む,并将其存储在 line 中
		{
			std::istringstream iss(line);//处理从文件中读取的每行数据，将其作为一个流对象来解析。
			std::vector<std::string> record;//1行分のデータを格納する変数
			std::string field;//1つ1つのデータを格納する変数
			while (std::getline(iss, field, ',')) 
			{
				record.push_back(field);
			}
			data.push_back(record);
		}
		return data;
	};

	std::vector<std::vector<int>> ReadMap(const std::string& file_path) {
		std::ifstream ifs(file_path);
		if (!ifs)
		{
			MessageBox(nullptr, TEXT("Failed to open csvfile."), TEXT("Error"), MB_OK);
			return {};
		}
		std::vector<std::vector<int>> data;
		std::string line;
		while (std::getline(ifs, line))
		{
			std::istringstream iss(line);
			std::vector<int> record;
			std::string field;
			while (std::getline(iss, field, ','))
			{
				record.push_back(std::stoi(field));
			}
			data.push_back(record);
		}
		return data;
	}

};

//getline(istream &is , string &str , char delim )
// is 进行读入操作的输入流
//str 用来存储读入的内容
//delim 终结符，遇到该字符停止读取操作，不写的话默认为回车，如定义2中的示例。