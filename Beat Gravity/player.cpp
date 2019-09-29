// インクルード -------------------------------------------------------------------------------------
#include "DxLib.h"

#include "common.h"
#include "input.h"
#include "player.h"
#include "stage.h"

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
    pl.posX = 0;
    pl.posY = 0;
    pl.pivotX = 0;
    pl.pivotY = 0;
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
        // プレイヤーの中心座標を更新
        pl.pivotX = pl.posX + PLAYER_SIZE / 2;
        pl.pivotY = pl.posY + PLAYER_SIZE / 2;

        // debug用------------------
        if (key[KEY_INPUT_A])
        {
            pl.posX-=3;
        }
        if (key[KEY_INPUT_D])
        {
            pl.posX+=3;
        }
        if (key[KEY_INPUT_W])
        {
            pl.posY-=3;
        }
        if (key[KEY_INPUT_S])
        {
            pl.posY+=3;
        }
        if (detect_chip(pl.posX, pl.posY + 64, STAGE4) == 1 ||
            detect_chip(pl.posX + 64, pl.posY + 64, STAGE4) == 1)
        {
            pl.posY = pl.posY / 64 * 64;
        }
        //--------------------------
        break;
    }
}

// プレイヤーの描画処理
void player_draw(void)
{
    DrawGraph(pl.posX, pl.posY, pl.plHND, true);
    // debug用
    DrawBox(pl.posX, pl.posY, pl.posX+63,pl.posY+63,GetColor(1, 0, 0), FALSE);
}

// プレイヤーの終了処理
void player_end(void)
{
    DeleteGraph(pl.plHND);
}