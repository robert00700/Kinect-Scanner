///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Sep  8 2010)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "noname.h"

///////////////////////////////////////////////////////////////////////////

control::control( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* vertLayout;
	vertLayout = new wxBoxSizer( wxVERTICAL );
	
	vertLayout->SetMinSize( wxSize( 300,50 ) ); 
	but1 = new wxButton( this, wxID_ANY, wxT("All"), wxDefaultPosition, wxDefaultSize, 0 );
	but1->SetMinSize( wxSize( 300,-1 ) );
	
	vertLayout->Add( but1, 0, wxALL|wxEXPAND, 5 );
	
	but2 = new wxButton( this, wxID_ANY, wxT("Banter"), wxDefaultPosition, wxDefaultSize, 0 );
	but2->SetMinSize( wxSize( 300,-1 ) );
	
	vertLayout->Add( but2, 0, wxALL|wxEXPAND, 5 );
	
	but3 = new wxButton( this, wxID_ANY, wxT("Filter"), wxDefaultPosition, wxDefaultSize, 0 );
	but3->SetMinSize( wxSize( 300,-1 ) );
	
	vertLayout->Add( but3, 0, wxALL|wxEXPAND, 5 );
	
	this->SetSizer( vertLayout );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	but1->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( control::all ), NULL, this );
	but2->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( control::calibrate ), NULL, this );
	but3->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( control::filter ), NULL, this );
}

control::~control()
{
	// Disconnect Events
	but1->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( control::all ), NULL, this );
	but2->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( control::calibrate ), NULL, this );
	but3->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( control::filter ), NULL, this );
	
}
