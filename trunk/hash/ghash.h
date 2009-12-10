#ifndef HASH_GHASH_H_
#define HASH_GHASH_H_

// nShiftBits == 3 or nShiftBits == 5
template<int nShiftBits>
class CGHash
{
	unsigned long m_context;
public:
	enum { nDigestLength = 4};
	int Init()
	{
		m_context = 0;
		return 0;
	}

	int Update(unsigned char *pData, unsigned long ulLen)
	{
		unsigned long i = 0;

		for(i = 0; i < ulLen; i++)
		{
			m_context = (m_context << nShiftBits) + m_context + pData[i];
		}
		return 0;
	}

	int Final(unsigned char *pszOut)
	{
		pszOut[0] = (unsigned char)((m_context & 0xFF000000 )>> 24);
		pszOut[1] = (unsigned char)((m_context & 0xFF0000 )>> 16);
		pszOut[2] = (unsigned char)((m_context & 0xFF00 )>> 8);
		pszOut[3] = (unsigned char)((m_context & 0xFF ));

		return 0;
	}
};

#endif