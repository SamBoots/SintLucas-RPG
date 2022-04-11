#pragma once
static unsigned int MATH_RANDOMSEED = 5;

/// <summary>
/// Get a Random unsigned int between 0 and INT_MAX.
/// </summary>
static unsigned int RandomUInt()
{
	MATH_RANDOMSEED ^= MATH_RANDOMSEED << 13, MATH_RANDOMSEED ^= MATH_RANDOMSEED >> 17;
	MATH_RANDOMSEED ^= MATH_RANDOMSEED << 5;
	return MATH_RANDOMSEED;
}

/// <summary>
/// Get a Random unsigned int between 0 and maxValue.
/// </summary>
static unsigned int RandomUIntMax(unsigned int maxValue)
{
	return RandomUInt() % maxValue;
}

/// <summary>
/// Get a Random unsigned int between min and max value.
/// </summary>
static unsigned int RandUintMinMax(unsigned int min, unsigned int max)
{
	return RandomUInt() % (max + 1 - min) + min;
}