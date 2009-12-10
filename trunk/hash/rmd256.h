#ifndef HASH_RIPEMD256_H_
#define HASH_RIPEMD256_H_

/* the four basic functions F(), G() and H() */
#define RMD256F(x, y, z)        ((x) ^ (y) ^ (z))
#define RMD256G(x, y, z)        (((x) & (y)) | (~(x) & (z)))
#define RMD256H(x, y, z)        (((x) | ~(y)) ^ (z))
#define RMD256I(x, y, z)        (((x) & (z)) | ((y) & ~(z)))

/* the eight basic operations FF() through III() */
#define RMD256FF(a, b, c, d, x, s)        \
	(a) += RMD256F((b), (c), (d)) + (x);\
	(a) = ROLc((a), (s));

#define RMD256GG(a, b, c, d, x, s)        \
	(a) += RMD256G((b), (c), (d)) + (x) + 0x5a827999UL;\
	(a) = ROLc((a), (s));

#define RMD256HH(a, b, c, d, x, s)        \
	(a) += RMD256H((b), (c), (d)) + (x) + 0x6ed9eba1UL;\
	(a) = ROLc((a), (s));

#define RMD256II(a, b, c, d, x, s)        \
	(a) += RMD256I((b), (c), (d)) + (x) + 0x8f1bbcdcUL;\
	(a) = ROLc((a), (s));

#define RMD256FFF(a, b, c, d, x, s)        \
	(a) += RMD256F((b), (c), (d)) + (x);\
	(a) = ROLc((a), (s));

#define RMD256GGG(a, b, c, d, x, s)        \
	(a) += RMD256G((b), (c), (d)) + (x) + 0x6d703ef3UL;\
	(a) = ROLc((a), (s));

#define RMD256HHH(a, b, c, d, x, s)        \
	(a) += RMD256H((b), (c), (d)) + (x) + 0x5c4dd124UL;\
	(a) = ROLc((a), (s));

#define RMD256III(a, b, c, d, x, s)        \
	(a) += RMD256I((b), (c), (d)) + (x) + 0x50a28be6UL;\
	(a) = ROLc((a), (s));

struct RMD256_CTX {
	ulong64 length;
	unsigned char buf[64];
	ulong32 curlen, state[8];
};

class CRMD256 : public CHashUpdate<CRMD256>
{
	RMD256_CTX m_context;
public:
	enum { nDigestLength =16 };

