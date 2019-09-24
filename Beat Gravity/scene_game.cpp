// インクルード -------------------------------------------------------------------------------------
#include "DxLib.h"

#include "common.h"
#include "scene_game.h"
// 実体宣言 ----------------------------------------------------------------------------------------
struct GAME game;

extern int nextScene;

// 関数実体 ----------------------------------------------------------------------------------------
// ゲームの初期設定
void game_initialize(void)
{
	game.state = 0;
	game.titmer = 0;
	game.transition_flg = false;
	game.bgHND = LoadGraph("Data\\Images\\game_bg1.png");
}

// ゲームの更新処理
void game_update(void)
{
	switch (game.state)
	{
	case INIT:
		///// 初期設定 /////
		game.state++;
		break;

	case NORMAL:
		///// 通常時 /////
		// debug用
		if (CheckHitKey(KEY_INPUT_1) == 1)
		{
			nextScene = SCENE_TITLE;
		}
		game_draw();
		break;
	}
	game.titmer++;
}

// ゲームの描画処理
void game_draw(void)
{
	DrawGraph(0, 0, game.bgHND, false);
}

// ゲームの終了処理
void game_end(void)
{
	DeleteGraph(game.bgHND);
}