// FftFloatView.h : CFftFloatView �N���X�̃C���^�[�t�F�C�X
//


#pragma once


class CFftFloatView : public CView
{
protected: // �V���A��������̂ݍ쐬���܂��B
	CFftFloatView();
	DECLARE_DYNCREATE(CFftFloatView)

// ����
public:
	CFftFloatDoc* GetDocument() const;

// ����
public:

// �I�[�o�[���C�h
public:
	virtual void OnDraw(CDC* pDC);  // ���̃r���[��`�悷�邽�߂ɃI�[�o�[���C�h����܂��B
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ����
public:
	virtual ~CFftFloatView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// �������ꂽ�A���b�Z�[�W���蓖�Ċ֐�
protected:
	DECLARE_MESSAGE_MAP()
public:
	void TxtLoad(CString fn, double *iW);
	void WaveDraw(CDC *pDC, int x1, int y1, int yrng, double *iW, BOOL scfreq, BOOL x10);
	void WaveDraw2(CDC *pDC, int x1, int y1, int yrng, double *iW, double *iW2, BOOL scfreq, BOOL x10);
	double Fsamp;
	double InWave[1024];
	double TriData[1024];
	double PwrSpec[1024];
	double RealSpec[1024];
	double ImagSpec[1024];
	BOOL InputLoaded;
	BOOL FftExecuted;
	BOOL ViewX10;
	void FftCal(double *iW, double *tW, double *oR, double *oI, double *oP);
	afx_msg void OnFftLoad();
	afx_msg void OnFftExec();
	afx_msg void OnViewX10();
	afx_msg void OnUpdateViewX10(CCmdUI *pCmdUI);
};

#ifndef _DEBUG  // FftFloatView.cpp �̃f�o�b�O �o�[�W����
inline CFftFloatDoc* CFftFloatView::GetDocument() const
   { return reinterpret_cast<CFftFloatDoc*>(m_pDocument); }
#endif

