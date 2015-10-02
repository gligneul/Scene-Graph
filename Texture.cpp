/**
 * PUC-Rio 2015.2
 * INF1339 - Computação Gráfica Tridimensional
 * Professor: Waldemar Celes
 * Gabriel de Quadros Ligneul 1212560
 * Trabalho - Projeto de Grafo de Cena
 */

#include <stdexcept>

#include <GL/gl.h>
#include <GL/glu.h>

#include "lodepng.h"

#include "Texture.h"

static int IsPowerOfTwo(unsigned int x)
{
    return (x & (x - 1)) == 0;
}

Texture::Texture(const std::string& path) {
    std::vector<unsigned char> image;
    unsigned int width, height;
    unsigned int error = lodepng::decode(image, width, height, path.c_str());
    if (error != 0)
        throw std::runtime_error(lodepng_error_text(error));

    if (!IsPowerOfTwo(width) || !IsPowerOfTwo(height))
        throw std::runtime_error("Width or height isn't power of two");

    glGenTextures(1, &id_);
    glBindTexture(GL_TEXTURE_2D, id_);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
            GL_LINEAR_MIPMAP_LINEAR);
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
//            GL_UNSIGNED_BYTE, image.data());
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, width, height, GL_RGBA,
            GL_UNSIGNED_BYTE, image.data());
}

Texture::~Texture() {
    glDeleteTextures(1, &id_);
}

void Texture::Load() {
    glBindTexture(GL_TEXTURE_2D, id_);
}

void Texture::Unload() {
}

