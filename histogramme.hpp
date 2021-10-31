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
            int nbPixels = itE - it;
            double max = 0, coef;

            for(; it != itE; it++)
                max = ++histo[(int)*it] > max ? histo[(int)*it] : max ;
            coef = 256 * nbPixels / max;

            for(int i=0; i<256; i++) {

                for(int j=0; j<i; j++)
                    histoCumul[i] += histo[j];

                histo[i] *= coef / (double)nbPixels;
                histoCumul[i] *= max /(double)nbPixels;

            }
        }

        GrayLevelImage2D exportImg() {
            GrayLevelImage2D img(512, 256, 255);

            for(int x=0; x<256; x++) {
                for(int y=256-histo[x]; y<256; y++) {
                    img.at(x, y) = 0;
                }

                for(int y=256-histoCumul[x]; y<256; y++) {
                    img.at(x+256, y) = 0;
                }
            }
            return img;
        }
};
