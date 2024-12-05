// EditorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MathEdit.h"
#include "EditorDlg.h"
#include "About.h"


/////////////////////////////////////////////////////////////////////////////
// CEditorDlg dialog


CEditorDlg::CEditorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEditorDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEditorDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}


void CEditorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEditorDlg)
	DDX_Control(pDX, IDC_FONTSIZE_LIST, m_FontSizeList);
	DDX_Control(pDX, IDC_EDITOR, m_Editor); 
	DDX_Control(pDX, IDC_EQUATION,		m_btnEquation);
	DDX_Control(pDX, IDC_BRACE,			m_btnBrace);
	DDX_Control(pDX, IDC_UPPER_GREEK,	m_btnUpperGreek);
	DDX_Control(pDX, IDC_LOWER_GREEK,	m_btnLowerGreek);
	DDX_Control(pDX, IDC_SUM,			m_btnSum);
	DDX_Control(pDX, IDC_PROD,			m_btnProd);
	DDX_Control(pDX, IDC_INTEGRAL,		m_btnIntegral);
	DDX_Control(pDX, IDC_DERIVATIVE,	m_btnDerivative);
	DDX_Control(pDX, IDC_MATRIX,		m_btnMatrix);
	DDX_Control(pDX, IDC_PBYQ,			m_btnPbyq);
	DDX_Control(pDX, IDC_FUNCTION,		m_btnFunction);
	DDX_Control(pDX, IDC_COREDATA,		m_btnCoreData);
	DDX_Control(pDX, IDC_VECTOR,		m_btnVector);
	DDX_Control(pDX, IDC_ARROWS,		m_btnArrows);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEditorDlg, CDialog)
	//{{AFX_MSG_MAP(CEditorDlg)
	ON_MESSAGE(CS_SELECTED, ToolBarCtrlSelected)
	ON_CBN_SELCHANGE(IDC_FONTSIZE_LIST, OnSelchangeFontsizeList)
	ON_BN_CLICKED(IDC_UNDO, OnUndo)
	ON_BN_CLICKED(IDC_REDO, OnRedo)
	ON_BN_CLICKED(IDC_PARSER, OnParser)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_SAVE_FILE, OnSaveFile)
	ON_BN_CLICKED(IDC_OPEN_FILE, OnOpenFile)
	ON_BN_CLICKED(IDC_COPY_IMAGE, OnCopyImage)
	ON_BN_CLICKED(IDC_COPY_MATHML, OnCopyMathml)
	ON_BN_CLICKED(IDC_CREDIT, OnCredit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditorDlg message handlers

BOOL CEditorDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// TODO: Add extra initialization here
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);

	//Initialize Entities Tables
	//InitEntityList();
	InitToolbarEntity();
	m_btnEquation.InitButton	(3, IDB_EQUATION,		21, RGB(255,255,255));
	m_btnBrace.InitButton		(4, IDB_BRACES,			21, RGB(255,255,255));
	m_btnUpperGreek.InitButton	(4, IDB_UPPER_GREEK,	21, RGB(255,255,255));
	m_btnLowerGreek.InitButton	(4, IDB_LOWER_GREEK,	21, RGB(255,255,255));
	m_btnSum.InitButton			(4, IDB_SUM,			21, RGB(255,255,255));
	m_btnProd.InitButton		(3, IDB_DOTSYMB,		21, RGB(255,255,255));
	m_btnIntegral.InitButton	(4, IDB_INTEGRALS,		21, RGB(255,255,255));
	m_btnDerivative.InitButton	(2, IDB_MORESYMBOL,		21, RGB(255,255,255));
	m_btnMatrix.InitButton		(3, IDB_MATRIX,			21, RGB(255,255,255));
	m_btnPbyq.InitButton		(3, IDB_FRS,			21, RGB(255,255,255));
	m_btnFunction.InitButton	(4, IDB_FUNCTION,		32, RGB(255,255,255));
	m_btnCoreData.InitButton	(4, IDB_SPECIALCHARS,	21, RGB(255,255,255));
	m_btnVector.InitButton		(3, IDB_VECTOR,			21, RGB(255,255,255));
	m_btnArrows.InitButton		(3, IDB_ARROWS,			21, RGB(255,255,255));

		// Create the ToolTip control.
	m_tooltip.Create(this);
	m_tooltip.Activate(TRUE);

	// Add the tools
	//m_tooltip.AddTool(GetDlgItem(IDC_BUTTON_UNDO), _T("Undo"));
	//m_tooltip.AddTool(GetDlgItem(IDC_BUTTON_REDO), _T("Redo"));

	m_tooltip.AddTool(GetDlgItem(IDC_EQUATION),		_T("Special Operators"));
	m_tooltip.AddTool(GetDlgItem(IDC_BRACE),		_T("Braces"));
	m_tooltip.AddTool(GetDlgItem(IDC_UPPER_GREEK),	_T("Upper Greek"));
	m_tooltip.AddTool(GetDlgItem(IDC_LOWER_GREEK),	_T("Lower Greek"));
	m_tooltip.AddTool(GetDlgItem(IDC_SUM),			_T("Sums, Producs, Unions, Intersections"));
	m_tooltip.AddTool(GetDlgItem(IDC_PROD),			_T("Dot symbols"));
	m_tooltip.AddTool(GetDlgItem(IDC_INTEGRAL),		_T("Integrals"));
	m_tooltip.AddTool(GetDlgItem(IDC_DERIVATIVE),	_T("More symbols"));
	m_tooltip.AddTool(GetDlgItem(IDC_MATRIX),		_T("Matrices"));
	m_tooltip.AddTool(GetDlgItem(IDC_PBYQ),			_T("Common equations"));
	m_tooltip.AddTool(GetDlgItem(IDC_FUNCTION),		_T("Functions"));
	m_tooltip.AddTool(GetDlgItem(IDC_COREDATA),		_T("Special Chars"));
	m_tooltip.AddTool(GetDlgItem(IDC_VECTOR),		_T("Vector, Over, Angle, Arc"));
	m_tooltip.AddTool(GetDlgItem(IDC_ARROWS),		_T("Arrows"));
	CString st;
	for (int i=8; i<=72; i++){
		st.Format(_T("%d"),i);
		m_FontSizeList.AddString(st);
	}
	m_FontSizeList.SetCurSel(4);
	m_Editor.EnableScrollBars(SB_BOTH);
	m_Editor.SetFocus();
	m_Editor.Invalidate(TRUE);

	CEdit* pEdit=(CEdit*)GetDlgItem(IDC_FORMULA_TEXT);
	pEdit->SetWindowText(_T("x_12=(-b+-sqrt(b^2-4ac))/2a"));

	CButton* pButton=(CButton*)GetDlgItem(IDC_COPY_MATHML);
	pButton->SetCheck(TRUE);
	pButton=(CButton*)GetDlgItem(IDC_COPY_IMAGE);
	pButton->SetCheck(TRUE);
	return FALSE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


