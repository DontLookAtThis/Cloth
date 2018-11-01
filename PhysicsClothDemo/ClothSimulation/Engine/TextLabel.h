#pragma once

// Global Include
#include "Utility.h"

// Foward Declare
class Text;

class CTextLabel
{
public:
	CTextLabel(std::string _fontFamily);
	CTextLabel(std::string _fontFamily, std::string _text, glm::vec2 _position);
	~CTextLabel();

	void RenderTextLabel();

	void SetText(std::string _text);
	void SetPosition(glm::vec2 _position);
	void SetColor(glm::vec3 _color);
	void SetScale(GLfloat _scale);
	bool ControlsActive;

private:
	
	Text* m_textObj;
	std::string m_text;
	glm::vec2 m_position;
	GLfloat m_scale;
	glm::vec3 m_color;
};