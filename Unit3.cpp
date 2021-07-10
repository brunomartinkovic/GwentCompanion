//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "Unit1.h"
#include "Unit3.h"
#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
#include "userinfo.h"
#include <string>
#include <iostream>
TForm3 *Form3;
HINSTANCE MyCards;
//---------------------------------------------------------------------------
int all = 0;
int count= 0;
__fastcall TForm3::TForm3(TComponent* Owner)
	: TForm(Owner) {
		Xuser->Active=true;
		_di_IXMLcollectedType User = Getcollected(Xuser);
		Background->SendToBack();
		MyCards=LoadLibraryA("cards.dll");
		if(!MyCards) {
			ShowMessage("cards not found");
			return;
		}
		if(User->card[0]->id==1 && User->card[1]->id==2) {
            ShowMessage("BLA");
        }
		DConnect->Connected=true;
        QCard->Active=true;
		QCard->Close();
		QCard->SQL->Text = "SELECT * FROM Cards WHERE NOT Source=\"Leader\"";
	    QCard->ExecSQL();
		QCard->Open();
		DGrid->Options = TDBGridOptions(DGrid->Options) >> dgEditing;
		DGrid->Fields[5]->Visible=false;
		DGrid->Fields[5]->Visible=false;
		QCard->First();
		all = QCard->RecordCount;
		count = User->Count;
		if(count == all) {
			Hide->Hide();
		}
		if(User->Count<4) {
			QCard->First();
			QCard->SQL->Text = "UPDATE Cards SET COLLECTED =1 WHERE Source=\"Basic\" OR Source=\"Leader\"";
			QCard->ExecSQL();
			QCard->SQL->Text = "SELECT * FROM Cards WHERE NOT Source=\"Leader\"";
			QCard->Open();
			count = 0;
			for(int i=0;i<QCard->RecordCount;i++) {
				int uvjet =  QCard->FieldByName("Collected") -> AsInteger;
				if(uvjet == 1 ){
					_di_IXMLcardType card = User->Add();
					card->name = AnsiString(QCard->FieldByName("Name") -> AsString).c_str();
					card->comment = "Basic";
					card->id = QCard->FieldByName("ID")->AsInteger;
					Xuser->SaveToFile(Xuser->FileName);
                    count++;
				}
				QCard->Next();
			}
			Xuser->SaveToFile(Xuser->FileName);
			ShowMessage("Basic Cards were added to Your Collection");
		}
		Name->Font->Color = (TColor) RGB(218,165,32);
		Strength->Font->Color = (TColor) RGB(218,165,32);
}
void __fastcall TForm3::HideClick(TObject *Sender)
{
	_di_IXMLcollectedType User = Getcollected(Xuser);
	if(Hide->Checked){
			QCard->Close();
			QCard->SQL->Text = "SELECT * FROM Cards WHERE Collected = 0 AND NOT Source=\"Leader\"";
			QCard->Open();
			int id = QCard->FieldByName("ID")->AsInteger;
			if (id == 0) {
				ShowMessage("No collected cards, yet!");
			}
			else {
				QCard->Open();
			}
	}
	else {
      		QCard->Close();
			QCard->SQL->Text = "SELECT * FROM Cards WHERE NOT Source=\"Leader\"";
			QCard->Open();
    }
}
void __fastcall TForm3::FactionChange(TObject *Sender)
{
	AnsiString s ="SELECT * FROM Cards WHERE Faction = \"";
	AnsiString t =(AnsiString)Faction->Text;
	AnsiString r ="\" AND NOT Source=\"Leader\"";
	AnsiString i =s+t+r;
	QCard->Close();
	QCard->SQL->Text = i;
	QCard->ExecSQL();
	QCard->Open();
}
void __fastcall TForm3::DCardDataChange(TObject *Sender, TField *Field)
{
	MyCards=LoadLibraryA("cards.dll");
	if(!MyCards) {
		ShowMessage("cards not found");
		return;
	}
	int id= QCard->FieldByName("ID")->AsInteger;
	Card->Picture->Bitmap->LoadFromResourceID((unsigned)MyCards, id);
	Name->Caption = AnsiString(QCard->FieldByName("Name") -> AsString).c_str();
	Position->Caption = AnsiString(QCard->FieldByName("Position") -> AsString).c_str();
	Source->Caption = AnsiString("Source: ")+ AnsiString(QCard->FieldByName("Source") -> AsString).c_str();
    Strength->Caption= QCard->FieldByName("Strength")->AsInteger;
}
void __fastcall TForm3::CollectClick(TObject *Sender)
{
	_di_IXMLcollectedType User = Getcollected(Xuser);
	int uvjet =  QCard->FieldByName("Collected") -> AsInteger;
	if(uvjet == 0 ){
		AnsiString Comment;
		_di_IXMLcardType card = User->Add();
		Comment = InputBox("Add a Comment", "Comment:", "");
		card->name = AnsiString(QCard->FieldByName("Name") -> AsString).c_str();
		card->comment = Comment;
		card->id= QCard->FieldByName("ID") -> AsInteger;
		Xuser->SaveToFile(Xuser->FileName);
		ShowMessage("Card has been added to Your collection!");
		count++;
		UnicodeString s ="UPDATE Cards SET Collected = 1 WHERE ID =  ";
		UnicodeString t =(UnicodeString)QCard->FieldByName("ID")->AsString;
		UnicodeString r =s+t;
		QCard->SQL->Text = r;
		QCard->ExecSQL();
		if(count == all) {
			ShowMessage("Congratulations! You've collected every card in the game.");
			QCard->SQL->Text="SELECT * FROM Cards WHERE NOT Source=\"Leader\"";
			QCard->Open();
			Hide->Hide();
		}
		else {
			QCard->SQL->Text = "SELECT * FROM Cards WHERE Collected = 0 AND NOT Source=\"Leader\"";
            Hide->Checked=true;
			QCard->Open();
		}
	}
	else {
		ShowMessage("Card already collected!");
	}
}
void __fastcall TForm3::AllClick(TObject *Sender)
{
	QCard->Close();
	QCard->SQL->Text = "SELECT * FROM Cards WHERE NOT Source=\"Leader\"";
	QCard->Open();
    Hide->Checked=false;
}
void __fastcall TForm3::ResetClick(TObject *Sender)
{
    QCard->Close();
	QCard->SQL->Text = "UPDATE Cards SET Collected = 0";
	QCard->ExecSQL();
	_di_IXMLcollectedType User = Getcollected(Xuser);
	while(User->Count !=0) {
		 User->Delete(0);
		 Xuser->SaveToFile(Xuser->FileName);
	}
	QCard->SQL->Text = "UPDATE Cards SET COLLECTED =1 WHERE Source=\"Basic\" OR Source=\"Leader\"";
	QCard->ExecSQL();
	QCard->SQL->Text = "SELECT * FROM Cards WHERE NOT Source=\"Leader\"";
	QCard->Open();
	QCard->First();
	count = 0;
	for(int i=0;i<QCard->RecordCount;i++) {
		int uvjet =  QCard->FieldByName("Collected") -> AsInteger;
		if(uvjet == 1 ){
			_di_IXMLcardType card = User->Add();
			card->name = AnsiString(QCard->FieldByName("Name") -> AsString).c_str();
			card->comment = "Basic";
			card->id = QCard->FieldByName("ID")->AsInteger;
			Xuser->SaveToFile(Xuser->FileName);
			count++;
		}
		QCard->Next();
	}
	Xuser->SaveToFile(Xuser->FileName);
	QCard->Close();
	QCard->SQL->Text = "SELECT * FROM Cards WHERE Collected = 0 AND NOT Source=\"Leader\"";
	QCard->ExecSQL();
	QCard->Open();
	QCard->First();
	Hide->Show();
	Hide->Checked=true;
	ShowMessage("Your Collection has been reset");
	ShowMessage("Basic Cards were added to your collection");
}
void __fastcall TForm3::FormClose(TObject *Sender, TCloseAction &Action)
{
	FreeLibrary(MyCards);
}