BOOL CEditorDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	m_tooltip.RelayEvent(pMsg);
	UpdateDialogControls( this, FALSE );
	return CDialog::PreTranslateMessage(pMsg);
}

LRESULT CEditorDlg::ToolBarCtrlSelected(WPARAM wParam , LPARAM lParam)
{
	CString strType;
	int more;
	CString id;
	if(wParam==-1)
		return 0L;

	switch (lParam)
	{
	case IDC_EQUATION: // from Toolbar Equations
		/*
		if (wParam<20)
			m_Editor.InsertElement("EQU",wParam);
		break;
		*/
		if (wParam<m_StdOp.GetSize() && m_StdOp[wParam]!=_T(""))
			m_Editor.InsertSpecialElement(m_StdOp[wParam]);
		break;
	case IDC_BRACE: // form toolbar Braces
		m_Editor.InsertElement(_T("Brace"),wParam);
		break;
	case IDC_COREDATA: // form toolbar Core Data
		if (wParam<m_GeoOp.GetSize() && m_GeoOp[wParam]!= _T(""))
			m_Editor.InsertSpecialElement(m_GeoOp[wParam]);
		break;
	case IDC_SUM: // form toolbar Sum
		m_Editor.InsertElement(_T("SUM"), wParam);
		break;

	case IDC_PROD: // form toolbar Prod (same behaviour as sum)
		if (wParam<m_DotOp.GetSize() && m_DotOp[wParam]!= _T(""))
			m_Editor.InsertSpecialElement(m_DotOp[wParam]);
		break;

	case IDC_FUNCTION: // form toolbar Function
		switch (wParam){
			case 0:
				id=_T("sin");
				more=0;
				break;
			case 1:
				id=_T("cos");
				more=0;
				break;
			case 2:
				id=_T("tan");
				more=0;
				break;
			case 3:
				id=_T("cot");
				more=0;
				break;
			case 4:
				id=_T("sin");
				more=1;
				break;
			case 5:
				id=_T("cos");
				more=1;
				break;
			case 6:
				id=_T("tan");
				more=1;
				break;
			case 7:
				id=_T("cot");
				more=1;
				break;
			case 8:
				id=_T("sinh");
				more=0;
				break;
			case 9:
				id=_T("cosh");
				more=0;
				break;
			case 10:
				id=_T("tanh");
				more=0;
				break;
			case 11:
				id=_T("coth");
				more=0;
				break;
			case 12:
				id=_T("sinh");
				more=1;
				break;
			case 13:
				id=_T("cosh");
				more=1;
				break;
			case 14:
				id=_T("tanh");
				more=1;
				break;
			case 15:
				id=_T("coth");
				more=1;
				break;
			case 16:
				id=_T("exp");
				more=0;
				break;
			case 17:
				id=_T("ln");
				more=0;
				break;
			case 18:
				id=_T("ln");
				more=2;
				break;
			case 19:
				id=_T("log");
				more=2;
				break;
			case 21:
				id=_T("lim");
				more=3;
				break;
			}
		m_Editor.InsertFuncOperator(id, more);
		break;

	case IDC_INTEGRAL: // form toolbar Integral
		m_Editor.InsertElement(_T("INT"),wParam);
		break;

	case IDC_DERIVATIVE: // form toolbar derivative
		if (wParam<m_MoreSym.GetSize() && m_MoreSym[wParam]!= _T(""))
			m_Editor.InsertSpecialElement(m_MoreSym[wParam]);
		break;

	case IDC_PBYQ: // form toolbar Operators
		if(wParam== 0)
			m_Editor.InsertElement(_T("MFrac"));
		if(wParam== 1 || wParam==2)
			m_Editor.InsertElement(_T("MRoot"),wParam);
		if (wParam==3)
			m_Editor.InsertElement(_T("MSup"));
		if (wParam==4)
			m_Editor.InsertElement(_T("MSub"));
		if (wParam==5)
			m_Editor.InsertElement(_T("MSubSup"));
		if (wParam>5)
			m_Editor.InsertElement(_T("MUnderOver"), wParam);
		break;
	case IDC_MATRIX: // form toolbar matrix
		m_Editor.InsertElement(_T("MTable"),wParam);
		break;
	case IDC_VECTOR: // form toolbar vector
		//if (wParam<2)
		m_Editor.InsertElement(_T("MOver"),wParam);
		break;
	case IDC_ARROWS: // form toolbar arrows
		if (wParam<m_ArrOp.GetSize() && m_ArrOp[wParam]!= _T(""))
			m_Editor.InsertSpecialElement(m_ArrOp[wParam]);
		break;
	case IDC_UPPER_GREEK: // form toolbar upper greek
		if (wParam<m_UpperGreek.GetSize() && m_UpperGreek[wParam]!= _T(""))
			m_Editor.InsertSpecialElement(m_UpperGreek[wParam]);
		break;
	case IDC_LOWER_GREEK: // form toolbar lower greek (same behaviour as upper greek)
		if (wParam<m_LowerGreek.GetSize() && m_LowerGreek[wParam]!= _T(""))
			m_Editor.InsertSpecialElement(m_LowerGreek[wParam]);
		break;
	default:
		break;
	}
	m_Editor.SetFocus();
    return 1L;
}

