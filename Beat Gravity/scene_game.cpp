// �C���N���[�h -------------------------------------------------------------------------------------
#include "DxLib.h"

#include "common.h"
#include "scene_game.h"
#include "scene_result.h"
#include "ranking.h"
#include "stage.h"

// �ϐ� --------------------------------------------------------------------------------------------
// �L�[�p�ϐ�
extern char key_buf[MAX_KEY];

// �V�[���J�ڗp�ϐ�
extern int nextScene;

// �C���X�^���X�錾 ---------------------------------------------------------------------------------
GAME game;
PLAYER pl;

extern STAGE stage;
// �֐����� ----------------------------------------------------------------------------------------
// �Q�[���̏����ݒ�
void game_initialize(void)
{
	game.state = 0;
	game.timer = 0;
    game.score = 0;
    game.bgposX = 0;
    game.bgposY = 0;
    game.bgspeed = 1;
    game.alpha1 = 0;
    game.alpha2 = 0;
    game.angle1 = 0;
    game.angle2 = 0;
    game.deathflg = false;
    game.clearflg = false;
    game.choice = true;
    game.bgHND[0] = LoadGraph("Data\\Images\\game_bg1.png");
    game.bgHND[1] = LoadGraph("Data\\Images\\game_bg2.png");
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
    case STAGE4:
        game.bgmHND = LoadSoundMem("Data\\Sounds\\stage4BGM.ogg");
        break;
    }
}

// �v���C���[�̏����ݒ�
void player_initialize(void)
{
    pl.state = 0;
    pl.posX = GAME_SCREEN_WIDTH / 2;
    pl.posY = GAME_SCREEN_HEIGHT / 2;
    pl.speed = 13;
    pl.jumppower = 25;
    pl.gravity = GRAVITY;
    pl.gravityflg = true;
    pl.grandflg = false;
    LoadDivGraph("Data\\Images\\player.png", 5, 5, 1, 60, 60, pl.plHND);
}

