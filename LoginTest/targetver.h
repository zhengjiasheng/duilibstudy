#pragma once

// ���� SDKDDKVer.h ��������õ���߰汾�� Windows ƽ̨��

// ���ҪΪ��ǰ�� Windows ƽ̨����Ӧ�ó�������� WinSDKVer.h������
// WIN32_WINNT ������ΪҪ֧�ֵ�ƽ̨��Ȼ���ٰ��� SDKDDKVer.h��

#include <SDKDDKVer.h>

/*Duilib API�����ú�ʹ��
Duilib���ã�
1���½�win32��Ŀ����ĿĿ¼����include��libs�ļ��У��ļ��������Duilib�Ĵ����lib������һ�����Բ��ã�ֱ������DuilibԴ���еĴ����lib��·��Ҳ�ǿ��Եģ�������ÿ��Բο�demos�е���Ŀʾ����
2�����ø��Ӱ���Ŀ¼��C/C++�µĳ��棩ΪincludeĿ¼�����ø��ӿ�Ŀ¼��������/���棩ΪlibsĿ¼����includeĿ¼����Duilib���룬������UIlib.hͷ�ļ���libsĿ¼����DuiLib.lib��������APIҲ���԰���ͬ���ķ�ʽ���ã�
3���������Ŀ¼���������exe�ļ�Ŀ¼������ʹ��Ĭ�ϡ��ҵ����exeĿ¼����DuiLib.dll�ŵ���Ŀ¼������̬���ӣ�������Ŀ��������ִ�У�exe��������ִ�У���ʵ���ǰ�dll�ŵ�exe��ͬ����������APIͬ����ˣ�
4������Ŀ��stdafx.h������Duilib������UIlib.hͷ�ļ�������lib���Լ��������á���stdafx.cpp����һЩ���ݡ�
Duilibʹ�ã�
��ĿԴ�ļ��У�LoginTest.cpp���������֣�1������ʵ������Ϣ��Ӧ����  class CFrameWindowWnd : public CWindowWnd, public INotifyUI{}   ����Duilibҳ�棺newһ��CFrameWindowWndʵ����
2��������ڼ�Duilib��ʼ������  int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE //hPrevInstance , LPSTR //lpCmdLine, int nCmdShow){} �൱��main�������������ڣ�������new Duilibʵ�������г�ʼ������������Duilib��Դ·���ȣ�

����Duilibʵ������CFrameWindowWnd�򵥽��ܣ�
class CFrameWindowWnd : public CWindowWnd, public INotifyUI
{
	//---------------�麯��-------------��
	//��ȡ��������
    LPCTSTR GetWindowClassName() const { return _T("UIMainFrame"); };
    UINT GetClassStyle() const { return UI_CLASSSTYLE_FRAME | CS_DBLCLKS; };
    void OnFinalMessage(HWND //hWnd) { delete this; };

	//�¼����� ***��Ҫ
	void Notify(TNotifyUI& msg){}
	//��Ϣ���� ***��Ҫ
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam){}
}
����ο�LoginTest.cpp�е���ϸע��
*/