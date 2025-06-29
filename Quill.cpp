#include "Quill.h"

#include <algorithm>
#include <iostream>
#include <fstream>

namespace ql
{
    void Quill::Run()
    {
        std::cout << "=== Quill ===" << std::endl;

        std::string input;

        while (true)
        {
            std::cout << lines.size() + 1 << "> ";
            std::getline(std::cin, input);

            if (input.empty())
            {
                lines.push_back("");
                continue;
            }

            if (input[0] == ':')
            {
                if (!HandleCommand(input))
                    break; // Quit command
            }
            else
            {
                lines.push_back(input);
            }
        }
    }


    bool Quill::HandleCommand(const string &command)
    {
        if (command == ":q")
        {
            std::cout << "Goodbye!" << std::endl;
            return false;
        }

        if (command == ":w")
            SaveFile();
        else if (command.substr(0, 2) == ":r" && command.length() > 3)
        {
            std::string file = command.substr(3);
            LoadFile(file);
        }
        else if (command == ":h")
            ShowHelp();
        else if (command == ":p")
            PrintLines();
        else if (command == ":c")
            ClearLines();
        else
            std::cout << "Unknown command: " << command << std::endl;
        return true;
    }

    bool Quill::SaveFile()
    {
        if (fileName.empty())
        {
            std::cout << "Enter filename: ";
            std::getline(std::cin, fileName);
        }

        std::ofstream file(fileName);
        if (!file.is_open())
        {
            std::cout << "Error: Could not save file!" << std::endl;
            return false;
        }

        for (const auto& line : lines)
            file << line << std::endl;

        file.close();
        std::cout << "File saved as: " << fileName << std::endl;

        return true;
    }


    bool Quill::LoadFile(const string& file)
    {
        std::ifstream infile(file);

        if (!infile.is_open())
        {
            std::cout << "Error: Could not load file: " << file << std::endl;
            return false;
        }

        lines.clear();
        fileName = file;
        std::string line;
        while (std::getline(infile, line))
            lines.push_back(line);
        infile.close();
        std::cout << "File loaded: " << file << " (" << lines.size() << " lines)" << std::endl;
        return true;
    }

    void Quill::PrintLines()
    {
        cout << "--- " << fileName << " ---" << endl;
        for (int i = 0; i < lines.size(); i++)
            cout << i + 1 << "| " << lines[i] << endl;
        cout << endl;
    }

    void Quill::ClearLines()
    {
        lines.clear();
        fileName.clear();
        cout << "Editor cleared." << endl;
    }

    void Quill::ShowHelp()
    {
        cout << "--- Help ---" << endl;
        cout << ":q          - Quit editor" << endl;
        cout << ":w          - Save file" << endl;
        cout << ":l <file>   - Load file" << endl;
        cout << ":p          - Print all lines" << endl;
        cout << ":c          - Clear all lines" << endl;
        cout << ":h          - Show this help" << endl;
    }

}