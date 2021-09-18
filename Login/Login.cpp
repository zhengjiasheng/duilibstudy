// Login.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "Login.h"
#include "ImageCanva.h"

const LPCTSTR MainWndFrame::kClassName = _T("login");                 //������
const LPCTSTR MainWndFrame::kMainWndFrame = _T("login.xml");          //������xml����ҳ���ļ�������

//��ҳ�淢�����¼�/��Ϣӳ�����Ӧ��������        ������ӳ�䣬ֻ��Ҫ��д����ĺ������ɣ�OnClick()��
//DUI_BEGIN_MESSAGE_MAP(MainWndFrame,CNotifyPump)
//	DUI_ON_MSGTYPE(DUI_MSGTYPE_CLICK,OnClick)
//DUI_END_MESSAGE_MAP()

DuiLib::CDuiString MainWndFrame::GetSkinFolder()
{
	// m_PaintManager:��ʵ��CPaintManagerUI  ���������/����ܼ�
	// GetInstancePath �ӿڷ���Ĭ�ϵ�Ƥ���ļ�λ�ã����������exe�ļ���Ŀ¼
	// �� main ���������ǿ���ͨ�� SetResourcePath ������·����������Դ·���������Դ��·��������xmlҳ���ļ��ȣ�������xml�ļ�����ҳ��ʱ�ʹӸ�Ŀ¼������Ӧ��xml�ļ�
	return m_PaintManager.GetInstancePath();
}

DuiLib::CDuiString MainWndFrame::GetSkinFile()
{
	// ��Ա���������Ƥ���ļ���������Ҫ������xml�ļ�������
	return kMainWndFrame;
}

LPCTSTR MainWndFrame::GetWindowClassName(void) const
{
	// ��Ա��������Ĵ��� class name�����ش�������
	return kClassName;
}

MainWndFrame::MainWndFrame()
{
	m_pMinBtn = nullptr;
	m_pMaxBtn = nullptr;
	m_pRestoreBtn = nullptr;
	m_pCloseBtn = nullptr;
	m_pUserName = nullptr;
	m_pPassWord = nullptr;
}

MainWndFrame::~MainWndFrame()
{

}

//���ڳ�ʼ����������д������������
void MainWndFrame::InitWindow()
{
	//��ȡ����ؼ������ؼ�ת���ɴ�����Բ����Ŀؼ�����ָ��
	m_pCloseBtn = dynamic_cast<CButtonUI*>(m_PaintManager.FindControl(_T("closebtn")));
	//ͨ����������ؼ�����Ӧ���������޸ĸÿؼ�����Ӧ����ֵ
	//m_pCloseBtn->SetVisible(false);  //��������ؼ�
	m_pUserName = dynamic_cast<CEditUI *>(m_PaintManager.FindControl(_T("username")));
	m_pPassWord = dynamic_cast<CEditUI *>(m_PaintManager.FindControl(_T("password")));
}

//���ڹرյĻص���������д�������������������˳�����Ĵ���
LRESULT MainWndFrame::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (uMsg == WM_CLOSE)
	{
		PostQuitMessage(0L);
	}
	return __super::OnClose(uMsg,wParam,lParam,bHandled);
}

//�������¼�����д������������
void MainWndFrame::OnClick(TNotifyUI & msg)
{
	CDuiString sCtrlName = msg.pSender->GetName();
	if (sCtrlName == _T("minbtn"))
	{
		SendMessage(WM_SYSCOMMAND,SC_MINIMIZE,0);
		return;
	}else if (sCtrlName == _T("maxbtn"))
	{
		SendMessage(WM_SYSCOMMAND,SC_MAXIMIZE,0);
		return;
	}else if (sCtrlName == _T("restorebtn"))
	{
		SendMessage(WM_SYSCOMMAND,SC_RESTORE,0);
		return;
	}else if (sCtrlName == _T("loginbtn"))
	{
		this->login();
	}
	return;
}

