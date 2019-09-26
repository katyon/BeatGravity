// �C���N���[�h -------------------------------------------------------------------------------------
#include "DxLib.h"

#include "common.h"
#include "input.h"
#include "player.h"

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

        break;
    }
}

// �v���C���[�̕`�揈��
void player_draw(void)
{
    DrawGraph(0, 0, pl.plHND, true);
}

// �v���C���[�̏I������
void player_end(void)
{
    DeleteGraph(pl.plHND);
}