// �Q�[���̍X�V����
void game_update(void)
{
#pragma region KeyUpdate
    //�L�[�̐ݒ�
    char key[MAX_KEY];              //������Ă���ԏ���������
    char key_trg[MAX_KEY] = { 0 };  //�����ꂽ�u�Ԃ�������

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
        ///// �����ݒ� /////
        game_initialize();
        player_initialize();
        stage_initialize();
        PlaySoundMem(game.bgmHND, DX_PLAYTYPE_BACK, TRUE);

        game.state++;
        break;
#pragma endregion
    case NORMAL:
#pragma region NORMAL
        ///// �ʏ펞 /////
        // debug�p-------------------------
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

        // �V�[���J��
        if (game.clearflg == true)
        {
            nextScene = SCENE_RESULT;
        }

        if (game.deathflg == true)
        {
            // ���S��
            game.state++;
        }
        else
        {
            ///// �v���C���[�̍X�V /////
            // �ʏ�d��
#pragma region NormalGravity
            if (pl.gravityflg == true)
            {
                // �W�����v
                if (pl.grandflg == true && key[KEY_INPUT_SPACE])
                {
                    pl.gravity -= pl.jumppower;
                }

                // �d�͂ƉE�ړ�
                //pl.posX += pl.speed;
                //pl.posY += pl.gravity;

                // �}�b�v�`�b�v���Ƃ̋���
                // ��
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
                // �n��
                if (detect_chip(pl.posX, pl.posY + CHIP_SIZE - 1) == BOTTOM ||
                    detect_chip(pl.posX + CHIP_SIZE - 1, pl.posY + CHIP_SIZE - 1) == BOTTOM)
                {
                    // �ړ�����
                    pl.posY = pl.posY / CHIP_SIZE * CHIP_SIZE;

                    pl.grandflg = true;
                    pl.gravity = 0;
                }
                // �p(��)
                if (detect_chip(pl.posX + CHIP_SIZE - 1, pl.posY) == BOTTOM_LCORNER ||
                    detect_chip(pl.posX + CHIP_SIZE - 1, pl.posY + CHIP_SIZE - 31) == BOTTOM_LCORNER)
                {
                    // ���S����
                    game.deathflg = true;
                }
                else if (detect_chip(pl.posX, pl.posY + CHIP_SIZE - 1) == BOTTOM_LCORNER ||
                    detect_chip(pl.posX + CHIP_SIZE - 1, pl.posY + CHIP_SIZE - 1) == BOTTOM_LCORNER)
                {
                    // �ړ�����
                    pl.posY = pl.posY / CHIP_SIZE * CHIP_SIZE;

                    pl.grandflg = true;
                    pl.gravity = 0;
                }
                // �p(�E)
                if (detect_chip(pl.posX, pl.posY) == BOTTOM_RCORNER ||
                    detect_chip(pl.posX, pl.posY + CHIP_SIZE - 31) == BOTTOM_RCORNER)
                {
                    // ���S����
                    game.deathflg = true;
                }
                else if (detect_chip(pl.posX, pl.posY + CHIP_SIZE - 1) == BOTTOM_RCORNER ||
                    detect_chip(pl.posX + CHIP_SIZE - 1, pl.posY + CHIP_SIZE - 1) == BOTTOM_RCORNER)
                {
                    // �ړ�����
                    pl.posY = pl.posY / CHIP_SIZE * CHIP_SIZE;

                    pl.grandflg = true;
                    pl.gravity = 0;
                }
            }
#pragma endregion
            // ���]�d��
#pragma region RebirthGravity
            else
            {
                // �W�����v
                if (pl.grandflg == true && key[KEY_INPUT_SPACE])
                {
                    pl.gravity -= pl.jumppower;
                }
                // �d�͂ƉE�ړ�
                //pl.posY -= pl.gravity;
                //pl.posX += pl.speed;

                // �}�b�v�`�b�v���Ƃ̋���
                // ��
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
                // �V��
                if (detect_chip(pl.posX, pl.posY) == TOP ||
                    detect_chip(pl.posX + CHIP_SIZE - 1, pl.posY) == TOP)
                {
                    // �ړ�����
                    pl.posY = pl.posY / CHIP_SIZE * CHIP_SIZE + CHIP_SIZE;

                    pl.grandflg = true;
                    pl.gravity = 0;
                }
                // �p(��)
                if (detect_chip(pl.posX + CHIP_SIZE - 1, pl.posY + 30) == TOP_LCORNER || 
                    detect_chip(pl.posX + CHIP_SIZE - 1, pl.posY + CHIP_SIZE) == TOP_LCORNER)
                {
                    // ���S����
                    game.deathflg = true;
                }
                else if (detect_chip(pl.posX, pl.posY) == TOP_LCORNER ||
                    detect_chip(pl.posX + CHIP_SIZE - 1, pl.posY) == TOP_LCORNER)
                {
                    // �ړ�����
                    pl.posY = pl.posY / CHIP_SIZE * CHIP_SIZE + CHIP_SIZE;

                    pl.grandflg = true;
                    pl.gravity = 0;
                }
                // �p(�E)
                if (detect_chip(pl.posX, pl.posY + 30) == TOP_RCORNER ||
                    detect_chip(pl.posX, pl.posY + CHIP_SIZE) == TOP_RCORNER)
                {
                    // ���S����
                    game.deathflg = true;
                }
                else if (detect_chip(pl.posX, pl.posY) == TOP_RCORNER ||
                    detect_chip(pl.posX + CHIP_SIZE - 1, pl.posY) == TOP_RCORNER)
                {
                    // �ړ�����
                    pl.posY = pl.posY / CHIP_SIZE * CHIP_SIZE + CHIP_SIZE;

                    pl.grandflg = true;
                    pl.gravity = 0;
                }
            }
#pragma endregion
            // ���ʏ���
#pragma region Common
            // ��(��)
            if (detect_chip(pl.posX + CHIP_SIZE - 1, pl.posY) == LEFT ||
                detect_chip(pl.posX + CHIP_SIZE - 1, pl.posY + CHIP_SIZE - 1) == LEFT)
            {
                // ���S����
                game.deathflg = true;
            }
            // ��(�E)
            if (detect_chip(pl.posX , pl.posY) == RIGHT ||
                detect_chip(pl.posX , pl.posY + CHIP_SIZE - 1) == RIGHT)
            {
                // ���S����
                game.deathflg = true;
            }
            // �R��
            if (detect_chip(pl.posX, pl.posY) == HOLE ||
                detect_chip(pl.posX + CHIP_SIZE - 1, pl.posY) == HOLE ||
                detect_chip(pl.posX, pl.posY + CHIP_SIZE - 1) == HOLE ||
                detect_chip(pl.posX + CHIP_SIZE - 1, pl.posY + CHIP_SIZE - 1) == HOLE)
            {
                // ���S����
                game.deathflg = true;
            }
            // �R�C��
            if (detect_chip(pl.posX, pl.posY) == COIN)
            {
                stage.map_copy[pl.posY / CHIP_SIZE][pl.posX / CHIP_SIZE] = EMPTY;
                game.score += SCORE_COIN;
            }
            if(detect_chip(pl.posX + CHIP_SIZE - 1, pl.posY) == COIN)
            {
                stage.map_copy[pl.posY / CHIP_SIZE][(pl.posX + CHIP_SIZE - 1) / CHIP_SIZE] = EMPTY;
                game.score += SCORE_COIN;
            }
            if(detect_chip(pl.posX, pl.posY + CHIP_SIZE - 1) == COIN)
            {
                stage.map_copy[(pl.posY + CHIP_SIZE - 1) / CHIP_SIZE][pl.posX / CHIP_SIZE] = EMPTY;
                game.score += SCORE_COIN;
            }
            if(detect_chip(pl.posX + CHIP_SIZE - 1, pl.posY + CHIP_SIZE - 1) == COIN)
            {
                stage.map_copy[(pl.posY + CHIP_SIZE - 1) / CHIP_SIZE][(pl.posX + CHIP_SIZE - 1) / CHIP_SIZE] = EMPTY;
                game.score += SCORE_COIN;
            }

            // �w�i�X�N���[������
            game.bgposX -= game.bgspeed;
            if (game.bgposX + GAME_SCREEN_WIDTH < 0)
            {
                game.bgposX = 0;
            }
        }
#pragma endregion

        // �����L���O
        R_flg = true;

        // debug�p------------------
        if (key[KEY_INPUT_LEFT])
        {
            pl.posX -= pl.speed;
        }
        if (key[KEY_INPUT_RIGHT])
        {
            pl.posX += pl.speed;
        }
        if (key[KEY_INPUT_0])
        {
            pl.posX++;
        }
        if (key[KEY_INPUT_9])
        {
            pl.posY++;
        }
        if (key[KEY_INPUT_UP])
        {
            pl.posY -= pl.speed;
        }
        if (key[KEY_INPUT_DOWN])
        {
            pl.posY += pl.speed;
        }
        if (key_trg[KEY_INPUT_C])
        {
            game.state = POSE;
        }
        //---------------------------

        break;
#pragma endregion
    case RETRY:
#pragma region RETRY
        ///// ���g���C /////
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
        // degug-------------------
        if (key_trg[KEY_INPUT_C])
        {
            game.state = NORMAL;
        }
        //-----------------------
        game.timer--;
        break;
#pragma endregion
    }

	game.timer++;
}

