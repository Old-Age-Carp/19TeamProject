#pragma once
#define NOMINMAX
#include <windows.h>

#include <string>
#include <vector>
#include <memory>
#include <optional>


class ILogable;
class CGameManager;


class CPrinter
{
public:
	static void ClearScreen();
	static void ClearInputBuffer();
	static void Pause();
	static void PrintLine(const std::wstring& line);

	template<typename T>
	static T GetInput();

	static std::vector<std::wstring> WrapText(const std::wstring& text, size_t width);
	static std::wstring PadRight(const std::wstring& text, size_t width);

	static void PrintBoxes(
		const std::vector<std::wstring>& texts,
		size_t boxWidth,
		size_t minBoxHeight,
		size_t boxCount
	);

private:
};

std::wstring Trim(const std::wstring& str)
{
	if (str.empty()) return L"";

	size_t start = str.find_first_not_of(L" \t\r\n");
	size_t end = str.find_last_not_of(L" \t\r\n");

	if (start == std::wstring::npos) return L"";
	return str.substr(start, end - start + 1);
}

template<typename T>
std::optional<T> ParseInput(const std::wstring& input)
{
	static_assert(std::is_same_v<T, int> || std::is_same_v<T, std::wstring>,
		"Only int and wstring are supported");

	std::wstring trimmed = Trim(input);
	if (trimmed.empty()) return std::nullopt;

	if constexpr (std::is_same_v<T, int>)
	{
		try
		{
			size_t pos = 0;
			int value = std::stoi(trimmed, &pos);
			// 전체 문자열이 숫자로 변환되었는지 확인
			return (pos == trimmed.length()) ? std::optional(value) : std::nullopt;
		}
		catch (...)
		{
			return std::nullopt;
		}
	}
	else if constexpr (std::is_same_v<T, std::wstring>)
	{
		return trimmed;
	}
}

template<typename T>
T CPrinter::GetInput()
{
	// 타입 제한 검사
	static_assert(std::is_same_v<T, int> || std::is_same_v<T, std::wstring>,
		"Only int and wstring are supported");

	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	wchar_t buffer[256];
	DWORD charsRead = 0;

	if (!ReadConsoleW(hInput, buffer, 255, &charsRead, nullptr))
	{
		return std::nullopt;
	}

	// 개행 문자 제거
	std::wstring inputStr(buffer, charsRead);
	if (!inputStr.empty() && inputStr.back() == L'\n')
		inputStr.pop_back();
	if (!inputStr.empty() && inputStr.back() == L'\r')
		inputStr.pop_back();

	return ParseInput<T>(inputStr);
}
