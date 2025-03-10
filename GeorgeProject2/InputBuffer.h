#pragma once
#include <iostream>
#include <bitset>
class InputBuffer
{
public:
    
    enum DirectionMask {
        RIGHT = 1 << 0, // 0b0001
        LEFT = 1 << 1, // 0b0010
        DOWN = 1 << 2, // 0b0100
        UP = 1 << 3  // 0b1000
    };
    DirectionMask checkedDirection = DirectionMask::LEFT;

    enum ButtonState {
        NONE = 0,
        PRESSED = 1,
        HELD = 2,
        RELEASED = 3
    };

    ButtonState returnInputNFramesAgo(int readInd, DirectionMask currButton);
    void printInputs(InputBuffer::DirectionMask direction, int readInd, InputBuffer::ButtonState state);
    void addToBuffer(int currInput);
};

