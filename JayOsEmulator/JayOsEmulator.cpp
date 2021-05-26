#include <wx/wx.h>
#include <wx/sizer.h>
#include "Games.cpp"
#include "MainOS.cpp"


class wxImagePanel : public wxPanel
{
	wxImage* image;
	wxBitmap resized;
	int w, h;
	InputSystem* inputSystem;

public:
	wxImagePanel(wxFrame* parent, wxImage* image2, wxBitmapType format);
	void SetInputSystem(InputSystem* timer);
	void paintEvent(wxPaintEvent& evt);
	void paintNow();
	void OnSize(wxSizeEvent& event);
	void render(wxDC& dc);

	// some useful events
	/*
	 void mouseMoved(wxMouseEvent& event);
	 void mouseDown(wxMouseEvent& event);
	 void mouseWheelMoved(wxMouseEvent& event);
	 void mouseReleased(wxMouseEvent& event);
	 void rightClick(wxMouseEvent& event);
	 void mouseLeftWindow(wxMouseEvent& event);
	 */
	void keyPressed(wxKeyEvent& event);
	void keyReleased(wxKeyEvent& event);

	DECLARE_EVENT_TABLE()
};

class RenderTimer : public wxTimer {
	wxImagePanel* pane;
	wxImage* image;
	JayOS* jayOS;
	InputSystem* inputs;

public: RenderTimer(wxImagePanel* pane, wxImage* image);
	  void Notify();
	  void start();
};

RenderTimer::RenderTimer(wxImagePanel* pane, wxImage* image) : wxTimer() {
	RenderTimer::pane = pane;
	RenderTimer::image = image;
	JayScreen* screen = new JayScreen(image);
	RenderTimer::jayOS = new JayOS(screen);
	inputs = new InputSystem();
	pane->SetInputSystem(inputs);
}

void RenderTimer::Notify() {
	image->Clear();
	jayOS->Update(inputs);
	pane->Refresh(false);
	inputs->Reset();

}

void RenderTimer::start() {
	wxTimer::Start(1);
}

void InputSystem::Reset() {

	for (int i = 0; i < 4; i++)
	{
		//button_pressed[i] = false;
		button_downEvent[i] = false;
		button_upEvent[i] = false;
	}
}

void InputSystem::keyPressed(wxKeyEvent& event) {
	if (event.GetKeyCode() == 0x41) //A key
		Pressed(0);
	else if (event.GetKeyCode() == 0x53) //S key
		Pressed(1);
	else if (event.GetKeyCode() == 0x44) //D key
		Pressed(2);
	else if (event.GetKeyCode() == 0x46) //F key
		Pressed(3);
}

void InputSystem::keyReleased(wxKeyEvent& event) {
	if (event.GetKeyCode() == 0x41) //A key
		Released(0);
	else if (event.GetKeyCode() == 0x53) //S key
		Released(1);
	else if (event.GetKeyCode() == 0x44) //D key
		Released(2);
	else if (event.GetKeyCode() == 0x46) //F key
		Released(3);
}

void InputSystem::Pressed(int button) {
	button_pressed[button] = true;
	button_downEvent[button] = true;
}

void InputSystem::Released(int button) {
	button_pressed[button] = false;
	button_upEvent[button] = true;
}




