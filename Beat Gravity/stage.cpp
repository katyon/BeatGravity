// �C���N���[�h -------------------------------------------------------------------------------------
#include "DxLib.h"

#include "input.h"
#include "stage.h"

// �ϐ� --------------------------------------------------------------------------------------------

// �C���X�^���X�錾 ---------------------------------------------------------------------------------
STAGE stage;

// �֐����� ----------------------------------------------------------------------------------------
// �X�e�[�W�̏����ݒ�
void stage_initialize(void)
{
    stage.num = STAGE4;
    stage.chip = 0;
#pragma region ConstInit
    for (int i = 0; i < STAGE1_XCONST; i++)
    {
        for (int j = 0; j < STAGE1_YCONST; j++)
        {
            stage.const1[i][j] = 0;
        }
    }
    for (int i = 0; i < STAGE2_XCONST; i++)
    {
        for (int j = 0; j < STAGE2_YCONST; j++)
        {
            stage.const2[i][j] = 0;
        }
    }
    for (int i = 0; i < STAGE3_XCONST; i++)
    {
        for (int j = 0; j < STAGE3_YCONST; j++)
        {
            stage.const3[i][j] = 0;
        }
    }
    for (int i = 0; i < STAGE4_XCONST; i++)
    {
        for (int j = 0; j < STAGE4_YCONST; j++)
        {
            stage.const4[i][j] = 0;
        }
    }
#pragma endregion
    int a=LoadDivGraph("Data//Images//stage.png", STAGE_ALLNUM, 4, 4, 64, 64, stage.stageHND);
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
        for (int i = 0; i < STAGE4_XCONST; i++)
        {
            for (int j = 0; j < STAGE4_YCONST; j++)
            {
                switch (stage.chip)
                {
                case UP:
                    DrawGraph(64 * i, 64 * j, stage.stageHND[0], true);
                    break;
                case DOWN:
                    DrawGraph(64 * i, 64 * j, stage.stageHND[1], true);
                    break;
                case LEFT:
                    DrawGraph(64 * i, 64 * j, stage.stageHND[2], true);
                    break;
                case RIGHT:
                    DrawGraph(64 * i, 64 * j, stage.stageHND[3], true);
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
        DeleteGraph(stage.stageHND[i]);
    }
}