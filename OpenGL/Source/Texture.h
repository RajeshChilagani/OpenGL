#pragma once
#include <string>
class Texture
{
public:
	Texture(const std::string& i_Filepath);
	~Texture();

	void Bind(uint32_t TextureSlot=0) const;
	void Unbind() const;
	inline int GetWidth() { return m_Width; }
	inline int GetHeight() { return m_Height; }
	
private:
	uint32_t m_RendererID;
	std::string m_Filepath;
	uint8_t* m_LocalBuffer;
	int m_Width, m_Height, m_BPP;
};