// �Q�[���̕`�揈��
void game_draw(void)
{
    // �w�i
    if (pl.gravityflg == true)
    {
        game.angle1 = 0;
    }
    else
    {
        game.angle1 = PI;
    }
    DrawRotaGraph(game.bgposX + GAME_SCREEN_WIDTH / 2, game.bgposY + GAME_SCREEN_HEIGHT / 2, 1, game.angle1, game.bgHND[0], true, false);
    DrawRotaGraph(game.bgposX + GAME_SCREEN_WIDTH + GAME_SCREEN_WIDTH / 2, game.bgposY + GAME_SCREEN_HEIGHT / 2, 1, game.angle1, game.bgHND[0], true, false);
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
    DrawRotaGraph(game.bgposX + GAME_SCREEN_WIDTH / 2, game.bgposY + GAME_SCREEN_HEIGHT / 2, 1, game.angle1, game.bgHND[1], true, false);
    DrawRotaGraph(game.bgposX + GAME_SCREEN_WIDTH + GAME_SCREEN_WIDTH / 2, game.bgposY + GAME_SCREEN_HEIGHT / 2, 1, game.angle1, game.bgHND[1], true, false);
    //DrawGraph(game.bgposX, game.bgposY, game.bg2HND, true);
    //DrawGraph(game.bgposX + GAME_SCREEN_WIDTH, 0, game.bg2HND, true);

    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

    stage_draw();
    player_draw();

    if (game.state == RETRY)
    {
        retry_draw();
    }
    // debug�p ------------------------------------------------------------------------------
    DrawFormatString(0, 0, GetColor(0, 255, 255), "�V�[���؂�ւ�");
    DrawFormatString(0, 20, GetColor(0, 255, 255), "title:1�L�[");
    DrawFormatString(0, 40, GetColor(0, 255, 255), "select:2�L�[");
    DrawFormatString(0, 60, GetColor(0, 255, 255), "load:3�L�[");
    DrawFormatString(0, 80, GetColor(0, 255, 255), "game:4�L�[");
    DrawFormatString(0, 100, GetColor(0, 255, 255), "result:5�L�[");
    DrawFormatString(0, 120, GetColor(0, 255, 255), "�d�͔��]:Z�L�[");
    DrawFormatString(0, 140, GetColor(0, 255, 255), "���Z�b�g:X�L�[");
    DrawFormatString(0, 160, GetColor(0, 255, 255), "�|�[�Y:C�L�[");
    
    DrawFormatString(150, 0, GetColor(0, 255, 255), "game.timer:%d", game.timer);
    DrawFormatString(150, 20, GetColor(0, 255, 255), "game.score:%d", game.score);
    DrawFormatString(150, 40, GetColor(0, 255, 255), "game.deathflg:%d", game.deathflg);
    DrawFormatString(150, 60, GetColor(0, 255, 255), "game.clearflg:%d", game.clearflg);

    DrawFormatString(300, 0, GetColor(0, 255, 255), "pl.posX:%d", pl.posX);
    DrawFormatString(300, 20, GetColor(0, 255, 255), "pl.posY:%d", pl.posY);
    DrawFormatString(300, 40, GetColor(0, 255, 255), "pl.gravity:%d", pl.gravity);
    DrawFormatString(300, 60, GetColor(0, 255, 255), "pl.gravityflg:%d", pl.gravityflg);
    DrawFormatString(300, 80, GetColor(0, 255, 255), "pl.grandflg:%d", pl.grandflg);
    //--------------------------------------------------------------------------------------
}

