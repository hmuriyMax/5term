//---------------------------------------------------------------------------

#include <vcl.h>
#include <cmath>
#pragma hdrstop

#define Drawer Form3->Canvas

#include "Unit3.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm3 *Form3;
//---------------------------------------------------------------------------
__fastcall TForm3::TForm3(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void DrawRect(const TPoint* pts, const TColor& clr){
	Drawer->Pen->Color = clr;
	Drawer->Brush->Color = clr;
	Drawer->Polygon(pts, 4);
}

void DrawRound(int x, int y, int r, const TColor& clr) {
	Drawer->Pen->Color = clr;
	Drawer->Brush->Color = clr;
	Drawer->Ellipse(x - r, y - r, x + r, y + r);
}

void DrawWall(){
    //?????? ?????? ?? ????
	{
		Drawer->Pen->Width = 2;
		Drawer->Brush->Color = TColor(RGB(75, 75, 75));
		Drawer->Rectangle(10,70,501,501);

		for (int j = 0; j <= 90; j++) {
			int i = 90-j;
			float num = j;
			DrawRound(270, 230, i, TColor(RGB(255-180*cos(3.14/2*num/90), 255-180*cos(3.14/2*num/90), 200-125*cos(3.14/2*num/90))));
		}

		TPoint pts_2[] = {{180, 230}, {180, 140}, {360, 140}, {360, 230}, {180, 230}};
		DrawRect(pts_2, TColor(RGB(75, 75, 75)));

		TPoint pts_3[] = {{260, 230}, {265, 210}, {275, 210}, {280, 230}, {260, 230}};
		DrawRect(pts_3, TColor(RGB(50, 50, 50)));

		TPoint pts_1[] = {{190, 460}, {210, 270}, {320, 270}, {300, 460}, {190, 460}};
		DrawRect(pts_1, TColor(RGB(100, 71, 50)));

		TPoint pts2[] = {{10, 450}, {500, 450}, {500, 500}, {10, 500}, {10, 450}};
		DrawRect(pts2, TColor(RGB(50, 50, 50)));

		TPoint pts0[] = {{200, 450}, {220, 280}, {310, 280}, {290, 450}, {200, 450}};
		DrawRect(pts0, TColor(RGB(240, 240, 150)));

		TPoint pts[] = {{200, 450}, {220, 280}, {290, 290}, {270, 460}, {200, 450}};
		DrawRect(pts, TColor(RGB(125, 104, 87)));

		for (int j = 0; j <= 15; j++) {
			int i = 15-j;
			TPoint pts3[] = {{100-i, 400+i}, {115-i, 300-i}, {170+i, 300-i}, {155+i, 400+i}, {100-i, 400+i}};
			int num = (240 - 75)/15;
			DrawRect(pts3, TColor(RGB(240-num*i, 240-num*i, i*75/15)));
		}
		TPoint pts31[] = {{96, 404}, {111, 296}, {174, 296}, {159, 404}, {96, 404}};
		DrawRect(pts31, TColor(RGB(170, 170, 100)));
		TPoint pts3[] = {{100, 400}, {115, 300}, {170, 300}, {155, 400}, {100, 400}};
		DrawRect(pts3, TColor(RGB(240, 240, 150)));

		for (int j = 0; j <= 15; j++) {
			int i = 15-j;
			TPoint pts4[] = {{340-i, 400+i}, {355-i, 300-i}, {410+i, 300-i}, {395+i, 400+i}, {340-i, 400+i}};
			int num = (240 - 75)/15;
			DrawRect(pts4, TColor(RGB(240-num*i, 240-num*i, i*75/15)));
		}
		TPoint pts41[] = {{336, 404}, {351, 296}, {414, 296}, {399, 404}, {336, 404}};
		DrawRect(pts41, TColor(RGB(170, 170, 100)));
		TPoint pts4[] = {{340, 400}, {355, 300}, {410, 300}, {395, 400}, {340, 400}};
		DrawRect(pts4, TColor(RGB(240, 240, 150)));
	}
}

void DrawButton(const TColor& clr){
		//?????? ??????
	Drawer->Pen->Width = 2;
	Drawer->Pen->Color = TColor(RGB(0, 120, 215));
	Drawer->Brush->Color = clr;
	Drawer->Rectangle(10, 520, 55, 550);
	Drawer->Brush->Style = bsClear;
	Drawer->Font->Name = "Arial";
	Drawer->Font->Size = 10;
	Drawer->Font->Color = TColor(RGB(0, 0, 0));
	Drawer->Font->Style = TFontStyles() << fsBold;
	Drawer->TextOut(20, 525, "ON");
}

void DrawText(){

	Drawer->Brush->Style = bsClear;
	Drawer->Font->Name = "Roboto Bk";
	Drawer->Font->Size = 40;
	Drawer->Font->Style = TFontStyles() << fsBold << fsItalic;

	for (int i = 50; i > 40; i--) {
		int j = 50-i;
		Drawer->Font->Color = TColor(RGB(75 + j*18, 75 - 5.5*j, 75 + 2.5*j));
		Drawer->TextOut(210+10-j, 125-5+j*0.5, "BAR");
	}

	Drawer->Font->Color = TColor(RGB(255, 20, 100));
	Drawer->TextOut(210, 125, "BAR");

	Drawer->Brush->Style = bsClear;
	Drawer->Font->Name = "Agency FB";
	Drawer->Font->Size = 20;
	Drawer->Font->Style = TFontStyles() << fsBold;

	for (int i = 50; i > 40; i--) {
		int j = 50-i;
		Drawer->Font->Color = TColor(RGB(75 + j*8, 75 - 5.5*j, 75 + 7.5*j));
		Drawer->TextOut(220+5-j*0.5, 100-2+j*0.2, "ZINZIVER");
	}

	Drawer->Font->Color = TColor(RGB(255, 120, 250));
	Drawer->TextOut(220, 100, "ZINZIVER");
}

void DrawCanvas(){
	Drawer->Pen->Width = 0;
	Drawer->Brush->Color = TColor(RGB(random(255), random(255), random(255)));
	Drawer->FillRect(Rect(0, 0, Form3->Width, Form3->Height));
}

void DrawTriangle(){
	Drawer->Pen->Color = clBlack;
	Drawer->Brush->Color = TColor(RGB(random(255), random(255), random(255)));
	TPoint pts[] = {{200, 300}, {300, 100}, {400, 300}, {200, 300}};
	Drawer->Polygon(pts, 3);
}

bool isInRound(int x, int y, TRound rnd){
	return pow(rnd.x - x, 2) + pow(rnd.y - y, 2) <= pow(rnd.rad, 2);
}

void __fastcall TForm3::Button1Click(TObject *Sender)
{
	 DrawWall();
	 DrawButton(TColor(RGB(225, 225, 225)));
	 wall_shown = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Label1MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y)
{
	 DrawButton(TColor(RGB(125, 125, 125)));
	 DrawText();
	 text_shown = true;
}
//---------------------------------------------------------------------------


void __fastcall TForm3::Label1MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y)
{
	 DrawButton(TColor(RGB(225, 225, 225)));
}
//---------------------------------------------------------------------------

