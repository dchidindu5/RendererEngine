#pragma once
#include <Rendering/Shaders/Compilers/ICompilerStage.h>

namespace ZEngine::Rendering::Shaders::Compilers
{

    class CompilationStage : public ICompilerStage
    {
    public:
        /**
         * Initialize a new CompilationStage instance.
         */
        CompilationStage();
        virtual ~CompilationStage();

        /**
         * Run Compiler stage
         *
         * @param information Collection of shader information
         */
        virtual void Run(std::vector<ShaderInformation>& information) override;

        /**
         * Run asynchronously compiler stage
         *
         * @param information Collection of shader information
         */
        virtual std::future<void> RunAsync(std::vector<ShaderInformation>& information) override;
    };
} // namespace ZEngine::Rendering::Shaders::Compilers
