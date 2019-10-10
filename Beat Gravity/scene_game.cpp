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

extern STAGE stage;
// 関数実体 ----------------------------------------------------------------------------------------
// ゲームの初期設定
void game_initialize(void)
{
	game.state = 0;
	game.timer = 0;
    game.score = 0;
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
    game.bgHND[0] = LoadGraph("Data\\Images\\game_bg1W.png");
    game.bgHND[1] = LoadGraph("Data\\Images\\game_bg2W.png");
    game.bgHND[2] = LoadGraph("Data\\Images\\game_bg1R.png");
    game.bgHND[3] = LoadGraph("Data\\Images\\game_bg2R.png");
    game.reHND[0] = LoadGraph("Data\\Images\\retry_yes.png");
    game.reHND[1] = LoadGraph("Data\\Images\\retry_no.png");
    switch (stage.num)
    {
    case STAGE1:
        game.bgmHND = LoadSoundMem("Data\\Sounds\\stage1BGM.ogg");
        break;
    case STAGE2:
        game.bgmHND = LoadSoundMem("Data\\Sounds\\stage2BGM.ogg");
        break;
    case STAGE3:
        game.bgmHND = LoadSoundMem("Data\\Sounds\\stage3BGM.ogg");
        break;
    }
    game.decideSE = LoadSoundMem("Data\\Sounds\\decideSE.ogg");
    game.choiceSE = LoadSoundMem("Data\\Sounds\\choiceSE.ogg");
    game.deathSE = LoadSoundMem("Data\\Sounds\\deathSE.ogg");
}

