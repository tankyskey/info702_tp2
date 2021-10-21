#ifndef _IMAGE2DWRITER_HPP_
#define _IMAGE2DWRITER_HPP_
 
#include <iostream>
#include <string>
#include "image2D.hpp"
#include "color.hpp"
 
template <typename TValue>
class Image2DWriter {
public:
  typedef TValue Value;
  typedef Image2D<Value> Image;
 
  static bool write( Image & img, std::ostream & output, bool ascii )
  {
    std::cerr << "[Image2DWriter<TValue>::write] NOT IMPLEMENTED." << std::endl;
    return false;
  }
};
 
/// Specialization for gray-level images.
template <>
class Image2DWriter<unsigned char> {
public:
  typedef unsigned char Value;
  typedef Image2D<Value> Image;
 
  static bool write( Image & img, std::ostream & output, bool ascii )
  {
    if(ascii) {
        output << "P2" << std::endl << img.w() << " " << img.h() << std::endl << "255" << std::endl;
        for( int y=0; y<img.h(); y++) {
            for( int x=0; x<img.w(); x++) 
                output <<  std::to_string( img.at(x, y) ) << " ";
            output << std::endl;
        }
    } else {
        output << "P5" << std::endl << img.w() << " " << img.h() << std::endl << "255" << std::endl;
        for( auto it = img.begin(); it != img.end(); it++) {
            output << *it;
        }
    }

    return true;
  }
};
 
/// Specialization for color images.
template <>
class Image2DWriter<Color> {
public:
  typedef Color Value;
  typedef Image2D<Value> Image;
 
  static bool write( Image & img, std::ostream & output, bool ascii )
  {
    if(ascii) {
        output << "P3" << std::endl << img.w() << " " << img.h() << std::endl << "255" << std::endl;
        for( int y=0; y<img.h(); y++) {
            for( int x=0; x<img.w(); x++) {
                auto& c = img.at(x, y);
                output <<  std::to_string( c.red ) << " " << std::to_string( c.green ) << " " << std::to_string( c.blue ) << " ";
            }
            output << std::endl;
        }
    } else {
        output << "P6" << std::endl << img.w() << " " << img.h() << std::endl << "255" << std::endl;
        for( auto it = img.begin(); it != img.end(); it++) {
            output << it->red << it->green << it->blue;
        }
    }

    return true;
  }
};
 
#endif // _IMAGE2DWRITER_HPP_

