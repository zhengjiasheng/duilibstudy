// LoginTest.cpp : ����Ӧ�ó������ڵ㡣
//
#include "stdafx.h"
#include "LoginTest.h"

CFrameWindowWnd::CFrameWindowWnd() { };
CFrameWindowWnd::~CFrameWindowWnd(){ };

//��ȡ��������
LPCTSTR CFrameWindowWnd::GetWindowClassName() const 
{ 
	return _T("UIMainFrame"); 
}

UINT CFrameWindowWnd::GetClassStyle() const 
{ 
	return UI_CLASSSTYLE_FRAME | CS_DBLCLKS; 
}

void CFrameWindowWnd::OnFinalMessage(HWND /*hWnd*/) 
{ 
	delete this; 
}

//�¼�������������ҳ�津�����¼���ҳ�津�����¼�����Notify��������:_T("windowinit") click  selectchanged��
//msg���������¼�
//msg.sType:�¼����ͣ������ж�    ��Ϊ�����������¼�����Notify����Ϊ�����֣����Խ����ж�
//msg.pSender:�����¼���/�����¼���Ԫ�أ�ע�⣺Ԫ�ر���  �����ж�
//msg.pSender->GetName():�����¼���Ԫ�ص����� �����ж�
void CFrameWindowWnd::Notify(TNotifyUI& msg)
{
	if( msg.sType == _T("click") ) {
		if( msg.pSender->GetName() == _T("closebtn") ) {
			Close();
			//::PostQuitMessage(0);
		}
		else if(msg.pSender->GetName() == _T("minbtn") )
		{
			SendMessage(WM_SYSCOMMAND, SC_MINIMIZE, 0); return; 
		}
		else if (msg.pSender->GetName() == _T("maxbtn") )
		{
			SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE, 0); return; 
		}
		else if( msg.pSender->GetName() == _T("closewindow") ){
			//�رմ˴��ڣ����˳�����ֻ�Ѹô������أ�û���˳�Duilib����Ϣѭ����
			this->ShowWindow(false,false);
			//::MessageBox(NULL, _T("buttonName1 has been clicked"), _T(""), NULL);  //��Ϣ֪ͨ����
		}else if(msg.pSender->GetName() == _T("loginbtn")) {
			this->ShowWindow(false,false);
			this->Login();
		}
	}
}

