// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
// This file is part of BOINC.
// http://boinc.berkeley.edu
// Copyright (C) 2008 University of California
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
// along with BOINC.  If not, see <http://www.gnu.org/licenses/>.
//
#if defined(__GNUG__) && !defined(__APPLE__)
#pragma implementation "DlgItemProperties.h"
#endif

#include "stdwx.h"
#include "util.h"
#include "DlgItemProperties.h"
#include "BOINCGUIApp.h"
#include "BOINCBaseFrame.h"
#include "Events.h"
#include "error_numbers.h"

IMPLEMENT_DYNAMIC_CLASS(CDlgItemProperties, wxDialog)

BEGIN_EVENT_TABLE(CDlgItemProperties, wxDialog)

END_EVENT_TABLE()

/* Constructor */
CDlgItemProperties::CDlgItemProperties(wxWindow* parent) : 
    wxDialog( parent, ID_ANYDIALOG, wxEmptyString, wxDefaultPosition, 
                wxSize( 503,480 ), wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER ) {
    CBOINCBaseFrame* pFrame = wxGetApp().GetFrame();
    wxASSERT(pFrame);
    if (!pFrame) return;

    SetSizeHints( wxDefaultSize, wxDefaultSize );
    SetExtraStyle( GetExtraStyle() | wxWS_EX_VALIDATE_RECURSIVELY );
    
    m_bSizer1 = new wxBoxSizer( wxVERTICAL );
    
    m_scrolledWindow = new wxScrolledWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxVSCROLL );
    m_scrolledWindow->SetScrollRate( 5, 5 );
    wxBoxSizer* m_bSizer2;
    m_bSizer2 = new wxBoxSizer( wxVERTICAL );
    
    m_gbSizer = new wxGridBagSizer( 0, 0 );
    m_gbSizer->SetCols(2);
    m_gbSizer->AddGrowableCol( 1 );
    m_gbSizer->SetFlexibleDirection( wxBOTH );
    m_gbSizer->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
    
    m_bSizer2->Add( m_gbSizer, 1, wxEXPAND, 5 );
    
    m_scrolledWindow->SetSizer( m_bSizer2 );
    m_scrolledWindow->Layout();
    m_bSizer2->Fit( m_scrolledWindow );
    m_bSizer1->Add( m_scrolledWindow, 1, wxEXPAND | wxALL, 5 );
    
    m_btnClose = new wxButton( this, wxID_OK, _("&Close"), wxDefaultPosition, wxDefaultSize, 0 );
    m_btnClose->SetDefault(); 
    m_bSizer1->Add( m_btnClose, 0, wxALIGN_BOTTOM|wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );
    
    SetSizer( m_bSizer1 );
    Layout();
    
    m_current_row=0;

    int currentTabView = pFrame->GetCurrentViewPage();
    switch(currentTabView) {
    case VW_PROJ:
        m_strBaseConfigLocation = wxString(wxT("/DlgProjectProperties/"));
        break;
    case VW_TASK:
        m_strBaseConfigLocation = wxString(wxT("/DlgTaskProperties/"));
        break;
    default:
        m_strBaseConfigLocation = wxString(wxT("/DlgProperties/"));
        break;
    }

    RestoreState();
}

// destructor
CDlgItemProperties::~CDlgItemProperties() {
    SaveState();
}

/* saves dialog size and (on Mac) position */
bool CDlgItemProperties::SaveState() {
    wxConfigBase*   pConfig = wxConfigBase::Get(FALSE);

    wxASSERT(pConfig);
    if (!pConfig) return false;

    pConfig->SetPath(m_strBaseConfigLocation);
    pConfig->Write(wxT("Width"), GetSize().GetWidth());
    pConfig->Write(wxT("Height"), GetSize().GetHeight());
    pConfig->Write(wxT("XPos"), GetPosition().x);
    pConfig->Write(wxT("YPos"), GetPosition().y);

    pConfig->Flush();
    
    return true;
}

