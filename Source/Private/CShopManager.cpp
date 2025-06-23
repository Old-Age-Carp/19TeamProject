#include "..\Public\CShopManager.h"

CShopManager* CShopManager::instance = nullptr;

CShopManager::CShopManager()
{
}

CShopManager::~CShopManager()
{
}

CShopManager* CShopManager::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new CShopManager();
	}
	return instance;
}

void CShopManager::DestroyInstance()
{
	if (instance != nullptr) {
		delete instance;
		instance = nullptr;
	}
}
