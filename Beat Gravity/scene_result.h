#pragma once
// �萔 ----------------------------------------------------------------
#define Score_h 5

// �N���X --------------------------------------------------------------
class RESULT
{
public:
    int state = 0;					// ���
    int timer = 0;					// �^�C�}�[
    int bgHND = 0;					// �w�i�̃f�[�^�n���h��
    bool transition_flg = false;	// �V�[���J�ڗp�̃t���O
};

// �v���g�^�C�v�錾 -----------------------------------------------------
void result_initialize(void);
void result_update(void);
void result_draw(void);
void result_end(void);

