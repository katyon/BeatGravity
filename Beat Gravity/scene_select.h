#pragma once
// �萔 ----------------------------------------------------------------

// �N���X --------------------------------------------------------------
class SELECT
{
public:
    int state = 0;					// ���
    int timer = 0;					// �^�C�}�[
    int bgHND = 0;					// �w�i�̃f�[�^�n���h��
    bool transition_flg = false;	// �V�[���J�ڗp�̃t���O
};

// �v���g�^�C�v�錾 -----------------------------------------------------
void select_initialize(void);
void select_update(void);
void select_draw(void);
void select_end(void);