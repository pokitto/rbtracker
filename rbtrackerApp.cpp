/***************************************************************
 * Name:      rbtrackerApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Jonne Valola (jonnev@gmail.com)
 * Created:   2014-11-09
 * Copyright: Jonne Valola ()
 * License:
 **************************************************************/

#include "rbtrackerApp.h"

//(*AppHeaders
#include "rbtrackerMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(rbtrackerApp);

bool rbtrackerApp::OnInit()
{
    initSound();

    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	rbtrackerFrame* Frame = new rbtrackerFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
