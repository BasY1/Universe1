/*!
 * \file src/Math/sphere.cpp
 * \brief Sphere cache initialization
 */

#include "sphere.h"

namespace U1 {
namespace Math {

#ifndef DOXYGEN_SKIP

template <>
std::map<size_t, std::pair<std::vector<Vec3<float>>, std::vector<std::pair<size_t, size_t>>>>
    Sphere<float>::m_unitSpheres = {};

template <>
std::map<size_t, std::pair<std::vector<Vec3<double>>, std::vector<std::pair<size_t, size_t>>>>
    Sphere<double>::m_unitSpheres = {};

template <>
std::map<size_t, std::pair<std::vector<Vec3<long double>>, std::vector<std::pair<size_t, size_t>>>>
    Sphere<long double>::m_unitSpheres = {};

#endif  // DOXYGEN_SKIP

}  // namespace Math
}  // namespace U1
