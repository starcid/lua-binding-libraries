#ifndef HASH_SIZE_H_
#define HASH_SIZE_H_

class CSizeHash
{
	unsigned long m_context;
public:
	enum { nDigestLength = 4};
	int Init()
	{
		m_context = 0;
		return 0;
	}

	int Update(unsigned char * /*pData*/, unsigned long ulLen)
	{
		m_context += ulLen;
		return 0;
	}

	int Final(unsigned char * pszOut)
	{
		pszOut[0] = (unsigned char)((m_context & 0xFF000000 )>> 24);
		pszOut[1] = (unsigned char)((m_context & 0xFF0000 )>> 16);
		pszOut[2] = (unsigned char)((m_context & 0xFF00 )>> 8);
		pszOut[3] = (unsigned char)((m_context & 0xFF ));
		return 0;
	}
};
#endif