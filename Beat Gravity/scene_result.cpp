// インクルード -------------------------------------------------------------------------------------
#include "DxLib.h"

#include "common.h"
#include "scene_game.h"
#include "ranking.h"
#include "scene_result.h"

// 変数 --------------------------------------------------------------------------------------------
// キー用変数
extern char key_buf[MAX_KEY];


// シーン遷移用変数
extern int nextScene;

// インスタンス宣言 ---------------------------------------------------------------------------------
RESULT result;

// 関数実体 ----------------------------------------------------------------------------------------

void result_initialize(void)
{
    result.state = 0;
    result.timer = 0;
    result.transition_flg = false;
    result.bgHND = LoadGraph("Data\\Images\\result_bg.png");
}

void result_update(void)
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
    switch (result.state)
    {
    case INIT:
        ///// 初期設定 /////
        result.state++;
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
        
        // ランキング

        if (R_flg == true) {
            rank_update();
            R_flg = false;
        }
        break;
    }
    result.timer++;
}

void result_draw(void)
{
    DrawGraph(0, 0, result.bgHND, false);

    // debug用 ---------------------------------------------------------
    DrawFormatString(0, 0, GetColor(255, 255, 255), "シーン切り替え");
    DrawFormatString(0, 20, GetColor(255, 255, 255), "title:1キー");
    DrawFormatString(0, 40, GetColor(255, 255, 255), "select:2キー");
    DrawFormatString(0, 60, GetColor(255, 255, 255), "load:3キー");
    DrawFormatString(0, 80, GetColor(255, 255, 255), "game:4キー");
    DrawFormatString(0, 100, GetColor(255, 255, 255), "result:5キー");
    //---------------------------------------------------------------
}

void result_end(void)
{
    DeleteGraph(result.bgHND);
}