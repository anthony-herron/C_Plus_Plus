#ifndef __IMAGE_H__
#define __IMAGE_H__
// Image.h: interface for the CImage class.
//
//Eric Wright(11/16/07- Changed from BOOL to bool, BYTE to char, TRUE to true
//////////////////////////////////////////////////////////////////////


class CImage  
{
public:
	CImage();
	virtual ~CImage();
public:

	bool ReadBitmap(char *fname);
	void Cleanup(void);
	char *GetImage();
	int GetImageWidth();
	int GetImageHeight();
	char * m_lpImage;

private:
    int m_ImageWidth;
	int m_ImageHeight;

};

#endif
