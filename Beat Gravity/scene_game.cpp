// インクルード -------------------------------------------------------------------------------------
#include "DxLib.h"

#include "common.h"
#include "input.h"
#include "player.h"
#include "scene_game.h"
#include "stage.h"

// 変数 --------------------------------------------------------------------------------------------
// キー用変数
extern char key_buf[MAX_KEY];

// シーン遷移用変数
extern int nextScene;

// インスタンス宣言 ---------------------------------------------------------------------------------
GAME game;

// 関数実体 ----------------------------------------------------------------------------------------
// ゲームの初期設定
void game_initialize(void)
{
	game.state = 0;
	game.titmer = 0;
	game.transition_flg = false;
	game.bgHND = LoadGraph("Data\\Images\\game_bg.png");
}

// ゲームの更新処理
void game_update(void)
{
#pragma region KeyUpdate
    //キーの設定
    char key[MAX_KEY];              //押されている間処理が続く
    char key_trg[MAX_KEY] = { 0 };  //押された瞬間だけ処理

    GetHitKeyStateAll(key);

    for (int n = 0; n < MAX_KEY; n++)
    {
        if (key[n] && !(key_buf[n])) key_trg[n] = key[n];
        key_buf[n] = key[n];
    }
#pragma endregion
	switch (game.state)
	{
	case INIT:
		///// 初期設定 /////
        player_initialize();
        stage_initialize();
		game.state++;
		break;

	case NORMAL:
		///// 通常時 /////
		// debug用-------------------------
		if (key_trg[KEY_INPUT_SPACE])
		{
			nextScene = SCENE_TITLE;
		}
        //---------------------------------
		game_draw();
		break;
	}
	game.titmer++;
}

// ゲームの描画処理
void game_draw(void)
{
	DrawGraph(0, 0, game.bgHND, false);
    stage_draw();
    player_draw();
}

// ゲームの終了処理
void game_end(void)
{
	DeleteGraph(game.bgHND);
    stage_end();
    player_end();
}