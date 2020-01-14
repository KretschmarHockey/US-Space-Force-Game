#ifndef __SCOREINPUT_H__
#define __SCOREINPUT_H__

#include <string>

class BackBuffer;

class ScoreInput
{
public:
	ScoreInput();
	~ScoreInput();

	void Initialise();
	void Process(float deltaTime);
	void Draw(BackBuffer& backBuffer);
	std::string GetText();
	void Append(char* key);
	void Rerender();
	void BackSpace();
	void Copy();
	void Paste();
	void Submit();

protected:
	// The starting input text
	std::string m_inputText = "Anonymous";
	
	// The rerender text flag
	bool m_bRenderText = true;
};

#endif // __SCOREINPUT_H__