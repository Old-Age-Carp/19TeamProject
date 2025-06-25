#pragma once
#define NOMINMAX
#include <windows.h>

#include <string>
#include <vector>
#include <memory>
#include <optional>

// 한글 출력이 안되는 문제는 링크 참고
// https://www.notion.so/teamsparta/19-1ff2dc3ef514807b9a50e62984d74000 

class ILogable;
class CPrinter
{
public:
	static void ClearScreen();
	static void Pause();
	static void PrintLine(const std::wstring& line);
	static std::wstring Trim(const std::wstring& str);

	template<typename T>
	static std::optional<T> GetInput();
	template<typename T>
	static std::optional<T> ParseInput(const std::wstring& input);

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

template<typename T>
std::optional<T> CPrinter::ParseInput(const std::wstring& input)
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
std::optional<T> CPrinter::GetInput()
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
