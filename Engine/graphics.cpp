#include "graphics.h"



Graphics::Graphics()
{
	direct3d = NULL;
	device3d = NULL;
	sprite = NULL;
	fullscreen = false;
	stencilSupport = false;
	width = GAME_WIDTH;
	height = GAME_HEIGHT;
	backColor = graphicsNS::BACK_COLOR;
	pOcclusionQuery = NULL;
	numberOfPixelsColliding = 0;
}

Graphics::~Graphics()
{
	releaseAll();
}

void Graphics::releaseAll()
{
	safeRelease(pOcclusionQuery);
	safeRelease(sprite);
	safeRelease(device3d);
	safeRelease(direct3d);
}
void Graphics::initD3Dpp()
{
	try {
		ZeroMemory(&d3dpp, sizeof(d3dpp));
		d3dpp.BackBufferWidth = width;
		d3dpp.BackBufferHeight = height;
		if (fullscreen)
			d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
		else
			d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;

		d3dpp.BackBufferCount = 1;
		d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		d3dpp.hDeviceWindow = hwnd;
		d3dpp.Windowed = (!fullscreen);
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
		d3dpp.EnableAutoDepthStencil = true;
		d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	}
	catch (...)
	{
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error Initializing D3D presentation Parameters"));
	}
}
void Graphics::initialize(HWND hw, int w, int h, bool full)
{
	hwnd = hw;
	width = w;
	height = h;
	fullscreen = full;

	direct3d = Direct3DCreate9(D3D_SDK_VERSION);
	if (direct3d == NULL)
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error Initializing D3D"));
	initD3Dpp();

	if (fullscreen)
	{
		if (isAdapterCompatible())
			d3dpp.FullScreen_RefreshRateInHz = pMode.RefreshRate;
		else
			throw(GameError(gameErrorNS::FATAL_ERROR, "The device does not support resolution or format"));
	}

	D3DCAPS9 caps;
	DWORD behavior;
	result = direct3d->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps);
	if ((caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT) == 0 ||
		caps.VertexShaderVersion < D3DVS_VERSION(1, 1))
		behavior = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	else
		behavior = D3DCREATE_HARDWARE_VERTEXPROCESSING;

	result = direct3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hwnd, behavior, &d3dpp, &device3d);
	if(FAILED(result))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error Creating D3D device"));
	result = D3DXCreateSprite(device3d, &sprite);

	if(FAILED(result))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error Creating D3DSprite"));

	if (FAILED(direct3d->CheckDeviceFormat(caps.AdapterOrdinal,
		caps.DeviceType,
		d3dpp.BackBufferFormat,
		D3DUSAGE_DEPTHSTENCIL,
		D3DRTYPE_SURFACE,
		D3DFMT_D24S8)))
		stencilSupport = false;
	else
		stencilSupport = true;
	device3d->CreateQuery(D3DQUERYTYPE_OCCLUSION, &pOcclusionQuery);

}

HRESULT Graphics::showBackBuffer()
{
	result = E_FAIL;
	result = device3d->Present(NULL, NULL, NULL, NULL);
	return result;
}

bool Graphics::isAdapterCompatible()
{
	UINT modes = direct3d->GetAdapterModeCount(D3DADAPTER_DEFAULT, d3dpp.BackBufferFormat);
	for (UINT i = 0; i < modes; i++)
	{
		result = direct3d->EnumAdapterModes(D3DADAPTER_DEFAULT, d3dpp.BackBufferFormat, i, &pMode);
		if (pMode.Height == d3dpp.BackBufferHeight && pMode.Width == d3dpp.BackBufferWidth &&
			pMode.RefreshRate >= d3dpp.FullScreen_RefreshRateInHz)
			return true;
	}
	return false;
}

HRESULT Graphics::reset()
{
	initD3Dpp();
	sprite->OnLostDevice();
	result = device3d->Reset(&d3dpp);
	sprite->OnResetDevice();
	return result;
}

HRESULT Graphics::getDeviceState()
{
	result = E_FAIL;
	if (device3d == NULL)
		return result;
	result = device3d->TestCooperativeLevel();
	return result;
}

HRESULT Graphics::loadTexture(const char * filename, COLOR_ARGB transcolor, UINT & width, UINT & height, LP_TEXTURE & texture)
{
	D3DXIMAGE_INFO info;
	result = E_FAIL;
	try
	{
		if (filename==NULL)
		{
			texture = NULL;
			return D3DERR_INVALIDCALL;
		}
		result = D3DXGetImageInfoFromFile(filename, &info);
		if (result != D3D_OK)
			return result;
		width = info.Width;
		height = info.Height;
		result = D3DXCreateTextureFromFileEx(device3d, filename, info.Width, info.Height, 1, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, transcolor, &info, NULL, &texture);

	}
	catch (...)
	{
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error in Graphics Load Texture"));
	}
	return result;
}

