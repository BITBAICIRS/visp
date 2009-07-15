/****************************************************************************
 *
 * $Id$
 *
 * Copyright (C) 1998-2006 Inria. All rights reserved.
 *
 * This software was developed at:
 * IRISA/INRIA Rennes
 * Projet Lagadic
 * Campus Universitaire de Beaulieu
 * 35042 Rennes Cedex
 * http://www.irisa.fr/lagadic
 *
 * This file is part of the ViSP toolkit
 *
 * This file may be distributed under the terms of the Q Public License
 * as defined by Trolltech AS of Norway and appearing in the file
 * LICENSE included in the packaging of this file.
 *
 * Licensees holding valid ViSP Professional Edition licenses may
 * use this file in accordance with the ViSP Commercial License
 * Agreement provided with the Software.
 *
 * This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 * WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 * Contact visp@irisa.fr if any conditions of this licensing are
 * not clear to you.
 *
 * Description:
 * D3D renderer for windows 32 display
 *
 * Authors:
 * Bruno Renier
 *
 *****************************************************************************/

#ifndef DOXYGEN_SHOULD_SKIP_THIS

#include <visp/vpConfig.h>
#if ( defined(VISP_HAVE_D3D9) )

#ifndef VPD3DRENDERER_HH
#define VPD3DRENDERER_HH

#include <windows.h>
#include <d3dx9.h>
#include <visp/vpWin32Renderer.h>
#include <visp/vpDisplayException.h>


#include <iostream>

/*!
  \class vpD3DRenderer.h

  \brief Display under windows using Direct3D9.
  Is used by vpD3DDisplay to do the drawing.

*/
class VISP_EXPORT vpD3DRenderer : public vpWin32Renderer
{

  IDirect3D9 * pD3D;

  //The d3d device we will be working with.
  IDirect3DDevice9 * pd3dDevice;

  //Sprite used to render the texture.
  ID3DXSprite * pSprite;

  //The system memory texture :
  //The one we will be drawing on.
  IDirect3DTexture9 * pd3dText;

  //The video memory texture :
  //The one we will use for display.
  IDirect3DTexture9 * pd3dVideoText;

  //The texture's width.
  int textWidth;

  //The window's handle.
  HWND hWnd;

  //Colors  for overlay drawn with d3d directly.
  long colors[vpColor::none];

  //Colors for overlay drawn with GDI.
  COLORREF colorsGDI[vpColor::none];

  //Font used for text drawing.
  HFONT hFont;

 public:

  bool init(HWND hwnd, unsigned int width, unsigned int height);
  bool render();

  vpD3DRenderer();
  virtual ~vpD3DRenderer();

  void setImg(const vpImage<vpRGBa>& im);

  void setImg(const vpImage<unsigned char>& im);

  void setPixel(const vpImagePoint iP, vpColor color);

  void drawLine(const vpImagePoint &ip1, 
		const vpImagePoint &ip2,
		vpColor color, unsigned int thickness, int style=PS_SOLID);

  void drawRect(const vpImagePoint &topLeft,
		unsigned int width, unsigned int height,
		vpColor color, bool fill=false,
		unsigned int thickness=1);

  void clear(vpColor color);

  void drawCircle(const vpImagePoint &center, unsigned int radius,
		  vpColor color, bool fill=false, unsigned char thickness=1);

  void drawText(const vpImagePoint &ip, const char * text,
		vpColor color);

  void drawCross(const vpImagePoint &ip, unsigned int size,
		 vpColor color, unsigned int thickness=1);

  void drawArrow(const vpImagePoint &ip1, 
		 const vpImagePoint &ip2,
		 vpColor color, unsigned int w,unsigned int h, unsigned int thickness=1);

  void getImage(vpImage<vpRGBa> &I);



 private:

  void initView(float, float);

  /*!
    Sub function for circle drawing.
    Circle drawing is based on Bresenham 's circle algorithm.
  */
  void subDrawCircle(int i, int j,
		     int x, int y,
		     vpColor col, unsigned char* buf,
		     unsigned int pitch, unsigned int maxX, unsigned int maxY);


  /*!
    Safe useful inline function to set a pixel in a texture buffer.
    \param buf The texture's buffer.
    \param pitch The image pitch.
    \param x The x-coordinate of the pixel (in the locked rectangle base)
    \param y The y-coordinate of the pixel (in the locked rectangle base)
    \param color The color of the pixel.
    \param maxX The maximum x value (equals to the width of the locked rectangle).
    \param maxY The maximum y value (equals to the height of the locked rectangle).

  */
  inline void setBufferPixel(unsigned char* buf, unsigned int pitch,
			     int x, int y,
			     vpColor color,
			     unsigned int maxX, unsigned int maxY)
    {
      if(x>=0 && y>=0 && x<= (int)maxX && y<= (int)maxY)
	*(long*)(buf + (y*pitch) + (x<<2)) = colors[color];
    }
  /*!
    Unsafe useful inline function to set a pixel in a texture buffer.
    \param buf The texture's buffer.
    \param pitch The image pitch.
    \param x The x-coordinate of the pixel (in the locked rectangle base)
    \param y The y-coordinate of the pixel (in the locked rectangle base)
    \param color The color of the pixel.

  */
  inline void setBufferPixel(unsigned char* buf, unsigned int pitch,
                             int x, int y,
                             vpColor color)
  {
      *(long*)(buf + (y*pitch) + (x<<2)) = colors[color];
  }

  int supPowerOf2(int n);

};
#endif
#endif
#endif
