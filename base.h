#ifndef BASE_H
#define BASE_H

#define self (*this)

namespace AlgebraTAU
{

class Fraction;
std::string to_string(const Fraction& f);

template<typename T>
inline T sqaure(const T& t){
    return t*t;
}

enum orientation
{
    row = 0,
    column
};
template <orientation O, typename T>
class vector;
template <typename T>
class matrix;

} // namespace AlgebraTAU

#endif