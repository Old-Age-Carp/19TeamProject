#pragma once

#include <string>

enum class EGameState
{
	START,				//게임시작
	IDLE,				//기본상태-게임시작시
	BATTLE,				//배틀중
	SELECT,				//메뉴고르는중
	SHOP,				//상점
	LEVELUP,			//레벨업상태
	INVENTORY,			//인벤토리
	GAMEOVER,			//게임오버
	END
};

struct FItemData
{
	int id;
	std::wstring name;
	int value;

	virtual ~FItemData() = default;

	FItemData(int InID = 0, const std::wstring& InName = L"", int InValue = 0)
		:id(InID), name(InName), value(InValue) {
	}
};

struct FItemPotionData :public FItemData
{
	int healAmount;

	FItemPotionData(int InID = 0, const std::wstring& InName = L"", int InValue = 0, int InHealAmount = 0)
		:FItemData(InID, InName, InValue), healAmount(InHealAmount) {
	}
};

struct FItemWeaponData :public FItemData
{
	int attackBonus;
	int defenseBonus;
	int healthBonus;

	FItemWeaponData(int InID = 0, const std::wstring& InName = L"", int InValue = 0, int InAttackBonus = 0,
		int InDefenseBonus = 0, int InHealthBonus = 0)
		:FItemData(InID, InName, InValue),
		attackBonus(InAttackBonus), defenseBonus(InDefenseBonus), healthBonus(InHealthBonus) {
	}
};

struct FItemArmorData :public FItemData
{
	int defenseBonus;
	int healthBonus;

	FItemArmorData(int InID = 0, const std::wstring& InName = L"", int InValue = 0, int InDefenseBonus = 0, int InHealthBonus = 0)
		:FItemData(InID, InName, InValue), defenseBonus(InDefenseBonus), healthBonus(InHealthBonus) {
	}
};
