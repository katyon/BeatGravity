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
	game.titmer = 0;
	game.nextSceneflg = false;
	game.bgHND = LoadGraph("Data\\Images\\game_bg.png");
}

// �v���C���[�̏����ݒ�
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
		///// �����ݒ� /////
        player_initialize();
        stage_initialize();
		game.state++;
		break;

	case NORMAL:
		///// �ʏ펞 /////
		// debug�p-------------------------
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
                detect_chip(pl.posX + CHIP_SIZE - 1,pl.posY) == TOP)
            {
                // �ړ�����
                pl.posY = pl.posY / CHIP_SIZE * CHIP_SIZE + CHIP_SIZE;

                pl.grandflg = true;
                pl.gravity = 0;
            }
        }
        // debug�p------------------
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

// �Q�[���̕`�揈��
void game_draw(void)
{
	DrawGraph(0, 0, game.bgHND, false);
    stage_draw();
    player_draw();
}

// �v���C���[�̕`�揈��
void player_draw(void)
{
    DrawGraph(GAME_SCREEN_WIDTH / 2, pl.posY, pl.plHND, true);
    // debug�p
    DrawBox(GAME_SCREEN_WIDTH / 2, pl.posY, GAME_SCREEN_WIDTH / 2 + CHIP_SIZE - 1, pl.posY + CHIP_SIZE - 1, GetColor(1, 1, 1), FALSE);
}

// �Q�[���̏I������
void game_end(void)
{
	DeleteGraph(game.bgHND);
    stage_end();
    player_end();
}

// �v���C���[�̏I������
void player_end(void)
{
    DeleteGraph(pl.plHND);
}