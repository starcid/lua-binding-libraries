/**
*   \file HashCalc.h
*   \brief hash计算模板类实现，header only
*   \attention Copyright (C) 2007 LLYF Software
*   \author YangFan
*   \date 11/17/2007 12:22:40 AM
*/

#ifndef HASHCALC_H_
#define HASHCALC_H_

#include <Windows.h>

#include "HashMacro.h"
#include "md2.h"
#include "md4.h"
#include "md5.h"
#include "sha1.h"
#include "sha256.h"
#include "sha512.h"
#include "rmd128.h"
#include "rmd160.h"
#include "rmd256.h"
#include "rmd320.h"
#include "tiger.h"
#include "whirl.h"
#include "haval3.h"
#include "haval4.h"
#include "haval5.h"
#include "crc.h"
#include "sizehash.h"
#include "fcs.h"
#include "ghash.h"
#include "gost.h"
#include "adler32.h"

/**
*   \class CHash
*   \brief hash计算模板类，好处是可以共享相同逻辑的代码，如用内存映射文件提高大文件的计算效率等
*   \author YangFan
*   \date 11/17/2007 12:23:15 AM
*/
template<class CAlgorithm>
class CHash
{
private:
	CAlgorithm m_algo;
public:
	/**
	*   \brief 初始化常量等
	*   \return int 一般不用关心
	*   \author YangFan
	*   \date 11/17/2007 12:27:56 AM
	*/
	int Init()
	{
		return m_algo.Init();
	}

	/**
	*   \brief 更新需要计算的数据
	*   \param[in] unsigned char * pData 需要计算的数据
	*   \param[in] unsigned long ulLen 需要计算的数据长度
	*   \return  int 一般不用关心
	*   \author YangFan
	*   \date 11/17/2007 12:27:59 AM
	*/
	int Update(unsigned char * pData, unsigned long ulLen)
	{
		return m_algo.Update(pData, ulLen);
	}

	/**
	*   \brief 得到hash结果
	*   \param[out] unsigned char * pszOut
	*   \return  int 一般不用关心
	*   \author YangFan
	*   \date 11/17/2007 12:28:01 AM
	*/
	int Final(unsigned char * pszOut)
	{
		return m_algo.Final(pszOut);
	}

	/**
	*   \brief 获取消息摘要长度，以字节为单位
	*   \return int 消息摘要长度，以字节为单位
	*   \author YangFan
	*   \date 11/17/2007 12:28:04 AM
	*/
	int GetDigestLength() const
	{
		return CAlgorithm::nDigestLength;
	}

#if defined(_WIN32) || defined(WIN32)
	/**
	*   \brief 计算文件的hash值，使用Windows平台提供的内存映射文件提高大文件的读取效率
	*   \param[in] LPCTSTR pszFileName
	*   \param[out] unsigned char * pszOut
	*   \return 无
	*   \author YangFan
	*   \date 11/17/2007 12:28:06 AM
	*/
	void HashFile(const char * pszFileName, unsigned char * pszOut)
	{
		SYSTEM_INFO sinf;

		/**
		* 获取当前系统的内存分页大小
		*/
		::GetSystemInfo(&sinf);

		/**
		* 打开文件
		*/
		HANDLE hFile = ::CreateFileA(pszFileName,
			GENERIC_READ,
			FILE_SHARE_READ,
			NULL,
			OPEN_EXISTING,
			FILE_FLAG_SEQUENTIAL_SCAN,
			NULL);

		if( hFile == INVALID_HANDLE_VALUE)
			return;

		/**
		* 创建内存映射文件
		*/
		HANDLE hFileMapping = ::CreateFileMapping(hFile,
			NULL,
			PAGE_READONLY,
			0,
			0,
			NULL);
	  if( hFileMapping == INVALID_HANDLE_VALUE)
	  	{ 
	  		CloseHandle( hFile );
	  		return;
	  	}
		DWORD dwFileSizeHigh;

		/**
		* 获取文件大小
		*/
		__int64 qwFileSize = ::GetFileSize(hFile, &dwFileSizeHigh);
		qwFileSize += (((__int64) dwFileSizeHigh) <<32);

		::CloseHandle(hFile);
		m_algo.Init();

		__int64 qwFileOffset = 0;


		/**
		* 循环每次映射一页大小的数据，进行hash计算
		*/
		while(qwFileSize > 0)
		{
			DWORD dwBytesInBlock = sinf.dwAllocationGranularity;
			if(qwFileSize < sinf.dwAllocationGranularity)
				dwBytesInBlock = (DWORD)qwFileSize;
			PBYTE pbFile = (PBYTE)::MapViewOfFile(hFileMapping,
				FILE_MAP_READ,
				(DWORD)(qwFileOffset>>32),
				(DWORD)(qwFileOffset&0xffffffff),
				dwBytesInBlock);
			m_algo.Update(pbFile,dwBytesInBlock);
			
			::UnmapViewOfFile(pbFile);

			qwFileOffset += dwBytesInBlock;
			qwFileSize -= dwBytesInBlock;	
		}
		m_algo.Final(pszOut);
		::CloseHandle(hFileMapping);
		
	}
#endif
	/**
	*   \brief 计算字符串的hash结果
	*   \param[in] unsigned char* pszText 要被计算hash的字符串
	*   \param[in] unsigned long ulLen 要被计算的字符串长度
	*   \param[out] unsigned char * pszOut 计算后的hash结果
	*   \return 无
	*   \author YangFan
	*   \date 11/17/2007 12:28:10 AM
	*/
	void HashText(unsigned char* pszText, unsigned long ulLen, unsigned char * pszOut)
	{
		m_algo.Init();
		m_algo.Update(pszText, ulLen);
		m_algo.Final(pszOut);
	}
};


#endif