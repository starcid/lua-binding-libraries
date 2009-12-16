/**
*   \file XercesCWrapper.h
*   \brief 对Xerces C的封装，以便适配STL算法
*   \author YangFan
*   \date 2009-11-23 19:56:43
*/

#ifndef XercesCWrapper_H_
#define XercesCWrapper_H_

#include <algorithm>
#include <cstdio>
#include <string>
#include <sstream>
#include <stdexcept>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/framework/LocalFileFormatTarget.hpp>
#include <xercesc/framework/MemBufInputSource.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/util/XMLUni.hpp>
#include <xercesc/util/OutOfMemoryException.hpp>

using namespace std;
XERCES_CPP_NAMESPACE_USE

typedef basic_string<TCHAR> tstring;

/**
*   \class CXmlDocumentWrapper
*   \brief XML DOM文档类封装
*   \author YangFan
*   \date 2009-11-23 19:57:19
*/
class CXmlDocumentWrapper
{
private:
    DOMImplementation *m_impl;
    XercesDOMParser *m_parser;
    XERCES_CPP_NAMESPACE::DOMDocument* m_doc;
public:
    CXmlDocumentWrapper()
        :m_impl(DOMImplementationRegistry::getDOMImplementation(L"Core"))
        ,m_parser(new XercesDOMParser)
        ,m_doc(NULL)
    {
        //配置DOMParser
        m_parser->setValidationScheme(XercesDOMParser::Val_Auto);
        m_parser->setDoNamespaces(false);
        m_parser->setDoSchema(false);
        m_parser->setLoadExternalDTD(false); 
    }

    XERCES_CPP_NAMESPACE::DOMDocument* Interface()
    {
        return m_doc;
    }

    ~CXmlDocumentWrapper()
    {
        delete m_parser;
        m_parser = NULL;
    }

    bool Load(const wchar_t * pwszFile)
    {
        m_parser->parse(pwszFile);
        m_doc = m_parser->getDocument();
        return (m_doc != NULL);
    }

    bool Load(const char * pszFile)
    {
        return Load(XMLString::transcode(pszFile));
    }

    DOMElement* AsNode()
    {
        if (m_doc)
        {
            return m_doc->getDocumentElement();
        }

        return NULL;
    }

    bool Save(const TCHAR* pszFile, bool bPrettyPrint = true)
    {
        bool bRet = false;
        if (m_doc && pszFile)
        {
            DOMLSOutput *theOutputDesc = ((DOMImplementationLS*)m_impl)->createLSOutput();
            DOMLSSerializer *theSerializer = ((DOMImplementationLS*)m_impl)->createLSSerializer();
            XMLFormatTarget *myFormTarget = new LocalFileFormatTarget(pszFile);
            theOutputDesc->setEncoding(L"UTF-8");
            theOutputDesc->setByteStream(myFormTarget);
            DOMConfiguration* theConfig = theSerializer->getDomConfig();
            theConfig->setParameter(L"format-pretty-print", bPrettyPrint);
            XMLCh* lfSeq = XMLString::transcode("\r\n");
            theSerializer->setNewLine(lfSeq);
            XMLString::release(&lfSeq); 
            bRet = theSerializer->write(m_doc, theOutputDesc);
            theOutputDesc->release();
            theSerializer->release();
            delete myFormTarget;
        }
        
        return bRet;
    }

    void LoadXML(const char * pszXML)
    {
        MemBufInputSource* memBufIS = new MemBufInputSource((const XMLByte*)pszXML, strlen(pszXML), "prodInfo", false);
        m_parser->parse(*memBufIS);
        m_doc = m_parser->getDocument();
    }

    void LoadXML(const wchar_t* pwszXML)
    {
        LoadXML(XMLString::transcode(pwszXML));
    }
};