	int  Compress(unsigned char *buf)
	{
		ulong32 aa,bb,cc,dd,aaa,bbb,ccc,ddd,tmp,X[16];
		int i;

		/* load words X */
		for (i = 0; i < 16; i++)
		{
			LOAD32L(X[i], buf + (4 * i));
		}

		/* load state */
		aa = m_context.state[0];
		bb = m_context.state[1];
		cc = m_context.state[2];
		dd = m_context.state[3];
		aaa = m_context.state[4];
		bbb = m_context.state[5];
		ccc = m_context.state[6];
		ddd = m_context.state[7];

		/* round 1 */
		RMD256FF(aa, bb, cc, dd, X[ 0], 11);
		RMD256FF(dd, aa, bb, cc, X[ 1], 14);
		RMD256FF(cc, dd, aa, bb, X[ 2], 15);
		RMD256FF(bb, cc, dd, aa, X[ 3], 12);
		RMD256FF(aa, bb, cc, dd, X[ 4],  5);
		RMD256FF(dd, aa, bb, cc, X[ 5],  8);
		RMD256FF(cc, dd, aa, bb, X[ 6],  7);
		RMD256FF(bb, cc, dd, aa, X[ 7],  9);
		RMD256FF(aa, bb, cc, dd, X[ 8], 11);
		RMD256FF(dd, aa, bb, cc, X[ 9], 13);
		RMD256FF(cc, dd, aa, bb, X[10], 14);
		RMD256FF(bb, cc, dd, aa, X[11], 15);
		RMD256FF(aa, bb, cc, dd, X[12],  6);
		RMD256FF(dd, aa, bb, cc, X[13],  7);
		RMD256FF(cc, dd, aa, bb, X[14],  9);
		RMD256FF(bb, cc, dd, aa, X[15],  8);
    
    /* parallel round 1 */
		RMD256III(aaa, bbb, ccc, ddd, X[ 5],  8);
		RMD256III(ddd, aaa, bbb, ccc, X[14],  9);
		RMD256III(ccc, ddd, aaa, bbb, X[ 7],  9);
		RMD256III(bbb, ccc, ddd, aaa, X[ 0], 11);
		RMD256III(aaa, bbb, ccc, ddd, X[ 9], 13);
		RMD256III(ddd, aaa, bbb, ccc, X[ 2], 15);
		RMD256III(ccc, ddd, aaa, bbb, X[11], 15);
		RMD256III(bbb, ccc, ddd, aaa, X[ 4],  5);
		RMD256III(aaa, bbb, ccc, ddd, X[13],  7);
		RMD256III(ddd, aaa, bbb, ccc, X[ 6],  7);
		RMD256III(ccc, ddd, aaa, bbb, X[15],  8);
		RMD256III(bbb, ccc, ddd, aaa, X[ 8], 11);
		RMD256III(aaa, bbb, ccc, ddd, X[ 1], 14);
		RMD256III(ddd, aaa, bbb, ccc, X[10], 14);
		RMD256III(ccc, ddd, aaa, bbb, X[ 3], 12);
		RMD256III(bbb, ccc, ddd, aaa, X[12],  6);
    
		tmp = aa; aa = aaa; aaa = tmp;
    
		/* round 2 */
		RMD256GG(aa, bb, cc, dd, X[ 7],  7);
		RMD256GG(dd, aa, bb, cc, X[ 4],  6);
		RMD256GG(cc, dd, aa, bb, X[13],  8);
		RMD256GG(bb, cc, dd, aa, X[ 1], 13);
		RMD256GG(aa, bb, cc, dd, X[10], 11);
		RMD256GG(dd, aa, bb, cc, X[ 6],  9);
		RMD256GG(cc, dd, aa, bb, X[15],  7);
		RMD256GG(bb, cc, dd, aa, X[ 3], 15);
		RMD256GG(aa, bb, cc, dd, X[12],  7);
		RMD256GG(dd, aa, bb, cc, X[ 0], 12);
		RMD256GG(cc, dd, aa, bb, X[ 9], 15);
		RMD256GG(bb, cc, dd, aa, X[ 5],  9);
		RMD256GG(aa, bb, cc, dd, X[ 2], 11);
		RMD256GG(dd, aa, bb, cc, X[14],  7);
		RMD256GG(cc, dd, aa, bb, X[11], 13);
		RMD256GG(bb, cc, dd, aa, X[ 8], 12);
    
		/* parallel round 2 */
		RMD256HHH(aaa, bbb, ccc, ddd, X[ 6],  9);
		RMD256HHH(ddd, aaa, bbb, ccc, X[11], 13);
		RMD256HHH(ccc, ddd, aaa, bbb, X[ 3], 15);
		RMD256HHH(bbb, ccc, ddd, aaa, X[ 7],  7);
		RMD256HHH(aaa, bbb, ccc, ddd, X[ 0], 12);
		RMD256HHH(ddd, aaa, bbb, ccc, X[13],  8);
		RMD256HHH(ccc, ddd, aaa, bbb, X[ 5],  9);
		RMD256HHH(bbb, ccc, ddd, aaa, X[10], 11);
		RMD256HHH(aaa, bbb, ccc, ddd, X[14],  7);
		RMD256HHH(ddd, aaa, bbb, ccc, X[15],  7);
		RMD256HHH(ccc, ddd, aaa, bbb, X[ 8], 12);
		RMD256HHH(bbb, ccc, ddd, aaa, X[12],  7);
		RMD256HHH(aaa, bbb, ccc, ddd, X[ 4],  6);
		RMD256HHH(ddd, aaa, bbb, ccc, X[ 9], 15);
		RMD256HHH(ccc, ddd, aaa, bbb, X[ 1], 13);
		RMD256HHH(bbb, ccc, ddd, aaa, X[ 2], 11);
    
		tmp = bb; bb = bbb; bbb = tmp;
    
		/* round 3 */
		RMD256HH(aa, bb, cc, dd, X[ 3], 11);
		RMD256HH(dd, aa, bb, cc, X[10], 13);
		RMD256HH(cc, dd, aa, bb, X[14],  6);
		RMD256HH(bb, cc, dd, aa, X[ 4],  7);
		RMD256HH(aa, bb, cc, dd, X[ 9], 14);
		RMD256HH(dd, aa, bb, cc, X[15],  9);
		RMD256HH(cc, dd, aa, bb, X[ 8], 13);
		RMD256HH(bb, cc, dd, aa, X[ 1], 15);
		RMD256HH(aa, bb, cc, dd, X[ 2], 14);
		RMD256HH(dd, aa, bb, cc, X[ 7],  8);
		RMD256HH(cc, dd, aa, bb, X[ 0], 13);
		RMD256HH(bb, cc, dd, aa, X[ 6],  6);
		RMD256HH(aa, bb, cc, dd, X[13],  5);
		RMD256HH(dd, aa, bb, cc, X[11], 12);
		RMD256HH(cc, dd, aa, bb, X[ 5],  7);
		RMD256HH(bb, cc, dd, aa, X[12],  5);
    
		/* parallel round 3 */
		RMD256GGG(aaa, bbb, ccc, ddd, X[15],  9);
		RMD256GGG(ddd, aaa, bbb, ccc, X[ 5],  7);
		RMD256GGG(ccc, ddd, aaa, bbb, X[ 1], 15);
		RMD256GGG(bbb, ccc, ddd, aaa, X[ 3], 11);
		RMD256GGG(aaa, bbb, ccc, ddd, X[ 7],  8);
		RMD256GGG(ddd, aaa, bbb, ccc, X[14],  6);
		RMD256GGG(ccc, ddd, aaa, bbb, X[ 6],  6);
		RMD256GGG(bbb, ccc, ddd, aaa, X[ 9], 14);
		RMD256GGG(aaa, bbb, ccc, ddd, X[11], 12);
		RMD256GGG(ddd, aaa, bbb, ccc, X[ 8], 13);
		RMD256GGG(ccc, ddd, aaa, bbb, X[12],  5);
		RMD256GGG(bbb, ccc, ddd, aaa, X[ 2], 14);
		RMD256GGG(aaa, bbb, ccc, ddd, X[10], 13);
		RMD256GGG(ddd, aaa, bbb, ccc, X[ 0], 13);
		RMD256GGG(ccc, ddd, aaa, bbb, X[ 4],  7);
		RMD256GGG(bbb, ccc, ddd, aaa, X[13],  5);
    
		tmp = cc; cc = ccc; ccc = tmp;
    
		/* round 4 */
		RMD256II(aa, bb, cc, dd, X[ 1], 11);
		RMD256II(dd, aa, bb, cc, X[ 9], 12);
		RMD256II(cc, dd, aa, bb, X[11], 14);
		RMD256II(bb, cc, dd, aa, X[10], 15);
		RMD256II(aa, bb, cc, dd, X[ 0], 14);
		RMD256II(dd, aa, bb, cc, X[ 8], 15);
		RMD256II(cc, dd, aa, bb, X[12],  9);
		RMD256II(bb, cc, dd, aa, X[ 4],  8);
		RMD256II(aa, bb, cc, dd, X[13],  9);
		RMD256II(dd, aa, bb, cc, X[ 3], 14);
		RMD256II(cc, dd, aa, bb, X[ 7],  5);
		RMD256II(bb, cc, dd, aa, X[15],  6);
		RMD256II(aa, bb, cc, dd, X[14],  8);
		RMD256II(dd, aa, bb, cc, X[ 5],  6);
		RMD256II(cc, dd, aa, bb, X[ 6],  5);
		RMD256II(bb, cc, dd, aa, X[ 2], 12);
    
		/* parallel round 4 */
		RMD256FFF(aaa, bbb, ccc, ddd, X[ 8], 15);
		RMD256FFF(ddd, aaa, bbb, ccc, X[ 6],  5);
		RMD256FFF(ccc, ddd, aaa, bbb, X[ 4],  8);
		RMD256FFF(bbb, ccc, ddd, aaa, X[ 1], 11);
		RMD256FFF(aaa, bbb, ccc, ddd, X[ 3], 14);
		RMD256FFF(ddd, aaa, bbb, ccc, X[11], 14);
		RMD256FFF(ccc, ddd, aaa, bbb, X[15],  6);
		RMD256FFF(bbb, ccc, ddd, aaa, X[ 0], 14);
		RMD256FFF(aaa, bbb, ccc, ddd, X[ 5],  6);
		RMD256FFF(ddd, aaa, bbb, ccc, X[12],  9);
		RMD256FFF(ccc, ddd, aaa, bbb, X[ 2], 12);
		RMD256FFF(bbb, ccc, ddd, aaa, X[13],  9);
		RMD256FFF(aaa, bbb, ccc, ddd, X[ 9], 12);
		RMD256FFF(ddd, aaa, bbb, ccc, X[ 7],  5);
		RMD256FFF(ccc, ddd, aaa, bbb, X[10], 15);
		RMD256FFF(bbb, ccc, ddd, aaa, X[14],  8);

		tmp = dd; dd = ddd; ddd = tmp;

		/* combine results */
		m_context.state[0] += aa;
		m_context.state[1] += bb;
		m_context.state[2] += cc;
		m_context.state[3] += dd;
		m_context.state[4] += aaa;
		m_context.state[5] += bbb;
		m_context.state[6] += ccc;
		m_context.state[7] += ddd;

		return 0;
	}

	int Init()
	{
		m_context.state[0] = 0x67452301UL;
		m_context.state[1] = 0xefcdab89UL;
		m_context.state[2] = 0x98badcfeUL;
		m_context.state[3] = 0x10325476UL;
		m_context.state[4] = 0x76543210UL;
		m_context.state[5] = 0xfedcba98UL;
		m_context.state[6] = 0x89abcdefUL;
		m_context.state[7] = 0x01234567UL;
		m_context.curlen   = 0;
		m_context.length   = 0;
		return 0;
	}

	int Update(unsigned char * pData, unsigned long ulLen)
	{
		return CHashUpdate<CRMD256>::Update(pData, 
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
			Compress( m_context.buf);
			m_context.curlen = 0;
		}

		/* pad upto 56 bytes of zeroes */
		while (m_context.curlen < 56) 
		{
			m_context.buf[m_context.curlen++] = (unsigned char)0;
		}

		/* store length */
		STORE64L(m_context.length, m_context.buf+56);
		Compress( m_context.buf);

		/* copy output */
		for (i = 0; i < 8; i++) 
		{
			STORE32L(m_context.state[i], pszOut+(4*i));
		}

		return 0;
	}

};


#endif