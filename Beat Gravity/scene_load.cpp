// インクルード -------------------------------------------------------------------------------------
#include "DxLib.h"

#include "common.h"
#include "scene_load.h"

// 変数 --------------------------------------------------------------------------------------------
// キー用変数
extern char key_buf[MAX_KEY];

// シーン遷移用変数
extern int nextScene;

// インスタンス宣言 ---------------------------------------------------------------------------------
LOAD load;


// 関数実体 ----------------------------------------------------------------------------------------
void load_initialize(void)
{
    load.state = 0;
    load.timer = 0;
    load.rnd = GetRand(5);
    load.transition_flg = false;
    LoadDivGraph("Data\\Images\\load_bg.png", 13, 13, 1, 1920, 1080, load.bgHND);
    load.bg[0] = LoadGraph("Data\\Images\\load1.png");
    load.bg[1] = LoadGraph("Data\\Images\\load2.png");
    load.bg[2] = LoadGraph("Data\\Images\\load3.png");
    load.bg[3] = LoadGraph("Data\\Images\\load4.png");
    load.bg[4] = LoadGraph("Data\\Images\\load5.png");
    load.bg[5] = LoadGraph("Data\\Images\\load6.png");
}

void load_update(void)
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
    switch (load.state)
    {
    case INIT:
        ///// 初期設定 /////
        load.state = NORMAL;
        break;

    case NORMAL:
        ///// 通常時 /////
        // debug用 ----------------------
        //if (key_trg[KEY_INPUT_1])nextScene = SCENE_TITLE;
        //if (key_trg[KEY_INPUT_2])nextScene = SCENE_SELECT;
        //if (key_trg[KEY_INPUT_3])nextScene = SCENE_LOAD;
        //if (key_trg[KEY_INPUT_4])nextScene = SCENE_GAME;
        //if (key_trg[KEY_INPUT_5])nextScene = SCENE_RESULT;
        //-------------------------------
        if (load.timer > 200)
        {
            nextScene = SCENE_GAME;
        }
        break;
    }
    load.timer++;
}

void load_draw(void)
{
    DrawGraph(0, 0, load.bgHND[load.timer / 5 % 13], true);
    DrawGraph(0, 0, load.bg[load.rnd], true);

    // debug用 ---------------------------------------------------------
    //DrawFormatString(0, 0, GetColor(255, 255, 255), "シーン切り替え");
    //DrawFormatString(0, 20, GetColor(255, 255, 255), "title:1キー");
    //DrawFormatString(0, 40, GetColor(255, 255, 255), "select:2キー");
    //DrawFormatString(0, 60, GetColor(255, 255, 255), "load:3キー");
    //DrawFormatString(0, 80, GetColor(255, 255, 255), "game:4キー");
    //DrawFormatString(0, 100, GetColor(255, 255, 255), "result:5キー");
    //---------------------------------------------------------------
}

void load_end(void)
{
    for (int i = 0; i < 13; i++)
    {
        DeleteGraph(load.bgHND[i]);
    }
    for (int i = 0; i < 6; i++)
    {
        DeleteGraph(load.bg[i]);
    }
}