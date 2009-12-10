#ifndef HASH_MD4_H_
#define HASH_MD4_H_

#define MD4S11 3
#define MD4S12 7
#define MD4S13 11
#define MD4S14 19
#define MD4S21 3
#define MD4S22 5
#define MD4S23 9
#define MD4S24 13
#define MD4S31 3
#define MD4S32 9
#define MD4S33 11
#define MD4S34 15

/* F, G and H are basic LTC_MD4 functions. */
#define MD4F(x, y, z) (z ^ (x & (y ^ z)))
#define MD4G(x, y, z) ((x & y) | (z & (x | y)))
#define MD4H(x, y, z) ((x) ^ (y) ^ (z))

/* ROTATE_LEFT rotates x left n bits. */
#define MD4ROTATE_LEFT(x, n) ROLc(x, n)

/* FF, GG and HH are transformations for rounds 1, 2 and 3 */ 
/* Rotation is separate from addition to prevent recomputation */ 

#define MD4FF(a, b, c, d, x, s) { \
	(a) += MD4F ((b), (c), (d)) + (x); \
	(a) = MD4ROTATE_LEFT ((a), (s)); \
}
#define MD4GG(a, b, c, d, x, s) { \
	(a) += MD4G ((b), (c), (d)) + (x) + 0x5a827999UL; \
	(a) = MD4ROTATE_LEFT ((a), (s)); \
}
#define MD4HH(a, b, c, d, x, s) { \
	(a) += MD4H ((b), (c), (d)) + (x) + 0x6ed9eba1UL; \
	(a) = MD4ROTATE_LEFT ((a), (s)); \
}


struct MD4_CTX {
	ulong64 length;
	ulong32 state[4], curlen;
	unsigned char buf[64];
};

class CMD4 : public CHashUpdate<CMD4>
{
	MD4_CTX m_context;
public:
	enum { nDigestLength =16 };

