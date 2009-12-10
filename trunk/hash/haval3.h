#ifndef HASH_HAVAL3_H_
#define HASH_HAVAL3_H_

#define HAVAL_PASS 3
#define HAVAL_VERSION    1                   /* current version number */

static unsigned char haval_padding[128] = {        /* constants for haval_padding */
	0x01, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

#define haval_f_1(x6, x5, x4, x3, x2, x1, x0)          \
	((x1) & ((x0) ^ (x4)) ^ (x2) & (x5) ^ \
	(x3) & (x6) ^ (x0))

#define haval_f_2(x6, x5, x4, x3, x2, x1, x0)                         \
	((x2) & ((x1) & ~(x3) ^ (x4) & (x5) ^ (x6) ^ (x0)) ^ \
	(x4) & ((x1) ^ (x5)) ^ (x3) & (x5) ^ (x0)) 

#define haval_f_3(x6, x5, x4, x3, x2, x1, x0)          \
	((x3) & ((x1) & (x2) ^ (x6) ^ (x0)) ^ \
	(x1) & (x4) ^ (x2) & (x5) ^ (x0))

#define haval_f_4(x6, x5, x4, x3, x2, x1, x0)                                 \
	((x4) & ((x5) & ~(x2) ^ (x3) & ~(x6) ^ (x1) ^ (x6) ^ (x0)) ^ \
	(x3) & ((x1) & (x2) ^ (x5) ^ (x6)) ^                        \
	(x2) & (x6) ^ (x0))

#define haval_f_5(x6, x5, x4, x3, x2, x1, x0)             \
	((x0) & ((x1) & (x2) & (x3) ^ ~(x5)) ^   \
	(x1) & (x4) ^ (x2) & (x5) ^ (x3) & (x6))


#define haval_Fphi_1(x6, x5, x4, x3, x2, x1, x0) \
	haval_f_1(x1, x0, x3, x5, x6, x2, x4)

#define haval_Fphi_2(x6, x5, x4, x3, x2, x1, x0) \
	haval_f_2(x4, x2, x1, x0, x5, x3, x6)

#define haval_Fphi_3(x6, x5, x4, x3, x2, x1, x0) \
	haval_f_3(x6, x1, x2, x3, x4, x5, x0)


#define haval_rotate_right(x, n) (((x) >> (n)) | ((x) << (32-(n))))

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


/*
* translate every four characters into a word.
* assume the number of characters is a multiple of four.
*/
#define haval_ch2uint(string, word, slen) {      \
	unsigned char *sp = string;              \
	unsigned long    *wp = word;                \
	while (sp < (string) + (slen)) {         \
	*wp++ =  (unsigned long)*sp            |  \
	((unsigned long)*(sp+1) <<  8) |  \
	((unsigned long)*(sp+2) << 16) |  \
	((unsigned long)*(sp+3) << 24);   \
	sp += 4;                               \
	}                                        \
}

/* translate each word into four characters */
#define haval_uint2ch(word, string, wlen) {              \
	unsigned long    *wp = word;                        \
	unsigned char *sp = string;                      \
	while (wp < (word) + (wlen)) {                   \
	*(sp++) = (unsigned char)( *wp        & 0xFF); \
	*(sp++) = (unsigned char)((*wp >>  8) & 0xFF); \
	*(sp++) = (unsigned char)((*wp >> 16) & 0xFF); \
	*(sp++) = (unsigned char)((*wp >> 24) & 0xFF); \
	wp++;                                          \
	}                                                \
}

struct HAVAL_CTX{
	unsigned long count[2];                /* number of bits in a message */
	unsigned long fingerprint[8];          /* current state of fingerprint */    
	unsigned long block[32];               /* buffer for a 32-word block */ 
	unsigned char remainder[32*4];         /* unhashed chars (No.<128) */   
} ;

template<class CHaval>
class CHavalUpdateFinal
{
public:
	int Update(unsigned char * pData, unsigned int ulLen, HAVAL_CTX& m_context)
	{
		unsigned int i,	rmd_len,fill_len;
		CHaval *pHaval = static_cast<CHaval *>(this);

		/* calculate the number of bytes in the remainder */
		rmd_len  = (unsigned int)((m_context.count[0] >> 3) & 0x7F);
		fill_len = 128 - rmd_len;

		/* update the number of bits */
		if ((m_context.count[0] +=  (unsigned long)ulLen << 3) < ((unsigned long)ulLen << 3)) 
		{
			m_context.count[1]++;
		}
		m_context.count[1] += (unsigned long)ulLen >> 29;


		/* hash as many blocks as possible */
		if (rmd_len + ulLen >= 128) 
		{
			memcpy (((unsigned char *)m_context.block)+rmd_len, pData, fill_len);
			pHaval->haval_hash_block ();
			for (i = fill_len; i + 127 < ulLen; i += 128)
			{
				memcpy ((unsigned char *)m_context.block, pData+i, 128);
				pHaval->haval_hash_block ();
			}
			rmd_len = 0;
		} 
		else 
		{
			i = 0;
		}
		memcpy (((unsigned char *)m_context.block)+rmd_len, pData+i, ulLen-i);
		return 0;
	}

