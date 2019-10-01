// インクルード -------------------------------------------------------------------------------------
#include "DxLib.h"

#include "common.h"
#include "scene_title.h"

// 変数 --------------------------------------------------------------------------------------------
// キー用変数
char key_buf[MAX_KEY];

// シーン遷移用変数
extern int nextScene;

// インスタンス宣言 ---------------------------------------------------------------------------------
TITLE title;


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
	switch (title.state)
	{
	case INIT:
		///// 初期設定 /////
		title.state++;
		break;

	case NORMAL:
		///// 通常時 /////
        // debug用 ----------------------
        if (key_trg[KEY_INPUT_LSHIFT])
		{
			nextScene = SCENE_GAME;
		}
        //-------------------------------
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