#pragma once
// �萔 ----------------------------------------------------------------

// �N���X --------------------------------------------------------------
class PLAYER
{
public:
    int state = 0;					// ���
    int plHND = 0;					// player�̃O���t�B�b�N�f�[�^�n���h��
};

// �v���g�^�C�v�錾 -----------------------------------------------------
void player_initialize(void);	// �v���C���[�̏����ݒ�
void player_update(void);		// �v���C���[�̍X�V����
void player_draw(void);			// �v���C���[�̕`�揈��
void player_end(void);			// �v���C���[�̏I������