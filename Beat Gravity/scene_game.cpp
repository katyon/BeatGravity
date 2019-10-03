// �C���N���[�h -------------------------------------------------------------------------------------
#include "DxLib.h"

#include "common.h"
#include "scene_game.h"
#include "stage.h"

// �ϐ� --------------------------------------------------------------------------------------------
// �L�[�p�ϐ�
extern char key_buf[MAX_KEY];

// �V�[���J�ڗp�ϐ�
extern int nextScene;

// �C���X�^���X�錾 ---------------------------------------------------------------------------------
GAME game;

PLAYER pl;

// �֐����� ----------------------------------------------------------------------------------------
// �Q�[���̏����ݒ�
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

// �v���C���[�̏����ݒ�
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
            game.state++;
        }
        else
        {
            ///// �v���C���[�̍X�V /////
            // �ʏ�d��
            if (pl.gravityflg == true)
            {
                // �W�����v
                if (pl.grandflg == true && key[KEY_INPUT_SPACE])
                {
                    pl.gravity -= pl.jumppower;
                }

                // �d�͂ƉE�ړ�
                pl.posY += pl.gravity;
                pl.posX += pl.speed;

                // �}�b�v�`�b�v���Ƃ̋���
                // ��
                if (detect_chip(pl.posX, pl.posY + CHIP_SIZE - 1) == EMPTY ||
                    detect_chip(pl.posX + CHIP_SIZE - 1, pl.posY + CHIP_SIZE - 1) == EMPTY)
                {
                    pl.grandflg = false;
                    pl.gravity += GRAVITY;
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
                // ��(��)
                if (detect_chip(pl.posX + CHIP_SIZE - 1, pl.posY) == LEFT ||
                    detect_chip(pl.posX + CHIP_SIZE - 1, pl.posY + CHIP_SIZE - 1) == LEFT)
                {
                    // ���S����
                    game.deathflg = true;
                }
            }
            // ���]�d��
            else
            {
                // �W�����v
                if (pl.grandflg == true && key[KEY_INPUT_SPACE])
                {
                    pl.gravity -= pl.jumppower;
                }

                // �d�͂ƉE�ړ�
                pl.posY -= pl.gravity;
                pl.posX += pl.speed;

                // �}�b�v�`�b�v���Ƃ̋���
                // ��
                if (detect_chip(pl.posX, pl.posY) == EMPTY ||
                    detect_chip(pl.posX + CHIP_SIZE - 1, pl.posY) == EMPTY)
                {
                    pl.grandflg = false;
                    pl.gravity += GRAVITY;
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
            }
            // �w�i�X�N���[������
            game.bgposX -= game.bgspeed;
            if (game.bgposX + GAME_SCREEN_WIDTH < 0)
            {
                game.bgposX = 0;
            }
        }
        // debug�p------------------
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

        break;
#pragma endregion
    }

	game.timer++;
}

// �Q�[���̕`�揈��
void game_draw(void)
{
    // �w�i
	DrawGraph(game.bgposX, game.bgposY, game.bgHND, false);
    DrawGraph(game.bgposX + GAME_SCREEN_WIDTH, 0, game.bgHND, false);

    stage_draw();
    player_draw();

    if (game.state == RETRY)
    {
        retry_draw();
    }
    // debug�p ------------------------------------------------------------------------------
    DrawFormatString(0, 0, GetColor(255, 255, 255), "�V�[���؂�ւ�");
    DrawFormatString(0, 20, GetColor(255, 255, 255), "title:1�L�[");
    DrawFormatString(0, 40, GetColor(255, 255, 255), "select:2�L�[");
    DrawFormatString(0, 60, GetColor(255, 255, 255), "load:3�L�[");
    DrawFormatString(0, 80, GetColor(255, 255, 255), "game:4�L�[");
    DrawFormatString(0, 100, GetColor(255, 255, 255), "result:5�L�[");
    DrawFormatString(0, 120, GetColor(255, 255, 255), "�d�͔��]:Z�L�[");
    DrawFormatString(0, 140, GetColor(255, 255, 255), "���Z�b�g:X�L�[");
    
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

// �v���C���[�̕`�揈��
void player_draw(void)
{
    DrawGraph(GAME_SCREEN_WIDTH / 2, pl.posY, pl.plHND, true);
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

// �Q�[���̏I������
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

// �v���C���[�̏I������
void player_end(void)
{
    DeleteGraph(pl.plHND);
}