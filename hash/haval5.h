#ifndef HASH_HAVAL5_H_
#define HASH_HAVAL5_H_

#include "haval4.h"

#define HAVAL_PASS 5

#define haval_Fphi_1(x6, x5, x4, x3, x2, x1, x0) \
	haval_f_1(x3, x4, x1, x0, x5, x2, x6)

#define haval_Fphi_2(x6, x5, x4, x3, x2, x1, x0) \
	haval_f_2(x6, x2, x1, x0, x3, x4, x5)

#define haval_Fphi_3(x6, x5, x4, x3, x2, x1, x0) \
	haval_f_3(x2, x6, x0, x4, x3, x1, x5)

#define haval_Fphi_4(x6, x5, x4, x3, x2, x1, x0) \
	haval_f_4(x1, x5, x3, x2, x0, x4, x6)

#define haval_Fphi_5(x6, x5, x4, x3, x2, x1, x0) \
	haval_f_5(x2, x5, x0, x6, x4, x3, x1)

#define haval_FF_1(x7, x6, x5, x4, x3, x2, x1, x0, w) {                        \
	register unsigned long temp = haval_Fphi_1(x6, x5, x4, x3, x2, x1, x0);     \
	(x7) = haval_rotate_right(temp, 7) + haval_rotate_right((x7), 11) + (w);       \
}

#define haval_FF_2(x7, x6, x5, x4, x3, x2, x1, x0, w, c) {                      \
	register unsigned long temp = haval_Fphi_2(x6, x5, x4, x3, x2, x1, x0);      \
	(x7) = haval_rotate_right(temp, 7) + haval_rotate_right((x7), 11) + (w) + (c);  \
}

#define haval_FF_3(x7, x6, x5, x4, x3, x2, x1, x0, w, c) {                      \
	register unsigned long temp = haval_Fphi_3(x6, x5, x4, x3, x2, x1, x0);      \
	(x7) = haval_rotate_right(temp, 7) + haval_rotate_right((x7), 11) + (w) + (c);  \
}

#define haval_FF_4(x7, x6, x5, x4, x3, x2, x1, x0, w, c) {                      \
	register unsigned long temp = haval_Fphi_4(x6, x5, x4, x3, x2, x1, x0);      \
	(x7) = haval_rotate_right(temp, 7) + haval_rotate_right((x7), 11) + (w) + (c);  \
}

#define haval_FF_5(x7, x6, x5, x4, x3, x2, x1, x0, w, c) {                      \
	register unsigned long temp = haval_Fphi_5(x6, x5, x4, x3, x2, x1, x0);      \
	(x7) = haval_rotate_right(temp, 7) + haval_rotate_right((x7), 11) + (w) + (c);  \
}

