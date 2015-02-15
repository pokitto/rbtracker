/***************************************************************
 * Name:      rbtrackerApp.h
 * Purpose:   Defines Application Class
 * Author:    Jonne Valola (jonnev@gmail.com)
 * Created:   2014-11-09
 * Copyright: Jonne Valola ()
 * License:
 **************************************************************/

#ifndef RBTRACKERAPP_H
#define RBTRACKERAPP_H

#include <wx/app.h>
#include "synth.h"

class rbtrackerApp : public wxApp
{
    public:
        virtual bool OnInit();
};

#endif // RBTRACKERAPP_H
