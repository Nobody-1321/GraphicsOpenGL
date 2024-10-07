#include "componentCreator.hpp"
#include "componentStruct.hpp"
#include <Utils.hpp>
#include <iostream>

std::unique_ptr<Shader> ComponentCreator::createShaderComponent(const std::filesystem::path& vertexPath, const std::filesystem::path& fragmentPath)
{

    unsigned int vertexShader = Utils::createShaderProgram(vertexPath.c_str(), fragmentPath.c_str());
    return std::make_unique<Shader>(vertexShader, vertexPath, fragmentPath);
}