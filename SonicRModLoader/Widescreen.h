#pragma once

void D3D_RenderHUD_MainTimer_AlignRight(int XPos, int YPos, float ZPos, int Time, int Unk);
void D3D_RenderHUD_LapTimer_AlignRight(int XPos, int YPos, int Time);
void D3D_Render2DObject_AlignLeft(int XPos, int YPos, float ZPos, int XScale, int YScale, int TexPage, int TexXOff, int TexYOff, int TexWidth, int TexHeight, int TexTint);
void D3D_Render2DObject_AlignRight(int XPos, int YPos, float ZPos, int XScale, int YScale, int TexPage, int TexXOff, int TexYOff, int TexWidth, int TexHeight, int TexTint);
void D3D_Render2DObject_AlignCenter(int XPos, int YPos, float ZPos, int XScale, int YScale, int TexPage, int TexXOff, int TexYOff, int TexWidth, int TexHeight, int TexTint);
void D3D_Render2DObject_AlignAuto(int XPos, int YPos, float ZPos, int XScale, int YScale, int TexPage, int TexXOff, int TexYOff, int TexWidth, int TexHeight, int TexTint);
void Render_SetViewport_FixUp();
