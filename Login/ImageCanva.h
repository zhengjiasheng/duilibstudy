#ifndef _IMAGE_CANVA_
#define _IMAGE_CANVA_
#include<fstream>
#include "json_utils.h"
#include "UICustomCanvas.h"

class RWFile;

//////////////////////////////////////////////////ImageCanvaFrame类
/*
m_hWnd = m_PaintManager.GetPaintDC() 窗口句柄
*/
class ImageCanvaFrame : public WindowImplBase
{
public:
	ImageCanvaFrame();
	~ImageCanvaFrame();

public:
	static const LPCTSTR kClassName;                                                         
	static const LPCTSTR kMainWndFrame;   

protected:
	virtual CDuiString GetSkinFolder() override;                                            
	virtual CDuiString GetSkinFile() override;                                               
	virtual LPCTSTR GetWindowClassName(void) const override;   

	virtual void InitWindow();                                                              
	virtual void Notify(TNotifyUI &msg);                                                    
	virtual LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);   
	virtual LRESULT OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);   //系统控制菜单消息WM_SYSCOMMAND的回调，该消息可以获得最大最小化、关闭等消息，重写这个函数，可以处理这些消息，即该函数可以作为最大最小化、关闭等消息的回调函数
	virtual LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	virtual CControlUI* CreateControl(LPCTSTR pstrClass);
	void OnClick(TNotifyUI &msg);                                                                                   

private:
	void cutLastBk();
	void cutNextBk();
	void handleMouseDown(UINT uMsg, WPARAM wParam, LPARAM lParam);
	void handleMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam);
	void handleMouseUp(UINT uMsg, WPARAM wParam, LPARAM lParam);
	BOOL isCanvaArea(POINT pt);
	void OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam);
	string lineListToString(vector<Line> lList);
	string getKeyValue(std::string sKey, std::string sValue);
	string getKeyValue(std::string sKey, int iValue);
	vector<Line> lineListToVector(string sList);

private:
	vector<string> m_vBkImgList;
	int m_iBkImgIndex;
	CCustomCanvasUI * m_pCanva;
	CButtonUI * m_pLastImg;
	CButtonUI * m_pNextImg;
	CButtonUI * m_pClearLine;
	BOOL m_bIsDrawLine;
	SIZE m_sInitialClientSize;
	RWFile * m_rwFile;
};

//////////////////////////////////////////////////////////RWFile类

class RWFile
{
public:
	RWFile();
	~RWFile();

	string readString(string fileName);
	void writeString(string fileName,string data);

private:

};


#endif