/**
*   \class CXmlNodeWrapper
*   \brief XML DOM节点类封装
*   \author YangFan
*   \date 2009-11-23 19:57:33
*/
class CXmlNodeWrapper
{
private:
    DOMNode* m_pNode;

    void UUIDFromString( tstring &val, UUID& uuid )
    {
        basic_istringstream<TCHAR> is;
        unsigned long ulData = 0;

        is.str(val.substr(0, 8));
        is >> hex >> uuid.Data1;

        is.clear();
        is.str(val.substr(9, 4));

        is >> hex >> ulData;
        uuid.Data2 = static_cast<unsigned long>(ulData & 0xFFFF);

        is.clear();
        is.str(val.substr(14, 4));
        is >> hex >> ulData;
        uuid.Data3 = static_cast<unsigned short>(ulData & 0xFFFF);

        is.clear();
        is.str(val.substr(19, 4));
        is >> hex >> ulData;
        uuid.Data4[0] = (unsigned char)(ulData >> 8) & 0xFF;
        uuid.Data4[1] = (unsigned char)ulData & 0xFF;

        is.clear();
        is.str(val.substr(24, 4));
        is >> hex >> ulData;
        uuid.Data4[2] = (unsigned char)(ulData >> 8) & 0xFF;
        uuid.Data4[3] = (unsigned char)ulData & 0xFF;

        is.clear();
        is.str(val.substr(28, 4));
        is >> hex >> ulData;
        uuid.Data4[4] = (unsigned char)(ulData >> 24) & 0xFF;
        uuid.Data4[5] = (unsigned char)(ulData >> 16) & 0xFF;
        uuid.Data4[6] = (unsigned char)(ulData >> 8) & 0xFF;
        uuid.Data4[7] = (unsigned char)ulData & 0xFF;
    }
public:
    CXmlNodeWrapper()
        :m_pNode(NULL)
    {

    }
    CXmlNodeWrapper(DOMNode* node)
        :m_pNode(node)
    {

    }

    ~CXmlNodeWrapper()
    {

    }

    void operator=(DOMNode* pNode)
    {
        m_pNode = pNode;
    }
    bool operator==(DOMNode* pNode)
    {
        return m_pNode == pNode;
    }
    bool operator!=(DOMNode* pNode)
    {
        return m_pNode != pNode;
    }

    DOMNode::NodeType GetNodeType()
    {
        if (m_pNode)
        {
            return m_pNode->getNodeType();
        }

        return  DOMNode::ELEMENT_NODE;
    }
    
    tstring GetAttribVal(int index)
    {
        if (m_pNode)
        {
            DOMNamedNodeMap * nm = m_pNode->getAttributes();
            if (nm)
            {
#ifdef _UNICODE
                return nm->item(index)->getNodeValue();
#else
                return XMLString::transcode(nm->item(index)->getNodeValue());
#endif
            }
        }

        return tstring();
    }

    tstring GetAttribName(int index)
    {
        if (m_pNode)
        {
            DOMNamedNodeMap * nm = m_pNode->getAttributes();
            if (nm)
            {
#ifdef _UNICODE
                return nm->item(index)->getNodeName();
#else
                return XMLString::transcode(nm->item(index)->getNodeName());
#endif
            }
        }

        return tstring();
    }

    bool ExistAttribute(const TCHAR* AttribName)
    {
        if (m_pNode)
        {
            DOMElement* pElement = dynamic_cast<DOMElement*>(m_pNode);
            if (pElement)
            {
                return pElement->hasAttribute(
#ifdef _UNICODE
                    AttribName
#else
                    XMLString::transcode(AttribName)
#endif
                    );
            }
        }
        return false;
    }

    int NumAttributes()
    {
        if (m_pNode)
        {
            DOMNamedNodeMap * nm = m_pNode->getAttributes();
            if (nm)
            {
                return (int)nm->getLength();
            }
        }

        return 0;
    }
    
