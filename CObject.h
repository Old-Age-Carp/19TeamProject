#pragma once
#include <string>

class CObject {
protected:
    int id;
    std::wstring name; 
    int atk;
    int def;
    int hp;

public:
    CObject(int id, const std::wstring& name, int atk, int def, int hp);

    // Getter 함수들
    int GetID() const;
    const std::wstring& GetName() const; 
    int GetAtk() const;
    int GetDef() const;
    int GetHP() const;

   
};
