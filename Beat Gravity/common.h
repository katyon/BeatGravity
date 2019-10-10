#pragma once
// 定数 ----------------------------------------------------------------
#define GAME_SCREEN_WIDTH	(1920)  // ゲーム画面の幅
#define GAME_SCREEN_HEIGHT	(1080)  // ゲーム画面の高さ
#define PI          (3.1415926535)  // 円周率
#define CHIP_SIZE           (60)    // マップチップの一つ当たりの大きさ
#define MAX_KEY	(256)

// シーン管理用定数
enum SCENE_CASE
{
	SCENE_TITLE, SCENE_SELECT,SCENE_LOAD,SCENE_GAME, SCENE_RESULT
};

// state用定数
enum STATE
{
    INIT, NORMAL, NEXT, RETRY, POSE
};