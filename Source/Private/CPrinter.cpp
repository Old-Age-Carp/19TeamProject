#define NOMINMAX
#include <windows.h>
#include <sstream>
#include <limits>
#include <iostream>
#include "CPrinter.h"
#include "CLogManager.h"
#include "CGameManager.h"

using namespace std;

void CPrinter::ClearScreen()
{
    system("cls");
}

void CPrinter::ClearInputBuffer() 
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void CPrinter::Pause() 
{
    system("pause");
}

void CPrinter::Print(const std::wstring& message)
{
    PrintLine(message);
}

void CPrinter::PrintAllLog(const vector<unique_ptr<ILogable>>& logs)
{
	vector<wstring> wrappedLog(logs.size() * 2);
    for (const unique_ptr<ILogable>& log : logs)
    {
        vector<wstring> wrapped = WrapText(log.get()->ToString(), 80); // 80은 박스 너비
        for (size_t i = 0; i < wrapped.size(); ++i)
        {
            if (i < wrappedLog.size())
            {
                wrappedLog[i] += wrapped[i];
            }
            else
            {
                wrappedLog.push_back(wrapped[i]);
            }
		}
	}
    PrintBoxes(wrappedLog, 80, wrappedLog.size() + 3, 1);
}

void CPrinter::PrintGameState(const CGameManager& gameManager)
{
    // 게임 매니저에서 현재 상태를 가져와 적절한 포맷으로 출력하기.
}

void CPrinter::PrintLine(const wstring& line)
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD written;
    WriteConsoleW(hOut, line.c_str(), static_cast<DWORD>(line.size()), &written, nullptr);
    WriteConsoleW(hOut, L"\n", 1, &written, nullptr);
}

vector<wstring> CPrinter::WrapText(const wstring& text, size_t width)
{
    vector<wstring> lines;
    for (size_t i = 0; i < text.length(); i += width)
    {
        lines.push_back(text.substr(i, width)); // 강제 분할
    }
    return lines;
}

wstring CPrinter::PadRight(const wstring& text, size_t width)
{
    if (text.length() >= width)
    {
        return text.substr(0, width);
    }

    return text + wstring(width - text.length(), L' ');
}

void CPrinter::PrintBoxes(
    const vector<wstring>& texts,
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
            vector<wstring> wrapped;

            if (i < texts.size())
            {
                wrapped = WrapText(texts[i], boxWidth); // boxWidth 전달
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
