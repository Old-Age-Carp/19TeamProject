#pragma once
#include <vector>
#include <memory>
#include <string>
#include "TSingleton.h"

class ILogable
{
public:
	virtual ~ILogable() = default;  // 가상 소멸자 추가
	virtual std::wstring ToString() const = 0;
};

class LogWString : public ILogable
{
	std::wstring mlog;
public:
	explicit LogWString(const std::wstring& string) : mlog(string) {}
	explicit LogWString(std::wstring&& string) : mlog(std::move(string)) {}
	// const 메서드로 오버라이드 + 명시적 override
	std::wstring ToString() const override
	{
		return mlog;
	};
};

class CLogManager : public TSingleton<CLogManager>
{
private:
	std::vector<std::unique_ptr<ILogable>> mlogs;

public:
	inline int GetLogCount() const { return (int)mlogs.size(); }
	inline const std::vector<std::unique_ptr<ILogable>>& GetLogs() const { return mlogs; }
	int AddLog(std::unique_ptr<ILogable> log);
	int AddLog(std::wstring logText);

	~CLogManager() = default;
};

