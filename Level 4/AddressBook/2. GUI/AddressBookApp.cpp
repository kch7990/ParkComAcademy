#include "AddressBookApp.h"
#include "UpdatingForm.h"

BOOL AddressBookApp::InitInstance() {
	UpdatingForm updatingForm;

	this->m_pMainWnd = &updatingForm;
	updatingForm.DoModal();

	return TRUE;
}
AddressBookApp addressBookApp;