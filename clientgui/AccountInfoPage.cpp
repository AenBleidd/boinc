// This file is part of BOINC.
// https://boinc.berkeley.edu
// Copyright (C) 2025 University of California
//
// BOINC is free software; you can redistribute it and/or modify it
// under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation,
// either version 3 of the License, or (at your option) any later version.
//
// BOINC is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with BOINC.  If not, see <https://www.gnu.org/licenses/>.

#if defined(__GNUG__) && !defined(__APPLE__)
#pragma implementation "AccountInfoPage.h"
#endif

#include "stdwx.h"
#include "diagnostics.h"
#include "util.h"
#include "mfile.h"
#include "miofile.h"
#include "parse.h"
#include "error_numbers.h"
#include "wizardex.h"
#include "error_numbers.h"
#include "BOINCGUIApp.h"
#include "SkinManager.h"
#include "MainDocument.h"
#include "wx/valgen.h"
#include "wx/valtext.h"
#include "ValidateEmailAddress.h"
#include "BOINCBaseWizard.h"
#include "WizardAttach.h"
#include "ProjectInfoPage.h"
#include "AccountManagerInfoPage.h"
#include "AccountInfoPage.h"


/*!
 * CAccountInfoPage type definition
 */

IMPLEMENT_DYNAMIC_CLASS( CAccountInfoPage, wxWizardPageEx )

/*!
 * CAccountInfoPage event table definition
 */

BEGIN_EVENT_TABLE( CAccountInfoPage, wxWizardPageEx )

////@begin CAccountInfoPage event table entries
    EVT_WIZARDEX_PAGE_CHANGED( wxID_ANY, CAccountInfoPage::OnPageChanged )
    EVT_WIZARDEX_PAGE_CHANGING( wxID_ANY, CAccountInfoPage::OnPageChanging )
    EVT_WIZARDEX_CANCEL( wxID_ANY, CAccountInfoPage::OnCancel )
    EVT_RADIOBUTTON( ID_ACCOUNTCREATECTRL, CAccountInfoPage::OnAccountCreateCtrlSelected )
    EVT_RADIOBUTTON( ID_ACCOUNTUSEEXISTINGCTRL, CAccountInfoPage::OnAccountUseExistingCtrlSelected )
////@end CAccountInfoPage event table entries

END_EVENT_TABLE()

/*!
 * CAccountInfoPage constructors
 */

CAccountInfoPage::CAccountInfoPage( )
{
}

CAccountInfoPage::CAccountInfoPage( CBOINCBaseWizard* parent )
{
    Create( parent );
}

/*!
 * AccountInfoPage creator
 */

bool CAccountInfoPage::Create( CBOINCBaseWizard* parent )
{

////@begin CAccountInfoPage member initialisation
    m_pTitleStaticCtrl = NULL;
    m_pAccountQuestionStaticCtrl = NULL;
    m_pAccountInformationStaticCtrl = NULL;
    m_pAccountCreateCtrl = NULL;
    m_pAccountUseExistingCtrl = NULL;
    m_pAccountEmailAddressStaticCtrl = NULL;
    m_pAccountEmailAddressCtrl = NULL;
    m_pAccountPasswordStaticCtrl = NULL;
    m_pAccountPasswordCtrl = NULL;
    m_pAccountConfirmPasswordStaticCtrl = NULL;
    m_pAccountConfirmPasswordCtrl = NULL;
    m_pAccountPasswordRequirmentsStaticCtrl = NULL;
    m_pAccountManagerLinkLabelStaticCtrl = NULL;
    m_pAccountForgotPasswordCtrl = NULL;
////@end CAccountInfoPage member initialisation

////@begin CAccountInfoPage creation
    wxWizardPageEx::Create( parent, ID_ACCOUNTINFOPAGE );

    CreateControls();
    GetSizer()->Fit(this);
////@end CAccountInfoPage creation

    return TRUE;
}

/*!
 * Control creation for AccountInfoPage
 */

