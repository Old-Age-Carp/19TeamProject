#pragma once
class CShopManager
{
	
private:
	static CShopManager* instance; //싱글톤 선언

	CShopManager(); // 생성자
	~CShopManager(); //소멸자



public:
	static CShopManager* GetInstance();
	static void				DestroyInstance();


protected:

};