//�¼�����������д������������
void MainWndFrame::Notify(TNotifyUI &msg)
{
	if (msg.sType == DUI_MSGTYPE_CLICK)
	{
		if (msg.pSender == m_pCloseBtn || msg.pSender->GetName() == _T("exitbtn"))
		{
			Close();  //���õ��Ǹ����Close(),ֻ�ܰ�������ڹر�/���أ������ܹرճ��򡣣�ԭ��û���˳�Duilib����Ϣѭ���� ����취����д�����OnClose()����OnClose()���˳���Ϣѭ����PostQuitMessage(0L)��
			return;
		}
	}else if (msg.sType == DUI_MSGTYPE_RETURN) //���»س��������¼�����
	{
		if (msg.pSender->GetName() == _T("password"))
		{
			this->login();
		}
	}
	__super::Notify(msg);  //�����ø���� Notify ����������������Ϣ������˵����������������д����������Լ����������������Ļ���������������������
}

//��Ϣ����������д�������Ϣ�����������������������ԭ����ϵͳ��Ϣ
LRESULT MainWndFrame::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_CHANGECBCHAIN)
	{
		// do something...
	}
	else if (uMsg == WM_DRAWCLIPBOARD)
	{
		// do something...
	}

	return __super::HandleMessage(uMsg, wParam, lParam);
}

void MainWndFrame::login()
{
	CDuiString username =  m_pUserName->GetText();
	CDuiString password =  m_pPassWord->GetText();
	if (username == "" || password == "")
	{
		::MessageBox(NULL,_T("�û��������벻��Ϊ��"),_T("��ʾ"),NULL);
		return;
	}
	string get_url = "http://localhost:8088/blogger/login?user_name="+(string)username+"&password="+(string)password;
	string get_res = this->loginRequest(get_url);
	CJsonReader reader;
	if (reader.parse(get_res))
	{
		int code = atoi(reader.getParam("code").c_str());
		if (code == 200)
		{
			ShowWindow(false);
			ImageCanvaFrame * pImageCanvaFrame = new ImageCanvaFrame();
			pImageCanvaFrame->Create(NULL,ImageCanvaFrame::kClassName,UI_WNDSTYLE_FRAME,0);
			pImageCanvaFrame->CenterWindow();
			pImageCanvaFrame->ShowWindow();
		}else
		{
			::MessageBox(NULL,_T(reader.getParam("msg").c_str()),_T("��ʾ"),NULL);
		}
	}	
}

string MainWndFrame::loginRequest(string get_url)
{
	string get_res;
	curl_global_init(CURL_GLOBAL_ALL);
	
	auto res = curl_get_req(get_url,get_res);
	if (res != CURLE_OK)
	{
		string errInfo = "curl_easy_perform() failed: " + string(curl_easy_strerror(res));
		::MessageBox(NULL,_T(errInfo.c_str()),_T("��ʾ"),NULL);
	}else
	{
		get_res = UTF8ToGBK(get_res.c_str());
	}

	curl_global_cleanup();
	return get_res;
}


int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	
	//���ô��ڹ���ʵ��(����������еĺ���)
	CPaintManagerUI::SetInstance(hInstance);

	//������Դ·��
	CPaintManagerUI::SetCurrentPath(CPaintManagerUI::GetInstancePath());
	CPaintManagerUI::SetResourcePath(_T("resource"));
	//ʹ����Դѹ������zip������ʽ�����Դ ע�⣺��ѹ������login.zip��ֻѹ��login.xml��������resource�ļ��У���ֱ�Ӱ�login.xml�ŵ�ѹ�����������
	/*CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath() + _T("resource"));
	CPaintManagerUI::SetResourceZip(_T("login.zip"));*/

	//��������
	MainWndFrame * pMainWndFrame = new MainWndFrame();
	pMainWndFrame->Create(nullptr,MainWndFrame::kClassName,UI_WNDSTYLE_FRAME,0);   //UI_WNDSTYLE_DIALOG�ĳ�UI_WNDSTYLE_FRAME�����ڵı�����˫���Ϳ�������ˡ�
	pMainWndFrame->CenterWindow();  //���ھ���
	pMainWndFrame->ShowWindow();    //������ʾ�����������λ�true����ʾ����false�����أ�������������øú�������ô�ú����ᱻĬ�ϵ�������ʾ

	//����duilib����Ϣѭ��
	CPaintManagerUI::MessageLoop();

	if (pMainWndFrame != nullptr)
	{
		delete pMainWndFrame;
	}

	return 0;
}
