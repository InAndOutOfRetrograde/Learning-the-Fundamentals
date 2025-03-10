#include "InputBuffer.h"

//SHOULD THESE VARS GO HERE? OR IN THE HEADER?
//circular buffer vars
int startIndex = 0;
int writeIndex = 0;
const int bufferArraySize = 60;
int inputList[100] = { };
int NFramesAgo = 20;//NEVER BIGGER THAN SIZE

InputBuffer::ButtonState InputBuffer::returnInputNFramesAgo(int readInd, DirectionMask currButton)
{
    if (readInd == -1) { return NONE; }

    int currInput = inputList[readInd] & currButton;
    int lastInput = inputList[readInd + 1] & currButton;

    ButtonState currState = NONE;
    if (((~currInput) & lastInput) > 0) { currState = PRESSED; }
    if ((currInput & lastInput) > 0) { currState = HELD; }
    if ((currInput & (~lastInput)) > 0) { currState = RELEASED; }

    return currState;
}

void InputBuffer::printInputs(InputBuffer::DirectionMask direction, int readInd, InputBuffer::ButtonState state)
{
    std::cout << "-----------" << std::endl;

    std::bitset<sizeof(int) * 8> bits(inputList[readInd]);
    std::cout << bits << " <--- " << NFramesAgo << "  FRAMES AGO" << std::endl;

    if (direction == RIGHT) { std::cout << "RIGHT -- "; }
    if (direction == LEFT) { std::cout << "LEFT -- "; }
    if (direction == UP) { std::cout << "UP -- "; }
    if (direction == DOWN) { std::cout << "DOWN --"; }

    if (state == NONE) { std::cout << "no press."; }
    if (state == PRESSED) { std::cout << "just pressed."; }
    if (state == HELD) { std::cout << "held."; }
    if (state == RELEASED) { std::cout << "released."; }

    std::cout << std::endl;
}

void InputBuffer::addToBuffer(int currInput)
{
    //write to buffer
    int delayFromTheStart = bufferArraySize - NFramesAgo;
    inputList[writeIndex] = currInput;
    writeIndex = (writeIndex + 1) % bufferArraySize;
    if ((startIndex + bufferArraySize) % bufferArraySize == writeIndex)
    {
        startIndex = (startIndex + 1) % bufferArraySize;
        //read from buffer
        int readInd = (startIndex + delayFromTheStart) % bufferArraySize;
        InputBuffer::ButtonState currButtonState = returnInputNFramesAgo((startIndex + delayFromTheStart) % bufferArraySize, checkedDirection);
        printInputs(checkedDirection, readInd, currButtonState);
    }
}