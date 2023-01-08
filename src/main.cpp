#include "pen.h"
#include <iostream>

int main()
{
	std::cout << "hello ryan\n";

	int screen_number;
	Window canvas_window;
	unsigned long white_pixel;
	unsigned long black_pixel;

	Display* display = XOpenDisplay(NULL); // Connect X server by opening a display

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
        if (dev->use != XISlavePointer || dev->enabled == 0 || !xinput2_device_is_pen(display, dev)) {
            continue;
        }

		std::cout << "I am a pen! My name is " << dev->name << std::endl;
	}
}
