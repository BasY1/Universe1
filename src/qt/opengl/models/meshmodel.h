/*!
 * \file qt/opengl/models/meshmodel.h
 * \author Michal Steller
 * \brief Base Open GL mesh model with material class declarations
 */

#ifndef UNIVERSE1_OPENGL_MODELS_MESHMODEL_H
#define UNIVERSE1_OPENGL_MODELS_MESHMODEL_H

#include "glmodel.h"

namespace Universe1 {
namespace OpenGL {
namespace Models {

/*!
 * \brief Base Open GL mesh model (object)
 */
class MeshModel : public GLModel
{
    Q_OBJECT
 public:
    /*!
     * \brief Model render mode
     */
    enum RenderMode
    {
        RenderBoth,       //!< Render triangles and lines
        RenderTriangles,  //!< Render triangles
        RenderLines       //!< Render lines
    };

    MeshModel(const std::vector<Material> &_materials,
              const RenderMode _renderMode,
              const bool _invertedFaces,
              QObject *_parent = nullptr);
    inline MeshModel(const std::vector<Material> &_materials, const RenderMode _renderMode, QObject *_parent = nullptr);
    inline MeshModel(const std::vector<Material> &_materials, const bool _invertedFaces, QObject *_parent = nullptr);
    inline MeshModel(const std::vector<Material> &_materials, QObject *_parent = nullptr);

    inline MeshModel(const Material &_material,
                     const RenderMode _renderMode,
                     const bool _invertedFaces,
                     QObject *_parent = nullptr);
    inline MeshModel(const Material &_material, const RenderMode _renderMode, QObject *_parent = nullptr);
    inline MeshModel(const Material &_material, const bool _invertedFaces, QObject *_parent = nullptr);
    inline MeshModel(const Material &_material, QObject *_parent = nullptr);

    ~MeshModel();

    inline bool canSwitchDrawWireFrame() const;
    inline bool drawWireFrame() const;
    inline bool invertedFaces() const;
    inline RenderMode renderMode() const;

    bool isInit() const override;

 protected:
    virtual bool initBuffers(const std::vector<QVector3D> &_vertexData,
                             const std::vector<QVector3D> &_normalData,
                             const std::vector<uint8_t> &_materialData,
                             const std::vector<uint> &_triangsData,
                             const std::vector<uint> &_linesData) final;

    void initGLImlp() override;
    void paintGLImlp(ShaderProgram *_program) override;

    /*!
     * \brief Rebuild model
     * \returns
     */
    virtual void rebuild() = 0;

 public slots:
    void setDrawWireFrame(bool _value);
    void setInvertedFaces(bool _value);
    void setRenderMode(RenderMode _value);

 protected:
    bool m_isInit;                  //!< OpenGL buffers initialized flag
    bool m_canSwitchDrawWireFrame;  //!< Is possible to switch value of draw wire-framed flag
    bool m_drawWireFrame;           //!< Draw wire-framed flag

    /*!
     * \brief Inverted faces flag
     * \details
     * | Value              | Expected triangle order          |
     * | :----------------- | :------------------------------- |
     * | \c false (default) | Counter-clockwise triangle order |
     * | \c true            | Clockwise triangle order         |
     */
    bool m_invertedFaces;

    RenderMode m_renderMode;  //!< Render mode

    std::vector<Material> m_materials;  //!< Used materials

 private:
    QOpenGLBuffer m_vertexBuffer;    //!< Vertex position buffer
    QOpenGLBuffer m_normalBuffer;    //!< Vertex normal buffer
    QOpenGLBuffer m_materialBuffer;  //!< Vertex material buffer
    QOpenGLBuffer m_triangsIndexes;  //!< Triangles faces index buffer
    QOpenGLBuffer m_linesIndexes;    //!< Line index buffer
    GLsizei m_triangsCount;          //!< Triangles faces index buffer item count
    GLsizei m_linesCount;            //!< Line index buffer item count
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Constructor
 * \param _materials Initial materials collection
 * \param _renderMode Initial render mode
 * \param _parent Parent \c QObject
 */
inline MeshModel::MeshModel(const std::vector<Material> &_materials, const RenderMode _renderMode, QObject *_parent)
    : MeshModel(_materials, _renderMode, false, _parent)
{
}

/*!
 * \brief Constructor
 * \param _materials Initial materials collection
 * \param _invertedFaces Initial inverted faces flag
 * \param _parent Parent \c QObject
 */
inline MeshModel::MeshModel(const std::vector<Material> &_materials, const bool _invertedFaces, QObject *_parent)
    : MeshModel(_materials, RenderBoth, _invertedFaces, _parent)
{
}

/*!
 * \brief Constructor
 * \param _materials Initial materials collection
 * \param _parent Parent \c QObject
 */
inline MeshModel::MeshModel(const std::vector<Material> &_materials, QObject *_parent)
    : MeshModel(_materials, RenderBoth, false, _parent)
{
}

/*!
 * \brief Constructor
 * \param _material Initial material
 * \param _renderMode Initial render mode
 * \param _invertedFaces Initial inverted faces flag
 * \param _parent Parent \c QObject
 */
inline MeshModel::MeshModel(const Material &_material,
                            const RenderMode _renderMode,
                            const bool _invertedFaces,
                            QObject *_parent)
    : MeshModel(std::vector<Material>({_material}), _renderMode, _invertedFaces, _parent)
{
}

/*!
 * \brief Constructor
 * \param _material Initial material
 * \param _renderMode Initial render mode
 * \param _parent Parent \c QObject
 */
inline MeshModel::MeshModel(const Material &_material, const RenderMode _renderMode, QObject *_parent)
    : MeshModel(std::vector<Material>({_material}), _renderMode, _parent)
{
}

/*!
 * \brief Constructor
 * \param _material Initial material
 * \param _invertedFaces Initial inverted faces flag
 * \param _parent Parent \c QObject
 */
inline MeshModel::MeshModel(const Material &_material, const bool _invertedFaces, QObject *_parent)
    : MeshModel(std::vector<Material>({_material}), _invertedFaces, _parent)
{
}

/*!
 * \brief Constructor
 * \param _material Initial material
 * \param _parent Parent \c QObject
 */
inline MeshModel::MeshModel(const Material &_material, QObject *_parent)
    : MeshModel(std::vector<Material>({_material}), _parent)
{
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Getter for is possible to switch value of draw wire-framed flag
 * \returns Is possible to switch value of draw wire-framed flag
 */
inline bool MeshModel::canSwitchDrawWireFrame() const
{
    return m_canSwitchDrawWireFrame;
}

/*!
 * \brief Getter for draw wire-framed flag
 * \returns Draw wire-framed flag
 */
inline bool MeshModel::drawWireFrame() const
{
    return m_drawWireFrame;
}

/*!
 * \brief Getter for inverted faces flag
 * \returns Inverted faces flag
 */
inline bool MeshModel::invertedFaces() const
{
    return m_invertedFaces;
}

/*!
 * \brief Getter for render mode
 * \returns Render mode
 */
inline MeshModel::RenderMode MeshModel::renderMode() const
{
    return m_renderMode;
}

}  // namespace Models
}  // namespace OpenGL
}  // namespace Universe1

#endif  // UNIVERSE1_OPENGL_MODELS_MESHMODEL_H
