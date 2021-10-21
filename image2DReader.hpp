#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include "image2D.hpp"
#include "color.hpp"

template <typename TValue>
class Image2DReader {
    public:
        typedef TValue Value;
        typedef Image2D<Value> Image;

        static bool read( Image & img, std::ostream & output, bool ascii )
        {
            std::cerr << "[Image2DWriter<TValue>::write] NOT IMPLEMENTED." << std::endl;
            return false;
        }
};

/// Specialization for gray-level images.
template <>
class Image2DReader<unsigned char> {
    public:
        typedef unsigned char Value;
        typedef Image2D<Value> Image;

        static bool read(Image & img, std::istream & input )
        {
            std::string line;
            int type;

            // get the type
            std::getline(input, line);
            type = line.compare( "P2" );

            if( type )
                input >> std::noskipws;
            else
                input >> std::skipws;

            // skip commented lines
            do std::getline(input, line); while( line.at(0) == '#' );

            // get m_width m_height and m_level
            std::istringstream istr( line );
            istr >> img.w() >> img.h();

            // fill m_data
            img.data().resize( img.w() * img.h() );

            if( type )
                for( auto it = img.begin(); it != img.end(); it++)
                    input >> *it;
            else {
                std::getline( input, line ); // skip first blank
                int y=0, tmp=0;

                while ( std::getline( input, line ) ) {
                    std::istringstream istr( line );

                    for( int x=0; x<img.w(); x++) {
                        istr >> tmp;
                        img.at(x, y) = tmp;
                    }

                    y++;
                }
            }
            return true;
        }
};

/// Specialization for color images.
template <>
class Image2DReader<Color> {
    public:
        typedef Color Value;
        typedef Image2D<Value> Image;

        static bool read( Image & img, std::istream & input )
        {
            std::string line;
            int type;

            // get the type
            std::getline(input, line);
            type = line.compare( "P3" );

            if( type )
                input >> std::noskipws;
            else
                input >> std::skipws;

            // skip commented lines
            do std::getline(input, line); while( line.at(0) == '#' );

            // get m_width m_height and m_level
            std::istringstream istr( line );
            istr >> img.w() >> img.h();

            // fill m_data
            img.data().resize( img.w() * img.h() );

            if( type ) {
                for( auto it = img.begin(); it != img.end(); it++) {
                    input >> it->red;
                    input >> it->green;
                    input >> it->blue;
                }
            } else {
                std::getline( input, line ); // skip first blank
                int y=0;

                while ( std::getline( input, line ) ) {
                    std::istringstream istr( line );

                    for( int x=0; x<img.w(); x++) {
                        auto& c = img.at(x, y);
                        istr >> c.red;
                        istr >> c.green;
                        istr >> c.blue;
                    }

                    y++;
                }
            }
            return true;
        }
};


