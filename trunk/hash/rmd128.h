#ifndef HASH_RIPEMD128_H_
#define HASH_RIPEMD128_H_

/* the four basic functions F(), G() and H() */
#define RMD128F(x, y, z)        ((x) ^ (y) ^ (z)) 
#define RMD128G(x, y, z)        (((x) & (y)) | (~(x) & (z))) 
#define RMD128H(x, y, z)        (((x) | ~(y)) ^ (z))
#define RMD128I(x, y, z)        (((x) & (z)) | ((y) & ~(z))) 

/* the eight basic operations FF() through III() */
#define RMD128FF(a, b, c, d, x, s)        \
	(a) += RMD128F((b), (c), (d)) + (x);\
	(a) = ROLc((a), (s));

#define RMD128GG(a, b, c, d, x, s)        \
	(a) += RMD128G((b), (c), (d)) + (x) + 0x5a827999UL;\
	(a) = ROLc((a), (s));

#define RMD128HH(a, b, c, d, x, s)        \
	(a) += RMD128H((b), (c), (d)) + (x) + 0x6ed9eba1UL;\
	(a) = ROLc((a), (s));

#define RMD128II(a, b, c, d, x, s)        \
	(a) += RMD128I((b), (c), (d)) + (x) + 0x8f1bbcdcUL;\
	(a) = ROLc((a), (s));

#define RMD128FFF(a, b, c, d, x, s)        \
	(a) += RMD128F((b), (c), (d)) + (x);\
	(a) = ROLc((a), (s));

#define RMD128GGG(a, b, c, d, x, s)        \
	(a) += RMD128G((b), (c), (d)) + (x) + 0x6d703ef3UL;\
	(a) = ROLc((a), (s));

#define RMD128HHH(a, b, c, d, x, s)        \
	(a) += RMD128H((b), (c), (d)) + (x) + 0x5c4dd124UL;\
	(a) = ROLc((a), (s));

#define RMD128III(a, b, c, d, x, s)        \
	(a) += RMD128I((b), (c), (d)) + (x) + 0x50a28be6UL;\
	(a) = ROLc((a), (s));

struct RMD128_CTX {
	ulong64 length;
	unsigned char buf[64];
	ulong32 curlen, state[4];
};

class CRMD128 : public CHashUpdate<CRMD128>
{
	RMD128_CTX m_context;
public:
	enum { nDigestLength =16 };

