#ifndef HASH_RMD320_H_
#define HASH_RMD320_H_

/* the five basic functions F(), G() and H() */
#define RMD320F(x, y, z)        ((x) ^ (y) ^ (z))
#define RMD320G(x, y, z)        (((x) & (y)) | (~(x) & (z)))
#define RMD320H(x, y, z)        (((x) | ~(y)) ^ (z))
#define RMD320I(x, y, z)        (((x) & (z)) | ((y) & ~(z)))
#define RMD320J(x, y, z)        ((x) ^ ((y) | ~(z)))

/* the ten basic operations FF() through III() */
#define RMD320FF(a, b, c, d, e, x, s)        \
	(a) += RMD320F((b), (c), (d)) + (x);\
	(a) = ROLc((a), (s)) + (e);\
	(c) = ROLc((c), 10);

#define RMD320GG(a, b, c, d, e, x, s)        \
	(a) += RMD320G((b), (c), (d)) + (x) + 0x5a827999UL;\
	(a) = ROLc((a), (s)) + (e);\
	(c) = ROLc((c), 10);

#define RMD320HH(a, b, c, d, e, x, s)        \
	(a) += RMD320H((b), (c), (d)) + (x) + 0x6ed9eba1UL;\
	(a) = ROLc((a), (s)) + (e);\
	(c) = ROLc((c), 10);

#define RMD320II(a, b, c, d, e, x, s)        \
	(a) += RMD320I((b), (c), (d)) + (x) + 0x8f1bbcdcUL;\
	(a) = ROLc((a), (s)) + (e);\
	(c) = ROLc((c), 10);

#define RMD320JJ(a, b, c, d, e, x, s)        \
	(a) += RMD320J((b), (c), (d)) + (x) + 0xa953fd4eUL;\
	(a) = ROLc((a), (s)) + (e);\
	(c) = ROLc((c), 10);

#define RMD320FFF(a, b, c, d, e, x, s)        \
	(a) += RMD320F((b), (c), (d)) + (x);\
	(a) = ROLc((a), (s)) + (e);\
	(c) = ROLc((c), 10);

#define RMD320GGG(a, b, c, d, e, x, s)        \
	(a) += RMD320G((b), (c), (d)) + (x) + 0x7a6d76e9UL;\
	(a) = ROLc((a), (s)) + (e);\
	(c) = ROLc((c), 10);

#define RMD320HHH(a, b, c, d, e, x, s)        \
	(a) += RMD320H((b), (c), (d)) + (x) + 0x6d703ef3UL;\
	(a) = ROLc((a), (s)) + (e);\
	(c) = ROLc((c), 10);

#define RMD320III(a, b, c, d, e, x, s)        \
	(a) += RMD320I((b), (c), (d)) + (x) + 0x5c4dd124UL;\
	(a) = ROLc((a), (s)) + (e);\
	(c) = ROLc((c), 10);

#define RMD320JJJ(a, b, c, d, e, x, s)        \
	(a) += RMD320J((b), (c), (d)) + (x) + 0x50a28be6UL;\
	(a) = ROLc((a), (s)) + (e);\
	(c) = ROLc((c), 10);

struct RMD320_CTX {
	ulong64 length;
	unsigned char buf[64];
	ulong32 curlen, state[10];
};

class CRMD320 : public CHashUpdate<CRMD320>
{
	RMD320_CTX m_context;
public:
	enum { nDigestLength = 20};