template<int HAVAL_FPTLEN>
class CHAVAL5 : public CHAVAL4<HAVAL_FPTLEN>, public CHavalUpdateFinal<CHAVAL5<HAVAL_FPTLEN> >
{
protected:
	void haval_pass123 (unsigned long& t0,
		unsigned long& t1,
		unsigned long& t2,
		unsigned long& t3,
		unsigned long& t4,
		unsigned long& t5,
		unsigned long& t6,
		unsigned long& t7)
	{
		t0 = CHAVAL3<HAVAL_FPTLEN>::m_context.fingerprint[0];
		t1 = CHAVAL3<HAVAL_FPTLEN>::m_context.fingerprint[1];
		t2 = CHAVAL3<HAVAL_FPTLEN>::m_context.fingerprint[2];
		t3 = CHAVAL3<HAVAL_FPTLEN>::m_context.fingerprint[3];
		t4 = CHAVAL3<HAVAL_FPTLEN>::m_context.fingerprint[4];
		t5 = CHAVAL3<HAVAL_FPTLEN>::m_context.fingerprint[5];
		t6 = CHAVAL3<HAVAL_FPTLEN>::m_context.fingerprint[6];
		t7 = CHAVAL3<HAVAL_FPTLEN>::m_context.fingerprint[7];
		unsigned long	*w = CHAVAL3<HAVAL_FPTLEN>::m_context.block;

		/* Pass 1 */
		haval_FF_1(t7, t6, t5, t4, t3, t2, t1, t0, *(w   ));
		haval_FF_1(t6, t5, t4, t3, t2, t1, t0, t7, *(w+ 1));
		haval_FF_1(t5, t4, t3, t2, t1, t0, t7, t6, *(w+ 2));
		haval_FF_1(t4, t3, t2, t1, t0, t7, t6, t5, *(w+ 3));
		haval_FF_1(t3, t2, t1, t0, t7, t6, t5, t4, *(w+ 4));
		haval_FF_1(t2, t1, t0, t7, t6, t5, t4, t3, *(w+ 5));
		haval_FF_1(t1, t0, t7, t6, t5, t4, t3, t2, *(w+ 6));
		haval_FF_1(t0, t7, t6, t5, t4, t3, t2, t1, *(w+ 7));

		haval_FF_1(t7, t6, t5, t4, t3, t2, t1, t0, *(w+ 8));
		haval_FF_1(t6, t5, t4, t3, t2, t1, t0, t7, *(w+ 9));
		haval_FF_1(t5, t4, t3, t2, t1, t0, t7, t6, *(w+10));
		haval_FF_1(t4, t3, t2, t1, t0, t7, t6, t5, *(w+11));
		haval_FF_1(t3, t2, t1, t0, t7, t6, t5, t4, *(w+12));
		haval_FF_1(t2, t1, t0, t7, t6, t5, t4, t3, *(w+13));
		haval_FF_1(t1, t0, t7, t6, t5, t4, t3, t2, *(w+14));
		haval_FF_1(t0, t7, t6, t5, t4, t3, t2, t1, *(w+15));

		haval_FF_1(t7, t6, t5, t4, t3, t2, t1, t0, *(w+16));
		haval_FF_1(t6, t5, t4, t3, t2, t1, t0, t7, *(w+17));
		haval_FF_1(t5, t4, t3, t2, t1, t0, t7, t6, *(w+18));
		haval_FF_1(t4, t3, t2, t1, t0, t7, t6, t5, *(w+19));
		haval_FF_1(t3, t2, t1, t0, t7, t6, t5, t4, *(w+20));
		haval_FF_1(t2, t1, t0, t7, t6, t5, t4, t3, *(w+21));
		haval_FF_1(t1, t0, t7, t6, t5, t4, t3, t2, *(w+22));
		haval_FF_1(t0, t7, t6, t5, t4, t3, t2, t1, *(w+23));

		haval_FF_1(t7, t6, t5, t4, t3, t2, t1, t0, *(w+24));
		haval_FF_1(t6, t5, t4, t3, t2, t1, t0, t7, *(w+25));
		haval_FF_1(t5, t4, t3, t2, t1, t0, t7, t6, *(w+26));
		haval_FF_1(t4, t3, t2, t1, t0, t7, t6, t5, *(w+27));
		haval_FF_1(t3, t2, t1, t0, t7, t6, t5, t4, *(w+28));
		haval_FF_1(t2, t1, t0, t7, t6, t5, t4, t3, *(w+29));
		haval_FF_1(t1, t0, t7, t6, t5, t4, t3, t2, *(w+30));
		haval_FF_1(t0, t7, t6, t5, t4, t3, t2, t1, *(w+31));

		/* Pass 2 */
		haval_FF_2(t7, t6, t5, t4, t3, t2, t1, t0, *(w+ 5), 0x452821E6L);
		haval_FF_2(t6, t5, t4, t3, t2, t1, t0, t7, *(w+14), 0x38D01377L);
		haval_FF_2(t5, t4, t3, t2, t1, t0, t7, t6, *(w+26), 0xBE5466CFL);
		haval_FF_2(t4, t3, t2, t1, t0, t7, t6, t5, *(w+18), 0x34E90C6CL);
		haval_FF_2(t3, t2, t1, t0, t7, t6, t5, t4, *(w+11), 0xC0AC29B7L);
		haval_FF_2(t2, t1, t0, t7, t6, t5, t4, t3, *(w+28), 0xC97C50DDL);
		haval_FF_2(t1, t0, t7, t6, t5, t4, t3, t2, *(w+ 7), 0x3F84D5B5L);
		haval_FF_2(t0, t7, t6, t5, t4, t3, t2, t1, *(w+16), 0xB5470917L);

		haval_FF_2(t7, t6, t5, t4, t3, t2, t1, t0, *(w   ), 0x9216D5D9L);
		haval_FF_2(t6, t5, t4, t3, t2, t1, t0, t7, *(w+23), 0x8979FB1BL);
		haval_FF_2(t5, t4, t3, t2, t1, t0, t7, t6, *(w+20), 0xD1310BA6L);
		haval_FF_2(t4, t3, t2, t1, t0, t7, t6, t5, *(w+22), 0x98DFB5ACL);
		haval_FF_2(t3, t2, t1, t0, t7, t6, t5, t4, *(w+ 1), 0x2FFD72DBL);
		haval_FF_2(t2, t1, t0, t7, t6, t5, t4, t3, *(w+10), 0xD01ADFB7L);
		haval_FF_2(t1, t0, t7, t6, t5, t4, t3, t2, *(w+ 4), 0xB8E1AFEDL);
		haval_FF_2(t0, t7, t6, t5, t4, t3, t2, t1, *(w+ 8), 0x6A267E96L);

		haval_FF_2(t7, t6, t5, t4, t3, t2, t1, t0, *(w+30), 0xBA7C9045L);
		haval_FF_2(t6, t5, t4, t3, t2, t1, t0, t7, *(w+ 3), 0xF12C7F99L);
		haval_FF_2(t5, t4, t3, t2, t1, t0, t7, t6, *(w+21), 0x24A19947L);
		haval_FF_2(t4, t3, t2, t1, t0, t7, t6, t5, *(w+ 9), 0xB3916CF7L);
		haval_FF_2(t3, t2, t1, t0, t7, t6, t5, t4, *(w+17), 0x0801F2E2L);
		haval_FF_2(t2, t1, t0, t7, t6, t5, t4, t3, *(w+24), 0x858EFC16L);
		haval_FF_2(t1, t0, t7, t6, t5, t4, t3, t2, *(w+29), 0x636920D8L);
		haval_FF_2(t0, t7, t6, t5, t4, t3, t2, t1, *(w+ 6), 0x71574E69L);

		haval_FF_2(t7, t6, t5, t4, t3, t2, t1, t0, *(w+19), 0xA458FEA3L);
		haval_FF_2(t6, t5, t4, t3, t2, t1, t0, t7, *(w+12), 0xF4933D7EL);
		haval_FF_2(t5, t4, t3, t2, t1, t0, t7, t6, *(w+15), 0x0D95748FL);
		haval_FF_2(t4, t3, t2, t1, t0, t7, t6, t5, *(w+13), 0x728EB658L);
		haval_FF_2(t3, t2, t1, t0, t7, t6, t5, t4, *(w+ 2), 0x718BCD58L);
		haval_FF_2(t2, t1, t0, t7, t6, t5, t4, t3, *(w+25), 0x82154AEEL);
		haval_FF_2(t1, t0, t7, t6, t5, t4, t3, t2, *(w+31), 0x7B54A41DL);
		haval_FF_2(t0, t7, t6, t5, t4, t3, t2, t1, *(w+27), 0xC25A59B5L);

		/* Pass 3 */
		haval_FF_3(t7, t6, t5, t4, t3, t2, t1, t0, *(w+19), 0x9C30D539L);
		haval_FF_3(t6, t5, t4, t3, t2, t1, t0, t7, *(w+ 9), 0x2AF26013L);
		haval_FF_3(t5, t4, t3, t2, t1, t0, t7, t6, *(w+ 4), 0xC5D1B023L);
		haval_FF_3(t4, t3, t2, t1, t0, t7, t6, t5, *(w+20), 0x286085F0L);
		haval_FF_3(t3, t2, t1, t0, t7, t6, t5, t4, *(w+28), 0xCA417918L);
		haval_FF_3(t2, t1, t0, t7, t6, t5, t4, t3, *(w+17), 0xB8DB38EFL);
		haval_FF_3(t1, t0, t7, t6, t5, t4, t3, t2, *(w+ 8), 0x8E79DCB0L);
		haval_FF_3(t0, t7, t6, t5, t4, t3, t2, t1, *(w+22), 0x603A180EL);

		haval_FF_3(t7, t6, t5, t4, t3, t2, t1, t0, *(w+29), 0x6C9E0E8BL);
		haval_FF_3(t6, t5, t4, t3, t2, t1, t0, t7, *(w+14), 0xB01E8A3EL);
		haval_FF_3(t5, t4, t3, t2, t1, t0, t7, t6, *(w+25), 0xD71577C1L);
		haval_FF_3(t4, t3, t2, t1, t0, t7, t6, t5, *(w+12), 0xBD314B27L);
		haval_FF_3(t3, t2, t1, t0, t7, t6, t5, t4, *(w+24), 0x78AF2FDAL);
		haval_FF_3(t2, t1, t0, t7, t6, t5, t4, t3, *(w+30), 0x55605C60L);
		haval_FF_3(t1, t0, t7, t6, t5, t4, t3, t2, *(w+16), 0xE65525F3L);
		haval_FF_3(t0, t7, t6, t5, t4, t3, t2, t1, *(w+26), 0xAA55AB94L);

		haval_FF_3(t7, t6, t5, t4, t3, t2, t1, t0, *(w+31), 0x57489862L);
		haval_FF_3(t6, t5, t4, t3, t2, t1, t0, t7, *(w+15), 0x63E81440L);
		haval_FF_3(t5, t4, t3, t2, t1, t0, t7, t6, *(w+ 7), 0x55CA396AL);
		haval_FF_3(t4, t3, t2, t1, t0, t7, t6, t5, *(w+ 3), 0x2AAB10B6L);
		haval_FF_3(t3, t2, t1, t0, t7, t6, t5, t4, *(w+ 1), 0xB4CC5C34L);
		haval_FF_3(t2, t1, t0, t7, t6, t5, t4, t3, *(w   ), 0x1141E8CEL);
		haval_FF_3(t1, t0, t7, t6, t5, t4, t3, t2, *(w+18), 0xA15486AFL);
		haval_FF_3(t0, t7, t6, t5, t4, t3, t2, t1, *(w+27), 0x7C72E993L);

		haval_FF_3(t7, t6, t5, t4, t3, t2, t1, t0, *(w+13), 0xB3EE1411L);
		haval_FF_3(t6, t5, t4, t3, t2, t1, t0, t7, *(w+ 6), 0x636FBC2AL);
		haval_FF_3(t5, t4, t3, t2, t1, t0, t7, t6, *(w+21), 0x2BA9C55DL);
		haval_FF_3(t4, t3, t2, t1, t0, t7, t6, t5, *(w+10), 0x741831F6L);
		haval_FF_3(t3, t2, t1, t0, t7, t6, t5, t4, *(w+23), 0xCE5C3E16L);
		haval_FF_3(t2, t1, t0, t7, t6, t5, t4, t3, *(w+11), 0x9B87931EL);
		haval_FF_3(t1, t0, t7, t6, t5, t4, t3, t2, *(w+ 5), 0xAFD6BA33L);
		haval_FF_3(t0, t7, t6, t5, t4, t3, t2, t1, *(w+ 2), 0x6C24CF5CL);
	}

