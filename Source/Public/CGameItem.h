#pragma once

#include <string>
#include <map>

template <typename T>
class Singleton {
protected:
	Singleton() {}
	virtual ~Singleton() {}
private:
	Singleton(const Singleton&) = delete;
	Singleton& operator = (const Singleton&) = delete;
public:
	static T& getInstance() {
		static T instance;
		return instance;
	}
};

class StaticDataManager : public Singleton<StaticDataManager> {
	friend class Singleton<StaticDataManager>;

public:
	struct ItemData {
		int id;
		std::wstring name;
		int value;
		int attackBonus;   //공격력 추가
		int defenseBonus;  //방어력 추가
		int healthBonus;   //체력 추가
		int healAmount;    //체력 회복량
		std::wstring type;
	};
	const ItemData* GetItemData(int id) const;

private:
	std::map<int, ItemData> itemTable;
	StaticDataManager();
	void loadItemData();
};

