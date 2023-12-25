// Start of wxWidgets "Hello World" Program
#include <iostream>
using namespace std;

#include <wx/wx.h>
#include <wx/spinctrl.h>

string fixedText = "1";
 
class MyApp : public wxApp
{
public:
    bool OnInit() override;
};
 
wxIMPLEMENT_APP(MyApp);
 
class MyFrame : public wxFrame
{
public:
    MyFrame();
 
private:
    void OnHello(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnMouseMoved(wxMouseEvent& event);

    void OnKeyEvent(wxKeyEvent& event);
};
 
enum
{
    ID_Hello = 1,
};
 
bool MyApp::OnInit()
{
    MyFrame *frame = new MyFrame();
    frame->SetClientSize(800, 800);
    frame->Center();
    frame->Show();
    return true;
}

string welcome() {
    return "Hi";
}
 
MyFrame::MyFrame()
    : wxFrame(nullptr, wxID_ANY, "Hello World")
{
    wxMenu *menuFile = new wxMenu;
    menuFile->Append(ID_Hello, "&Hello there!\tCtrl-H",
                     "Help string shown in status bar for this menu item");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);
 
    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);
 
    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuHelp, "&Help");
 
    SetMenuBar( menuBar );
 
    CreateStatusBar();
    string welcomeText = welcome();
 
    Bind(wxEVT_MENU, &MyFrame::OnHello, this, ID_Hello);
    Bind(wxEVT_MENU, &MyFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT);


    wxPanel* panel = new wxPanel(this);
    panel->SetBackgroundColour(wxColour(* wxLIGHT_GREY));
    panel->Bind(wxEVT_KEY_DOWN, &MyFrame::OnKeyEvent, this);
    //panel->Bind(wxEVT_MOTION, &MyFrame::OnMouseMoved, this);

    panel->SetFont(panel->GetFont().Scale(2));
    wxPanel* panel1 = new wxPanel(panel, wxID_ANY, wxPoint(100, 100), wxSize(100, 100));
    panel1->SetBackgroundColour(wxColour(* wxWHITE));
    panel1->Bind(wxEVT_MOTION, &MyFrame::OnMouseMoved, this);

    wxStaticText* staticText = new wxStaticText(panel1, wxID_ANY, fixedText, wxPoint(0, 50), wxSize(100, 100), wxALIGN_CENTRE_HORIZONTAL);
    staticText->SetForegroundColour(wxColour(* wxBLACK));
    //staticText->SetBackgroundColour(wxColour(255, 0, 0));
    //staticText->Refresh();
}
 
void MyFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}
 
void MyFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox("This is a wxWidgets Hello World example",
                 "About Hello World", wxOK | wxICON_INFORMATION);
}
 
void MyFrame::OnHello(wxCommandEvent& event)
{
    wxLogMessage("Hello world from wxWidgets!");
}


void MyFrame::OnMouseMoved(wxMouseEvent& event) {
    wxPoint mousePos = event.GetPosition();
    wxString message = wxString::Format("x: %d, y: %d", mousePos.x, mousePos.y);
    //string message = "x: " + mousePos.x + ", y: " + mousePos.y;
    wxLogStatus(message);
}

void MyFrame::OnKeyEvent(wxKeyEvent& event) {
    wxLogStatus("Key Event");
}