BOOL CEditorDlg::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	m_Editor.DestroyMath();
	m_LowerGreek.RemoveAll();
	m_UpperGreek.RemoveAll();
	m_StdOp.RemoveAll();
	m_GeoOp.RemoveAll();
	m_ArrOp.RemoveAll();
	return CDialog::DestroyWindow();
}



void CEditorDlg::OnSelchangeFontsizeList() 
{
	// TODO: Add your control notification handler code here
	//return;
	int k=m_FontSizeList.GetCurSel()+8;
	m_Editor.SetBaseFontSize(k);
}

void CEditorDlg::OnUndo() 
{
	// TODO: Add your control notification handler code here
	//m_Editor.ScaleUp();
}

void CEditorDlg::OnRedo() 
{
	// TODO: Add your control notification handler code here
//	m_Editor.Redo();
//	m_Editor.SetFocus();
}

void CEditorDlg::OnParser() 
{
	// TODO: Add your control notification handler code here
	CEdit* pEdit=(CEdit*)GetDlgItem(IDC_FORMULA_TEXT);
	CString st;
	pEdit->GetWindowText(st);
	st.TrimLeft();
	st.TrimRight();
	if (st== _T("")) return;
	m_Editor.SetFormulaText(st);
	m_Editor.ParseFormula();
	m_Editor.SetFocus();
}

