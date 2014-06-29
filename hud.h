#ifndef _HUD_H_
#define _HUD_H_

#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

void renderHud(Velocity velocity, int life, int focus, Dimension cenarySize);
void renderSpeed(Velocity velocity, Dimension cenarySize);
void renderLife(int life, Dimension cenarySize);
void renderFocus(int focus, Dimension cenarySize);
#endif
