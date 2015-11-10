/**
 * PUC-Rio 2015.2
 * INF1339 - Computação Gráfica Tridimensional
 * Professor: Waldemar Celes
 * Gabriel de Quadros Ligneul 1212560
 * Trabalho - Projeto Final
 */

#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <string>

#include <glm/glm.hpp>

class ShaderProgram {
public:
    /**
     * Loads, compiles and links the shader program
     * Expects a prefix (%) for the files: %_vs.glsl and %_fs.glsl
     */
    ShaderProgram(const std::string& prefix);

    /**
     * Destructor
     */
    ~ShaderProgram();

    /**
     * Enables or disables the program
     */
    void Enable();
    void Disable();

    /**
     * Sets an attribute location
     */
    void SetAttribLocation(const char *name, unsigned int location);

    /**
     * Sets an uniform variable
     */
    void SetUniformBool(const char *name, bool value);
    void SetUniformVec3(const char *name, const glm::vec3& value);
    void SetUniformVec4(const char *name, const glm::vec4& value);
    void SetUniformMat4(const char *name, const glm::mat4& value);

    /**
     * Obtains the shader program handle
     */
    unsigned int GetHandle();

private:
    /**
     * Reads the whole file and returns it as a string
     */
    std::string ReadFile(const std::string& path);

    /**
     * Loads and compiles a shader from a file
     */
    void CompileShader(int shader_type, const std::string& path);

    /**
     * Links the shader program
     */
    void LinkShader();

    unsigned int program_;
};

#endif

