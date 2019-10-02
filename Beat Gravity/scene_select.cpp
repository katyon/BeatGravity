// インクルード -------------------------------------------------------------------------------------
#include "DxLib.h"

#include "common.h"
#include "scene_select.h"

// 変数 --------------------------------------------------------------------------------------------
// キー用変数
extern char key_buf[MAX_KEY];

// シーン遷移用変数
extern int nextScene;

// インスタンス宣言 ---------------------------------------------------------------------------------
SELECT Select;


// 関数実体 ----------------------------------------------------------------------------------------
void select_initialize(void)
{
    Select.state = 0;
    Select.timer = 0;
    Select.transition_flg = false;
    Select.bgHND = LoadGraph("Data\\Images\\select_bg.png");
}

void select_update(void)
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
    switch (Select.state)
    {
    case INIT:
        ///// 初期設定 /////
        Select.state++;
        break;

    case NORMAL:
        ///// 通常時 /////
        // debug用 ----------------------
        if (key_trg[KEY_INPUT_1])nextScene = SCENE_TITLE;
        if (key_trg[KEY_INPUT_2])nextScene = SCENE_SELECT;
        if (key_trg[KEY_INPUT_3])nextScene = SCENE_LOAD;
        if (key_trg[KEY_INPUT_4])nextScene = SCENE_GAME;
        if (key_trg[KEY_INPUT_1])nextScene = SCENE_RESULT;
        //-------------------------------
        break;
    }
    Select.timer++;
}

void select_draw(void)
{
    DrawGraph(0, 0, Select.bgHND, false);
}

void select_end(void)
{
    DeleteGraph(Select.bgHND);
}