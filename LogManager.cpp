#include "LogManager.h"

/// <param name="log">내용</param>
/// <returns>몇 번째 로그인지</returns>
int CLogManager::AddLog(std::unique_ptr<ILogable> log)
{
	logs.push_back(std::move(log));
    return 0;
}
