// インクルード -------------------------------------------------------------------------------------
#include "DxLib.h"

#include "common.h"
#include "scene_title.h"
// 実体宣言 ----------------------------------------------------------------------------------------
struct TITLE title;

extern int nextScene;

// 関数実体 ----------------------------------------------------------------------------------------
// タイトルの初期設定
void title_initialize(void)
{
	title.state = 0;
	title.titmer = 0;
	title.transition_flg = false;
	title.bgHND = LoadGraph("Data\\Images\\title_bg.png");
}

// タイトルの更新処理
void title_update(void)
{
	switch (title.state)
	{
	case INIT:
		///// 初期設定 /////
		title.state++;
		break;

	case NORMAL:
		///// 通常時 /////
		if (CheckHitKey(KEY_INPUT_SPACE) == 1)
		{
			nextScene = SCENE_GAME;
		}
		title_draw();
		break;
	}
	title.titmer++;
}

// タイトルの描画処理
void title_draw(void)
{
	DrawGraph(0, 0, title.bgHND, false);
}

// タイトルの終了処理
void title_end(void)
{
	DeleteGraph(title.bgHND);
}