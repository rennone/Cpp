// FftFloat.h : FftFloat �A�v���P�[�V�����̃��C�� �w�b�_�[ �t�@�C��
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH �ɑ΂��Ă��̃t�@�C�����C���N���[�h����O�� 'stdafx.h' ���C���N���[�h���Ă�������"
#endif

#include "resource.h"       // ���C�� �V���{��


// CFftFloatApp:
// ���̃N���X�̎����ɂ��ẮAFftFloat.cpp ���Q�Ƃ��Ă��������B
//

class CFftFloatApp : public CWinApp
{
public:
	CFftFloatApp();


// �I�[�o�[���C�h
public:
	virtual BOOL InitInstance();

// ����
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CFftFloatApp theApp;