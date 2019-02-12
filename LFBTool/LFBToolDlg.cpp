
// LFBToolDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "LFBTool.h"
#include "LFBToolDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#define BUFFLEN 33554432

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CLFBToolDlg �Ի���




CLFBToolDlg::CLFBToolDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLFBToolDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLFBToolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CONTEXT, m_sList);
}

BEGIN_MESSAGE_MAP(CLFBToolDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CLFBToolDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_LEFT, &CLFBToolDlg::OnBnClickedLeft)
	ON_BN_CLICKED(IDC_RIGHT, &CLFBToolDlg::OnBnClickedRight)
END_MESSAGE_MAP()


// CLFBToolDlg ��Ϣ�������

BOOL CLFBToolDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	ShowWindow(SW_MINIMIZE);

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	// ����ListCtrl�ķ����չ���
	DWORD dwStyle = m_sList.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;                                        //ѡ��ĳ��ʹ���и���(LVS_REPORT)
	dwStyle |= LVS_EX_GRIDLINES;                                            //������(LVS_REPORT)
	dwStyle |= LVS_EX_SUBITEMIMAGES;                                            //CheckBox
	m_sList.SetExtendedStyle(dwStyle); 

	// ��ListCtrl��������
	m_sList.InsertColumn( 0, _T("Context"), LVCFMT_LEFT, 1020);
	strPath = "E:\\VC";
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CLFBToolDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CLFBToolDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CLFBToolDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
int CALLBACK BwsCallbackProc(HWND hwnd,UINT uMsg,LPARAM lParam,LPARAM lpData)
{
	switch(uMsg)
	{
	case BFFM_INITIALIZED:
		::SendMessage(hwnd,BFFM_SETSELECTION,TRUE,lpData);
		break;
	}
	return 0;
}

