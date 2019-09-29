// �C���N���[�h -------------------------------------------------------------------------------------
#include "DxLib.h"

#include "input.h"
#include "player.h"
#include "stage.h"

// �ϐ� --------------------------------------------------------------------------------------------

// �C���X�^���X�錾 ---------------------------------------------------------------------------------
STAGE stage;

// �X�e�[�W�\�� ------------------------------------------------------------------------------------
#pragma region ConstInit
// �X�e�[�W1
int const1[STAGE1_YCONST][STAGE1_XCONST] = { 0 };

// �X�e�[�W2
int const2[STAGE2_YCONST][STAGE2_XCONST] = { 0 };

// �X�e�[�W3
int const3[STAGE3_YCONST][STAGE3_XCONST] = { 0 };

// debug�p
int const4[STAGE4_YCONST][STAGE4_XCONST] = {
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
};
#pragma endregion

// �֐����� ----------------------------------------------------------------------------------------
// �X�e�[�W�̏����ݒ�
void stage_initialize(void)
{
    // debug�p
    stage.num = STAGE4;

    LoadDivGraph("Data//Images//stage.png", STAGE_ALLNUM, 4, 4, 64, 64, stage.chipHND);
}

// �Ή�����}�b�v�`�b�v�̔ԍ������o
int detect_chip(int pl_posX, int pl_posY, int stage_num)
{
    switch (stage_num)
    {
    case STAGE1:
        return const1[pl_posY / 64][pl_posX / 64];
        break;
    case STAGE2:
        return const2[pl_posY / 64][pl_posX / 64];
        break;
    case STAGE3:
        return const3[pl_posY / 64][pl_posX / 64];
        break;
        // debug�p
    case STAGE4:
        return const4[pl_posY / 64][pl_posX / 64];
        break;
    }
}

// �X�e�[�W�̕`�揈��
void stage_draw(void)
{
    switch (stage.num)
    {
    case STAGE1:

        break;
    case STAGE2:

        break;
    case STAGE3:

        break;
        // debug�p
    case STAGE4:
        for (int i = 0; i < STAGE4_YCONST; i++)
        {
            for (int j = 0; j < STAGE4_XCONST; j++)
            {
                switch (const4[i][j])
                {
                case UP:
                    DrawGraph(64 * j, 64 * i, stage.chipHND[0], true);
                    break;
                case DOWN:
                    DrawGraph(64 * j, 64 * i, stage.chipHND[1], true);
                    break;
                case LEFT:
                    DrawGraph(64 * j, 64 * i, stage.chipHND[2], true);
                    break;
                case RIGHT:
                    DrawGraph(64 * j, 64 * i, stage.chipHND[3], true);
                    break;
                }
            }
        }
        break;
    }
}

// �X�e�[�W�̏I������
void stage_end(void)
{
    for (int i = 0; i < STAGE_ALLNUM; i++)
    {
        DeleteGraph(stage.chipHND[i]);
    }
}