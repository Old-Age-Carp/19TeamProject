#pragma once
#include <string>
#include <vector>
#include <memory>

class ILogable;

static class CPrinter
{
public:
    static void ClearScreen();
    static void ClearInputBuffer();
    static void Pause();
    static void Print(const std::wstring& message);
	static void PrintAllLog(const std::vector<std::unique_ptr<ILogable>>& log);

    static std::wstring PlayerInfoToString();
    static std::wstring BattleInfoToString();

    static std::vector<std::wstring> WrapText(const std::wstring& text, size_t width);
    static std::wstring PadRight(const std::wstring& text, size_t width);

    static void PrintBoxes(
        const std::vector<std::wstring>& texts,
        size_t boxWidth,
        size_t minBoxHeight,
        size_t boxCount
    );

private:
    static void PrintLine(const std::wstring& line);
};
