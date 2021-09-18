// LoginTest.cpp : 定义应用程序的入口点。
//
#include "stdafx.h"
#include "LoginTest.h"

CFrameWindowWnd::CFrameWindowWnd() { };
CFrameWindowWnd::~CFrameWindowWnd(){ };

//获取窗口类名
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

//事件处理：用来处理页面触发的事件，页面触发的事件都由Notify处理，包括:_T("windowinit") click  selectchanged等
//msg：触发的事件
//msg.sType:事件类型，用于判断    因为触发的所有事件都由Notify处理，为了区分，所以进行判断
//msg.pSender:发送事件者/触发事件的元素（注意：元素本身）  用于判断
//msg.pSender->GetName():触发事件的元素的名字 用于判断
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
			//关闭此窗口，不退出程序（只把该窗口隐藏，没有退出Duilib的消息循环）
			this->ShowWindow(false,false);
			//::MessageBox(NULL, _T("buttonName1 has been clicked"), _T(""), NULL);  //消息通知弹窗
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
	pImgSchFrame->Create(NULL, _T("图片切换"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
	pImgSchFrame->ShowWindow(true);
	//pImgSchFrame->ShowModal();
}

//消息处理：用来处理消息，包括windows消息，Duilib消息，自定义消息
//uMsg:消息 如：WM_CREATE windows消息 创建消息
//wParam/lParam:消息参数
LRESULT CFrameWindowWnd::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//结果码：发送消息的结果码
	LRESULT lRes = 0;
	//是否是系统消息
	BOOL bHandled = true;

	switch (uMsg)
	{//windows系统消息
	case WM_CREATE:		lRes = OnCreate(uMsg,wParam,lParam,bHandled); break;       //创建窗口消息：窗口创建成功还未显示，windows系统发送该消息，给该程序，该程序把这个消息交给HandleMessage()来处理，即消息处理函数HandleMessage()接收到系统发的WM_CREATE消息。
	case WM_DESTROY:	lRes = OnDestroy(uMsg,wParam,lParam,bHandled); break;      //关闭程序消息：关闭程序时系统发送该消息。比较下面三个消息：WM_DESTROY：是用来关闭程序的。 WM_CLOSE：是用来关闭窗口的。 WM_QUIT：是用来关闭消息循环的。当用户点击窗口上的关闭按钮时，系统发出 WM_CLOSE消息，首先关闭了当前窗口，然后发送WM_DESTROY 消息关闭应用程序，最后发出WM_QUIT 消息来关闭消息循环
	//下面三个消息去除界面中系统的标题栏和边框
	case WM_NCACTIVATE: lRes = OnNcActivate(uMsg,wParam,lParam,bHandled); break;   //WM_NCACTIVATE消息：设置标题栏显示为激活或者非激活状态.
	case WM_NCCALCSIZE: lRes = OnNcCalcSize(uMsg,wParam,lParam,bHandled); break;   //在计算窗口客户区的大小和位置时发送。通过处理这个消息，应用程序可以在窗口大小或位置改变时控制客户区的内容。
	case WM_NCPAINT:    lRes = OnNcPaint(uMsg,wParam,lParam,bHandled); break;      //当窗体框架（非客户区）要被重画时，发送该消息
		//非系统消息，Duilib消息（自定义消息）
	default: bHandled = false; break;
	}
	//系统消息
	if(bHandled) return lRes;
	//Duilib消息
	if( m_pm.MessageHandler(uMsg, wParam, lParam, lRes) ) return lRes;
	//处理不了，交给父类的消息处理函数处理
	return CWindowWnd::HandleMessage(uMsg, wParam, lParam);
}

//创建窗口回调
LRESULT CFrameWindowWnd::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled)
{
	////界面管家的初始化函数，初始化界面元素
	m_pm.Init(m_hWnd);

	////代码方式创建UI，创建一个按钮
	//CControlUI *pButton = new CButtonUI;
	//pButton->SetName(_T("closebtn"));        //设置名字，名字唯一，用于区分元素/控件，判断发生事件的控件
	//pButton->SetText(_T("退出"));
	//pButton->SetBkColor(0xFFFF0000);

	//解析xml的方式创建UI
	//声明一个窗口构造器
	CDialogBuilder builder;
	//解析xml创建UI  注意：xml文件的路径为设置的资源的默认路径
	CControlUI* pRoot =  builder.Create(_T("begin.xml"), (UINT)0, NULL, &m_pm);
	ASSERT(pRoot && "Failed to parse XML");

	//调用页面管家的添加元素函数，把创建的元素添加到Duilib界面中
	m_pm.AttachDialog(pRoot);
	//调用AddNotifier（添加事件处理器），把界面添加到事件处理器中，这样，Duilib界面触发的事件才能被事件处理器（Notify函数）处理
	//注意：这两步要在windows发送WM_CREATE消息时执行（创建的元素，包括从xml文件中解析的元素，和代码创建的元素一样，AttachDialog添加到Duilib界面中）
	m_pm.AddNotifier(this);
	return 0;
}

//关闭/销毁程序回调
LRESULT CFrameWindowWnd::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled)
{
	::PostQuitMessage(0);
	bHandled = false;
	return 0;
}

//用来设置标题栏显示为激活或者非激活状态
LRESULT CFrameWindowWnd::OnNcActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled)
{
	if( ::IsIconic(*this) ) bHandled = FALSE;
    return (wParam == 0) ? TRUE : FALSE;
}

//在窗口大小或位置改变时控制客户区的内容
LRESULT CFrameWindowWnd::OnNcCalcSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return 0;
}

//处理窗体更新区域，应用这个消息就返回0
LRESULT CFrameWindowWnd::OnNcPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return 0;
}


// 程序入口及Duilib初始化部分
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPSTR /*lpCmdLine*/, int nCmdShow)
{
	//设置程序实例句柄
    CPaintManagerUI::SetInstance(hInstance);
	
	//调试
	CDuiString path =  CPaintManagerUI::GetInstancePath();
	//设置资源的默认路径：GetInstancePath()：输出路径，输出的exe文件路径  同时解析xml创建界面时就是再该目录下查找xml文件
    CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath() + _T("TextResource"));

	//创建并显示窗口
    CFrameWindowWnd* pFrame = new CFrameWindowWnd();
    if( pFrame == NULL ) return 0;
    pFrame->Create(NULL, _T("登录"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
    pFrame->ShowWindow(true);
	//Duilib的消息循环：程序运行时一直在执行duilib的消息循环函数MessageLoop，一直没有返回，当点击退出时（即），该消息循环函数才会结束，才会返回，然后return 0退出这个程序。（注意：在消息循环函数未返回前，该程序不会结束，即使关闭了窗口ShowWindow(false)，只要消息循环未结束，程序也不会结束，这样可以实现窗口切换，即关闭这个窗口，重新打开一个窗口）
    CPaintManagerUI::MessageLoop();

    return 0;
}


