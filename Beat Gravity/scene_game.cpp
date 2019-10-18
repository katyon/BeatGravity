// インクルード -------------------------------------------------------------------------------------
#include "DxLib.h"

#include "common.h"
#include "scene_game.h"
#include "scene_result.h"
#include "ranking.h"
#include "stage.h"

// 変数 --------------------------------------------------------------------------------------------
// キー用変数
extern char key_buf[MAX_KEY];

// シーン遷移用変数
extern int nextScene;

// インスタンス宣言 ---------------------------------------------------------------------------------
GAME game;
PLAYER pl;

extern COMMON common;
extern STAGE stage;
extern int H_score[Score_h];
extern bool R_flg;
// 関数実体 ----------------------------------------------------------------------------------------
// ゲームの初期設定
void game_initialize(void)
{
	game.state = 0;
	game.timer = 0;
    game.scenetimer = 0;
    game.score = 0;
    game.percentage = 0;
    game.sceneposX = GAME_SCREEN_WIDTH;
    game.sceneposY = 0;
    game.bg1posX = 0;
    game.bg1posY = 0;
    game.bg1speed = 1;
    game.bg2posX = 0;
    game.bg2posY = 0;
    game.bg2speed = 2;
    game.alpha1 = 0;
    game.alpha2 = 0;
    game.angle1 = 0;
    game.angle2 = 0;
    game.deathflg = false;
    game.clearflg = false;
    game.choice = true;
    game.sceneHND = LoadGraph("Data\\Images\\scene.png");
    game.decideSE = LoadSoundMem("Data\\Sounds\\decideSE.ogg");
    game.choiceSE = LoadSoundMem("Data\\Sounds\\choiceSE.ogg");
    game.deathSE = LoadSoundMem("Data\\Sounds\\deathSE.ogg");
}

