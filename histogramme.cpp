#include <cmath>
#include <iostream>
#include <fstream>
#include "image2D.hpp"
#include "image2DReader.hpp"
#include "image2DWriter.hpp"
#include "accessor.hpp"
#include "histogramme.hpp"

typedef Image2D<Color> ColorImage2D;
typedef Image2DReader<Color> ColorImage2DReader;
typedef ColorImage2D::Iterator ColorIterator;
typedef Image2D<unsigned char> GrayLevelImage2D;
typedef GrayLevelImage2D::Iterator GrayLevelIterator;

typedef ColorImage2D::GenericIterator< ColorRedAccessor >   ColorRedConstIterator;
typedef ColorImage2D::GenericIterator< ColorGreenAccessor > ColorGreenConstIterator;
typedef ColorImage2D::GenericIterator< ColorBlueAccessor >  ColorBlueConstIterator;


int main( int argc, char** argv )
{
    Histogramme H;
    ColorImage2D img;
    std::ifstream input( argv[1] );
    if ( !ColorImage2DReader::read( img, input ) ) {
        std::cerr << "Error reading input file." << std::endl;
        return 1;
    }
    input.close();

    H.init( img.begin(), img.end() );
    GrayLevelImage2D img2 = H.exportImg();

    std::ofstream output( argv[2] );
    if( !Image2DWriter<unsigned char>::write( img2, output, false ) ) {
        std::cerr << "Error writing output file." << std::endl;
        return 1;
    }
    output.close();
    return 0;
}
