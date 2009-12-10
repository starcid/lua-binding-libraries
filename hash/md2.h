#ifndef HASH_MD2_H_
#define HASH_MD2_H_

static const unsigned char PI_SUBST[256] = {
	41, 46, 67, 201, 162, 216, 124, 1, 61, 54, 84, 161, 236, 240, 6,
		19, 98, 167, 5, 243, 192, 199, 115, 140, 152, 147, 43, 217, 188,
		76, 130, 202, 30, 155, 87, 60, 253, 212, 224, 22, 103, 66, 111, 24,
		138, 23, 229, 18, 190, 78, 196, 214, 218, 158, 222, 73, 160, 251,
		245, 142, 187, 47, 238, 122, 169, 104, 121, 145, 21, 178, 7, 63,
		148, 194, 16, 137, 11, 34, 95, 33, 128, 127, 93, 154, 90, 144, 50,
		39, 53, 62, 204, 231, 191, 247, 151, 3, 255, 25, 48, 179, 72, 165,
		181, 209, 215, 94, 146, 42, 172, 86, 170, 198, 79, 184, 56, 210,
		150, 164, 125, 182, 118, 252, 107, 226, 156, 116, 4, 241, 69, 157,
		112, 89, 100, 113, 135, 32, 134, 91, 207, 101, 230, 45, 168, 2, 27,
		96, 37, 173, 174, 176, 185, 246, 28, 70, 97, 105, 52, 64, 126, 15,
		85, 71, 163, 35, 221, 81, 175, 58, 195, 92, 249, 206, 186, 197,
		234, 38, 44, 83, 13, 110, 133, 40, 132, 9, 211, 223, 205, 244, 65,
		129, 77, 82, 106, 220, 55, 200, 108, 193, 171, 250, 36, 225, 123,
		8, 12, 189, 177, 74, 120, 136, 149, 139, 227, 99, 232, 109, 233,
		203, 213, 254, 59, 0, 29, 57, 242, 239, 183, 14, 102, 88, 208, 228,
		166, 119, 114, 248, 235, 117, 75, 10, 49, 68, 80, 180, 143, 237,
		31, 26, 219, 153, 141, 51, 159, 17, 131, 20
};

struct MD2_CTX {
	unsigned char chksum[16], X[48], buf[16];
	unsigned long curlen;
};

class CMD2
{
	MD2_CTX m_context;

	void UpdateChecksum()
	{
		int j;
		unsigned char L;
		L = m_context.chksum[15];
		for (j = 0; j < 16; j++) 
		{

			/* caution, the RFC says its "C[j] = S[M[i*16+j] xor L]" but the reference source code [and test vectors] say 
			otherwise.
			*/
			L = (m_context.chksum[j] ^= PI_SUBST[(int)(m_context.buf[j] ^ L)] & 255);
		}
	}

	void Compress()
	{
		int j, k;
		unsigned char t;

		/* copy block */
		for (j = 0; j < 16; j++) 
		{
			m_context.X[16+j] = m_context.buf[j];
			m_context.X[32+j] = m_context.X[j] ^ m_context.X[16+j];
		}

		t = (unsigned char)0;

		/* do 18 rounds */
		for (j = 0; j < 18; j++) 
		{
			for (k = 0; k < 48; k++) 
			{
				t = (m_context.X[k] ^= PI_SUBST[(int)(t & 255)]);
			}
			t = (t + (unsigned char)j) & 255;
		}
	}

public:
	enum { nDigestLength =16 };

	int Init()
	{
		memset(&m_context, 0, sizeof(m_context));
		return 0;
	}

	int Update(unsigned char * pData, unsigned long ulLen)
	{
		unsigned long n;

		if (m_context.curlen > sizeof(m_context.buf)) 
		{                            
			return -1;                                                           
		}                                                                                       
		while (ulLen > 0) 
		{
            n = (ulLen < (16 - m_context.curlen) ? ulLen : (16 - m_context.curlen));
			memcpy(m_context.buf + m_context.curlen, pData, (size_t)n);
			m_context.curlen += n;
			pData += n;
			ulLen -= n;

			/* is 16 bytes full? */
			if (m_context.curlen == 16) 
			{
				Compress();
				UpdateChecksum();
				m_context.curlen = 0;
			}
		}

		return 0;
	}

	int Final(unsigned char * pszOut)
	{
		unsigned long i, k;

		if (m_context.curlen >= sizeof(m_context.buf)) {
			return -1;
		}


		/* pad the message */
		k = 16 - m_context.curlen;
		for (i = m_context.curlen; i < 16; i++) {
			m_context.buf[i] = (unsigned char)k;
		}

		/* hash and update */
		Compress();
		UpdateChecksum();

		/* hash checksum */
		memcpy(m_context.buf, m_context.chksum, 16);
		Compress();

		/* output is lower 16 bytes of X */
		memcpy(pszOut, m_context.X, 16);

		return 0;
	}
};

#endif