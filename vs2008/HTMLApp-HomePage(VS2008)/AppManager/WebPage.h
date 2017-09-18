// WebPage.h: interface for the CWebPage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WEBPAGE_H__AEBD50B8_EE66_40AB_8B92_C4EECB9BCD22__INCLUDED_)
#define AFX_WEBPAGE_H__AEBD50B8_EE66_40AB_8B92_C4EECB9BCD22__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <atlbase.h>
#include <Mshtml.h>

class CWebPage  
{
public:
	CWebPage();
	virtual ~CWebPage();

	bool SetDocument(IDispatch* pDisp);
	LPDISPATCH GetHtmlDocument() const;
	const CString GetLastError() const;
	bool GetJScript(CComPtr<IDispatch>& spDisp);
	bool GetJScripts(CComPtr<IHTMLElementCollection>& spColl);

	CString ScanJScript(CString& strAText, CStringArray& args);

	bool CallJScript(const CString strFunc,CComVariant* pVarResult = NULL);
	bool CallJScript(const CString strFunc,const CString strArg1,CComVariant* pVarResult = NULL);
	bool CallJScript(const CString strFunc,const CString strArg1,const CString strArg2,CComVariant* pVarResult = NULL);
	bool CallJScript(const CString strFunc,const CString strArg1,const CString strArg2,const CString strArg3,CComVariant* pVarResult = NULL);
	bool CallJScript(const CString strFunc,const CStringArray& paramArray,CComVariant* pVarResult = NULL);    

    // HTML 요소 찾기
    BOOL FindElement(LPCTSTR tszElem,UINT uIndex);

    // Item에 HTML 쓰기
    BOOL    WriteElement(LPCTSTR HTMLText);
	CString ReadElement();

	// Input Element
    BOOL    WriteInputElement(LPCTSTR HTMLText);
	CString ReadInputElement();
    

    CString ReadTextElement();
    BOOL    WriteTextElement(LPCTSTR HTMLText);


protected:


	void ShowError(LPCSTR lpszText);

protected:

	CComPtr<IHTMLDocument2>	m_spDoc;
    CComQIPtr<IHTMLElement> m_pElem;
    
	CString	m_strError;

};

inline
void CWebPage::ShowError(LPCSTR lpszText)
{
	m_strError = "JSCall Error:\n" + CString(lpszText);
}
inline 
const CString CWebPage::GetLastError() const
{
	return m_strError;
}
inline
LPDISPATCH CWebPage::GetHtmlDocument() const
{
	return m_spDoc;
}

CString GetNextToken(CString& strSrc, const CString strDelim,bool bTrim = false, bool bFindOneOf = true);

#endif // !defined(AFX_WEBPAGE_H__AEBD50B8_EE66_40AB_8B92_C4EECB9BCD22__INCLUDED_)
