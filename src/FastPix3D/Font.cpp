#include "FastPix3D.h"
#include "lodepng.h"

Font::Font(string path) {

    std::vector<unsigned char> image; //the raw pixels
    unsigned width, height;

    //decode
    unsigned error = lodepng::decode(image, width, height, path);

    if (width % 16 > 0 || height % 16 > 0 || width > 4096)
        throw std::runtime_error("");

    Width = width >> 4;
    Height = height >> 4;
    CharacterSpacing = 2;
    Buffer = new byte[width * height];
    CharacterDimensions = new Point[256];

    byte* bitmapPtr = Buffer;
    for (int32 i = 0, *buffer = (int32*)image.data(); i < width * height; i++) {
        int32 r = (*buffer & 0xff0000) >> 16;
        int32 g = (*buffer & 0xff00) >> 8;
        int32 b = *buffer & 0xff;
        buffer++;
        *bitmapPtr++ = (byte)((r + g + b) / 3);
    }

    for (int32 i = 0; i < 256; i++) {
        CharacterDimensions[i] = Point(0, CharacterSpacing * 3);
        int32 characterX = (i & 15) * Width, characterY = (i >> 4) * Height;

        bool found = false;
        for (int32 x = 0; x < Width; x++) {
            for (int32 y = 0; y < Height; y++) {
                if ((int)Buffer[(x + characterX) + (y + characterY) * (Width << 4)] != -1) {
                    CharacterDimensions[i].X = x;
                    found = true;
                    break;
                }
            }
            if (found)
                break;
        }

        found = false;
        for (int32 x = Width - 1; x >= 0; x--) {
            for (int32 y = 0; y < Height; y++) {
                if ((int)Buffer[(x + characterX) + (y + characterY) * (Width << 4)] != -1) {
                    CharacterDimensions[i].Y = x + 1;
                    found = true;
                    break;
                }
            }
            if (found)
                break;
        }
    }
}
Font::~Font() {
    delete[] Buffer, CharacterDimensions;
}

int32 Font::getCharacterSpacing() {
    return CharacterSpacing;
}

void Font::setCharacterSpacing(int32 characterSpacing) {
    CharacterSpacing = characterSpacing;
}
