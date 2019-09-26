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
    int chip;                                 // �}�b�v�`�b�v�̎�ޕ����p
    int const1[STAGE1_XCONST][STAGE1_YCONST]; // �X�e�[�W1�̍\��
    int const2[STAGE2_XCONST][STAGE2_YCONST]; // �X�e�[�W2�̍\��
    int const3[STAGE3_XCONST][STAGE3_YCONST]; // �X�e�[�W3�̍\��
    int const4[STAGE4_XCONST][STAGE4_YCONST]; // debug�p�̍\��
    int stageHND[STAGE_ALLNUM];               // stage�̃O���t�B�b�N�n���h��
};

// �v���g�^�C�v�錾 -----------------------------------------------------
void stage_initialize(void);    // �X�e�[�W�̏����ݒ�
void stage_draw(void);          // �X�e�[�W�̕`�揈��
void stage_end(void);           // �X�e�[�W�̏I������