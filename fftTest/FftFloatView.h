// FftFloatView.h : CFftFloatView クラスのインターフェイス
//


#pragma once


class CFftFloatView : public CView
{
protected: // シリアル化からのみ作成します。
	CFftFloatView();
	DECLARE_DYNCREATE(CFftFloatView)

// 属性
public:
	CFftFloatDoc* GetDocument() const;

// 操作
public:

// オーバーライド
public:
	virtual void OnDraw(CDC* pDC);  // このビューを描画するためにオーバーライドされます。
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 実装
public:
	virtual ~CFftFloatView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成された、メッセージ割り当て関数
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

#ifndef _DEBUG  // FftFloatView.cpp のデバッグ バージョン
inline CFftFloatDoc* CFftFloatView::GetDocument() const
   { return reinterpret_cast<CFftFloatDoc*>(m_pDocument); }
#endif

