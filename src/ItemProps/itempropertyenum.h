/*!
 * \file src/ItemProps/itempropertyenum.h
 * \brief Enumerator dynamic item property
 */

#ifndef PROPS_ITEMPROPERTYENUM_H
#define PROPS_ITEMPROPERTYENUM_H

#include "itemproperty.h"

#include <QMetaEnum>
#include <map>

namespace U1 {
namespace Props {

/*! \brief Enumerator dynamic item property */
class ItemPropertyEnum : public ItemProperty
{
 protected:
    const QMetaEnum m_enum;                       //!< QT meta enum descriptor
    const std::map<int, QString> m_enumLiterals;  //!< Enumeration literal names
    std::map<size_t, int> m_jobs;                 //!< Property jobs

 public:
    /*!
     * \brief Create literal names from \c QMetaEnum
     * \param _metaEnumData \c QMetaEnum static object
     * \return Enum literal names
     */
    inline static std::map<int, QString> createLiteralNames(const QMetaEnum &_metaEnumData)
    {
        std::map<int, QString> result;
        for (int i = 0; i < _metaEnumData.keyCount(); ++i)
            result.insert(result.end(), {_metaEnumData.value(i), QString(_metaEnumData.key(i))});

        return result;
    }

    /*!
     * \brief Constructor
     * \param _name Item property name
     * \param _metaEnumData QT meta enum data
     * \param _enumLiterals Enum literal names
     * \param _initialValue Initial value
     */
    ItemPropertyEnum(const std::string &_name,
                     const QMetaEnum &_metaEnumData,
                     const std::map<int, QString> &_enumLiterals,
                     const int _initialValue);

    /*!
     * \brief Constructor
     * \param _name Item property name
     * \param _metaEnumData QT meta enum data
     * \param _initialValue Initial value
     */
    inline ItemPropertyEnum(const std::string &_name, const QMetaEnum &_metaEnumData, const int _initialValue)
        : ItemPropertyEnum(_name, _metaEnumData, createLiteralNames(_metaEnumData), _initialValue)
    {
    }

    /*!
     * \brief Constructor
     * \tparam T_ENUM Enumeration type
     * \param _name Item property name
     * \param _metaEnumData QT meta enum descriptor
     * \param _enumLiterals Enum literal names
     * \param _initialValue Initial value
     */
    template <typename T_ENUM>
    inline ItemPropertyEnum(const std::string &_name,
                            const QMetaEnum &_metaEnumData,
                            const std::map<int, QString> &_enumLiterals,
                            const T_ENUM _initialValue)
        : ItemPropertyEnum(_name, _metaEnumData, _enumLiterals, static_cast<int>(_initialValue))
    {
    }

    /*!
     * \brief Constructor
     * \tparam T_ENUM Enumeration type
     * \param _name Item property name
     * \param _metaEnumData QT meta enum descriptor
     * \param _initialValue Initial value
     */
    template <typename T_ENUM>
    inline ItemPropertyEnum(const std::string &_name, const QMetaEnum &_metaEnumData, const T_ENUM _initialValue)
        : ItemPropertyEnum(_name, _metaEnumData, static_cast<int>(_initialValue))
    {
    }

    /*!
     * \brief Getter for item property type
     * \return Item property type
     */
    PropertyType type() const override;

    /*!
     * \brief Getter for QT meta enum property type
     * \return QT meta enum property type
     */
    inline const QMetaEnum &metaEnumType() const
    {
        return m_enum;
    }

    /*!
     * \brief Getter for enumeration literal names map
     * \return Enumeration literal names map
     */
    inline const std::map<int, QString> &enumLiterals() const
    {
        return m_enumLiterals;
    }

    /*!
     * \brief Returns latest stored time step
     * \return Latest stored time step
     */
    size_t latestTimeStep() const override;

    /*!
     * \brief Getter for property value at specific time step
     * \param _timeStep Time step
     * \return Property value
     */
    int value(const size_t _timeStep) const;

    /*!
     * \brief Getter for property value at specific time step
     * \tparam T_ENUM Enumeration type
     * \param _timeStep Time step
     * \return Property value converted to enum
     */
    template <typename T_ENUM>
    inline T_ENUM valueEnum(const size_t _timeStep) const
    {
        return static_cast<T_ENUM>(value(_timeStep));
    }

    /*!
     * \brief Returns value at given time-step as text
     * \param _timeStep Time-step
     * \return Value at given time-step as text
     */
    QString textValue(const size_t _timeStep) const override;

    /*!
     * \brief Setup new value at time-step
     * \param _timeStep Time-step
     * \param _value Value at time-step
     */
    void setValue(const size_t _timeStep, const int _value);

    /*!
     * \brief Setup new value at time-step
     * \tparam T_ENUM Enumeration type
     * \param _timeStep Time-step
     * \param _value Value at time-step
     */
    template <typename T_ENUM>
    inline void setValue(const size_t _timeStep, const T_ENUM _value)
    {
        setValue(_timeStep, static_cast<int>(_value));
    }

    /*!
     * \brief Setup initial value
     * \param _value Initial value
     */
    void initValue(const int _value);

    /*!
     * \brief Setup initial value
     * \tparam T_ENUM Enumeration type
     * \param _value Initial value
     */
    template <typename T_ENUM>
    inline void initValue(const T_ENUM _value)
    {
        initValue(static_cast<int>(_value));
    }

    /*!
     * \brief Getter for the initial value
     * \return Initial value
     */
    inline int getInitValue() const
    {
        return m_jobs.empty() ? 0 : (*m_jobs.cbegin()).second;
    }

    /*!
     * \brief Latest time-step value
     * \return Value stored at latest time-step
     */
    inline int latestValue() const
    {
        return m_jobs.empty() ? 0 : (*m_jobs.crbegin()).second;
    }

    /*!
     * \brief Jobs getter
     * \return Jobs map
     */
    inline const std::map<size_t, int> &jobs() const
    {
        return m_jobs;
    }

    /*!
     * \brief Test if given value is a valid literal from this enum
     * \param _value Literal integer value
     * \return \c true when given value is a valid literal from this enum
     */
    inline bool isValidLiteral(const int _value) const
    {
        return m_enumLiterals.find(_value) != m_enumLiterals.cend();
    }

    /*!
     * \brief Parse string to literal index
     * \param _text Text to parse
     * \param _ok Output success flag
     * \return Literal index
     */
    int parseLiteral(const QString &_text, bool *_ok = nullptr);
};

}  // namespace Props
}  // namespace U1

#endif  // PROPS_ITEMPROPERTYENUM_H