/* restores former dialog size and position */
bool CDlgItemProperties::RestoreState() {
    wxConfigBase* pConfig = wxConfigBase::Get(FALSE);
    wxPoint oTempPoint;
    wxSize  oTempSize;

    wxASSERT(pConfig);
    if (!pConfig) return false;

    pConfig->SetPath(m_strBaseConfigLocation);

    pConfig->Read(wxT("YPos"), &oTempPoint.y, wxDefaultCoord);
    pConfig->Read(wxT("XPos"), &oTempPoint.x, wxDefaultCoord);
    pConfig->Read(wxT("Width"), &oTempSize.x, wxDefaultCoord);
    pConfig->Read(wxT("Height"), &oTempSize.y, wxDefaultCoord);

    // Guard against a rare situation where registry values are zero
    if ((oTempSize.x < 50) && (oTempSize.x != wxDefaultCoord)) oTempSize.x = wxDefaultCoord;
    if ((oTempSize.y < 50) && (oTempSize.y != wxDefaultCoord)) oTempSize.y = wxDefaultCoord;

    // If either co-ordinate is less then 0 then set it equal to 0 to ensure
    // it displays on the screen.
    if ((oTempPoint.x < 0) && (oTempPoint.x != wxDefaultCoord)) oTempPoint.x = wxDefaultCoord;
    if ((oTempPoint.y < 0) && (oTempPoint.y != wxDefaultCoord)) oTempPoint.y = wxDefaultCoord;

    // Set size and position to saved values or defaults if no saved values
    SetSize(oTempPoint.x, oTempPoint.y, oTempSize.x, oTempSize.y, wxSIZE_USE_EXISTING);

    // Now make sure window is on screen
    oTempPoint = GetScreenPosition();
    oTempSize = GetSize();

#ifdef __WXMSW__
    // Get the current display space for the current window
	int iDisplay = wxNOT_FOUND;
	if ( wxGetApp().GetFrame() != NULL )
        iDisplay = wxDisplay::GetFromWindow(this);
	if ( iDisplay == wxNOT_FOUND )
        iDisplay = 0;
    wxDisplay *display = new wxDisplay(iDisplay);
    wxRect rDisplay = display->GetClientArea();

	// Check that the saved height and width is not larger than the displayable space.
	// If it is, then reduce the size.
    if ( oTempSize.GetWidth() > rDisplay.width ) oTempSize.SetWidth(rDisplay.width);
    if ( oTempSize.GetHeight() > rDisplay.height ) oTempSize.SetHeight(rDisplay.height);

    // Check if part of the display was going to be off the screen, if so, center the 
    // display on that axis
	if ( oTempPoint.x < rDisplay.x ) {
		oTempPoint.x = rDisplay.x;
	} else if ( oTempPoint.x + oTempSize.GetWidth() > rDisplay.x + rDisplay.width ) {
		oTempPoint.x = rDisplay.x + rDisplay.width - oTempSize.GetWidth();
	}

	if ( oTempPoint.y < rDisplay.y ) {
		oTempPoint.y = rDisplay.y;
	} else if ( oTempPoint.y + oTempSize.GetHeight() > rDisplay.y + rDisplay.height ) {
		oTempPoint.y = rDisplay.y + rDisplay.height - oTempSize.GetHeight();
	}

    delete display;
#endif
#ifdef __WXMAC__
    // If the user has changed the arrangement of multiple 
    // displays, make sure the window title bar is still on-screen.
    if (!IsWindowOnScreen(oTempPoint.x, oTempPoint.y, oTempSize.GetWidth(), oTempSize.GetHeight())) {
        oTempPoint.y = oTempPoint.x = 30;
    }
#endif  // ! __WXMAC__

    // Set size and position to saved values or defaults if no saved values
    SetSize(oTempPoint.x, oTempPoint.y, oTempSize.x, oTempSize.y, wxSIZE_USE_EXISTING);

    return true;
}

void CDlgItemProperties::show_rsc(wxString rsc_name, RSC_DESC rsc_desc) {
    if (rsc_desc.no_rsc_pref) {
        addProperty(_("Don't request tasks for ") + rsc_name, _("Project preference"));
    }
    if (rsc_desc.no_rsc_ams) {
        addProperty(_("Don't request tasks for ") + rsc_name, _("Account manager preference"));
    }
    if (rsc_desc.no_rsc_apps) {
        addProperty(_("Don't request tasks for ") + rsc_name, _("Project has no apps for ") + rsc_name);
    }
    if (rsc_desc.no_rsc_config) {
        addProperty(_("Don't request tasks for ") + rsc_name, _("Client configuration excludes ") + rsc_name);
    }
    double x = rsc_desc.backoff_time - dtime();
    if (x<0) x = 0;
    if (x) {
        addProperty(
			wxString::Format(_("%s task request deferred for"), rsc_name.c_str()),
			FormatTime(x)
	    );
        addProperty(
			wxString::Format(_("%s task request deferral interval"), rsc_name.c_str()),
			FormatTime(rsc_desc.backoff_interval)
		);
    }
}

