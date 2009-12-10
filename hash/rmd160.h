#ifndef HASH_RIPEME160_H_
#define HASH_RIPEME160_H_

/* the five basic functions F(), G() and H() */
#define RMD160F(x, y, z)        ((x) ^ (y) ^ (z)) 
#define RMD160G(x, y, z)        (((x) & (y)) | (~(x) & (z))) 
#define RMD160H(x, y, z)        (((x) | ~(y)) ^ (z))
#define RMD160I(x, y, z)        (((x) & (z)) | ((y) & ~(z))) 
#define RMD160J(x, y, z)        ((x) ^ ((y) | ~(z)))

/* the ten basic operations FF() through III() */
#define RMD160FF(a, b, c, d, e, x, s)        \
	(a) += RMD160F((b), (c), (d)) + (x);\
	(a) = ROLc((a), (s)) + (e);\
	(c) = ROLc((c), 10);

#define RMD160GG(a, b, c, d, e, x, s)        \
	(a) += RMD160G((b), (c), (d)) + (x) + 0x5a827999UL;\
	(a) = ROLc((a), (s)) + (e);\
	(c) = ROLc((c), 10);

#define RMD160HH(a, b, c, d, e, x, s)        \
	(a) += RMD160H((b), (c), (d)) + (x) + 0x6ed9eba1UL;\
	(a) = ROLc((a), (s)) + (e);\
	(c) = ROLc((c), 10);

#define RMD160II(a, b, c, d, e, x, s)        \
	(a) += RMD160I((b), (c), (d)) + (x) + 0x8f1bbcdcUL;\
	(a) = ROLc((a), (s)) + (e);\
	(c) = ROLc((c), 10);

#define RMD160JJ(a, b, c, d, e, x, s)        \
	(a) += RMD160J((b), (c), (d)) + (x) + 0xa953fd4eUL;\
	(a) = ROLc((a), (s)) + (e);\
	(c) = ROLc((c), 10);

#define RMD160FFF(a, b, c, d, e, x, s)        \
	(a) += RMD160F((b), (c), (d)) + (x);\
	(a) = ROLc((a), (s)) + (e);\
	(c) = ROLc((c), 10);

#define RMD160GGG(a, b, c, d, e, x, s)        \
	(a) += RMD160G((b), (c), (d)) + (x) + 0x7a6d76e9UL;\
	(a) = ROLc((a), (s)) + (e);\
	(c) = ROLc((c), 10);

#define RMD160HHH(a, b, c, d, e, x, s)        \
	(a) += RMD160H((b), (c), (d)) + (x) + 0x6d703ef3UL;\
	(a) = ROLc((a), (s)) + (e);\
	(c) = ROLc((c), 10);

#define RMD160III(a, b, c, d, e, x, s)        \
	(a) += RMD160I((b), (c), (d)) + (x) + 0x5c4dd124UL;\
	(a) = ROLc((a), (s)) + (e);\
	(c) = ROLc((c), 10);

#define RMD160JJJ(a, b, c, d, e, x, s)        \
	(a) += RMD160J((b), (c), (d)) + (x) + 0x50a28be6UL;\
	(a) = ROLc((a), (s)) + (e);\
	(c) = ROLc((c), 10);


struct RMD160_CTX {
	ulong64 length;
	unsigned char buf[64];
	ulong32 curlen, state[5];
};

class CRMD160 : public CHashUpdate<CRMD160>
{
	RMD160_CTX m_context;
public:
	enum { nDigestLength =20 };