    tstring Name()
    {
#ifdef _UNICODE
        return m_pNode->getNodeName();
#else
        return XMLString::transcode(m_pNode->getNodeName());
#endif
    }

    DOMNode* Parent()
    {
        if (m_pNode)
        {
            return m_pNode->getParentNode();
        }

        return NULL;
    }

    DOMNodeList* ChildNodes()
    {
        if (m_pNode)
        {
            return m_pNode->getChildNodes();
        }

        return NULL;
    }

    void RemoveNodes(const wchar_t* searchStr)
    {
        if (m_pNode)
        {
            DOMNodeList* pChildren = m_pNode->getChildNodes();
            XMLSize_t nCount = pChildren->getLength();
            for (XMLSize_t nIndex = 0; nIndex < nCount; nIndex++)
            {
                DOMNode* pChild = pChildren->item(nIndex);
                if (pChild && wcscmp(searchStr, pChild->getNodeName()) == 0)
                {
                    m_pNode->removeChild(pChild);
                }
            }
        }
    }

    DOMNode* Interface()
    {
        return m_pNode;
    }
    
    void ReplaceNode(DOMNode* pOldNode,DOMNode* pNewNode)
    {
        if (m_pNode)
        {
            m_pNode->replaceChild(pNewNode, pOldNode);
        }
    }
    
    DOMNode* InsertBefore(DOMNode* refNode, DOMNode* pNode)
    {
        if (m_pNode)
        {
            return m_pNode->insertBefore(pNode, refNode);
        }

        return NULL;
    }

    DOMNode* InsertAfter(DOMNode* refNode, const TCHAR* nodeName)
    {
        if (m_pNode)
        {
            XERCES_CPP_NAMESPACE::DOMDocument* pDoc = m_pNode->getOwnerDocument();
            DOMElement* newNode= pDoc->createElement(
#ifdef _UNICODE
                nodeName
#else
                XMLString::transcode(nodeName)
#endif
                );
            DOMNode* refNext = refNode->getNextSibling();
            if (refNext)
            {
                return m_pNode->insertBefore(newNode, refNext);
            }
            else
            {
                return m_pNode->appendChild(newNode);
            }
        }

        return NULL;
    }

    DOMNode* InsertBefore(DOMNode* refNode, const TCHAR* nodeName)
    {
        if (m_pNode)
        {
            XERCES_CPP_NAMESPACE::DOMDocument* pDoc = m_pNode->getOwnerDocument();
            DOMElement* newNode= pDoc->createElement(
#ifdef _UNICODE
                nodeName
#else
                XMLString::transcode(nodeName)
#endif
            );
            return m_pNode->insertBefore(newNode, refNode);
        }

        return NULL;
    }

    DOMNode* InsertNode(int index,const TCHAR* nodeName)
    {
        if (m_pNode)
        {
            XERCES_CPP_NAMESPACE::DOMDocument* pDoc = m_pNode->getOwnerDocument();
            DOMElement* newNode= pDoc->createElement(
#ifdef _UNICODE
                nodeName
#else
                XMLString::transcode(nodeName)
#endif
            );
            return InsertNode(index, newNode);
        }

        return NULL;
    }

    DOMNode* InsertNode(int index,DOMNode* pNode)
    {
        if (m_pNode)
        {
            DOMNodeList* pChildren = m_pNode->getChildNodes();
            if ((XMLSize_t)index >= pChildren->getLength())
            {
                index = pChildren->getLength()-1;
            }
            DOMNode* refNode = pChildren->item(index);
            return m_pNode->insertBefore(pNode, refNode);
        }

        return NULL;
    }

    DOMNode* AppendNode(const TCHAR* nodeName)
    {
        if (m_pNode)
        {
            XERCES_CPP_NAMESPACE::DOMDocument* pDoc = m_pNode->getOwnerDocument();
            DOMElement* newNode= pDoc->createElement(
#ifdef _UNICODE
                nodeName
#else
                XMLString::transcode(nodeName)
#endif
            );
            return AppendNode(newNode);
        }
        return NULL;
    }

