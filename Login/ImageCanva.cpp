#include "stdafx.h"
#include "ImageCanva.h"

vector<string> split(string str,string pattern)
{
	string::size_type pos;
	vector<string> result;
	str+=pattern;//扩展字符串以方便操作
	int size=str.size();

	for(int i=0; i<size; i++)
	{
		pos=str.find(pattern,i);
		if(pos<size)
		{
			string s=str.substr(i,pos-i);
			result.push_back(s);
			i=pos+pattern.size()-1;
		}
	}
	return result;
}

const LPCTSTR ImageCanvaFrame::kClassName = _T("图片画布");                 
const LPCTSTR ImageCanvaFrame::kMainWndFrame = _T("imagecanva.xml");    

//////////////////////////////////////////////ImageCanvaFrame类

DuiLib::CDuiString ImageCanvaFrame::GetSkinFolder()
{
	return m_PaintManager.GetInstancePath();
}

DuiLib::CDuiString ImageCanvaFrame::GetSkinFile()
{
	return kMainWndFrame;
}

LPCTSTR ImageCanvaFrame::GetWindowClassName(void) const
{
	return kClassName;
}

ImageCanvaFrame::ImageCanvaFrame()
{
	m_pCanva = nullptr;
	m_pLastImg = nullptr;
	m_pNextImg = nullptr;
	m_pClearLine = nullptr;
	m_rwFile = new RWFile();
	m_iBkImgIndex = 0;
	m_vBkImgList.push_back("scenery10.jpeg");
	m_vBkImgList.push_back("scenery11.jpeg");
	m_vBkImgList.push_back("scenery13.jpeg");
	m_vBkImgList.push_back("scenery16.jpeg");
	m_vBkImgList.push_back("scenery19.jpeg");
	m_bIsDrawLine = false;
}

ImageCanvaFrame::~ImageCanvaFrame()
{
	delete m_rwFile;
}

void ImageCanvaFrame::InitWindow()
{
	m_pCanva = dynamic_cast<CCustomCanvasUI *>(m_PaintManager.FindControl(_T("canvacontrol")));
	m_pLastImg = dynamic_cast<CButtonUI *>(m_PaintManager.FindControl(_T("lastimg")));
	m_pNextImg = dynamic_cast<CButtonUI *>(m_PaintManager.FindControl(_T("nextimg")));
	m_pClearLine = dynamic_cast<CButtonUI *>(m_PaintManager.FindControl(_T("clearline")));
	//m_sInitialClientSize = m_PaintManager.GetClientSize();

	m_pCanva->SetBkImage(m_vBkImgList[m_iBkImgIndex].c_str());
	string rFileName = split(m_vBkImgList[m_iBkImgIndex],".")[0] + ".txt";
	string lineData = m_rwFile->readString("resource/lineData/" + rFileName);
	if (!lineData.empty())
	{
		vector<Line> list = this->lineListToVector(lineData);
		m_pCanva->setLineList(list);
	}
}

CControlUI* ImageCanvaFrame::CreateControl(LPCTSTR pstrClass)
{
	if (_tcsicmp(pstrClass,CCustomCanvasInterface) == 0)
		return new CCustomCanvasUI();

	return NULL;
}

LRESULT ImageCanvaFrame::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (uMsg == WM_CLOSE)
	{
		PostQuitMessage(0L);
	}
	return __super::OnClose(uMsg,wParam,lParam,bHandled);
}

LRESULT ImageCanvaFrame::OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	//拦截系统控制菜单消息
	return __super::OnSysCommand(uMsg,wParam,lParam,bHandled);
}

LRESULT ImageCanvaFrame::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	//拦截窗口大小改变触发的消息
	return __super::OnSize(uMsg,wParam,lParam,bHandled);	
}

