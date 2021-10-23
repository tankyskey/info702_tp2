#pragma once
#include <iostream>
#include <fstream>
#include "image2D.hpp"
#include "image2DReader.hpp"
#include "image2DWriter.hpp"
#include "accessor.hpp"

typedef Image2D<unsigned char> GrayLevelImage2D;
typedef GrayLevelImage2D::Iterator GrayLevelIterator;

class Histogramme {
    double histo[256] = {0},
           histoCumul[256] = {0};

    public:
        template <typename InputIterator>
        void init( InputIterator it, InputIterator itE ) {
            for( ; it != itE; it++ ) {
                int h;
                float s, v;
                it->getHSV(h, s, v);
                histo[h]++;

                for( int i=h; i<256; i++)
                    histoCumul[i]++;
            }
        }

        GrayLevelImage2D exportImg() {
            GrayLevelImage2D img(256, 256);
            for(int x=0; x<256; x++) {
                for(int y=256; y>256-histo[x]; y--) {
                    img.at(x, y) = 255;
                }
            }
            std::cout<<"hi"<<std::endl;
            return img;
        }
};
