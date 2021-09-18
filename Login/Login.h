#pragma once

#include "resource.h"
#include "http_libcurl.h"
#include "json_utils.h"

class MainWndFrame : public WindowImplBase
{
protected:
	virtual CDuiString GetSkinFolder() override;                                             // ��ȡƤ���ļ���Ŀ¼,��������ļ���exe����Ŀ¼(�Դ�Ŀ¼��������ԴĿ¼��xmlUI��)
	virtual CDuiString GetSkinFile() override;                                               //����Ƥ���ļ����֣�����xmlUIҳ����ļ�����
	virtual LPCTSTR GetWindowClassName(void) const override;                                 //���õ�ǰ���ڵ����֣�class name��

	//��д�Ӹ����м̳еĺ���
	virtual void InitWindow();                                                               //���ڳ�ʼ������
	virtual void Notify(TNotifyUI &msg);                                                     //�¼�������
	virtual LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);        //���ڹرյĻص�����������ĸú���ֻ�ǰѴ��������ˣ���û���˳��������������д�ú���������˳�����Ĵ���

	//��MFC��ʽ���¼������淢�����¼�/��Ϣ��������Notify����ӳ�䵽ĳ������������ ע�⣺��Ӧ���¼�ӳ�����Ӧ�ĺ���
	//DUI_DECLARE_MESSAGE_MAP()                                                                //����ӳ���¼�������
	//��������ӳ�䣬ֻ��Ҫ��д�����OnClick()����
	void OnClick(TNotifyUI &msg);                                                            //����ӳ�����¼��ĺ������������¼�
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);                          //��д�������Ϣ�����������������������ԭ����ϵͳ��Ϣ

public:
	MainWndFrame();
	~MainWndFrame();

	static const LPCTSTR kClassName;                                                         //��������
	static const LPCTSTR kMainWndFrame;                                                      //����ҳ��:������xmlҳ���ļ�������

private:
	CButtonUI * m_pMinBtn;                                                                  //����������С����ť
	CButtonUI * m_pMaxBtn;																	//��󻯰�ť
	CButtonUI * m_pRestoreBtn;																//��ԭ��ť
	CButtonUI * m_pCloseBtn;																//�رհ�ť
	CEditUI * m_pUserName;
	CEditUI * m_pPassWord;

	void login();                                                                           //�û���¼
	string loginRequest(string get_url);                                              //��¼����
};