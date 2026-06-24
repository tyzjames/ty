/* TyTools - public domain
   Niels Martignène <niels.martignene@protonmail.com>
   https://koromix.dev/tytools

   This software is in the public domain. Where that dedication is not
   recognized, you are granted a perpetual, irrevocable license to copy,
   distribute, and modify this file as you see fit.

   See the LICENSE file for more details. */

#include "common.h"
#include "class_priv.h"
#include "device.h"

extern const struct _ty_class_vtable _ty_teensy_class_vtable;
extern const struct _ty_class_vtable _ty_generic_class_vtable;

static const hs_match_spec default_match_specs[] = {
    HS_MATCH_VID_PID(0x16C0, 0x0485, (void *)&_ty_teensy_class_vtable), // USB MIDI
    HS_MATCH_VID_PID(0x16C0, 0x0478, (void *)&_ty_teensy_class_vtable), // Halfkay
    HS_MATCH_VID_PID(0x331b, 0x01,   (void *)&_ty_teensy_class_vtable),
    HS_MATCH_VID_PID(0x331b, 0x02,   (void *)&_ty_teensy_class_vtable),
    HS_MATCH_VID_PID(0x331b, 0x03,   (void *)&_ty_teensy_class_vtable),
    HS_MATCH_VID_PID(0x331b, 0x04,   (void *)&_ty_teensy_class_vtable),
    HS_MATCH_VID_PID(0x331b, 0x05,   (void *)&_ty_teensy_class_vtable),
    HS_MATCH_VID_PID(0x331b, 0x06,   (void *)&_ty_teensy_class_vtable),
    HS_MATCH_VID_PID(0x331b, 0x07,   (void *)&_ty_teensy_class_vtable),
    HS_MATCH_VID_PID(0x331b, 0x08,   (void *)&_ty_teensy_class_vtable),
    HS_MATCH_VID_PID(0x331b, 0x09,   (void *)&_ty_teensy_class_vtable),
    HS_MATCH_VID_PID(0x331b, 0x0A,   (void *)&_ty_teensy_class_vtable),
    HS_MATCH_VID_PID(0x331b, 0x0B,   (void *)&_ty_teensy_class_vtable),
    HS_MATCH_VID_PID(0x331b, 0x0C,   (void *)&_ty_teensy_class_vtable),
    HS_MATCH_VID_PID(0x331b, 0x0D,   (void *)&_ty_teensy_class_vtable),
    HS_MATCH_VID_PID(0x331b, 0x0E,   (void *)&_ty_teensy_class_vtable),
    HS_MATCH_VID_PID(0x331b, 0x0F,   (void *)&_ty_teensy_class_vtable),
    HS_MATCH_VID_PID(0x331b, 0x10,   (void *)&_ty_teensy_class_vtable),
    HS_MATCH_VID_PID(0x331b, 0x11,   (void *)&_ty_teensy_class_vtable),
    HS_MATCH_VID_PID(0x331b, 0x12,   (void *)&_ty_teensy_class_vtable),
    HS_MATCH_VID_PID(0x331b, 0x13,   (void *)&_ty_teensy_class_vtable),
    HS_MATCH_VID_PID(0x331b, 0x14,   (void *)&_ty_teensy_class_vtable),
    HS_MATCH_VID_PID(0x331b, 0x15,   (void *)&_ty_teensy_class_vtable),
    HS_MATCH_VID_PID(0x331b, 0x16,   (void *)&_ty_teensy_class_vtable),
    HS_MATCH_VID_PID(0x331b, 0x17,   (void *)&_ty_teensy_class_vtable),
    HS_MATCH_VID_PID(0x331b, 0x18,   (void *)&_ty_teensy_class_vtable),
    HS_MATCH_VID_PID(0x331b, 0x19,   (void *)&_ty_teensy_class_vtable),
    HS_MATCH_VID_PID(0x331b, 0x1A,   (void *)&_ty_teensy_class_vtable),
    HS_MATCH_VID_PID(0x331b, 0x1B,   (void *)&_ty_teensy_class_vtable),
    HS_MATCH_VID_PID(0x331b, 0x1C,   (void *)&_ty_teensy_class_vtable),
    HS_MATCH_VID_PID(0x331b, 0x1D,   (void *)&_ty_teensy_class_vtable),
    HS_MATCH_VID_PID(0x331b, 0x1E,   (void *)&_ty_teensy_class_vtable),
    HS_MATCH_VID_PID(0x331b, 0x1F,   (void *)&_ty_teensy_class_vtable),
    HS_MATCH_VID_PID(0x331b, 0x20,   (void *)&_ty_teensy_class_vtable),
    HS_MATCH_VID_PID(0x331b, 0x21,   (void *)&_ty_teensy_class_vtable),
    HS_MATCH_VID_PID(0x331b, 0x22,   (void *)&_ty_teensy_class_vtable),
    HS_MATCH_VID_PID(0x331b, 0x23,   (void *)&_ty_teensy_class_vtable),
    HS_MATCH_VID_PID(0x331b, 0x24,   (void *)&_ty_teensy_class_vtable),
    HS_MATCH_VID_PID(0x331b, 0x25,   (void *)&_ty_teensy_class_vtable),
    HS_MATCH_VID_PID(0x331b, 0x26,   (void *)&_ty_teensy_class_vtable),
    HS_MATCH_VID_PID(0x331b, 0x27,   (void *)&_ty_teensy_class_vtable),
    HS_MATCH_VID_PID(0x331b, 0x28,   (void *)&_ty_teensy_class_vtable),
    HS_MATCH_VID_PID(0x331b, 0x29,   (void *)&_ty_teensy_class_vtable),
    HS_MATCH_VID_PID(0x331b, 0x2A,   (void *)&_ty_teensy_class_vtable),
    HS_MATCH_VID_PID(0x331b, 0x2B,   (void *)&_ty_teensy_class_vtable),
    HS_MATCH_VID_PID(0x331b, 0x2C,   (void *)&_ty_teensy_class_vtable),
    HS_MATCH_VID_PID(0x331b, 0x2D,   (void *)&_ty_teensy_class_vtable),
    HS_MATCH_VID_PID(0x331b, 0x2E,   (void *)&_ty_teensy_class_vtable),
    HS_MATCH_VID_PID(0x331b, 0x2F,   (void *)&_ty_teensy_class_vtable),
    HS_MATCH_VID_PID(0x331b, 0x30,   (void *)&_ty_teensy_class_vtable),
    HS_MATCH_VID_PID(0x331b, 0x31,   (void *)&_ty_teensy_class_vtable),
    HS_MATCH_VID_PID(0x331b, 0x32,   (void *)&_ty_teensy_class_vtable),
    HS_MATCH_VID_PID(0x331b, 0x33,   (void *)&_ty_teensy_class_vtable),
    HS_MATCH_VID_PID(0x331b, 0x34,   (void *)&_ty_teensy_class_vtable),
    HS_MATCH_VID_PID(0x331b, 0x35,   (void *)&_ty_teensy_class_vtable),
    HS_MATCH_VID_PID(0x331b, 0x36,   (void *)&_ty_teensy_class_vtable),
    HS_MATCH_VID_PID(0x331b, 0x37,   (void *)&_ty_teensy_class_vtable),
    HS_MATCH_VID_PID(0x331b, 0x38,   (void *)&_ty_teensy_class_vtable),
    HS_MATCH_VID_PID(0x331b, 0x39,   (void *)&_ty_teensy_class_vtable),
    HS_MATCH_VID_PID(0x331b, 0x3A,   (void *)&_ty_teensy_class_vtable),
    HS_MATCH_VID_PID(0x331b, 0x3B,   (void *)&_ty_teensy_class_vtable),
    HS_MATCH_VID_PID(0x331b, 0x3C,   (void *)&_ty_teensy_class_vtable),
    HS_MATCH_VID_PID(0x331b, 0x3D,   (void *)&_ty_teensy_class_vtable),
    HS_MATCH_VID_PID(0x331b, 0x3E,   (void *)&_ty_teensy_class_vtable),
    HS_MATCH_VID_PID(0x331b, 0x3F,   (void *)&_ty_teensy_class_vtable),
    HS_MATCH_VID_PID(0x331b, 0x40,   (void *)&_ty_teensy_class_vtable),
    HS_MATCH_VID_PID(0x331b, 0x41,   (void *)&_ty_teensy_class_vtable),
    HS_MATCH_VID_PID(0x331b, 0x42,   (void *)&_ty_teensy_class_vtable),
    HS_MATCH_VID_PID(0x331b, 0x43,   (void *)&_ty_teensy_class_vtable),
    HS_MATCH_VID_PID(0x331b, 0x44,   (void *)&_ty_teensy_class_vtable),
    HS_MATCH_VID_PID(0x331b, 0x45,   (void *)&_ty_teensy_class_vtable),
    HS_MATCH_VID_PID(0x331b, 0x46,   (void *)&_ty_teensy_class_vtable),
    HS_MATCH_VID_PID(0x331b, 0x47,   (void *)&_ty_teensy_class_vtable),
    HS_MATCH_VID_PID(0x331b, 0x48,   (void *)&_ty_teensy_class_vtable),
    HS_MATCH_VID_PID(0x331b, 0x49,   (void *)&_ty_teensy_class_vtable),
    HS_MATCH_VID_PID(0x331b, 0x4A,   (void *)&_ty_teensy_class_vtable),
    HS_MATCH_VID_PID(0x331b, 0x4B,   (void *)&_ty_teensy_class_vtable),
    HS_MATCH_VID_PID(0x331b, 0x4C,   (void *)&_ty_teensy_class_vtable),
    HS_MATCH_VID_PID(0x331b, 0x4D,   (void *)&_ty_teensy_class_vtable),
    HS_MATCH_VID_PID(0x331b, 0x4E,   (void *)&_ty_teensy_class_vtable),
    HS_MATCH_VID_PID(0x331b, 0x4F,   (void *)&_ty_teensy_class_vtable),
    HS_MATCH_TYPE(HS_DEVICE_TYPE_SERIAL, (void *)&_ty_generic_class_vtable)
};

const hs_match_spec *_ty_class_match_specs = default_match_specs;
unsigned int _ty_class_match_specs_count = _HS_COUNTOF(default_match_specs);
