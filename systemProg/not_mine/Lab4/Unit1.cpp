#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
#include <math.h>
TForm1 *Form1;

TRect circle;
bool f1 = false;
bool f2 = false;
bool f3 = false;
bool f4 = false;

const int butOffset = 40;
int circleX = 150;
int circleY = 150;

double func(double x) {
	return x / 2 * exp(x / 9 + 0.8) * cos(x + 1.2);
}

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
void DrawPicture()
{
	TCanvas *canvas = Form1->Canvas;
	TPen *pen = canvas->Pen;
	TBrush *brush = canvas->Brush;

	pen->Width=1;

	//????
	brush->Color = clWebSkyBlue;
	pen->Color = clWebSkyBlue;
	canvas->Rectangle(10,10 + butOffset,600,170 + butOffset);

	//?????
	brush->Color = clWebLime;
	pen->Color = clWebLime;
	canvas->Rectangle(10,170 + butOffset,600,250 + butOffset);

	// ???
	brush->Color = clWebPeru;
	pen->Color = clBlack;
	canvas->Rectangle(100,200 + butOffset,300,100 + butOffset);
	TPoint p[3];
	p[0] = Point(100,100 + butOffset);
	p[1] = Point(300,100 + butOffset);
	p[2] = Point(200,50 + butOffset);
	canvas->Polygon(p,2);

	//????
	brush->Color = clWebCornFlowerBlue;
	canvas->Rectangle(130, 120 + butOffset, 170, 170 + butOffset);
	canvas->Rectangle(210, 120 + butOffset, 250, 170 + butOffset);
	brush->Color = clWebGoldenRod;
	canvas->Rectangle(148, 120 + butOffset, 152, 170 + butOffset);
	canvas->Rectangle(130, 136 + butOffset, 170, 140 + butOffset);
	canvas->Rectangle(228, 120 + butOffset, 232, 170 + butOffset);
	canvas->Rectangle(210, 136 + butOffset, 250, 140 + butOffset);

	//??????
	brush->Color = clWebYellow;
	pen->Color = clWebYellow;
	canvas->Ellipse(500, 30 + butOffset, 550, 80 + butOffset);

	pen->Width=3;
	canvas->MoveTo(525, 30 - 4 + butOffset);
	canvas->LineTo(525, 30 - 4 - 13 + butOffset);
	canvas->MoveTo(525, 80 + 4 + butOffset);
	canvas->LineTo(525, 80 + 4 + 13 + butOffset);

	canvas->MoveTo(500 - 4, 55 + butOffset);
	canvas->LineTo(500 - 4 - 13, 55 + butOffset);
	canvas->MoveTo(550 + 4, 55 + butOffset);
	canvas->LineTo(550 + 4 + 13, 55 + butOffset);

	canvas->MoveTo(514, 44 + butOffset);
	canvas->LineTo(514 - 13, 44 - 13 + butOffset);
	canvas->MoveTo(539, 44 + butOffset);
	canvas->LineTo(539 + 13, 43 - 13 + butOffset);
	canvas->MoveTo(514, 69 + butOffset);
	canvas->LineTo(514 - 13, 69 + 13 + butOffset);
	canvas->MoveTo(539, 69 + butOffset);
	canvas->LineTo(539 + 13, 69 + 13 + butOffset);
}

