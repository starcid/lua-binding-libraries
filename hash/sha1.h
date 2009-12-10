#ifndef HASH_SHA1_H_
#define HASH_SHA1_H_

#define SHA1F0(x,y,z)  (z ^ (x & (y ^ z)))
#define SHA1F1(x,y,z)  (x ^ y ^ z)
#define SHA1F2(x,y,z)  ((x & y) | (z & (x | y)))
#define SHA1F3(x,y,z)  (x ^ y ^ z)

struct SHA1_CTX {
	ulong64 length;
	ulong32 state[5], curlen;
	unsigned char buf[64];
};

class CSHA1 : public CHashUpdate<CSHA1>
{
	SHA1_CTX m_context;
public:
	enum { nDigestLength =20 };

	int  Compress(unsigned char *buf)
	{
		ulong32 a,b,c,d,e,W[80],i;

		/* copy the state into 512-bits into W[0..15] */
		for (i = 0; i < 16; i++) 
		{
			LOAD32H(W[i], buf + (4*i));
		}

		/* copy state */
		a = m_context.state[0];
		b = m_context.state[1];
		c = m_context.state[2];
		d = m_context.state[3];
		e = m_context.state[4];

		/* expand it */
		for (i = 16; i < 80; i++) {
			W[i] = ROL(W[i-3] ^ W[i-8] ^ W[i-14] ^ W[i-16], 1); 
		}

		/* compress */
		/* round one */
#define SHA1FF0(a,b,c,d,e,i) e = (ROLc(a, 5) + SHA1F0(b,c,d) + e + W[i] + 0x5a827999UL); b = ROLc(b, 30);
#define SHA1FF1(a,b,c,d,e,i) e = (ROLc(a, 5) + SHA1F1(b,c,d) + e + W[i] + 0x6ed9eba1UL); b = ROLc(b, 30);
#define SHA1FF2(a,b,c,d,e,i) e = (ROLc(a, 5) + SHA1F2(b,c,d) + e + W[i] + 0x8f1bbcdcUL); b = ROLc(b, 30);
#define SHA1FF3(a,b,c,d,e,i) e = (ROLc(a, 5) + SHA1F3(b,c,d) + e + W[i] + 0xca62c1d6UL); b = ROLc(b, 30);

		for (i = 0; i < 20; ) {
			SHA1FF0(a,b,c,d,e,i++);
			SHA1FF0(e,a,b,c,d,i++);
			SHA1FF0(d,e,a,b,c,i++);
			SHA1FF0(c,d,e,a,b,i++);
			SHA1FF0(b,c,d,e,a,i++);
		}

		/* round two */
		for (; i < 40; )  { 
			SHA1FF1(a,b,c,d,e,i++);
			SHA1FF1(e,a,b,c,d,i++);
			SHA1FF1(d,e,a,b,c,i++);
			SHA1FF1(c,d,e,a,b,i++);
			SHA1FF1(b,c,d,e,a,i++);
		}

		/* round three */
		for (; i < 60; )  { 
			SHA1FF2(a,b,c,d,e,i++);
			SHA1FF2(e,a,b,c,d,i++);
			SHA1FF2(d,e,a,b,c,i++);
			SHA1FF2(c,d,e,a,b,i++);
			SHA1FF2(b,c,d,e,a,i++);
		}

		/* round four */
		for (; i < 80; )  { 
			SHA1FF3(a,b,c,d,e,i++);
			SHA1FF3(e,a,b,c,d,i++);
			SHA1FF3(d,e,a,b,c,i++);
			SHA1FF3(c,d,e,a,b,i++);
			SHA1FF3(b,c,d,e,a,i++);
		}


#undef SHA1FF0
#undef SHA1FF1
#undef SHA1FF2
#undef SHA1FF3

		/* store */
		m_context.state[0] = m_context.state[0] + a;
		m_context.state[1] = m_context.state[1] + b;
		m_context.state[2] = m_context.state[2] + c;
		m_context.state[3] = m_context.state[3] + d;
		m_context.state[4] = m_context.state[4] + e;

		return 0;
	}

	int Init()
	{
		m_context.state[0] = 0x67452301UL;
		m_context.state[1] = 0xefcdab89UL;
		m_context.state[2] = 0x98badcfeUL;
		m_context.state[3] = 0x10325476UL;
		m_context.state[4] = 0xc3d2e1f0UL;
		m_context.curlen = 0;
		m_context.length = 0;
		return 0;
	}

	int Update(unsigned char * pData, unsigned long ulLen)
	{
		return CHashUpdate<CSHA1>::Update(pData, 
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
		STORE64H(m_context.length, m_context.buf+56);
		Compress(m_context.buf);

		/* copy output */
		for (i = 0; i < 5; i++) 
		{
			STORE32H(m_context.state[i], pszOut+(4*i));
		}
		return 0;
	}
};
#endif