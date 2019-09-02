#include "console.h"

Console::Console()
{
	initialized = false;              
	graphics = NULL;
	visible = false;                    
	fontColor = consoleNS::FONT_COLOR;
	backColor = consoleNS::BACK_COLOR;

	x = consoleNS::X;                   
	y = consoleNS::Y;

	textRect.bottom = consoleNS::Y + consoleNS::HEIGHT - consoleNS::MARGIN;
	textRect.left = consoleNS::X + consoleNS::MARGIN;
	textRect.right = consoleNS::X + consoleNS::WIDTH - consoleNS::MARGIN;
	textRect.top = consoleNS::Y + consoleNS::MARGIN;

	vertexBuffer = NULL;

	rows = 0;
	scrollAmount = 0;
}

Console::~Console()
{
	onLostDevice();
}

bool Console::initialize(Graphics * g, Input * in)
{
	try {
		graphics = g;                    // the graphics system
		input = in;

		vtx[0].x = x;
		vtx[0].y = y;
		vtx[0].z = 0.0f;
		vtx[0].rhw = 1.0f;
		vtx[0].color = backColor;

		vtx[1].x = x + consoleNS::WIDTH;
		vtx[1].y = y;
		vtx[1].z = 0.0f;
		vtx[1].rhw = 1.0f;
		vtx[1].color = backColor;

		vtx[2].x = x + consoleNS::WIDTH;
		vtx[2].y = y + consoleNS::HEIGHT;
		vtx[2].z = 0.0f;
		vtx[2].rhw = 1.0f;
		vtx[2].color = backColor;

		vtx[3].x = x;
		vtx[3].y = y + consoleNS::HEIGHT;
		vtx[3].z = 0.0f;
		vtx[3].rhw = 1.0f;
		vtx[3].color = backColor;

		graphics->createVertexBuffer(vtx, sizeof vtx, vertexBuffer);

		if (dxFont.initialize(graphics, consoleNS::FONT_HEIGHT, false,
			false, consoleNS::FONT) == false)
			return false;      
		dxFont.setFontColor(fontColor);

	}
	catch (...) {
		return false;
	}

	initialized = true;
	return true;
}

const void Console::draw()
{
	if (!visible || graphics == NULL || !initialized)
		return;

	graphics->drawQuad(vertexBuffer);      
	if (text.size() == 0)
		return;

	graphics->spriteBegin();                

	textRect.left = 0;
	textRect.top = 0;

	dxFont.print("|", textRect, DT_CALCRECT);
	int rowHeight = textRect.bottom + 2;    // height of 1 row (+2 is row spacing)
	if (rowHeight <= 0)                      // this should never be true
		rowHeight = 20;                     // force a workable result

	rows = (consoleNS::HEIGHT - 2 * consoleNS::MARGIN) / rowHeight;
	rows -= 2;                              // room for input prompt at bottom
	if (rows <= 0)                          // this should never be true
		rows = 5;                           // force a workable result

	textRect.left = (long)(x + consoleNS::MARGIN);
	textRect.right = (long)(textRect.right + consoleNS::WIDTH - consoleNS::MARGIN);
	textRect.bottom = (long)(y + consoleNS::HEIGHT - 2 * consoleNS::MARGIN - 2 * rowHeight);

	for (int r = scrollAmount; r < rows + scrollAmount && r < (int)(text.size()); r++)
	{
		textRect.top = textRect.bottom - rowHeight;
		dxFont.print(text[r], textRect, DT_LEFT);
		textRect.bottom -= rowHeight;
	}

	textRect.bottom = (long)(y + consoleNS::HEIGHT - consoleNS::MARGIN);
	textRect.top = textRect.bottom - rowHeight;
	std::string prompt = ">";                  
	prompt += input->getTextIn();
	dxFont.print(prompt, textRect, DT_LEFT);      

	graphics->spriteEnd();                    
}

void Console::showHide()
{
	if (!initialized)
		return;
	visible = !visible;
	input->clear(inputNS::KEYS_PRESSED | inputNS::TEXT_IN);

}

void Console::print(const std::string & str)
{
	if (!initialized)
		return;
	text.push_front(str);                      
	if (text.size() > consoleNS::MAX_LINES)
		text.pop_back();                        
}

std::string Console::getCommand()
{
	if (!initialized || !visible)
		return "";

	if (input->wasKeyPressed(CONSOLE_KEY))
		hide();                                 // turn off console

	if (input->wasKeyPressed(ESC_KEY))
		return "";

	if (input->wasKeyPressed(VK_UP))            // if up arrow
		scrollAmount++;
	else if (input->wasKeyPressed(VK_DOWN))     // if down arrow
		scrollAmount--;
	else if (input->wasKeyPressed(VK_PRIOR))    // if page up
		scrollAmount += rows;
	else if (input->wasKeyPressed(VK_NEXT))     // if page down
		scrollAmount -= rows;
	if (scrollAmount < 0)
		scrollAmount = 0;
	if (scrollAmount > consoleNS::MAX_LINES - 1)
		scrollAmount = consoleNS::MAX_LINES - 1;
	if (scrollAmount > (int)(text.size()) - 1)
		scrollAmount = (int)(text.size()) - 1;

	commandStr = input->getTextIn();            // get user entered text

	input->clear(inputNS::KEYS_DOWN | inputNS::KEYS_PRESSED | inputNS::MOUSE);

	if (commandStr.length() == 0)               // if no command entered
		return "";
	if (commandStr.at(commandStr.length() - 1) != '\r')   // if 'Enter' key not pressed
		return "";                              // return, can't be command

	commandStr.erase(commandStr.length() - 1);    // erase '\r' from end of command string
	input->clearTextIn();                       // clear input line
	inputStr = commandStr;                      // save input text
	return commandStr;                          // return command
}

void Console::onLostDevice()
{
	if (!initialized)
		return;
	dxFont.onLostDevice();
	safeRelease(vertexBuffer);
}

void Console::onResetDevice()
{
	if (!initialized)
		return;
	graphics->createVertexBuffer(vtx, sizeof vtx, vertexBuffer);
	dxFont.onResetDevice();
}