	int  Compress(unsigned char *buf)
	{
		ulong32 aa,bb,cc,dd,ee,aaa,bbb,ccc,ddd,eee,X[16];
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
		ee = eee = m_context.state[4];

		/* round 1 */
		RMD160FF(aa, bb, cc, dd, ee, X[ 0], 11);
		RMD160FF(ee, aa, bb, cc, dd, X[ 1], 14);
		RMD160FF(dd, ee, aa, bb, cc, X[ 2], 15);
		RMD160FF(cc, dd, ee, aa, bb, X[ 3], 12);
		RMD160FF(bb, cc, dd, ee, aa, X[ 4],  5);
		RMD160FF(aa, bb, cc, dd, ee, X[ 5],  8);
		RMD160FF(ee, aa, bb, cc, dd, X[ 6],  7);
		RMD160FF(dd, ee, aa, bb, cc, X[ 7],  9);
		RMD160FF(cc, dd, ee, aa, bb, X[ 8], 11);
		RMD160FF(bb, cc, dd, ee, aa, X[ 9], 13);
		RMD160FF(aa, bb, cc, dd, ee, X[10], 14);
		RMD160FF(ee, aa, bb, cc, dd, X[11], 15);
		RMD160FF(dd, ee, aa, bb, cc, X[12],  6);
		RMD160FF(cc, dd, ee, aa, bb, X[13],  7);
		RMD160FF(bb, cc, dd, ee, aa, X[14],  9);
		RMD160FF(aa, bb, cc, dd, ee, X[15],  8);
    
		/* round 2 */
		RMD160GG(ee, aa, bb, cc, dd, X[ 7],  7);
		RMD160GG(dd, ee, aa, bb, cc, X[ 4],  6);
		RMD160GG(cc, dd, ee, aa, bb, X[13],  8);
		RMD160GG(bb, cc, dd, ee, aa, X[ 1], 13);
		RMD160GG(aa, bb, cc, dd, ee, X[10], 11);
		RMD160GG(ee, aa, bb, cc, dd, X[ 6],  9);
		RMD160GG(dd, ee, aa, bb, cc, X[15],  7);
		RMD160GG(cc, dd, ee, aa, bb, X[ 3], 15);
		RMD160GG(bb, cc, dd, ee, aa, X[12],  7);
		RMD160GG(aa, bb, cc, dd, ee, X[ 0], 12);
		RMD160GG(ee, aa, bb, cc, dd, X[ 9], 15);
		RMD160GG(dd, ee, aa, bb, cc, X[ 5],  9);
		RMD160GG(cc, dd, ee, aa, bb, X[ 2], 11);
		RMD160GG(bb, cc, dd, ee, aa, X[14],  7);
		RMD160GG(aa, bb, cc, dd, ee, X[11], 13);
		RMD160GG(ee, aa, bb, cc, dd, X[ 8], 12);
    
		/* round 3 */
		RMD160HH(dd, ee, aa, bb, cc, X[ 3], 11);
		RMD160HH(cc, dd, ee, aa, bb, X[10], 13);
		RMD160HH(bb, cc, dd, ee, aa, X[14],  6);
		RMD160HH(aa, bb, cc, dd, ee, X[ 4],  7);
		RMD160HH(ee, aa, bb, cc, dd, X[ 9], 14);
		RMD160HH(dd, ee, aa, bb, cc, X[15],  9);
		RMD160HH(cc, dd, ee, aa, bb, X[ 8], 13);
		RMD160HH(bb, cc, dd, ee, aa, X[ 1], 15);
		RMD160HH(aa, bb, cc, dd, ee, X[ 2], 14);
		RMD160HH(ee, aa, bb, cc, dd, X[ 7],  8);
		RMD160HH(dd, ee, aa, bb, cc, X[ 0], 13);
		RMD160HH(cc, dd, ee, aa, bb, X[ 6],  6);
		RMD160HH(bb, cc, dd, ee, aa, X[13],  5);
		RMD160HH(aa, bb, cc, dd, ee, X[11], 12);
		RMD160HH(ee, aa, bb, cc, dd, X[ 5],  7);
		RMD160HH(dd, ee, aa, bb, cc, X[12],  5);
    
		/* round 4 */
		RMD160II(cc, dd, ee, aa, bb, X[ 1], 11);
		RMD160II(bb, cc, dd, ee, aa, X[ 9], 12);
		RMD160II(aa, bb, cc, dd, ee, X[11], 14);
		RMD160II(ee, aa, bb, cc, dd, X[10], 15);
		RMD160II(dd, ee, aa, bb, cc, X[ 0], 14);
		RMD160II(cc, dd, ee, aa, bb, X[ 8], 15);
		RMD160II(bb, cc, dd, ee, aa, X[12],  9);
		RMD160II(aa, bb, cc, dd, ee, X[ 4],  8);
		RMD160II(ee, aa, bb, cc, dd, X[13],  9);
		RMD160II(dd, ee, aa, bb, cc, X[ 3], 14);
		RMD160II(cc, dd, ee, aa, bb, X[ 7],  5);
		RMD160II(bb, cc, dd, ee, aa, X[15],  6);
		RMD160II(aa, bb, cc, dd, ee, X[14],  8);
		RMD160II(ee, aa, bb, cc, dd, X[ 5],  6);
		RMD160II(dd, ee, aa, bb, cc, X[ 6],  5);
		RMD160II(cc, dd, ee, aa, bb, X[ 2], 12);
    
		/* round 5 */
		RMD160JJ(bb, cc, dd, ee, aa, X[ 4],  9);
		RMD160JJ(aa, bb, cc, dd, ee, X[ 0], 15);
		RMD160JJ(ee, aa, bb, cc, dd, X[ 5],  5);
		RMD160JJ(dd, ee, aa, bb, cc, X[ 9], 11);
		RMD160JJ(cc, dd, ee, aa, bb, X[ 7],  6);
		RMD160JJ(bb, cc, dd, ee, aa, X[12],  8);
		RMD160JJ(aa, bb, cc, dd, ee, X[ 2], 13);
		RMD160JJ(ee, aa, bb, cc, dd, X[10], 12);
		RMD160JJ(dd, ee, aa, bb, cc, X[14],  5);
		RMD160JJ(cc, dd, ee, aa, bb, X[ 1], 12);
		RMD160JJ(bb, cc, dd, ee, aa, X[ 3], 13);
		RMD160JJ(aa, bb, cc, dd, ee, X[ 8], 14);
		RMD160JJ(ee, aa, bb, cc, dd, X[11], 11);
		RMD160JJ(dd, ee, aa, bb, cc, X[ 6],  8);
		RMD160JJ(cc, dd, ee, aa, bb, X[15],  5);
		RMD160JJ(bb, cc, dd, ee, aa, X[13],  6);
    
		/* parallel round 1 */
		RMD160JJJ(aaa, bbb, ccc, ddd, eee, X[ 5],  8);
		RMD160JJJ(eee, aaa, bbb, ccc, ddd, X[14],  9);
		RMD160JJJ(ddd, eee, aaa, bbb, ccc, X[ 7],  9);
		RMD160JJJ(ccc, ddd, eee, aaa, bbb, X[ 0], 11);
		RMD160JJJ(bbb, ccc, ddd, eee, aaa, X[ 9], 13);
		RMD160JJJ(aaa, bbb, ccc, ddd, eee, X[ 2], 15);
		RMD160JJJ(eee, aaa, bbb, ccc, ddd, X[11], 15);
		RMD160JJJ(ddd, eee, aaa, bbb, ccc, X[ 4],  5);
		RMD160JJJ(ccc, ddd, eee, aaa, bbb, X[13],  7);
		RMD160JJJ(bbb, ccc, ddd, eee, aaa, X[ 6],  7);
		RMD160JJJ(aaa, bbb, ccc, ddd, eee, X[15],  8);
		RMD160JJJ(eee, aaa, bbb, ccc, ddd, X[ 8], 11);
		RMD160JJJ(ddd, eee, aaa, bbb, ccc, X[ 1], 14);
		RMD160JJJ(ccc, ddd, eee, aaa, bbb, X[10], 14);
		RMD160JJJ(bbb, ccc, ddd, eee, aaa, X[ 3], 12);
		RMD160JJJ(aaa, bbb, ccc, ddd, eee, X[12],  6);
    
		/* parallel round 2 */
		RMD160III(eee, aaa, bbb, ccc, ddd, X[ 6],  9); 
		RMD160III(ddd, eee, aaa, bbb, ccc, X[11], 13);
		RMD160III(ccc, ddd, eee, aaa, bbb, X[ 3], 15);
		RMD160III(bbb, ccc, ddd, eee, aaa, X[ 7],  7);
		RMD160III(aaa, bbb, ccc, ddd, eee, X[ 0], 12);
		RMD160III(eee, aaa, bbb, ccc, ddd, X[13],  8);
		RMD160III(ddd, eee, aaa, bbb, ccc, X[ 5],  9);
		RMD160III(ccc, ddd, eee, aaa, bbb, X[10], 11);
		RMD160III(bbb, ccc, ddd, eee, aaa, X[14],  7);
		RMD160III(aaa, bbb, ccc, ddd, eee, X[15],  7);
		RMD160III(eee, aaa, bbb, ccc, ddd, X[ 8], 12);
		RMD160III(ddd, eee, aaa, bbb, ccc, X[12],  7);
		RMD160III(ccc, ddd, eee, aaa, bbb, X[ 4],  6);
		RMD160III(bbb, ccc, ddd, eee, aaa, X[ 9], 15);
		RMD160III(aaa, bbb, ccc, ddd, eee, X[ 1], 13);
		RMD160III(eee, aaa, bbb, ccc, ddd, X[ 2], 11);
    
		/* parallel round 3 */
		RMD160HHH(ddd, eee, aaa, bbb, ccc, X[15],  9);
		RMD160HHH(ccc, ddd, eee, aaa, bbb, X[ 5],  7);
		RMD160HHH(bbb, ccc, ddd, eee, aaa, X[ 1], 15);
		RMD160HHH(aaa, bbb, ccc, ddd, eee, X[ 3], 11);
		RMD160HHH(eee, aaa, bbb, ccc, ddd, X[ 7],  8);
		RMD160HHH(ddd, eee, aaa, bbb, ccc, X[14],  6);
		RMD160HHH(ccc, ddd, eee, aaa, bbb, X[ 6],  6);
		RMD160HHH(bbb, ccc, ddd, eee, aaa, X[ 9], 14);
		RMD160HHH(aaa, bbb, ccc, ddd, eee, X[11], 12);
		RMD160HHH(eee, aaa, bbb, ccc, ddd, X[ 8], 13);
		RMD160HHH(ddd, eee, aaa, bbb, ccc, X[12],  5);
		RMD160HHH(ccc, ddd, eee, aaa, bbb, X[ 2], 14);
		RMD160HHH(bbb, ccc, ddd, eee, aaa, X[10], 13);
		RMD160HHH(aaa, bbb, ccc, ddd, eee, X[ 0], 13);
		RMD160HHH(eee, aaa, bbb, ccc, ddd, X[ 4],  7);
		RMD160HHH(ddd, eee, aaa, bbb, ccc, X[13],  5);
    
		/* parallel round 4 */   
		RMD160GGG(ccc, ddd, eee, aaa, bbb, X[ 8], 15);
		RMD160GGG(bbb, ccc, ddd, eee, aaa, X[ 6],  5);
		RMD160GGG(aaa, bbb, ccc, ddd, eee, X[ 4],  8);
		RMD160GGG(eee, aaa, bbb, ccc, ddd, X[ 1], 11);
		RMD160GGG(ddd, eee, aaa, bbb, ccc, X[ 3], 14);
		RMD160GGG(ccc, ddd, eee, aaa, bbb, X[11], 14);
		RMD160GGG(bbb, ccc, ddd, eee, aaa, X[15],  6);
		RMD160GGG(aaa, bbb, ccc, ddd, eee, X[ 0], 14);
		RMD160GGG(eee, aaa, bbb, ccc, ddd, X[ 5],  6);
		RMD160GGG(ddd, eee, aaa, bbb, ccc, X[12],  9);
		RMD160GGG(ccc, ddd, eee, aaa, bbb, X[ 2], 12);
		RMD160GGG(bbb, ccc, ddd, eee, aaa, X[13],  9);
		RMD160GGG(aaa, bbb, ccc, ddd, eee, X[ 9], 12);
		RMD160GGG(eee, aaa, bbb, ccc, ddd, X[ 7],  5);
		RMD160GGG(ddd, eee, aaa, bbb, ccc, X[10], 15);
		RMD160GGG(ccc, ddd, eee, aaa, bbb, X[14],  8);
    
		/* parallel round 5 */
		RMD160FFF(bbb, ccc, ddd, eee, aaa, X[12] ,  8);
		RMD160FFF(aaa, bbb, ccc, ddd, eee, X[15] ,  5);
		RMD160FFF(eee, aaa, bbb, ccc, ddd, X[10] , 12);
		RMD160FFF(ddd, eee, aaa, bbb, ccc, X[ 4] ,  9);
		RMD160FFF(ccc, ddd, eee, aaa, bbb, X[ 1] , 12);
		RMD160FFF(bbb, ccc, ddd, eee, aaa, X[ 5] ,  5);
		RMD160FFF(aaa, bbb, ccc, ddd, eee, X[ 8] , 14);
		RMD160FFF(eee, aaa, bbb, ccc, ddd, X[ 7] ,  6);
		RMD160FFF(ddd, eee, aaa, bbb, ccc, X[ 6] ,  8);
		RMD160FFF(ccc, ddd, eee, aaa, bbb, X[ 2] , 13);
		RMD160FFF(bbb, ccc, ddd, eee, aaa, X[13] ,  6);
		RMD160FFF(aaa, bbb, ccc, ddd, eee, X[14] ,  5);
		RMD160FFF(eee, aaa, bbb, ccc, ddd, X[ 0] , 15);
		RMD160FFF(ddd, eee, aaa, bbb, ccc, X[ 3] , 13);
		RMD160FFF(ccc, ddd, eee, aaa, bbb, X[ 9] , 11);
		RMD160FFF(bbb, ccc, ddd, eee, aaa, X[11] , 11);

		/* combine results */
		ddd += cc + m_context.state[1];               /* final result for m_context.state[0] */
		m_context.state[1] = m_context.state[2] + dd + eee;
		m_context.state[2] = m_context.state[3] + ee + aaa;
		m_context.state[3] = m_context.state[4] + aa + bbb;
		m_context.state[4] = m_context.state[0] + bb + ccc;
		m_context.state[0] = ddd;

		return 0;
	}

	int Init()
	{
		m_context.state[0] = 0x67452301UL;
		m_context.state[1] = 0xefcdab89UL;
		m_context.state[2] = 0x98badcfeUL;
		m_context.state[3] = 0x10325476UL;
		m_context.state[4] = 0xc3d2e1f0UL;
		m_context.curlen   = 0;
		m_context.length   = 0;
		return 0;
	}

	int Update(unsigned char * pData, unsigned long ulLen)
	{
		return CHashUpdate<CRMD160>::Update(pData, 
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
		for (i = 0; i < 5; i++) {
			STORE32L(m_context.state[i], pszOut+(4*i));
		}

		return 0;
	}
};
#endif