	int Final(unsigned char * pszOut, int nHavalPass, HAVAL_CTX& m_context, int HAVAL_FPTLEN)
	{
		unsigned char tail[10];
		unsigned int  rmd_len, pad_len;

		CHaval *pHaval = static_cast<CHaval *>(this);
		/*
		* save the version number, the number of passes, the fingerprint 
		* length and the number of bits in the unpadded message.
		*/
		tail[0] = (unsigned char)(((HAVAL_FPTLEN  & 0x3) << 6) |
			((nHavalPass  & 0x7) << 3) |
			(HAVAL_VERSION & 0x7));
		tail[1] = (unsigned char)((HAVAL_FPTLEN >> 2) & 0xFF);
		haval_uint2ch (m_context.count, &tail[2], 2);

		/* pad out to 118 mod 128 */
		rmd_len = (unsigned int)((m_context.count[0] >> 3) & 0x7f);
		pad_len = (rmd_len < 118) ? (118 - rmd_len) : (246 - rmd_len);
		Update ( haval_padding, pad_len, m_context);

		/*
		* append the version number, the number of passes,
		* the fingerprint length and the number of bits
		*/
		Update ( tail, 10, m_context);

		/* tailor the last output */
		pHaval->haval_tailor();

		/* translate and save the final fingerprint */
		haval_uint2ch (m_context.fingerprint, pszOut, HAVAL_FPTLEN >> 5);

		return 0;
	}
};

template<int HAVAL_FPTLEN>
class CHAVAL3 : public CHavalUpdateFinal<CHAVAL3<HAVAL_FPTLEN> >
{
protected:
	HAVAL_CTX m_context;

