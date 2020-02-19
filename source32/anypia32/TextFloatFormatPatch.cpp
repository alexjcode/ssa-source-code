// $Id: TextFloatFormatPatch.cpp 1.1 2017/12/12 08:20:05EST 277133 Development  $
//
// Reimplementation of AfxTextFloatFormat because of buggy _sntscanf_s function
//
// See:
// - https://social.msdn.microsoft.com/Forums/vstudio/en-US/4a04b861-8b16-4bb3-8a0d-f4e78b1c2a5a/sntscanfs-doesnt-work-as-expected-in-vs2015?forum=vcgeneral
// - https://connect.microsoft.com/VisualStudio/feedback/details/1773279/bug-in-sntscanf-s
// - https://connect.microsoft.com/VisualStudio/feedback/details/1642606/mfc-cdialog-dodataexchange-cdataexchange-pdx-fails-when-value-is-zero
// - https://stackoverflow.com/questions/44059775/visual-c-2017-bug-mfc-ddx-text-for-double

#include "stdafx.h"
#include "TextFloatFormatPatch.h"
#include "afxpriv.h"
#include <float.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


// Copied from MFC source code

void AFXAPI AfxTextFloatFormat2(CDataExchange* pDX, int nIDC,
	void* pData, double value, int nSizeGcvt)
{
	ASSERT(pData != NULL);

	pDX->PrepareEditCtrl(nIDC);
	HWND hWndCtrl;
	pDX->m_pDlgWnd->GetDlgItem(nIDC, &hWndCtrl);
	
	const int TEXT_BUFFER_SIZE = 400;
	TCHAR szBuffer[TEXT_BUFFER_SIZE] = { 0 };          
	if (pDX->m_bSaveAndValidate)
	{
		::GetWindowText(hWndCtrl, szBuffer, _countof(szBuffer));
		double d;
		if (_sntscanf_s(szBuffer, _countof(szBuffer), _T("%lf"), &d) != 1)
		{
			AfxMessageBox(AFX_IDP_PARSE_REAL);
			pDX->Fail();            // throws exception
		}
		if (nSizeGcvt == FLT_DIG)
			*((float*)pData) = (float)d;
		else
			*((double*)pData) = d;
	}
	else
	{
		ATL_CRT_ERRORCHECK_SPRINTF(_sntprintf_s(szBuffer, _countof(szBuffer), _countof(szBuffer) -1, _T("%.*g"), nSizeGcvt, value));
		AfxSetWindowText(hWndCtrl, szBuffer);
	}
}


void AFXAPI DDX_Text2(CDataExchange* pDX, int nIDC, float& value)
{
    AfxTextFloatFormat2(pDX, nIDC, &value, value, FLT_DIG);
}


void AFXAPI DDX_Text2(CDataExchange* pDX, int nIDC, double& value)
{
    AfxTextFloatFormat2(pDX, nIDC, &value, value, DBL_DIG);
}