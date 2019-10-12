#include "NeuronApp.h"
#include "NeuronForm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BOOL NeuronApp::InitInstance() {
	NeuronForm *neuronForm = new NeuronForm;
	neuronForm->Create(NULL, "´º·±", WS_BORDER | WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU , CRect(160, 50, 1760, 1000));
	neuronForm->ShowWindow(SW_SHOWNORMAL);
	neuronForm->UpdateWindow();
	this->m_pMainWnd = neuronForm;

	return TRUE;
}

NeuronApp neuronApp;