void CEditorDlg::OnOK() 
{
	// TODO: Add extra validation here
	
	return;
}

void CEditorDlg::InitEntityList()
{
	TCHAR path[MAX_PATH];
	GetModuleFileName(NULL,path, MAX_PATH);
	CString st(path);
	CStringArray tokens;
	int i, k, j;
	TCHAR ch;
	k=st.ReverseFind(_T('\\'));
	st=st.Left(k+1);
	st=st + _T("Entity.txt");
	CStdioFile file;
	tokens.SetSize(7);
	if (!file.Open(st,CFile::modeRead)){
		AfxMessageBox(_T("Could not open entity list file"));
		CDialog::OnCancel();
		return;
	}
	while (true){
		if (!file.ReadString(st))
			break;
		if (st==_T(""))
			break;
		if (st[st.GetLength()-1]!=_T('\t'))
			st=st+_T("\t");
		i=0;
		for (j=0; j<7; j++){
			k=i;
			do{
				ch=st[k];
				k=k+1;
				if (k==st.GetLength())
					break;
			} while (ch!=_T('\t')); 
			tokens[j]=st.Mid(i,k-i-1);
			//TRACE(st.Mid(i,k-i-1)+"\n");
			i=k;
		}
		m_Editor.AddMathEntity(tokens[0], tokens[2], tokens[4], tokens[5], (BOOL)_ttoi(tokens[6]), (BOOL)_ttoi(tokens[1]), HexToInt(tokens[3]));
	}
}

