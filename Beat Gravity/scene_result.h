#pragma once
// �萔 ----------------------------------------------------------------

// �N���X --------------------------------------------------------------
class RESULT
{
public:
    int state = 0;					// ���
    int timer = 0;					// �^�C�}�[
    int scenetimer = 0;
    int sceneposX = 0;
    int sceneposY = 0;
    int bgHND = 0;					// �w�i�̃f�[�^�n���h��
    int spaceHND[2] = { 0 };
    int sceneHND = 0;
    int BGM = 0;
    int decideSE = 0;
    bool transition_flg = false;	// �V�[���J�ڗp�̃t���O
};

// �v���g�^�C�v�錾 -----------------------------------------------------
void result_initialize(void);
void result_update(void);
void result_draw(void);
void result_end(void);