void CAccountInfoPage::CreateControls()
{

////@begin CAccountInfoPage content construction
    CAccountInfoPage* itemWizardPage56 = this;

    wxBoxSizer* itemBoxSizer57 = new wxBoxSizer(wxVERTICAL);
    itemWizardPage56->SetSizer(itemBoxSizer57);

    m_pTitleStaticCtrl = new wxStaticText;
    m_pTitleStaticCtrl->Create( itemWizardPage56, wxID_STATIC, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    m_pTitleStaticCtrl->SetFont(wxFont(10, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, FALSE, _T("Verdana")));
    itemBoxSizer57->Add(m_pTitleStaticCtrl, 0, wxALIGN_LEFT|wxGROW|wxALL, 5);

    m_pAccountQuestionStaticCtrl = new wxStaticText;
    m_pAccountQuestionStaticCtrl->Create( itemWizardPage56, wxID_STATIC, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer57->Add(m_pAccountQuestionStaticCtrl, 0, wxALIGN_LEFT|wxALL, 5);

    wxFlexGridSizer* itemFlexGridSizer61 = new wxFlexGridSizer(1, 2, 0, 0);
    itemFlexGridSizer61->AddGrowableCol(1);
    itemBoxSizer57->Add(itemFlexGridSizer61, 0, wxGROW|wxALL, 5);

    m_pAccountCreateCtrl = new wxRadioButton;
    m_pAccountCreateCtrl->Create( itemWizardPage56, ID_ACCOUNTCREATECTRL, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxRB_GROUP );
    m_pAccountCreateCtrl->SetValue(TRUE);
    itemFlexGridSizer61->Add(m_pAccountCreateCtrl, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_pAccountUseExistingCtrl = new wxRadioButton;
    m_pAccountUseExistingCtrl->Create( itemWizardPage56, ID_ACCOUNTUSEEXISTINGCTRL, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    m_pAccountUseExistingCtrl->SetValue(FALSE);
    itemFlexGridSizer61->Add(m_pAccountUseExistingCtrl, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_pAccountInformationStaticCtrl = new wxStaticText;
    m_pAccountInformationStaticCtrl->Create( itemWizardPage56, wxID_STATIC, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer57->Add(m_pAccountInformationStaticCtrl, 0, wxALIGN_LEFT|wxALL, 5);

    wxFlexGridSizer* itemFlexGridSizer64 = new wxFlexGridSizer(2, 0, 0);
    itemFlexGridSizer64->AddGrowableCol(1);
    itemBoxSizer57->Add(itemFlexGridSizer64, 0, wxEXPAND|wxALL, 0);

    m_pAccountEmailAddressStaticCtrl = new wxStaticText;
    m_pAccountEmailAddressStaticCtrl->Create( itemWizardPage56, ID_ACCOUNTEMAILADDRESSSTATICCTRL, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer64->Add(m_pAccountEmailAddressStaticCtrl, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_pAccountEmailAddressCtrl = new wxTextCtrl;
    m_pAccountEmailAddressCtrl->Create( itemWizardPage56, ID_ACCOUNTEMAILADDRESSCTRL, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer64->Add(m_pAccountEmailAddressCtrl, 0, wxEXPAND|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_pAccountUsernameStaticCtrl = new wxStaticText;
    m_pAccountUsernameStaticCtrl->Create( itemWizardPage56, ID_ACCOUNTUSERNAMESTATICCTRL, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer64->Add(m_pAccountUsernameStaticCtrl, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_pAccountUsernameCtrl = new wxTextCtrl;
    m_pAccountUsernameCtrl->Create( itemWizardPage56, ID_ACCOUNTUSERNAMECTRL, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer64->Add(m_pAccountUsernameCtrl, 0, wxEXPAND|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_pAccountPasswordStaticCtrl = new wxStaticText;
    m_pAccountPasswordStaticCtrl->Create( itemWizardPage56, ID_ACCOUNTPASSWORDSTATICCTRL, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer64->Add(m_pAccountPasswordStaticCtrl, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_pAccountPasswordCtrl = new wxTextCtrl;
    m_pAccountPasswordCtrl->Create( itemWizardPage56, ID_ACCOUNTPASSWORDCTRL, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD );
    itemFlexGridSizer64->Add(m_pAccountPasswordCtrl, 0, wxEXPAND|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_pAccountConfirmPasswordStaticCtrl = new wxStaticText;
    m_pAccountConfirmPasswordStaticCtrl->Create( itemWizardPage56, ID_ACCOUNTCONFIRMPASSWORDSTATICCTRL, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer64->Add(m_pAccountConfirmPasswordStaticCtrl, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_pAccountConfirmPasswordCtrl = new wxTextCtrl;
    m_pAccountConfirmPasswordCtrl->Create( itemWizardPage56, ID_ACCOUNTCONFIRMPASSWORDCTRL, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD );
    itemFlexGridSizer64->Add(m_pAccountConfirmPasswordCtrl, 0, wxEXPAND|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    itemFlexGridSizer64->Add( 0, 0 );

    m_pAccountPasswordRequirmentsStaticCtrl = new wxStaticText;
    m_pAccountPasswordRequirmentsStaticCtrl->Create( itemWizardPage56, ID_ACCOUNTREQUIREMENTSSTATICCTRL, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    m_pAccountPasswordRequirmentsStaticCtrl->SetFont(wxFont(7, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, FALSE));
    itemFlexGridSizer64->Add(m_pAccountPasswordRequirmentsStaticCtrl, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_pAccountManagerLinkLabelStaticCtrl = new wxStaticText;
    m_pAccountManagerLinkLabelStaticCtrl->Create( itemWizardPage56, ID_ACCOUNTLINKLABELSTATICCTRL, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer57->Add(m_pAccountManagerLinkLabelStaticCtrl, 0, wxGROW|wxALL, 5);

    m_pAccountForgotPasswordCtrl = new wxHyperlinkCtrl;
    m_pAccountForgotPasswordCtrl->Create( itemWizardPage56, ID_ACCOUNTFORGOTPASSWORDCTRL, wxT(" "), wxT(" "), wxDefaultPosition, wxDefaultSize, wxNO_BORDER | wxHL_ALIGN_LEFT | wxHL_CONTEXTMENU );
    itemBoxSizer57->Add(m_pAccountForgotPasswordCtrl, 0, wxGROW|wxALL, 5);
    ////@end CAccountInfoPage content construction

}

/*!
 * Gets the previous page.
 */

wxWizardPageEx* CAccountInfoPage::GetPrev() const
{
    return PAGE_TRANSITION_BACK;
}

/*!
 * Gets the next page.
 */

wxWizardPageEx* CAccountInfoPage::GetNext() const
{
    if (CHECK_CLOSINGINPROGRESS()) {
        // Cancel Event Detected
        return PAGE_TRANSITION_NEXT(ID_COMPLETIONERRORPAGE);
    } else if (IS_ATTACHTOPROJECTWIZARD()) {
        return PAGE_TRANSITION_NEXT(ID_PROJECTPROCESSINGPAGE);
    } else if (IS_ACCOUNTMANAGERWIZARD()) {
        return PAGE_TRANSITION_NEXT(ID_ACCOUNTMANAGERPROCESSINGPAGE);
    }
    return NULL;
}

/*!
 * Should we show tooltips?
 */

bool CAccountInfoPage::ShowToolTips()
{
    return TRUE;
}

/*!
 * Get bitmap resources
 */

wxBitmap CAccountInfoPage::GetBitmapResource( const wxString& WXUNUSED(name) )
{
    // Bitmap retrieval
////@begin CAccountInfoPage bitmap retrieval
    return wxNullBitmap;
////@end CAccountInfoPage bitmap retrieval
}

/*!
 * Get icon resources
 */

wxIcon CAccountInfoPage::GetIconResource( const wxString& WXUNUSED(name) )
{
    // Icon retrieval
////@begin CAccountInfoPage icon retrieval
    return wxNullIcon;
////@end CAccountInfoPage icon retrieval
}

/*!
 * wxEVT_WIZARD_PAGE_CHANGED event handler for ID_ACCOUNTINFOPAGE
 */

void CAccountInfoPage::OnPageChanged( wxWizardExEvent& /* event */ ) {
    CWizardAttach*   pWA = ((CWizardAttach*)GetParent());
    CSkinAdvanced*   pSkinAdvanced = wxGetApp().GetSkinManager()->GetAdvanced();
    CSkinWizardATAM* pSkinWizardATAM = wxGetApp().GetSkinManager()->GetWizards()->GetWizardATAM();
    PROJECT_CONFIG&  pc = pWA->project_config;
    wxString         strBaseConfigLocation = wxString(wxT("/Wizards"));
    wxConfigBase*    pConfig = wxConfigBase::Get(FALSE);

    wxASSERT(pSkinAdvanced);
    wxASSERT(pSkinWizardATAM);
    wxASSERT(wxDynamicCast(pSkinAdvanced, CSkinAdvanced));
    wxASSERT(wxDynamicCast(pSkinWizardATAM, CSkinWizardATAM));

    pWA->EnableNextButton();

    // We are entering this page, so retrieve the previously used email
    // address and/or username.
    pConfig->SetPath(strBaseConfigLocation);
    m_strAccountEmailAddress = pConfig->Read(wxT("DefaultEmailAddress"));
    m_strAccountUsername = pConfig->Read(wxT("DefaultUsername"));

    // Setup the desired controls and default values.
    static bool bRunOnce = true;
    if (bRunOnce) {
        bRunOnce = false;
        if (!IS_ACCOUNTMANAGERWIZARD()) {
            m_pAccountCreateCtrl->SetValue(true);
            m_pAccountUseExistingCtrl->SetValue(false);
        }
    }

    if (IS_ACCOUNTMANAGERWIZARD()) {
        m_pAccountQuestionStaticCtrl->Hide();
        m_pAccountCreateCtrl->SetValue(false);
        m_pAccountCreateCtrl->Hide();
        m_pAccountUseExistingCtrl->SetValue(true);
        m_pAccountUseExistingCtrl->Hide();
        m_pAccountConfirmPasswordStaticCtrl->Hide();
        m_pAccountConfirmPasswordCtrl->Hide();
        m_pAccountPasswordRequirmentsStaticCtrl->Hide();
    } else {
        if (pc.account_creation_disabled || pc.client_account_creation_disabled) {
            m_pAccountCreateCtrl->SetValue(false);
            m_pAccountCreateCtrl->Hide();
            m_pAccountUseExistingCtrl->SetValue(true);
            m_pAccountUseExistingCtrl->Hide();
        } else {
            m_pAccountCreateCtrl->Show();
            m_pAccountCreateCtrl->Enable();
            m_pAccountUseExistingCtrl->Show();
        }
        m_pAccountManagerLinkLabelStaticCtrl->Hide();
    }

    wxString str;
    wxString name = wxString(pc.name.c_str(), wxConvUTF8);
    str.Printf(_("Identify your account at %s"),
        name.empty()? pWA->GetProjectName().c_str() : name.c_str()
            // one or the other is populated depending on how project was selected
    );
    m_pTitleStaticCtrl->SetLabel(str);

    if (!IS_ACCOUNTMANAGERWIZARD() && !IS_ACCOUNTMANAGERUPDATEWIZARD()) {
		if (pc.client_account_creation_disabled) {
			m_pAccountQuestionStaticCtrl->SetLabel(
				_("Please enter your account information\n(to create an account, visit the project's web site)")
			);
		} else if (pc.account_creation_disabled) {
			m_pAccountQuestionStaticCtrl->SetLabel(
				_("This project is not currently accepting new accounts.\nYou can add it only if you already have an account.")
			);
		} else {
			m_pAccountQuestionStaticCtrl->SetLabel(
				_("Are you already running this project?")
			);
		}
        m_pAccountCreateCtrl->SetLabel(
            _("&No, new user")
        );
        m_pAccountUseExistingCtrl->SetLabel(
            _("&Yes, existing user")
        );
    } else {
        if (pSkinAdvanced->IsBranded() &&
            !pSkinWizardATAM->GetAccountInfoMessage().IsEmpty()) {
            m_pAccountInformationStaticCtrl->SetLabel(
                pSkinWizardATAM->GetAccountInfoMessage()
            );
        }
    }

    if (m_pAccountUseExistingCtrl->GetValue()) {
        m_pAccountConfirmPasswordStaticCtrl->Hide();
        m_pAccountConfirmPasswordCtrl->Hide();
        m_pAccountPasswordRequirmentsStaticCtrl->Hide();
        m_pAccountPasswordStaticCtrl->SetLabel(
            _("&Password:")
        );
    } else {
        m_pAccountConfirmPasswordStaticCtrl->Show();
        m_pAccountConfirmPasswordCtrl->Show();
        m_pAccountPasswordRequirmentsStaticCtrl->Show();
        m_pAccountPasswordStaticCtrl->SetLabel(
            _("Choose a &password:")
        );
        m_pAccountConfirmPasswordStaticCtrl->SetLabel(
            _("C&onfirm password:")
        );
    }

    if (!pWA->GetProjectName().IsEmpty()) {
        wxString strQuestion;
        strQuestion.Printf(
            _("Are you already running %s?"),
            pWA->GetProjectName().c_str()
        );
        m_pAccountQuestionStaticCtrl->SetLabel(strQuestion);
    }

    if (pc.uses_username) {
        if (IS_ACCOUNTMANAGERWIZARD()) {
            if (pSkinAdvanced->IsBranded() &&
                !pSkinWizardATAM->GetAccountInfoMessage().IsEmpty()) {
                m_pAccountInformationStaticCtrl->SetLabel(
                    pSkinWizardATAM->GetAccountInfoMessage()
                );
            }
        }

        m_pAccountEmailAddressCtrl->SetValidator(
            wxTextValidator(wxFILTER_NONE, &m_strAccountEmailAddress)
        );
        m_pAccountUsernameCtrl->SetValidator(
            wxTextValidator(wxFILTER_ASCII, &m_strAccountUsername)
        );

        m_pAccountEmailAddressStaticCtrl->Hide();
        m_pAccountEmailAddressCtrl->Hide();
        m_pAccountUsernameStaticCtrl->Show();
        m_pAccountUsernameCtrl->Show();

        m_pAccountUsernameStaticCtrl->SetLabel(
            _("&Username:")
        );
        m_pAccountUsernameCtrl->SetValue(m_strAccountUsername);
    } else {
        if (IS_ACCOUNTMANAGERWIZARD()) {
            if (pSkinAdvanced->IsBranded() &&
                !pSkinWizardATAM->GetAccountInfoMessage().IsEmpty()) {
                m_pAccountInformationStaticCtrl->SetLabel(
                    pSkinWizardATAM->GetAccountInfoMessage()
                );
            }
        }

        if (!pc.ldap_auth) {
            m_pAccountEmailAddressCtrl->SetValidator(
                CValidateEmailAddress(&m_strAccountEmailAddress)
            );
        }
        m_pAccountUsernameCtrl->SetValidator(
            wxTextValidator(wxFILTER_NONE, &m_strAccountUsername)
        );

        m_pAccountEmailAddressStaticCtrl->Show();
        m_pAccountEmailAddressCtrl->Show();
        m_pAccountUsernameStaticCtrl->Hide();
        m_pAccountUsernameCtrl->Hide();

        if (pc.ldap_auth) {
            m_pAccountEmailAddressStaticCtrl->SetLabel(
                _("&Email address or LDAP ID:")
            );
        } else {
            m_pAccountEmailAddressStaticCtrl->SetLabel(
                _("&Email address:")
            );
        }
        m_pAccountEmailAddressCtrl->SetValue(m_strAccountEmailAddress);
    }

    if (pc.min_passwd_length) {
        wxString str2;
        str2.Printf(_("minimum length %d"), pc.min_passwd_length);
        m_pAccountPasswordRequirmentsStaticCtrl->SetLabel( str2 );
    }


    if (!IS_ACCOUNTMANAGERWIZARD()) {
        m_pAccountForgotPasswordCtrl->SetLabel(
            _("Forgot your password?")
        );
        m_pAccountForgotPasswordCtrl->SetURL(
            wxString(pWA->GetProjectURL() + _T("get_passwd.php"))
        );
    } else {
        m_pAccountManagerLinkLabelStaticCtrl->SetLabel(
            _("If you have not yet registered with this account manager,\nplease do so before proceeding.  Click on the link below\nto register or to retrieve a forgotten password." )
        );
        m_pAccountForgotPasswordCtrl->SetLabel(
            _("Account manager web site")
        );
        m_pAccountForgotPasswordCtrl->SetURL(
            wxString(pWA->GetProjectURL())
        );
    }

    if (pc.uses_username) {
        m_pAccountUsernameCtrl->SetFocus();
    } else {
        m_pAccountEmailAddressCtrl->SetFocus();
    }

    Fit();
}

/*!
 * wxEVT_WIZARD_PAGE_CHANGING event handler for ID_ACCOUNTINFOPAGE
 */

void CAccountInfoPage::OnPageChanging( wxWizardExEvent& event ) {
    if (event.GetDirection() == false) return;

    CWizardAttach*         pWA = ((CWizardAttach*)GetParent());
    PROJECT_CONFIG&        pc = pWA->project_config;
    wxString               strTitle;
    wxString               strMessage = wxT("");
    bool                   bDisplayError = false;
    wxString               strBaseConfigLocation = wxString(wxT("/Wizards"));
    wxConfigBase*          pConfig = wxConfigBase::Get(FALSE);

    if (!CHECK_CLOSINGINPROGRESS()) {
        // We are leaving this page, so store the email address for future
        // use.
        pConfig->SetPath(strBaseConfigLocation);
        pConfig->Write(wxT("DefaultEmailAddress"), m_strAccountEmailAddress);
        pConfig->Write(wxT("DefaultUsername"), m_strAccountUsername);

        pConfig->Flush();

        // Construct potential dialog title
        if (IS_ATTACHTOPROJECTWIZARD()) {
            strTitle = _("Add project");
        } else if (IS_ACCOUNTMANAGERWIZARD() && IS_ACCOUNTMANAGERUPDATEWIZARD()) {
            strTitle = _("Update account manager");
        } else if (IS_ACCOUNTMANAGERWIZARD()) {
            strTitle = _("Use account manager");
        }

        // Verify minimum username length
        if (!m_pAccountUseExistingCtrl->GetValue()) {
            if (!(m_pAccountPasswordCtrl->GetValue().Length() > 0)) {
                if (pc.uses_username) {
                    strMessage.Printf(_("Please enter a user name."));
                } else {
                    strMessage.Printf(_("Please enter an email address."));
                }
                bDisplayError = true;
            }
        }

        // Verify minimum password length
        if (!m_pAccountUseExistingCtrl->GetValue()) {
            if (m_pAccountPasswordCtrl->GetValue().Length() < (size_t)pc.min_passwd_length) {
                strMessage.Printf(
                    _("Please enter a password of at least %d characters."),
                    pc.min_passwd_length
                );
                bDisplayError = true;
            }
        }

        // Verify that the password and confirmation password math.
        if (!IS_ACCOUNTMANAGERWIZARD() && m_pAccountCreateCtrl->GetValue()) {
            if (m_pAccountPasswordCtrl->GetValue() != m_pAccountConfirmPasswordCtrl->GetValue()) {
                strMessage = _("The password and confirmation password do not match. Please type them again.");
                bDisplayError = true;
            }
        }

        if (bDisplayError) {

            wxGetApp().SafeMessageBox(
                strMessage,
                strTitle,
                wxICON_ERROR | wxOK,
                this
            );
            event.Veto();

        } else {

            // Update authoritative data in CWizardAttach
            pWA->SetAccountEmailAddress(m_strAccountEmailAddress);
            pWA->SetAccountUsername(m_strAccountUsername);
            pWA->SetAccountPassword(m_pAccountPasswordCtrl->GetValue());

        }
    }
}

/*!
 * wxEVT_WIZARD_CANCEL event handler for ID_ACCOUNTINFOPAGE
 */

void CAccountInfoPage::OnCancel( wxWizardExEvent& event ) {
    PROCESS_CANCELEVENT(event);
}

/*!
 * wxEVT_COMMAND_RADIOBUTTON_SELECTED event handler for ID_ACCOUNTUSEXISTINGBUTTON
 */

void CAccountInfoPage::OnAccountUseExistingCtrlSelected( wxCommandEvent& WXUNUSED(event) ) {
    CWizardAttach*         pWA = ((CWizardAttach*)GetParent());
    PROJECT_CONFIG&        pc = pWA->project_config;

    m_pAccountPasswordStaticCtrl->SetLabel(
        _("&Password:")
    );
    m_pAccountConfirmPasswordStaticCtrl->Hide();
    m_pAccountConfirmPasswordCtrl->Hide();
    m_pAccountPasswordRequirmentsStaticCtrl->Hide();

    if (pc.uses_username) {
        m_pAccountUsernameCtrl->SetFocus();
    } else {
        m_pAccountEmailAddressCtrl->SetFocus();
    }

    Fit();
}

/*!
 * wxEVT_COMMAND_RADIOBUTTON_SELECTED event handler for ID_ACCOUNTCREATEBUTTON
 */

void CAccountInfoPage::OnAccountCreateCtrlSelected( wxCommandEvent& WXUNUSED(event) ) {
    CWizardAttach*         pWA = ((CWizardAttach*)GetParent());
    PROJECT_CONFIG&        pc = pWA->project_config;

    m_pAccountPasswordStaticCtrl->SetLabel(
        _("Choose a &password:")
    );
    m_pAccountConfirmPasswordStaticCtrl->Show();
    m_pAccountConfirmPasswordCtrl->Show();
    m_pAccountPasswordRequirmentsStaticCtrl->Show();

    if (pc.uses_username) {
        m_pAccountUsernameCtrl->SetFocus();
    } else {
        m_pAccountEmailAddressCtrl->SetFocus();
    }

    Fit();
}

