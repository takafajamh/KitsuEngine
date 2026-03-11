#pragma once

#include <array>
#include "Material.hpp"
#include "GPUPipeline.hpp"
#include "Texture.hpp"
#include "../KitsuAsserts.hpp"

class Material
{
public:

    static constexpr size_t MaxTextures = 8;

    Material() = default;

    void SetPipeline(Pipeline* pipeline)
    {
        kitsu_assert(
            pipeline != nullptr,
            "Material pipeline is null",
            "Material pipeline set"
        );

        m_Pipeline = pipeline;
    }
    Pipeline* GetPipeline() const
    {
        return m_Pipeline;
    }

    void SetTexture(size_t slot, Texture* texture)
    {
        kitsu_assert(
            slot < MaxTextures,
            "Material texture slot out of range: {}",
            "Material texture slot valid",
            slot
        );

        m_Textures[slot] = texture;
    }
    Texture* GetTexture(size_t slot) const
    {
        kitsu_assert(
            slot < MaxTextures,
            "Material texture slot out of range: {}",
            "Material texture slot valid",
            slot
        );

        return m_Textures[slot];
    }

private:

    Pipeline* m_Pipeline = nullptr;

    std::array<Texture*, MaxTextures> m_Textures{};
};