void CEditorDlg::InitToolbarEntity()
{
	m_LowerGreek.SetSize(28);
	m_LowerGreek[0]=_T("alpha");
	m_LowerGreek[1]=_T("beta");
	m_LowerGreek[2]=_T("chi");
	m_LowerGreek[3]=_T("delta");
	m_LowerGreek[4]=_T("epsi");
	m_LowerGreek[5]=_T("phi");
	m_LowerGreek[6]=_T("phiv");
	m_LowerGreek[7]=_T("gamma");
	m_LowerGreek[8]=_T("eta");
	m_LowerGreek[9]=_T("iota");
	m_LowerGreek[10]=_T("kappa");
	m_LowerGreek[11]=_T("lambda");
	m_LowerGreek[12]=_T("mu");
	m_LowerGreek[13]=_T("nu");
	m_LowerGreek[14]=_T("omicron");
	m_LowerGreek[15]=_T("pi");
	m_LowerGreek[16]=_T("theta");
	m_LowerGreek[17]=_T("rho");
	m_LowerGreek[18]=_T("sigma");
	m_LowerGreek[19]=_T("tau");
	m_LowerGreek[20]=_T("upsi");
	m_LowerGreek[21]=_T("piv");
	m_LowerGreek[22]=_T("omega");
	m_LowerGreek[23]=_T("xi");
	m_LowerGreek[24]=_T("psi");
	m_LowerGreek[25]=_T("zeta");
	m_LowerGreek[26]=_T("part");
	m_LowerGreek[27]=_T("");

	m_UpperGreek.SetSize(26);
	m_UpperGreek[0]=_T("Alpha");
	m_UpperGreek[1]=_T("Beta");
	m_UpperGreek[2]=_T("Chi");
	m_UpperGreek[3]=_T("Delta");
	m_UpperGreek[4]=_T("Epsi");
	m_UpperGreek[5]=_T("Phi");
	m_UpperGreek[6]=_T("Gamma");
	m_UpperGreek[7]=_T("Eta");
	m_UpperGreek[8]=_T("Iota");
	m_UpperGreek[9]=_T("thetav");
	m_UpperGreek[10]=_T("Kappa");
	m_UpperGreek[11]=_T("Lamda");
	m_UpperGreek[12]=_T("Mu");
	m_UpperGreek[13]=_T("Nu");
	m_UpperGreek[14]=_T("Omicron");
	m_UpperGreek[15]=_T("Pi");
	m_UpperGreek[16]=_T("Theta");
	m_UpperGreek[17]=_T("Rho");
	m_UpperGreek[18]=_T("Sigma");
	m_UpperGreek[19]=_T("Tau");
	m_UpperGreek[20]=_T("Upsilon");
	m_UpperGreek[21]=_T("sigmav");
	m_UpperGreek[22]=_T("Omega");
	m_UpperGreek[23]=_T("Xi");
	m_UpperGreek[24]=_T("Psi");
	m_UpperGreek[25]=_T("Zeta");

	m_StdOp.SetSize(20);
	m_StdOp[0]=_T("plusmn");
	m_StdOp[1]=_T("mnplus");
	m_StdOp[2]=_T("divide");
	m_StdOp[3]=_T("le");
	m_StdOp[4]=_T("ge");
	m_StdOp[5]=_T("ne");
	m_StdOp[6]=_T("equiv");
	m_StdOp[7]=_T("ap");
	m_StdOp[8]=_T("cong");
	m_StdOp[9]=_T("cap");
	m_StdOp[10]=_T("cup");
	m_StdOp[11]=_T("sup");
	m_StdOp[12]=_T("supE");
	m_StdOp[13]=_T("nsub");
	m_StdOp[14]=_T("sub");
	m_StdOp[15]=_T("subE");
	m_StdOp[16]=_T("isin");
	m_StdOp[17]=_T("notin");
	m_StdOp[18]=_T("exist");
	m_StdOp[19]=_T("forall");

	m_GeoOp.SetSize(12);
	m_GeoOp[0]=_T("infin");
	m_GeoOp[1]=_T("esim");
	m_GeoOp[2]=_T("sime");
	m_GeoOp[3]=_T("wreath");
	m_GeoOp[4]=_T("ang");
	m_GeoOp[5]=_T("angmsd");
	m_GeoOp[6]=_T("angsph");
	m_GeoOp[7]=_T("par");
	m_GeoOp[8]=_T("vangrt");
	m_GeoOp[9]=_T("lrtri");
	m_GeoOp[10]=_T("xutri");
	m_GeoOp[11]=_T("bottom");

	m_ArrOp.SetSize(12);
	m_ArrOp[0]=_T("rarr");
	m_ArrOp[1]=_T("larr");
	m_ArrOp[2]=_T("harr");
	m_ArrOp[3]=_T("uarr");
	m_ArrOp[4]=_T("darr");
	m_ArrOp[5]=_T("varr");
	m_ArrOp[6]=_T("rArr");
	m_ArrOp[7]=_T("lArr");
	m_ArrOp[8]=_T("hArr");
	m_ArrOp[9]=_T("uArr");
	m_ArrOp[10]=_T("dArr");
	m_ArrOp[11]=_T("vArr");

	m_DotOp.SetSize(12);
	m_DotOp[0]=_T("there4");
	m_DotOp[1]=_T("becaus");
	m_DotOp[2]=_T("ratio");
	m_DotOp[3]=_T("Colon");
	m_DotOp[4]=_T("minusd");
	m_DotOp[5]=_T("mDot");
	m_DotOp[6]=_T("mDDot");
	m_DotOp[7]=_T("homtht");
	m_DotOp[8]=_T("esdot");
	m_DotOp[9]=_T("eDot");
	m_DotOp[10]=_T("efDot");
	m_DotOp[11]=_T("erDot");

	m_MoreSym.SetSize(8);
	m_MoreSym[0]=_T("not");
	m_MoreSym[1]=_T("emptyv");
	m_MoreSym[2]=_T("oplus");
	m_MoreSym[3]=_T("ominus");
	m_MoreSym[4]=_T("odot");
	m_MoreSym[5]=_T("real");
	m_MoreSym[6]=_T("image");
	m_MoreSym[7]=_T("aleph");
}

