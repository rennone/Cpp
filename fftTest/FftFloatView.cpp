// FftFloatView.cpp : CFftFloatView �N���X�̎���
//

#include "stdafx.h"
#include "FftFloat.h"

#include "FftFloatDoc.h"
#include "FftFloatView.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFftFloatView

IMPLEMENT_DYNCREATE(CFftFloatView, CView)

BEGIN_MESSAGE_MAP(CFftFloatView, CView)
	// �W������R�}���h
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_FFT_LOAD, &CFftFloatView::OnFftLoad)
	ON_COMMAND(ID_FFT_EXEC, &CFftFloatView::OnFftExec)
	ON_COMMAND(ID_VIEW_X10, &CFftFloatView::OnViewX10)
	ON_UPDATE_COMMAND_UI(ID_VIEW_X10, &CFftFloatView::OnUpdateViewX10)
END_MESSAGE_MAP()

// CFftFloatView �R���X�g���N�V����/�f�X�g���N�V����

CFftFloatView::CFftFloatView()
{
	// TODO: �\�z�R�[�h�������ɒǉ����܂��B
	Fsamp = 97700.0;
	InputLoaded = FALSE;
	FftExecuted = FALSE;
	ViewX10 = FALSE;
}

CFftFloatView::~CFftFloatView()
{
}

BOOL CFftFloatView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: ���̈ʒu�� CREATESTRUCT cs ���C������ Window �N���X�܂��̓X�^�C����
	//  �C�����Ă��������B

	return CView::PreCreateWindow(cs);
}

// CFftFloatView �`��

void CFftFloatView::OnDraw(CDC* pDC)
{
	CFftFloatDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���̏ꏊ�Ƀl�C�e�B�u �f�[�^�p�̕`��R�[�h��ǉ����܂��B
	if(!InputLoaded) {
		pDC->TextOut( 50, 50, "FftFloat.exe");
		pDC->TextOut( 50, 80, "FFT�𕂓������_�ōs��");
		pDC->TextOut( 50, 110, "���j���[��FFT�����͔g�`�ƎO�p�֐��̓Ǎ���I��");
		pDC->TextOut( 50, 140, "by DIGITALFILTER.COM");
	} else if(!FftExecuted) {
		pDC->TextOut( 50, 10, "���j���[��FFT��FFT�̎��s�ŃX�y�N�g���𓾂�");
		pDC->TextOut( 100, 35, "���͔g�`(6000Hz�T�C���g��97700Hz�T���v�����O");
		WaveDraw(pDC, 80, 140, 1, InWave, FALSE, ViewX10);
		pDC->TextOut( 100, 285, "�O�p�֐�(���������R�T�C���A�E�������T�C��)");
		WaveDraw(pDC, 80, 390, 1, TriData, FALSE, ViewX10);
	} else {
		pDC->TextOut( 100, 15, "�X�y�N�g��(�Ԃ������A�΂�����)");
		WaveDraw2(pDC, 80, 120, 1000, RealSpec, ImagSpec, TRUE, ViewX10);
		pDC->TextOut( 100, 265, "�p���[�X�y�N�g��(������2��{������2��)");
		WaveDraw(pDC, 80, 370, 500000, PwrSpec, TRUE, ViewX10);
	}
}


// CFftFloatView ���

BOOL CFftFloatView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// ����̈������
	return DoPreparePrinting(pInfo);
}

void CFftFloatView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ����O�̓��ʂȏ�����������ǉ����Ă��������B
}

void CFftFloatView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �����̌㏈����ǉ����Ă��������B
}


// CFftFloatView �f�f

#ifdef _DEBUG
void CFftFloatView::AssertValid() const
{
	CView::AssertValid();
}

void CFftFloatView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CFftFloatDoc* CFftFloatView::GetDocument() const // �f�o�b�O�ȊO�̃o�[�W�����̓C�����C���ł��B
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFftFloatDoc)));
	return (CFftFloatDoc*)m_pDocument;
}
#endif //_DEBUG