void ImageCanvaFrame::OnClick(TNotifyUI & msg)
{
	CDuiString sCtrlName = msg.pSender->GetName();
	if (sCtrlName == _T("closebtn")){
		Close();  
	}else if (sCtrlName == _T("minbtn"))
	{
		SendMessage(WM_SYSCOMMAND,SC_MINIMIZE,0);
	}else if (sCtrlName == _T("maxbtn"))
	{
		SendMessage(WM_SYSCOMMAND,SC_MAXIMIZE,0);
	}else if (sCtrlName == _T("restorebtn"))
	{
		SendMessage(WM_SYSCOMMAND,SC_RESTORE,0);
	}else if (sCtrlName == m_pLastImg->GetName())
	{
		this->cutLastBk();
	}else if (sCtrlName == m_pNextImg->GetName())
	{
		this->cutNextBk();
	}else if (sCtrlName == m_pClearLine->GetName())
	{
		m_pCanva->clearLineList();
	}
	return;
}

void ImageCanvaFrame::Notify(TNotifyUI &msg)
{
	__super::Notify(msg);  
}

LRESULT ImageCanvaFrame::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//lRes用来保存这里的消息处理返回的结果
	LRESULT lRes = 0;
	//bHandled用来作条件判断，判断消息在这里处理之后，是否直接返回，不交给基类的HandleMessage处理了  通常在这里处理的消息（拦截）处理之后可能不交给基类处理，也可能交给基类处理，这需要视情况而定，而一般这里不处理的消息，都需要交给基类的HandleMessage来处理。
	BOOL bHandled = TRUE;

	switch (uMsg)
	{
	case WM_LBUTTONDOWN: 
		this->handleMouseDown(uMsg,wParam,lParam);
		break;
	case WM_MOUSEMOVE:
		this->handleMouseMove(uMsg,wParam,lParam);
		break;
	case WM_LBUTTONUP:
		this->handleMouseUp(uMsg,wParam,lParam);
		break;
	//case WM_PAINT:
	//	OnPaint(uMsg,wParam,lParam);
	//	break;
	default:
		break;
	}
	
	return __super::HandleMessage(uMsg, wParam, lParam);
}


void ImageCanvaFrame::cutLastBk()
{
	if (m_iBkImgIndex > 0)
	{
		vector<Line> vlineList =  m_pCanva->getLineList();
		string strLineList = this->lineListToString(vlineList);
		m_pCanva->clearLineList();
		string wFileName = split(m_vBkImgList[m_iBkImgIndex],".")[0] + ".txt";
		m_rwFile->writeString("resource/lineData/" + wFileName,strLineList);
		m_iBkImgIndex--;
		string rFileName = split(m_vBkImgList[m_iBkImgIndex],".")[0] + ".txt";
		string lineData = m_rwFile->readString("resource/lineData/" + rFileName);
		if (!lineData.empty())
		{
			vector<Line> list = this->lineListToVector(lineData);
			m_pCanva->setLineList(list);
		}
		m_pCanva->SetBkImage(m_vBkImgList[m_iBkImgIndex].c_str());
	}
}

void ImageCanvaFrame::cutNextBk()
{
	if (m_iBkImgIndex < m_vBkImgList.size()-1)
	{
		vector<Line> vlineList =  m_pCanva->getLineList();
		string strLineList = this->lineListToString(vlineList);
		m_pCanva->clearLineList();
		string wFileName = split(m_vBkImgList[m_iBkImgIndex],".")[0] + ".txt";
		m_rwFile->writeString("resource/lineData/" + wFileName,strLineList);
		m_iBkImgIndex++;
		string rFileName = split(m_vBkImgList[m_iBkImgIndex],".")[0] + ".txt";
		string lineData = m_rwFile->readString("resource/lineData/" + rFileName);
		if (!lineData.empty())
		{
			vector<Line> list = this->lineListToVector(lineData);
			m_pCanva->setLineList(list);
		}
		m_pCanva->SetBkImage(m_vBkImgList[m_iBkImgIndex].c_str());
	}
}

void ImageCanvaFrame::handleMouseDown(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	POINT pt = { GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam) };
	if (this->isCanvaArea(pt))
	{
		m_bIsDrawLine = true;
	} 
}

void ImageCanvaFrame::handleMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	POINT pt = { GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam) };
	if (m_bIsDrawLine)
	{
		if (this->isCanvaArea(pt))
		{
			
		}else
		{
			m_bIsDrawLine = false;
		} 
	}
}

