#ifndef HASH_MD5_H_
#define HASH_MD5_H_

#define MD5F(x,y,z)  (z ^ (x & (y ^ z)))
#define MD5G(x,y,z)  (y ^ (z & (y ^ x)))
#define MD5H(x,y,z)  (x^y^z)
#define MD5I(x,y,z)  (y^(x|(~z)))


#define MD5FF(a,b,c,d,M,s,t) \
	a = (a + MD5F(b,c,d) + M + t); a = ROLc(a, s) + b;

#define MD5GG(a,b,c,d,M,s,t) \
	a = (a + MD5G(b,c,d) + M + t); a = ROLc(a, s) + b;

#define MD5HH(a,b,c,d,M,s,t) \
	a = (a + MD5H(b,c,d) + M + t); a = ROLc(a, s) + b;

#define MD5II(a,b,c,d,M,s,t) \
	a = (a + MD5I(b,c,d) + M + t); a = ROLc(a, s) + b;


struct MD5_CTX {
	ulong64 length;
	ulong32 state[4], curlen;
	unsigned char buf[64];
};

class CMD5 : public CHashUpdate<CMD5>
{
	MD5_CTX m_context;
public:
	enum { nDigestLength =16 };

	int  Compress(unsigned char *buf)
	{
		ulong32 i, W[16], a, b, c, d;

		/* copy the state into 512-bits into W[0..15] */
		for (i = 0; i < 16; i++) 
		{
			LOAD32L(W[i], buf + (4*i));
		}

		/* copy state */
		a = m_context.state[0];
		b = m_context.state[1];
		c = m_context.state[2];
		d = m_context.state[3];

		MD5FF(a,b,c,d,W[0],7,0xd76aa478UL)
		MD5FF(d,a,b,c,W[1],12,0xe8c7b756UL)
		MD5FF(c,d,a,b,W[2],17,0x242070dbUL)
		MD5FF(b,c,d,a,W[3],22,0xc1bdceeeUL)
		MD5FF(a,b,c,d,W[4],7,0xf57c0fafUL)
		MD5FF(d,a,b,c,W[5],12,0x4787c62aUL)
		MD5FF(c,d,a,b,W[6],17,0xa8304613UL)
		MD5FF(b,c,d,a,W[7],22,0xfd469501UL)
		MD5FF(a,b,c,d,W[8],7,0x698098d8UL)
		MD5FF(d,a,b,c,W[9],12,0x8b44f7afUL)
		MD5FF(c,d,a,b,W[10],17,0xffff5bb1UL)
		MD5FF(b,c,d,a,W[11],22,0x895cd7beUL)
		MD5FF(a,b,c,d,W[12],7,0x6b901122UL)
		MD5FF(d,a,b,c,W[13],12,0xfd987193UL)
		MD5FF(c,d,a,b,W[14],17,0xa679438eUL)
		MD5FF(b,c,d,a,W[15],22,0x49b40821UL)
		MD5GG(a,b,c,d,W[1],5,0xf61e2562UL)
		MD5GG(d,a,b,c,W[6],9,0xc040b340UL)
		MD5GG(c,d,a,b,W[11],14,0x265e5a51UL)
		MD5GG(b,c,d,a,W[0],20,0xe9b6c7aaUL)
		MD5GG(a,b,c,d,W[5],5,0xd62f105dUL)
		MD5GG(d,a,b,c,W[10],9,0x02441453UL)
		MD5GG(c,d,a,b,W[15],14,0xd8a1e681UL)
		MD5GG(b,c,d,a,W[4],20,0xe7d3fbc8UL)
		MD5GG(a,b,c,d,W[9],5,0x21e1cde6UL)
		MD5GG(d,a,b,c,W[14],9,0xc33707d6UL)
		MD5GG(c,d,a,b,W[3],14,0xf4d50d87UL)
		MD5GG(b,c,d,a,W[8],20,0x455a14edUL)
		MD5GG(a,b,c,d,W[13],5,0xa9e3e905UL)
		MD5GG(d,a,b,c,W[2],9,0xfcefa3f8UL)
		MD5GG(c,d,a,b,W[7],14,0x676f02d9UL)
		MD5GG(b,c,d,a,W[12],20,0x8d2a4c8aUL)
		MD5HH(a,b,c,d,W[5],4,0xfffa3942UL)
		MD5HH(d,a,b,c,W[8],11,0x8771f681UL)
		MD5HH(c,d,a,b,W[11],16,0x6d9d6122UL)
		MD5HH(b,c,d,a,W[14],23,0xfde5380cUL)
		MD5HH(a,b,c,d,W[1],4,0xa4beea44UL)
		MD5HH(d,a,b,c,W[4],11,0x4bdecfa9UL)
		MD5HH(c,d,a,b,W[7],16,0xf6bb4b60UL)
		MD5HH(b,c,d,a,W[10],23,0xbebfbc70UL)
		MD5HH(a,b,c,d,W[13],4,0x289b7ec6UL)
		MD5HH(d,a,b,c,W[0],11,0xeaa127faUL)
		MD5HH(c,d,a,b,W[3],16,0xd4ef3085UL)
		MD5HH(b,c,d,a,W[6],23,0x04881d05UL)
		MD5HH(a,b,c,d,W[9],4,0xd9d4d039UL)
		MD5HH(d,a,b,c,W[12],11,0xe6db99e5UL)
		MD5HH(c,d,a,b,W[15],16,0x1fa27cf8UL)
		MD5HH(b,c,d,a,W[2],23,0xc4ac5665UL)
		MD5II(a,b,c,d,W[0],6,0xf4292244UL)
		MD5II(d,a,b,c,W[7],10,0x432aff97UL)
		MD5II(c,d,a,b,W[14],15,0xab9423a7UL)
		MD5II(b,c,d,a,W[5],21,0xfc93a039UL)
		MD5II(a,b,c,d,W[12],6,0x655b59c3UL)
		MD5II(d,a,b,c,W[3],10,0x8f0ccc92UL)
		MD5II(c,d,a,b,W[10],15,0xffeff47dUL)
		MD5II(b,c,d,a,W[1],21,0x85845dd1UL)
		MD5II(a,b,c,d,W[8],6,0x6fa87e4fUL)
		MD5II(d,a,b,c,W[15],10,0xfe2ce6e0UL)
		MD5II(c,d,a,b,W[6],15,0xa3014314UL)
		MD5II(b,c,d,a,W[13],21,0x4e0811a1UL)
		MD5II(a,b,c,d,W[4],6,0xf7537e82UL)
		MD5II(d,a,b,c,W[11],10,0xbd3af235UL)
		MD5II(c,d,a,b,W[2],15,0x2ad7d2bbUL)
		MD5II(b,c,d,a,W[9],21,0xeb86d391UL)


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
		m_context.curlen = 0;
		m_context.length = 0;
		return 0;
	}

	int Update(unsigned char * pData, unsigned long ulLen)
	{
		return CHashUpdate<CMD5>::Update(pData, 
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