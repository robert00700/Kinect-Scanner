///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Sep  8 2010)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __noname__
#define __noname__

#include <wx/string.h>
#include <wx/button.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/sizer.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class control
///////////////////////////////////////////////////////////////////////////////
class control : public wxFrame 
{
	private:
	
	protected:
		wxButton* but1;
		wxButton* but2;
		wxButton* but3;
		
		// Virtual event handlers, overide them in your derived class
		virtual void all( wxCommandEvent& event );
		virtual void calibrate( wxCommandEvent& event );
		virtual void filter( wxCommandEvent& event );
		
	
	public:
		
		control( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Kinect Scanner"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 321,147 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		~control();
	
};

#endif //__noname__
