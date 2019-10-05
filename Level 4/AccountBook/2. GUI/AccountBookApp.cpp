#include "AccountBookApp.h"
#include "AccountBookForm.h"

BOOL AccountBookApp::InitInstance() {
	AccountBookForm accountBookForm;
	this->m_pMainWnd = &accountBookForm;
	accountBookForm.DoModal();

	return TRUE;
}
AccountBookApp accountBookApp;
