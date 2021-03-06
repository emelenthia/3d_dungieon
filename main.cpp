#include "DxLib.h"
#include<time.h>
#include "SceneBase.h"
#include"Battle.h"
#include"Key_Input.h"
#include"Flags.h"
#include"Scene.h"
#include"Colors.h"
#include"FPSer.h"

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{

	ChangeWindowMode(TRUE); // ウィンドウモードに設定
	SetMainWindowText("名称未設定"); //タイトルの指定。何にしよう
	SetDrawScreen(DX_SCREEN_BACK);
	//SetBackgroundColor(0, 0, 0); //背景の色変更5
	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	Scene scene; //現在の場面
	Key_Input key_input; //キー入力用
	//int reaction_return; //Reaction()の返り値を受け取る
	Flags flags;
	Colors colors; //コンストラクタ
	FPSer fpser;
	
	while (1) //メインループ
	{

		ClearDrawScreen(); //画面をクリア。描画処理はこれより後に書く

		key_input.KeyUpdate(); //キー入力
		//reaction_return = nowpointa->Reaction(); //キー入力などによる情報の更新
		scene.Reaction(); //キー入力などによる情報の更新
		scene.Draw(); //現在の場面の描画
		//fpser.CountFPS(); //デバッグ的な

		ScreenFlip(); //裏と表の仲介役。描画処理よりも後に書く


		if (ProcessMessage()) //×クリック待ち
		{
			break;
		}
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)  //Esc入力待ち
		{
			break;
		}
	}
	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}