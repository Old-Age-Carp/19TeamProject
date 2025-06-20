#pragma once
#include <vector>
#include <memory>

class ILogable
{
public:
	virtual class wstring ToString() const = 0;
	virtual ~ILogable() = default;
};
// 
class LogManager
{
private:
	std::vector<std::unique_ptr<ILogable>> logs;

public:
	void AddLog(std::unique_ptr<ILogable> log);
};

