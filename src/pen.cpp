#include "pen.h"

/* Converts XINPUT2 valuators into pen axis information, including normalisation */
//void X11_PenAxesFromValuators(const SDL_Pen *pen,
//                              const double *input_values, const unsigned char *mask, const int mask_len,
//                              /* out-mode parameters: */
//                              float axis_values[SDL_PEN_NUM_AXES]);

/* Map X11 device ID to pen ID */
//int X11_PenIDFromDeviceID(int deviceid);

bool xinput2_device_is_pen(Display* display, const XIDeviceInfo *dev)
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