#ifndef _COLOR_HPP_
#define _COLOR_HPP_

#include <iostream>

typedef unsigned char Byte;

/**
  Représente une couleur avec un codage RGB. Ce codage utilise 3
  octets, le premier octet code l'intensité du rouge, le deuxième
  l'intensité du vert, le troisième l'intensité du bleu.
  */
struct Color {
    typedef unsigned char Byte;

    /// Code les 3 canaux RGB sur 3 octets.
    Byte red, green, blue;

    Color() {}
    /// Crée la couleur spécifiée par (_red,_green,_blue).
    Color( Byte _red, Byte _green, Byte _blue )
        : red( _red ), green( _green ), blue( _blue ) {}

    /// @return l'intensité de rouge (entre 0.0 et 1.0)
    float r() const { return ( (float) red ) / 255.0; }
    /// @return l'intensité de vert (entre 0.0 et 1.0)
    float g() const { return ( (float) green ) / 255.0; }
    /// @return l'intensité de bleu (entre 0.0 et 1.0)
    float b() const { return ( (float) blue ) / 255.0; }

    /// Sert à désigner un canal.
    enum Channel { Red, Green, Blue };
    /// @return le canal le plus intense.
    Channel argmax() const 
    {
        if ( red >= green ) return red >= blue ? Red : Blue;
        else                return green >= blue ? Green : Blue;
    }
    /// @return l'intensité maximale des canaux
    float max() const { return std::max( std::max( r(), g() ), b() ); }
    /// @return l'intensité minimale des canaux
    float min() const { return std::min( std::min( r(), g() ), b() ); }
    /**
      Convertit la couleur RGB en le modèle HSV (TSV en français).
      @param h la teinte de la couleur (entre 0 et 359), hue en anglais.
      @param s la saturation de la couleur (entre 0.0 et 1.0)
      @param v la valeur ou brillance de la couleur (entre 0.0 et 1.0).
      */
    void getHSV( int & h, float & s, float & v ) const
    {
        // Taking care of hue
        if ( max() == min() ) h = 0;
        else {
            switch ( argmax() ) {
                case Red:   h = ( (int) ( 60.0 * ( g() - b() ) / ( max() - min() ) + 360.0 ) ) % 360;
                            break;
                case Green: h = ( (int) ( 60.0 * ( b() - r() ) / ( max() - min() ) + 120.0 ) );
                            break;
                case Blue:  h = ( (int) ( 60.0 * ( r() - g() ) / ( max() - min() ) + 240.0 ) );
                            break;
            }
        }
        // Taking care of saturation
        s = max() == 0.0 ? 0.0 : 1.0 - min() / max();
        // Taking care of value
        v = max();
    }
    /**
TODO: Convertit la couleur donnée avec le modèle HSV (TSV en
français) en une couleur RGB.
*/
    void setHSV( int h, float s, float v )
    {
        Byte t = h/60 % 6,
             f = h/60 - t;
        Byte l = v * (1-s),
             m = v * (1-f*s),
             n = v * (1 - (1-f) * f);

        switch(t) {
            case 0:
                red = v; green = n; blue = l;
                break;

            case 1:
                red = m; green = v; blue = l;
                break;

            case 2:
                red = l; green = v; blue = n;
                break;

            case 3:
                red = l; green = m; blue = v;
                break;

            case 4:
                red = n; green = l; blue = v;
                break;

            case 5:
                red = v; green = l; blue = m;
                break;

            default:
                break;
        }
    }
};

#endif //_COLOR_HPP_
