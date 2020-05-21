#pragma once
enum CollisionFilter
{
    PLAYER = 0x0001,
    BOX = 0x0002,
    SPHERE = 0x0004,
    FLOOR = 0x0008,
    START = 0x0016,
    CHECKPOINT = 0x0032,
    COIN = 0x00064
};