// プレイヤーの初期設定
void player_initialize(void)
{
    pl.state = 0;
    pl.box_speedX[0] = 5;
    pl.box_speedY[0] = 2;
    pl.box_speedX[1] = 4;
    pl.box_speedY[1] = 3;
    pl.box_speedX[2] = 3;
    pl.box_speedY[2] = 2;
    pl.init_posX = GAME_SCREEN_WIDTH / 2;
    pl.init_posY = 720;
    pl.posX = 0;
    pl.posY = pl.init_posY + CHIP_SIZE * STAGE_SIZE_Y / 3;
    for (int i = 0; i < 20; i++)
    {
        pl.death_posX[i] = 0;
        pl.death_posY[i] = 0;

        pl.death_rndX[i] = GetRand(50) - 25;
        pl.death_rndY[i] = GetRand(50) - 25;
    }
    pl.death_speed = 0;
    pl.speed = 13;
    pl.jumppower = 25;
    pl.gravity = GRAVITY;
    pl.gravityflg = true;
    pl.grandflg = false;
    LoadDivGraph("Data\\Images\\player.png", 5, 5, 1, 60, 60, pl.plHND);
    pl.deathHND = LoadGraph("Data\\Images\\death.png");
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
        PlaySoundMem(stage.stageBGM[stage.num], DX_PLAYTYPE_BACK, true);


        game.state = NORMAL;
        break;
#pragma endregion
    case NORMAL:
#pragma region NORMAL
        ///// 通常時 /////
        // debug用 -------------------------
        //if (key_trg[KEY_INPUT_1])nextScene = SCENE_TITLE;
        //if (key_trg[KEY_INPUT_2])nextScene = SCENE_SELECT;
        //if (key_trg[KEY_INPUT_3])nextScene = SCENE_LOAD;
        //if (key_trg[KEY_INPUT_4])nextScene = SCENE_GAME;
        //if (key_trg[KEY_INPUT_5])nextScene = SCENE_RESULT;

        //if (key_trg[KEY_INPUT_LSHIFT])
        //{
        //    game.clearflg = true;
        //}
        //if (key_trg[KEY_INPUT_Z])
        //{
        //    if (pl.gravityflg == true)
        //    {
        //        pl.gravityflg = false;
        //    }
        //    else
        //    {
        //        pl.gravityflg = true;
        //    }
        //}
        //if (key_trg[KEY_INPUT_X])
        //{
        //    game_end();
        //    game.state = INIT;
        //}
        //---------------------------------

        // シーン遷移
        if (game.clearflg == true)
        {
            game.state = NEXT;
        }
        if (game.deathflg == true)
        {
            // 死亡時
            PlaySoundMem(game.deathSE, DX_PLAYTYPE_BACK, true);
            game.state = RETRY;
        }
        else
        {
            ///// プレイヤーの更新 /////
            // 通常重力
#pragma region NormalGravity
            if (pl.gravityflg == true)
            {
                pl.init_posY += SWAP_SPEED;
                if (pl.init_posY > 720)
                {
                    pl.init_posY = 720;
                }
                // ジャンプ
                if (pl.grandflg == true && key[KEY_INPUT_SPACE])
                {
                    pl.gravity -= pl.jumppower;
                }
                else
                {
                    // ジャンプパッド
                    if (detect_chip(pl.posX, pl.posY + 12) == BOTTOM_JUMPPAD)
                    {
                        pl.gravity = 0;
                        pl.gravity -= pl.jumppower + 10;
                    }
                    if (detect_chip(pl.posX + CHIP_SIZE - 1, pl.posY + 12) == BOTTOM_JUMPPAD)
                    {
                        pl.gravity = 0;
                        pl.gravity -= pl.jumppower + 10;
                    }
                }
                // 重力と右移動
                pl.posX += pl.speed;
                pl.posY += pl.gravity;

                // マップチップごとの挙動
                // 無
                if (detect_chip(pl.posX, pl.posY + CHIP_SIZE) == EMPTY ||
                    detect_chip(pl.posX + CHIP_SIZE - 1, pl.posY + CHIP_SIZE) == EMPTY ||
                    detect_chip(pl.posX, pl.posY + CHIP_SIZE) == SPACE1 ||
                    detect_chip(pl.posX + CHIP_SIZE - 1, pl.posY + CHIP_SIZE) == SPACE1 ||
                    detect_chip(pl.posX, pl.posY + CHIP_SIZE) == SPACE2 ||
                    detect_chip(pl.posX + CHIP_SIZE - 1, pl.posY + CHIP_SIZE) == SPACE2)
                {
                    pl.grandflg = false;
                    pl.gravity += GRAVITY;
                    if (pl.gravity > 30)
                    {
                        pl.gravity = 30;
                    }
                }
                // 地上
                if (detect_chip(pl.posX, pl.posY + CHIP_SIZE - 1) == BOTTOM ||
                    detect_chip(pl.posX + CHIP_SIZE - 1, pl.posY + CHIP_SIZE - 1) == BOTTOM ||
                    detect_chip(pl.posX, pl.posY + CHIP_SIZE - 1) == BOTTOM_AIR ||
                    detect_chip(pl.posX + CHIP_SIZE - 1, pl.posY + CHIP_SIZE - 1) == BOTTOM_AIR)
                {
                    // 移動制限
                    pl.posY = pl.posY / CHIP_SIZE * CHIP_SIZE;

                    pl.grandflg = true;
                    pl.gravity = 0;
                }
                // 重力反転
                if (detect_chip(pl.posX, pl.posY) == CHANGE_GRAVITY ||
                    detect_chip(pl.posX + CHIP_SIZE - 1, pl.posY) == CHANGE_GRAVITY ||
                    detect_chip(pl.posX, pl.posY + CHIP_SIZE - 1) == CHANGE_GRAVITY ||
                    detect_chip(pl.posX + CHIP_SIZE - 1, pl.posY + CHIP_SIZE - 1) == CHANGE_GRAVITY ||
                    detect_chip(pl.posX, pl.posY) == CHANGE_GRAVITY2 ||
                    detect_chip(pl.posX + CHIP_SIZE - 1, pl.posY) == CHANGE_GRAVITY2 ||
                    detect_chip(pl.posX, pl.posY + CHIP_SIZE - 1) == CHANGE_GRAVITY2 ||
                    detect_chip(pl.posX + CHIP_SIZE - 1, pl.posY + CHIP_SIZE - 1) == CHANGE_GRAVITY2)
                {
                    pl.grandflg = false;
                    pl.gravity += GRAVITY;
                    if (pl.gravity > 30)
                    {
                        pl.gravity = 30;
                    }
                    if (key_trg[KEY_INPUT_SPACE])
                    {
                        pl.gravity += pl.jumppower;
                        pl.gravityflg = false;
                    }
                }
                // 角(左)
                if (detect_chip(pl.posX + CHIP_SIZE - 1, pl.posY) == BOTTOM_LCORNER ||
                    detect_chip(pl.posX + CHIP_SIZE - 1, pl.posY + CHIP_SIZE - 31) == BOTTOM_LCORNER ||
                    detect_chip(pl.posX + CHIP_SIZE - 1, pl.posY) == BOTTOM_LAIR ||
                    detect_chip(pl.posX + CHIP_SIZE - 1, pl.posY + CHIP_SIZE - 31) == BOTTOM_LAIR)
                {
                    // 死亡判定
                    game.deathflg = true;
                }
                else if (detect_chip(pl.posX, pl.posY + CHIP_SIZE - 1) == BOTTOM_LCORNER ||
                    detect_chip(pl.posX + CHIP_SIZE - 1, pl.posY + CHIP_SIZE - 1) == BOTTOM_LCORNER ||
                    detect_chip(pl.posX, pl.posY + CHIP_SIZE - 1) == BOTTOM_LAIR ||
                    detect_chip(pl.posX + CHIP_SIZE - 1, pl.posY + CHIP_SIZE - 1) == BOTTOM_LAIR)
                {
                    // 移動制限
                    pl.posY = pl.posY / CHIP_SIZE * CHIP_SIZE;

                    pl.grandflg = true;
                    pl.gravity = 0;
                }
                // 角(右)
                if (detect_chip(pl.posX, pl.posY) == BOTTOM_RCORNER ||
                    detect_chip(pl.posX, pl.posY + CHIP_SIZE - 31) == BOTTOM_RCORNER ||
                    detect_chip(pl.posX, pl.posY) == BOTTOM_RAIR ||
                    detect_chip(pl.posX, pl.posY + CHIP_SIZE - 31) == BOTTOM_RAIR)
                {
                    // 死亡判定
                    game.deathflg = true;
                }
                else if (detect_chip(pl.posX, pl.posY + CHIP_SIZE - 1) == BOTTOM_RCORNER ||
                    detect_chip(pl.posX + CHIP_SIZE - 1, pl.posY + CHIP_SIZE - 1) == BOTTOM_RCORNER ||
                    detect_chip(pl.posX, pl.posY + CHIP_SIZE - 1) == BOTTOM_RAIR ||
                    detect_chip(pl.posX + CHIP_SIZE - 1, pl.posY + CHIP_SIZE - 1) == BOTTOM_RAIR)
                {
                    // 移動制限
                    pl.posY = pl.posY / CHIP_SIZE * CHIP_SIZE;

                    pl.grandflg = true;
                    pl.gravity = 0;
                }
                // ジャンプポイント
                if (detect_chip(pl.posX - 10, pl.posY - 10) == AIRJUMP ||
                    detect_chip(pl.posX + CHIP_SIZE - 1 + 10, pl.posY - 10) == AIRJUMP ||
                    detect_chip(pl.posX - 10, pl.posY + CHIP_SIZE - 1 + 10) == AIRJUMP ||
                    detect_chip(pl.posX + CHIP_SIZE - 1 + 10, pl.posY + CHIP_SIZE - 1 + 10) == AIRJUMP)
                {
                    if (key_trg[KEY_INPUT_SPACE])
                    {
                        pl.gravity = 0;
                        pl.gravity -= pl.jumppower;
                    }
                }
                // 壁(左)
                if (detect_chip(pl.posX + CHIP_SIZE - 1, pl.posY) == BOTTOM_LEFT ||
                    detect_chip(pl.posX + CHIP_SIZE - 1, pl.posY + CHIP_SIZE - 1) == BOTTOM_LEFT ||
                    detect_chip(pl.posX + CHIP_SIZE - 1, pl.posY) == LDARK ||
                    detect_chip(pl.posX + CHIP_SIZE - 1, pl.posY + CHIP_SIZE - 1) == LDARK)
                {
                    // 死亡判定
                    game.deathflg = true;
                }
                // 壁(右)
                if (detect_chip(pl.posX, pl.posY) == BOTTOM_RIGHT ||
                    detect_chip(pl.posX, pl.posY + CHIP_SIZE - 1) == BOTTOM_RIGHT ||
                    detect_chip(pl.posX, pl.posY) == RDARK ||
                    detect_chip(pl.posX, pl.posY + CHIP_SIZE - 1) == RDARK)
                {
                    // 死亡判定
                    game.deathflg = true;
                }
                // 崖下
                if (detect_chip(pl.posX, pl.posY) == HOLE ||
                    detect_chip(pl.posX + CHIP_SIZE - 1, pl.posY) == HOLE ||
                    detect_chip(pl.posX, pl.posY + CHIP_SIZE - 1) == HOLE ||
                    detect_chip(pl.posX + CHIP_SIZE - 1, pl.posY + CHIP_SIZE - 1) == HOLE)
                {
                    // 死亡判定
                    game.deathflg = true;
                }
                // トゲ
                if (detect_chip(pl.posX + 10, pl.posY + 10) == BOTTOM_NEEDLE ||
                    detect_chip(pl.posX + CHIP_SIZE - 1 - 10, pl.posY + 10) == BOTTOM_NEEDLE ||
                    detect_chip(pl.posX + 10, pl.posY + CHIP_SIZE - 1 - 10) == BOTTOM_NEEDLE ||
                    detect_chip(pl.posX + CHIP_SIZE - 1 - 10, pl.posY + CHIP_SIZE - 1 - 10) == BOTTOM_NEEDLE ||
                    detect_chip(pl.posX + 10, pl.posY + 10) == TOP_NEEDLE ||
                    detect_chip(pl.posX + CHIP_SIZE - 1 - 10, pl.posY + 10) == TOP_NEEDLE ||
                    detect_chip(pl.posX + 10, pl.posY + CHIP_SIZE - 1 - 10) == TOP_NEEDLE ||
                    detect_chip(pl.posX + CHIP_SIZE - 1 - 10, pl.posY + CHIP_SIZE - 1 - 10) == TOP_NEEDLE)
                {
                    // 死亡判定
                    game.deathflg = true;
                }
            }
#pragma endregion
            // 反転重力
#pragma region RebirthGravity
            else
            {
                pl.init_posY -= SWAP_SPEED;
                if (pl.init_posY < 300)
                {
                    pl.init_posY = 300;
                }
                // ジャンプ
                if (pl.grandflg == true && key[KEY_INPUT_SPACE])
                {
                    pl.gravity -= pl.jumppower;
                }
                else
                {
                    // ジャンプパッド
                    if (detect_chip(pl.posX, pl.posY + CHIP_SIZE - 1 - 12) == TOP_JUMPPAD)
                    {
                        pl.gravity = 0;
                        pl.gravity -= pl.jumppower + 10;
                    }
                    if (detect_chip(pl.posX + CHIP_SIZE - 1, pl.posY + CHIP_SIZE - 1 - 12) == TOP_JUMPPAD)
                    {
                        pl.gravity = 0;
                        pl.gravity -= pl.jumppower + 10;
                    }
                }
                // 重力と右移動
                pl.posY -= pl.gravity;
                pl.posX += pl.speed;

                // マップチップごとの挙動
                // 無
                if (detect_chip(pl.posX, pl.posY - 1) == EMPTY ||
                    detect_chip(pl.posX + CHIP_SIZE - 1, pl.posY - 1) == EMPTY ||
                    detect_chip(pl.posX, pl.posY - 1) == SPACE1 ||
                    detect_chip(pl.posX + CHIP_SIZE - 1, pl.posY - 1) == SPACE1 ||
                    detect_chip(pl.posX, pl.posY - 1) == SPACE2 ||
                    detect_chip(pl.posX + CHIP_SIZE - 1, pl.posY - 1) == SPACE2)
                {
                    pl.grandflg = false;
                    pl.gravity += GRAVITY;
                    if (pl.gravity > 30)
                    {
                        pl.gravity = 30;
                    }
                }
                // 天井
                if (detect_chip(pl.posX, pl.posY) == TOP ||
                    detect_chip(pl.posX + CHIP_SIZE - 1, pl.posY) == TOP ||
                    detect_chip(pl.posX, pl.posY) == TOP_AIR ||
                    detect_chip(pl.posX + CHIP_SIZE - 1, pl.posY) == TOP_AIR)
                {
                    // 移動制限
                    pl.posY = pl.posY / CHIP_SIZE * CHIP_SIZE + CHIP_SIZE;

                    pl.grandflg = true;
                    pl.gravity = 0;
                }
                // 重力反転
                if (detect_chip(pl.posX, pl.posY) == CHANGE_GRAVITY ||
                    detect_chip(pl.posX + CHIP_SIZE - 1, pl.posY) == CHANGE_GRAVITY ||
                    detect_chip(pl.posX, pl.posY + CHIP_SIZE - 1) == CHANGE_GRAVITY ||
                    detect_chip(pl.posX + CHIP_SIZE - 1, pl.posY + CHIP_SIZE - 1) == CHANGE_GRAVITY ||
                    detect_chip(pl.posX, pl.posY) == CHANGE_GRAVITY2 ||
                    detect_chip(pl.posX + CHIP_SIZE - 1, pl.posY) == CHANGE_GRAVITY2 ||
                    detect_chip(pl.posX, pl.posY + CHIP_SIZE - 1) == CHANGE_GRAVITY2 ||
                    detect_chip(pl.posX + CHIP_SIZE - 1, pl.posY + CHIP_SIZE - 1) == CHANGE_GRAVITY2)
                {
                    pl.grandflg = false;
                    pl.gravity += GRAVITY;
                    if (pl.gravity > 30)
                    {
                        pl.gravity = 30;
                    }
                    if (key_trg[KEY_INPUT_SPACE])
                    {
                        pl.gravity += pl.jumppower;
                        pl.gravityflg = true;
                    }
                }
                // 角(左)
                if (detect_chip(pl.posX + CHIP_SIZE - 1, pl.posY + 30) == TOP_LCORNER ||
                    detect_chip(pl.posX + CHIP_SIZE - 1, pl.posY + CHIP_SIZE) == TOP_LCORNER ||
                    detect_chip(pl.posX + CHIP_SIZE - 1, pl.posY + 30) == TOP_LAIR ||
                    detect_chip(pl.posX + CHIP_SIZE - 1, pl.posY + CHIP_SIZE) == TOP_LAIR)
                {
                    // 重力反転
                    pl.gravityflg = true;
                }
                else if (detect_chip(pl.posX, pl.posY) == TOP_LCORNER ||
                    detect_chip(pl.posX + CHIP_SIZE - 1, pl.posY) == TOP_LCORNER ||
                    detect_chip(pl.posX, pl.posY) == TOP_LAIR ||
                    detect_chip(pl.posX + CHIP_SIZE - 1, pl.posY) == TOP_LAIR)
                {
                    // 移動制限
                    pl.posY = pl.posY / CHIP_SIZE * CHIP_SIZE + CHIP_SIZE;

                    pl.grandflg = true;
                    pl.gravity = 0;
                }
                // 角(右)
                if (detect_chip(pl.posX, pl.posY + 30) == TOP_RCORNER ||
                    detect_chip(pl.posX, pl.posY + CHIP_SIZE) == TOP_RCORNER ||
                    detect_chip(pl.posX, pl.posY + 30) == TOP_RAIR ||
                    detect_chip(pl.posX, pl.posY + CHIP_SIZE) == TOP_RAIR)
                {
                    // 重力反転
                    pl.gravityflg = true;
                }
                else if (detect_chip(pl.posX, pl.posY) == TOP_RCORNER ||
                    detect_chip(pl.posX + CHIP_SIZE - 1, pl.posY) == TOP_RCORNER ||
                    detect_chip(pl.posX, pl.posY) == TOP_RAIR ||
                    detect_chip(pl.posX + CHIP_SIZE - 1, pl.posY) == TOP_RAIR)
                {
                    // 移動制限
                    pl.posY = pl.posY / CHIP_SIZE * CHIP_SIZE + CHIP_SIZE;

                    pl.grandflg = true;
                    pl.gravity = 0;
                }
                // ジャンプポイント
                if (detect_chip(pl.posX - 10, pl.posY - 10) == AIRJUMP ||
                    detect_chip(pl.posX + CHIP_SIZE - 1 + 10, pl.posY - 10) == AIRJUMP ||
                    detect_chip(pl.posX - 10, pl.posY + CHIP_SIZE - 1 + 10) == AIRJUMP ||
                    detect_chip(pl.posX + CHIP_SIZE - 1 + 10, pl.posY + CHIP_SIZE - 1 + 10) == AIRJUMP)
                {
                    if (key_trg[KEY_INPUT_SPACE])
                    {
                        pl.gravity = 0;
                        pl.gravity -= pl.jumppower;
                    }
                }
                // 壁(左)
                if (detect_chip(pl.posX + CHIP_SIZE - 1, pl.posY) == TOP_LEFT ||
                    detect_chip(pl.posX + CHIP_SIZE - 1, pl.posY + CHIP_SIZE - 1) == TOP_LEFT ||
                    detect_chip(pl.posX + CHIP_SIZE - 1, pl.posY) == LDARK ||
                    detect_chip(pl.posX + CHIP_SIZE - 1, pl.posY + CHIP_SIZE - 1) == LDARK)
                {
                    // 重力反転
                    pl.gravityflg = true;
                }
                // 壁(右)
                if (detect_chip(pl.posX, pl.posY) == TOP_RIGHT ||
                    detect_chip(pl.posX, pl.posY + CHIP_SIZE - 1) == TOP_RIGHT ||
                    detect_chip(pl.posX, pl.posY) == RDARK ||
                    detect_chip(pl.posX, pl.posY + CHIP_SIZE - 1) == RDARK)
                {
                    // 重力反転
                    pl.gravityflg = true;
                }
                // 崖下
                if (detect_chip(pl.posX, pl.posY) == HOLE ||
                    detect_chip(pl.posX + CHIP_SIZE - 1, pl.posY) == HOLE ||
                    detect_chip(pl.posX, pl.posY + CHIP_SIZE - 1) == HOLE ||
                    detect_chip(pl.posX + CHIP_SIZE - 1, pl.posY + CHIP_SIZE - 1) == HOLE)
                {
                    // 重力反転
                    pl.gravityflg = true;
                }
                // トゲ
                if (detect_chip(pl.posX, pl.posY) == TOP_NEEDLE ||
                    detect_chip(pl.posX + CHIP_SIZE - 1, pl.posY) == TOP_NEEDLE ||
                    detect_chip(pl.posX, pl.posY + CHIP_SIZE - 1) == TOP_NEEDLE ||
                    detect_chip(pl.posX + CHIP_SIZE - 1, pl.posY + CHIP_SIZE - 1) == TOP_NEEDLE)
                {
                    // 重力反転
                    pl.gravityflg = true;
                }
            }
#pragma endregion
            // 共通処理
#pragma region Common
            //// 壁(左)
            //if (detect_chip(pl.posX + CHIP_SIZE - 1, pl.posY) == TOP_LEFT ||
            //    detect_chip(pl.posX + CHIP_SIZE - 1, pl.posY + CHIP_SIZE - 1) == TOP_LEFT ||
            //    detect_chip(pl.posX + CHIP_SIZE - 1, pl.posY) == BOTTOM_LEFT ||
            //    detect_chip(pl.posX + CHIP_SIZE - 1, pl.posY + CHIP_SIZE - 1) == BOTTOM_LEFT)
            //{
            //    // 死亡判定
            //    game.deathflg = true;
            //}
            //// 壁(右)
            //if (detect_chip(pl.posX, pl.posY) == TOP_RIGHT ||
            //    detect_chip(pl.posX, pl.posY + CHIP_SIZE - 1) == TOP_RIGHT ||
            //    detect_chip(pl.posX, pl.posY) == BOTTOM_RIGHT ||
            //    detect_chip(pl.posX, pl.posY + CHIP_SIZE - 1) == BOTTOM_RIGHT)
            //{
            //    // 死亡判定
            //    game.deathflg = true;
            //}
            //// 崖下
            //if (detect_chip(pl.posX, pl.posY) == HOLE ||
            //    detect_chip(pl.posX + CHIP_SIZE - 1, pl.posY) == HOLE ||
            //    detect_chip(pl.posX, pl.posY + CHIP_SIZE - 1) == HOLE ||
            //    detect_chip(pl.posX + CHIP_SIZE - 1, pl.posY + CHIP_SIZE - 1) == HOLE)
            //{
            //    // 死亡判定
            //    game.deathflg = true;
            //}
            //// トゲ
            //if (detect_chip(pl.posX + 10, pl.posY + 10) == BOTTOM_NEEDLE ||
            //    detect_chip(pl.posX + CHIP_SIZE - 1 - 10, pl.posY + 10) == BOTTOM_NEEDLE ||
            //    detect_chip(pl.posX + 10, pl.posY + CHIP_SIZE - 1 - 10) == BOTTOM_NEEDLE ||
            //    detect_chip(pl.posX + CHIP_SIZE - 1 - 10, pl.posY + CHIP_SIZE - 1 - 10) == BOTTOM_NEEDLE ||
            //    detect_chip(pl.posX, pl.posY) == TOP_NEEDLE ||
            //    detect_chip(pl.posX + CHIP_SIZE - 1, pl.posY) == TOP_NEEDLE ||
            //    detect_chip(pl.posX, pl.posY + CHIP_SIZE - 1) == TOP_NEEDLE ||
            //    detect_chip(pl.posX + CHIP_SIZE - 1, pl.posY + CHIP_SIZE - 1) == TOP_NEEDLE)
            //{
            //    // 死亡判定
            //    game.deathflg = true;
            //}
            // アイテム
            if (detect_chip(pl.posX, pl.posY) == BOTTOM_ITEM)
            {
                stage.map_copy[pl.posY / CHIP_SIZE][pl.posX / CHIP_SIZE] = EMPTY;
                game.score += SCORE_ITEM1;
            }
            if (detect_chip(pl.posX + CHIP_SIZE - 1, pl.posY) == BOTTOM_ITEM)
            {
                stage.map_copy[pl.posY / CHIP_SIZE][(pl.posX + CHIP_SIZE - 1) / CHIP_SIZE] = EMPTY;
                game.score += SCORE_ITEM1;
            }
            if (detect_chip(pl.posX, pl.posY + CHIP_SIZE - 1) == BOTTOM_ITEM)
            {
                stage.map_copy[(pl.posY + CHIP_SIZE - 1) / CHIP_SIZE][pl.posX / CHIP_SIZE] = EMPTY;
                game.score += SCORE_ITEM1;
            }
            if (detect_chip(pl.posX + CHIP_SIZE - 1, pl.posY + CHIP_SIZE - 1) == BOTTOM_ITEM)
            {
                stage.map_copy[(pl.posY + CHIP_SIZE - 1) / CHIP_SIZE][(pl.posX + CHIP_SIZE - 1) / CHIP_SIZE] = EMPTY;
                game.score += SCORE_ITEM1;
            }

            if (detect_chip(pl.posX, pl.posY) == TOP_ITEM)
            {
                stage.map_copy[pl.posY / CHIP_SIZE][pl.posX / CHIP_SIZE] = EMPTY;
                game.score += SCORE_ITEM2;
            }
            if (detect_chip(pl.posX + CHIP_SIZE - 1, pl.posY) == TOP_ITEM)
            {
                stage.map_copy[pl.posY / CHIP_SIZE][(pl.posX + CHIP_SIZE - 1) / CHIP_SIZE] = EMPTY;
                game.score += SCORE_ITEM2;
            }
            if (detect_chip(pl.posX, pl.posY + CHIP_SIZE - 1) == TOP_ITEM)
            {
                stage.map_copy[(pl.posY + CHIP_SIZE - 1) / CHIP_SIZE][pl.posX / CHIP_SIZE] = EMPTY;
                game.score += SCORE_ITEM2;
            }
            if (detect_chip(pl.posX + CHIP_SIZE - 1, pl.posY + CHIP_SIZE - 1) == TOP_ITEM)
            {
                stage.map_copy[(pl.posY + CHIP_SIZE - 1) / CHIP_SIZE][(pl.posX + CHIP_SIZE - 1) / CHIP_SIZE] = EMPTY;
                game.score += SCORE_ITEM2;
            }
            // ゴール
            if (detect_chip(pl.posX, pl.posY) == GOAL ||
                detect_chip(pl.posX + CHIP_SIZE - 1, pl.posY) == GOAL ||
                detect_chip(pl.posX, pl.posY + CHIP_SIZE - 1) == GOAL ||
                detect_chip(pl.posX + CHIP_SIZE - 1, pl.posY + CHIP_SIZE - 1) == GOAL)
            {
                // クリア判定
                game.clearflg = true;
            }
            // 強制ダウン
            if (detect_chip(pl.posX, pl.posY) == CHANGE ||
                detect_chip(pl.posX + CHIP_SIZE - 1, pl.posY) == CHANGE ||
                detect_chip(pl.posX, pl.posY + CHIP_SIZE - 1) == CHANGE ||
                detect_chip(pl.posX + CHIP_SIZE - 1, pl.posY + CHIP_SIZE - 1) == CHANGE)
            {
                pl.gravityflg = true;
            }

            // 背景スクロール処理
            game.bg1posX -= game.bg1speed;
            if (game.bg1posX + GAME_SCREEN_WIDTH < 0)
            {
                game.bg1posX = 0;
            }
            game.bg2posX -= game.bg2speed;
            if (game.bg2posX + GAME_SCREEN_WIDTH < 0)
            {
                game.bg2posX = 0;
            }
        }
#pragma endregion

        // ランキング
        R_flg = true;

        // debug用------------------
        //if (key[KEY_INPUT_LEFT])
        //{
        //    pl.posX -= pl.speed;
        //}
        //if (key[KEY_INPUT_RIGHT])
        //{
        //    pl.posX += pl.speed;
        //}
        //if (key[KEY_INPUT_0])
        //{
        //    pl.posX++;
        //}
        //if (key[KEY_INPUT_9])
        //{
        //    pl.posY++;
        //}
        //if (key[KEY_INPUT_UP])
        //{
        //    pl.posY -= pl.speed;
        //}
        //if (key[KEY_INPUT_DOWN])
        //{
        //    pl.posY += pl.speed;
        //}
        //if (key_trg[KEY_INPUT_C])
        //{
        //    game.state = POSE;
        //}
        //---------------------------

        break;
#pragma endregion
    case RETRY:
#pragma region RETRY
        ///// リトライ /////
        StopSoundMem(stage.stageBGM[stage.num]);

        if (key_trg[KEY_INPUT_LEFT])
        {
            PlaySoundMem(game.choiceSE, DX_PLAYTYPE_BACK, true);

            game.choice = true;
        }
        if (key_trg[KEY_INPUT_RIGHT])
        {
            PlaySoundMem(game.choiceSE, DX_PLAYTYPE_BACK, true);

            game.choice = false;
        }

        if (key_trg[KEY_INPUT_SPACE])
        {
            PlaySoundMem(game.decideSE, DX_PLAYTYPE_BACK, true);

            if (game.choice == true)
            {
                //game_end();
                player_end();
                game.state = INIT;
            }
            else
            {
                //player_end();
                //game_end();
                game.state = NEXT;
            }
        }

        game.timer--;
        break;
#pragma endregion
//    case POSE:
//#pragma region POSE
//        StopSoundMem(game.bgmHND);
//
//        // degug-------------------
//        if (key_trg[KEY_INPUT_C])
//        {
//            game.state = NORMAL;
//            PlaySoundMem(game.bgmHND, DX_PLAYTYPE_BACK, false);
//        }
//        //-----------------------
//  
//        game.timer--;
//        break;
//#pragma endregion
    case NEXT:
        game.sceneposX -= 50;
        if (game.sceneposX < -300)
        {
            game.sceneposX = -300;
            nextScene = SCENE_RESULT;
        }
        game.scenetimer++;
        break;
    }

    game.timer++;
}

