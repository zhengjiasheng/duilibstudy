
class CImgSwitchWnd : public CWindowWnd, public INotifyUI
{
public:
	CImgSwitchWnd();
	~CImgSwitchWnd();

	 LPCTSTR GetWindowClassName() const; 
    UINT GetClassStyle() const;
    void OnFinalMessage(HWND /*hWnd*/);

	void Notify(TNotifyUI& msg);
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled);
	LRESULT OnNcActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled);
	LRESULT OnNcCalcSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled);
	LRESULT OnNcPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

private:
	CPaintManagerUI m_pm;
};
