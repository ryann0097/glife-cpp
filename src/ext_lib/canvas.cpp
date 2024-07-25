/*!
 * Canvas class implementation.
 * @file canvas.cpp
 */

#include "canvas.h"

namespace life {

  Canvas::Canvas(size_t w, size_t h, short bs) : m_width{ w * bs }, m_height{ h * bs }, m_block_size{ bs }
  { m_pixels.resize(m_width * m_height * image_depth); }
    /// Destructor.
  Canvas::~Canvas(void) = default;
    /// Copy constructor.
  Canvas::Canvas(const Canvas& clone){
     m_width = clone.m_width;
     m_height = clone.m_height;
     m_block_size =  clone.m_block_size;
     m_pixels = clone.m_pixels;
  }
  /// Assignment operator.
  Canvas& Canvas::operator=(const Canvas& other){
  	if (this != &other) {
        m_width = other.m_width;
        m_height = other.m_height;
        m_block_size = other.m_block_size;
        m_pixels = other.m_pixels;
    } return *this;
  }
  //=== Members
  /// Clear the canvas with black color.
  void Canvas::clear(const Color&c){
    // Calcula o tamanho total dos pixels no canvas
    size_t total_pixels = m_width * m_height * image_depth;

    // Preenche m_pixels com a cor especificada
    for (size_t i = 0; i < total_pixels; i += image_depth) {
        m_pixels[i] = c.channels[Color::R];
        m_pixels[i+1] = c.channels[Color::G];
        m_pixels[i+2] = c.channels[Color::B];
        m_pixels[i+3] = 255; // nao tirar isso ou deixar em zero, se n, n aparece nada
    }
  }
  /// Set the color of a pixel on the canvas.
  void Canvas::pixel(coord_t x, coord_t y, const Color& c){
    size_t i = (y*m_width+x)*image_depth; // Como temos um vetor unidimensional, a maneira de acessar é essa.
    m_pixels[i] = c.channels[0];
    m_pixels[i+1] = c.channels[1];
    m_pixels[i+2] = c.channels[2];
    m_pixels[i+3] = 255;
  }
  /// Get the pixel color from the canvas.
  Color Canvas::pixel(coord_t x, coord_t y) const{
    size_t index = (y*m_width+x)*image_depth;
    Color returnColor(m_pixels[index], m_pixels[index+1], m_pixels[index+2]);
    return returnColor;
  }

}  // namespace life

//================================[ canvas.cpp ]================================//
