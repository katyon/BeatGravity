#pragma once
// �萔 ----------------------------------------------------------------
#define GAME_SCREEN_WIDTH	(1920)  // �Q�[����ʂ̕�
#define GAME_SCREEN_HEIGHT	(1080)  // �Q�[����ʂ̍���
#define MAX_KEY	(256)
#define CHIP_SIZE           (60)    // �}�b�v�`�b�v�̈������̑傫��
#define GRAVITY             (2)     // �d�͉����x

// �V�[���Ǘ��p�萔
enum SCENE_CASE
{
	SCENE_TITLE, SCENE_GAME, SCENE_RESULT
};

// state�p�萔
enum STATE
{
	INIT,NORMAL
};