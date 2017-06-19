#include <stdint.h>

/*
 * test ranges of signed and unsigned integer additions, specifically testing
 * DI/longlong lhs operand with various rhs operand types (register/constant)
 * and differing integer sizes.
 */

int testcase_adddi3_reg64_reg_ranges(void)
{
	int64_t i = 9000;
	uint64_t a = 9000;

	/* operands as registers when not optimized away */
	uint64_t u64 = 0;
	uint32_t u32 = 0;
	uint16_t u16 = 0;
	int64_t i64 = 0;
	int32_t i32 = 0;
	int16_t i16 = 0;

	/* signed */
	i64 = i32 = -2147483647L;
	if ((i + i32) != -2147474647L) abort();
	if ((i + i64) != -2147474647L) abort();
	i64 = i32 = -65535L;
	if ((i + i32) != -56535L) abort();
	if ((i + i64) != -56535L) abort();
	i64 = i32 = -32768;
	if ((i + i32) != -23768) abort();
	if ((i + i64) != -23768) abort();
	i64 = i32 = i16 = -1;
	if ((i + i16) != 8999) abort();
	if ((i + i32) != 8999) abort();
	if ((i + i64) != 8999) abort();
	i64 = i32 = i16 = 0;
	if ((i + i16) != 9000) abort();
	if ((i + i32) != 9000) abort();
	if ((i + i64) != 9000) abort();
	i64 = i32 = i16 = 1;
	if ((i + i16) != 9001) abort();
	if ((i + i32) != 9001) abort();
	if ((i + i64) != 9001) abort();
	i64 = i32 = i16 = 10;
	if ((i + i16) != 9010) abort();
	if ((i + i32) != 9010) abort();
	if ((i + i64) != 9010) abort();
	i64 = i32 = 32767;
	if ((i + i32) != 41767) abort();
	if ((i + i64) != 41767) abort();
	i64 = i32 = 65535L;
	if ((i + i32) != 74535) abort();
	if ((i + i64) != 74535) abort();
	i64 = i32 = 2147483647L;
	if ((i + i32) != 2147492647L) abort();
	if ((i + i64) != 2147492647L) abort();
	i64 = 2147483648LL;
	if ((i + i64) != 2147492648LL) abort();
	i64 = 281474976710655LL;
	if ((i + i64) != 281474976719655LL) abort();

	/* unsigned */
	u64 = u32 = u16 = 0;
	if ((a + u16) != 9000) abort();
	if ((a + u32) != 9000) abort();
	if ((a + u64) != 9000) abort();
	u64 = u32 = u16 = 1;
	if ((a + u16) != 9001) abort();
	if ((a + u32) != 9001) abort();
	if ((a + u64) != 9001) abort();
	u64 = u32 = u16 = 10;
	if ((a + u16) != 9010UL) abort();
	if ((a + u32) != 9010UL) abort();
	if ((a + u64) != 9010UL) abort();
	u64 = u32 = 32767;
	if ((i + u32) != 41767) abort();
	if ((i + u64) != 41767) abort();
	u64 = u32 = 65535UL;
	if ((i + u32) != 74535) abort();
	if ((i + u64) != 74535) abort();
	u64 = u32 = 0x10000;
	if ((a + u32) != 0x12328UL) abort();
	if ((a + u64) != 0x12328UL) abort();
	u64 = u32 = 0x10000000UL;
	if ((a + u32) != 0x10002328UL) abort();
	if ((a + u64) != 0x10002328UL) abort();
	u64 = u32 = 2147483647UL;
	if ((a + u32) != 2147492647UL) abort();
	if ((a + u64) != 2147492647UL) abort();
	u64 = u32 = 0xffffffffUL;
	if ((a + u32) != 4294976295ULL) abort();
	if ((a + u64) != 4294976295ULL) abort();
	u64 = 0xffffffffffffULL;
	if ((a + u64) != 281474976719655ULL) abort();
	u64 = 0xfffffffffffffffULL;
	if ((a + u64) != 1152921504606855975ULL) abort();

	return 0;
}

int testcase_adddi3_reg64_const_ranges(void)
{
	int64_t i = 9000;
	uint64_t a = 9000;

	/* signed */
	if ((i + (-2147483647L)) != -2147474647L) abort();
	if ((i + (-65535L)) != -56535L) abort();
	if ((i + (-32768)) != -23768) abort();
	if ((i + (-1)) != 8999) abort();
	if ((i + (0)) != 9000) abort();
	if ((i + (1)) != 9001) abort();
	if ((i + ((int16_t)10)) != 9010) abort();
	if ((i + (32767)) != 41767) abort();
	if ((i + (65535L)) != 74535) abort();
	if ((i + (2147483647L)) != 2147492647L) abort();
	if ((i + (2147483648LL)) != 2147492648LL) abort();
	if ((i + (281474976710655LL)) != 281474976719655LL) abort();

	/* unsigned */
	if ((a + (0)) != 9000) abort();
	if ((a + (1)) != 9001) abort();
	if ((a + ((uint16_t)10)) != 9010) abort();
	if ((a + (32767)) != 41767) abort();
	if ((a + (65535UL)) != 74535) abort();
	if ((a + (0x10000)) != 0x12328UL) abort();
	if ((a + (0x10000000UL)) != 0x10002328UL) abort();
	if ((a + (2147483647UL)) != 2147492647UL) abort();
	if ((a + (0xffffffffUL)) != 4294976295ULL) abort();
	if ((a + (0xffffffffffffULL)) != 281474976719655ULL) abort();
	if ((a + (0xfffffffffffffffULL)) != 1152921504606855975ULL) abort();

	return 0;
}

int main(void)
{
	testcase_adddi3_reg64_reg_ranges();
	testcase_adddi3_reg64_const_ranges();

	return 0;
}