    DOMNode* AppendNode(DOMNode* pNode)
    {
        if (m_pNode)
        {
            return m_pNode->appendChild(pNode);
        }

        return NULL;
    }

    XERCES_CPP_NAMESPACE::DOMDocument* Document()
    {
        if (m_pNode)
        {
            return m_pNode->getOwnerDocument();
        }

        return NULL;
    }

    DOMNode* RemoveNode(DOMNode* pNode)
    {
        if (m_pNode)
        {
            return m_pNode->removeChild(pNode);
        }

        return NULL;
    }

    long NumNodes()
    {
        if (m_pNode)
        {
            DOMNodeList* pNodeList = m_pNode->getChildNodes();
            if (pNodeList)
            {
                return pNodeList->getLength();
            }
        }

        return 0;
    }

    DOMNode* FindNode(const TCHAR* searchString)
    {
        if (m_pNode)
        {
            DOMNodeList* pChildren = m_pNode->getChildNodes();
            XMLSize_t nCount = pChildren->getLength();
            for (XMLSize_t nIndex = 0; nIndex < nCount; nIndex++)
            {
                DOMNode* pChild = pChildren->item(nIndex);
                if (pChild && wcscmp(
#ifdef _UNICODE
                    searchString, 
#else
                    XMLString::transcode(searchString),
#endif
                    pChild->getNodeName()) == 0)
                {
                    return pChild;
                }
            }
        }

        return NULL;
    }

    DOMNodeList* FindNodes(const TCHAR* searchString)
    {
        if (m_pNode)
        {
            DOMElement* pElement = dynamic_cast<DOMElement*>(m_pNode);
            if (pElement)
            {
                return pElement->getElementsByTagName(
#ifdef _UNICODE
                    searchString
#else
                    XMLString::transcode(searchString)
#endif
                    );
            }
        }
        return NULL;
    }

    DOMNode* GetPrevSibling()
    {
        if (m_pNode)
        {
            return m_pNode->getPreviousSibling();
        }

        return NULL;
    }

    DOMNode* GetNextSibling()
    {
        if (m_pNode)
        {
            return m_pNode->getNextSibling();
        }

        return NULL;
    }

    void SetValue(const TCHAR* valueName, const TCHAR* value)
    {
        if (m_pNode)
        {
            DOMElement* pElement = dynamic_cast<DOMElement*>(m_pNode);
            if (pElement)
            {
                pElement->setAttribute(
#ifdef _UNICODE
                    valueName, value
#else
                    XMLString::transcode(valueName),XMLString::transcode(value)
#endif
                    );
            }
        }
    }
    void SetValue(const TCHAR* valueName, int value)
    {
        TCHAR val[100] = {0};
#if _MSC_VER >=1400
        _stprintf_s(
            val,
            _countof(val),
            _T("%d"),
            value);
#else
        _stprintf(
            val,
            _T("%d"),
            value);
#endif
        SetValue(valueName, val);
    }
    void SetValue(const TCHAR* valueName, short value)
    {
        TCHAR val[100] = {0};
#if _MSC_VER >=1400
        _stprintf_s(
            val,
            _countof(val),
            _T("%d"),
            value);
#else
        _stprintf(
            val,
            _T("%d"),
            value);
#endif
        SetValue(valueName, val);
    }
    void SetValue(const TCHAR* valueName, double value)
    {
        TCHAR val[100] = {0};
#if _MSC_VER >=1400
        _stprintf_s(
            val,
            _countof(val),
            _T("%f"),
            value);
#else
        _stprintf(
            val,
            _T("%f"),
            value);
#endif
        SetValue(valueName, val);
    }

