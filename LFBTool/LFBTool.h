
// LFBTool.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CLFBToolApp:
// �йش����ʵ�֣������ LFBTool.cpp
//

class CLFBToolApp : public CWinApp
{
public:
	CLFBToolApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CLFBToolApp theApp;