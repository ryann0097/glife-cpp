#ifndef CANVAS_H
#define CANVAS_H

#include <vector>
using std::vector;
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <cstdint>

#include "common.h"

namespace life {

class Canvas {
 public:
  //== Alias
  typedef uint8_t component_t;     //!< Varia de 0 a 255...
  typedef unsigned long coord_t; //!< Onde tá a porcaria do pixel...
  //== Constants
  static constexpr uint8_t image_depth = 4;  //!< Default value is RGBA (4 channels).

 public:
  //=== Special members
  /// Constructor
  /*! Creates an empty canvas with the requested dimensions.
   * @param w The canvas width in virtual pixels.
   * @param h The canvas height in virtual pixels.
   * @param bs The canvas block size in real pixels.
   */
  Canvas(size_t w = 0, size_t h = 0, short bs = 4);
  /// Destructor.
  virtual ~Canvas(void);
  /// Copy constructor.
  Canvas(const Canvas& clone);
  /// Assignment operator.
  Canvas& operator=(const Canvas& other);

  //=== Members
  /// Clear the canvas with black color.
  void clear(const Color&c);
  /// Set the color of a pixel on the canvas.
  void pixel(coord_t x, coord_t y, const Color& c);
  /// Get the pixel color from the canvas.
  [[nodiscard]] Color pixel(coord_t x, coord_t y) const;

  //=== Attribute accessors members.
  /// Get the canvas width.
  [[nodiscard]] size_t width(void) const
  { return m_width; }
  /// Get the canvas height.
  [[nodiscard]] size_t height(void) const
  { return m_height; }
  /// Get the canvas pixels, as an array of `unsigned char`.
  [[nodiscard]] const component_t* pixels(void) const
  { return m_pixels.data(); }

 private:
  size_t m_width;                //!< The image width in pixel units.
  size_t m_height;               //!< The image height in pixel units.
  short m_block_size;            //!< Cell size in pixels
  vector<component_t> m_pixels;  //!< The pixels, stored as 3 RGB components.
};
}  // namespace life

#endif  // CANVAS_H
