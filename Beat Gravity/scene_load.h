#pragma once
// �萔 ----------------------------------------------------------------

// �N���X --------------------------------------------------------------
class LOAD
{
public:
    int state = 0;					// ���
    int timer = 0;					// �^�C�}�[
    int rnd = 0;
    int bgHND[13] = { 0 };			// �w�i�̃f�[�^�n���h��
    int bg[6] = { 0 };
    bool transition_flg = false;	// �V�[���J�ڗp�̃t���O
};

// �v���g�^�C�v�錾 -----------------------------------------------------
void load_initialize(void);
void load_update(void);
void load_draw(void);
void load_end(void);