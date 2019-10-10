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
	title.timer = 0;
	title.transition_flg = false;
	title.bgHND = LoadGraph("Data\\Images\\title_bg.png");
    title.BGM = LoadSoundMem("Data\\Sounds\\titleBGM.ogg");
    title.decideSE = LoadSoundMem("Data\\Sounds\\decideSE.ogg");
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
        PlaySoundMem(title.BGM, DX_PLAYTYPE_LOOP, true);

        title.state = NORMAL;
		break;

	case NORMAL:
		///// 通常時 /////
        // debug用 ----------------------
        if (key_trg[KEY_INPUT_1])nextScene = SCENE_TITLE;
        if (key_trg[KEY_INPUT_2])nextScene = SCENE_SELECT;
        if (key_trg[KEY_INPUT_3])nextScene = SCENE_LOAD;
        if (key_trg[KEY_INPUT_4])nextScene = SCENE_GAME;
        if (key_trg[KEY_INPUT_5])nextScene = SCENE_RESULT;
        //-------------------------------
        if (key_trg[KEY_INPUT_SPACE])
        {
            PlaySoundMem(title.decideSE, DX_PLAYTYPE_BACK, true);
            nextScene = SCENE_SELECT;
        }
		break;
	}
	title.timer++;
}

// タイトルの描画処理
void title_draw(void)
{
	DrawGraph(0, 0, title.bgHND, false);

    // debug用 ---------------------------------------------------------
    DrawFormatString(0, 0, GetColor(255, 255, 255), "シーン切り替え");
    DrawFormatString(0, 20, GetColor(255, 255, 255), "title:1キー");
    DrawFormatString(0, 40, GetColor(255, 255, 255), "select:2キー");
    DrawFormatString(0, 60, GetColor(255, 255, 255), "load:3キー");
    DrawFormatString(0, 80, GetColor(255, 255, 255), "game:4キー");
    DrawFormatString(0, 100, GetColor(255, 255, 255), "result:5キー");
    //---------------------------------------------------------------
}

// タイトルの終了処理
void title_end(void)
{
	DeleteGraph(title.bgHND);
    DeleteSoundMem(title.decideSE);
    //DeleteSoundMem(title.BGM);
}