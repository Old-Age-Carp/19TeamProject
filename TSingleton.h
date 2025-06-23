#pragma once

template <typename T>
class TSingleton
{
protected:
	TSingleton() {}
	virtual ~TSingleton() {}
private:
	TSingleton(const TSingleton&) = delete;
	TSingleton& operator = (const TSingleton&) = delete;
public:
	static T& getinstance()
	{
		static T instance;
		return instance;
	}
};