    void SetValue(const TCHAR* valueName, float value)
    {
        TCHAR val[100] = {0};
#if _MSC_VER >=1400
        _stprintf_s(
            val,
            _countof(val),
            _T("%f"),
            value);
#else
        _stprintf(
            val,
            _T("%f"),
            value);
#endif
        SetValue(valueName, val);
    }
    void SetValue(const TCHAR* valueName, bool value)
    {
        SetValue(valueName, value ? _T("true") : _T("false"));
    }

    void SetValue(const TCHAR* valueName, UUID& value)
    {
        TCHAR val[100] = {0};
#if _MSC_VER >=1400
        _stprintf_s(val,
            sizeof(val)/sizeof(val[0]),
            _T("%8.8X-%4.4X-%4.4X-%2.2X%2.2X%-2.2X%2.2X%2.2X%2.2X%2.2X%2.2X"),
            value.Data1, value.Data2, value.Data3, 
            value.Data4[0], value.Data4[1], value.Data4[2], 
            value.Data4[3], value.Data4[4], value.Data4[5], 
            value.Data4[6], value.Data4[7] );
#else
        _stprintf(val,
            _T("%8.8X-%4.4X-%4.4X-%2.2X%2.2X%-2.2X%2.2X%2.2X%2.2X%2.2X%2.2X"),
            (unsigned int)value.Data1, value.Data2, value.Data3, 
            value.Data4[0], value.Data4[1], value.Data4[2], 
            value.Data4[3], value.Data4[4], value.Data4[5], 
            value.Data4[6], value.Data4[7] );
#endif
        SetValue(valueName,val);
    }