BEGIN_EVENT_TABLE(wxImagePanel, wxPanel)
// some useful events
/*
 EVT_MOTION(wxImagePanel::mouseMoved)
 EVT_LEFT_DOWN(wxImagePanel::mouseDown)
 EVT_LEFT_UP(wxImagePanel::mouseReleased)
 EVT_RIGHT_DOWN(wxImagePanel::rightClick)
 EVT_LEAVE_WINDOW(wxImagePanel::mouseLeftWindow)
 EVT_MOUSEWHEEL(wxImagePanel::mouseWheelMoved)
 */
	EVT_KEY_DOWN(wxImagePanel::keyPressed)
	EVT_KEY_UP(wxImagePanel::keyReleased)

	// catch paint events
	EVT_PAINT(wxImagePanel::paintEvent)
	//Size event
	EVT_SIZE(wxImagePanel::OnSize)
	END_EVENT_TABLE()


	// some useful events
	/*
	 void wxImagePanel::mouseMoved(wxMouseEvent& event) {}
	 void wxImagePanel::mouseDown(wxMouseEvent& event) {}
	 void wxImagePanel::mouseWheelMoved(wxMouseEvent& event) {}
	 void wxImagePanel::mouseReleased(wxMouseEvent& event) {}
	 void wxImagePanel::rightClick(wxMouseEvent& event) {}
	 void wxImagePanel::mouseLeftWindow(wxMouseEvent& event) {}
	 */

	wxImagePanel::wxImagePanel(wxFrame* parent, wxImage* image2, wxBitmapType format) :
	wxPanel(parent)
{
	// load the file... ideally add a check to see if loading was successful
	image = image2;
	w = -1;
	h = -1;
}

/*
 * Called by the system of by wxWidgets when the panel needs
 * to be redrawn. You can also trigger this call by
 * calling Refresh()/Update().
 */

void wxImagePanel::paintEvent(wxPaintEvent& evt)
{
	// depending on your system you may need to look at double-buffered dcs
	wxPaintDC dc(this);
	render(dc);
}

void wxImagePanel::keyPressed(wxKeyEvent& event) {
	if (this->inputSystem)
		this->inputSystem->keyPressed(event);
}
void wxImagePanel::keyReleased(wxKeyEvent& event) {
	if (this->inputSystem)
		this->inputSystem->keyReleased(event);
}
/*
 * Alternatively, you can use a clientDC to paint on the panel
 * at any time. Using this generally does not free you from
 * catching paint events, since it is possible that e.g. the window
 * manager throws away your drawing when the window comes to the
 * background, and expects you will redraw it when the window comes
 * back (by sending a paint event).
 */
void wxImagePanel::paintNow()
{
	// depending on your system you may need to look at double-buffered dcs
	wxClientDC dc(this);
	render(dc);
}

/*
 * Here we do the actual rendering. I put it in a separate
 * method so that it can work no matter what type of DC
 * (e.g. wxPaintDC or wxClientDC) is used.
 */
void wxImagePanel::render(wxDC& dc)
{
	int neww, newh;
	dc.GetSize(&neww, &newh);
	resized = wxBitmap(image->Scale(neww, newh /*, wxIMAGE_QUALITY_HIGH*/));
	dc.DrawBitmap(resized, 0, 0, false);
}

/*
 * Here we call refresh to tell the panel to draw itself again.
 * So when the user resizes the image panel the image should be resized too.
 */
void wxImagePanel::OnSize(wxSizeEvent& event) {
	Refresh();
	//skip the event.
	event.Skip();
}
void wxImagePanel::SetInputSystem(InputSystem* inputSystem) {
	this->inputSystem = inputSystem;
}

// ----------------------------------------
// how-to-use example

class MyApp : public wxApp
{

	wxFrame* frame;
	RenderTimer* timer;
	wxImagePanel* drawPane;
public:
	bool OnInit()
	{
		// make sure to call this first
		wxInitAllImageHandlers();

		wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
		frame = new wxFrame(NULL, wxID_ANY, wxT("JayOS Emulator"), wxPoint(50, 50), wxSize(400, 800));

		// then simply create like this
		wxImage* image = new wxImage(8, 16);
		//image.SetRGB(1, 1, 0, 200, 0);
		drawPane = new wxImagePanel(frame, image, wxBITMAP_TYPE_JPEG);
		sizer->Add(drawPane, 1, wxEXPAND);

		frame->SetSizer(sizer);

		frame->Show();

		timer = new RenderTimer(drawPane, image);
		timer->start();

		return true;
	}

};

IMPLEMENT_APP(MyApp)