// ゲームの描画処理
void game_draw(void)
{
    // 背景
    if (pl.gravityflg == true)
    {
        game.angle1 = 0;
    }
    else
    {
        game.angle1 = PI;
    }
    switch (stage.num)
    {
    case STAGE1:
        DrawRotaGraph(game.bg1posX + GAME_SCREEN_WIDTH / 2, game.bg1posY + GAME_SCREEN_HEIGHT / 2, 1, game.angle1, game.bgHND[0], true, false);
        DrawRotaGraph(game.bg1posX + GAME_SCREEN_WIDTH + GAME_SCREEN_WIDTH / 2, game.bg1posY + GAME_SCREEN_HEIGHT / 2, 1, game.angle1, game.bgHND[0], true, false);
        DrawRotaGraph(game.bg2posX + GAME_SCREEN_WIDTH / 2, game.bg2posY + GAME_SCREEN_HEIGHT / 2, 1, game.angle1, game.bgHND[1], true, false);
        DrawRotaGraph(game.bg2posX + GAME_SCREEN_WIDTH + GAME_SCREEN_WIDTH / 2, game.bg2posY + GAME_SCREEN_HEIGHT / 2, 1, game.angle1, game.bgHND[1], true, false);
        break;
    case STAGE2:
        DrawRotaGraph(game.bg1posX + GAME_SCREEN_WIDTH / 2, game.bg1posY + GAME_SCREEN_HEIGHT / 2, 1, game.angle1, game.bgHND[4], true, false);
        DrawRotaGraph(game.bg1posX + GAME_SCREEN_WIDTH + GAME_SCREEN_WIDTH / 2, game.bg1posY + GAME_SCREEN_HEIGHT / 2, 1, game.angle1, game.bgHND[4], true, false);
        DrawRotaGraph(game.bg2posX + GAME_SCREEN_WIDTH / 2, game.bg2posY + GAME_SCREEN_HEIGHT / 2, 1, game.angle1, game.bgHND[5], true, false);
        DrawRotaGraph(game.bg2posX + GAME_SCREEN_WIDTH + GAME_SCREEN_WIDTH / 2, game.bg2posY + GAME_SCREEN_HEIGHT / 2, 1, game.angle1, game.bgHND[5], true, false);
        break;
    }

    if (pl.gravityflg == true)
    {
        game.alpha1 = 0;

        SetDrawBlendMode(DX_BLENDMODE_ALPHA, game.alpha2);
        if (game.alpha2 > 0)
        {
            game.alpha2 -= 5;
        }
    }
    else
    {
        game.alpha2 = 255;

        SetDrawBlendMode(DX_BLENDMODE_ALPHA, game.alpha1);
        if (game.alpha1 < 255)
        {
            game.alpha1 += 5;
        }
    }
    switch (stage.num)
    {
    case STAGE1:
        DrawRotaGraph(game.bg1posX + GAME_SCREEN_WIDTH / 2, game.bg1posY + GAME_SCREEN_HEIGHT / 2, 1, game.angle1, game.bgHND[2], true, false);
        DrawRotaGraph(game.bg1posX + GAME_SCREEN_WIDTH + GAME_SCREEN_WIDTH / 2, game.bg1posY + GAME_SCREEN_HEIGHT / 2, 1, game.angle1, game.bgHND[2], true, false);
        DrawRotaGraph(game.bg2posX + GAME_SCREEN_WIDTH / 2, game.bg2posY + GAME_SCREEN_HEIGHT / 2, 1, game.angle1, game.bgHND[3], true, false);
        DrawRotaGraph(game.bg2posX + GAME_SCREEN_WIDTH + GAME_SCREEN_WIDTH / 2, game.bg2posY + GAME_SCREEN_HEIGHT / 2, 1, game.angle1, game.bgHND[3], true, false);
        break;
    case STAGE2:
        DrawRotaGraph(game.bg1posX + GAME_SCREEN_WIDTH / 2, game.bg1posY + GAME_SCREEN_HEIGHT / 2, 1, game.angle1, game.bgHND[6], true, false);
        DrawRotaGraph(game.bg1posX + GAME_SCREEN_WIDTH + GAME_SCREEN_WIDTH / 2, game.bg1posY + GAME_SCREEN_HEIGHT / 2, 1, game.angle1, game.bgHND[6], true, false);
        DrawRotaGraph(game.bg2posX + GAME_SCREEN_WIDTH / 2, game.bg2posY + GAME_SCREEN_HEIGHT / 2, 1, game.angle1, game.bgHND[7], true, false);
        DrawRotaGraph(game.bg2posX + GAME_SCREEN_WIDTH + GAME_SCREEN_WIDTH / 2, game.bg2posY + GAME_SCREEN_HEIGHT / 2, 1, game.angle1, game.bgHND[7], true, false);
        break;
    }

    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

    stage_draw();
    player_draw();

    if (game.state == RETRY)
    {
        retry_draw();
    }

    DrawFormatStringToHandle(GAME_SCREEN_WIDTH - 500, 30, GetColor(0, 0, 0), common.font, "%d", game.score);

    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 170 + game.scenetimer * 2);
    DrawGraph(game.sceneposX, game.sceneposY, game.sceneHND, true);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

    // debug用 ------------------------------------------------------------------------------
    //unsigned int Cr = GetColor(0, 200, 200);

    //DrawFormatString(10, 10, Cr, "シーン切り替え");
    //DrawFormatString(10, 30, Cr, "title:1キー");
    //DrawFormatString(10, 50, Cr, "select:2キー");
    //DrawFormatString(10, 70, Cr, "load:3キー");
    //DrawFormatString(10, 90, Cr, "game:4キー");
    //DrawFormatString(10, 110, Cr, "result:5キー");
    //DrawFormatString(10, 130, Cr, "重力反転:Zキー");
    //DrawFormatString(10, 150, Cr, "リセット:Xキー");
    //DrawFormatString(10, 170, Cr, "ポーズ:Cキー");

    //DrawFormatString(140, 10, Cr, "game.timer:%d", game.timer);
    //DrawFormatString(140, 30, Cr, "game.score:%d", game.score);
    //DrawFormatString(140, 50, Cr, "game.deathflg:%d", game.deathflg);
    //DrawFormatString(140, 70, Cr, "game.clearflg:%d", game.clearflg);

    //DrawFormatString(310, 10, Cr, "pl.posX:%d", pl.posX);
    //DrawFormatString(310, 30, Cr, "pl.posY:%d", pl.posY);
    //DrawFormatString(310, 50, Cr, "pl.gravity:%d", pl.gravity);
    //DrawFormatString(310, 70, Cr, "pl.gravityflg:%d", pl.gravityflg);
    //DrawFormatString(310, 90, Cr, "pl.grandflg:%d", pl.grandflg);

    //DrawFormatString(460, 10, Cr, "現在のプレイヤーの位置(マップチップ数)");
    //DrawFormatString(460, 30, Cr, "X:%d", pl.posX / CHIP_SIZE);
    //DrawFormatString(460, 50, Cr, "Y:%d", pl.posY / CHIP_SIZE);
    //--------------------------------------------------------------------------------------
}

