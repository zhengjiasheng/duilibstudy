#pragma once

#include "resource.h"
#include "http_libcurl.h"
#include "json_utils.h"

class MainWndFrame : public WindowImplBase
{
protected:
	virtual CDuiString GetSkinFolder() override;                                             // 获取皮肤文件的目录,就是输出文件（exe）的目录(以此目录来设置资源目录（xmlUI）)
	virtual CDuiString GetSkinFile() override;                                               //设置皮肤文件名字，就是xmlUI页面的文件名字
	virtual LPCTSTR GetWindowClassName(void) const override;                                 //设置当前窗口的名字（class name）

	//重写从父类中继承的函数
	virtual void InitWindow();                                                               //窗口初始化函数
	virtual void Notify(TNotifyUI &msg);                                                     //事件处理函数
	virtual LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);        //窗口关闭的回调函数：父类的该函数只是把窗口隐藏了，并没有退出程序。这里，子类重写该函数，添加退出程序的代码

	//仿MFC形式将事件（界面发生的事件/消息，本来由Notify处理）映射到某个函数来处理 注意：相应的事件映射给相应的函数
	//DUI_DECLARE_MESSAGE_MAP()                                                                //用来映射事件给函数
	//不用做该映射，只需要重写父类的OnClick()即可
	void OnClick(TNotifyUI &msg);                                                            //用来映射点击事件的函数，处理点击事件
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);                          //重写父类的消息处理函数，用来捕获或者拦截原声的系统消息

public:
	MainWndFrame();
	~MainWndFrame();

	static const LPCTSTR kClassName;                                                         //窗口名字
	static const LPCTSTR kMainWndFrame;                                                      //窗口页面:解析的xml页面文件的名字

private:
	CButtonUI * m_pMinBtn;                                                                  //用来保存最小化按钮
	CButtonUI * m_pMaxBtn;																	//最大化按钮
	CButtonUI * m_pRestoreBtn;																//还原按钮
	CButtonUI * m_pCloseBtn;																//关闭按钮
	CEditUI * m_pUserName;
	CEditUI * m_pPassWord;

	void login();                                                                           //用户登录
	string loginRequest(string get_url);                                              //登录请求
};