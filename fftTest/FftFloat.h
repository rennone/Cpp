// FftFloat.h : FftFloat アプリケーションのメイン ヘッダー ファイル
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH に対してこのファイルをインクルードする前に 'stdafx.h' をインクルードしてください"
#endif

#include "resource.h"       // メイン シンボル


// CFftFloatApp:
// このクラスの実装については、FftFloat.cpp を参照してください。
//

class CFftFloatApp : public CWinApp
{
public:
	CFftFloatApp();


// オーバーライド
public:
	virtual BOOL InitInstance();

// 実装
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CFftFloatApp theApp;