// プレイヤーの初期設定
void player_initialize(void)
{
    pl.state = 0;
    pl.init_posX = GAME_SCREEN_WIDTH / 2;
    pl.init_posY = 720;
    pl.posX = 0;
    pl.posY = pl.init_posY + CHIP_SIZE * STAGE_SIZE_Y / 3;
    pl.speed = 13;
    pl.jumppower = 25;
    pl.gravity = GRAVITY;
    pl.gravityflg = true;
    pl.grandflg = false;
    LoadDivGraph("Data\\Images\\player.png", 5, 5, 1, 60, 60, pl.plHND);
    pl.koHND = LoadGraph("Data\\Images\\kobun.png");
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
        PlaySoundMem(game.bgmHND, DX_PLAYTYPE_BACK, false);

        game.state = NORMAL;
        break;
#pragma endregion
    case NORMAL:
#pragma region NORMAL
        ///// 通常時 /////
        // debug用 -------------------------
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
                if (detect_chip(pl.posX, pl.posY + CHIP_SIZE - 1) == EMPTY ||
                    detect_chip(pl.posX + CHIP_SIZE - 1, pl.posY + CHIP_SIZE - 1) == EMPTY)
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
                if (detect_chip(pl.posX, pl.posY) == AIRJUMP ||
                    detect_chip(pl.posX + CHIP_SIZE - 1, pl.posY) == AIRJUMP ||
                    detect_chip(pl.posX, pl.posY + CHIP_SIZE - 1) == AIRJUMP ||
                    detect_chip(pl.posX + CHIP_SIZE - 1, pl.posY + CHIP_SIZE - 1) == AIRJUMP)
                {
                    if (key_trg[KEY_INPUT_SPACE])
                    {
                        pl.gravity = 0;
                        pl.gravity -= pl.jumppower;
                    }
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
                if (detect_chip(pl.posX, pl.posY) == EMPTY ||
                    detect_chip(pl.posX + CHIP_SIZE - 1, pl.posY) == EMPTY)
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
                // 角(左)
                if (detect_chip(pl.posX + CHIP_SIZE - 1, pl.posY + 30) == TOP_LCORNER ||
                    detect_chip(pl.posX + CHIP_SIZE - 1, pl.posY + CHIP_SIZE) == TOP_LCORNER ||
                    detect_chip(pl.posX + CHIP_SIZE - 1, pl.posY + 30) == TOP_LAIR ||
                    detect_chip(pl.posX + CHIP_SIZE - 1, pl.posY + CHIP_SIZE) == TOP_LAIR)
                {
                    // 死亡判定
                    game.deathflg = true;
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
                    // 死亡判定
                    game.deathflg = true;
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
                if (detect_chip(pl.posX, pl.posY) == AIRJUMP ||
                    detect_chip(pl.posX + CHIP_SIZE - 1, pl.posY) == AIRJUMP ||
                    detect_chip(pl.posX, pl.posY + CHIP_SIZE - 1) == AIRJUMP ||
                    detect_chip(pl.posX + CHIP_SIZE - 1, pl.posY + CHIP_SIZE - 1) == AIRJUMP)
                {
                    if (key_trg[KEY_INPUT_SPACE])
                    {
                        pl.gravity = 0;
                        pl.gravity -= pl.jumppower;
                    }
                }
            }
#pragma endregion
            // 共通処理
#pragma region Common
            // 壁(左)
            if (detect_chip(pl.posX + CHIP_SIZE - 1, pl.posY) == TOP_LEFT ||
                detect_chip(pl.posX + CHIP_SIZE - 1, pl.posY + CHIP_SIZE - 1) == TOP_LEFT ||
                detect_chip(pl.posX + CHIP_SIZE - 1, pl.posY) == BOTTOM_LEFT ||
                detect_chip(pl.posX + CHIP_SIZE - 1, pl.posY + CHIP_SIZE - 1) == BOTTOM_LEFT)
            {
                // 死亡判定
                game.deathflg = true;
            }
            // 壁(右)
            if (detect_chip(pl.posX, pl.posY) == TOP_RIGHT ||
                detect_chip(pl.posX, pl.posY + CHIP_SIZE - 1) == TOP_RIGHT ||
                detect_chip(pl.posX, pl.posY) == BOTTOM_RIGHT ||
                detect_chip(pl.posX, pl.posY + CHIP_SIZE - 1) == BOTTOM_RIGHT)
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
                detect_chip(pl.posX, pl.posY) == TOP_NEEDLE ||
                detect_chip(pl.posX + CHIP_SIZE - 1, pl.posY) == TOP_NEEDLE ||
                detect_chip(pl.posX, pl.posY + CHIP_SIZE - 1) == TOP_NEEDLE ||
                detect_chip(pl.posX + CHIP_SIZE - 1, pl.posY + CHIP_SIZE - 1) == TOP_NEEDLE)
            {
                // 死亡判定
                game.deathflg = true;
            }
            // アイテム
            if (detect_chip(pl.posX, pl.posY) == ITEM1 || detect_chip(pl.posX, pl.posY) == ITEM2)
            {
                stage.map_copy[pl.posY / CHIP_SIZE][pl.posX / CHIP_SIZE] = EMPTY;
                game.score += SCORE_ITEM;
            }
            if (detect_chip(pl.posX + CHIP_SIZE - 1, pl.posY) == ITEM1 || detect_chip(pl.posX + CHIP_SIZE - 1, pl.posY) == ITEM2)
            {
                stage.map_copy[pl.posY / CHIP_SIZE][(pl.posX + CHIP_SIZE - 1) / CHIP_SIZE] = EMPTY;
                game.score += SCORE_ITEM;
            }
            if (detect_chip(pl.posX, pl.posY + CHIP_SIZE - 1) == ITEM1 || detect_chip(pl.posX, pl.posY + CHIP_SIZE - 1) == ITEM2)
            {
                stage.map_copy[(pl.posY + CHIP_SIZE - 1) / CHIP_SIZE][pl.posX / CHIP_SIZE] = EMPTY;
                game.score += SCORE_ITEM;
            }
            if (detect_chip(pl.posX + CHIP_SIZE - 1, pl.posY + CHIP_SIZE - 1) == ITEM1 || detect_chip(pl.posX + CHIP_SIZE - 1, pl.posY + CHIP_SIZE - 1) == ITEM2)
            {
                stage.map_copy[(pl.posY + CHIP_SIZE - 1) / CHIP_SIZE][(pl.posX + CHIP_SIZE - 1) / CHIP_SIZE] = EMPTY;
                game.score += SCORE_ITEM;
            }
            // 重力反転
            if (detect_chip(pl.posX, pl.posY) == CHANGE_GRAVITY ||
                detect_chip(pl.posX + CHIP_SIZE - 1, pl.posY) == CHANGE_GRAVITY ||
                detect_chip(pl.posX, pl.posY + CHIP_SIZE - 1) == CHANGE_GRAVITY ||
                detect_chip(pl.posX + CHIP_SIZE - 1, pl.posY + CHIP_SIZE - 1) == CHANGE_GRAVITY)
            {
                if (key_trg[KEY_INPUT_SPACE])
                {
                    if (pl.gravityflg == true)
                    {
                        pl.gravityflg = false;
                        pl.init_posY -= 660;
                    }
                    else
                    {
                        pl.gravityflg = true;
                        pl.init_posY += 660;
                    }
                }
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
        if (key_trg[KEY_INPUT_C])
        {
            game.state = POSE;
        }
        //---------------------------

        break;
#pragma endregion
    case RETRY:
#pragma region RETRY
        ///// リトライ /////
        StopSoundMem(game.bgmHND);

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

        game.timer--;
        break;
#pragma endregion
    case POSE:
#pragma region POSE
        StopSoundMem(game.bgmHND);

        // degug-------------------
        if (key_trg[KEY_INPUT_C])
        {
            game.state = NORMAL;
            PlaySoundMem(game.bgmHND, DX_PLAYTYPE_BACK, false);
        }
        //-----------------------
  
        game.timer--;
        break;
#pragma endregion
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
    DrawRotaGraph(game.bg1posX + GAME_SCREEN_WIDTH / 2, game.bg1posY + GAME_SCREEN_HEIGHT / 2, 1, game.angle1, game.bgHND[0], true, false);
    DrawRotaGraph(game.bg1posX + GAME_SCREEN_WIDTH + GAME_SCREEN_WIDTH / 2, game.bg1posY + GAME_SCREEN_HEIGHT / 2, 1, game.angle1, game.bgHND[0], true, false);
    DrawRotaGraph(game.bg2posX + GAME_SCREEN_WIDTH / 2, game.bg2posY + GAME_SCREEN_HEIGHT / 2, 1, game.angle1, game.bgHND[1], true, false);
    DrawRotaGraph(game.bg2posX + GAME_SCREEN_WIDTH + GAME_SCREEN_WIDTH / 2, game.bg2posY + GAME_SCREEN_HEIGHT / 2, 1, game.angle1, game.bgHND[1], true, false);
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
    DrawRotaGraph(game.bg1posX + GAME_SCREEN_WIDTH / 2, game.bg1posY + GAME_SCREEN_HEIGHT / 2, 1, game.angle1, game.bgHND[2], true, false);
    DrawRotaGraph(game.bg1posX + GAME_SCREEN_WIDTH + GAME_SCREEN_WIDTH / 2, game.bg1posY + GAME_SCREEN_HEIGHT / 2, 1, game.angle1, game.bgHND[2], true, false);
    DrawRotaGraph(game.bg2posX + GAME_SCREEN_WIDTH / 2, game.bg2posY + GAME_SCREEN_HEIGHT / 2, 1, game.angle1, game.bgHND[3], true, false);
    DrawRotaGraph(game.bg2posX + GAME_SCREEN_WIDTH + GAME_SCREEN_WIDTH / 2, game.bg2posY + GAME_SCREEN_HEIGHT / 2, 1, game.angle1, game.bgHND[3], true, false);

    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

    stage_draw();
    player_draw();

    if (game.state == RETRY)
    {
        retry_draw();
    }
    // debug用 ------------------------------------------------------------------------------
    unsigned int Cr = GetColor(0, 200, 200);

    DrawFormatString(10, 10, Cr, "シーン切り替え");
    DrawFormatString(10, 30, Cr, "title:1キー");
    DrawFormatString(10, 50, Cr, "select:2キー");
    DrawFormatString(10, 70, Cr, "load:3キー");
    DrawFormatString(10, 90, Cr, "game:4キー");
    DrawFormatString(10, 110, Cr, "result:5キー");
    DrawFormatString(10, 130, Cr, "重力反転:Zキー");
    DrawFormatString(10, 150, Cr, "リセット:Xキー");
    DrawFormatString(10, 170, Cr, "ポーズ:Cキー");

    DrawFormatString(140, 10, Cr, "game.timer:%d", game.timer);
    DrawFormatString(140, 30, Cr, "game.score:%d", game.score);
    DrawFormatString(140, 50, Cr, "game.deathflg:%d", game.deathflg);
    DrawFormatString(140, 70, Cr, "game.clearflg:%d", game.clearflg);

    DrawFormatString(310, 10, Cr, "pl.posX:%d", pl.posX);
    DrawFormatString(310, 30, Cr, "pl.posY:%d", pl.posY);
    DrawFormatString(310, 50, Cr, "pl.gravity:%d", pl.gravity);
    DrawFormatString(310, 70, Cr, "pl.gravityflg:%d", pl.gravityflg);
    DrawFormatString(310, 90, Cr, "pl.grandflg:%d", pl.grandflg);
    DrawFormatString(310, 150, Cr, "pl.init_posY:%d", pl.init_posY);

    DrawFormatString(460, 10, Cr, "現在のプレイヤーの位置(マップチップ数)");
    DrawFormatString(460, 30, Cr, "X:%d", pl.posX / CHIP_SIZE);
    DrawFormatString(460, 50, Cr, "Y:%d", pl.posY / CHIP_SIZE);
    //--------------------------------------------------------------------------------------
}

// プレイヤーの描画処理
void player_draw(void)
{
    if (game.deathflg == false)
    {
        if (pl.gravityflg == true)
        {
            DrawGraph(pl.init_posX, pl.init_posY, pl.plHND[game.timer / 3 % 5], true);
            if (1)
            {
                DrawGraph(pl.init_posX - pl.posX/3%CHIP_SIZE, pl.init_posY + CHIP_SIZE - 10, pl.koHND, true);
            }
        }
        else
        {
            DrawGraph(pl.init_posX, pl.init_posY, pl.plHND[game.timer / 3 % 5], true);
        }
    }
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
    for (int i = 0; i < 4; i++)
    {
        DeleteGraph(game.bgHND[i]);
    }
    for (int i = 0; i < 2; i++)
    {
        DeleteGraph(game.bgHND[i]);
        DeleteGraph(game.reHND[i]);
    }

    DeleteSoundMem(game.bgmHND);
    DeleteSoundMem(game.decideSE);
    DeleteSoundMem(game.choiceSE);
    DeleteSoundMem(game.deathSE);

    stage_end();
    player_end();
}

// プレイヤーの終了処理
void player_end(void)
{
    for (int i = 0; i < 5; i++)
    {
        DeleteGraph(pl.plHND[i]);
    }
}