	int  Compress(unsigned char *buf)
	{
		ulong32 aa,bb,cc,dd,aaa,bbb,ccc,ddd,X[16];
		int i;

		/* load words X */
		for (i = 0; i < 16; i++){
			LOAD32L(X[i], buf + (4 * i));
		}

		/* load state */
		aa = aaa = m_context.state[0];
		bb = bbb = m_context.state[1];
		cc = ccc = m_context.state[2];
		dd = ddd = m_context.state[3];

		/* round 1 */
		RMD128FF(aa, bb, cc, dd, X[ 0], 11);
		RMD128FF(dd, aa, bb, cc, X[ 1], 14);
		RMD128FF(cc, dd, aa, bb, X[ 2], 15);
		RMD128FF(bb, cc, dd, aa, X[ 3], 12);
		RMD128FF(aa, bb, cc, dd, X[ 4],  5);
		RMD128FF(dd, aa, bb, cc, X[ 5],  8);
		RMD128FF(cc, dd, aa, bb, X[ 6],  7);
		RMD128FF(bb, cc, dd, aa, X[ 7],  9);
		RMD128FF(aa, bb, cc, dd, X[ 8], 11);
		RMD128FF(dd, aa, bb, cc, X[ 9], 13);
		RMD128FF(cc, dd, aa, bb, X[10], 14);
		RMD128FF(bb, cc, dd, aa, X[11], 15);
		RMD128FF(aa, bb, cc, dd, X[12],  6);
		RMD128FF(dd, aa, bb, cc, X[13],  7);
		RMD128FF(cc, dd, aa, bb, X[14],  9);
		RMD128FF(bb, cc, dd, aa, X[15],  8);

		/* round 2 */
		RMD128GG(aa, bb, cc, dd, X[ 7],  7);
		RMD128GG(dd, aa, bb, cc, X[ 4],  6);
		RMD128GG(cc, dd, aa, bb, X[13],  8);
		RMD128GG(bb, cc, dd, aa, X[ 1], 13);
		RMD128GG(aa, bb, cc, dd, X[10], 11);
		RMD128GG(dd, aa, bb, cc, X[ 6],  9);
		RMD128GG(cc, dd, aa, bb, X[15],  7);
		RMD128GG(bb, cc, dd, aa, X[ 3], 15);
		RMD128GG(aa, bb, cc, dd, X[12],  7);
		RMD128GG(dd, aa, bb, cc, X[ 0], 12);
		RMD128GG(cc, dd, aa, bb, X[ 9], 15);
		RMD128GG(bb, cc, dd, aa, X[ 5],  9);
		RMD128GG(aa, bb, cc, dd, X[ 2], 11);
		RMD128GG(dd, aa, bb, cc, X[14],  7);
		RMD128GG(cc, dd, aa, bb, X[11], 13);
		RMD128GG(bb, cc, dd, aa, X[ 8], 12);
    
		/* round 3 */
		RMD128HH(aa, bb, cc, dd, X[ 3], 11);
		RMD128HH(dd, aa, bb, cc, X[10], 13);
		RMD128HH(cc, dd, aa, bb, X[14],  6);
		RMD128HH(bb, cc, dd, aa, X[ 4],  7);
		RMD128HH(aa, bb, cc, dd, X[ 9], 14);
		RMD128HH(dd, aa, bb, cc, X[15],  9);
		RMD128HH(cc, dd, aa, bb, X[ 8], 13);
		RMD128HH(bb, cc, dd, aa, X[ 1], 15);
		RMD128HH(aa, bb, cc, dd, X[ 2], 14);
		RMD128HH(dd, aa, bb, cc, X[ 7],  8);
		RMD128HH(cc, dd, aa, bb, X[ 0], 13);
		RMD128HH(bb, cc, dd, aa, X[ 6],  6);
		RMD128HH(aa, bb, cc, dd, X[13],  5);
		RMD128HH(dd, aa, bb, cc, X[11], 12);
		RMD128HH(cc, dd, aa, bb, X[ 5],  7);
		RMD128HH(bb, cc, dd, aa, X[12],  5);
    
		/* round 4 */
		RMD128II(aa, bb, cc, dd, X[ 1], 11);
		RMD128II(dd, aa, bb, cc, X[ 9], 12);
		RMD128II(cc, dd, aa, bb, X[11], 14);
		RMD128II(bb, cc, dd, aa, X[10], 15);
		RMD128II(aa, bb, cc, dd, X[ 0], 14);
		RMD128II(dd, aa, bb, cc, X[ 8], 15);
		RMD128II(cc, dd, aa, bb, X[12],  9);
		RMD128II(bb, cc, dd, aa, X[ 4],  8);
		RMD128II(aa, bb, cc, dd, X[13],  9);
		RMD128II(dd, aa, bb, cc, X[ 3], 14);
		RMD128II(cc, dd, aa, bb, X[ 7],  5);
		RMD128II(bb, cc, dd, aa, X[15],  6);
		RMD128II(aa, bb, cc, dd, X[14],  8);
		RMD128II(dd, aa, bb, cc, X[ 5],  6);
		RMD128II(cc, dd, aa, bb, X[ 6],  5);
		RMD128II(bb, cc, dd, aa, X[ 2], 12);
    
		/* parallel round 1 */
		RMD128III(aaa, bbb, ccc, ddd, X[ 5],  8); 
		RMD128III(ddd, aaa, bbb, ccc, X[14],  9);
		RMD128III(ccc, ddd, aaa, bbb, X[ 7],  9);
		RMD128III(bbb, ccc, ddd, aaa, X[ 0], 11);
		RMD128III(aaa, bbb, ccc, ddd, X[ 9], 13);
		RMD128III(ddd, aaa, bbb, ccc, X[ 2], 15);
		RMD128III(ccc, ddd, aaa, bbb, X[11], 15);
		RMD128III(bbb, ccc, ddd, aaa, X[ 4],  5);
		RMD128III(aaa, bbb, ccc, ddd, X[13],  7);
		RMD128III(ddd, aaa, bbb, ccc, X[ 6],  7);
		RMD128III(ccc, ddd, aaa, bbb, X[15],  8);
		RMD128III(bbb, ccc, ddd, aaa, X[ 8], 11);
		RMD128III(aaa, bbb, ccc, ddd, X[ 1], 14);
		RMD128III(ddd, aaa, bbb, ccc, X[10], 14);
		RMD128III(ccc, ddd, aaa, bbb, X[ 3], 12);
		RMD128III(bbb, ccc, ddd, aaa, X[12],  6);
    
		/* parallel round 2 */
		RMD128HHH(aaa, bbb, ccc, ddd, X[ 6],  9);
		RMD128HHH(ddd, aaa, bbb, ccc, X[11], 13);
		RMD128HHH(ccc, ddd, aaa, bbb, X[ 3], 15);
		RMD128HHH(bbb, ccc, ddd, aaa, X[ 7],  7);
		RMD128HHH(aaa, bbb, ccc, ddd, X[ 0], 12);
		RMD128HHH(ddd, aaa, bbb, ccc, X[13],  8);
		RMD128HHH(ccc, ddd, aaa, bbb, X[ 5],  9);
		RMD128HHH(bbb, ccc, ddd, aaa, X[10], 11);
		RMD128HHH(aaa, bbb, ccc, ddd, X[14],  7);
		RMD128HHH(ddd, aaa, bbb, ccc, X[15],  7);
		RMD128HHH(ccc, ddd, aaa, bbb, X[ 8], 12);
		RMD128HHH(bbb, ccc, ddd, aaa, X[12],  7);
		RMD128HHH(aaa, bbb, ccc, ddd, X[ 4],  6);
		RMD128HHH(ddd, aaa, bbb, ccc, X[ 9], 15);
		RMD128HHH(ccc, ddd, aaa, bbb, X[ 1], 13);
		RMD128HHH(bbb, ccc, ddd, aaa, X[ 2], 11);
    
		/* parallel round 3 */   
		RMD128GGG(aaa, bbb, ccc, ddd, X[15],  9);
		RMD128GGG(ddd, aaa, bbb, ccc, X[ 5],  7);
		RMD128GGG(ccc, ddd, aaa, bbb, X[ 1], 15);
		RMD128GGG(bbb, ccc, ddd, aaa, X[ 3], 11);
		RMD128GGG(aaa, bbb, ccc, ddd, X[ 7],  8);
		RMD128GGG(ddd, aaa, bbb, ccc, X[14],  6);
		RMD128GGG(ccc, ddd, aaa, bbb, X[ 6],  6);
		RMD128GGG(bbb, ccc, ddd, aaa, X[ 9], 14);
		RMD128GGG(aaa, bbb, ccc, ddd, X[11], 12);
		RMD128GGG(ddd, aaa, bbb, ccc, X[ 8], 13);
		RMD128GGG(ccc, ddd, aaa, bbb, X[12],  5);
		RMD128GGG(bbb, ccc, ddd, aaa, X[ 2], 14);
		RMD128GGG(aaa, bbb, ccc, ddd, X[10], 13);
		RMD128GGG(ddd, aaa, bbb, ccc, X[ 0], 13);
		RMD128GGG(ccc, ddd, aaa, bbb, X[ 4],  7);
		RMD128GGG(bbb, ccc, ddd, aaa, X[13],  5);
    
		/* parallel round 4 */
		RMD128FFF(aaa, bbb, ccc, ddd, X[ 8], 15);
		RMD128FFF(ddd, aaa, bbb, ccc, X[ 6],  5);
		RMD128FFF(ccc, ddd, aaa, bbb, X[ 4],  8);
		RMD128FFF(bbb, ccc, ddd, aaa, X[ 1], 11);
		RMD128FFF(aaa, bbb, ccc, ddd, X[ 3], 14);
		RMD128FFF(ddd, aaa, bbb, ccc, X[11], 14);
		RMD128FFF(ccc, ddd, aaa, bbb, X[15],  6);
		RMD128FFF(bbb, ccc, ddd, aaa, X[ 0], 14);
		RMD128FFF(aaa, bbb, ccc, ddd, X[ 5],  6);
		RMD128FFF(ddd, aaa, bbb, ccc, X[12],  9);
		RMD128FFF(ccc, ddd, aaa, bbb, X[ 2], 12);
		RMD128FFF(bbb, ccc, ddd, aaa, X[13],  9);
		RMD128FFF(aaa, bbb, ccc, ddd, X[ 9], 12);
		RMD128FFF(ddd, aaa, bbb, ccc, X[ 7],  5);
		RMD128FFF(ccc, ddd, aaa, bbb, X[10], 15);
		RMD128FFF(bbb, ccc, ddd, aaa, X[14],  8);

		/* combine results */
		ddd += cc + m_context.state[1];               /* final result for MDbuf[0] */
		m_context.state[1] = m_context.state[2] + dd + aaa;
		m_context.state[2] = m_context.state[3] + aa + bbb;
		m_context.state[3] = m_context.state[0] + bb + ccc;
		m_context.state[0] = ddd;

		return 0;
	}

	int Init()
	{
		m_context.state[0] = 0x67452301UL;
		m_context.state[1] = 0xefcdab89UL;
		m_context.state[2] = 0x98badcfeUL;
		m_context.state[3] = 0x10325476UL;
		m_context.curlen   = 0;
		m_context.length   = 0;
		return 0;
	}

	int Update(unsigned char * pData, unsigned long ulLen)
	{
		return CHashUpdate<CRMD128>::Update(pData, 
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
		for (i = 0; i < 4; i++) 
		{
			STORE32L(m_context.state[i], pszOut+(4*i));
		}

		return 0;  
	}
};
#endif