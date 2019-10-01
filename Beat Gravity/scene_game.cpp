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
		if (key_trg[KEY_INPUT_LSHIFT])
		{
			nextScene = SCENE_TITLE;
		}
        //---------------------------------
        player_update();
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

// プレイヤーの初期設定
void player_initialize(void)
{
    pl.state = 0;
    pl.posX = 0;
    pl.posY = 0;
    pl.pivotX = 0;
    pl.pivotY = 0;
    pl.speed = 5;
    pl.jumppower = 0;
    pl.jumpflg = false;
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

    // プレイヤーの中心座標を更新
    pl.pivotX = pl.posX + CHIP_SIZE / 2;
    pl.pivotY = pl.posY + CHIP_SIZE / 2;

    // マップチップごとの挙動
    // 床
    if (detect_chip(pl.posX, pl.posY + CHIP_SIZE, STAGE4) == 1 ||
        detect_chip(pl.posX + CHIP_SIZE, pl.posY + CHIP_SIZE, STAGE4) == 1)
    {
        // 空中にいるかどうかの判定
        pl.jumpflg = false;
        // 移動制限
        pl.posY = pl.posY / CHIP_SIZE * CHIP_SIZE;
        pl.jumppower = 0;
    }
    else
    {
        pl.jumpflg = true;
    }

    // 自由落下
    pl.posY -= pl.jumppower;
    pl.jumppower -= 1;

    // ジャンプ
    if (pl.jumpflg == true && key[KEY_INPUT_SPACE])
    {
        pl.jumppower = 20;
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
        pl.posY -= 50;
    }
    if (key[KEY_INPUT_DOWN])
    {
        pl.posY += pl.speed;
    }
    //---------------------------
}

// プレイヤーの描画処理
void player_draw(void)
{
    DrawGraph(pl.posX, pl.posY, pl.plHND, true);
    // debug用
    DrawBox(pl.posX, pl.posY, pl.posX + CHIP_SIZE - 1, pl.posY + CHIP_SIZE - 1, GetColor(1, 1, 1), FALSE);
}

// プレイヤーの終了処理
void player_end(void)
{
    DeleteGraph(pl.plHND);
}