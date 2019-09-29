#pragma once
// �萔 ----------------------------------------------------------------
#define STAGE_ALLNUM     (16)
#define STAGE1_XCONST    (16)
#define STAGE1_YCONST    (9)
#define STAGE2_XCONST    (16)
#define STAGE2_YCONST    (9)
#define STAGE3_XCONST    (16)
#define STAGE3_YCONST    (9)
#define STAGE4_XCONST    (25)
#define STAGE4_YCONST    (15)

enum STAGENUM
{
    STAGE1, STAGE2, STAGE3,STAGE4
};

enum CHIP
{
    UP, DOWN, LEFT, RIGHT, HOLE
};

// �N���X --------------------------------------------------------------
class STAGE
{
public:
    int num;                                  // �X�e�[�W�i���o�[
    int chipHND[STAGE_ALLNUM];                // �}�b�v�`�b�v�̃O���t�B�b�N�n���h��
};

// �v���g�^�C�v�錾 -----------------------------------------------------
void stage_initialize(void);     // �X�e�[�W�̏����ݒ�
int detect_chip(int pl_posX, int pl_posY, int stage_num);  // �Ή�����}�b�v�`�b�v�̔ԍ������o
void stage_draw(void);           // �X�e�[�W�̕`�揈��
void stage_end(void);            // �X�e�[�W�̏I������