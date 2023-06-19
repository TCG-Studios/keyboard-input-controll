#pragma once

typedef unsigned long long	uint64,	uint64_t,	u64;
typedef unsigned int		uint32,	uint32_t,	u32;
typedef unsigned short		uint16,	uint16_t,	u16;
typedef unsigned char		uint8,	uint8_t,	u8;

template <typename T>
using fncptr = void(__stdcall*)(T*);