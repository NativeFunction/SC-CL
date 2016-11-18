#include "types.h"
#include "natives.h"
#include "constants.h"
#include "intrinsics.h"

#define SwapEndian(x) _Generic((x),\
short int: SwapEndian16(x), unsigned short int: SwapEndian16(x),\
default: SwapEndian32(x))

void print(char* str, int ms)
{
	#ifdef __GTAV__
		_set_text_entry_2("STRING");
		add_text_component_substring_player_name(str);
		_draw_subtitle_timed(ms, 1);
	#else
		#ifdef __RDR__
			_clear_prints();
			_print_subtitle(str, ms != 0 ? (float)ms / 1000.0f : 0, true, 2, 1, 0, 0, 0);
		#endif
	#endif
}

int SwapEndian32(int value)
{
	return ((((value) & 0xff000000) >> 24) | (((value) & 0x00ff0000) >>  8) | (((value) & 0x0000ff00) <<  8) | (((value) & 0x000000ff) << 24));
}
short SwapEndian16(short value)
{
	return (((value) & 0xff000000) >> 24) | (((value) & 0x00ff0000) >>  8);
}
int CeilDivInt(uint a, uint b) 
{ 
	return a == 0 || b == 0 ? 0 : 1 + ((a - 1) / b); 
}
int DivInt(int a, int b)
{ 
	return a == 0 || b == 0 ? 0 : a / b;
}
char* IntToHex(int val)
{
	char* hex_str = "0123456789ABCDEF";
	byte* bin = (byte*)&val;

	char* str = "         ";

	for (int i = 0; i < 4; i++)
	{
		str[i * 2] = hex_str[(bin[i] >> 4) & 0x0F];
		str[i * 2 + 1] = hex_str[(bin[i]) & 0x0F];
	}
	str[8] = 0;
	return str;
}
int HexToInt(char *hex)
{
	uint result = 0;

	while (*hex)
	{
		if (*hex > 47 && *hex < 58)
			result += (*hex - 48);
		else if (*hex > 64 && *hex < 71)
			result += (*hex - 55);
		else if (*hex > 96 && *hex < 103)
			result += (*hex - 87);

		if (*++hex)
			result <<= 4;
	}

	return result;
}
int SetBit(int value, uint index)
{
	return index > 31 ? value : value | (1 << index);
}
int ClearBit(int value, uint index)
{
	return index > 31 ? value : value & ~(1 << index);
}
int ToggleBit(int value, uint index)
{
	return index > 31 ? value : value ^ (1 << index);
}
int SetBitInline(int value, uint index, bool bit)
{
	return index > 31 ? value : value ^ ((-bit ^ value) & (1 << index));
}
int ModNegitive(int value1, int value2)
{
	int ret = value1 % value2;
	return ret < 0 ? ret + value2 : ret;
}
float DegreesToRadians(float degrees)
{
	return degrees * (PI / 180);
}
float RadiansToDegrees(float radians)
{
	return radians * (180 / PI);
}
quaternion EulerToQuaternion(vector3 euler)
{
	float cosYawOver2 = cos(euler.x * 0.5),
	sinYawOver2 = sin(euler.x * 0.5),
	
	cosPitchOver2 = cos(euler.y * 0.5),
	sinPitchOver2 = sin(euler.y * 0.5),
	
	cosRollOver2 = cos(euler.z * 0.5),
	sinRollOver2 = sin(euler.z * 0.5);
	
	quaternion out = 
	{
		(cosYawOver2 * cosPitchOver2 * cosRollOver2) + (sinYawOver2 * sinPitchOver2 * sinRollOver2),
		(cosYawOver2 * cosPitchOver2 * sinRollOver2) - (sinYawOver2 * sinPitchOver2 * cosRollOver2),
		(cosYawOver2 * sinPitchOver2 * cosRollOver2) + (sinYawOver2 * cosPitchOver2 * sinRollOver2),
		(sinYawOver2 * cosPitchOver2 * cosRollOver2) - (cosYawOver2 * sinPitchOver2 * sinRollOver2)
	};
	return out;
}
vector3 RotationLookAtPoint(vector3 pos, vector3 endpos)
{
	vector3 out = 
	{
		atan2(pos.y, pos.z),
		atan2(pos.x * cos(endpos.x), pos.z),
		atan2(cos(endpos.x), sin(endpos.x) * sin(pos.y))
	};
	return out;
}

#ifndef __GTAV__
float acos(float number)
{
	//this works fine for floats as negitive ints and floats both have msb set
	if (reinterpretFloatToInt(number) < 0)
	{
		number = -number;
		return 
		-(((((((
		-0.0187293f * number)
		+ 0.0742610f)
		* number)
		- 0.2121144f)
		* number)
		+ 1.5707288f)
		* sqrt(1.0 - number)) 
		+ PI;
	}
	
	return 
	((((((
	-0.0187293f * number)
	+ 0.0742610f)
	* number)
	- 0.2121144f)
	* number)
	+ 1.5707288f)
	* sqrt(1.0 - number);

}
float asin(float number)
{
	//this works fine for floats as negitive ints and floats both have msb set
	if (reinterpretFloatToInt(number) < 0)
	{
		number = -number;
		return 
		(((((((
		-0.0187293f * number)
		+ 0.0742610f)
		* number)
		- 0.2121144f)
		* number)
		+ 1.5707288f)
		* sqrt(1.0 - number))
		- 1.57079632;
	}
	return
	-(((((((
	-0.0187293f * number)
	+ 0.0742610f)
	* number)
	- 0.2121144f)
	* number)
	+ 1.5707288f)
	* sqrt(1.0 - number))
	+ 1.57079632;
}

#endif

float StringToFloat(char* str)
{
	float rez = 0, fact = 1;
	bool point_seen = false;
	str -= 3;
	int d = 0, read_char = *str & 0xFF;
	
	if(read_char == '-')
	{
		fact = -1;
		read_char = *++str & 0xFF;
	}
	
	while(read_char)
	{
		if(read_char == '.')
		{
			point_seen = true;
		    read_char = *++str & 0xFF;
			continue;
		}
		
		d = read_char - '0';
		
		if(d >= 0 && d <= 9)
		{
			if(point_seen)
				fact /= 10;
			rez = rez * 10.0f + (float)d;
		}
		read_char = *++str & 0xFF;
	}
	return rez * fact;
}

