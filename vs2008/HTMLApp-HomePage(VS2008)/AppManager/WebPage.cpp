/////////////////////////////////////////////////////////////////
//             By Eugene Khodakovsky                           //
//                  April,2002                                 //
//             Eugene@cpplab.com                               //
//            Last Update: April, 2002                         //
/////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "WebPage.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


#define CHECK_POINTER(p)\
	ATLASSERT(p != NULL);\
	if(p == NULL)\
	{\
		ShowError("NULL pointer");\
		return false;\
	}

const CString GetSystemErrorMessage(DWORD dwError)
{
	CString strError;
	LPTSTR lpBuffer;

	if(!FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
			NULL,  dwError,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_SYS_DEFAULT),
			(LPTSTR) &lpBuffer, 0, NULL))

	{
		strError = "FormatMessage Netive Error" ;
	}
	else
	{
		strError = lpBuffer;
		LocalFree(lpBuffer);
	}
	return strError;
}

CString GetNextToken(CString& strSrc, const CString strDelim,bool bTrim, bool bFindOneOf)
{
	CString strToken;
	int idx = bFindOneOf? strSrc.FindOneOf(strDelim) : strSrc.Find(strDelim);
	if(idx != -1)
	{
		strToken  = strSrc.Left(idx);
		strSrc = strSrc.Right(strSrc.GetLength() - (idx + 1) );
	}
	else
	{
		strToken = strSrc;
		strSrc.Empty();
	}
	if(bTrim)
	{
		strToken.TrimLeft();
		strToken.TrimRight();
	}
	return strToken;
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWebPage::CWebPage()
{
}

CWebPage::~CWebPage()
{

}

bool CWebPage::SetDocument(IDispatch* pDisp)
{
	CHECK_POINTER(pDisp);

	m_spDoc = NULL;

	CComPtr<IDispatch> spDisp = pDisp;

	HRESULT hr = spDisp->QueryInterface(IID_IHTMLDocument2,(void**)&m_spDoc);
	if(FAILED(hr))
	{
		ShowError("Failed to get HTML document COM object");
		return false;
	}
	return true;
}

bool CWebPage::GetJScript(CComPtr<IDispatch>& spDisp)
{
	CHECK_POINTER(m_spDoc);
	HRESULT hr = m_spDoc->get_Script(&spDisp);
	ATLASSERT(SUCCEEDED(hr));
	return SUCCEEDED(hr);
}

bool CWebPage::GetJScripts(CComPtr<IHTMLElementCollection>& spColl)
{
	CHECK_POINTER(m_spDoc);
	HRESULT hr = m_spDoc->get_scripts(&spColl);
	ATLASSERT(SUCCEEDED(hr));
	return SUCCEEDED(hr);
}

bool CWebPage::CallJScript(const CString strFunc,CComVariant* pVarResult)
{
	CStringArray paramArray;
	return CallJScript(strFunc,paramArray,pVarResult);
}

bool CWebPage::CallJScript(const CString strFunc,const CString strArg1,CComVariant* pVarResult)
{
	CStringArray paramArray;
	paramArray.Add(strArg1);
	return CallJScript(strFunc,paramArray,pVarResult);
}

bool CWebPage::CallJScript(const CString strFunc,const CString strArg1,const CString strArg2,CComVariant* pVarResult)
{
	CStringArray paramArray;
	paramArray.Add(strArg1);
	paramArray.Add(strArg2);
	return CallJScript(strFunc,paramArray,pVarResult);
}

bool CWebPage::CallJScript(const CString strFunc,const CString strArg1,const CString strArg2,const CString strArg3,CComVariant* pVarResult)
{
	CStringArray paramArray;
	paramArray.Add(strArg1);
	paramArray.Add(strArg2);
	paramArray.Add(strArg3);
	return CallJScript(strFunc,paramArray,pVarResult);
}

bool CWebPage::CallJScript(const CString strFunc, const CStringArray& paramArray,CComVariant* pVarResult)
{
	
    CComPtr<IDispatch> spScript;
	if(!GetJScript(spScript))
	{
		ShowError("Cannot GetScript");
		return false;
	}
	CComBSTR bstrMember(strFunc);
	DISPID dispid = NULL;
	HRESULT hr = spScript->GetIDsOfNames(IID_NULL,&bstrMember,1,
											LOCALE_SYSTEM_DEFAULT,&dispid);
	if(FAILED(hr))
	{
		ShowError(GetSystemErrorMessage(hr));
		return false;
	}

	const int arraySize = paramArray.GetSize();

	DISPPARAMS dispparams;
	memset(&dispparams, 0, sizeof dispparams);
	dispparams.cArgs = arraySize;
	dispparams.rgvarg = new VARIANT[dispparams.cArgs];
	
	for( int i = 0; i < arraySize; i++)
	{
		CComBSTR bstr = paramArray.GetAt(arraySize - 1 - i); // back reading
		bstr.CopyTo(&dispparams.rgvarg[i].bstrVal);
		dispparams.rgvarg[i].vt = VT_BSTR;
	}
	dispparams.cNamedArgs = 0;

	EXCEPINFO excepInfo;
	memset(&excepInfo, 0, sizeof excepInfo);
   	CComVariant vaResult;
	UINT nArgErr = (UINT)-1;  // initialize to invalid arg
         
	hr = spScript->Invoke(dispid,IID_NULL,0,
							DISPATCH_METHOD,&dispparams,&vaResult,&excepInfo,&nArgErr);


	delete [] dispparams.rgvarg;
	if(FAILED(hr))
	{
		ShowError(GetSystemErrorMessage(hr));
		return false;
	}
	
	if(pVarResult)
	{
		*pVarResult = vaResult;
	}

	return true;
}

// returned java script function name, input string is truncating
CString CWebPage::ScanJScript(CString& strAText, CStringArray& args)
{
	args.RemoveAll();
	CString strDelim(" \n\r\t"),strSrc(strAText);
	bool bFound = false;
	while(!strSrc.IsEmpty())
	{
		CString strStart = GetNextToken(strSrc,strDelim);
		if(strStart == "function")
		{
			bFound = true;
			break;
		}
		if(strStart == "/*")
		{
			// Skip comments
			while(!strSrc.IsEmpty())
			{
				CString strStop = GetNextToken(strSrc,strDelim);
				if(strStop == "*/")
				{
					break;
				}
			}
		}
	}

	if(!bFound)
		return "";
	
	CString strFunc = GetNextToken(strSrc,"(",true);
	CString strArgs = GetNextToken(strSrc,")",true);

	// Parse arguments
	CString strArg;
	while(!(strArg = GetNextToken(strArgs,",")).IsEmpty())
		args.Add(strArg);

	strAText= strSrc;
	return strFunc;
}

// 항목찾기
BOOL CWebPage::FindElement(LPCTSTR tszElem,UINT uIndex)
{
	USES_CONVERSION;
	CComPtr<IHTMLElementCollection> allElems;
    CComPtr<IDispatch> pDisp;
    VARIANT varName, varIx;
    
    CComPtr<IHTMLElementCollection> allAnchors;
    CComPtr<IDispatch> pAnchorDisp;
    CComQIPtr<IHTMLElement> pElem;
    LPCWSTR        pszElem = NULL;

    
    IHTMLDocument2* pDoc = m_spDoc;

	if (!pDoc)
		return FALSE;
	if (FAILED(pDoc->get_all(&allElems)))
		return FALSE;

	varName.vt = VT_BSTR;
	varName.bstrVal = SysAllocString(A2W(tszElem));
	varIx.vt = VT_I2;
	varIx.iVal = uIndex;

	if (SUCCEEDED(allElems->item(varName, varIx, &pDisp)))
		m_pElem = pDisp;
	SysFreeString(varName.bstrVal);

	if (m_pElem)
		return TRUE;
    
	return FALSE;	//Elemement not found
}

// 항목에 HTML 쓰기
BOOL CWebPage::WriteElement(LPCTSTR HTMLText)
{
   
    // BSTR 변환에 신경쓰자
    CString str(HTMLText); 
    BSTR bstr = str.AllocSysString(); 

    if(!m_pElem) return FALSE;

    HRESULT hr = E_FAIL;
    hr = m_pElem->put_innerHTML(bstr);

    SysFreeString(bstr);
		
	return TRUE;
}


// 항목에 HTML 읽기
CString CWebPage::ReadElement()
{
    BSTR bstr; 

    if(!m_pElem) return " ";

    HRESULT hr = E_FAIL;
    		
    hr = m_pElem->get_innerHTML(&bstr);
             
	CString s = CString( " " );
	s = CString(bstr);
    
    return s;
}

// Input 항목에 HTML 쓰기
BOOL CWebPage::WriteInputElement(LPCTSTR HTMLText)
{
   
    // BSTR 변환에 신경쓰자
    CString str(HTMLText); 
    BSTR bstr = str.AllocSysString(); 

    if(!m_pElem) return FALSE;

    HRESULT hr = E_FAIL;
    
	CComQIPtr<IHTMLInputTextElement> m_pInput;
	m_pInput = m_pElem;
	hr = m_pInput->put_value( bstr ) ;

    SysFreeString(bstr);
		
	return TRUE;
}


// Input 항목에 HTML 읽기
CString CWebPage::ReadInputElement()
{
    BSTR bstr; 

    if(!m_pElem) return " ";

    HRESULT hr = E_FAIL;
    		
    CComQIPtr<IHTMLInputTextElement> m_pInput;
	m_pInput = m_pElem;
	
	hr = m_pInput->get_value (&bstr);
             
	CString s = CString( " " );
	s = CString(bstr);
    
	return s;
}


// 2006.11.23 박성완 추가 
// TextArea 내용을 가져온다.
CString CWebPage::ReadTextElement()
{
    BSTR bstr; 

    if(!m_pElem) return " ";

    HRESULT hr = E_FAIL;
    		
    CComQIPtr<IHTMLTextAreaElement> m_pInput;
	m_pInput = m_pElem;
	
	hr = m_pInput->get_value (&bstr);
             
	CString s = CString( " " );
	s = CString(bstr);
    
	return s;
}

// 2006.11.23 박성완 추가 
// TextArea 내용을 가져온다.
BOOL CWebPage::WriteTextElement(LPCTSTR HTMLText)
{
    
    // BSTR 변환에 신경쓰자
    CString str(HTMLText); 
    BSTR bstr = str.AllocSysString(); 
    if(!m_pElem) return false;

    HRESULT hr = E_FAIL;
    		
    CComQIPtr<IHTMLTextAreaElement> m_pInput;
	m_pInput = m_pElem;
	
	hr = m_pInput->put_value (bstr);
             
    SysFreeString(bstr);
    
	return TRUE;
}
