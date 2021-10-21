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
typedef Image2DWriter<unsigned char> GrayLevelImage2DWriter;
typedef GrayLevelImage2D::Iterator GrayLevelIterator;

template<typename ColorAccessor>
int saveChannel(ColorImage2D& img, std::string ofile) {
    GrayLevelImage2D img2( img.w(), img.h() );

    auto channelIt = img.begin< ColorAccessor >();
    for ( GrayLevelIterator it = img2.begin(), itE = img2.end(); it != itE; ++it ) {
        *it = *channelIt;
        ++channelIt;
    }

    std::ofstream output( ofile );
    if( !GrayLevelImage2DWriter::write( img2, output, false ) ) {
        std::cerr << "Error writing output file." << std::endl;
        return 1;
    }
    output.close();
    return 0;
}

int main( int argc, char** argv )
{
    if ( argc < 2 ) 
    { 
        std::cerr << "Usage: save-channels <input.ppm>" << std::endl;
        return 0;
    }
    ColorImage2D img;
    std::ifstream input( argv[1] ); // récupère le 1er argument.
    bool ok = ColorImage2DReader::read( img, input );
    if ( !ok )
    {
        std::cerr << "Error reading input file." << std::endl;
        return 1;
    }
    input.close();
    std::string s = argv[1];

    auto offset = s.find(".ppm");
    s.erase(s.begin() + offset, s.end() );

    saveChannel<ColorRedAccessor>( img, s + "_red.ppm" );
    saveChannel<ColorGreenAccessor>( img, s + "_green.ppm" );
    saveChannel<ColorBlueAccessor>( img, s + "_blue.ppm" );

    return 0;
}

