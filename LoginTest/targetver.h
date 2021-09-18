#pragma once

// 包括 SDKDDKVer.h 将定义可用的最高版本的 Windows 平台。

// 如果要为以前的 Windows 平台生成应用程序，请包括 WinSDKVer.h，并将
// WIN32_WINNT 宏设置为要支持的平台，然后再包括 SDKDDKVer.h。

#include <SDKDDKVer.h>

/*Duilib API的配置和使用
Duilib配置：
1、新建win32项目，项目目录新增include、libs文件夹，文件夹中添加Duilib的代码和lib。（这一步可以不用，直接配置Duilib源码中的代码和lib的路径也是可以的，这个配置可以参考demos中的项目示例）
2、配置附加包含目录（C/C++下的常规）为include目录，配置附加库目录（链接器/常规）为libs目录。（include目录放置Duilib代码，尤其是UIlib.h头文件。libs目录放置DuiLib.lib。其他的API也可以按照同样的方式放置）
3、配置输出目录，即输出的exe文件目录，可以使用默认。找到输出exe目录，把DuiLib.dll放到该目录。（动态链接：这样项目才能正常执行，exe才能正常执行，其实就是把dll放到exe的同级）（其他API同样如此）
4、在项目的stdafx.h中配置Duilib，包含UIlib.h头文件，引入lib，以及其他配置。在stdafx.cpp配置一些数据。
Duilib使用：
项目源文件中（LoginTest.cpp）：两部分，1、窗口实例及消息响应部分  class CFrameWindowWnd : public CWindowWnd, public INotifyUI{}   创建Duilib页面：new一个CFrameWindowWnd实例。
2、程序入口及Duilib初始化部分  int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE //hPrevInstance , LPSTR //lpCmdLine, int nCmdShow){} 相当于main函数，程序的入口，在这里new Duilib实例，进行初始化（包括设置Duilib资源路径等）

创建Duilib实例的类CFrameWindowWnd简单介绍：
class CFrameWindowWnd : public CWindowWnd, public INotifyUI
{
	//---------------虚函数-------------：
	//获取窗口类名
    LPCTSTR GetWindowClassName() const { return _T("UIMainFrame"); };
    UINT GetClassStyle() const { return UI_CLASSSTYLE_FRAME | CS_DBLCLKS; };
    void OnFinalMessage(HWND //hWnd) { delete this; };

	//事件处理 ***主要
	void Notify(TNotifyUI& msg){}
	//消息处理 ***主要
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam){}
}
详情参考LoginTest.cpp中的详细注解
*/