    void SetText(const TCHAR* text)
    {
        if (m_pNode)
        {
            m_pNode->setTextContent(
#ifdef _UNICODE
                text
#else
                XMLString::transcode(text)
#endif
                );
        }
    }
    void SetText(int text)
    {
        TCHAR val[100] = {0};
#if _MSC_VER >=1400
        _stprintf_s(
            val,
            sizeof(val)/sizeof(val[0]),
#else
        _stprintf(
            val,
#endif
            _T("%ds"),
            text);
        SetText(val);
    }
    void SetText(short text)
    {
        TCHAR val[100] = {0};
#if _MSC_VER >=1400
        _stprintf_s(
            val,
            sizeof(val)/sizeof(val[0]),
#else
        _stprintf(
            val,
#endif
            _T("%d"),
            text);
        SetText(val);
    }
    void SetText(double text)
    {
        TCHAR val[100] = {0};
#if _MSC_VER >=1400
        _stprintf_s(
            val,
            sizeof(val)/sizeof(val[0]),
#else
        _stprintf(
            val,
#endif
            _T("%f"),
            text);
        SetText(val);
    }
    void SetText(float text)
    {
        TCHAR val[100] = {0};
#if _MSC_VER >=1400
        _stprintf_s(
            val,
            sizeof(val)/sizeof(val[0]),
#else
        _stprintf(
            val,
#endif
            _T("%f"),
            text);
        SetText(val);
    }
    void SetText(bool text)
    {
        SetText(text ? _T("true") : _T("false"));
    }
    void SetText(UUID& text)
    {
        TCHAR val[100] = {0};
#if _MSC_VER >=1400
        _stprintf_s(
            val,
            sizeof(val)/sizeof(val[0]),
#else
        _stprintf(
            val,
#endif
            _T("%8.8X-%4.4X-%4.4X-%2.2X%2.2X%-2.2X%2.2X%2.2X%2.2X%2.2X%2.2X"),
            (unsigned int)text.Data1, text.Data2, text.Data3, 
            text.Data4[0], text.Data4[1], text.Data4[2], 
            text.Data4[3], text.Data4[4], text.Data4[5], 
            text.Data4[6], text.Data4[7] );
        SetText(val);
    }

    tstring GetValue(const TCHAR* valueName)
    {
        if (m_pNode)
        {
            DOMElement* pEle = dynamic_cast<DOMElement*>(m_pNode);
            if (pEle)
            {
#ifdef _UNICODE
                return pEle->getAttribute(valueName);
#else
                return XMLString::transcode(pEle->getAttribute(XMLString::transcode(valueName)));
#endif
            }
        }

        return _T("");
    }
    int GetIntValue(const TCHAR* valueName)
    {
        tstring val = GetValue(valueName);
        if (!val.empty())
        {
            return _ttoi(val.c_str());
        }

        return 0xFFFFFFFF;
    }
    DWORD GetHexValue(const TCHAR* valueName)
    {
        unsigned int dwRet = 0xFFFFFFFF;
        tstring val = GetValue(valueName);
        if (!val.empty())
        {
            transform(val.begin(), val.end(), val.begin(), ::tolower);
            _stscanf(val.c_str(),_T("0x%x"), &dwRet);
        }

        return dwRet;
    }

    COLORREF GetColorValue(const TCHAR* valueName)
    {
        COLORREF crRet = RGB(0,0,0);
        DWORD dwColor = GetHexValue(valueName);
        crRet = RGB((dwColor & 0xFF0000)>> 16, (dwColor & 0x00FF00) >> 8, dwColor & 0xff);
        return crRet;
    }

    UUID GetUUIDValue(const TCHAR* valueName)
    {
        UUID uuid = {0};
        tstring val = GetValue(valueName);
        if (!val.empty())
        {
            UUIDFromString(val, uuid);
        }

        return uuid;
    }

    tstring GetText()
    {
        tstring text;
        if (m_pNode)
        {
#ifdef _UNICODE
            text = m_pNode->getTextContent();
#else
            text = XMLString::transcode(m_pNode->getTextContent());
#endif
        }

        return text;
    }

    int GetIntText()
    {
        int nRet = 0xFFFFFFFF;
        if (m_pNode)
        {
#ifdef _UNICODE
            tstring text = m_pNode->getTextContent();
#else
            tstring text = XMLString::transcode(m_pNode->getTextContent());
#endif
            if (!text.empty())
            {
                nRet = _ttoi(text.c_str());
            }
        }

        return nRet;
    }

    DWORD GetHexText()
    {
        unsigned int dwRet = 0xFFFFFFFF;
        if (m_pNode)
        {
#ifdef _UNICODE
            tstring text = m_pNode->getTextContent();
#else
            tstring text = XMLString::transcode(m_pNode->getTextContent());
#endif
            if (!text.empty())
            {
                transform(text.begin(), text.end(), text.begin(), ::tolower);
                _stscanf(text.c_str(),_T("0x%x"), &dwRet);
            }
        }

        return dwRet;
    }

    COLORREF GetColorText()
    {
        COLORREF crRet = RGB(0,0,0);
        if (m_pNode)
        {
#ifdef _UNICODE
            tstring text = m_pNode->getTextContent();
#else
            tstring text = XMLString::transcode(m_pNode->getTextContent());
#endif
            if (!text.empty())
            {
                transform(text.begin(), text.end(), text.begin(), ::tolower);
                unsigned int dwRet = 0;
                _stscanf(text.c_str(),_T("0x%x"), &dwRet);

                crRet = RGB((dwRet & 0xFF0000)>> 16, (dwRet & 0x00FF00) >> 8, dwRet & 0xff);
            }
        }

        return crRet;
    }

    UUID GetUUIDText()
    {
        UUID uuid = {0};
        if (m_pNode)
        {
#ifdef _UNICODE
            tstring text = m_pNode->getTextContent();
#else
            tstring text = XMLString::transcode(m_pNode->getTextContent());
#endif
            UUIDFromString(text, uuid);
        }

        return uuid;
    }

    bool IsValid()
    {
        return (m_pNode != NULL);
    }
};

class CXmlNodelistWrapper;

/**
*   \class CXmlNodeIterator
*   \brief 在节点集合中支持STL算法的迭代器类型
*   \author YangFan
*   \date 2009-11-23 19:58:04
*/
class CXmlNodeIterator
    : public std::iterator<std::random_access_iterator_tag, CXmlNodeWrapper>
{
private:
    size_t m_nIndex;
    DOMNodeList* m_pNodelist;
    CXmlNodeWrapper m_refNode;
public:
    explicit CXmlNodeIterator(int nIndex, DOMNodeList* pNodelist)
        :m_nIndex(nIndex), m_pNodelist(pNodelist)
    {
        if (!pNodelist || (pNodelist && m_nIndex >= pNodelist->getLength()) || m_nIndex == 0xFFFFFFFF)
        {
            m_nIndex = 0xFFFFFFFF;
        }
    }

    ~CXmlNodeIterator()
    {

    }

    size_t Index() const { return m_nIndex; }
    void Index(size_t val) { m_nIndex = val; }


    CXmlNodeIterator& operator++() // prefix
    {
        size_t nIndex = ++m_nIndex;
        if (nIndex == 0 || nIndex >= (size_t)m_pNodelist->getLength())
        {
            m_nIndex = 0xFFFFFFFF;
        }
        return *this;
    }

    CXmlNodeIterator operator++(int) // postfix
    {
        CXmlNodeIterator old = *this;
        size_t nIndex = ++m_nIndex;
        if (nIndex == 0 || nIndex >= (size_t)m_pNodelist->getLength())
        {
            m_nIndex = 0xFFFFFFFF;
        }
        return old;
    }

    CXmlNodeIterator& operator--() // prefix
    {
        size_t nIndex = m_nIndex--;
        if (nIndex == 0xFFFFFFFF || m_nIndex == 0xFFFFFFFF )
        {
            m_nIndex = 0xFFFFFFFF;
        }
        return *this;
    }

    CXmlNodeIterator operator--(int) // postfix
    {
        CXmlNodeIterator old = *this;
        size_t nIndex = m_nIndex--;
        if (nIndex == 0xFFFFFFFF ||m_nIndex == 0xFFFFFFFF )
        {
            m_nIndex = 0xFFFFFFFF;
        }
        return old;
    }

    CXmlNodeIterator& operator+=(int n)
    {
        if(m_nIndex == 0xFFFFFFFF)
        {
            return *this;
        }

        m_nIndex += n;
        if (++m_nIndex >= m_pNodelist->getLength())
        {
            m_nIndex = 0xFFFFFFFF;
        }

        return *this;
    }

    CXmlNodeIterator& operator-=(int n)
    {
        if (m_nIndex < (size_t)n)
        {
            m_nIndex = 0xFFFFFFFF;
            return *this;
        }

        m_nIndex -= n;

        if (--m_nIndex < 0)
        {
            m_nIndex = 0xFFFFFFFF;
        }

        return *this;
    }

    CXmlNodeIterator operator+(CXmlNodeIterator& iter)
    {
        return CXmlNodeIterator(iter.Index() + m_nIndex, m_pNodelist);
    } 

    CXmlNodeIterator operator-(CXmlNodeIterator& iter)
    {
        return CXmlNodeIterator(iter.Index() - m_nIndex, m_pNodelist);
    } 

    bool operator>(CXmlNodeIterator& iter)
    {
        return m_nIndex > iter.Index();
    }

    bool operator>=(CXmlNodeIterator& iter)
    {
        return m_nIndex >= iter.Index();
    }

    bool operator<(CXmlNodeIterator& iter)
    {
        return m_nIndex < iter.Index();
    }

    bool operator<=(CXmlNodeIterator& iter)
    {
        return m_nIndex <= iter.Index();
    }

    bool operator==(CXmlNodeIterator& iter)
    {
        return m_nIndex == iter.Index();
    }

    bool operator!=(CXmlNodeIterator& iter)
    {
        return m_nIndex != iter.Index();
    }

    reference operator*()
    {
        m_refNode = m_pNodelist->item(m_nIndex);
        return m_refNode;
    }

    pointer operator->()
    {
        m_refNode = m_pNodelist->item(m_nIndex);
        return &m_refNode;
    }
};


/**
*   \class CXmlNodelistWrapper
*   \brief XML DOM节点集合类封装
*   \author YangFan
*   \date 2009-11-23 19:58:38
*/
class CXmlNodelistWrapper
{
private:
    DOMNodeList* m_pNodelist;
    CXmlNodeWrapper m_refNode;
public:
    typedef DOMNode* value_type;
    typedef CXmlNodeIterator iterator;
    typedef const CXmlNodeIterator const_iterator;
    typedef CXmlNodeWrapper& reference;
    typedef const CXmlNodeWrapper const_reference;
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;

    CXmlNodelistWrapper(DOMNodeList* pNodelist)
        :m_pNodelist(pNodelist)
    {

    }

    CXmlNodelistWrapper()
        :m_pNodelist(NULL)
    {

    }

    virtual ~CXmlNodelistWrapper()
    {

    }

    XERCES_CPP_NAMESPACE::DOMDocument* AsDocument()
    {
        if (m_pNodelist)
        {
            
        }
        return NULL;
    }

    DOMNode* Node(int nIndex)
    {
        if (m_pNodelist)
        {
            return m_pNodelist->item(nIndex);
        }

        return NULL;
    }

    bool IsValid()
    {
        return (m_pNodelist != NULL);
    }

    int Count()
    {
        if (m_pNodelist)
        {
            return (int)m_pNodelist->getLength();
        }

        return 0;
    }

    iterator begin()
    {
        iterator iter(0, m_pNodelist);
        return iter;
    }

    const_iterator begin() const
    {
        const_iterator iter(0, m_pNodelist);
        return iter;
    }

    iterator end()
    {
        iterator iter(0xFFFFFFFF, m_pNodelist);
        return iter;
    }

    reference operator[](size_type index)
    {
        m_refNode = IsValid() ? m_pNodelist->item(index) : NULL;
        return (reference)m_refNode;
    }

    const_reference operator[](size_type index) const
    {
        CXmlNodeIterator refNode(index, m_pNodelist);
        return *refNode;
    }

    reference at(size_type index)
    {
        if (!m_pNodelist || (XMLSize_t)index >= m_pNodelist->getLength())
        {
            std::string err_msg = "out of XMLDOMNodelist range";

            throw std::out_of_range(err_msg);
        }
        m_refNode = IsValid() ? m_pNodelist->item(index) : NULL;
        return m_refNode;
    }

    reference front()
    {
        m_refNode = IsValid() ? m_pNodelist->item(0) : NULL;
        return (reference)m_refNode;
    }

    const_reference front() const
    {
        CXmlNodeIterator refNode(0, m_pNodelist);
        return *refNode;
    }

    reference back()
    {
        m_refNode = IsValid() ? m_pNodelist->item(m_pNodelist->getLength() -1) : NULL;
        return (reference)m_refNode;        
    }

    const_reference back() const
    {
        CXmlNodeIterator refNode(m_pNodelist->getLength() -1, m_pNodelist);
        return *refNode;
    }

    size_type size()
    {
        return (size_type)(IsValid() ? m_pNodelist->getLength() : 0);
    }

    bool empty()
    {
        return IsValid() ? (m_pNodelist->getLength() == 0) : true;
    }

    void operator=(DOMNodeList* pNode)
    {
        m_pNodelist = pNode;
    }
};


class CXercesCInitializer
{
public:
    CXercesCInitializer()
    {
        try
        {
            XMLPlatformUtils::Initialize();
        }
        catch(const XMLException &toCatch)
        {
            toCatch.getMessage();
        }
    }

    ~CXercesCInitializer()
    {
        XMLPlatformUtils::Terminate();
    }
};

#endif
