#include "stdafx.h"
#include "Widescreen.h"
#include "SonicRModLoader.h"

// Widescreen support
int MapWidthTo640() {
	int HorizontalResolution = *(int*)0x5F3874;
	int VerticalResolution = *(int*)0x75353C;
	float AspRatio = (float)HorizontalResolution / (float)VerticalResolution;
	return (int)(480 * AspRatio);
}

int GetExtraSpace() {
	return (MapWidthTo640() - 640);
}

void D3D_RenderHUD_MainTimer_AlignRight(
	int XPos, int YPos, float ZPos, int Time, int Unk
) {
	int *SpriteXOff = (int*)0x72E010;
	int tmp = *SpriteXOff;
	// Right side of screen?
	if (*SpriteXOff + 1 >= (HorizontalResolution >> 1)) {
		*SpriteXOff = HorizontalResolution >> 1;
	}
	else {
		*SpriteXOff = 0;
	}
	int WidthRatio = 0;
	if (MP_WindowCount == 2 && MP_HUD2PSplit == 1) {
		WidthRatio = 1;
	}

	D3D_RenderHUD_MainTimer(
		XPos + (GetExtraSpace() >> WidthRatio), YPos, ZPos, Time, Unk
	);

	*SpriteXOff = tmp;
}

void D3D_RenderHUD_LapTimer_AlignRight(int XPos, int YPos, int Time) {
	int *SpriteXOff = (int*)0x72E010;
	int tmp = *SpriteXOff;
	// Right side of screen?
	if (*SpriteXOff + 1 >= (HorizontalResolution >> 1)) {
		*SpriteXOff = HorizontalResolution >> 1;
	}
	else {
		*SpriteXOff = 0;
	}
	int WidthRatio = 0;
	if (MP_WindowCount == 2 && MP_HUD2PSplit == 1) {
		WidthRatio = 1;
	}

	D3D_RenderHUD_LapTimer(
		//(int)((WidthRatio * HorizontalResolution)) - (640 * WidthRatio - XPos),
		XPos + (GetExtraSpace() >> WidthRatio), YPos, Time
	);

	*SpriteXOff = tmp;
}

void D3D_Render2DObject_AlignLeft(
	int XPos, int YPos, float ZPos, int XScale, int YScale, int TexPage,
	int TexXOff, int TexYOff, int TexWidth, int TexHeight, int TexTint
) {
	// We run into clipping issues, so we have to disable our centering hack
	// to left-align HUD elements
	int *SpriteXOff = (int*)0x72E010;
	int tmp = *SpriteXOff;
	// Right side of screen?
	if (*SpriteXOff + 1 >= (HorizontalResolution >> 1)) {
		*SpriteXOff = HorizontalResolution >> 1;
	}
	else {
		*SpriteXOff = 0;
	}

	D3D_Render2DObject(
		XPos, YPos, ZPos, XScale, YScale, TexPage,
		TexXOff, TexYOff, TexWidth, TexHeight, TexTint
	);

	*SpriteXOff = tmp;
}

void D3D_Render2DObject_AlignRight(
	int XPos, int YPos, float ZPos, int XScale, int YScale, int TexPage,
	int TexXOff, int TexYOff, int TexWidth, int TexHeight, int TexTint
) {
	int *SpriteXOff = (int*)0x72E010;
	int tmp = *SpriteXOff;
	// Right side of screen?
	if (*SpriteXOff + 1 >= (HorizontalResolution >> 1)) {
		*SpriteXOff = HorizontalResolution >> 1;
	}
	else {
		*SpriteXOff = 0;
	}
	int WidthRatio = 0;
	if (MP_WindowCount == 2 && MP_HUD2PSplit == 1) {
		WidthRatio = 1;
	}

	D3D_Render2DObject(
		XPos + (GetExtraSpace() >> WidthRatio),
		YPos, ZPos, XScale, YScale, TexPage,
		TexXOff, TexYOff, TexWidth, TexHeight, TexTint
	);

	*SpriteXOff = tmp;
}

void D3D_Render2DObject_AlignCenter(
	int XPos, int YPos, float ZPos, int XScale, int YScale, int TexPage,
	int TexXOff, int TexYOff, int TexWidth, int TexHeight, int TexTint
) {
	int *SpriteXOff = (int*)0x72E010;
	int tmp = *SpriteXOff;
	int HorizOffset = 0;
	int MPScaler = 0;
	int *XStretch = (int*)0x7BCB88;
	int ExpectedXScale = (int)(VerticalResolution * (16.0f / 15.0f));
	bool NeedsHalving = (*XStretch != ExpectedXScale);

	if (*SpriteXOff + 1 >= (HorizontalResolution >> 1)) {
		HorizOffset = HorizontalResolution;
	}
	if ((MP_WindowCount == 2 && MP_HUD2PSplit == 1) || NeedsHalving) {
		HorizOffset = HorizOffset >> 2;
		MPScaler = 1; // Divide center by 2
	}

	*SpriteXOff = HorizOffset + (tmp >> MPScaler);
	D3D_Render2DObject(
		XPos, YPos, ZPos, XScale, YScale, TexPage,
		TexXOff, TexYOff, TexWidth, TexHeight, TexTint
	);

	*SpriteXOff = tmp;
}

void D3D_Render2DObject_AlignAuto(
	int XPos, int YPos, float ZPos, int XScale, int YScale, int TexPage,
	int TexXOff, int TexYOff, int TexWidth, int TexHeight, int TexTint
) {
	int CompVal = 320;
	if (MP_WindowCount == 2 && MP_HUD2PSplit == 1) {
		CompVal = 120;
	}
	if (XPos < CompVal) {
		D3D_Render2DObject_AlignLeft(
			XPos, YPos, ZPos, XScale, YScale, TexPage,
			TexXOff, TexYOff, TexWidth, TexHeight, TexTint
		);
	}
	else {
		D3D_Render2DObject_AlignRight(
			XPos, YPos, ZPos, XScale, YScale, TexPage,
			TexXOff, TexYOff, TexWidth, TexHeight, TexTint
		);
	}
}

void Render_SetViewport_FixUp() {
	int *XStretch = (int*)0x7BCB88;
	int *XOff = (int*)0x7AF248;
	// donor address (doesn't seem to effect anything)
	int *SpriteXOff = (int*)0x72E010;
	float AspRatio = (float)HorizontalResolution / (float)VerticalResolution;
	int ExpectedXScale = HorizontalResolution * 0.8;
	bool NeedsHalving = (*XStretch != ExpectedXScale);
	//float WidthAdjRatio = (4.0f / 3.0f) / AspRatio;

	float InvAspRatio = (float)VerticalResolution / (float)HorizontalResolution;
	*XStretch = (int)(VerticalResolution * (16.0f / 15.0f));

	// Vertical split requires halved aspect ratio
	if (NeedsHalving && MP_WindowCount > 1) {
		*XStretch /= 2;
	}

	// Simplified form of (HorizontalResolution - (VerticalResolution * (4.0f/3.0f))) / 2
	*SpriteXOff = *XOff + (int)(((0.5f) * HorizontalResolution) - ((2.0f / 3.0f) * VerticalResolution));
}