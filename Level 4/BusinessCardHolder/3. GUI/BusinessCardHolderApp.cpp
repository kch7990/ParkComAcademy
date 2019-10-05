#include "BusinessCardHolderApp.h"
#include "BusinessCardHolderForm.h"

BOOL BusinessCardHolderApp::InitInstance() {
	BusinessCardHolderForm businessCardHolderForm;
	this->m_pMainWnd = &businessCardHolderForm;
	businessCardHolderForm.DoModal();

	return TRUE;
}
BusinessCardHolderApp businessCardHolderApp;