// CFftFloatView ���b�Z�[�W �n���h��
void CFftFloatView::TxtLoad(CString fn, double *iW)
{
	FILE *ifp;
	int count = 0;
	float doubleline;

	fopen_s( &ifp, fn, "r" );
	// start reading file
	if (ifp != NULL) {
		fseek( ifp, 0L, SEEK_SET );
		while( fscanf(ifp, "%f", &doubleline) != EOF ) {
			iW[count] = (double)doubleline;
			count++;
			if(count == 1024) {
				break;
			}
		} 
		fclose( ifp );
	} else {
		CString tmpstr = fn + "��������܂���B";
		AfxMessageBox(tmpstr, MB_OK|MB_ICONEXCLAMATION);
	}
}

void CFftFloatView::WaveDraw(CDC *pDC, int x1, int y1, int yrng, double *iW, BOOL scfreq, BOOL x10)
{
	CPen	myPen;
	CPen*	pOldPen;

	int i;
	int ytmp;
	char tmpchar[12];
	int xscale = 1024;
	int yscale = 80;
	int dotn = 1024;
	int xstep = 1;

	if(!x10) {
		dotn = 1024;
		xstep = 1;
	} else {
		dotn = 102;
		xstep = 10;
	}

	sprintf(tmpchar,"%7d", yrng);
	pDC->TextOut( x1 - 55, y1 - yscale - 8, tmpchar);
	sprintf(tmpchar,"%6d", -yrng);
	pDC->TextOut( x1 - 55, y1 + yscale - 8, tmpchar);
	pDC->TextOut( x1 - 20, y1 - 8, "0");

	if(!scfreq) {
		for(i = 0; i <= 8; i++) {
			sprintf(tmpchar,"%7.5f", (double)(dotn*i/8)/Fsamp);
			pDC->TextOut( x1 + xscale*i/8 - 30, y1 + yscale + 8, tmpchar);
		}
		pDC->TextOut( x1 + xscale + 30, y1 + yscale + 8, "[s]");
	} else {
		for(i = 0; i <= 8; i++) {
			if(!x10) sprintf(tmpchar,"%7.0f", Fsamp*i/8);
			else sprintf(tmpchar,"%7.0f", Fsamp*i/8/10);
			pDC->TextOut( x1 + xscale*i/8 - 30, y1 + yscale + 8, tmpchar);
		}
		pDC->TextOut( x1 + xscale + 30, y1 + yscale + 8, "[Hz]");
	}

	myPen.CreatePen(PS_SOLID, 1, RGB(200,200,200));
	pOldPen = pDC->SelectObject(&myPen);

	pDC->MoveTo(x1, y1);
	pDC->LineTo(x1 + xscale, y1);

	pDC->MoveTo(x1, y1 - yscale);
	pDC->LineTo(x1 + xscale, y1 - yscale);

	pDC->MoveTo(x1, y1 + yscale);
	pDC->LineTo(x1 + xscale, y1 + yscale);

	pDC->MoveTo(x1, y1 - yscale);
	pDC->LineTo(x1, y1 + yscale);
	for(i = 1; i <= 7; i++) {
		pDC->MoveTo(x1 + xscale * i / 8, y1 - yscale);
		pDC->LineTo(x1 + xscale * i / 8, y1 + yscale);
	}
	pDC->MoveTo(x1 + xscale, y1 - yscale);
	pDC->LineTo(x1 + xscale, y1 + yscale);

	pDC->SelectObject(pOldPen);
	myPen.DeleteObject();

	myPen.CreatePen(PS_SOLID, 1, RGB(0,0,255));
	pOldPen = pDC->SelectObject(&myPen);

	for(i = 0; i < dotn-1; i++) {
		ytmp = (int)(-yscale * iW[i+0] / yrng);
		if( ytmp > yscale ) ytmp = yscale;
		if( ytmp < -yscale ) ytmp = -yscale;
		pDC->MoveTo(x1 + (i+0) * xstep, y1 + ytmp);
		ytmp = (int)(-yscale * iW[i+1] / yrng);
		if( ytmp > yscale ) ytmp = yscale;
		if( ytmp < -yscale ) ytmp = -yscale;
		pDC->LineTo(x1 + (i+1) * xstep, y1 + ytmp);
	}
	pDC->SelectObject(pOldPen);
	myPen.DeleteObject();
}

