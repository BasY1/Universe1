#ifndef UNIVERSE1_VIDEO_ITEM3DSPACE_H
#define UNIVERSE1_VIDEO_ITEM3DSPACE_H

#include "../arrow/item3dangledim.h"

namespace Universe1 {
namespace Video {

/*! \brief 3D space item */
struct Item3DSpace : public Item3D
{
    DynamicBool showArrows;      //!< Show arrow flag
    DynamicBool showArrowNames;  //!< Show arrow names flag
    DynamicBool showPlaneXY;     //!< Show X-Y plane flag

    DynamicValue<uint> sizePlanePX;  //!< Count steps to +X
    DynamicValue<uint> sizePlaneMX;  //!< Count steps to -X
    DynamicValue<uint> sizePlanePY;  //!< Count steps to +Y
    DynamicValue<uint> sizePlaneMY;  //!< Count steps to -Y

    /*!
     * \brief Constructor
     * \param _showArrows Initial show arrow flag
     * \param _showArrowNames Initial show arrow names flag
     * \param _showPlaneXY Initial show X-Y plane flag
     * \param _sizePlanePX Initial count steps to +X
     * \param _sizePlaneMX Initial count steps to -X
     * \param _sizePlanePY Initial count steps to +Y
     * \param _sizePlaneMY Initial count steps to -Y
     * \param _visible Initial visible flag
     * \param _name Item name
     */
    Item3DSpace(const bool _showArrows,
                const bool _showArrowNames,
                const bool _showPlaneXY,
                const uint _sizePlanePX,
                const uint _sizePlaneMX,
                const uint _sizePlanePY,
                const uint _sizePlaneMY,
                const bool _visible,
                const std::string &_name);

    /*!
     * \brief Create 3D data at given time-step
     * \param _out Output 3D data list
     * \param _shader Shader program
     * \param _timeStep Time-step
     */
    void addData3D(std::list<Data3D> &_out, const Shader *_shader, const uint64_t _timeStep) const;
};

/*! \brief Footage 3D space database */
struct DBItem3DSpace : public DBItems3D
{
    /*!
     * \brief Constructor
     * \param _footageName Footage name
     * \param _items Pointer to all 3D items collection
     */
    DBItem3DSpace(const std::string &_footageName, std::list<Item3D *> *_items);

    Item3DSpace *curSpace = nullptr;  //!< Current space pointer (singleton space item)

    /*!
     * \brief Add 3D space item
     * \param _showArrows Initial show arrow flag
     * \param _showArrowNames Initial show arrow names flag
     * \param _showPlaneXY Initial show X-Y plane flag
     * \param _sizePlanePX Initial count steps to +X
     * \param _sizePlaneMX Initial count steps to -X
     * \param _sizePlanePY Initial count steps to +Y
     * \param _sizePlaneMY Initial count steps to -Y
     * \param _visible Initial visible flag
     * \return Created item
     */
    Item3DSpace *add(const bool _showArrows,
                     const bool _showArrowNames,
                     const bool _showPlaneXY,
                     const uint _sizePlanePX,
                     const uint _sizePlaneMX,
                     const uint _sizePlanePY,
                     const uint _sizePlaneMY,
                     const bool _visible);

    /*!
     * \brief Add visible 3D space item
     * \param _showArrows Initial show arrow flag
     * \param _showArrowNames Initial show arrow names flag
     * \param _showPlaneXY Initial show X-Y plane flag
     * \param _sizePlanePX Initial count steps to +X
     * \param _sizePlaneMX Initial count steps to -X
     * \param _sizePlanePY Initial count steps to +Y
     * \param _sizePlaneMY Initial count steps to -Y
     * \return Created item
     */
    inline Item3DSpace *add(const bool _showArrows,
                            const bool _showArrowNames,
                            const bool _showPlaneXY,
                            const uint _sizePlanePX,
                            const uint _sizePlaneMX,
                            const uint _sizePlanePY,
                            const uint _sizePlaneMY)
    {
        return add(
            _showArrows, _showArrowNames, _showPlaneXY, _sizePlanePX, _sizePlaneMX, _sizePlanePY, _sizePlaneMY, true);
    }

    /*!
     * \brief Add visible 3D space item
     * \return Created item
     */
    inline Item3DSpace *add()
    {
        return add(true, true, true, 20, 20, 20, 20);
    }

    /*!
     * \brief Add hidden 3D space item
     * \param _showArrows Initial show arrow flag
     * \param _showArrowNames Initial show arrow names flag
     * \param _showPlaneXY Initial show X-Y plane flag
     * \param _sizePlanePX Initial count steps to +X
     * \param _sizePlaneMX Initial count steps to -X
     * \param _sizePlanePY Initial count steps to +Y
     * \param _sizePlaneMY Initial count steps to -Y
     * \return Created item
     */
    inline Item3DSpace *addHidden(const bool _showArrows,
                                  const bool _showArrowNames,
                                  const bool _showPlaneXY,
                                  const uint _sizePlanePX,
                                  const uint _sizePlaneMX,
                                  const uint _sizePlanePY,
                                  const uint _sizePlaneMY)
    {
        return add(
            _showArrows, _showArrowNames, _showPlaneXY, _sizePlanePX, _sizePlaneMX, _sizePlanePY, _sizePlaneMY, false);
    }

    /*!
     * \brief Add hidden 3D space item
     * \return Created item
     */
    inline Item3DSpace *addHidden()
    {
        return addHidden(true, true, true, 20, 20, 20, 20);
    }
};

}  // namespace Video
}  // namespace Universe1

#endif  // UNIVERSE1_VIDEO_ITEM3DSPACE_H
