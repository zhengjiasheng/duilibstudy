#include "stdafx.h"
#include "UICustomCanvas.h"
#include <atlconv.h>

CCustomCanvasUI::CCustomCanvasUI() : m_bInitialPaint(true),m_bMouseDown(false)
{
	m_sInitialCanvasSize.cx = m_sInitialCanvasSize.cy = m_sOriginPoint.cx = 0;
	m_sCurrentCanvasSize.cx = m_sCurrentCanvasSize.cy = m_sOriginPoint.cy = 0;
	m_lCurrentLine.clear();
	m_vLineList.clear();
}

CCustomCanvasUI::~CCustomCanvasUI()
{
	
}

LPCTSTR CCustomCanvasUI::GetClass() const
{
	return CCustomCanvasClassName;
}

LPVOID CCustomCanvasUI::GetInterface(LPCTSTR pstrName)
{
	if (_tcscmp(pstrName, CCustomCanvasInterface) == 0) return static_cast<CCustomCanvasUI*>(this);              //_tcscmp(string,string) 比较字符串是否相等（忽略大小写） 返回0，表示相等
	return CControlUI::GetInterface(pstrName);
}


void CCustomCanvasUI::DoEvent(TEventUI& event)
{
	switch (event.Type)
	{
	case UIEVENT_BUTTONDOWN:
		{
		m_bMouseDown = true;
		m_sCurrentCanvasSize.cx = this->GetWidth();
		m_sCurrentCanvasSize.cy = this->GetHeight();
		this->addPointToLine(event.ptMouse);
		break;
		}
	case UIEVENT_MOUSEMOVE:
		if (m_bMouseDown)
		{
			RECT rect = this->GetPos();
			if (event.ptMouse.x >= rect.left && event.ptMouse.x <= rect.right && event.ptMouse.y >= rect.top && event.ptMouse.y <= rect.bottom)
			{
				this->addPointToLine(event.ptMouse);
				Invalidate();
			}else
			{
				m_bMouseDown = false;
				this->addLineToList(m_lCurrentLine);
			}
			
		}
		break;
	case UIEVENT_BUTTONUP:
		m_bMouseDown = false;
		this->addLineToList(m_lCurrentLine);
		break;
	default:
		break;
	}
	CControlUI::DoEvent(event);
}

void CCustomCanvasUI::SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue)
{
	CControlUI::SetAttribute(pstrName, pstrValue);
}

bool CCustomCanvasUI::DoPaint(HDC hDC, const RECT& rcPaint, CControlUI* pStopControl)
{
	bool ret = CControlUI::DoPaint(hDC, rcPaint, pStopControl);

	RECT rect = this->GetPos();
	int canvasWidth = this->GetWidth();
	int canvasHeight = this->GetHeight();
	if (m_bInitialPaint)
	{
		m_sInitialCanvasSize.cx = m_sCurrentCanvasSize.cx = canvasWidth;
		m_sInitialCanvasSize.cy = m_sCurrentCanvasSize.cy = canvasHeight;
		m_sOriginPoint.cx = rect.left;
		m_sOriginPoint.cy = rect.top;
		m_bInitialPaint = false;
	}
	m_sCurrentCanvasSize.cx = this->GetWidth();
	m_sCurrentCanvasSize.cy = this->GetHeight();

	if ( m_vLineList.size() != 0)              //重绘     
	{
		for (int i = 0; i < m_vLineList.size(); i++)
		{
			this->drawLine(hDC,m_vLineList[i]);
		}
	}

	if (m_lCurrentLine.size() != 0 && m_lCurrentLine.size() != 1)
	{
		this->drawLine(hDC,m_lCurrentLine);
	}

	return ret;
}

void CCustomCanvasUI::DoInit()
{

}

void CCustomCanvasUI::SetEnabled(bool enable)
{
	CControlUI::SetEnabled(enable);
}


void CCustomCanvasUI::addPointToLine(POINT curPoint)
{
	POINT initPoint = this->CurrentToInitial(curPoint);
	m_lCurrentLine.push_back(initPoint);
}

void CCustomCanvasUI::addLineToList(Line curLine)
{
	if (m_lCurrentLine.size() != 0 && m_lCurrentLine.size() != 1)
	{
		m_vLineList.push_back(curLine);
	}
	this->clearCurrentLine();
}

void CCustomCanvasUI::clearCurrentLine()
{
	m_lCurrentLine.swap(Line());
}

void CCustomCanvasUI::clearLineList()
{
	m_vLineList.swap(vector<Line>());
	Invalidate();
}

void CCustomCanvasUI::drawLine(HDC hdc,Line line)
{
	POINT curPoint;
	curPoint = this->InitialToCurrent(line[0]);
	MoveToEx(hdc,curPoint.x,curPoint.y,NULL);
	for (int i = 1; i < line.size(); i++)
	{
		curPoint = this->InitialToCurrent(line[i]);
		LineTo(hdc,curPoint.x,curPoint.y);
	}
}

POINT CCustomCanvasUI::InitialToCurrent(POINT point)
{
	RECT rect = this->GetPos();
	point.x = point.x + (rect.left - m_sOriginPoint.cx);
	point.y = point.y + (rect.top - m_sOriginPoint.cy);
	double scale_X = (double)m_sCurrentCanvasSize.cx / (double)m_sInitialCanvasSize.cx;
	double scale_Y = (double)m_sCurrentCanvasSize.cy / (double)m_sInitialCanvasSize.cy;
	point.x = (point.x-rect.left) * scale_X + rect.left;
	point.y = (point.y-rect.top) * scale_Y + rect.top;
	return point;
}

POINT CCustomCanvasUI::CurrentToInitial(POINT point)
{
	RECT rect = this->GetPos();
	double scale_X = (double)m_sCurrentCanvasSize.cx / (double)m_sInitialCanvasSize.cx;
	double scale_Y = (double)m_sCurrentCanvasSize.cy / (double)m_sInitialCanvasSize.cy;
	point.x = (point.x-rect.left) / scale_X + rect.left;
	point.y = (point.y-rect.top) / scale_Y + rect.top;
	point.x = point.x + (m_sOriginPoint.cx - rect.left);
	point.y = point.y + (m_sOriginPoint.cy - rect.top);
	return point;
}

vector<Line> CCustomCanvasUI::getLineList()
{
	return m_vLineList;
}

void CCustomCanvasUI::setLineList(vector<Line> lineList)
{
	m_vLineList = lineList;
}