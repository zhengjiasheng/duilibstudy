////////////////////////////////////////////////////Duilib自定义控件--画布
#ifndef _UI_CUSTOM_CANVAS_H_
#define _UI_CUSTOM_CANVAS_H_
#pragma once

#include "DuiLib\UIlib.h"
using namespace DuiLib;

typedef vector<POINT> Line;
//类名和接口名，在CreateControl函数中会用到
const TCHAR CCustomCanvasClassName[] =	_T("CustomCanvasUI");
const TCHAR CCustomCanvasInterface[] =	_T("CustomCanvas");

class CCustomCanvasUI : public CControlUI
{
public:
	CCustomCanvasUI();
	~CCustomCanvasUI();

	//用来区分控件的类型的虚函数，用于动态识别控件类型和做控件的类型转换
	LPCTSTR GetClass() const;                                 //控件类名：CCustomCanvasClassName：CustomCanvaUI 用于代码中判断
	LPVOID GetInterface(LPCTSTR pstrName);                    //控件接口名：CCustomCanvasInterface：CustomCanvas 用于xml文件中控件标签

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
	bool m_bInitialPaint;                         //是否是初始绘制
	SIZE m_sInitialCanvasSize;                    //初始画布大小
	SIZE m_sOriginPoint;                          //坐标原点
	SIZE m_sCurrentCanvasSize;                    //当前画布大小
	bool m_bMouseDown;                            //鼠标是否按下
	Line m_lCurrentLine;                          //当前正在绘制的线
	vector<Line> m_vLineList;                     //绘制的全部线
};

/*
自定义控件经常重写的函数：
LPCTSTR GetClass() const;                                //控件类名：CCustomCanvasClassName：CustomCanvaUI 用于代码中判断
LPVOID GetInterface(LPCTSTR pstrName);                   //控件接口名：CCustomCanvasInterface：CustomCanvas 用于xml文件中控件标签
virtual void DoEvent(TEventUI& event);                   //消息处理函数，用来处理Duilib封装过的各个消息，比如鼠标的移入移出、出现的悬停、单击双击、右击、获取焦点、设置光标等等
virtual void DoPaint(HDC hDC, const RECT& rcPaint);      //控件的绘制处理函数，当Duilib底层要重新绘制这个控件，或者控件自己调用Invalidata函数强制自己刷新时，这个函数就会被触发，在这个函数里完成了各种状态下的背景前景绘制，背景色绘制，文本绘制，边框绘制。而这个函数会调用PaintBkColor、PaintBkImage、PaintStatusImage、PaintText、PaintBorder等函数来完成各个绘制步骤。所以你可以根据需求来决定重写DoPaint或者只重写某几个PaintXXX函数。DoPaint函数经常和DoEvent函数结合使用，DoEvent得到了某个消息后，改变控件的状态，然后调用Invalidate函数让控件重绘
virtual void PaintBkColor(HDC hDC);
virtual void PaintBkImage(HDC hDC);
virtual void PaintStatusImage(HDC hDC);
virtual void PaintText(HDC hDC);
virtual void PaintBorder(HDC hDC);                       //和DoPaint函数配合使用
virtual void DoInit();                                   //当控件被添加到容器后，由容器调用的函数。在这里，整个Duilib程序框架已经完成，当需要做一些界面的初始操作时可以重写此函数，常见的用法就是在此建立Win32子窗体并且封装它，相关内容我在后面再说。
virtual void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);  //用于扩展自定义控件的属性，从父控件继承了一些属性，如果要增加新属性（独属于自定义控件的属性），就需要重写此函数来扩展属性
virtual bool IsVisible() const;
virtual void SetVisible(bool bVisible = true);
virtual void SetInternVisible(bool bVisible = true); // 仅供内部调用，有些UI拥有窗口句柄，需要重写此函数
virtual void SetPos(RECT rc);                           //这几个函数和DoInit类似，当控件封装了Win32子窗口后，重写这几个函数来控制子窗口的显示和隐藏、和位置。
*/

#endif