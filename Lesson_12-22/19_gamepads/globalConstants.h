#ifndef GLOBALCONSTANTS_H
#define GLOBALCONSTANTS_H

enum KeyPressSurfaces
{
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL
};

namespace gConstants
{
    constexpr int numOfTextures{ 5 };
};

namespace gJoystick
{
    constexpr int JOYSTICK_DEAD_ZONE = 8000;
};

#endif