#include <iostream>

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>

int main()
{
	std::cout << "hello ryan\n";

	Display *display; // A connection to X server
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

	std::cin >> x;   // just so that the program does not end
}
