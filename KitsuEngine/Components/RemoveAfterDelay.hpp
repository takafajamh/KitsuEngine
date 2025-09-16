#pragma once

struct RemoveAfterDelay
{
	float delay;		// After what time shall it be removed
	float current = 0;	// how long has it been on?
};