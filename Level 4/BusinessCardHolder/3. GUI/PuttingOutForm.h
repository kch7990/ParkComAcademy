#ifndef _PUTTIONOUTFORM
#define _PUTTIONOUTFORM

#include <afxwin.h>
#include "resource.h"

class PuttingOutForm : public CDialog
{
public:
	enum { IDD = IDD_PUTTINGOUTFORM };

public:
	PuttingOutForm(CWnd *parent = NULL);
	virtual BOOL OnInitDialog();

protected:
	afx_msg void OnClose();
	DECLARE_MESSAGE_MAP()
};

#endif // !_PUTTIONOUTFORM