	void haval_pass4 (unsigned long& t0,
		unsigned long& t1,
		unsigned long& t2,
		unsigned long& t3,
		unsigned long& t4,
		unsigned long& t5,
		unsigned long& t6,
		unsigned long& t7)
	{
		unsigned long	*w = CHAVAL3<HAVAL_FPTLEN>::m_context.block;

		haval_FF_4(t7, t6, t5, t4, t3, t2, t1, t0, *(w+24), 0x7A325381L);
		haval_FF_4(t6, t5, t4, t3, t2, t1, t0, t7, *(w+ 4), 0x28958677L);
		haval_FF_4(t5, t4, t3, t2, t1, t0, t7, t6, *(w   ), 0x3B8F4898L);
		haval_FF_4(t4, t3, t2, t1, t0, t7, t6, t5, *(w+14), 0x6B4BB9AFL);
		haval_FF_4(t3, t2, t1, t0, t7, t6, t5, t4, *(w+ 2), 0xC4BFE81BL);
		haval_FF_4(t2, t1, t0, t7, t6, t5, t4, t3, *(w+ 7), 0x66282193L);
		haval_FF_4(t1, t0, t7, t6, t5, t4, t3, t2, *(w+28), 0x61D809CCL);
		haval_FF_4(t0, t7, t6, t5, t4, t3, t2, t1, *(w+23), 0xFB21A991L);

		haval_FF_4(t7, t6, t5, t4, t3, t2, t1, t0, *(w+26), 0x487CAC60L);
		haval_FF_4(t6, t5, t4, t3, t2, t1, t0, t7, *(w+ 6), 0x5DEC8032L);
		haval_FF_4(t5, t4, t3, t2, t1, t0, t7, t6, *(w+30), 0xEF845D5DL);
		haval_FF_4(t4, t3, t2, t1, t0, t7, t6, t5, *(w+20), 0xE98575B1L);
		haval_FF_4(t3, t2, t1, t0, t7, t6, t5, t4, *(w+18), 0xDC262302L);
		haval_FF_4(t2, t1, t0, t7, t6, t5, t4, t3, *(w+25), 0xEB651B88L);
		haval_FF_4(t1, t0, t7, t6, t5, t4, t3, t2, *(w+19), 0x23893E81L);
		haval_FF_4(t0, t7, t6, t5, t4, t3, t2, t1, *(w+ 3), 0xD396ACC5L);

		haval_FF_4(t7, t6, t5, t4, t3, t2, t1, t0, *(w+22), 0x0F6D6FF3L);
		haval_FF_4(t6, t5, t4, t3, t2, t1, t0, t7, *(w+11), 0x83F44239L);
		haval_FF_4(t5, t4, t3, t2, t1, t0, t7, t6, *(w+31), 0x2E0B4482L);
		haval_FF_4(t4, t3, t2, t1, t0, t7, t6, t5, *(w+21), 0xA4842004L);
		haval_FF_4(t3, t2, t1, t0, t7, t6, t5, t4, *(w+ 8), 0x69C8F04AL);
		haval_FF_4(t2, t1, t0, t7, t6, t5, t4, t3, *(w+27), 0x9E1F9B5EL);
		haval_FF_4(t1, t0, t7, t6, t5, t4, t3, t2, *(w+12), 0x21C66842L);
		haval_FF_4(t0, t7, t6, t5, t4, t3, t2, t1, *(w+ 9), 0xF6E96C9AL);

		haval_FF_4(t7, t6, t5, t4, t3, t2, t1, t0, *(w+ 1), 0x670C9C61L);
		haval_FF_4(t6, t5, t4, t3, t2, t1, t0, t7, *(w+29), 0xABD388F0L);
		haval_FF_4(t5, t4, t3, t2, t1, t0, t7, t6, *(w+ 5), 0x6A51A0D2L);
		haval_FF_4(t4, t3, t2, t1, t0, t7, t6, t5, *(w+15), 0xD8542F68L);
		haval_FF_4(t3, t2, t1, t0, t7, t6, t5, t4, *(w+17), 0x960FA728L);
		haval_FF_4(t2, t1, t0, t7, t6, t5, t4, t3, *(w+10), 0xAB5133A3L);
		haval_FF_4(t1, t0, t7, t6, t5, t4, t3, t2, *(w+16), 0x6EEF0B6CL);
		haval_FF_4(t0, t7, t6, t5, t4, t3, t2, t1, *(w+13), 0x137A3BE4L);
	}