// プレイヤーの描画処理
void player_draw(void)
{
    unsigned int Cr;
    Cr = GetColor(0, 0, 0);

    if (game.deathflg == false)
    {
        if (pl.gravityflg == true)
        {
            DrawGraph(pl.init_posX, pl.init_posY, pl.plHND[game.timer / 3 % 5], true);
            if (pl.grandflg == true)
            {
                SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200 - pl.box_moveX[0] * 2);

                DrawBox(pl.init_posX - 10 - pl.rndX[0] - pl.box_moveX[0], pl.init_posY + CHIP_SIZE - pl.rndY[0] - pl.box_moveY[0],
                    pl.init_posX - pl.rndX[0] - pl.box_moveX[0], pl.init_posY + CHIP_SIZE, Cr, true);
                DrawBox(pl.init_posX - 10 - pl.rndX[1] - pl.box_moveX[1], pl.init_posY + CHIP_SIZE - pl.rndY[1] - pl.box_moveY[1],
                    pl.init_posX - pl.rndX[1] - pl.box_moveX[1], pl.init_posY + CHIP_SIZE, Cr, true);
                DrawBox(pl.init_posX - 10 - pl.rndX[2] - pl.box_moveX[2], pl.init_posY + CHIP_SIZE - pl.rndY[2] - pl.box_moveY[2],
                    pl.init_posX - pl.rndX[2] - pl.box_moveX[2], pl.init_posY + CHIP_SIZE, Cr, true);

                SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
            }
        }
        else
        {
            DrawTurnGraph(pl.init_posX, pl.init_posY, pl.plHND[game.timer / 3 % 5], true);
            if (pl.grandflg == true)
            {
                SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200 - pl.box_moveX[0] * 2);

                DrawBox(pl.init_posX - 10 - pl.rndX[0] - pl.box_moveX[0], pl.init_posY + pl.rndY[0] + pl.box_moveY[0],
                    pl.init_posX - pl.rndX[0] - pl.box_moveX[0], pl.init_posY, Cr, true);
                DrawBox(pl.init_posX - 10 - pl.rndX[1] - pl.box_moveX[1], pl.init_posY + pl.rndY[1] + pl.box_moveY[1],
                    pl.init_posX - pl.rndX[1] - pl.box_moveX[1], pl.init_posY, Cr, true);
                DrawBox(pl.init_posX - 10 - pl.rndX[2] - pl.box_moveX[2], pl.init_posY + pl.rndY[2] + pl.box_moveY[2],
                    pl.init_posX - pl.rndX[2] - pl.box_moveX[2], pl.init_posY, Cr, true);

                SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
            }
        }

        if (pl.box_moveX[0] > 80)
        {
            pl.rndX[0] = GetRand(6)*5;
            pl.rndY[0] = GetRand(6)*5;
            pl.box_moveX[0] = 0;
            pl.box_moveY[0] = 0;
            pl.box_speedY[0] = pl.box_speedY[0] * -1;
        };
        if (pl.box_moveY[0] > 30)
        {
            pl.box_speedY[0] = pl.box_speedY[0]*-1;
        }
        pl.box_moveX[0] += pl.box_speedX[0];
        pl.box_moveY[0] += pl.box_speedY[0];
        if (pl.box_moveX[1] > 80)
        {
            pl.rndX[1] = GetRand(6) * 5;
            pl.rndY[1] = GetRand(6) * 3;
            pl.box_moveX[1] = 0;
            pl.box_moveY[1] = 0;
            pl.box_speedY[1] = pl.box_speedY[1] * -1;
        }
        if (pl.box_moveY[1] > 30)
        {
            pl.box_speedY[1] = pl.box_speedY[1] * -1;
        }
        pl.box_moveX[1] += pl.box_speedX[1];
        pl.box_moveY[1] += pl.box_speedY[1];
        if (pl.box_moveX[2] > 80)
        {
            pl.rndX[2] = GetRand(6) * 5;
            pl.rndY[2] = GetRand(6) * 3;
            pl.box_moveX[2] = 0;
            pl.box_moveY[2] = 0;
            pl.box_speedY[2] = pl.box_speedY[2] * -1;
        }
        if (pl.box_moveY[2] > 30)
        {
            pl.box_speedY[2] = pl.box_speedY[2] * -1;
        }
        pl.box_moveX[2] += pl.box_speedX[2];
        pl.box_moveY[2] += pl.box_speedY[2];
    }
}