	int  Compress( unsigned char *buf)
	{
		ulong32 aa,bb,cc,dd,ee,aaa,bbb,ccc,ddd,eee,tmp,X[16];
		int i;

		/* load words X */
		for (i = 0; i < 16; i++){
			LOAD32L(X[i], buf + (4 * i));
		}

		/* load state */
		aa = m_context.state[0];
		bb = m_context.state[1];
		cc = m_context.state[2];
		dd = m_context.state[3];
		ee = m_context.state[4];
		aaa = m_context.state[5];
		bbb = m_context.state[6];
		ccc = m_context.state[7];
		ddd = m_context.state[8];
		eee = m_context.state[9];

		/* round 1 */
		RMD320FF(aa, bb, cc, dd, ee, X[ 0], 11);
		RMD320FF(ee, aa, bb, cc, dd, X[ 1], 14);
		RMD320FF(dd, ee, aa, bb, cc, X[ 2], 15);
		RMD320FF(cc, dd, ee, aa, bb, X[ 3], 12);
		RMD320FF(bb, cc, dd, ee, aa, X[ 4],  5);
		RMD320FF(aa, bb, cc, dd, ee, X[ 5],  8);
		RMD320FF(ee, aa, bb, cc, dd, X[ 6],  7);
		RMD320FF(dd, ee, aa, bb, cc, X[ 7],  9);
		RMD320FF(cc, dd, ee, aa, bb, X[ 8], 11);
		RMD320FF(bb, cc, dd, ee, aa, X[ 9], 13);
		RMD320FF(aa, bb, cc, dd, ee, X[10], 14);
		RMD320FF(ee, aa, bb, cc, dd, X[11], 15);
		RMD320FF(dd, ee, aa, bb, cc, X[12],  6);
		RMD320FF(cc, dd, ee, aa, bb, X[13],  7);
		RMD320FF(bb, cc, dd, ee, aa, X[14],  9);
		RMD320FF(aa, bb, cc, dd, ee, X[15],  8);
    
		/* parallel round 1 */
		RMD320JJJ(aaa, bbb, ccc, ddd, eee, X[ 5],  8);
		RMD320JJJ(eee, aaa, bbb, ccc, ddd, X[14],  9);
		RMD320JJJ(ddd, eee, aaa, bbb, ccc, X[ 7],  9);
		RMD320JJJ(ccc, ddd, eee, aaa, bbb, X[ 0], 11);
		RMD320JJJ(bbb, ccc, ddd, eee, aaa, X[ 9], 13);
		RMD320JJJ(aaa, bbb, ccc, ddd, eee, X[ 2], 15);
		RMD320JJJ(eee, aaa, bbb, ccc, ddd, X[11], 15);
		RMD320JJJ(ddd, eee, aaa, bbb, ccc, X[ 4],  5);
		RMD320JJJ(ccc, ddd, eee, aaa, bbb, X[13],  7);
		RMD320JJJ(bbb, ccc, ddd, eee, aaa, X[ 6],  7);
		RMD320JJJ(aaa, bbb, ccc, ddd, eee, X[15],  8);
		RMD320JJJ(eee, aaa, bbb, ccc, ddd, X[ 8], 11);
		RMD320JJJ(ddd, eee, aaa, bbb, ccc, X[ 1], 14);
		RMD320JJJ(ccc, ddd, eee, aaa, bbb, X[10], 14);
		RMD320JJJ(bbb, ccc, ddd, eee, aaa, X[ 3], 12);
		RMD320JJJ(aaa, bbb, ccc, ddd, eee, X[12],  6);
    
		tmp = aa; aa = aaa; aaa = tmp;
    
		/* round 2 */
		RMD320GG(ee, aa, bb, cc, dd, X[ 7],  7);
		RMD320GG(dd, ee, aa, bb, cc, X[ 4],  6);
		RMD320GG(cc, dd, ee, aa, bb, X[13],  8);
		RMD320GG(bb, cc, dd, ee, aa, X[ 1], 13);
		RMD320GG(aa, bb, cc, dd, ee, X[10], 11);
		RMD320GG(ee, aa, bb, cc, dd, X[ 6],  9);
		RMD320GG(dd, ee, aa, bb, cc, X[15],  7);
		RMD320GG(cc, dd, ee, aa, bb, X[ 3], 15);
		RMD320GG(bb, cc, dd, ee, aa, X[12],  7);
		RMD320GG(aa, bb, cc, dd, ee, X[ 0], 12);
		RMD320GG(ee, aa, bb, cc, dd, X[ 9], 15);
		RMD320GG(dd, ee, aa, bb, cc, X[ 5],  9);
		RMD320GG(cc, dd, ee, aa, bb, X[ 2], 11);
		RMD320GG(bb, cc, dd, ee, aa, X[14],  7);
		RMD320GG(aa, bb, cc, dd, ee, X[11], 13);
		RMD320GG(ee, aa, bb, cc, dd, X[ 8], 12);
    
		/* parallel round 2 */
		RMD320III(eee, aaa, bbb, ccc, ddd, X[ 6],  9);
		RMD320III(ddd, eee, aaa, bbb, ccc, X[11], 13);
		RMD320III(ccc, ddd, eee, aaa, bbb, X[ 3], 15);
		RMD320III(bbb, ccc, ddd, eee, aaa, X[ 7],  7);
		RMD320III(aaa, bbb, ccc, ddd, eee, X[ 0], 12);
		RMD320III(eee, aaa, bbb, ccc, ddd, X[13],  8);
		RMD320III(ddd, eee, aaa, bbb, ccc, X[ 5],  9);
		RMD320III(ccc, ddd, eee, aaa, bbb, X[10], 11);
		RMD320III(bbb, ccc, ddd, eee, aaa, X[14],  7);
		RMD320III(aaa, bbb, ccc, ddd, eee, X[15],  7);
		RMD320III(eee, aaa, bbb, ccc, ddd, X[ 8], 12);
		RMD320III(ddd, eee, aaa, bbb, ccc, X[12],  7);
		RMD320III(ccc, ddd, eee, aaa, bbb, X[ 4],  6);
		RMD320III(bbb, ccc, ddd, eee, aaa, X[ 9], 15);
		RMD320III(aaa, bbb, ccc, ddd, eee, X[ 1], 13);
		RMD320III(eee, aaa, bbb, ccc, ddd, X[ 2], 11);
    
		tmp = bb; bb = bbb; bbb = tmp;
    
		/* round 3 */
		RMD320HH(dd, ee, aa, bb, cc, X[ 3], 11);
		RMD320HH(cc, dd, ee, aa, bb, X[10], 13);
		RMD320HH(bb, cc, dd, ee, aa, X[14],  6);
		RMD320HH(aa, bb, cc, dd, ee, X[ 4],  7);
		RMD320HH(ee, aa, bb, cc, dd, X[ 9], 14);
		RMD320HH(dd, ee, aa, bb, cc, X[15],  9);
		RMD320HH(cc, dd, ee, aa, bb, X[ 8], 13);
		RMD320HH(bb, cc, dd, ee, aa, X[ 1], 15);
		RMD320HH(aa, bb, cc, dd, ee, X[ 2], 14);
		RMD320HH(ee, aa, bb, cc, dd, X[ 7],  8);
		RMD320HH(dd, ee, aa, bb, cc, X[ 0], 13);
		RMD320HH(cc, dd, ee, aa, bb, X[ 6],  6);
		RMD320HH(bb, cc, dd, ee, aa, X[13],  5);
		RMD320HH(aa, bb, cc, dd, ee, X[11], 12);
		RMD320HH(ee, aa, bb, cc, dd, X[ 5],  7);
		RMD320HH(dd, ee, aa, bb, cc, X[12],  5);
    
		/* parallel round 3 */
		RMD320HHH(ddd, eee, aaa, bbb, ccc, X[15],  9);
		RMD320HHH(ccc, ddd, eee, aaa, bbb, X[ 5],  7);
		RMD320HHH(bbb, ccc, ddd, eee, aaa, X[ 1], 15);
		RMD320HHH(aaa, bbb, ccc, ddd, eee, X[ 3], 11);
		RMD320HHH(eee, aaa, bbb, ccc, ddd, X[ 7],  8);
		RMD320HHH(ddd, eee, aaa, bbb, ccc, X[14],  6);
		RMD320HHH(ccc, ddd, eee, aaa, bbb, X[ 6],  6);
		RMD320HHH(bbb, ccc, ddd, eee, aaa, X[ 9], 14);
		RMD320HHH(aaa, bbb, ccc, ddd, eee, X[11], 12);
		RMD320HHH(eee, aaa, bbb, ccc, ddd, X[ 8], 13);
		RMD320HHH(ddd, eee, aaa, bbb, ccc, X[12],  5);
		RMD320HHH(ccc, ddd, eee, aaa, bbb, X[ 2], 14);
		RMD320HHH(bbb, ccc, ddd, eee, aaa, X[10], 13);
		RMD320HHH(aaa, bbb, ccc, ddd, eee, X[ 0], 13);
		RMD320HHH(eee, aaa, bbb, ccc, ddd, X[ 4],  7);
		RMD320HHH(ddd, eee, aaa, bbb, ccc, X[13],  5);
    
		tmp = cc; cc = ccc; ccc = tmp;
    
		/* round 4 */
		RMD320II(cc, dd, ee, aa, bb, X[ 1], 11);
		RMD320II(bb, cc, dd, ee, aa, X[ 9], 12);
		RMD320II(aa, bb, cc, dd, ee, X[11], 14);
		RMD320II(ee, aa, bb, cc, dd, X[10], 15);
		RMD320II(dd, ee, aa, bb, cc, X[ 0], 14);
		RMD320II(cc, dd, ee, aa, bb, X[ 8], 15);
		RMD320II(bb, cc, dd, ee, aa, X[12],  9);
		RMD320II(aa, bb, cc, dd, ee, X[ 4],  8);
		RMD320II(ee, aa, bb, cc, dd, X[13],  9);
		RMD320II(dd, ee, aa, bb, cc, X[ 3], 14);
		RMD320II(cc, dd, ee, aa, bb, X[ 7],  5);
		RMD320II(bb, cc, dd, ee, aa, X[15],  6);
		RMD320II(aa, bb, cc, dd, ee, X[14],  8);
		RMD320II(ee, aa, bb, cc, dd, X[ 5],  6);
		RMD320II(dd, ee, aa, bb, cc, X[ 6],  5);
		RMD320II(cc, dd, ee, aa, bb, X[ 2], 12);
    
		/* parallel round 4 */
		RMD320GGG(ccc, ddd, eee, aaa, bbb, X[ 8], 15);
		RMD320GGG(bbb, ccc, ddd, eee, aaa, X[ 6],  5);
		RMD320GGG(aaa, bbb, ccc, ddd, eee, X[ 4],  8);
		RMD320GGG(eee, aaa, bbb, ccc, ddd, X[ 1], 11);
		RMD320GGG(ddd, eee, aaa, bbb, ccc, X[ 3], 14);
		RMD320GGG(ccc, ddd, eee, aaa, bbb, X[11], 14);
		RMD320GGG(bbb, ccc, ddd, eee, aaa, X[15],  6);
		RMD320GGG(aaa, bbb, ccc, ddd, eee, X[ 0], 14);
		RMD320GGG(eee, aaa, bbb, ccc, ddd, X[ 5],  6);
		RMD320GGG(ddd, eee, aaa, bbb, ccc, X[12],  9);
		RMD320GGG(ccc, ddd, eee, aaa, bbb, X[ 2], 12);
		RMD320GGG(bbb, ccc, ddd, eee, aaa, X[13],  9);
		RMD320GGG(aaa, bbb, ccc, ddd, eee, X[ 9], 12);
		RMD320GGG(eee, aaa, bbb, ccc, ddd, X[ 7],  5);
		RMD320GGG(ddd, eee, aaa, bbb, ccc, X[10], 15);
		RMD320GGG(ccc, ddd, eee, aaa, bbb, X[14],  8);
    
		tmp = dd; dd = ddd; ddd = tmp;
    
		/* round 5 */
		RMD320JJ(bb, cc, dd, ee, aa, X[ 4],  9);
		RMD320JJ(aa, bb, cc, dd, ee, X[ 0], 15);
		RMD320JJ(ee, aa, bb, cc, dd, X[ 5],  5);
		RMD320JJ(dd, ee, aa, bb, cc, X[ 9], 11);
		RMD320JJ(cc, dd, ee, aa, bb, X[ 7],  6);
		RMD320JJ(bb, cc, dd, ee, aa, X[12],  8);
		RMD320JJ(aa, bb, cc, dd, ee, X[ 2], 13);
		RMD320JJ(ee, aa, bb, cc, dd, X[10], 12);
		RMD320JJ(dd, ee, aa, bb, cc, X[14],  5);
		RMD320JJ(cc, dd, ee, aa, bb, X[ 1], 12);
		RMD320JJ(bb, cc, dd, ee, aa, X[ 3], 13);
		RMD320JJ(aa, bb, cc, dd, ee, X[ 8], 14);
		RMD320JJ(ee, aa, bb, cc, dd, X[11], 11);
		RMD320JJ(dd, ee, aa, bb, cc, X[ 6],  8);
		RMD320JJ(cc, dd, ee, aa, bb, X[15],  5);
		RMD320JJ(bb, cc, dd, ee, aa, X[13],  6);
    
		/* parallel round 5 */
		RMD320FFF(bbb, ccc, ddd, eee, aaa, X[12] ,  8);
		RMD320FFF(aaa, bbb, ccc, ddd, eee, X[15] ,  5);
		RMD320FFF(eee, aaa, bbb, ccc, ddd, X[10] , 12);
		RMD320FFF(ddd, eee, aaa, bbb, ccc, X[ 4] ,  9);
		RMD320FFF(ccc, ddd, eee, aaa, bbb, X[ 1] , 12);
		RMD320FFF(bbb, ccc, ddd, eee, aaa, X[ 5] ,  5);
		RMD320FFF(aaa, bbb, ccc, ddd, eee, X[ 8] , 14);
		RMD320FFF(eee, aaa, bbb, ccc, ddd, X[ 7] ,  6);
		RMD320FFF(ddd, eee, aaa, bbb, ccc, X[ 6] ,  8);
		RMD320FFF(ccc, ddd, eee, aaa, bbb, X[ 2] , 13);
		RMD320FFF(bbb, ccc, ddd, eee, aaa, X[13] ,  6);
		RMD320FFF(aaa, bbb, ccc, ddd, eee, X[14] ,  5);
		RMD320FFF(eee, aaa, bbb, ccc, ddd, X[ 0] , 15);
		RMD320FFF(ddd, eee, aaa, bbb, ccc, X[ 3] , 13);
		RMD320FFF(ccc, ddd, eee, aaa, bbb, X[ 9] , 11);
		RMD320FFF(bbb, ccc, ddd, eee, aaa, X[11] , 11);

		tmp = ee; ee = eee; eee = tmp;

		/* combine results */
		m_context.state[0] += aa;
		m_context.state[1] += bb;
		m_context.state[2] += cc;
		m_context.state[3] += dd;
		m_context.state[4] += ee;
		m_context.state[5] += aaa;
		m_context.state[6] += bbb;
		m_context.state[7] += ccc;
		m_context.state[8] += ddd;
		m_context.state[9] += eee;

		return 0;
	}

	int Init()
	{
		m_context.state[0] = 0x67452301UL;
		m_context.state[1] = 0xefcdab89UL;
		m_context.state[2] = 0x98badcfeUL;
		m_context.state[3] = 0x10325476UL;
		m_context.state[4] = 0xc3d2e1f0UL;
		m_context.state[5] = 0x76543210UL;
		m_context.state[6] = 0xfedcba98UL;
		m_context.state[7] = 0x89abcdefUL;
		m_context.state[8] = 0x01234567UL;
		m_context.state[9] = 0x3c2d1e0fUL;
		m_context.curlen   = 0;
		m_context.length   = 0;
		return 0;
	}

	int Update(unsigned char * pData, unsigned long ulLen)
	{
		return CHashUpdate<CRMD320>::Update(pData, 
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
		for (i = 0; i < 10; i++) 
		{
			STORE32L(m_context.state[i], pszOut+(4*i));
		}

		return 0;
	}
};
#endif