/**************************************************************************
## Function: ReadForLine  for open one big file and get line index
## Author  :  water
## Date    :  2019-01-25
**************************************************************************/
void CLFBToolDlg::ReadForLine()
{
	LONGLONG x_iFileLength = 0;
	LONGLONG x_ipos = 0;
	 HANDLE hFile = CreateFile(strPath, GENERIC_READ | GENERIC_WRITE,0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	// �õ��ļ��ߴ�
	DWORD dwFileSizeHigh;
	__int64 qwFileSize = GetFileSize(hFile, &dwFileSizeHigh);
	qwFileSize |= (((__int64)dwFileSizeHigh) << 32);
	__int64 qwFileSizeEx = qwFileSize;
	x_iFileLength = qwFileSizeEx;
	CloseHandle(hFile);
	char* x_Buff = new char[BUFFLEN];
	FILE* f = NULL;
	if ((f = fopen(strPath,"r")) == NULL)
	{
		printf("open fail errno = %d\n", errno);
		return;
	}
	fseek(f,0,0);
	while (1)
	{
		if (x_ipos + BUFFLEN < x_iFileLength)
		{
			fread(x_Buff,BUFFLEN,1,f);
			for (int i = 0; i < BUFFLEN; ++i)
			{
				if (x_Buff[i] == '\n')
				{
					g_iIndexList.push_back(x_ipos + i + 1);
				}
			}
		}else{
			int ilength = x_iFileLength - x_ipos;
			LONGLONG iLast = 0;
			fread(x_Buff,ilength,1,f);
			for (int i = 0;i < ilength; ++i)
			{
				if (x_Buff[i] == '\n')
				{
					iLast = x_ipos + i + 1;
					g_iIndexList.push_back(iLast);
				}
			}
			if (iLast != x_iFileLength)
			{
				g_iIndexList.push_back(x_iFileLength);
			}
			break;
		}
		x_ipos += BUFFLEN;
	}
	delete [] x_Buff;
	fclose(f);
}
/**************************************************************************
## Function: InitDlgList  for open one big file and get line context
## Author  :  water
## Date    :  2019-01-25
**************************************************************************/
void CLFBToolDlg::InitDlgList()
{
	CStdioFile g_file;
	CFileException ex;
	g_file.Open(strPath,CFile::modeRead,&ex);
	CString str("");
	str.Format("%d",GetLastError());
	MessageBox(str);
	if (0 == iCurLine)
	{
		g_file.Seek(0,SEEK_SET);
	}else{
		if (iCurLine - 1 < 0)
		{
			iCurLine = 0;
		}
		LONG x = g_iIndexList[iCurLine - 1];
		g_file.Seek(x,CFile::begin);
	}
	CString strtemp("");
	int iTotalLine = g_iIndexList.size();
	for (int i = 0; i < 1000; ++i)
	{
		if (i + iCurLine < iTotalLine)
		{
			g_file.ReadString(strtemp);
			LV_ITEM lvitem;
			memset ((char *) &lvitem, '\0', sizeof (LV_ITEM));
			lvitem.mask = LVIF_TEXT  | LVIF_STATE;
			//lvitem.iItem = i;
			lvitem.iSubItem = 0;
			lvitem.stateMask = 0;
			lvitem.iItem =i;
			lvitem.pszText = (LPSTR)(LPCTSTR)strtemp;
			m_sList.InsertItem (&lvitem);
		}else{
			break;
		}
	}
	g_file.Close();
	strtemp.Format("Total Line: %d",iTotalLine);
	SetDlgItemText(IDC_TOTALSTATIC,strtemp);
	strtemp.Format("Cur Line: %d - %d",iCurLine + 1,iCurLine + 1000);
	SetDlgItemText(IDC_CURSTATIC,strtemp);
}
/**************************************************************************
## Function: OnBnClickedOk  for open one big file
## Author  :  water
## Date    :  2019-01-24
**************************************************************************/
void CLFBToolDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//CDialogEx::OnOK();
	m_sList.DeleteAllItems();
	//�򿪶Ի���
	static CString szFilter="Text Files (*.txt)|*.txt|Excel csv(*.csv)|*.csv|All Files (*.*)|*.*||";
	char x_sBuf[256] = {NULL};
	CString x_strPath(x_sBuf);
	x_strPath.Trim();
	CFileDialog dlg(true,"Open","",OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,szFilter,this);
	dlg.m_ofn.lpstrInitialDir = strPath;
	if(dlg.DoModal()==IDOK)
	{
		strPath=dlg.GetPathName();//����ļ�·��

		SetDlgItemText(IDC_PATH,strPath);

	}else{
		return;
	}
	//deal with data
	g_iIndexList.clear();
	//ReadForLine();//slowly==>bug--file length wrong
	//ReadForLineEx();//5 minutes ==>10G
	MapReadForLineEx();
	iCurLine = 0;
	InitDlgList();
	int iTotal = g_iIndexList.size();
	if (iTotal < iCurLine + 1000)
	{
		GetDlgItem(IDC_LEFT)->EnableWindow(FALSE);
		GetDlgItem(IDC_RIGHT)->EnableWindow(FALSE);
	}
}
/**************************************************************************
## Function: OnBnClickedLeft  for open the last 1000 lines of file
## Author  :  water
## Date    :  2019-01-24
**************************************************************************/
void CLFBToolDlg::OnBnClickedLeft()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GetDlgItem(IDC_LEFT)->EnableWindow(FALSE);
	GetDlgItem(IDC_RIGHT)->EnableWindow(FALSE);
	if (iCurLine - 1000 < 0)
	{
		iCurLine = 0;
	}else{
		iCurLine -= 1000;
	}

	m_sList.DeleteAllItems();
	InitDlgList();
	int iTotal = g_iIndexList.size();
	GetDlgItem(IDC_RIGHT)->EnableWindow(TRUE);
	if (0 == iCurLine)
	{
		GetDlgItem(IDC_LEFT)->EnableWindow(FALSE);
		if (iTotal < 1000)
		{
			GetDlgItem(IDC_RIGHT)->EnableWindow(FALSE);
		}
	}else{
		GetDlgItem(IDC_LEFT)->EnableWindow(TRUE);
	}
}
/**************************************************************************
## Function: OnBnClickedRight  for open the next 1000 lines of file
## Author  :  water
## Date    :  2019-01-24
**************************************************************************/
void CLFBToolDlg::OnBnClickedRight()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GetDlgItem(IDC_LEFT)->EnableWindow(FALSE);
	GetDlgItem(IDC_RIGHT)->EnableWindow(FALSE);
	iCurLine += 1000;

	m_sList.DeleteAllItems();
	InitDlgList();
	int iTotal = g_iIndexList.size();
	GetDlgItem(IDC_LEFT)->EnableWindow(TRUE);
	if (iTotal <= iCurLine + 1000)
	{
		GetDlgItem(IDC_RIGHT)->EnableWindow(FALSE);
	}else{
		GetDlgItem(IDC_RIGHT)->EnableWindow(TRUE);
	}
}
/**************************************************************************
## Function: ReadForLineEx  for open one big file and get line index
## Author  :  water
## Date    :  2019-01-28
**************************************************************************/
void CLFBToolDlg::ReadForLineEx()
{
	CFile g_xFile;
	CFileException ex;
	g_xFile.Open(strPath,CFile::modeRead,&ex);
	char* x_Buff = new char[BUFFLEN];
	LONGLONG x_iFileLength = 0;
	LONGLONG x_ipos = 0;
	
	x_iFileLength = g_xFile.GetLength();
	g_xFile.Seek(0,SEEK_CUR);
	while (1)
	{
		if (x_ipos + BUFFLEN < x_iFileLength)
		{
			g_xFile.Read(x_Buff,BUFFLEN);
			for (int i = 0; i < BUFFLEN; ++i)
			{
				if (x_Buff[i] == '\n')
				{
					g_iIndexList.push_back(x_ipos + i + 1);
				}
			}
		}else{
			int ilength = x_iFileLength - x_ipos;
			LONGLONG iLast = 0;
			g_xFile.Read(x_Buff,ilength);
			for (int i = 0;i < ilength; ++i)
			{
				if (x_Buff[i] == '\n')
				{
					iLast = x_ipos + i + 1;
					g_iIndexList.push_back(iLast);
				}
			}
			if (iLast != x_iFileLength)
			{
				g_iIndexList.push_back(x_iFileLength);
			}
			break;
		}
		x_ipos += BUFFLEN;
	}
	delete [] x_Buff;
	g_xFile.Close();
}
/**************************************************************************
## Function: ReadForLineEx  for open one big file and get line index
## Author  :  water
## Date    :  2019-01-28
**************************************************************************/
void CLFBToolDlg::MapReadForLineEx()
{
	LONGLONG iLast = 0;
	HANDLE hFile = CreateFile(strPath, GENERIC_READ|GENERIC_WRITE,0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	HANDLE hMapFile = CreateFileMapping(hFile, NULL, PAGE_READWRITE, 0, 0,NULL);
	// �õ�ϵͳ��������
	SYSTEM_INFO SysInfo;
	GetSystemInfo(&SysInfo);
	DWORD dwGran = SysInfo.dwAllocationGranularity;

	// �õ��ļ��ߴ�
	DWORD dwFileSizeHigh;
	__int64 qwFileSize = GetFileSize(hFile, &dwFileSizeHigh);
	qwFileSize |= (((__int64)dwFileSizeHigh) << 32);
	__int64 qwFileSizeEx = qwFileSize;
	// �ر��ļ�����
	CloseHandle(hFile);
	// ƫ�Ƶ�ַ 
	__int64 qwFileOffset = 0;
	// ���С
	DWORD dwBlockBytes = 10 * dwGran;
	if (qwFileSize < 10 * dwGran)
		dwBlockBytes = (DWORD)qwFileSize;
	while (1)
	{
		// ӳ����ͼ
		char* lpbMapAddress = (char*)MapViewOfFile(hMapFile,FILE_MAP_ALL_ACCESS,(DWORD)(qwFileOffset >> 32), (DWORD)(qwFileOffset & 0xFFFFFFFF),
				dwBlockBytes);
		if (lpbMapAddress == NULL)
		{
			CString str("");
			str.Format("Failure,err code:%d--%lld--%d",GetLastError(),qwFileOffset,dwBlockBytes);
			MessageBox(str);
			TRACE("ӳ���ļ�ӳ��ʧ��,�������:%d\r\n", GetLastError());
			CloseHandle(hMapFile);
			return;
		}
		// ��ӳ�����ͼ���з���
		for(DWORD i = 0; i < dwBlockBytes; ++i)
		{
			char* temp = (lpbMapAddress + i);
			if (*temp == '\n')
			{
				iLast = qwFileOffset + i + 1;
				g_iIndexList.push_back(iLast);
			}
			if (iLast == qwFileSizeEx)
			{
				break;
			}
		}
		// �����ļ�ӳ��
		UnmapViewOfFile(lpbMapAddress);
		// ��������
		qwFileOffset += dwBlockBytes;
		if (qwFileOffset + dwBlockBytes > qwFileSizeEx)
		{
			dwBlockBytes = qwFileSizeEx - qwFileOffset;
			if (0 == dwBlockBytes)
			{
				break;
			}
		}
		//qwFileSize -= dwBlockBytes;
	}
	if (iLast != qwFileSizeEx)
	{
		g_iIndexList.push_back(qwFileSizeEx);
	}
	
	CloseHandle(hMapFile);
	//CloseHandle(hFile);
}
