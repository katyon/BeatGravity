// インクルード -------------------------------------------------------------------------------------
//#include "DxLib.h"
//
//#include "input.h"

// 関数実体 ----------------------------------------------------------------------------------------
//// 入力状態の初期化
//void INPUTKEY::initialize(void)
//{
//    for (int i = 0; i < MAX_KEY; i++)
//    {
//        key_buf[i] = 0;
//        key[i] = 0;
//        key_trg[i] = 0;
//    }
//}
//
//// 入力状態の更新
//void INPUTKEY::update(void)
//{
//	GetHitKeyStateAll(key);
//
//	for (int n = 0; n < MAX_KEY; n++)
//	{
//		if (key[n] && !(key_buf[n]))
//		{
//            key_trg[n] = key[n];
//		}
//        key_buf[n] = key[n];
//	}
//}