#include "stdafx.h"
#include "SwitchImg.h"

CImgSwitchWnd::CImgSwitchWnd() { };
CImgSwitchWnd::~CImgSwitchWnd(){ };

//获取窗口类名
LPCTSTR CImgSwitchWnd::GetWindowClassName() const 
{ 
	return _T("CImgSwitchWnd"); 
}

UINT CImgSwitchWnd::GetClassStyle() const 
{ 
	return UI_CLASSSTYLE_FRAME | CS_DBLCLKS; 
}

void CImgSwitchWnd::OnFinalMessage(HWND /*hWnd*/) 
{ 
	delete this; 
}

void CImgSwitchWnd::Notify(TNotifyUI& msg)
{
	if( msg.sType == _T("click") ) {
		if( msg.pSender->GetName() == _T("closebtn") ) {
			Close();
			//::PostQuitMessage(0);
		}
		else if( msg.pSender->GetName() == _T("closewindow") ){
			ShowWindow(false,false);
		}
	}
}

LRESULT CImgSwitchWnd::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT lRes = 0;
	BOOL bHandled = true;

	switch (uMsg)
	{
	case WM_CREATE:		lRes = OnCreate(uMsg,wParam,lParam,bHandled); break;       
	case WM_DESTROY:	lRes = OnDestroy(uMsg,wParam,lParam,bHandled); break;      
	//case WM_NCACTIVATE: lRes = OnNcActivate(uMsg,wParam,lParam,bHandled); break;   
	//case WM_NCCALCSIZE: lRes = OnNcCalcSize(uMsg,wParam,lParam,bHandled); break;   
	//case WM_NCPAINT:    lRes = OnNcPaint(uMsg,wParam,lParam,bHandled); break;    
	default: bHandled = false; break;
	}
	if(bHandled) return lRes;
	if( m_pm.MessageHandler(uMsg, wParam, lParam, lRes) ) return lRes;
	return CWindowWnd::HandleMessage(uMsg, wParam, lParam);
}

LRESULT CImgSwitchWnd::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled)
{
	m_pm.Init(m_hWnd);

	CDialogBuilder builder;
	CControlUI* pRoot =  builder.Create(_T("imgswitch.xml"), (UINT)0, NULL, &m_pm);
	ASSERT(pRoot && "Failed to parse XML");

	m_pm.AttachDialog(pRoot);
	m_pm.AddNotifier(this);
	return 0;
}

LRESULT CImgSwitchWnd::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled)
{
	::PostQuitMessage(0);
	bHandled = false;
	return 0;
}

LRESULT CImgSwitchWnd::OnNcActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled)
{
	if( ::IsIconic(*this) ) bHandled = FALSE;
    return (wParam == 0) ? TRUE : FALSE;
}

LRESULT CImgSwitchWnd::OnNcCalcSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return 0;
}

LRESULT CImgSwitchWnd::OnNcPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return 0;
}
