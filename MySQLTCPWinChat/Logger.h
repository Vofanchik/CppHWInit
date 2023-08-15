#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <mutex>
#include <shared_mutex>
#include <ctime>

class Logger
{
private:
    std::ofstream _logFile;
    mutable std::shared_mutex _logMutex;
	std::time_t dtimel = std::time(nullptr);


public:
    Logger() {
		std::ifstream logFileCheck("log.txt");
		if (!logFileCheck)
		{
			std::cout << "Error: log.txt doesnt exists" << std::endl;
			std::ofstream fileCreate("log.txt");
			if (fileCreate)
			{
				fileCreate << asctime(localtime(&dtimel)) << "log file created " << std::endl;
				fileCreate.close();
				_logFile.open("log.txt", std::ios::app);
			}
			else
			{
				std::cout << "\nError: when create log.txt" << std::endl;
			}
		}
		else
		{
			_logFile.open("log.txt", std::ios::app);
		}
	};
    ~Logger() {
		if (_logFile.is_open())
		{
			_logFile.close();
		}
	};

    void writeLog(const std::string& logMessage)
	{
		std::unique_lock<std::shared_mutex> lock(_logMutex);
		if (_logFile.is_open())
		{
			_logFile << logMessage << std::endl;
		}
		else
		{
			std::cout << "\nError" << std::endl;
		}
	};
    void readLog()
	{
		std::shared_lock<std::shared_mutex> lock(_logMutex);
		std::ifstream inputFile("log.txt");

		if (inputFile.is_open())
		{
			std::string line;
			while (std::getline(inputFile, line))
			{
				std::cout << line << std::endl;
			}

			inputFile.close();
		}
	};

};

