#include "Texture.h"

Texture::Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType) {
	
	type = texType;

	int width, height, nrChannels;
	//specifica che l'origine dell'immagine è in alto a sinistra
	stbi_set_flip_vertically_on_load(true);
	//carico l'immagine sotto forma di array di unsigned char
	unsigned char* bytes = stbi_load(image, &width, &height, &nrChannels, 0);

	//genero un id per la texture
	glGenTextures(1, &ID);
	glActiveTexture(slot);
	//specifico che tipo di texture sto creando
	glBindTexture(texType, ID);

	//setto i parametri della texture
	glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	//setto i parametri di wrapping 
	glTexParameterf(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//carico l'immagine nella texture
	glTexImage2D(texType, 0, GL_RGBA, width, height, 0, format, pixelType, bytes);
	//genero i mipmaps: sono delle versioni ridotte dell'immagine che vengono usate per il rendering a distanza
	glGenerateMipmap(texType);

	//libero la memoria dell'immagine
	stbi_image_free(bytes);
	glBindTexture(texType, 0);

}

void Texture::texUnit(Shader& shader, const char* uniform, GLuint unit)
{
	//setto la variabile uniform sampler2D texture
	GLuint tex0Uni = glGetUniformLocation(shader.ID, uniform);
	shader.Activate();
	glUniform1i(tex0Uni, unit);

}

void Texture::Bind()
{
	glBindTexture(type, ID);
}	

void Texture::Unbind()
{
	glBindTexture(type, 0);
}

void Texture::Delete()
{
	glDeleteTextures(1, &ID);
}
