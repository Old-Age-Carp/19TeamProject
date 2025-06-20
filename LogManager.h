#pragma once
#include <vector>
#include <memory>
#include <string>

class ILogable
{
public:
	virtual std::wstring ToString() const = 0;
};
// 
class CLogManager
{
private:
	std::vector<std::unique_ptr<ILogable>> logs;

public:
	inline int GetLogCount() const { return logs.size(); }
	int AddLog(std::unique_ptr<ILogable> log);
	inline const std::vector<std::unique_ptr<ILogable>>& GetLogs() const { return logs; }

	~CLogManager() = default;
};

