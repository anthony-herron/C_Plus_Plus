// Image.cpp: implementation of the CImage class.
//Eric Wright- 11/16/07 Changed from BOOL to bool, BYTE to char, TRUE to true

//#include "stdafx.h"
#include <stdio.h>

#include "Image.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CImage::CImage()
{

}

CImage::~CImage()
{

}

bool CImage::ReadBitmap(char *fname)
{
      FILE *fpIn;
	  fpIn=fopen(fname,"rb");
	  fread(&m_ImageWidth,1,sizeof(int),fpIn);
  	  fread(&m_ImageHeight,1,sizeof(int),fpIn);
	  long int  dwSizeImage;
      dwSizeImage=m_ImageWidth*m_ImageHeight*3;
	  m_lpImage =new char[dwSizeImage];
	  fread(m_lpImage,dwSizeImage,sizeof(char),fpIn);
	  fclose(fpIn);
	  return(true);
    
}

void CImage::Cleanup(void)
{
   delete m_lpImage;
}

int CImage::GetImageWidth()
{
   return m_ImageWidth;
}
int CImage::GetImageHeight()
{
    return m_ImageHeight;
}

char *CImage::GetImage()
{

     return m_lpImage;

}
