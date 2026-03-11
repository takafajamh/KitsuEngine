#pragma once
#include <SDL3/SDL_gpu.h>
#include "../KitsuAsserts.hpp"

class Pipeline
{
public:

    Pipeline() = default;
    ~Pipeline()
    {
        Destroy();
    }

    Pipeline(const Pipeline&) = delete;
    Pipeline& operator=(const Pipeline&) = delete;

    Pipeline(Pipeline&& other) noexcept
    {
        m_Pipeline = other.m_Pipeline;
        m_Device = other.m_Device;

        other.m_Pipeline = nullptr;
    }

    Pipeline& operator=(Pipeline&& other) noexcept
    {
        if (this != &other)
        {
            Destroy();

            m_Pipeline = other.m_Pipeline;
            m_Device = other.m_Device;

            other.m_Pipeline = nullptr;
        }

        return *this;
    }

    bool Load(SDL_GPUDevice* device, const SDL_GPUGraphicsPipelineCreateInfo& info)
    {
        kitsu_return_assert(device != nullptr,
            "Pipeline creation failed: GPU device is null",
            "GPU device valid",
            false);

        m_Device = device;

        m_Pipeline = SDL_CreateGPUGraphicsPipeline(device, &info);

        kitsu_assert(
            m_Pipeline != nullptr,
            "Pipeline creation failed: {}",
            "Pipeline created successfully",
            SDL_GetError()
        );

        return m_Pipeline != nullptr;
    }

    void Destroy()
    {
        if (m_Pipeline)
        {
            SDL_ReleaseGPUGraphicsPipeline(m_Device, m_Pipeline);
            m_Pipeline = nullptr;
        }
    }

    SDL_GPUGraphicsPipeline* Get() const { return m_Pipeline; }

    bool Valid() const { return m_Pipeline != nullptr; }

private:

    SDL_GPUGraphicsPipeline* m_Pipeline = nullptr;
    SDL_GPUDevice* m_Device = nullptr;
};