// show project properties
//
void CDlgItemProperties::renderInfos(PROJECT* project_in) {
    std::string projectname;
    //collecting infos
    project_in->get_name(projectname);
    //disk usage needs additional lookups
    CMainDocument* pDoc = wxGetApp().GetDocument();
    pDoc->CachedDiskUsageUpdate();
    
    // CachedDiskUsageUpdate() may have invalidated our project 
    // pointer, so get an updated pointer to this project
    PROJECT* project = pDoc->project(project_in->master_url);
    if (!project) return;     // TODO: display some sort of error alert?

    std::vector<PROJECT*> dp = pDoc->disk_usage.projects;
    double diskusage=0.0;    
    for (unsigned int i=0; i< dp.size(); i++) {
        PROJECT* tp = dp[i];        
        std::string tname;        
        tp->get_name(tname);
        wxString t1(wxString(tname.c_str(), wxConvUTF8));
        if(t1.IsSameAs(wxString(projectname.c_str(), wxConvUTF8)) || t1.IsSameAs(wxString(project->master_url, wxConvUTF8))) {
            diskusage = tp->disk_usage;
            break;
        }
    }
    //set dialog title
    wxString wxTitle = _("Properties of project ");
    wxTitle.append(wxString(projectname.c_str(),wxConvUTF8));
    SetTitle(wxTitle);
    //layout controls
    addSection(_("General"));
    addProperty(_("URL"), wxString(project->master_url, wxConvUTF8));
    addProperty(_("User name"), wxString(project->user_name.c_str(), wxConvUTF8));
    addProperty(_("Team name"), wxString(project->team_name.c_str(), wxConvUTF8));
    addProperty(_("Resource share"), wxString::Format(wxT("%s"), format_number(project->resource_share, 0)));
    if (project->min_rpc_time > dtime()) {
        addProperty(_("Scheduler RPC deferred for"), FormatTime(project->min_rpc_time - dtime()));
    }
    if (project->download_backoff) {
        addProperty(_("File downloads deferred for"), FormatTime(project->download_backoff));
    }
    if (project->upload_backoff) {
        addProperty(_("File uploads deferred for"), FormatTime(project->upload_backoff));
    }
    addProperty(_("Disk usage"), FormatDiskSpace(diskusage));
    addProperty(_("Computer ID"), wxString::Format(wxT("%d"), project->hostid));
    if (project->non_cpu_intensive) {
        addProperty(_("Non CPU intensive"), _("yes"));
    }
    addProperty(_("Suspended via GUI"), project->suspended_via_gui ? _("yes") : _("no"));
    addProperty(_("Don't request tasks"), project->dont_request_more_work ? _("yes") : _("no"));
    if (project->scheduler_rpc_in_progress) {
        addProperty(_("Scheduler call in progress"), _("yes"));
    }
    if (project->trickle_up_pending) {
        addProperty(_("Trickle-up pending"), _("yes"));
    }
    if (strlen(project->venue)) {
        addProperty(_("Host location"), wxString(project->venue, wxConvUTF8));
    } else {
        addProperty(_("Host location"), _("default"));
    }

    if (project->attached_via_acct_mgr) {
        addProperty(_("Added via account manager"), _("yes"));
    }
    if (project->detach_when_done) {
        addProperty(_("Remove when tasks done"), _("yes"));
    }
    if (project->ended) {
        addProperty(_("Ended"), _("yes"));
    }
    addProperty(_("Tasks completed"), wxString::Format(wxT("%s"), format_number(project->njobs_success, 0)));
    addProperty(_("Tasks failed"), wxString::Format(wxT("%s"), format_number(project->njobs_error, 0)));

    addSection(_("Credit"));
    addProperty(_("User"),
		// Displays the average and total user credit
        wxString::Format(
            _("%s total, %s average"),
            format_number(project->user_total_credit, 0).c_str(),
            format_number(project->user_expavg_credit, 2).c_str()
        )
    );
    addProperty(_("Host"),
		// Displays the average and total host credit
        wxString::Format(
            _("%s total, %s average"),
            format_number(project->host_total_credit, 0).c_str(),
            format_number(project->host_expavg_credit, 2).c_str()
        )
    );
    
    if (!project->non_cpu_intensive) {
        addSection(_("Scheduling"));
        addProperty(_("Scheduling priority"), format_number(project->sched_priority, 2));
        show_rsc(_("CPU"), project->rsc_desc_cpu);
        if (pDoc->state.host_info.coprocs.have_nvidia()) {
            show_rsc(
                wxString(proc_type_name(PROC_TYPE_NVIDIA_GPU), wxConvUTF8),
                project->rsc_desc_nvidia
            );
        }
        if (pDoc->state.host_info.coprocs.have_ati()) {
            show_rsc(
                wxString(proc_type_name(PROC_TYPE_AMD_GPU), wxConvUTF8),
                project->rsc_desc_ati
            );
        }
        if (pDoc->state.host_info.coprocs.have_intel_gpu()) {
            show_rsc(
                wxString(proc_type_name(PROC_TYPE_INTEL_GPU), wxConvUTF8),
                project->rsc_desc_intel_gpu
            );
        }
        double dcf = project->duration_correction_factor;
        // if it's exactly 1, it's not being used
        //
        if (dcf != 1) {
            addProperty(
                _("Duration correction factor"),
                wxString::Format(wxT("%0.4f"), dcf)
            );
        }
    }
    if (project->last_rpc_time) {
        wxDateTime dt;
        dt.Set((time_t)project->last_rpc_time);
        addProperty(_("Last scheduler reply"), dt.Format());
    }
    m_gbSizer->Layout();
    m_scrolledWindow->FitInside();
}

