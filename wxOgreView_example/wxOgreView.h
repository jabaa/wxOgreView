/// The wxOgreView class
/** The wxOgreView class provides an Ogre render window
    and a function to get the window handle. You can assign a render window
    wit the setRenderWindow method.
*/
#ifndef __WXOGRE_H__
#define __WXOGRE_H__

#include <wx/wx.h>
#include <Ogre.h>
#include <OgrePrerequisites.h>

class wxOgreView : public wxControl
{
public:
    /** A new wxOgreView must receive a parent frame to which it can be attached
        @param parent pointer to a parent window.
        @param id pointer to a parent window.
        @param pos Window position. wxDefaultPosition indicates that wxWidgets should generate a default
               position for the window. If using the wxWindow class directly, supply an actual position.
        @param size Window size. wxDefaultSize indicates that wxWidgets should generate a default size
               for the window. If no suitable size can be found, the window will be sized to 20x20 pixels
               so that the window is visible but obviously not correctly sized.
        @param style Window style. For generic window styles, please see wxWindow.
        @param validator pointer to a pvalidator.
        @param name wxOgreView name. */
	wxOgreView (wxWindow* parent,
                wxWindowID id = -1,
                const wxPoint &pos=wxDefaultPosition,
                const wxSize &size=wxDefaultSize,
                long style=0,
                const wxValidator& validator = wxDefaultValidator,
                const wxString &name=wxPanelNameStr);
    wxOgreView();
	/** Standard Destructor*/
	~wxOgreView();
	/** Assign a RenderWindow to the RenderWindow pointer
        @param name The name of the window. */
    void setRenderWindow(const Ogre::String &name);
    /** Return the RenderWindow pointer */
    Ogre::RenderWindow* getRenderWindow();
    /** Return the window handle that is used to create a RenderWindow */
    Ogre::String getWindowHandle();

private:
    /** Notify Ogre on a window resize event
        @param event the rezising event. */
    void OnSize(wxSizeEvent& event);

protected:
    ///RenderWindow pointer
	  Ogre::RenderWindow* mpRenderWindow;
    ///Event table for resize events
    DECLARE_EVENT_TABLE()

};

#endif // __WXOGRE_H__

