////////////////////////////////////////////////////Duilib�Զ���ؼ�--����
#ifndef _UI_CUSTOM_CANVAS_H_
#define _UI_CUSTOM_CANVAS_H_
#pragma once

#include "DuiLib\UIlib.h"
using namespace DuiLib;

typedef vector<POINT> Line;
//�����ͽӿ�������CreateControl�����л��õ�
const TCHAR CCustomCanvasClassName[] =	_T("CustomCanvasUI");
const TCHAR CCustomCanvasInterface[] =	_T("CustomCanvas");

class CCustomCanvasUI : public CControlUI
{
public:
	CCustomCanvasUI();
	~CCustomCanvasUI();

	//�������ֿؼ������͵��麯�������ڶ�̬ʶ��ؼ����ͺ����ؼ�������ת��
	LPCTSTR GetClass() const;                                 //�ؼ�������CCustomCanvasClassName��CustomCanvaUI ���ڴ������ж�
	LPVOID GetInterface(LPCTSTR pstrName);                    //�ؼ��ӿ�����CCustomCanvasInterface��CustomCanvas ����xml�ļ��пؼ���ǩ

	void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
	bool DoPaint(HDC hDC, const RECT& rcPaint, CControlUI* pStopControl);
	void DoEvent(TEventUI& event);
	virtual void DoInit();
	virtual void SetEnabled(bool enable = true);

public:
	void addPointToLine(POINT curPoint);
	void addLineToList(Line curLine);
	void clearCurrentLine();
	void clearLineList();
	void drawLine(HDC hdc,Line line);
	POINT InitialToCurrent(POINT point);
	POINT CurrentToInitial(POINT point);
	vector<Line> getLineList();
	void setLineList(vector<Line> lineList);
	
private:
	bool m_bInitialPaint;                         //�Ƿ��ǳ�ʼ����
	SIZE m_sInitialCanvasSize;                    //��ʼ������С
	SIZE m_sOriginPoint;                          //����ԭ��
	SIZE m_sCurrentCanvasSize;                    //��ǰ������С
	bool m_bMouseDown;                            //����Ƿ���
	Line m_lCurrentLine;                          //��ǰ���ڻ��Ƶ���
	vector<Line> m_vLineList;                     //���Ƶ�ȫ����
};

/*
�Զ���ؼ�������д�ĺ�����
LPCTSTR GetClass() const;                                //�ؼ�������CCustomCanvasClassName��CustomCanvaUI ���ڴ������ж�
LPVOID GetInterface(LPCTSTR pstrName);                   //�ؼ��ӿ�����CCustomCanvasInterface��CustomCanvas ����xml�ļ��пؼ���ǩ
virtual void DoEvent(TEventUI& event);                   //��Ϣ����������������Duilib��װ���ĸ�����Ϣ���������������Ƴ������ֵ���ͣ������˫�����һ�����ȡ���㡢���ù��ȵ�
virtual void DoPaint(HDC hDC, const RECT& rcPaint);      //�ؼ��Ļ��ƴ���������Duilib�ײ�Ҫ���»�������ؼ������߿ؼ��Լ�����Invalidata����ǿ���Լ�ˢ��ʱ����������ͻᱻ���������������������˸���״̬�µı���ǰ�����ƣ�����ɫ���ƣ��ı����ƣ��߿���ơ���������������PaintBkColor��PaintBkImage��PaintStatusImage��PaintText��PaintBorder�Ⱥ�������ɸ������Ʋ��衣��������Ը���������������дDoPaint����ֻ��дĳ����PaintXXX������DoPaint����������DoEvent�������ʹ�ã�DoEvent�õ���ĳ����Ϣ�󣬸ı�ؼ���״̬��Ȼ�����Invalidate�����ÿؼ��ػ�
virtual void PaintBkColor(HDC hDC);
virtual void PaintBkImage(HDC hDC);
virtual void PaintStatusImage(HDC hDC);
virtual void PaintText(HDC hDC);
virtual void PaintBorder(HDC hDC);                       //��DoPaint�������ʹ��
virtual void DoInit();                                   //���ؼ�����ӵ����������������õĺ��������������Duilib�������Ѿ���ɣ�����Ҫ��һЩ����ĳ�ʼ����ʱ������д�˺������������÷������ڴ˽���Win32�Ӵ��岢�ҷ�װ��������������ں�����˵��
virtual void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);  //������չ�Զ���ؼ������ԣ��Ӹ��ؼ��̳���һЩ���ԣ����Ҫ���������ԣ��������Զ���ؼ������ԣ�������Ҫ��д�˺�������չ����
virtual bool IsVisible() const;
virtual void SetVisible(bool bVisible = true);
virtual void SetInternVisible(bool bVisible = true); // �����ڲ����ã���ЩUIӵ�д��ھ������Ҫ��д�˺���
virtual void SetPos(RECT rc);                           //�⼸��������DoInit���ƣ����ؼ���װ��Win32�Ӵ��ں���д�⼸�������������Ӵ��ڵ���ʾ�����ء���λ�á�
*/

#endif