#pragma once
// �萔 ----------------------------------------------------------------
#define PLAYER_SIZE (70)

// �N���X --------------------------------------------------------------
class PLAYER
{
public:
    int state;  // ���
    int posX;   // X���W
    int posY;   // Y���W
    int pivotX; // ���SX���W
    int pivotY; // ���SY���W
    int plHND;  // player�̃O���t�B�b�N�n���h��
};

// �v���g�^�C�v�錾 -----------------------------------------------------
void player_initialize(void);	    // �v���C���[�̏����ݒ�
void player_update(void);	    	// �v���C���[�̍X�V����
void player_draw(void);		    	// �v���C���[�̕`�揈��
void player_end(void);		    	// �v���C���[�̏I������