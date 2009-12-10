#ifndef HASH_SHA256_H_
#define HASH_SHA256_H_

#define SHA256Ch(x,y,z)       (z ^ (x & (y ^ z)))
#define SHA256Maj(x,y,z)      (((x | y) & z) | (x & y)) 
#define SHA256S(x, n)         RORc((x),(n))
#define SHA256R(x, n)         (((x)&0xFFFFFFFFUL)>>(n))
#define SHA256Sigma0(x)       (SHA256S(x, 2) ^ SHA256S(x, 13) ^ SHA256S(x, 22))
#define SHA256Sigma1(x)       (SHA256S(x, 6) ^ SHA256S(x, 11) ^ SHA256S(x, 25))
#define SHA256Gamma0(x)       (SHA256S(x, 7) ^ SHA256S(x, 18) ^ SHA256R(x, 3))
#define SHA256Gamma1(x)       (SHA256S(x, 17) ^ SHA256S(x, 19) ^ SHA256R(x, 10))

struct SHA256_CTX {
	ulong64 length;
	ulong32 state[8], curlen;
	unsigned char buf[64];
};

class CSHA256 : public CHashUpdate<CSHA256>
{
protected:
	SHA256_CTX m_context;
public:
	enum { nDigestLength =32 };

	int  Compress(unsigned char *buf)
	{
		ulong32 S[8], W[64], t0, t1;
		int i;

		/* copy state into S */
		for (i = 0; i < 8; i++) {
			S[i] = m_context.state[i];
		}

		/* copy the state into 512-bits into W[0..15] */
		for (i = 0; i < 16; i++) {
			LOAD32H(W[i], buf + (4*i));
		}

		/* fill W[16..63] */
		for (i = 16; i < 64; i++) {
			W[i] = SHA256Gamma1(W[i - 2]) + W[i - 7] + SHA256Gamma0(W[i - 15]) + W[i - 16];
		}        

		/* Compress */

#define SHA256RND(a,b,c,d,e,f,g,h,i,ki)                    \
	t0 = h + SHA256Sigma1(e) + SHA256Ch(e, f, g) + ki + W[i];   \
	t1 = SHA256Sigma0(a) + SHA256Maj(a, b, c);                  \
	d += t0;                                        \
	h  = t0 + t1;

		SHA256RND(S[0],S[1],S[2],S[3],S[4],S[5],S[6],S[7],0,0x428a2f98);
		SHA256RND(S[7],S[0],S[1],S[2],S[3],S[4],S[5],S[6],1,0x71374491);
		SHA256RND(S[6],S[7],S[0],S[1],S[2],S[3],S[4],S[5],2,0xb5c0fbcf);
		SHA256RND(S[5],S[6],S[7],S[0],S[1],S[2],S[3],S[4],3,0xe9b5dba5);
		SHA256RND(S[4],S[5],S[6],S[7],S[0],S[1],S[2],S[3],4,0x3956c25b);
		SHA256RND(S[3],S[4],S[5],S[6],S[7],S[0],S[1],S[2],5,0x59f111f1);
		SHA256RND(S[2],S[3],S[4],S[5],S[6],S[7],S[0],S[1],6,0x923f82a4);
		SHA256RND(S[1],S[2],S[3],S[4],S[5],S[6],S[7],S[0],7,0xab1c5ed5);
		SHA256RND(S[0],S[1],S[2],S[3],S[4],S[5],S[6],S[7],8,0xd807aa98);
		SHA256RND(S[7],S[0],S[1],S[2],S[3],S[4],S[5],S[6],9,0x12835b01);
		SHA256RND(S[6],S[7],S[0],S[1],S[2],S[3],S[4],S[5],10,0x243185be);
		SHA256RND(S[5],S[6],S[7],S[0],S[1],S[2],S[3],S[4],11,0x550c7dc3);
		SHA256RND(S[4],S[5],S[6],S[7],S[0],S[1],S[2],S[3],12,0x72be5d74);
		SHA256RND(S[3],S[4],S[5],S[6],S[7],S[0],S[1],S[2],13,0x80deb1fe);
		SHA256RND(S[2],S[3],S[4],S[5],S[6],S[7],S[0],S[1],14,0x9bdc06a7);
		SHA256RND(S[1],S[2],S[3],S[4],S[5],S[6],S[7],S[0],15,0xc19bf174);
		SHA256RND(S[0],S[1],S[2],S[3],S[4],S[5],S[6],S[7],16,0xe49b69c1);
		SHA256RND(S[7],S[0],S[1],S[2],S[3],S[4],S[5],S[6],17,0xefbe4786);
		SHA256RND(S[6],S[7],S[0],S[1],S[2],S[3],S[4],S[5],18,0x0fc19dc6);
		SHA256RND(S[5],S[6],S[7],S[0],S[1],S[2],S[3],S[4],19,0x240ca1cc);
		SHA256RND(S[4],S[5],S[6],S[7],S[0],S[1],S[2],S[3],20,0x2de92c6f);
		SHA256RND(S[3],S[4],S[5],S[6],S[7],S[0],S[1],S[2],21,0x4a7484aa);
		SHA256RND(S[2],S[3],S[4],S[5],S[6],S[7],S[0],S[1],22,0x5cb0a9dc);
		SHA256RND(S[1],S[2],S[3],S[4],S[5],S[6],S[7],S[0],23,0x76f988da);
		SHA256RND(S[0],S[1],S[2],S[3],S[4],S[5],S[6],S[7],24,0x983e5152);
		SHA256RND(S[7],S[0],S[1],S[2],S[3],S[4],S[5],S[6],25,0xa831c66d);
		SHA256RND(S[6],S[7],S[0],S[1],S[2],S[3],S[4],S[5],26,0xb00327c8);
		SHA256RND(S[5],S[6],S[7],S[0],S[1],S[2],S[3],S[4],27,0xbf597fc7);
		SHA256RND(S[4],S[5],S[6],S[7],S[0],S[1],S[2],S[3],28,0xc6e00bf3);
		SHA256RND(S[3],S[4],S[5],S[6],S[7],S[0],S[1],S[2],29,0xd5a79147);
		SHA256RND(S[2],S[3],S[4],S[5],S[6],S[7],S[0],S[1],30,0x06ca6351);
		SHA256RND(S[1],S[2],S[3],S[4],S[5],S[6],S[7],S[0],31,0x14292967);
		SHA256RND(S[0],S[1],S[2],S[3],S[4],S[5],S[6],S[7],32,0x27b70a85);
		SHA256RND(S[7],S[0],S[1],S[2],S[3],S[4],S[5],S[6],33,0x2e1b2138);
		SHA256RND(S[6],S[7],S[0],S[1],S[2],S[3],S[4],S[5],34,0x4d2c6dfc);
		SHA256RND(S[5],S[6],S[7],S[0],S[1],S[2],S[3],S[4],35,0x53380d13);
		SHA256RND(S[4],S[5],S[6],S[7],S[0],S[1],S[2],S[3],36,0x650a7354);
		SHA256RND(S[3],S[4],S[5],S[6],S[7],S[0],S[1],S[2],37,0x766a0abb);
		SHA256RND(S[2],S[3],S[4],S[5],S[6],S[7],S[0],S[1],38,0x81c2c92e);
		SHA256RND(S[1],S[2],S[3],S[4],S[5],S[6],S[7],S[0],39,0x92722c85);
		SHA256RND(S[0],S[1],S[2],S[3],S[4],S[5],S[6],S[7],40,0xa2bfe8a1);
		SHA256RND(S[7],S[0],S[1],S[2],S[3],S[4],S[5],S[6],41,0xa81a664b);
		SHA256RND(S[6],S[7],S[0],S[1],S[2],S[3],S[4],S[5],42,0xc24b8b70);
		SHA256RND(S[5],S[6],S[7],S[0],S[1],S[2],S[3],S[4],43,0xc76c51a3);
		SHA256RND(S[4],S[5],S[6],S[7],S[0],S[1],S[2],S[3],44,0xd192e819);
		SHA256RND(S[3],S[4],S[5],S[6],S[7],S[0],S[1],S[2],45,0xd6990624);
		SHA256RND(S[2],S[3],S[4],S[5],S[6],S[7],S[0],S[1],46,0xf40e3585);
		SHA256RND(S[1],S[2],S[3],S[4],S[5],S[6],S[7],S[0],47,0x106aa070);
		SHA256RND(S[0],S[1],S[2],S[3],S[4],S[5],S[6],S[7],48,0x19a4c116);
		SHA256RND(S[7],S[0],S[1],S[2],S[3],S[4],S[5],S[6],49,0x1e376c08);
		SHA256RND(S[6],S[7],S[0],S[1],S[2],S[3],S[4],S[5],50,0x2748774c);
		SHA256RND(S[5],S[6],S[7],S[0],S[1],S[2],S[3],S[4],51,0x34b0bcb5);
		SHA256RND(S[4],S[5],S[6],S[7],S[0],S[1],S[2],S[3],52,0x391c0cb3);
		SHA256RND(S[3],S[4],S[5],S[6],S[7],S[0],S[1],S[2],53,0x4ed8aa4a);
		SHA256RND(S[2],S[3],S[4],S[5],S[6],S[7],S[0],S[1],54,0x5b9cca4f);
		SHA256RND(S[1],S[2],S[3],S[4],S[5],S[6],S[7],S[0],55,0x682e6ff3);
		SHA256RND(S[0],S[1],S[2],S[3],S[4],S[5],S[6],S[7],56,0x748f82ee);
		SHA256RND(S[7],S[0],S[1],S[2],S[3],S[4],S[5],S[6],57,0x78a5636f);
		SHA256RND(S[6],S[7],S[0],S[1],S[2],S[3],S[4],S[5],58,0x84c87814);
		SHA256RND(S[5],S[6],S[7],S[0],S[1],S[2],S[3],S[4],59,0x8cc70208);
		SHA256RND(S[4],S[5],S[6],S[7],S[0],S[1],S[2],S[3],60,0x90befffa);
		SHA256RND(S[3],S[4],S[5],S[6],S[7],S[0],S[1],S[2],61,0xa4506ceb);
		SHA256RND(S[2],S[3],S[4],S[5],S[6],S[7],S[0],S[1],62,0xbef9a3f7);
		SHA256RND(S[1],S[2],S[3],S[4],S[5],S[6],S[7],S[0],63,0xc67178f2);

#undef SHA256RND     


		/* feedback */
		for (i = 0; i < 8; i++) 
		{
			m_context.state[i] = m_context.state[i] + S[i];
		}
		return 0;
	}

