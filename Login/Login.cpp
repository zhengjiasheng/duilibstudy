// Login.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "Login.h"
#include "ImageCanva.h"

const LPCTSTR MainWndFrame::kClassName = _T("login");                 //窗口名
const LPCTSTR MainWndFrame::kMainWndFrame = _T("login.xml");          //解析的xml窗口页面文件的名字

//将页面发生的事件/消息映射给相应函数处理        不用做映射，只需要重写父类的函数即可（OnClick()）
//DUI_BEGIN_MESSAGE_MAP(MainWndFrame,CNotifyPump)
//	DUI_ON_MSGTYPE(DUI_MSGTYPE_CLICK,OnClick)
//DUI_END_MESSAGE_MAP()

DuiLib::CDuiString MainWndFrame::GetSkinFolder()
{
	// m_PaintManager:其实是CPaintManagerUI  界面管理器/界面管家
	// GetInstancePath 接口返回默认的皮肤文件位置，就是输出的exe文件的目录
	// 在 main 函数中我们可以通过 SetResourcePath 来设置路径，设置资源路径：存放资源的路径，包括xml页面文件等，即解析xml文件创建页面时就从该目录查找相应的xml文件
	return m_PaintManager.GetInstancePath();
}

DuiLib::CDuiString MainWndFrame::GetSkinFile()
{
	// 成员变量定义的皮肤文件名，返回要解析的xml文件的名字
	return kMainWndFrame;
}

LPCTSTR MainWndFrame::GetWindowClassName(void) const
{
	// 成员变量定义的窗口 class name，返回窗口名字
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

//窗口初始化函数：重写父类的这个函数
void MainWndFrame::InitWindow()
{
	//获取这个控件：将控件转换成代码可以操作的控件对象指针
	m_pCloseBtn = dynamic_cast<CButtonUI*>(m_PaintManager.FindControl(_T("closebtn")));
	//通过调用这个控件的相应函数可以修改该控件的相应属性值
	//m_pCloseBtn->SetVisible(false);  //隐藏这个控件
	m_pUserName = dynamic_cast<CEditUI *>(m_PaintManager.FindControl(_T("username")));
	m_pPassWord = dynamic_cast<CEditUI *>(m_PaintManager.FindControl(_T("password")));
}

//窗口关闭的回调函数：重写父类的这个函数，增加退出程序的代码
LRESULT MainWndFrame::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (uMsg == WM_CLOSE)
	{
		PostQuitMessage(0L);
	}
	return __super::OnClose(uMsg,wParam,lParam,bHandled);
}

//处理点击事件：重写父类的这个函数
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

//事件处理函数：重写父类的这个函数
void MainWndFrame::Notify(TNotifyUI &msg)
{
	if (msg.sType == DUI_MSGTYPE_CLICK)
	{
		if (msg.pSender == m_pCloseBtn || msg.pSender->GetName() == _T("exitbtn"))
		{
			Close();  //调用的是父类的Close(),只能把这个窗口关闭/隐藏，并不能关闭程序。（原因：没有退出Duilib的消息循环） 解决办法：重写父类的OnClose()，在OnClose()中退出消息循环（PostQuitMessage(0L)）
			return;
		}
	}else if (msg.sType == DUI_MSGTYPE_RETURN) //按下回车按键的事件处理
	{
		if (msg.pSender->GetName() == _T("password"))
		{
			this->login();
		}
	}
	__super::Notify(msg);  //最后调用父类的 Notify 函数来处理其他消息，就是说，满足条件的由重写的这个函数自己处理，不满足条件的还交给父类的这个函数处理。
}

//消息处理函数：重写父类的消息处理函数，用来捕获或者拦截原声的系统消息
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
		::MessageBox(NULL,_T("用户名或密码不能为空"),_T("提示"),NULL);
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
			::MessageBox(NULL,_T(reader.getParam("msg").c_str()),_T("提示"),NULL);
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
		::MessageBox(NULL,_T(errInfo.c_str()),_T("提示"),NULL);
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
	
	//设置窗口关联实例(界面管理器中的函数)
	CPaintManagerUI::SetInstance(hInstance);

	//设置资源路径
	CPaintManagerUI::SetCurrentPath(CPaintManagerUI::GetInstancePath());
	CPaintManagerUI::SetResourcePath(_T("resource"));
	//使用资源压缩包（zip）的形式存放资源 注意：该压缩包（login.zip）只压缩login.xml，不包括resource文件夹，即直接把login.xml放到压缩包的最外层
	/*CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath() + _T("resource"));
	CPaintManagerUI::SetResourceZip(_T("login.zip"));*/

	//创建窗口
	MainWndFrame * pMainWndFrame = new MainWndFrame();
	pMainWndFrame->Create(nullptr,MainWndFrame::kClassName,UI_WNDSTYLE_FRAME,0);   //UI_WNDSTYLE_DIALOG改成UI_WNDSTYLE_FRAME，窗口的标题栏双击就可以最大化了。
	pMainWndFrame->CenterWindow();  //窗口居中
	pMainWndFrame->ShowWindow();    //窗口显示出来，不传参或传true会显示，传false会隐藏，另外如果不调用该函数，那么该函数会被默认调用且显示

	//开启duilib的消息循环
	CPaintManagerUI::MessageLoop();

	if (pMainWndFrame != nullptr)
	{
		delete pMainWndFrame;
	}

	return 0;
}
