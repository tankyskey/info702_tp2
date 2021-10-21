#include <iostream>
#include <fstream>
#include "image2D.hpp"
#include "color.hpp"
#include "image2DReader.hpp"
#include "image2DWriter.hpp"

template<typename T>
void swap(T* a, T* b) {
    T tmp = *a; *a = *b; *b = tmp;
}

int main( int argc, char** argv )
{
    if( argc < 2 ) {
        std::cerr<< "invert-red-blue <input> <output>" << std::endl;
        return 0;
    }
    Image2D<Color> img;
    std::ifstream input( argv[1] );
    Image2DReader<Color>::read(img, input);
    input.close();

    for(auto it=img.begin(); it != img.end(); it++) {
        swap<unsigned char>(&it->green, &it->blue);
    }

    std::ofstream output( argv[2] );
    Image2DWriter<Color>::write(img, output, false);
  //static bool write( Image & img, std::ostream & output, bool ascii )

    return 0;
}