// リトライの描画処理
void retry_draw(void)
{
    unsigned int Cr;
    Cr = GetColor(0, 0, 0);

    // 死亡エフェクト
    if (pl.death_speed < 200)
    {
        pl.death_speed += 8;
        for (int i = 0; i < 20; i++)
        {
            pl.death_posX[i] += pl.death_rndX[i];
            pl.death_posY[i] += pl.death_rndY[i];
        }
    }
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200 - pl.death_speed);

    for (int i = 0; i < 20; i++)
    {
        DrawBox(pl.init_posX + CHIP_SIZE / 2 - 10 + pl.death_posX[i], pl.init_posY + CHIP_SIZE / 2 - 10 + pl.death_posY[i],
            pl.init_posX + CHIP_SIZE / 2 + 10 + pl.death_posX[i], pl.init_posY + CHIP_SIZE / 2 + 10 + pl.death_posY[i], Cr, true);
    }

    DrawRotaGraph2(pl.init_posX + CHIP_SIZE / 2, pl.init_posY + CHIP_SIZE / 2, CHIP_SIZE / 2, CHIP_SIZE / 2, pl.death_speed / 5, 0, pl.deathHND, true);

    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

    if (game.choice == true)
    {
        DrawGraph(0, 0, game.reHND[0],TRUE);
    }
    else
    {
        DrawGraph(0, 0, game.reHND[1], TRUE);
    }
    switch (stage.num)
    {
    case STAGE1:
        game.percentage = 100 - game.timer / 72;
        break;
    case STAGE2:
        game.percentage = 100 - game.timer / 65;
        break;
    }
    if (game.percentage < 0)
    {
        game.percentage = 0;
    }
    DrawFormatStringToHandle(GAME_SCREEN_WIDTH / 2 - 260, 800, GetColor(255, 255, 255), common.font, "%d%% left", game.percentage);
}

// ゲームの終了処理
void game_end(void)
{

    for (int i = 0; i < 4; i++)
    {
        DeleteGraph(game.bgHND[i]);
    }
    for (int i = 0; i < 2; i++)
    {
        DeleteGraph(game.bgHND[i]);
        DeleteGraph(game.reHND[i]);
    }

    DeleteGraph(game.sceneHND);
    DeleteSoundMem(stage.stageBGM[STAGE1]);
    DeleteSoundMem(stage.stageBGM[STAGE2]);
    DeleteSoundMem(game.decideSE);
    DeleteSoundMem(game.choiceSE);
    DeleteSoundMem(game.deathSE);

    player_end();
}

// プレイヤーの終了処理
void player_end(void)
{
    for (int i = 0; i < 5; i++)
    {
        DeleteGraph(pl.plHND[i]);
    }
    DeleteGraph(pl.deathHND);
}