// show task properties
//
void CDlgItemProperties::renderInfos(RESULT* result) {
    CMainDocument* pDoc = wxGetApp().GetDocument();
    wxDateTime dt;
    wxString wxTitle = _("Properties of task ");
    wxTitle.append(wxString(result->name, wxConvUTF8));
    SetTitle(wxTitle);

    APP_VERSION* avp = NULL;
    WORKUNIT* wup = NULL;
    RESULT* r = pDoc->state.lookup_result(result->project_url, result->name);
    if (r) {
        avp = r->avp;
        wup = r->wup;
    }
    
    addProperty(_("Application"), FormatApplicationName(result));
    addProperty(_("Name"), wxString(result->wu_name, wxConvUTF8));
    addProperty(_("State"), result_description(result, false));
    if (result->received_time) {
        dt.Set((time_t)result->received_time);
        addProperty(_("Received"), dt.Format());
    }
    dt.Set((time_t)result->report_deadline);
    addProperty(_("Report deadline"), dt.Format());
    if (strlen(result->resources)) {
        addProperty(_("Resources"), wxString(result->resources, wxConvUTF8));
    }
    if (wup) {
        addProperty(_("Estimated computation size"),
            wxString::Format(wxT("%s GFLOPs"), format_number(wup->rsc_fpops_est/1e9, 0))
        );
    }
    if (result->active_task) {
        addProperty(_("CPU time"), FormatTime(result->current_cpu_time));
        addProperty(_("CPU time since checkpoint"), FormatTime(result->current_cpu_time - result->checkpoint_cpu_time));
        if (result->elapsed_time >= 0) {
            addProperty(_("Elapsed time"), FormatTime(result->elapsed_time));
        }
        addProperty(_("Estimated time remaining"), FormatTime(result->estimated_cpu_time_remaining));
        addProperty(_("Fraction done"), wxString::Format(wxT("%.3f%%"), result->fraction_done*100));
        addProperty(_("Virtual memory size"), FormatDiskSpace(result->swap_size));
        addProperty(_("Working set size"), FormatDiskSpace(result->working_set_size_smoothed));
        if (result->slot >= 0) {
            addProperty(_("Directory"), wxString::Format(wxT("slots/%d"), result->slot));
        }
        if (result->pid) {
            addProperty(_("Process ID"), wxString::Format(wxT("%d"), result->pid));
        }
        if (result->progress_rate) {
            // express rate in the largest time unit (hr/min/sec) for which rate < 100%
            //
            if (result->progress_rate*3600 < 1) {
                addProperty(_("Progress rate"), wxString::Format(wxT("%.3f%% %s"), 100*3600*result->progress_rate, _("per hour")));
            } else if (result->progress_rate*60 < 1) {
                addProperty(_("Progress rate"), wxString::Format(wxT("%.3f%% %s"), 100*60*result->progress_rate, _("per minute")));
            } else {
                addProperty(_("Progress rate"), wxString::Format(wxT("%.3f%% %s"), 100*result->progress_rate, _("per second")));
            }
        }
    } else if (result->state >= RESULT_COMPUTE_ERROR) {
        addProperty(_("CPU time"), FormatTime(result->final_cpu_time));
        addProperty(_("Elapsed time"), FormatTime(result->final_elapsed_time));
    }
    if (avp) {
        addProperty(_("Executable"), wxString(avp->exec_filename, wxConvUTF8));
    }
    m_gbSizer->Layout();
    m_scrolledWindow->FitInside();
}

