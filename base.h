#ifndef BASE_H
#define BASE_H

namespace AlgebraTAU {

enum orientation { row, column };
#define orientation_negate(a) ((a==row)? column : row)
template <orientation O,typename T> class vector;
template <typename T> class matrix;

} // namespace AlgebraTAU

#endif