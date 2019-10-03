// インクルード -------------------------------------------------------------------------------------
#include "DxLib.h"

#include "common.h"
#include "scene_game.h"
#include "stage.h"

// 変数 --------------------------------------------------------------------------------------------
// キー用変数
extern char key_buf[MAX_KEY];

// シーン遷移用変数
extern int nextScene;

// インスタンス宣言 ---------------------------------------------------------------------------------
GAME game;

PLAYER pl;

// 関数実体 ----------------------------------------------------------------------------------------
// ゲームの初期設定
void game_initialize(void)
{
	game.state = 0;
	game.timer = 0;
    game.score = 0;
    game.bgposX = 0;
    game.bgposY = 0;
    game.bgspeed = 5;
    game.deathflg = false;
    game.clearflg = false;
    game.choice = true;
    game.bgHND = LoadGraph("Data\\Images\\game_bg.png");
    int a=game.reHND[0] = LoadGraph("Data\\Images\\retry_yes.png");
    int b=game.reHND[1] = LoadGraph("Data\\Images\\retry_no.png");
}

// プレイヤーの初期設定
void player_initialize(void)
{
    pl.state = 0;
    pl.posX = GAME_SCREEN_WIDTH/2;
    pl.posY = GAME_SCREEN_HEIGHT/2;
    pl.speed = 8;
    pl.jumppower = 20;
    pl.gravity = GRAVITY;
    pl.gravityflg = true;
    pl.grandflg = false;
    pl.plHND = LoadGraph("Data\\Images\\player.png");
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
#pragma region INIT
        ///// 初期設定 /////
        game_initialize();
        player_initialize();
        stage_initialize();

        game.state++;
        break;
#pragma endregion
    case NORMAL:
#pragma region NORMAL
        ///// 通常時 /////
        // debug用-------------------------
        if (key_trg[KEY_INPUT_1])nextScene = SCENE_TITLE;
        if (key_trg[KEY_INPUT_2])nextScene = SCENE_SELECT;
        if (key_trg[KEY_INPUT_3])nextScene = SCENE_LOAD;
        if (key_trg[KEY_INPUT_4])nextScene = SCENE_GAME;
        if (key_trg[KEY_INPUT_5])nextScene = SCENE_RESULT;

        if (key_trg[KEY_INPUT_LSHIFT])
        {
            game.clearflg = true;
        }
        if (key_trg[KEY_INPUT_Z])
        {
            if (pl.gravityflg == true)
            {
                pl.gravityflg = false;
            }
            else
            {
                pl.gravityflg = true;
            }
        }
        if (key_trg[KEY_INPUT_X])
        {
            game_end();
            game.state = INIT;
        }
        //---------------------------------

        // シーン遷移
        if (game.clearflg == true)
        {
            nextScene = SCENE_RESULT;
        }

        if (game.deathflg == true)
        {
            game.state++;
        }
        else
        {
            ///// プレイヤーの更新 /////
            // 通常重力
            if (pl.gravityflg == true)
            {
                // ジャンプ
                if (pl.grandflg == true && key[KEY_INPUT_SPACE])
                {
                    pl.gravity -= pl.jumppower;
                }

                // 重力と右移動
                pl.posY += pl.gravity;
                pl.posX += pl.speed;

                // マップチップごとの挙動
                // 無
                if (detect_chip(pl.posX, pl.posY + CHIP_SIZE - 1) == EMPTY ||
                    detect_chip(pl.posX + CHIP_SIZE - 1, pl.posY + CHIP_SIZE - 1) == EMPTY)
                {
                    pl.grandflg = false;
                    pl.gravity += GRAVITY;
                }
                // 地上
                if (detect_chip(pl.posX, pl.posY + CHIP_SIZE - 1) == BOTTOM ||
                    detect_chip(pl.posX + CHIP_SIZE - 1, pl.posY + CHIP_SIZE - 1) == BOTTOM)
                {
                    // 移動制限
                    pl.posY = pl.posY / CHIP_SIZE * CHIP_SIZE;

                    pl.grandflg = true;
                    pl.gravity = 0;
                }
                // 壁(左)
                if (detect_chip(pl.posX + CHIP_SIZE - 1, pl.posY) == LEFT ||
                    detect_chip(pl.posX + CHIP_SIZE - 1, pl.posY + CHIP_SIZE - 1) == LEFT)
                {
                    // 死亡判定
                    game.deathflg = true;
                }
            }
            // 反転重力
            else
            {
                // ジャンプ
                if (pl.grandflg == true && key[KEY_INPUT_SPACE])
                {
                    pl.gravity -= pl.jumppower;
                }

                // 重力と右移動
                pl.posY -= pl.gravity;
                pl.posX += pl.speed;

                // マップチップごとの挙動
                // 無
                if (detect_chip(pl.posX, pl.posY) == EMPTY ||
                    detect_chip(pl.posX + CHIP_SIZE - 1, pl.posY) == EMPTY)
                {
                    pl.grandflg = false;
                    pl.gravity += GRAVITY;
                }
                // 天井
                if (detect_chip(pl.posX, pl.posY) == TOP ||
                    detect_chip(pl.posX + CHIP_SIZE - 1, pl.posY) == TOP)
                {
                    // 移動制限
                    pl.posY = pl.posY / CHIP_SIZE * CHIP_SIZE + CHIP_SIZE;

                    pl.grandflg = true;
                    pl.gravity = 0;
                }
            }
            // 背景スクロール処理
            game.bgposX -= game.bgspeed;
            if (game.bgposX + GAME_SCREEN_WIDTH < 0)
            {
                game.bgposX = 0;
            }
        }
        // debug用------------------
        //if (key[KEY_INPUT_LEFT])
        //{
        //    pl.posX -= pl.speed;
        //}
        //if (key[KEY_INPUT_RIGHT])
        //{
        //    pl.posX += pl.speed;
        //}
        //if (key[KEY_INPUT_UP])
        //{
        //    pl.posY -= pl.speed;
        //}
        //if (key[KEY_INPUT_DOWN])
        //{
        //    pl.posY += pl.speed;
        //}
        //---------------------------
        break;
#pragma endregion
    case RETRY:
#pragma region RETRY
        ///// リトライ /////
        if (key_trg[KEY_INPUT_UP])
        {
            game.choice = true;
        }
        if (key_trg[KEY_INPUT_DOWN])
        {
            game.choice = false;
        }

        if (key_trg[KEY_INPUT_SPACE])
        {
            if (game.choice == true)
            {
                game_end();
                game.state = INIT;
            }
            else
            {
                nextScene = SCENE_TITLE;
            }
        }

        break;
#pragma endregion
    }

	game.timer++;
}

