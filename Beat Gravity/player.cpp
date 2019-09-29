// �C���N���[�h -------------------------------------------------------------------------------------
#include "DxLib.h"

#include "common.h"
#include "input.h"
#include "player.h"
#include "stage.h"

// �ϐ� --------------------------------------------------------------------------------------------
// �L�[�p�ϐ�
extern char key_buf[MAX_KEY];

// �V�[���J�ڗp�ϐ�
extern int nextScene;

// �C���X�^���X�錾 ---------------------------------------------------------------------------------
PLAYER pl;

// �֐����� ----------------------------------------------------------------------------------------
// �v���C���[�̏����ݒ�
void player_initialize(void)
{
    pl.state = 0;
    pl.posX = 0;
    pl.posY = 0;
    pl.pivotX = 0;
    pl.pivotY = 0;
    pl.plHND = LoadGraph("Data\\Images\\player.png");
}

// �v���C���[�̍X�V����
void player_update(void)
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
    switch (pl.state)
    {
    case INIT:
        ///// �����ݒ� /////
        pl.state++;
        break;

    case NORMAL:
        ///// �ʏ펞 /////
        // �v���C���[�̒��S���W���X�V
        pl.pivotX = pl.posX + PLAYER_SIZE / 2;
        pl.pivotY = pl.posY + PLAYER_SIZE / 2;

        // debug�p------------------
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

// �v���C���[�̕`�揈��
void player_draw(void)
{
    DrawGraph(pl.posX, pl.posY, pl.plHND, true);
    // debug�p
    DrawBox(pl.posX, pl.posY, pl.posX+63,pl.posY+63,GetColor(1, 0, 0), FALSE);
}

// �v���C���[�̏I������
void player_end(void)
{
    DeleteGraph(pl.plHND);
}