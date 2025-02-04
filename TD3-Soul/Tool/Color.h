#pragma once
#include <cstdint>
inline uint32_t LerpColor(uint32_t startColor, uint32_t endColor, float t)
{
	uint8_t startA = (startColor >> 24) & 0xFF;
	uint8_t startR = (startColor >> 16) & 0xFF;
	uint8_t startG = (startColor >> 8) & 0xFF;
	uint8_t startB = startColor & 0xFF;

	uint8_t endA = (endColor >> 24) & 0xFF;
	uint8_t endR = (endColor >> 16) & 0xFF;
	uint8_t endG = (endColor >> 8) & 0xFF;
	uint8_t endB = endColor & 0xFF;

	uint8_t resultA = static_cast<uint8_t>(startA + t * (endA - startA));
	uint8_t resultR = static_cast<uint8_t>(startR + t * (endR - startR));
	uint8_t resultG = static_cast<uint8_t>(startG + t * (endG - startG));
	uint8_t resultB = static_cast<uint8_t>(startB + t * (endB - startB));

	return (resultA << 24) | (resultR << 16) | (resultG << 8) | resultB;
}