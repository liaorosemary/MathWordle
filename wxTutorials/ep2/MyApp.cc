#include "MyApp.h"
#include "MyFrame.h"
#include <wx/wx.h>

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit() {
    Mainframe* mainFrame = new Mainframe("C++ GUI");
    mainFrame->Show();
    return true;
};


/*
#include "MyApp.h"
#include "MyFrame.h"
#include <wx/wx.h>

wxIMPLEMENT_APP(App);

bool MyApp::OnInit()
{
    MyFrame *frame = new MyFrame();
    frame->Show(true);
    return true;
}
*/