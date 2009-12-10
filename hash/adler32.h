#ifndef HASH_ADLER32_H_
#define HASH_ADLER32_H_

class CAdler32
{
	unsigned short m_s1, m_s2;
public:
	enum { nDigestLength = 4};
	
	int Init()
	{
		m_s1 = 1; m_s2 = 0;
		return 0;
	}

	int Update(unsigned char * pData, unsigned long ulLen)
	{
		const unsigned long BASE = 65521;

		unsigned long s1 = m_s1;
		unsigned long s2 = m_s2;

		if (ulLen % 8 != 0)
		{
			do
			{
				s1 += *pData++;
				s2 += s1;
				ulLen--;
			} while (ulLen % 8 != 0);

			if (s1 >= BASE)
				s1 -= BASE;
			s2 %= BASE;
		}

		while (ulLen > 0)
		{
			s1 += pData[0]; s2 += s1;
			s1 += pData[1]; s2 += s1;
			s1 += pData[2]; s2 += s1;
			s1 += pData[3]; s2 += s1;
			s1 += pData[4]; s2 += s1;
			s1 += pData[5]; s2 += s1;
			s1 += pData[6]; s2 += s1;
			s1 += pData[7]; s2 += s1;

			ulLen -= 8;
			pData += 8;

			if (s1 >= BASE)
				s1 -= BASE;
			if (ulLen % 0x8000 == 0)
				s2 %= BASE;
		}

		//ASSERT(s1 < BASE);
		//ASSERT(s2 < BASE);

		m_s1 = (unsigned short)s1;
		m_s2 = (unsigned short)s2;
		return 0;
	}

	int Final(unsigned char * pszOut)
	{
		pszOut[0] = (unsigned char)(m_s2 >> 8);
		pszOut[1] = (unsigned char)(m_s2);
		pszOut[2] = (unsigned char)(m_s1 >> 8);
		pszOut[3] = (unsigned char)(m_s1);
		return 0;
	}

};
#endif