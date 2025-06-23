#include "CLogManager.h"

using namespace std;
/// <param name="log">내용</param>
/// <returns>몇 번째 로그인지</returns>
int CLogManager::AddLog(std::unique_ptr<ILogable> log)
{
	mlogs.push_back(std::move(log));
    return mlogs.size();
}

int CLogManager::AddLog(std::wstring logText)
{
	mlogs.push_back(make_unique<LogWString>(logText));
	return mlogs.size();
}
