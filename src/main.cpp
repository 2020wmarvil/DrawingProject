#include <iostream>

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <X11/Xatom.h>

#include <X11/extensions/XInput2.h>

//#include <X11/ImUtil.h>
//#include <X11/XKBlib.h>
//#include <X11/Xcms.h>
//#include <X11/Xlibint.h>
//#include <X11/Xlocale.h>
//#include <X11/Xregion.h>
//#include <X11/Xresource.h>
//#include <X11/keysym.h>
//#include <X11/cursorfont.h>
//#include <X11/Xcursor/Xcursor.h>
//#include <X11/extensions/Xdbe.h>
//#include <X11/extensions/Xinerama.h>
//#include <X11/extensions/Xrandr.h>
//#include <X11/extensions/scrnsaver.h>
//#include <X11/extensions/shape.h>
//#include <X11/extensions/xf86vmode.h>
//#include <X11/extensions/Xfixes.h>
//#include <X11/extensions/Xext.h>
//#include <X11/extensions/XShm.h>

/* Detect XINPUT2 devices that are pens / erasers, or update the list after hotplugging */
void X11_InitPen();

///* Converts XINPUT2 valuators into pen axis information, including normalisation */
//extern void X11_PenAxesFromValuators(const SDL_Pen *pen,
//                                     const double *input_values, const unsigned char *mask, const int mask_len,
//                                     /* out-mode parameters: */
//                                     float axis_values[SDL_PEN_NUM_AXES]);
//
///* Map X11 device ID to pen ID */
//extern int X11_PenIDFromDeviceID(int deviceid);

Display *display; // A connection to X server

static bool xinput2_device_is_pen(const XIDeviceInfo *dev)
{
    int classct;
    for (classct = 0; classct < dev->num_classes; ++classct) {
        const XIAnyClassInfo *classinfo = dev->classes[classct];

        switch (classinfo->type) {
            case XIValuatorClass: {
                XIValuatorClassInfo *val_classinfo = (XIValuatorClassInfo*) classinfo;
                Atom vname = val_classinfo->label;

                if (vname == XInternAtom(display, "Abs Pressure", True)) {
                    return true;
                }
            }
        }
    }

    return false;
}

int main()
{
	std::cout << "hello ryan\n";

	int screen_number;
	Window canvas_window;
	unsigned long white_pixel;
	unsigned long black_pixel;

	display = XOpenDisplay(NULL);    // Connect X server by opening a display

	if(!display){
	  std::cerr<<"Unable to connect X server\n";
	  return 1;
	}

	screen_number = DefaultScreen(display);
	white_pixel = WhitePixel(display, screen_number);
	black_pixel = BlackPixel(display, screen_number);

	int x=0, y=100, w=300, h=400;

	canvas_window = XCreateSimpleWindow(display,
	                                    RootWindow(display, screen_number),
	                                    x,y,  // top left corner
	                                    w,h,  // width and height
	                                    2,    // border width
	                                    black_pixel,
	                                    white_pixel);

	XMapWindow(display, canvas_window);    // Map canvas window to display
	XSync(display, False);

	XIDeviceInfo *device_info;
	int num_devices;

    device_info = XIQueryDevice(display, XIAllDevices, &num_devices);

	std::cout << "Number of devices: " << num_devices << "\n";

	for (int i = 0; i < num_devices; ++i) {
        const XIDeviceInfo *dev = &device_info[i];
        //int classct;
        //xinput2_pen pen_device;
        //Uint32 capabilities = 0;
        //Uint32 axis_mask = ~0; /* Permitted axes (default: all) */
        //int valuator_5_axis = -1; /* For Wacom devices, the 6th valuator (offset 5) has a model-specific meaning */

        /* Only track physical devices that are enabled */
        if (dev->use != XISlavePointer || dev->enabled == 0 || !xinput2_device_is_pen(dev)) {
            continue;
        }

		std::cout << "I am a pen!" << std::endl;
	}
}
