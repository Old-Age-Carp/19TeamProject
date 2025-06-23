#pragma once
#include <vector>
#include <memory>
#include <string>
#include "CGameItem.h"

class ILogable
{
public:
	virtual std::wstring ToString() const = 0;
};

class CLogManager : public Singleton<CLogManager>
{
private:
	std::vector<std::unique_ptr<ILogable>> mlogs;

public:
	inline int GetLogCount() const { return (int)mlogs.size(); }
	inline const std::vector<std::unique_ptr<ILogable>>& GetLogs() const { return mlogs; }
	int AddLog(std::unique_ptr<ILogable> log);

	~CLogManager() = default;
};

