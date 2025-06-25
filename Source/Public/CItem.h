#pragma once

#include <string>
#include "define.h"

class CItem
{
private:
	const FItemData* ItemDefinition;

	int CurrentStack = 0;
	bool bIsEquipped = false;
	//초기화시 값설정 준식

public:
	CItem(const FItemData* InDefinition, int InStack = 1);
	//준식
	const FItemData* Get_pItemData()	{ return ItemDefinition; };
	bool* Get_pEquipped()				{ return &bIsEquipped; };
	//준식

	void Use();

	int GetID() const;
	std::wstring GetName() const;
	int GetValue() const;
	int GetCurrentStack() const;
	bool IsEquipped() const;

	void SetCurrentStack(int NewStack);
	void AddCurrentStack(int NewStack); //준식
	void SetEquipped(bool bEquipped);

	~CItem() = default;
};
