#pragma once

#include "resource.h"
#include "SwitchImg.h"


// ����ʵ������Ϣ��Ӧ��
class CFrameWindowWnd : public CWindowWnd, public INotifyUI
{
public:
	CFrameWindowWnd();
	~CFrameWindowWnd();

	//---------------�麯��-------------
	//��ȡ��������
    LPCTSTR GetWindowClassName() const;  //����ǰ���const��ʾ��������const���������������const��ʾ������������޸ĸ���ĳ�Ա��������ֻ������
    UINT GetClassStyle() const;
    void OnFinalMessage(HWND /*hWnd*/);

public:
	//�¼�������������ҳ�津�����¼���ҳ�津�����¼�����Notify��������:_T("windowinit") click  selectchanged��
	//msg���������¼�
	//msg.sType:�¼����ͣ������ж�    ��Ϊ�����������¼�����Notify����Ϊ�����֣����Խ����ж�
	//msg.pSender:�����¼���/�����¼���Ԫ�أ�ע�⣺Ԫ�ر���  �����ж�
	//msg.pSender->GetName():�����¼���Ԫ�ص����� �����ж�
    void Notify(TNotifyUI& msg);

	//��¼
	void Login();

	//��Ϣ��������������Ϣ������windows��Ϣ��Duilib��Ϣ���Զ�����Ϣ
	//uMsg:��Ϣ �磺WM_CREATE windows��Ϣ ������Ϣ
	//wParam/lParam:��Ϣ����
    LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

	//�������ڻص�
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled);
	//�ر�/���ٳ���ص�
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled);
	//�������ñ�������ʾΪ������߷Ǽ���״̬ ����������������ȥ��������ϵͳ�ı������ͱ߿�
	LRESULT OnNcActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled);
	//�ڴ��ڴ�С��λ�øı�ʱ���ƿͻ���������
	LRESULT OnNcCalcSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled);
	//�������������
	LRESULT OnNcPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

private:
	CPaintManagerUI m_pm; //Duilib�Ľ���ܼ�
	/*����ܼҺ�����
	void Init(HWND hWnd, LPCTSTR pstrName = NULL)����ʼ������Ԫ�أ�������е�ͼƬ�����塢һ�лָ���ԭʼ״̬��   ��ʹ�ã�m_pm.Init(m_hWnd)
	void Invalidate()/void Invalidate(RECT& rcItem)��ˢ�½��棬ˢ��ĳ������
	pos��size�����磺POINT GetMousePos() const/SIZE GetClientSize() const�ȵȣ����ڽ���λ����ߴ�
	Font�����磺TFontInfo* GetDefaultFontInfo()����������
	�ȵȣ�������ο���https://blog.csdn.net/wyansai/article/details/51052441
	*/
};