//
wxString CDlgItemProperties::FormatDiskSpace(double bytes) {    
    wxString strBuffer= wxEmptyString;

    if (bytes >= TERA) {
        strBuffer.Printf(wxT("%0.2f TB"), bytes/TERA);
    } else if (bytes >= GIGA) {
        strBuffer.Printf(wxT("%0.2f GB"), bytes/GIGA);
    } else if (bytes >= MEGA) {
        strBuffer.Printf(wxT("%0.2f MB"), bytes/MEGA);
    } else if (bytes >= KILO) {
        strBuffer.Printf(wxT("%0.2f KB"), bytes/KILO);
    } else {
        strBuffer.Printf(wxT("%0.0f bytes"), bytes);
    }
    return strBuffer;
}

//
wxString CDlgItemProperties::FormatApplicationName(RESULT* result ) {
    wxString       strBuffer = wxEmptyString;
    CMainDocument* pDoc = wxGetApp().GetDocument();
    RESULT*        state_result = NULL;
    wxString       strAppBuffer = wxEmptyString;
    wxString       strClassBuffer = wxEmptyString;

    wxASSERT(pDoc);
    wxASSERT(wxDynamicCast(pDoc, CMainDocument));

    if (result) {
        state_result = pDoc->state.lookup_result(result->project_url, result->name);
        if (!state_result) {
            pDoc->ForceCacheUpdate();
            state_result = pDoc->state.lookup_result(result->project_url, result->name);
        }
        wxASSERT(state_result);

        if (!state_result) return strBuffer;
        WORKUNIT* wup = state_result->wup;
        if (!wup) return strBuffer;
        APP* app = wup->app;
        if (!app) return strBuffer;
        APP_VERSION* avp = state_result->avp;
        if (!avp) return strBuffer;

        if (strlen(app->user_friendly_name)) {
            strAppBuffer = wxString(state_result->app->user_friendly_name, wxConvUTF8);
        } else {
            strAppBuffer = wxString(state_result->avp->app_name, wxConvUTF8);
        }

        if (strlen(avp->plan_class)) {
            strClassBuffer.Printf(
                wxT(" (%s)"),
                wxString(avp->plan_class, wxConvUTF8).c_str()
            );
        }

        strBuffer.Printf(
            wxT("%s%s %d.%02d %s"),
            state_result->project->anonymous_platform?_("Local: "):wxT(""),
            strAppBuffer.c_str(),
            state_result->avp->version_num / 100,
            state_result->avp->version_num % 100,
            strClassBuffer.c_str()
        );
    }
    return strBuffer;
}


// adds a title section label to the dialog 
void CDlgItemProperties::addSection(const wxString& title) {
    wxStaticText* staticText = new wxStaticText(m_scrolledWindow, wxID_ANY, title, wxDefaultPosition, wxDefaultSize, 0);
    staticText->Wrap(-1);
    staticText->SetFont(wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 92, false, wxEmptyString));    
    m_gbSizer->Add(staticText, wxGBPosition( m_current_row, 0), wxGBSpan(1, 2), wxALL|wxEXPAND, 3);
    m_current_row++;
}

// adds a property row to the dialog 
void CDlgItemProperties::addProperty(const wxString& name, const wxString& value) {
    
    wxStaticText* staticText = new wxStaticText( m_scrolledWindow, wxID_ANY, name, wxDefaultPosition, wxDefaultSize, 0 );
    staticText->Wrap( -1 );
    m_gbSizer->Add( staticText, wxGBPosition( m_current_row, 0 ), wxGBSpan( 1, 1 ), wxALL, 3 );
    
    staticText = new wxStaticText( m_scrolledWindow, wxID_ANY, value, wxDefaultPosition, wxDefaultSize, 0 );
    staticText->Wrap( -1 );
    m_gbSizer->Add( staticText, wxGBPosition( m_current_row, 1 ), wxGBSpan( 1, 1 ), wxALL|wxEXPAND, 3 );
    m_current_row++;
}
