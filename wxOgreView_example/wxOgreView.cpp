#include "wxOgreView.h"

//================================================================================= BEGIN_EVENT_TABLE()//
BEGIN_EVENT_TABLE(wxOgreView, wxControl)
	EVT_SIZE(wxOgreView::OnSize)
	//EVT_PAINT(wxOgre::OnPaint) // Produces flickers and runs too fast!
	//EVT_ERASE_BACKGROUND( wxOgre::OnEraseBackground )
END_EVENT_TABLE()

//================================================================================= wxOgreView()//
wxOgreView::wxOgreView(wxWindow* parent,
                       wxWindowID id,
                       const wxPoint &pos,
                       const wxSize &size,
                       long style,
                       const wxValidator& validator,
                       const wxString &name) :   wxControl(parent, id, pos, size, style, validator, name),
                                                 mpRenderWindow(0)
{

}

wxOgreView::wxOgreView() : wxControl(),
                           mpRenderWindow(0)
{
}
//================================================================================= ~wxOgreView()//
wxOgreView::~wxOgreView()
{
}

//================================================================================= getWindowHandle()//
Ogre::String wxOgreView::getWindowHandle()
{
	Ogre::String handle;

#ifdef __WXMSW__
	handle = Ogre::StringConverter::toString((size_t)((HWND)GetHandle()));
#elif defined(__WXGTK__)NameValuePairList
	// TODO: Someone test this. you might to use "parentWindowHandle" if this
	// does not work.  Ogre 1.2 + Linux + GLX platform wants a string of the
	// format display:screen:window, which has variable types ulong:uint:ulong.
	GtkWidget* widget = GetHandle();
	gtk_widget_realize( widget );	// Mandatory. Otherwise, a segfault happens.
	std::stringstream handleStream;
	Display* display = GDK_WINDOW_XDISPLAY( widget->window );
	Window wid = GDK_WINDOW_XWINDOW( widget->window );	// Window is a typedef for XID, which is a typedef for unsigned int
	/* Get the right display (DisplayString() returns ":display.screen") */
	std::string displayStr = DisplayString( display );
	displayStr = displayStr.substr( 1, ( displayStr.find( ".", 0 ) - 1 ) );
	/* Put all together */
	handleStream << displayStr << ':' << DefaultScreen( display ) << ':' << wid;
	handle = handleStream.str();
#else
	#error Not supported on this platform.
#endif

    return handle;
}

//================================================================================= getRenderWindow()
Ogre::RenderWindow* wxOgreView::getRenderWindow()
{
    return mpRenderWindow;
}

//================================================================================= setRenderWindow()
void wxOgreView::setRenderWindow(const Ogre::String &name)
{
    int width, height;
    GetSize(&width,&height);
    Ogre::NameValuePairList params;
    params["externalWindowHandle"] = getWindowHandle();
    mpRenderWindow = Ogre::Root::getSingleton().createRenderWindow(name, width, height, false, &params);
}

//================================================================================= OnSize()//
void wxOgreView::OnSize(wxSizeEvent& event)
{
    if(mpRenderWindow)
    {
		int width;
		int height;
		GetSize(&width, &height);
		mpRenderWindow->resize( width, height );
		// Letting Ogre know the window has been resized;
		mpRenderWindow->windowMovedOrResized();
    }
}

