// texture.cpp: texture slot management

#include "engine.h"
#include "shared/entities/basephysicalentity.h"

#ifdef __APPLE__
  #include "SDL_image.h"
#else
    #include <SDL2/SDL_image.h>
#endif

struct DDCOLORKEY { uint dwColorSpaceLowValue, dwColorSpaceHighValue; };
struct DDPIXELFORMAT
{
    uint dwSize, dwFlags, dwFourCC;
    union { uint dwRGBBitCount, dwYUVBitCount, dwZBufferBitDepth, dwAlphaBitDepth, dwLuminanceBitCount, dwBumpBitCount, dwPrivateFormatBitCount; };
    union { uint dwRBitMask, dwYBitMask, dwStencilBitDepth, dwLuminanceBitMask, dwBumpDuBitMask, dwOperations; };
    union { uint dwGBitMask, dwUBitMask, dwZBitMask, dwBumpDvBitMask; struct { ushort wFlipMSTypes, wBltMSTypes; } MultiSampleCaps; };
    union { uint dwBBitMask, dwVBitMask, dwStencilBitMask, dwBumpLuminanceBitMask; };
    union { uint dwRGBAlphaBitMask, dwYUVAlphaBitMask, dwLuminanceAlphaBitMask, dwRGBZBitMask, dwYUVZBitMask; };

};
struct DDSCAPS2 { uint dwCaps, dwCaps2, dwCaps3, dwCaps4; };
struct DDSURFACEDESC2
{
    uint dwSize, dwFlags, dwHeight, dwWidth;
    union { int lPitch; uint dwLinearSize; };
    uint dwBackBufferCount;
    union { uint dwMipMapCount, dwRefreshRate, dwSrcVBHandle; };
    uint dwAlphaBitDepth, dwReserved, lpSurface;
    union { DDCOLORKEY ddckCKDestOverlay; uint dwEmptyFaceColor; };
    DDCOLORKEY ddckCKDestBlt, ddckCKSrcOverlay, ddckCKSrcBlt;
    union { DDPIXELFORMAT ddpfPixelFormat; uint dwFVF; };
    DDSCAPS2 ddsCaps;
    uint dwTextureStage;
};

DDPIXELFORMAT myFormatBiatch;

#define DECODEDDS(name, dbpp, initblock, writeval, nextval) \
static void name(ImageData &s) \
{ \
    ImageData d(s.w, s.h, dbpp); \
    uchar *dst = d.data; \
    const uchar *src = s.data; \
    for(int by = 0; by < s.h; by += s.align) \
    { \
        for(int bx = 0; bx < s.w; bx += s.align, src += s.bpp) \
        { \
            int maxy = min(d.h - by, s.align), maxx = min(d.w - bx, s.align); \
            initblock; \
            loop(y, maxy) \
            { \
                int x; \
                for(x = 0; x < maxx; ++x) \
                { \
                    writeval; \
                    nextval; \
                    dst += d.bpp; \
                }  \
                for(; x < s.align; ++x) { nextval; } \
                dst += d.pitch - maxx*d.bpp; \
            } \
            dst += maxx*d.bpp - maxy*d.pitch; \
        } \
        dst += (s.align-1)*d.pitch; \
    } \
    s.replace(d); \
}

DECODEDDS(decodedxt1, s.compressed == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT ? 4 : 3,
    ushort color0 = lilswap(*(const ushort *)src);
    ushort color1 = lilswap(*(const ushort *)&src[2]);
    uint bits = lilswap(*(const uint *)&src[4]);
    bvec4 rgba[4];
    rgba[0] = bvec4(bvec::from565(color0), 0xFF);
    rgba[1] = bvec4(bvec::from565(color1), 0xFF);
    if(color0 > color1)
    {
        rgba[2].lerp(rgba[0], rgba[1], 2, 1, 3);
        rgba[3].lerp(rgba[0], rgba[1], 1, 2, 3);
    }
    else
    {
        rgba[2].lerp(rgba[0], rgba[1], 1, 1, 2);
        rgba[3] = bvec4(0, 0, 0, 0);
    }
,
    memcpy(dst, rgba[bits&3].v, d.bpp);
,
    bits >>= 2;
);

DECODEDDS(decodedxt3, 4,
    ullong alpha = lilswap(*(const ullong *)src);
    ushort color0 = lilswap(*(const ushort *)&src[8]);
    ushort color1 = lilswap(*(const ushort *)&src[10]);
    uint bits = lilswap(*(const uint *)&src[12]);
    bvec rgb[4];
    rgb[0] = bvec::from565(color0);
    rgb[1] = bvec::from565(color1);
    rgb[2].lerp(rgb[0], rgb[1], 2, 1, 3);
    rgb[3].lerp(rgb[0], rgb[1], 1, 2, 3);
,
    memcpy(dst, rgb[bits&3].v, 3);
    dst[3] = ((alpha&0xF)*1088 + 32) >> 6;
,
    bits >>= 2;
    alpha >>= 4;
);
