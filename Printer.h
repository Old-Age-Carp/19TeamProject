#pragma once
#include <string>
#include <vector>

class Printer
{
public:
    void ClearScreen() const;
    void ClearInputBuffer() const;
    void Pause() const;
    void Print(const std::wstring& message) const;

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
