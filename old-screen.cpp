#include <cmath>
#include <iostream>
#include <fstream>
#include "image2D.hpp"
#include "image2DReader.hpp"
#include "image2DWriter.hpp"
#include "accessor.hpp"

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
    if ( argc < 2 ) { 
        std::cerr << "Usage: old-screen <input.ppm> <output.ppm>" << std::endl;
        return 0;
    }

    ColorImage2D img;
    std::ifstream input( argv[1] );
    if ( !ColorImage2DReader::read( img, input ) ) {
        std::cerr << "Error reading input file." << std::endl;
        return 1;
    }
    input.close();

    ColorRedConstIterator   itRed   = img.begin< ColorRedAccessor >();
    ColorGreenConstIterator itGreen = img.begin< ColorGreenAccessor >();
    ColorBlueConstIterator  itBlue  = img.begin< ColorBlueAccessor >();

    // On écrit la composante verte dans l'image en niveaux de gris.
    int x = 0;
    for ( ColorIterator it = img.begin(), itE = img.end();
            it != itE; ++it )
    {
        switch ( x % 3 ) {
            case 0: *itGreen = *itBlue  = 0; break;
            case 1: *itRed   = *itBlue  = 0; break;
            case 2: *itRed   = *itGreen = 0; break;
        }
        ++itRed; ++itGreen; ++itBlue;
        x = ( x+1 ) % img.w();
    }

    std::ofstream output( argv[2] );
    if( !Image2DWriter<Color>::write( img, output, false ) ) {
        std::cerr << "Error writing output file." << std::endl;
        return 1;
    }
    output.close();

    return 0;
}
