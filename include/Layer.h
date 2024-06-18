#pragma once
#ifndef LAYER_H
#define LAYER_H

// Used for the painter's algorithm
enum class Layer
{
	BACKGROUND = 0,
	MIDDLEGROUND = 1,
	FOREGROUND = 2,
	END

};

#endif // !LAYER_H