int CEditorDlg::HexToInt(CString st)
{
	TCHAR ch1, ch2;
	int d1, d2;
	st=st.Right(2);
	st.MakeUpper();
	ch1=st[0];
	ch2=st[1];
	if (ch1>='A')
		d1=10+ch1-'A';
	else
		d1=ch1-'0';

	if (ch2>='A')
		d2=10+ch2-'A';
	else
		d2=ch2-'0';
	return d1*16+d2;
}

void CEditorDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

void CEditorDlg::OnSaveFile() 
{
	// TODO: Add your control notification handler code here
	static TCHAR BASED_CODE szFilter[] = _T("Math equation files (*.meq)|*.meq|MathML files (*.mml)|*.mml|Windows metafile (*.wmf)|*.wmf|");
	
	CFileDialog fdlg( FALSE, _T("meq"), _T(""), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT , szFilter, NULL );
				
	if (fdlg.DoModal() == IDOK)
	{
		CString strFile=fdlg.m_ofn.lpstrFile;
		CString ext=fdlg.GetFileExt();
		ext.MakeLower();
		if (ext==_T("wmf"))
			m_Editor.ExportToWMF(strFile);
		else if (ext==_T("meq"))
			m_Editor.SaveFile(strFile);
		else{
			CString st=m_Editor.GetMathML();
			CStdioFile ouFile;
			ouFile.Open(strFile, CFile::modeCreate | CFile::modeWrite);
			ouFile.WriteString(st);
			ouFile.Close();
		}
	}	
}

void CEditorDlg::OnOpenFile() 
{
	// TODO: Add your control notification handler code here
	static TCHAR BASED_CODE szFilter[] = _T("Math equation files (*.meq)|*.meq|");
	
	CFileDialog fdlg( TRUE, _T("meq"), _T(""), OFN_HIDEREADONLY | OFN_FILEMUSTEXIST , szFilter, NULL );
				
	if (fdlg.DoModal() == IDOK)
	{
		CString strFile=fdlg.m_ofn.lpstrFile;
		m_Editor.OpenFile(strFile);
	}	
}

void CEditorDlg::OnCopyImage() 
{
	// TODO: Add your control notification handler code here
	ResetCopyOptions();
}

void CEditorDlg::OnCopyMathml() 
{
	// TODO: Add your control notification handler code here
	ResetCopyOptions();
}

void CEditorDlg::ResetCopyOptions()
{
	CButton* pButton=(CButton*)GetDlgItem(IDC_COPY_MATHML);
	BOOL b1=pButton->GetCheck();
	pButton=(CButton*)GetDlgItem(IDC_COPY_IMAGE);
	BOOL b2=pButton->GetCheck();
	m_Editor.SetCopyOption(b1, b2);
}

void CEditorDlg::OnCredit() 
{
	// TODO: Add your control notification handler code here
	CAbout ab;
	ab.DoModal();
}
