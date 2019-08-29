#ifndef _TEXT_H
#define _TEXT_H
#include <string>
#include"image.h"
#include"constants.h"

namespace textNS
{
	enum Alignment { LEFT, RIGHT, CENTER, CENTER_MIDDLE, CENTER_BOTTOM, LEFT_BOTTOM, RIGHT_BOTTOM };
	struct FontData
	{
		UINT left;
		UINT right;
	};
	// Actual font width is 48, font height is 62
	const int FONT_BORDER = 3;      // 1 pixel wide transparent border + visible cell border on right and bottom
	const int FONT_WIDTH = 48;
	const int FONT_HEIGHT = 62;     // font is 62 pixels high
	const int GRID_WIDTH = FONT_WIDTH + FONT_BORDER;
	const int GRID_HEIGHT = FONT_HEIGHT + FONT_BORDER;
	const int COLUMNS = 16;         // number of columns in font image
	const int ROWS = 14;            // number of rows in font image
	const int FRAMES = 1;           // how many frames of animation (1 = not animated)
	const double ANIM_DELAY = 0.0;  // delay between animation frames
	const int MAX_FONT_HEIGHT = 1000;
	const int MIN_CHAR = 0x0020;    // minimum character code
	const int MAX_CHAR = 0x00FF;    // maximum character code
	const int PROPORTIONAL_SPACING = 5; // pixels between 1:1 scaled characters
	const int TAB_SIZE = 8;
	const char UNDERLINE = '_';
	const char SOLID = 0x7F;        // solid block used for fill character ASCII $7F
	const int BOLD_SIZE = 4;        // pixel shift for bold display
}
class Text :public Image
{
private:
	TextureManager fontTexture;
	LP_TEXTURE textureData;
	Graphics* graphics;
	char* file;
	UINT width;
	UINT height;
	textNS::FontData fontData[textNS::ROWS][textNS::COLUMNS];
	COLOR_ARGB color;
	COLOR_ARGB backColor;
	UINT fontHeight;
	UINT tabSize;
	UINT proportionalSpacing;
	bool proportional;
	bool underline;
	bool bold;
	textNS::Alignment align;
public:
	Text();
	virtual ~Text();
	virtual bool initialize(Graphics* g, const char *infile);
	virtual void update(float frameTime) {};
	virtual void onLostDevice();
	virtual void onResetDevice();

	virtual void setXY(int x, int y);
	virtual void print(const std::string &str);
	virtual void print(const std::string &str, int x, int y);
	virtual void print(const std::string &str, int x, int y, textNS::Alignment inalign);

	virtual void getWidthHeight(const std::string &str, UINT &width, UINT &height);
	virtual void setFontColor(COLOR_ARGB c) { color = c; }
	virtual COLOR_ARGB getFontColor() { return color; }
	virtual void setBackColor(COLOR_ARGB bc) { backColor = bc; }
	virtual COLOR_ARGB getBackColor() { return backColor; }
	virtual void setFontHeight(UINT height)
	{
		if (height == 0 || height > textNS::MAX_FONT_HEIGHT)
			return;
		fontHeight = height;
		spriteData.scale = (float)height / (float)textNS::FONT_HEIGHT;
	}
	virtual UINT getFontHeight() { return fontHeight; }
	virtual void setProportional(bool p) { proportional = p; }
	virtual bool getProportional() { return proportional; }
	virtual void setProportionalSpacing(UINT s) { proportionalSpacing = s; }
	virtual UINT getProportionalSpacing() { return proportionalSpacing; }
	virtual void setUnderline(bool u) { underline = u; }
	virtual bool getUnderline() { return underline; }
	virtual void setBold(bool b) { bold = b; }
	virtual bool getBold() { return bold; }
	virtual void setTabSize(UINT size)
	{
		if (size == 0)
			return;
		tabSize = size;
	}
	virtual UINT getTabSize() { return tabSize; }
	virtual void doAlign(const std::string &str);
	virtual void drawChar(UCHAR ch);
};
#endif