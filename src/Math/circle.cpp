/*!
 * \file src/Math/circle.cpp
 * \brief 2D and 3D circle cache initialization
 */

#include "circle.h"

namespace U1 {
namespace Math {

#ifndef DOXYGEN_SKIP

template <>
std::map<size_t, std::pair<std::vector<Vec2<float>>, std::vector<std::pair<size_t, size_t>>>>
    Circle2<float>::m_unitCircles = {};

template <>
std::map<size_t, std::pair<std::vector<Vec2<double>>, std::vector<std::pair<size_t, size_t>>>>
    Circle2<double>::m_unitCircles = {};

template <>
std::map<size_t, std::pair<std::vector<Vec2<long double>>, std::vector<std::pair<size_t, size_t>>>>
    Circle2<long double>::m_unitCircles = {};

template <>
std::map<size_t, std::pair<std::vector<float>, std::vector<std::pair<size_t, size_t>>>> Circle2<float>::m_circleAngles =
    {};

template <>
std::map<size_t, std::pair<std::vector<double>, std::vector<std::pair<size_t, size_t>>>>
    Circle2<double>::m_circleAngles = {};

template <>
std::map<size_t, std::pair<std::vector<long double>, std::vector<std::pair<size_t, size_t>>>>
    Circle2<long double>::m_circleAngles = {};

#endif  // DOXYGEN_SKIP

}  // namespace Math
}  // namespace U1