void ImageCanvaFrame::handleMouseUp(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	m_bIsDrawLine = false;
}

BOOL ImageCanvaFrame::isCanvaArea(POINT pt)
{
	LONG min_X,min_Y,max_X,max_Y;
	SIZE clientSize = m_PaintManager.GetClientSize();
	min_X = 20;
	max_X = clientSize.cx - 20;
	min_Y = 55;
	max_Y = clientSize.cy - 60;
	if (pt.x >= min_X && pt.x <= max_X && pt.y >= min_Y && pt.y <= max_Y)
	{
		return true;
	}else
	{
		return false;
	}
}


void ImageCanvaFrame::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT pt;
    HDC hdc;
    hdc=BeginPaint(m_hWnd,&pt);

	SIZE clientSize = m_PaintManager.GetClientSize();
	Rectangle(hdc,20,55,clientSize.cx - 40,clientSize.cy - 60);

    EndPaint(m_hWnd, &pt);
}

string ImageCanvaFrame::lineListToString(vector<Line> lList)
{
	string strLineList = "";
	strLineList += "{\"lines\":[";
	for (int i = 0; i < lList.size(); i++)
	{
		strLineList += "{\"line\":\"";
		for (int j = 0; j < lList[i].size(); j++)
		{
			char szValue[50] = { 0 };  
			strLineList += "";
			sprintf(szValue, "%d", lList[i][j].x);
			strLineList.append(szValue);
			strLineList += ",";
			memset(szValue,0,sizeof(szValue));
			sprintf(szValue, "%d", lList[i][j].y);
			strLineList.append(szValue);
			if (j != lList[i].size() -1)
				strLineList += "|";
		}
		if (i == lList.size()-1)
		{
			strLineList += "\"}";
		}else
		{
			strLineList += "\"},";
		}
	}
	strLineList += "]}";
	return strLineList;
}

vector<Line> ImageCanvaFrame::lineListToVector(string strLineList)
{
	CJsonReader reader;
	vector<Line> vLineList;
	if (reader.parse(strLineList))
	{
		int i = 0;
		while (reader.getParam("lines","line",i) != "")
		{
			vector<POINT> vLine;
			string strLine = reader.getParam("lines","line",i);
			vector<string> vsLine = split(strLine,"|");
			for (int j = 0; j < vsLine.size(); j++)
			{
				POINT point;
				vector<string> vsPoint = split(vsLine[j],",");
				point.x = stoi(vsPoint[0]);
				point.y = stoi(vsPoint[1]);
				vLine.push_back(point);
			}
			vLineList.push_back(vLine);
			i++;
		}	
	}
	return vLineList;
}

string ImageCanvaFrame::getKeyValue(std::string sKey, std::string sValue){    
	char szDoubleQutoes[] = "\"";    
	char szColon[] = ":";   
	string strResult;

    strResult.append(szDoubleQutoes);
    strResult.append(sKey);
    strResult.append(szDoubleQutoes);

    strResult.append(szColon);
    strResult.append(szDoubleQutoes);
    strResult.append(sValue);
    strResult.append(szDoubleQutoes);   
	return strResult;
}

string ImageCanvaFrame::getKeyValue(std::string sKey, int iValue){   
	char szDoubleQutoes[] = "\"";  
	char szColon[] = ":";    
	char szValue[50] = { 0 };   
	string strResult;

    strResult.append(szDoubleQutoes);
    strResult.append(sKey);
    strResult.append(szDoubleQutoes);

    strResult.append(szColon);    
	sprintf(szValue, "%d", iValue);
    strResult.append(szValue);    
	return strResult;
}


//////////////////////////////////////////RWFile类
RWFile::RWFile()
{

}
RWFile::~RWFile()
{

}

string RWFile::readString(string fileName)
{
	ifstream ifs;
	ifs.open(fileName,ios::in | ios::binary);
	if (!ifs.is_open())
	{
		return "";
	}
	string data;
	ifs >> data;
	ifs.close();
	return data;
}

void RWFile::writeString(string fileName,string data)
{
	ofstream ofs;
	ofs.open(fileName,ios::out | ios::binary);
	ofs << data;
	ofs.close();
}