void CFftFloatView::WaveDraw2(CDC *pDC, int x1, int y1, int yrng, double *iW, double *iW2, BOOL scfreq, BOOL x10)
{
	CPen	myPen;
	CPen*	pOldPen;

	int i;
	int ytmp;
	char tmpchar[12];
	int xscale = 1024;
	int yscale = 80;
	int dotn, xstep;
	
	if(!x10) {
		dotn = 1024;
		xstep = 1;
	} else {
		dotn = 102;
		xstep = 10;
	}

	sprintf(tmpchar,"%7d", yrng);
	pDC->TextOut( x1 - 55, y1 - yscale - 8, tmpchar);
	sprintf(tmpchar,"%6d", -yrng);
	pDC->TextOut( x1 - 55, y1 + yscale - 8, tmpchar);
	pDC->TextOut( x1 - 20, y1 - 8, "0");

	if(!scfreq) {
		for(i = 0; i <= 8; i++) {
			sprintf(tmpchar,"%7.5f", (double)(dotn*i/8)/Fsamp);
			pDC->TextOut( x1 + xscale*i/8 - 30, y1 + yscale + 8, tmpchar);
		}
		pDC->TextOut( x1 + xscale + 30, y1 + yscale + 8, "[s]");
	} else {
		for(i = 0; i <= 8; i++) {
			if(!x10) sprintf(tmpchar,"%7.0f", Fsamp*i/8);
			else sprintf(tmpchar,"%7.0f", Fsamp*i/8/10);
			pDC->TextOut( x1 + xscale*i/8 - 30, y1 + yscale + 8, tmpchar);
		}
		pDC->TextOut( x1 + xscale + 30, y1 + yscale + 8, "[Hz]");
	}

	myPen.CreatePen(PS_SOLID, 1, RGB(200,200,200));
	pOldPen = pDC->SelectObject(&myPen);

	pDC->MoveTo(x1, y1);
	pDC->LineTo(x1 + xscale, y1);

	pDC->MoveTo(x1, y1 - yscale);
	pDC->LineTo(x1 + xscale, y1 - yscale);

	pDC->MoveTo(x1, y1 + yscale);
	pDC->LineTo(x1 + xscale, y1 + yscale);

	pDC->MoveTo(x1, y1 - yscale);
	pDC->LineTo(x1, y1 + yscale);
	for(i = 1; i <= 7; i++) {
		pDC->MoveTo(x1 + xscale * i / 8, y1 - yscale);
		pDC->LineTo(x1 + xscale * i / 8, y1 + yscale);
	}
	pDC->MoveTo(x1 + xscale, y1 - yscale);
	pDC->LineTo(x1 + xscale, y1 + yscale);

	pDC->SelectObject(pOldPen);
	myPen.DeleteObject();

	myPen.CreatePen(PS_SOLID, 2, RGB(255,0,0));
	pOldPen = pDC->SelectObject(&myPen);

	for(i = 0; i < dotn-1; i++) {
		ytmp = (int)(-yscale * iW[i+0] / yrng);
		if( ytmp > yscale ) ytmp = yscale;
		if( ytmp < -yscale ) ytmp = -yscale;
		pDC->MoveTo(x1 + (i+0) * xstep, y1 + ytmp);
		ytmp = (int)(-yscale * iW[i+1] / yrng);
		if( ytmp > yscale ) ytmp = yscale;
		if( ytmp < -yscale ) ytmp = -yscale;
		pDC->LineTo(x1 + (i+1) * xstep, y1 + ytmp);
	}
	pDC->SelectObject(pOldPen);
	myPen.DeleteObject();

	myPen.CreatePen(PS_SOLID, 1, RGB(0,255,0));
	pOldPen = pDC->SelectObject(&myPen);

	for(i = 0; i < dotn-1; i++) {
		ytmp = (int)(-yscale * iW2[i+0] / yrng);
		if( ytmp > yscale ) ytmp = yscale;
		if( ytmp < -yscale ) ytmp = -yscale;
		pDC->MoveTo(x1 + (i+0) * xstep, y1 + ytmp);
		ytmp = (int)(-yscale * iW2[i+1] / yrng);
		if( ytmp > yscale ) ytmp = yscale;
		if( ytmp < -yscale ) ytmp = -yscale;
		pDC->LineTo(x1 + (i+1) * xstep, y1 + ytmp);
	}
	pDC->SelectObject(pOldPen);
	myPen.DeleteObject();
}

