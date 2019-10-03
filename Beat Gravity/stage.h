#pragma once
// �萔 ----------------------------------------------------------------
#define STAGE_ALLNUM     (16)
#define STAGE_XMAX       (256)
#define STAGE_YMAX       (36)
#define STAGE1_XCONST    (16)
#define STAGE1_YCONST    (9)
#define STAGE2_XCONST    (16)
#define STAGE2_YCONST    (9)
#define STAGE3_XCONST    (16)
#define STAGE3_YCONST    (9)
#define STAGE4_XCONST    (64)
#define STAGE4_YCONST    (18)

enum STAGENUM
{
    STAGE1, STAGE2, STAGE3,STAGE4
};

enum CHIP
{
    EMPTY, TOP, BOTTOM, LEFT, RIGHT, LCORNER, RCORNER, INSIDE, 
    HOLE,
};

// �N���X --------------------------------------------------------------
class STAGE
{
public:
    int num;                                        // �X�e�[�W�i���o�[
    int map_copy[STAGE_YMAX][STAGE_XMAX] = { 0 };   // �e�X�e�[�W�̃R�s�[
    int chipHND[STAGE_ALLNUM];                      // �}�b�v�`�b�v�̃O���t�B�b�N�n���h��
};

// �v���g�^�C�v�錾 -----------------------------------------------------
void stage_initialize(void);     // �X�e�[�W�̏����ݒ�
int detect_chip(int pl_posX, int pl_posY);  // �Ή�����}�b�v�`�b�v�̔ԍ������o
void stage_draw(void);           // �X�e�[�W�̕`�揈��
void stage_end(void);            // �X�e�[�W�̏I������