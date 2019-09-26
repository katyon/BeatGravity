// インクルード -------------------------------------------------------------------------------------
#include "DxLib.h"

#include "common.h"
#include "input.h"
#include "player.h"

// 変数 --------------------------------------------------------------------------------------------
// キー用変数
extern char key_buf[MAX_KEY];

// シーン遷移用変数
extern int nextScene;

// インスタンス宣言 ---------------------------------------------------------------------------------
PLAYER pl;

// 関数実体 ----------------------------------------------------------------------------------------
// プレイヤーの初期設定
void player_initialize(void)
{
    pl.state = 0;
    pl.plHND = LoadGraph("Data\\Images\\player.png");
}

// プレイヤーの更新処理
void player_update(void)
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
    switch (pl.state)
    {
    case INIT:
        ///// 初期設定 /////
        pl.state++;
        break;

    case NORMAL:
        ///// 通常時 /////

        break;
    }
}

// プレイヤーの描画処理
void player_draw(void)
{
    DrawGraph(0, 0, pl.plHND, true);
}

// プレイヤーの終了処理
void player_end(void)
{
    DeleteGraph(pl.plHND);
}