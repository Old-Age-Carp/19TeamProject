#pragma once

#include <string>
#include "define.h"

class CItem
{
private:
	const FItemData* ItemDefinition;

	int CurrentStack;
	bool bIsEquipped;

public:
	CItem(const FItemData* InDefinition, int InStack = 1);

	void Use();

	int GetID() const;
	std::wstring GetName() const;
	int GetValue() const;
	int GetCurrentStack() const;
	bool IsEquipped() const;

	void SetCurrentStack(int NewStack);
	void SetEquipped(bool bEquipped);

	~CItem() = default;
};