// ゲームの描画処理
void game_draw(void)
{
    // 背景
	DrawGraph(game.bgposX, game.bgposY, game.bgHND, false);
    DrawGraph(game.bgposX + GAME_SCREEN_WIDTH, 0, game.bgHND, false);

    stage_draw();
    player_draw();

    if (game.state == RETRY)
    {
        retry_draw();
    }
    // debug用 ------------------------------------------------------------------------------
    DrawFormatString(0, 0, GetColor(255, 255, 255), "シーン切り替え");
    DrawFormatString(0, 20, GetColor(255, 255, 255), "title:1キー");
    DrawFormatString(0, 40, GetColor(255, 255, 255), "select:2キー");
    DrawFormatString(0, 60, GetColor(255, 255, 255), "load:3キー");
    DrawFormatString(0, 80, GetColor(255, 255, 255), "game:4キー");
    DrawFormatString(0, 100, GetColor(255, 255, 255), "result:5キー");
    DrawFormatString(0, 120, GetColor(255, 255, 255), "重力反転:Zキー");
    DrawFormatString(0, 140, GetColor(255, 255, 255), "リセット:Xキー");
    
    DrawFormatString(150, 0, GetColor(255, 255, 255), "game.timer:%d", game.timer);
    DrawFormatString(150, 20, GetColor(255, 255, 255), "game.score:%d", game.score);
    DrawFormatString(150, 40, GetColor(255, 255, 255), "game.deathflg:%d", game.deathflg);
    DrawFormatString(150, 60, GetColor(255, 255, 255), "game.clearflg:%d", game.clearflg);

    DrawFormatString(300, 0, GetColor(255, 255, 255), "pl.posX:%d", pl.posX);
    DrawFormatString(300, 20, GetColor(255, 255, 255), "pl.posY:%d", pl.posY);
    DrawFormatString(300, 40, GetColor(255, 255, 255), "pl.gravity:%d", pl.gravity);
    DrawFormatString(300, 60, GetColor(255, 255, 255), "pl.gravityflg:%d", pl.gravityflg);
    DrawFormatString(300, 80, GetColor(255, 255, 255), "pl.grandflg:%d", pl.grandflg);
    //--------------------------------------------------------------------------------------
}

// プレイヤーの描画処理
void player_draw(void)
{
    DrawGraph(GAME_SCREEN_WIDTH / 2, pl.posY, pl.plHND, true);
    // debug用
    DrawBox(GAME_SCREEN_WIDTH / 2, pl.posY, GAME_SCREEN_WIDTH / 2 + CHIP_SIZE + 1, pl.posY + CHIP_SIZE + 1, GetColor(255, 255, 255), FALSE);
}

// リトライの描画処理
void retry_draw(void)
{
    if (game.choice == true)
    {
        DrawGraph(0, 0, game.reHND[0],TRUE);
    }
    else
    {
        DrawGraph(0, 0, game.reHND[1], TRUE);
    }
}

// ゲームの終了処理
void game_end(void)
{
	DeleteGraph(game.bgHND);
    for (int i = 0; i < 2; i++)
    {
        DeleteGraph(game.reHND[i]);
    }
    stage_end();
    player_end();
}

// プレイヤーの終了処理
void player_end(void)
{
    DeleteGraph(pl.plHND);
}