	void haval_pass123 (unsigned long& t0,
		unsigned long& t1,
		unsigned long& t2,
		unsigned long& t3,
		unsigned long& t4,
		unsigned long& t5,
		unsigned long& t6,
		unsigned long& t7)
	{
		t0 = m_context.fingerprint[0];
		t1 = m_context.fingerprint[1];
		t2 = m_context.fingerprint[2];
		t3 = m_context.fingerprint[3];
		t4 = m_context.fingerprint[4];
		t5 = m_context.fingerprint[5];
		t6 = m_context.fingerprint[6];
		t7 = m_context.fingerprint[7];
		unsigned long	*w = m_context.block;

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

public:
	enum { nDigestLength = HAVAL_FPTLEN/8 };

	int Init()
	{
		memset(&m_context, 0, sizeof(m_context));
		m_context.fingerprint[0] = 0x243F6A88L;           /* initial fingerprint */
		m_context.fingerprint[1] = 0x85A308D3L;
		m_context.fingerprint[2] = 0x13198A2EL;
		m_context.fingerprint[3] = 0x03707344L;
		m_context.fingerprint[4] = 0xA4093822L;
		m_context.fingerprint[5] = 0x299F31D0L;
		m_context.fingerprint[6] = 0x082EFA98L;
		m_context.fingerprint[7] = 0xEC4E6C89L;
		return 0;
	}

	void haval_hash_block()
	{
		unsigned long t0, t1, t2, t3,t4,t5,t6,t7;

		haval_pass123(t0,t1,t2,t3,t4,t5,t6,t7);
		m_context.fingerprint[0] += t0;
		m_context.fingerprint[1] += t1;
		m_context.fingerprint[2] += t2;
		m_context.fingerprint[3] += t3;
		m_context.fingerprint[4] += t4;
		m_context.fingerprint[5] += t5;
		m_context.fingerprint[6] += t6;
		m_context.fingerprint[7] += t7;
	}

	int Update(unsigned char * pData, unsigned long ulLen)
	{
		return CHavalUpdateFinal<CHAVAL3<HAVAL_FPTLEN> >::Update(pData, ulLen, m_context);
	}

	int Final(unsigned char * pszOut)
	{
		return CHavalUpdateFinal<CHAVAL3<HAVAL_FPTLEN> >::Final(pszOut, HAVAL_PASS, m_context, HAVAL_FPTLEN);
	}

	void haval_tailor ()
	{
		unsigned long temp;

		if( HAVAL_FPTLEN == 128)
		{
			temp = (m_context.fingerprint[7] & 0x000000FFL) | 
				(m_context.fingerprint[6] & 0xFF000000L) | 
				(m_context.fingerprint[5] & 0x00FF0000L) | 
				(m_context.fingerprint[4] & 0x0000FF00L);
			m_context.fingerprint[0] += haval_rotate_right(temp,  8);

			temp = (m_context.fingerprint[7] & 0x0000FF00L) | 
				(m_context.fingerprint[6] & 0x000000FFL) | 
				(m_context.fingerprint[5] & 0xFF000000L) | 
				(m_context.fingerprint[4] & 0x00FF0000L);
			m_context.fingerprint[1] += haval_rotate_right(temp, 16);

			temp  = (m_context.fingerprint[7] & 0x00FF0000L) | 
				(m_context.fingerprint[6] & 0x0000FF00L) | 
				(m_context.fingerprint[5] & 0x000000FFL) | 
				(m_context.fingerprint[4] & 0xFF000000L);
			m_context.fingerprint[2] += haval_rotate_right(temp, 24);

			temp = (m_context.fingerprint[7] & 0xFF000000L) | 
				(m_context.fingerprint[6] & 0x00FF0000L) | 
				(m_context.fingerprint[5] & 0x0000FF00L) | 
				(m_context.fingerprint[4] & 0x000000FFL);
			m_context.fingerprint[3] += temp;
		}
		else if(HAVAL_FPTLEN == 160)
		{

			temp = (m_context.fingerprint[7] &  (unsigned long)0x3F) | 
				(m_context.fingerprint[6] & ((unsigned long)0x7F << 25)) |  
				(m_context.fingerprint[5] & ((unsigned long)0x3F << 19));
			m_context.fingerprint[0] += haval_rotate_right(temp, 19);

			temp = (m_context.fingerprint[7] & ((unsigned long)0x3F <<  6)) | 
				(m_context.fingerprint[6] &  (unsigned long)0x3F) |  
				(m_context.fingerprint[5] & ((unsigned long)0x7F << 25));
			m_context.fingerprint[1] += haval_rotate_right(temp, 25);

			temp = (m_context.fingerprint[7] & ((unsigned long)0x7F << 12)) | 
				(m_context.fingerprint[6] & ((unsigned long)0x3F <<  6)) |  
				(m_context.fingerprint[5] &  (unsigned long)0x3F);
			m_context.fingerprint[2] += temp;

			temp = (m_context.fingerprint[7] & ((unsigned long)0x3F << 19)) | 
				(m_context.fingerprint[6] & ((unsigned long)0x7F << 12)) |  
				(m_context.fingerprint[5] & ((unsigned long)0x3F <<  6));
			m_context.fingerprint[3] += temp >> 6; 

			temp = (m_context.fingerprint[7] & ((unsigned long)0x7F << 25)) | 
				(m_context.fingerprint[6] & ((unsigned long)0x3F << 19)) |  
				(m_context.fingerprint[5] & ((unsigned long)0x7F << 12));
			m_context.fingerprint[4] += temp >> 12;
		}
		else if(HAVAL_FPTLEN == 192)
		{

			temp = (m_context.fingerprint[7] &  (unsigned long)0x1F) | 
				(m_context.fingerprint[6] & ((unsigned long)0x3F << 26));
			m_context.fingerprint[0] += haval_rotate_right(temp, 26);

			temp = (m_context.fingerprint[7] & ((unsigned long)0x1F <<  5)) | 
				(m_context.fingerprint[6] &  (unsigned long)0x1F);
			m_context.fingerprint[1] += temp;

			temp = (m_context.fingerprint[7] & ((unsigned long)0x3F << 10)) | 
				(m_context.fingerprint[6] & ((unsigned long)0x1F <<  5));
			m_context.fingerprint[2] += temp >> 5;

			temp = (m_context.fingerprint[7] & ((unsigned long)0x1F << 16)) | 
				(m_context.fingerprint[6] & ((unsigned long)0x3F << 10));
			m_context.fingerprint[3] += temp >> 10;

			temp = (m_context.fingerprint[7] & ((unsigned long)0x1F << 21)) | 
				(m_context.fingerprint[6] & ((unsigned long)0x1F << 16));
			m_context.fingerprint[4] += temp >> 16;

			temp = (m_context.fingerprint[7] & ((unsigned long)0x3F << 26)) | 
				(m_context.fingerprint[6] & ((unsigned long)0x1F << 21));
			m_context.fingerprint[5] += temp >> 21;
		}
		else if (HAVAL_FPTLEN == 224)
		{

			m_context.fingerprint[0] += (m_context.fingerprint[7] >> 27) & 0x1F;
			m_context.fingerprint[1] += (m_context.fingerprint[7] >> 22) & 0x1F;
			m_context.fingerprint[2] += (m_context.fingerprint[7] >> 18) & 0x0F;
			m_context.fingerprint[3] += (m_context.fingerprint[7] >> 13) & 0x1F;
			m_context.fingerprint[4] += (m_context.fingerprint[7] >>  9) & 0x0F;
			m_context.fingerprint[5] += (m_context.fingerprint[7] >>  4) & 0x1F;
			m_context.fingerprint[6] +=  m_context.fingerprint[7]        & 0x0F;
		}

	}
};

#undef haval_FF_1
#undef haval_FF_2
#undef haval_FF_3
#undef haval_Fphi_1
#undef haval_Fphi_2
#undef haval_Fphi_3
#undef HAVAL_PASS
#endif