	void haval_pass5 (unsigned long& t0,
		unsigned long& t1,
		unsigned long& t2,
		unsigned long& t3,
		unsigned long& t4,
		unsigned long& t5,
		unsigned long& t6,
		unsigned long& t7)
	{
		unsigned long	*w = CHAVAL3<HAVAL_FPTLEN>::m_context.block;

		haval_FF_5(t7, t6, t5, t4, t3, t2, t1, t0, *(w+27), 0xBA3BF050L);
		haval_FF_5(t6, t5, t4, t3, t2, t1, t0, t7, *(w+ 3), 0x7EFB2A98L);
		haval_FF_5(t5, t4, t3, t2, t1, t0, t7, t6, *(w+21), 0xA1F1651DL);
		haval_FF_5(t4, t3, t2, t1, t0, t7, t6, t5, *(w+26), 0x39AF0176L);
		haval_FF_5(t3, t2, t1, t0, t7, t6, t5, t4, *(w+17), 0x66CA593EL);
		haval_FF_5(t2, t1, t0, t7, t6, t5, t4, t3, *(w+11), 0x82430E88L);
		haval_FF_5(t1, t0, t7, t6, t5, t4, t3, t2, *(w+20), 0x8CEE8619L);
		haval_FF_5(t0, t7, t6, t5, t4, t3, t2, t1, *(w+29), 0x456F9FB4L);

		haval_FF_5(t7, t6, t5, t4, t3, t2, t1, t0, *(w+19), 0x7D84A5C3L);
		haval_FF_5(t6, t5, t4, t3, t2, t1, t0, t7, *(w   ), 0x3B8B5EBEL);
		haval_FF_5(t5, t4, t3, t2, t1, t0, t7, t6, *(w+12), 0xE06F75D8L);
		haval_FF_5(t4, t3, t2, t1, t0, t7, t6, t5, *(w+ 7), 0x85C12073L);
		haval_FF_5(t3, t2, t1, t0, t7, t6, t5, t4, *(w+13), 0x401A449FL);
		haval_FF_5(t2, t1, t0, t7, t6, t5, t4, t3, *(w+ 8), 0x56C16AA6L);
		haval_FF_5(t1, t0, t7, t6, t5, t4, t3, t2, *(w+31), 0x4ED3AA62L);
		haval_FF_5(t0, t7, t6, t5, t4, t3, t2, t1, *(w+10), 0x363F7706L);

		haval_FF_5(t7, t6, t5, t4, t3, t2, t1, t0, *(w+ 5), 0x1BFEDF72L);
		haval_FF_5(t6, t5, t4, t3, t2, t1, t0, t7, *(w+ 9), 0x429B023DL);
		haval_FF_5(t5, t4, t3, t2, t1, t0, t7, t6, *(w+14), 0x37D0D724L);
		haval_FF_5(t4, t3, t2, t1, t0, t7, t6, t5, *(w+30), 0xD00A1248L);
		haval_FF_5(t3, t2, t1, t0, t7, t6, t5, t4, *(w+18), 0xDB0FEAD3L);
		haval_FF_5(t2, t1, t0, t7, t6, t5, t4, t3, *(w+ 6), 0x49F1C09BL);
		haval_FF_5(t1, t0, t7, t6, t5, t4, t3, t2, *(w+28), 0x075372C9L);
		haval_FF_5(t0, t7, t6, t5, t4, t3, t2, t1, *(w+24), 0x80991B7BL);

		haval_FF_5(t7, t6, t5, t4, t3, t2, t1, t0, *(w+ 2), 0x25D479D8L);
		haval_FF_5(t6, t5, t4, t3, t2, t1, t0, t7, *(w+23), 0xF6E8DEF7L);
		haval_FF_5(t5, t4, t3, t2, t1, t0, t7, t6, *(w+16), 0xE3FE501AL);
		haval_FF_5(t4, t3, t2, t1, t0, t7, t6, t5, *(w+22), 0xB6794C3BL);
		haval_FF_5(t3, t2, t1, t0, t7, t6, t5, t4, *(w+ 4), 0x976CE0BDL);
		haval_FF_5(t2, t1, t0, t7, t6, t5, t4, t3, *(w+ 1), 0x04C006BAL);
		haval_FF_5(t1, t0, t7, t6, t5, t4, t3, t2, *(w+25), 0xC1A94FB6L);
		haval_FF_5(t0, t7, t6, t5, t4, t3, t2, t1, *(w+15), 0x409F60C4L);
	}

public:
	void haval_hash_block()
	{
		unsigned long t0, t1, t2, t3,t4,t5,t6,t7;

		haval_pass123(t0,t1,t2,t3,t4,t5,t6,t7);
		haval_pass4(t0,t1,t2,t3,t4,t5,t6,t7);
		haval_pass5(t0,t1,t2,t3,t4,t5,t6,t7);

		CHAVAL3<HAVAL_FPTLEN>::m_context.fingerprint[0] += t0;
		CHAVAL3<HAVAL_FPTLEN>::m_context.fingerprint[1] += t1;
		CHAVAL3<HAVAL_FPTLEN>::m_context.fingerprint[2] += t2;
		CHAVAL3<HAVAL_FPTLEN>::m_context.fingerprint[3] += t3;
		CHAVAL3<HAVAL_FPTLEN>::m_context.fingerprint[4] += t4;
		CHAVAL3<HAVAL_FPTLEN>::m_context.fingerprint[5] += t5;
		CHAVAL3<HAVAL_FPTLEN>::m_context.fingerprint[6] += t6;
		CHAVAL3<HAVAL_FPTLEN>::m_context.fingerprint[7] += t7;
	}

	int Update(unsigned char * pData, unsigned long ulLen)
	{
		return CHavalUpdateFinal<CHAVAL5<HAVAL_FPTLEN> >::Update(pData, ulLen, CHAVAL3<HAVAL_FPTLEN>::m_context);
	}

	int Final(unsigned char * pszOut)
	{
		return CHavalUpdateFinal<CHAVAL5<HAVAL_FPTLEN> >::Final(pszOut, HAVAL_PASS, CHAVAL3<HAVAL_FPTLEN>::m_context, HAVAL_FPTLEN);
	}

};

#undef haval_Fphi_1
#undef haval_Fphi_2
#undef haval_Fphi_3
#undef haval_Fphi_4
#undef haval_Fphi_5
#undef HAVAL_PASS
#endif