#pragma once
// �萔 ----------------------------------------------------------------

// �N���X --------------------------------------------------------------
class SELECT
{
public:
    int state = 0;					// ���
    int timer = 0;					// �^�C�}�[
    int bgposX = 0;
    int bgposY = 0;
    int bgHND = 0;					// �w�i�̃f�[�^�n���h��
    int numHND[4] = { 0 };          // select�p�n���h��
    int sceneHND = 0;
    int decideSE = 0;
    int choiceSE = 0;
    bool transition_flg = false;	// �V�[���J�ڗp�̃t���O
};

// �v���g�^�C�v�錾 -----------------------------------------------------
void select_initialize(void);
void select_update(void);
void select_draw(void);
void select_end(void);