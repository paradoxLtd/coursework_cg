// fixed.h
#ifndef __FIXED__
#define __FIXED__

#include "math.h"

#define fixed int
#define round(x) floor(x + 0.5)
#define roundf(x) floor(x + 0.5f)

// ������������ ����� ����� � ������� ����� � ������������� ������
inline fixed int_to_fixed(int value)
{
	return (value << 16);
}

// ����� ����� ����� � ������������� ������
inline int fixed_to_int(fixed value)
{
	if (value < 0) return (value >> 16 - 1);
	if (value >= 0) return (value >> 16);
}

// ���������� �� ���������� ������
inline int round_fixed(fixed value)
{
	return fixed_to_int(value + (1 << 15));
}

// ������������ ����� � ��������� ������ � ������� ����� � ������������� ������
// ����� ���������� ������� ������ ��������
inline fixed double_to_fixed(double value)
{
	return round(value * (65536.0));
}

inline fixed float_to_fixed(float value)
{
	return roundf(value * (65536.0f));
}

// ���������� ��������� (a / b) � ������� ����� � ������������� ������
inline fixed frac_to_fixed(int a, int b)
{
	return (a << 16) / b;
}

#endif