//---------------------------------------------------------------------------
void DrawGrafic()
{
	int width = Form1->PaintBox1->Width;
	int height = Form1->PaintBox1->Height;
	int xdel = width / 14;
	int ydel = height / 14;

	TCanvas *canvas = Form1->PaintBox1->Canvas;
	TPen *pen = canvas->Pen;

	pen->Width=1;

	// ???????????? ????? ? ? ?
	pen->Color = clBlack;
	canvas->MoveTo(width / 2, 0);
	canvas->LineTo(width / 2 ,height);
	canvas->MoveTo(0, height / 2);
	canvas->LineTo(width, height / 2);

	// ??????? ?
	canvas->MoveTo(width, height / 2);
	canvas->LineTo(width - 5, height / 2 - 3);
	canvas->MoveTo(width, height / 2);
	canvas->LineTo(width - 5, height / 2 + 3);
	// ??????? ?
	canvas->MoveTo(width - 2, height / 2 + 5);
	canvas->LineTo(width - 6, height / 2 + 12);
	canvas->MoveTo(width - 6, height / 2 + 5);
	canvas->LineTo(width - 2, height / 2 + 12);

	// ??????? Y
	canvas->MoveTo(width / 2, 0);
	canvas->LineTo(width / 2 - 3, 0 + 5);
	canvas->MoveTo(width / 2, 0);
	canvas->LineTo(width / 2 + 3, 0 + 5);
	// ??????? Y
	canvas->MoveTo(width / 2 - 5, 0 + 2);
	canvas->LineTo(width / 2 - 9, 0 + 12);
	canvas->MoveTo(width / 2 - 9, 0 + 2);
	canvas->LineTo(width / 2 - 7, 0 + 7);

	// ??????
	for (int x=xdel; x<width; x+=xdel)
	{
		canvas->MoveTo(x, height / 2 + 3);
		canvas->LineTo(x, height / 2 - 3);
	}
	for (int y=ydel; y<height; y+=ydel)
	{
		canvas->MoveTo(width / 2 + 3, y);
		canvas->LineTo(width / 2 - 3, y);
	}


	double x0 = -7.0;
	double y0 = 0.0;
	double dx = 0.25;
	double xMax = 7.0;

	pen->Color = clBlue;
	pen->Width=3;

	// ??????
	canvas->MoveTo(x0 * xdel, height / 2 - func(x0) * ydel);
	for (double x = x0 + dx; x <= xMax; x = x + dx) {
		canvas->LineTo(width / 2 + x * xdel, height / 2 - func(x) * ydel);
	}

}

//---------------------------------------------------------------------------
void DrawCircle(int X0, int Y0)
{
	Form1->Canvas->Pen->Width = 1;
	Form1->Canvas->Brush->Color = clBlue;
	Form1->Canvas->Pen->Color = clBlue;

	circle.Left = X0;
	circle.Top = Y0;
	circle.Right = X0 + 200;
	circle.Bottom = Y0 + 200;

	Form1->Canvas->Ellipse(circle.Left, circle.Top, circle.Right, circle.Bottom);
}

//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
	Form1->Button4Click(Sender);

	f1 = true;
	f2 = false;
	f3 = false;
}

//---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender)
{
	Form1->Button4Click(Sender);

	f1 = false;
	f2 = true;
	f3 = false;
}

 //---------------------------------------------------------------------------
void __fastcall TForm1::Button3Click(TObject *Sender)
{
	Form1->Button4Click(Sender);

	f1 = false;
	f2 = false;
	f3 = true;

	PaintBox1->Width = 20;
	PaintBox1->Height = 20;
}

//---------------------------------------------------------------------------
void __fastcall TForm1::Button4Click(TObject *Sender)
{
	::InvalidateRect(Form1->Handle, NULL, true);
	f1 = false;
	f2 = false;
	f3 = false;
	Form1->Canvas->Refresh();
	Form1->PaintBox1->Canvas->Refresh();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormResize(TObject *Sender)
{
	if (Form1->Height < 2 * butOffset) {
		Form1->Height = 2 * butOffset;
	}
	if (Form1->Width < 350) {
		Form1->Width = 350;
	}

}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormPaint(TObject *Sender)
{
	if (f1) {
		DrawPicture();
	}
	else if (f2) {
		PaintBox1->Width = Form1->Width - 70;
		PaintBox1->Height = Form1->Height - butOffset;
		DrawGrafic();
	}
	else if (f3) {
		DrawCircle(circleX,circleY);
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y)
{
	if (X > circle.Left && X < circle.Right && Y > circle.Top && Y < circle.Bottom ) {
		if(Button == mbLeft)
			f4 = true;
		else if (f3 && Button == mbRight) {
			f3 = false;
			::InvalidateRect(Form1->Handle, &circle, true);
			Form1->Canvas->Refresh();
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y)
{
	if(Button == mbLeft)
		f4 = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormMouseMove(TObject *Sender, TShiftState Shift, int X, int Y)
{
	if (f4) {
		::InvalidateRect(Form1->Handle, &circle, true);  // ???????
		Form1->Canvas->Refresh();
		circleX = X - 100;
		circleY = Y - 100;
		Form1->FormPaint(Sender);
	}
}
//---------------------------------------------------------------------------

