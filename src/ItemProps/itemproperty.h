/*!
 * \file src/ItemProps/itemproperty.h
 * \brief Base class for dynamic item properties
 */

#ifndef PROPS_ITEMPROPERTY_H
#define PROPS_ITEMPROPERTY_H

#include <string>
#include <QString>

namespace U1 {

/*!
 * \namespace U1::Props
 * \brief Dynamic properties
 */
namespace Props {

/*! \brief Base class for dynamic item properties */
class ItemProperty
{
 public:
    const std::string name;  //!< Item property name

    /*! \brief Enumeration of used item property types */
    enum PropertyType : int
    {
        _PropertyGroup = 0,   //!< Group of properties
        _PropertyBool,        //!< Boolean property
        _PropertyInt8,        //!< 8 bit signed integer scalar property
        _PropertyUInt8,       //!< 8 bit unsigned integer scalar property
        _PropertyInt16,       //!< 16 bit signed integer scalar property
        _PropertyUInt16,      //!< 16 bit unsigned integer scalar property
        _PropertyInt32,       //!< 32 bit signed integer scalar property
        _PropertyUInt32,      //!< 32 bit unsigned integer scalar property
        _PropertyInt64,       //!< 64 bit signed integer scalar property
        _PropertyUInt64,      //!< 64 bit unsigned integer scalar property
        _PropertyQuality,     //!< 64 bit unsigned integer scalar property for object (circle) quality
        _PropertyPattern,     //!< 64 bit unsigned integer scalar property for line patterns
        _PropertyFloat,       //!< 32 bit floating point scalar property
        _PropertyDouble,      //!< 64 bit floating point scalar property
        _PropertyLongDouble,  //!< 128 bit floating point scalar property
        _PropertyVec2F,       //!< 32 bit 2D vector property
        _PropertyVec3F,       //!< 32 bit 3D vector property
        _PropertyVec2D,       //!< 64 bit 2D vector property
        _PropertyVec3D,       //!< 64 bit 3D vector property
        _PropertyVec2L,       //!< 128 bit 2D vector property
        _PropertyVec3L,       //!< 128 bit 3D vector property
        _PropertyText,        //!< \c QString text property -> any text
        _PropertyEnum,        //!< Enumeration property
    };

 protected:
    /*!
     * \brief Constructor
     * \param _name Item property name
     */
    inline ItemProperty(const std::string &_name)
        : name(_name)
    {
    }

 public:
    virtual ~ItemProperty() = default;

    /*!
     * \brief Getter for item property type
     * \return Item property type
     */
    virtual PropertyType type() const = 0;

    /*!
     * \brief Returns latest stored time step
     * \return Latest stored time step
     */
    virtual size_t latestTimeStep() const = 0;

    /*!
     * \brief Returns value at given time-step as text
     * \param _timeStep Time-step
     * \return Value at given time-step as text
     */
    virtual QString textValue(const size_t _timeStep) const = 0;
};

}  // namespace Props
}  // namespace U1

#endif  // PROPS_ITEMPROPERTY_H
