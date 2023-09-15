#pragma once

enum Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN,
    JUMP,
    ROTATE_LEFT,
    ROTATE_RIGHT
};

enum PickupType
{
    Health,
    Speed,
    Life,
    Damage,
    Switch
};
