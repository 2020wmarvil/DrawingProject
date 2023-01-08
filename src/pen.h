#pragma once

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <X11/Xatom.h>
#include <X11/extensions/XInput2.h>

/**
 * Pen axis indices
 *
 * Below are the valid indices to the "axis" array from ::SDL_PenMotionEvent and ::SDL_PenButtonEvent.
 * The axis indices form a contiguous range of ints from 0 to ::SDL_PEN_AXIS_LAST, inclusive.
 * All "axis[]" entries are normalised to either 0..1 (unidirectional axes) or between -1..1 (bidirectional axes).
 * Unsupported entries are always "0.0f".
 *
 */
typedef enum {
    PEN_AXIS_PRESSURE = 0,                /**< Pen pressure.  Unidirectional: 0..1.0 */
    PEN_AXIS_XTILT,                       /**< Pen horizontal tilt fraction.  Bidirectional: -1.0..1.0 (left-to-right).  This is NOT the angle, but the tilt vector x component.  The physical max/min tilt may be smaller than -1.0 / 1.0, cf. \link SDL_PenCapabilityInfo \endlink .  */
    PEN_AXIS_YTILT,                       /**< Pen vertical tilt fraction.  Bidirectional: -1.0..1.0 (top-to-bottom).  This is NOT the angle, but the tilt vector y component.  */
    PEN_AXIS_DISTANCE,                    /**< Pen distance to drawing surface.  Unidirectional: 0.0..1.0 */
    PEN_AXIS_ROTATION,                    /**< Pen barrel rotation.  Bidirectional: -1.0..1.0 (clockwise, 0 is facing up).  Multiply with "2.0 * M_PI" to get radians, or "360.0" for degrees. */
    PEN_AXIS_SLIDER,                      /**< Pen finger wheel or slider (e.g., Airbrush Pen).  Unidirectional: 0..1.0 */
    PEN_NUM_AXES,                         /**< Last valid axis index */
    PEN_AXIS_LAST = PEN_NUM_AXES - 1  /**< Last axis index plus 1 */
} PenAxis;

/* X11-specific information attached to each pen */
typedef struct xinput2_pen {
    float axis_min[PEN_NUM_AXES];
    float axis_max[PEN_NUM_AXES];
    float slider_bias;   /* shift value to add to PEN_AXIS_SLIDER (before normalisation) */
    float rotation_bias; /* rotation to add to PEN_AXIS_ROTATION  (after normalisation) */
    int valuator_for_axis[PEN_NUM_AXES]; /* SDL_PEN_AXIS_VALUATOR_MISSING if not supported */
} xinput2_pen;

/* X11 atoms */
static struct {
    int initialized;        /* initialised to 0 */
    Atom device_product_id;
    Atom abs_pressure;
    Atom abs_tilt_x;
    Atom abs_tilt_y;
    Atom wacom_serial_ids;
    Atom wacom_tool_type;
} pen_atoms;

bool xinput2_device_is_pen(Display* display, const XIDeviceInfo *dev);