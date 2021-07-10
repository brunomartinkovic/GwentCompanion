//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include <vector>
#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
#include<iostream>
#include "Unit2.h"
#include "Unit3.h"
#include "Unit4.h"
#include "Unit5.h"
#include <MMSystem.h>
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
	Background->SendToBack();
    PlaySound(TEXT("mainmenu.wav"), NULL, SND_LOOP | SND_ASYNC);
}
void __fastcall TForm1::MultiplayerClick(TObject *Sender)
{
    Form5->Show();
}
void __fastcall TForm1::BuilderClick(TObject *Sender)
{
	TForm4 *Form = new TForm4( this );
	Form->ShowModal();
}
void __fastcall TForm1::CDBClick(TObject *Sender)
{
	TForm3 *Form = new TForm3( this );
	Form->ShowModal();
}
void __fastcall TForm1::CollectionClick(TObject *Sender)
{
	TForm2 *Form = new TForm2( this );
	Form->ShowModal();
}
