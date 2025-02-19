#include <pch.h>
#include <uuid.h>
#include <Managers/ShaderManager.h>

namespace ZEngine::Managers {

    ShaderManager::ShaderManager() : IAssetManager() {
        this->m_suffix = "_shader";
    }

    Ref<Rendering::Shaders::Shader> ShaderManager::Add(const char* name, const char* filename) {

        Ref<Rendering::Shaders::Shader> shader;
        shader.reset(Rendering::Shaders::CreateShader(filename, true));

        std::random_device                                     rd;
        std::ranlux48_base                                     generator(rd());
        uuids::basic_uuid_random_generator<std::ranlux48_base> gen(&generator);

        uuids::uuid const guid   = gen();
        const auto        key    = uuids::to_string(guid) + m_suffix;
        const auto        result = IManager::Add(key, std::move(shader));

        assert(result.has_value() == true);
        return result->get();
    }

    Ref<Rendering::Shaders::Shader> ShaderManager::Load(const char* filename) {
        std::filesystem::path p(filename);
        const auto            name = p.stem();
        return Add(reinterpret_cast<const char*>(name.u8string().c_str()), filename);
    }
} // namespace ZEngine::Managers
