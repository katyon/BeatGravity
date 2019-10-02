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
	game.titmer = 0;
	game.nextSceneflg = false;
	game.bgHND = LoadGraph("Data\\Images\\game_bg.png");
}

// プレイヤーの初期設定
void player_initialize(void)
{
    pl.state = 0;
    pl.posX = GAME_SCREEN_WIDTH/2;
    pl.posY = GAME_SCREEN_HEIGHT/2;
    pl.speed = 5;
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
		///// 初期設定 /////
        player_initialize();
        stage_initialize();
		game.state++;
		break;

	case NORMAL:
		///// 通常時 /////
		// debug用-------------------------
		if (key_trg[KEY_INPUT_LSHIFT])
		{
			nextScene = SCENE_TITLE;
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
            pl.posX = GAME_SCREEN_WIDTH / 2;
            pl.posY = GAME_SCREEN_HEIGHT / 2;
        }
        //---------------------------------

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
                detect_chip(pl.posX + CHIP_SIZE - 1,pl.posY) == TOP)
            {
                // 移動制限
                pl.posY = pl.posY / CHIP_SIZE * CHIP_SIZE + CHIP_SIZE;

                pl.grandflg = true;
                pl.gravity = 0;
            }
        }
        // debug用------------------
        if (key[KEY_INPUT_LEFT])
        {
            pl.posX -= pl.speed;
        }
        if (key[KEY_INPUT_RIGHT])
        {
            pl.posX += pl.speed;
        }
        if (key[KEY_INPUT_UP])
        {
            pl.posY -= pl.speed;
        }
        if (key[KEY_INPUT_DOWN])
        {
            pl.posY += pl.speed;
        }
        //---------------------------
        
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

// プレイヤーの描画処理
void player_draw(void)
{
    DrawGraph(GAME_SCREEN_WIDTH / 2, pl.posY, pl.plHND, true);
    // debug用
    DrawBox(GAME_SCREEN_WIDTH / 2, pl.posY, GAME_SCREEN_WIDTH / 2 + CHIP_SIZE - 1, pl.posY + CHIP_SIZE - 1, GetColor(1, 1, 1), FALSE);
}

// ゲームの終了処理
void game_end(void)
{
	DeleteGraph(game.bgHND);
    stage_end();
    player_end();
}

// プレイヤーの終了処理
void player_end(void)
{
    DeleteGraph(pl.plHND);
}