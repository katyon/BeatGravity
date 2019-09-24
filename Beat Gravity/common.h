#pragma once
// 定数 ----------------------------------------------------------------
#define GAME_SCREEN_WIDTH	(1280)					// ゲーム画面の幅
#define GAME_SCREEN_HEIGHT	(720)					// ゲーム画面の高さ
#define PI	(3.1415926535897932384626433832795f)	// π

// シーン管理用定数
enum SCENE_CASE
{
	SCENE_TITLE, SCENE_GAME, SCENE_RESULT
};

// state用定数
enum STATE
{
	INIT,NORMAL
};