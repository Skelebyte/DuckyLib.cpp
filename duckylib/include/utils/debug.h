#pragma once

#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <sstream>

using namespace std;

namespace DL
{
    enum Severity
    {
        MSG = 0,
        WRN = 1,
        ERR = 2
    };

    class Debug
    {
        public:
        static void Log(std::string message, Severity severity);

        private:
        static void WriteFile(const char *path, const char *content);
    };
}