
// LFBToolDlg.h : ͷ�ļ�
//

#pragma once
#include <vector>
using namespace std;
// CLFBToolDlg �Ի���
class CLFBToolDlg : public CDialogEx
{
// ����
public:
	CLFBToolDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_LFBTOOL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

public:
	CString strPath;
	int iCurLine;
	vector<LONGLONG> g_iIndexList;
	void InitDlgList();
	void ReadForLine();
// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CListCtrl m_sList;
	afx_msg void OnBnClickedLeft();
	afx_msg void OnBnClickedRight();
};
