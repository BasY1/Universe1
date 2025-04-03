/*!
 * \file src/ItemProps/itempropertymaterial.h
 * \brief Open GL dynamic material properties
 */

#include "itempropertymaterial.h"

namespace U1 {
namespace Props {

ItemPropertyMaterialRGB::ItemPropertyMaterialRGB(const std::string &_name, const Math::MaterialRGB &_initialValue)
    : ItemPropertyGroup(_name)
    , ambient("ambient", _initialValue.ambient)
    , diffuse("diffuse", _initialValue.diffuse)
    , specular("specular", _initialValue.specular)
    , shine("shine", _initialValue.shine, 1.0f, 1024.0f)
{
    setupProperties({&ambient, &diffuse, &specular, &shine});
}

ItemPropertyMaterialRGBA::ItemPropertyMaterialRGBA(const std::string &_name, const Math::MaterialRGBA &_initialValue)
    : ItemPropertyGroup(_name)
    , ambient("ambient", _initialValue.ambient)
    , diffuse("diffuse", _initialValue.diffuse)
    , specular("specular", _initialValue.specular)
    , shine("shine", _initialValue.shine, 1.0f, 1024.0f)
    , alpha("alpha", _initialValue.alpha)
{
    setupProperties({&ambient, &diffuse, &specular, &shine, &alpha});
}

}  // namespace Props
}  // namespace U1
