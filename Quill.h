#pragma once

#include  <vector>
#include  <string>

using namespace std;

namespace ql
{
    class Quill
    {
    private:
        vector<string> lines;
        string fileName;
    public:
        void Run();
    private:
        bool HandleCommand(const string& command);
        bool SaveFile();
        bool LoadFile(const string& file);
        void PrintLines();
        void ClearLines();
        void ShowHelp();
    };
}