#include "Printer.h"
#define NOMINMAX
#include <windows.h>
#include <sstream>
#include <limits>
#include <iostream>

using namespace std;

void Printer::ClearScreen() const
{
    system("cls");
}

void Printer::ClearInputBuffer() const
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void Printer::Pause() const
{
    system("pause");
}

void Printer::Print(const std::wstring& message) const
{
    PrintLine(message);
}

void Printer::PrintLine(const std::wstring& line)
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD written;
    WriteConsoleW(hOut, line.c_str(), static_cast<DWORD>(line.size()), &written, nullptr);
    WriteConsoleW(hOut, L"\n", 1, &written, nullptr);
}

std::vector<std::wstring> Printer::WrapText(const std::wstring& text, size_t width)
{
    vector<wstring> lines;
    wstringstream iss(text);
    wstring word, line;

    while (iss >> word)
    {
        if (line.length() + word.length() + 1 > width)
        {
            lines.push_back(line);
            line = word;
        }
        else
        {
            if (!line.empty()) line += L" ";
            line += word;
        }
    }

    if (!line.empty())
    {
        lines.push_back(line);
    }

    return lines;
}

std::wstring Printer::PadRight(const std::wstring& text, size_t width)
{
    if (text.length() >= width)
    {
        return text.substr(0, width);
    }

    return text + std::wstring(width - text.length(), L' ');
}

void Printer::PrintBoxes(
    const std::vector<std::wstring>& texts,
    size_t boxWidth,
    size_t boxHeight,
    size_t boxCount
)
{
    vector<vector<wstring>> allBoxLines;

    for (size_t i = 0; i < boxCount; ++i)
    {
        vector<wstring> wrapped;

        if (i < texts.size())
        {
            wstringstream ss(texts[i]);
            wstring line;

            while (getline(ss, line))
            {
                auto w = WrapText(line, boxWidth);
                wrapped.insert(wrapped.end(), w.begin(), w.end());
            }
        }

        while (wrapped.size() < boxHeight)
        {
            wrapped.push_back(L"");
        }

        if (wrapped.size() > boxHeight)
        {
            wrapped.resize(boxHeight);
        }

        allBoxLines.push_back(wrapped);
    }

    wstring top = L"╔";
    for (size_t i = 0; i < boxCount; ++i)
    {
        top += wstring(boxWidth, L'═');
        top += (i == boxCount - 1 ? L"╗" : L"╦");
    }
    PrintLine(top);

    for (size_t line = 0; line < boxHeight; ++line)
    {
        wstring row = L"║";
        for (size_t b = 0; b < boxCount; ++b)
        {
            row += PadRight(allBoxLines[b][line], boxWidth);
            row += L"║";
        }
        PrintLine(row);
    }

    wstring bottom = L"╚";
    for (size_t i = 0; i < boxCount; ++i)
    {
        bottom += wstring(boxWidth, L'═');
        bottom += (i == boxCount - 1 ? L"╝" : L"╩");
    }
    PrintLine(bottom);
}