void __fastcall TForm3::FormPaint(TObject *Sender)
{
	DrawCanvas();
	if (wall_shown) {
		DrawWall();
		DrawButton(TColor(RGB(225, 225, 225)));
	}
	if (text_shown) {
		DrawText();
	}
	if (trng_shown) {
		DrawTriangle();
	}
	if (crcl_shown) {
		DrawRound(rnd.x, rnd.y, rnd.rad, TColor(RGB(255, 0, 200)));
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Button2Click(TObject *Sender)
{
	DrawTriangle();
	trng_shown = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Button3Click(TObject *Sender)
{
	if (!crcl_shown) {
		rnd = {295, 600, 50};
		crcl_shown = true;
		DrawRound(rnd.x, rnd.y, rnd.rad, TColor(RGB(255, 0, 200)));
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm3::FormMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y)
{
	if (isInRound(X, Y, rnd)) {
		start = mv = {X, Y};
		move = true;
	}
	
}
//---------------------------------------------------------------------------

void __fastcall TForm3::FormMouseMove(TObject *Sender, TShiftState Shift, int X, int Y)
{
	if (move) {
		rnd.x += X - mv.x;
		rnd.y += Y - mv.y;
		mv.x = X;
		mv.y = Y;
		InvalidateRect(Handle, 0, true);
	}	
}
//---------------------------------------------------------------------------

void __fastcall TForm3::FormMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y)
{
	if (move && X == start.x && Y == start.y) {
		crcl_shown = false;
		InvalidateRect(Handle, 0, true);
	}
	move = false; 
}
//---------------------------------------------------------------------------