	int Init()
	{
		m_context.curlen = 0;
		m_context.length = 0;
		m_context.state[0] = 0x6A09E667UL;
		m_context.state[1] = 0xBB67AE85UL;
		m_context.state[2] = 0x3C6EF372UL;
		m_context.state[3] = 0xA54FF53AUL;
		m_context.state[4] = 0x510E527FUL;
		m_context.state[5] = 0x9B05688CUL;
		m_context.state[6] = 0x1F83D9ABUL;
		m_context.state[7] = 0x5BE0CD19UL;
		return 0;
	}

	int Update(unsigned char * pData, unsigned long ulLen)
	{
		return CHashUpdate<CSHA256>::Update(pData, 
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
		for (i = 0; i < 8; i++) 
		{
			STORE32H(m_context.state[i], pszOut+(4*i));
		}

		return 0;
	}
};

class CSHA224 : public CSHA256
{
public:
	enum { nDigestLength =28 };

	int Init()
	{
		m_context.curlen = 0;
		m_context.length = 0;
		m_context.state[0] = 0xc1059ed8UL;
		m_context.state[1] = 0x367cd507UL;
		m_context.state[2] = 0x3070dd17UL;
		m_context.state[3] = 0xf70e5939UL;
		m_context.state[4] = 0xffc00b31UL;
		m_context.state[5] = 0x68581511UL;
		m_context.state[6] = 0x64f98fa7UL;
		m_context.state[7] = 0xbefa4fa4UL;
		return 0;
	}

	int Final(unsigned char *pszOut)
	{
		unsigned char buf[32];
		int err = CSHA256::Final(buf);
		memcpy(pszOut, buf, 28);

		return err;
	}
};

#endif