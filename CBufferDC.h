#pragma once
#include <afxwin.h>

class CBufferDC :public CDC
{
    DECLARE_DYNAMIC(CBufferDC)  // CObject::IsKindOf() Allowed
private:
    CBufferDC(){}
    CBufferDC(const CBufferDC& src){}
    CBufferDC& operator= (const CBufferDC &rsc){}
protected:
    BOOL Attach(HDC hdc);
    HDC Detach();
private:
    CWnd*       m_pParent;  // 
    CDC*        m_pTarget ;
    PAINTSTRUCT m_PaintStruct;
    CRect       m_RcClient, m_RcWindow;

    CDC         m_MemoryDC;
    CBitmap     m_MemoryBmp, *m_pOldMemoryBmp;

public:
    CBufferDC(CWnd* pParent);
    ~CBufferDC();

public:
    inline CRect ClientRect() const { return m_RcClient; }
    inline CRect WindowRect() const { return m_RcWindow; }
    inline CRect UpdateRect() const { return m_PaintStruct.rcPaint; }

    operator HDC() const { return m_MemoryDC.m_hDC; }       //  DC handle for API functions

};

