#pragma once
#include <stdint.h>	// uint64_t
#include <limits.h> // ULLONG_MAX

static inline uint64_t rotl(const uint64_t x, int k)
{
	return (x << k) | (x >> (64 - k));
}

uint64_t xoroshiro128_next(uint64_t* s0, uint64_t* s1)
{
	const uint64_t _s0 = *s0;
	uint64_t _s1 = *s1;
	const uint64_t result = _s0 + _s1;

	_s1 ^= _s0;
	*s0 = rotl(_s0, 24) ^ _s1 ^ (_s1 << 16);
	*s1 = rotl(_s1, 37);

	return result;
}

double next_double(uint64_t* s0, uint64_t* s1)
{
	return (double)xoroshiro128_next(s0, s1) / (double)ULLONG_MAX;
}