void CFrameWindowWnd::Login()
{
	CImgSwitchWnd * pImgSchFrame = new CImgSwitchWnd();
	if( pImgSchFrame == NULL ) {
		pImgSchFrame->Close();
		return;
	}
	pImgSchFrame->Create(NULL, _T("ͼƬ�л�"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
	pImgSchFrame->ShowWindow(true);
	//pImgSchFrame->ShowModal();
}

//��Ϣ��������������Ϣ������windows��Ϣ��Duilib��Ϣ���Զ�����Ϣ
//uMsg:��Ϣ �磺WM_CREATE windows��Ϣ ������Ϣ
//wParam/lParam:��Ϣ����
LRESULT CFrameWindowWnd::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//����룺������Ϣ�Ľ����
	LRESULT lRes = 0;
	//�Ƿ���ϵͳ��Ϣ
	BOOL bHandled = true;

	switch (uMsg)
	{//windowsϵͳ��Ϣ
	case WM_CREATE:		lRes = OnCreate(uMsg,wParam,lParam,bHandled); break;       //����������Ϣ�����ڴ����ɹ���δ��ʾ��windowsϵͳ���͸���Ϣ�����ó��򣬸ó���������Ϣ����HandleMessage()����������Ϣ������HandleMessage()���յ�ϵͳ����WM_CREATE��Ϣ��
	case WM_DESTROY:	lRes = OnDestroy(uMsg,wParam,lParam,bHandled); break;      //�رճ�����Ϣ���رճ���ʱϵͳ���͸���Ϣ���Ƚ�����������Ϣ��WM_DESTROY���������رճ���ġ� WM_CLOSE���������رմ��ڵġ� WM_QUIT���������ر���Ϣѭ���ġ����û���������ϵĹرհ�ťʱ��ϵͳ���� WM_CLOSE��Ϣ�����ȹر��˵�ǰ���ڣ�Ȼ����WM_DESTROY ��Ϣ�ر�Ӧ�ó�����󷢳�WM_QUIT ��Ϣ���ر���Ϣѭ��
	//����������Ϣȥ��������ϵͳ�ı������ͱ߿�
	case WM_NCACTIVATE: lRes = OnNcActivate(uMsg,wParam,lParam,bHandled); break;   //WM_NCACTIVATE��Ϣ�����ñ�������ʾΪ������߷Ǽ���״̬.
	case WM_NCCALCSIZE: lRes = OnNcCalcSize(uMsg,wParam,lParam,bHandled); break;   //�ڼ��㴰�ڿͻ����Ĵ�С��λ��ʱ���͡�ͨ�����������Ϣ��Ӧ�ó�������ڴ��ڴ�С��λ�øı�ʱ���ƿͻ��������ݡ�
	case WM_NCPAINT:    lRes = OnNcPaint(uMsg,wParam,lParam,bHandled); break;      //�������ܣ��ǿͻ�����Ҫ���ػ�ʱ�����͸���Ϣ
		//��ϵͳ��Ϣ��Duilib��Ϣ���Զ�����Ϣ��
	default: bHandled = false; break;
	}
	//ϵͳ��Ϣ
	if(bHandled) return lRes;
	//Duilib��Ϣ
	if( m_pm.MessageHandler(uMsg, wParam, lParam, lRes) ) return lRes;
	//�����ˣ������������Ϣ����������
	return CWindowWnd::HandleMessage(uMsg, wParam, lParam);
}

//�������ڻص�
LRESULT CFrameWindowWnd::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled)
{
	////����ܼҵĳ�ʼ����������ʼ������Ԫ��
	m_pm.Init(m_hWnd);

	////���뷽ʽ����UI������һ����ť
	//CControlUI *pButton = new CButtonUI;
	//pButton->SetName(_T("closebtn"));        //�������֣�����Ψһ����������Ԫ��/�ؼ����жϷ����¼��Ŀؼ�
	//pButton->SetText(_T("�˳�"));
	//pButton->SetBkColor(0xFFFF0000);

	//����xml�ķ�ʽ����UI
	//����һ�����ڹ�����
	CDialogBuilder builder;
	//����xml����UI  ע�⣺xml�ļ���·��Ϊ���õ���Դ��Ĭ��·��
	CControlUI* pRoot =  builder.Create(_T("begin.xml"), (UINT)0, NULL, &m_pm);
	ASSERT(pRoot && "Failed to parse XML");

	//����ҳ��ܼҵ����Ԫ�غ������Ѵ�����Ԫ����ӵ�Duilib������
	m_pm.AttachDialog(pRoot);
	//����AddNotifier������¼������������ѽ�����ӵ��¼��������У�������Duilib���津�����¼����ܱ��¼���������Notify����������
	//ע�⣺������Ҫ��windows����WM_CREATE��Ϣʱִ�У�������Ԫ�أ�������xml�ļ��н�����Ԫ�أ��ʹ��봴����Ԫ��һ����AttachDialog��ӵ�Duilib�����У�
	m_pm.AddNotifier(this);
	return 0;
}

//�ر�/���ٳ���ص�
LRESULT CFrameWindowWnd::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled)
{
	::PostQuitMessage(0);
	bHandled = false;
	return 0;
}

//�������ñ�������ʾΪ������߷Ǽ���״̬
LRESULT CFrameWindowWnd::OnNcActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled)
{
	if( ::IsIconic(*this) ) bHandled = FALSE;
    return (wParam == 0) ? TRUE : FALSE;
}

//�ڴ��ڴ�С��λ�øı�ʱ���ƿͻ���������
LRESULT CFrameWindowWnd::OnNcCalcSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return 0;
}

//�������������Ӧ�������Ϣ�ͷ���0
LRESULT CFrameWindowWnd::OnNcPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return 0;
}


// ������ڼ�Duilib��ʼ������
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPSTR /*lpCmdLine*/, int nCmdShow)
{
	//���ó���ʵ�����
    CPaintManagerUI::SetInstance(hInstance);
	
	//����
	CDuiString path =  CPaintManagerUI::GetInstancePath();
	//������Դ��Ĭ��·����GetInstancePath()�����·���������exe�ļ�·��  ͬʱ����xml��������ʱ�����ٸ�Ŀ¼�²���xml�ļ�
    CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath() + _T("TextResource"));

	//��������ʾ����
    CFrameWindowWnd* pFrame = new CFrameWindowWnd();
    if( pFrame == NULL ) return 0;
    pFrame->Create(NULL, _T("��¼"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
    pFrame->ShowWindow(true);
	//Duilib����Ϣѭ������������ʱһֱ��ִ��duilib����Ϣѭ������MessageLoop��һֱû�з��أ�������˳�ʱ������������Ϣѭ�������Ż�������Ż᷵�أ�Ȼ��return 0�˳�������򡣣�ע�⣺����Ϣѭ������δ����ǰ���ó��򲻻��������ʹ�ر��˴���ShowWindow(false)��ֻҪ��Ϣѭ��δ����������Ҳ�����������������ʵ�ִ����л������ر�������ڣ����´�һ�����ڣ�
    CPaintManagerUI::MessageLoop();

    return 0;
}


