#pragma once


enum class EGameState
{
	IDLE,				//기본상태-게임시작시
	BATTLE,				//배틀중
	SELECT,				//메뉴고르는중
	SHOP,				//상점
	LEVELUP,			//레벨업상태
	INVENTORY,			//인벤토리
	GAMEOVER,			//게임오버
	END
};