	int Compress(unsigned char *buf)
	{
		ulong32 x[16], a, b, c, d;
		int i;

		/* copy state */
		a = m_context.state[0];
		b = m_context.state[1];
		c = m_context.state[2];
		d = m_context.state[3];

		/* copy the state into 512-bits into W[0..15] */
		for (i = 0; i < 16; i++) 
		{
			LOAD32L(x[i], buf + (4*i));
		}

		/* Round 1 */ 
		MD4FF (a, b, c, d, x[ 0], MD4S11); /* 1 */ 
		MD4FF (d, a, b, c, x[ 1], MD4S12); /* 2 */ 
		MD4FF (c, d, a, b, x[ 2], MD4S13); /* 3 */ 
		MD4FF (b, c, d, a, x[ 3], MD4S14); /* 4 */ 
		MD4FF (a, b, c, d, x[ 4], MD4S11); /* 5 */ 
		MD4FF (d, a, b, c, x[ 5], MD4S12); /* 6 */ 
		MD4FF (c, d, a, b, x[ 6], MD4S13); /* 7 */ 
		MD4FF (b, c, d, a, x[ 7], MD4S14); /* 8 */ 
		MD4FF (a, b, c, d, x[ 8], MD4S11); /* 9 */ 
		MD4FF (d, a, b, c, x[ 9], MD4S12); /* 10 */
		MD4FF (c, d, a, b, x[10], MD4S13); /* 11 */ 
		MD4FF (b, c, d, a, x[11], MD4S14); /* 12 */
		MD4FF (a, b, c, d, x[12], MD4S11); /* 13 */
		MD4FF (d, a, b, c, x[13], MD4S12); /* 14 */ 
		MD4FF (c, d, a, b, x[14], MD4S13); /* 15 */ 
		MD4FF (b, c, d, a, x[15], MD4S14); /* 16 */ 
                              
		/* Round 2 */             
		MD4GG (a, b, c, d, x[ 0], MD4S21); /* 17 */ 
		MD4GG (d, a, b, c, x[ 4], MD4S22); /* 18 */ 
		MD4GG (c, d, a, b, x[ 8], MD4S23); /* 19 */ 
		MD4GG (b, c, d, a, x[12], MD4S24); /* 20 */ 
		MD4GG (a, b, c, d, x[ 1], MD4S21); /* 21 */ 
		MD4GG (d, a, b, c, x[ 5], MD4S22); /* 22 */ 
		MD4GG (c, d, a, b, x[ 9], MD4S23); /* 23 */ 
		MD4GG (b, c, d, a, x[13], MD4S24); /* 24 */ 
		MD4GG (a, b, c, d, x[ 2], MD4S21); /* 25 */ 
		MD4GG (d, a, b, c, x[ 6], MD4S22); /* 26 */ 
		MD4GG (c, d, a, b, x[10], MD4S23); /* 27 */ 
		MD4GG (b, c, d, a, x[14], MD4S24); /* 28 */ 
		MD4GG (a, b, c, d, x[ 3], MD4S21); /* 29 */ 
		MD4GG (d, a, b, c, x[ 7], MD4S22); /* 30 */ 
		MD4GG (c, d, a, b, x[11], MD4S23); /* 31 */ 
		MD4GG (b, c, d, a, x[15], MD4S24); /* 32 */ 
                              
		/* Round 3 */             
		MD4HH (a, b, c, d, x[ 0], MD4S31); /* 33 */ 
		MD4HH (d, a, b, c, x[ 8], MD4S32); /* 34 */ 
		MD4HH (c, d, a, b, x[ 4], MD4S33); /* 35 */ 
		MD4HH (b, c, d, a, x[12], MD4S34); /* 36 */ 
		MD4HH (a, b, c, d, x[ 2], MD4S31); /* 37 */ 
		MD4HH (d, a, b, c, x[10], MD4S32); /* 38 */ 
		MD4HH (c, d, a, b, x[ 6], MD4S33); /* 39 */ 
		MD4HH (b, c, d, a, x[14], MD4S34); /* 40 */ 
		MD4HH (a, b, c, d, x[ 1], MD4S31); /* 41 */ 
		MD4HH (d, a, b, c, x[ 9], MD4S32); /* 42 */ 
		MD4HH (c, d, a, b, x[ 5], MD4S33); /* 43 */ 
		MD4HH (b, c, d, a, x[13], MD4S34); /* 44 */ 
		MD4HH (a, b, c, d, x[ 3], MD4S31); /* 45 */ 
		MD4HH (d, a, b, c, x[11], MD4S32); /* 46 */ 
		MD4HH (c, d, a, b, x[ 7], MD4S33); /* 47 */ 
		MD4HH (b, c, d, a, x[15], MD4S34); /* 48 */ 


		/* Update our state */
		m_context.state[0] = m_context.state[0] + a;
		m_context.state[1] = m_context.state[1] + b;
		m_context.state[2] = m_context.state[2] + c;
		m_context.state[3] = m_context.state[3] + d;

		return 0;
	}

	int Init()
	{
		m_context.state[0] = 0x67452301UL;
		m_context.state[1] = 0xefcdab89UL;
		m_context.state[2] = 0x98badcfeUL;
		m_context.state[3] = 0x10325476UL;
		m_context.length  = 0;
		m_context.curlen  = 0;
		return 0;
	}

	int Update(unsigned char * pData, unsigned long ulLen)
	{
		return CHashUpdate<CMD4>::Update(pData, 
			ulLen, 
			m_context.curlen, 
			m_context.length, 
			m_context.buf, 
			sizeof(m_context.buf));
	}

	int Final(unsigned char *pszOut)
	{
		int i;

		if (m_context.curlen >= sizeof(m_context.buf)) 
		{
			return -1;
		}

		/* increase the length of the message */
		m_context.length += m_context.curlen * 8;

		/* append the '1' bit */
		m_context.buf[m_context.curlen++] = (unsigned char)0x80;

		/* if the length is currently above 56 bytes we append zeros
		* then compress.  Then we can fall back to padding zeros and length
		* encoding like normal.
		*/
		if (m_context.curlen > 56) 
		{
			while (m_context.curlen < 64) 
			{
				m_context.buf[m_context.curlen++] = (unsigned char)0;
			}
			Compress(m_context.buf);
			m_context.curlen = 0;
		}

		/* pad upto 56 bytes of zeroes */
		while (m_context.curlen < 56) 
		{
			m_context.buf[m_context.curlen++] = (unsigned char)0;
		}

		/* store length */
		STORE64L(m_context.length, m_context.buf+56);
		Compress(m_context.buf);

		/* copy output */
		for (i = 0; i < 4; i++) {
			STORE32L(m_context.state[i], pszOut+(4*i));
		}

		return 0;
	}
};
#endif