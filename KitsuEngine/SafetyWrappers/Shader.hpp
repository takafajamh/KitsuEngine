#pragma once

#include <SDL3/SDL_gpu.h>
#include <vector>
#include <string>
#include "../KitsuAsserts.hpp"

class Shader
{
public:

    Shader() = default;
    ~Shader()
    {
        Destroy();
    }

    Shader(const Shader&) = delete;
    Shader& operator=(const Shader&) = delete;

    Shader(Shader&& other) noexcept
    {
        m_Shader = other.m_Shader;
        m_Device = other.m_Device;

        other.m_Shader = nullptr;
    }

    Shader& operator=(Shader&& other) noexcept
    {
        if (this != &other)
        {
            Destroy();

            m_Shader = other.m_Shader;
            m_Device = other.m_Device;

            other.m_Shader = nullptr;
        }

        return *this;
    }

    bool Load(SDL_GPUDevice* device, const std::vector<uint8_t>& code, SDL_GPUShaderStage stage, SDL_GPUShaderFormat format, const std::string& entry = "main")
    {
        kitsu_return_assert(device != nullptr,
            "Shader load failed: GPU device is null",
            "GPU device valid",
            false);

        kitsu_return_assert(!code.empty(),
            "Shader load failed: bytecode empty",
            "Shader bytecode valid",
            false);

        SDL_GPUShaderCreateInfo info{};
        info.code = code.data();
        info.code_size = code.size();
        info.entrypoint = entry.c_str();
        info.format = format;
        info.stage = stage;

        info.num_samplers = 0;
        info.num_storage_buffers = 0;
        info.num_storage_textures = 0;
        info.num_uniform_buffers = 0;

        m_Shader = SDL_CreateGPUShader(device, &info);

        kitsu_assert(
            m_Shader != nullptr,
            "Failed to create shader: {}",
            "Shader created successfully",
            SDL_GetError()
        );

        m_Device = device;

        return m_Shader != nullptr;
    }

    void Destroy()
    {
        if (m_Shader)
        {
            SDL_ReleaseGPUShader(m_Device, m_Shader);
            m_Shader = nullptr;
        }
    }

    SDL_GPUShader* Get() const { return m_Shader; }
    bool Valid() const { return m_Shader != nullptr; }

private:

    SDL_GPUShader* m_Shader = nullptr;
    SDL_GPUDevice* m_Device = nullptr;
};