// FFT�����s����֐�
void CFftFloatView::FftCal(double *iW, double *tW, double *oR, double *oI, double *oP)
{
	int N = 1024; // 1024�|�C���gFFT
	int P; 
	int N_2 = N/2;
	int i,j,k,kp,m,h;
	// �ϐ��͕��������_
	double w1, w2;
	double t1,t2,s1,s2;
	double tri[1024];
	double fReal[1024], fImag[1024];

	// 2^P=N, N��1024�̂Ƃ�P��10
	i = N; P = 0;
	while (i != 1) {
		i = i / 2;
		P++;
	}

	// �������ɂ͎��Ԏ��g�`������B�������̓[���Ŗ��߂�B
	for (i = 0; i < N; i++) {
		fReal[i] = iW[i]; fImag[i] = 0.0;
	}

	// �O�p�֐��̑��
	for ( i = 0; i < N; i++ ) {
		tri[i] = tW[i];
	}

	// �r�b�g�t���\�[�g
	j = 0;
	for ( i = 0; i <= N-2; i++ ) {
		if (i < j) {
			t1 = fReal[j]; fReal[j] = fReal[i]; fReal[i] = t1;
			t2 = fImag[j]; fImag[j] = fImag[i]; fImag[i] = t2;
		}
		k = N_2;
		while (k <= j) {
			j = j - k; k = k/2;
		}
		j = j + k;
	}

	// �o�^�t���C���Z
	for ( i = 1; i <= P; i++ ) {
		m = (int)(pow(2.0, double(i)));
		h = m/2;
		for ( j = 0; j < h; j++ ) {
			w1 = tri[j*(N/m)];
			w2 = tri[j*(N/m) + N_2];
			for( k = j; k < N; k+=m ) {
				kp = k + h;
				s1 = fReal[kp] * w1 - fImag[kp] * w2;
				s2 = fReal[kp] * w2 + fImag[kp] * w1;
				t1 = fReal[k] + s1; fReal[kp] = fReal[k] - s1; fReal[k] = t1;
				t2 = fImag[k] + s2; fImag[kp] = fImag[k] - s2; fImag[k] = t2;
			}
		}
	}

	// �������A�������A�p���[�X�y�N�g����Ԃ�
	for ( i = 0; i < N; i++ ) {
		oR[i] = fReal[i];
		oI[i] = fImag[i];
		oP[i] = fReal[i] * fReal[i] + fImag[i] * fImag[i];
	}
}

void CFftFloatView::OnFftLoad()
{
	TxtLoad("FloatingIn.txt", InWave);
	TxtLoad("FloatingTri.txt", TriData);
	InputLoaded = TRUE;
	FftExecuted = FALSE;
	InvalidateRect(NULL, TRUE);		
}

void CFftFloatView::OnFftExec()
{
	FftCal(InWave, TriData, RealSpec, ImagSpec, PwrSpec);
	FftExecuted = TRUE;
	InvalidateRect(NULL, TRUE);		
}

void CFftFloatView::OnViewX10()
{
	ViewX10 = !ViewX10;
	InvalidateRect(NULL, TRUE);		
}

void CFftFloatView::OnUpdateViewX10(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(ViewX10);
}
