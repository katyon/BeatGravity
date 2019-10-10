#pragma once
// �萔 ----------------------------------------------------------------
#define STAGE_ALLNUM       (36)
#define STAGE_SIZE_X       (1700)
#define STAGE_SIZE_Y       (54)

enum STAGENUM
{
    STAGE1, STAGE2, STAGE3
};

enum CHIP
{
    EMPTY, BOTTOM, BOTTOM_LCORNER, BOTTOM_RCORNER, BOTTOM_INSIDE, BOTTOM_LEFT, BOTTOM_RIGHT, BOTTOM_AIR, BOTTOM_LAIR, BOTTOM_RAIR,
    TOP, TOP_LCORNER, TOP_RCORNER, TOP_INSIDE, TOP_LEFT, TOP_RIGHT, TOP_AIR, TOP_LAIR, TOP_RAIR, DARK, LDARK, RDARK,
    HOLE, BOTTOM_NEEDLE, TOP_NEEDLE, AIRJUMP, BOTTOM_JUMPPAD, TOP_JUMPPAD, ITEM1, ITEM2, CHANGE_GRAVITY, GOAL
};

// �N���X --------------------------------------------------------------
class STAGE
{
public:
    int num;                                        // �X�e�[�W�i���o�[
    int map_copy[STAGE_SIZE_Y][STAGE_SIZE_X] = { 0 };   // �e�X�e�[�W�̃R�s�[
    int chipHND[STAGE_ALLNUM];                      // �}�b�v�`�b�v�̃O���t�B�b�N�n���h��
};

// �v���g�^�C�v�錾 -----------------------------------------------------
void load_mapFile(void);         // �X�e�[�W�̓ǂݍ���
void stage_initialize(void);     // �X�e�[�W�̏����ݒ�
int detect_chip(int pl_posX, int pl_posY);  // �Ή�����}�b�v�`�b�v�̔ԍ������o
void stage_draw(void);           // �X�e�[�W�̕`�揈��
void stage_end(void);            // �X�e�[�W�̏I������