// �v���C���[�̕`�揈��
void player_draw(void)
{
    if (game.deathflg == false)
    {
        if (pl.gravityflg == true)
        {
            DrawGraph(GAME_SCREEN_WIDTH / 2, pl.posY, pl.plHND[game.timer / 3 % 5], true);
        }
        else
        {
            DrawTurnGraph(GAME_SCREEN_WIDTH / 2, pl.posY, pl.plHND[game.timer / 3 % 5], true);
        }
    }
    // debug�p
    DrawBox(GAME_SCREEN_WIDTH / 2, pl.posY, GAME_SCREEN_WIDTH / 2 + CHIP_SIZE + 1, pl.posY + CHIP_SIZE + 1, GetColor(255, 255, 255), FALSE);
}

// ���g���C�̕`�揈��
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

//// BGM�̍Đ�����
//void sound_play(void)
//{
//    PlaySoundMem(game.bgmHND, DX_PLAYTYPE_BACK, TRUE);
//}

// �Q�[���̏I������
void game_end(void)
{
    for (int i = 0; i < 2; i++)
    {
        DeleteGraph(game.bgHND[i]);
        DeleteGraph(game.reHND[i]);
    }
    DeleteSoundMem(game.bgmHND);

    stage_end();
    player_end();
}

// �v���C���[�̏I������
void player_end(void)
{
    for (int i = 0; i < 5; i++)
    {
        DeleteGraph(pl.plHND[i]);
    }
}