void Graphics::drawSprite(const SpriteData & spriteData, COLOR_ARGB color)
{
	if (spriteData.texture == NULL)
		return;
	D3DXVECTOR2 spriteCenter = D3DXVECTOR2((float)(spriteData.width / 2 * spriteData.scale), (float)(spriteData.height / 2 * spriteData.scale));
	D3DXVECTOR2 translate = D3DXVECTOR2((float)spriteData.x, (float)spriteData.y);
	D3DXVECTOR2 scaling(spriteData.scale, spriteData.scale);
	if (spriteData.flipHorizontal)
	{
		scaling.x *= -1;
		spriteCenter.x = (float)(spriteData.width*spriteData.scale);
		translate.x += (float)(spriteData.width*spriteData.scale);
	}
	if (spriteData.flipVertical)
	{
		scaling.y *= -1;
		spriteCenter.y = (float)(spriteData.height*spriteData.scale);
		translate.y += (float)(spriteData.height*spriteData.scale);
	}
	D3DXMATRIX matrix;
	D3DXMatrixTransformation2D(&matrix, NULL, 0.0f, &scaling, &spriteCenter, (float)(spriteData.angle), &translate);
	sprite->SetTransform(&matrix);
	sprite->Draw(spriteData.texture, &spriteData.rect, NULL, NULL, color);
}

void Graphics::changeDisplayMode(graphicsNS::DISPLAY_MODE mode)
{
	try {
		switch (mode)
		{
		case graphicsNS::FULLSCREEN:
			if (fullscreen)      // if already in fullscreen mode
				return;
			fullscreen = true; break;
		case graphicsNS::WINDOW:
			if (fullscreen == false) // if already in window mode
				return;
			fullscreen = false; break;
		default:        // default to toggle window/fullscreen
			fullscreen = !fullscreen;
		}
		reset();
		if (fullscreen)  // fullscreen
		{
			SetWindowLong(hwnd, GWL_STYLE, WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP);
		}
		else            // windowed
		{
			SetWindowLong(hwnd, GWL_STYLE, WS_OVERLAPPEDWINDOW);
			SetWindowPos(hwnd, HWND_TOP, 0, 0, GAME_WIDTH, GAME_HEIGHT,
				SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);

			// Adjust window size so client area is GAME_WIDTH x GAME_HEIGHT
			RECT clientRect;
			GetClientRect(hwnd, &clientRect);   // get size of client area of window
			MoveWindow(hwnd,
				0,                                           // Left
				0,                                           // Top
				GAME_WIDTH + (GAME_WIDTH - clientRect.right),    // Right
				GAME_HEIGHT + (GAME_HEIGHT - clientRect.bottom), // Bottom
				TRUE);                                       // Repaint the window
		}

	}
	catch (...)
	{
		// An error occured, try windowed mode 
		SetWindowLong(hwnd, GWL_STYLE, WS_OVERLAPPEDWINDOW);
		SetWindowPos(hwnd, HWND_TOP, 0, 0, GAME_WIDTH, GAME_HEIGHT,
			SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);

		// Adjust window size so client area is GAME_WIDTH x GAME_HEIGHT
		RECT clientRect;
		GetClientRect(hwnd, &clientRect);   // get size of client area of window
		MoveWindow(hwnd,
			0,                                           // Left
			0,                                           // Top
			GAME_WIDTH + (GAME_WIDTH - clientRect.right),    // Right
			GAME_HEIGHT + (GAME_HEIGHT - clientRect.bottom), // Bottom
			TRUE);                                       // Repaint the window
	}
}

DWORD Graphics::pixelCollision(const SpriteData & sprite1, const SpriteData & sprite2)
{
	if (!stencilSupport)     // if no stencil buffer support
		return 0;

	beginScene();

	// Set up stencil buffer using current entity
	device3d->SetRenderState(D3DRS_STENCILENABLE, true);
	device3d->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);
	device3d->SetRenderState(D3DRS_STENCILREF, 0x1);
	device3d->SetRenderState(D3DRS_STENCILMASK, 0xffffffff);
	device3d->SetRenderState(D3DRS_STENCILWRITEMASK, 0xffffffff);
	device3d->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);
	device3d->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_REPLACE);

	// Write a 1 into the stencil buffer for each non-transparent pixel in ent
	spriteBegin();
	// Enable stencil buffer (must be after spriteBegin)
	device3d->SetRenderState(D3DRS_STENCILENABLE, true);
	drawSprite(sprite2);            // write 1s to stencil buffer
	spriteEnd();

	// Change stencil buffer to only allow writes where the stencil value is 1
	// (where the ent sprite is colliding with the current sprite)
	device3d->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);
	device3d->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP);

	// Begin occlusion query to count pixels that are drawn
	pOcclusionQuery->Issue(D3DISSUE_BEGIN);

	spriteBegin();
	// Enable stencil buffer (must be after spriteBegin)
	device3d->SetRenderState(D3DRS_STENCILENABLE, true);
	drawSprite(sprite1);            // draw current entity 
	spriteEnd();
	// End occlusion query
	pOcclusionQuery->Issue(D3DISSUE_END);

	// Wait until the GPU is finished.
	while (S_FALSE == pOcclusionQuery->GetData(&numberOfPixelsColliding,
		sizeof(DWORD), D3DGETDATA_FLUSH))
	{
	}

	// Turn off stencil
	device3d->SetRenderState(D3DRS_STENCILENABLE, false);

	endScene();
	return numberOfPixelsColliding;
}
