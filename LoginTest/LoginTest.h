#pragma once

#include "resource.h"
#include "SwitchImg.h"


// 窗口实例及消息响应类
class CFrameWindowWnd : public CWindowWnd, public INotifyUI
{
public:
	CFrameWindowWnd();
	~CFrameWindowWnd();

	//---------------虚函数-------------
	//获取窗口类名
    LPCTSTR GetWindowClassName() const;  //函数前面的const表示函数返回const常量，函数后面的const表示这个函数不能修改该类的成员变量，即只读函数
    UINT GetClassStyle() const;
    void OnFinalMessage(HWND /*hWnd*/);

public:
	//事件处理：用来处理页面触发的事件，页面触发的事件都由Notify处理，包括:_T("windowinit") click  selectchanged等
	//msg：触发的事件
	//msg.sType:事件类型，用于判断    因为触发的所有事件都由Notify处理，为了区分，所以进行判断
	//msg.pSender:发送事件者/触发事件的元素（注意：元素本身）  用于判断
	//msg.pSender->GetName():触发事件的元素的名字 用于判断
    void Notify(TNotifyUI& msg);

	//登录
	void Login();

	//消息处理：用来处理消息，包括windows消息，Duilib消息，自定义消息
	//uMsg:消息 如：WM_CREATE windows消息 创建消息
	//wParam/lParam:消息参数
    LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

	//创建窗口回调
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled);
	//关闭/销毁程序回调
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled);
	//用来设置标题栏显示为激活或者非激活状态 下面三个函数用来去除界面中系统的标题栏和边框
	LRESULT OnNcActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled);
	//在窗口大小或位置改变时控制客户区的内容
	LRESULT OnNcCalcSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled);
	//处理窗体更新区域
	LRESULT OnNcPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

private:
	CPaintManagerUI m_pm; //Duilib的界面管家
	/*界面管家函数：
	void Init(HWND hWnd, LPCTSTR pstrName = NULL)：初始化界面元素，清除所有的图片、字体、一切恢复到原始状态了   常使用：m_pm.Init(m_hWnd)
	void Invalidate()/void Invalidate(RECT& rcItem)：刷新界面，刷新某个区域
	pos与size：例如：POINT GetMousePos() const/SIZE GetClientSize() const等等：关于界面位置与尺寸
	Font：例如：TFontInfo* GetDefaultFontInfo()：关于字体
	等等，详情请参考：https://blog.csdn.net/wyansai/article/details/51052441
	*/
};
