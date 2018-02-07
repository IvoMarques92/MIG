#include "CQuadrantRelativePattern.h"

CQuadrantRelativePattern::CQuadrantRelativePattern()
{
    device = "/dev/MIG4Leds";
    layer = 0;
}

CQuadrantRelativePattern::~CQuadrantRelativePattern()
{

}

int CQuadrantRelativePattern::getQuadrant()
{
    return layer;
}

void CQuadrantRelativePattern::writeQuadrant() {

    uint8_t tx[] = {layer,};

    fd = open(device.c_str(), O_RDWR);
    if(fd < 0)
        perror("ERROR: Can not open the device MIG4Leds");

    if (write(fd, tx, 1) != 1)
        perror("ERROR: Can not write on the MIG4Leds");

    close(fd);

    return;
}

void CQuadrantRelativePattern::setQuadrant( int x, int y) {
    layer = 0 | (x & 0x01) | ((y & 0x01) <<1);
    return;
}
