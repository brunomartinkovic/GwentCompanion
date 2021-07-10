//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "Unit4.h"
#include "decknames.h"
#include <vector>
#include <string>
#include <set>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm4 *Form4;
HINSTANCE MyCards;
//---------------------------------------------------------------------------
class Carddef {
public:
	 Carddef(){};
	 int ID;
	 AnsiString name;
	 int  strength;
	 AnsiString faction;
	 AnsiString position;
	 ~Carddef(){};
};
class Deck {
public:
	AnsiString name;
	AnsiString faction;
	std::vector <Carddef> list;
	int mcount;
	int rcount;
	int scount;
	~Deck() {
		list.clear();
	}
	void set_info(AnsiString name, AnsiString faction) {
			this->name = name;
			this->faction = faction;
	}
	void add(Carddef z) {
		list.push_back(z);
	}
	void clean() {
	   list.clear();
	}
	int size() {
	   return(list.size());
	}
};
Deck allcards;
Deck build;
Deck final;
int lead;
int skin;
__fastcall TForm4::TForm4(TComponent* Owner)
	: TForm(Owner)
{
	MyCards=LoadLibraryA("cards.dll");
    if(!MyCards) {
		ShowMessage("cards not found");
		return;
	}
	Background->SendToBack();
	DConnect->Connected=true;
	QCard->Active=true;
	QDeck->Active=true;
    Xuser->Active=true;
	DGrid->Options = TDBGridOptions(DGrid->Options) >> dgEditing;
	_di_IXMLmadeType Made = Getmade(Xuser);
	for(int i=0;i<Made->Count;i++) {
		Decks->Items ->Add(Made->deck[i]->name);
	}
	CardList->Hide();
	DeckDetail->Hide();
    DGrid->Hide();
	CreateD->Hide();
    CreateDL->Hide();
	AddS->Hide();
	AddSL->Hide();
	StReport->Hide();
    StReportL->Hide();
	PReport->Hide();
    PReportL->Hide();
	Delete->Hide();
    DeleteL->Hide();
	QCard->First();
}
void __fastcall TForm4::FactionsChange(TObject *Sender)
{
	AnsiString s ="SELECT * FROM Cards WHERE Faction = \"";
	AnsiString t =(AnsiString)Factions->Text;
	AnsiString r ="\" OR Faction = \"Neutral\"";
	QCard->Close();
	QCard->SQL->Text = s+t+r;
	QCard->ExecSQL();
	QCard->Open();
	QCard->First();
	allcards.clean();
	build.clean();
    CardList->Clear();
	Carddef temp;
	for(int i=0;i<QCard->RecordCount;i++) {
		temp.ID = QCard->FieldByName("ID") -> AsInteger;
		temp.name = AnsiString(QCard->FieldByName("Name") -> AsString).c_str();
		temp.strength = QCard->FieldByName("Strength")->AsInteger;
		temp.faction = AnsiString(QCard->FieldByName("Faction") -> AsString).c_str();
		temp.position = AnsiString(QCard->FieldByName("Position") -> AsString).c_str();
		if(temp.strength!=0) {
			allcards.add(temp);
    }
	QCard->Next();
	}
	if(t=="Northern Realms") {
		lead=46;
        skin=1;
	}
	else if(t=="Scoia'tael") {
		lead=47;
        skin=2;
	}
	else if(t=="Monsters") {
		lead=48;
        skin=3;
	}
	else {
		lead=49;
        skin=4;
	}
	Leader->Picture->Bitmap->LoadFromResourceID((unsigned)MyCards,lead);
	AnsiString sk = "skin/";
	AnsiString ki = skin;
	AnsiString in =".bmp";
	Skin->Picture->Bitmap->LoadFromFile(sk+ki+in);
	DGrid->Columns->Items[0]->Visible=false;
	DGrid->Columns->Items[1]->Width=100;
	DGrid->Columns->Items[2]->Width=100;
	DGrid->Columns->Items[3]->Width=80;
	DGrid->Columns->Items[4]->Visible=false;
	DGrid->Columns->Items[5]->Visible=false;
	DGrid->Columns->Items[6]->Visible=false;
    DGrid->Width=320;
	DGrid->Show();
	CardList->Hide();
	AddS->Hide();
	AddSL->Hide();
	CreateD->Show();
	CreateDL->Show();
}
void __fastcall TForm4::CreateDClick(TObject *Sender)
{
	build.clean();
	for(int i=0;i<allcards.size();i++) {
		if(allcards.list[i].faction == (AnsiString)Factions->Text || allcards.list[i].faction =="Neutral") {
			build.add(allcards.list[i]);
		}
	}
	for (int i=0; i < build.size(); i++) {
	  	CardList->Items->Add(build.list[i].name);
	}
	CardList->Show();
    All->Show();
	AddS->Show();
    AddSL->Show();
}
void __fastcall TForm4::AddSClick(TObject *Sender)
{
	int condition=0;
	for(int i =0;i<CardList->Items->Count;i++) {
		if(CardList->Checked[i]) {
			final.add(build.list[i]);
			condition++;
		}
	}
	if(condition<12 || condition >30) {
		ShowMessage("Choose between 12 and 30 cards. You have selected " +(AnsiString)condition+ " cards.");
        final.clean();
	}
	else {
		AnsiString s ="CREATE TABLE ";
		AnsiString t = InputBox("Name", "Name your deck:", "");
		t = StringReplace(t, " ", "", TReplaceFlags() << rfReplaceAll);
		while (t.Length()==0 || t=="NPremade" || t=="NRPremade" || t=="SPremade" || t=="MPremade") {
			t = InputBox("Name", "Name your deck:", "");
			t = StringReplace(t, " ", "", TReplaceFlags() << rfReplaceAll);
			build.set_info(Name,(AnsiString)Factions->Text);
		}
		AnsiString r =" (id INT,Name VARCHAR(50),Place VARCHAR(50),Strength INT)";
		QDeck->SQL->Text = s+t+r;
		QDeck->ExecSQL();
		for (int j=0; j < final.size(); j++) {
			AnsiString i ="INSERT INTO ";
			AnsiString n ="(id, Name,Strength,Place)";
			AnsiString g =" VALUES(";
			AnsiString com =",";
			AnsiString brack =");";
			AnsiString qoute="\"";
			AnsiString id = final.list[j].ID;
			AnsiString na = final.list[j].name;
			AnsiString st = final.list[j].strength;
			AnsiString po = final.list[j].position;
			QDeck->SQL->Text= i+t+n+g+id+com+qoute+na+qoute+com+st+com+qoute+po+qoute+brack;
			QDeck->ExecSQL();
		}
		DeckDetail->Items->Clear();
		AnsiString select="SELECT * FROM ";
		QDeck->SQL->Text = select + t;
		QDeck->Open();
		QDeck->First();
		for(int i=0;i<final.size();i++) {
			DeckDetail->Items->Add();
			DeckDetail->Items->Item[i]->Caption = AnsiString(QDeck->FieldByName("Name") -> AsString).c_str();
			DeckDetail->Items->Item[i]->SubItems->Add(QDeck->FieldByName("Strength") -> AsInteger);
			DeckDetail->Items->Item[i]->SubItems->Add(AnsiString(QDeck->FieldByName("Place") ->AsString).c_str());
			QDeck->Next();
		}
		_di_IXMLmadeType Made = Getmade(Xuser);
		_di_IXMLdeckType deck = Made->Add();
		deck->name=t;
		deck->leader=lead;
        deck->skin=skin;
		Xuser->SaveToFile(Xuser->FileName);
		CardList->Items->Clear();
		Decks->Items->Add(t);
		DLeader->Picture->Bitmap->LoadFromResourceID((unsigned)MyCards,lead);
		AnsiString sk = "skin/";
		AnsiString ki = skin;
		AnsiString in =".bmp";
		DSkin->Picture->Bitmap->LoadFromFile(sk+ki+in);
        Decks->Text=t;
		CardList->Hide();
		AddS->Hide();
		AddSL->Hide();
		StReport->Show();
        StReportL->Show();
		PReport->Show();
        PReportL->Show();
		Delete->Show();
        DeleteL->Show();
		DeckDetail->Show();
		final.clean();
		All->Checked=false;
        All->Hide();
    }
}
void __fastcall TForm4::DecksChange(TObject *Sender)
{
	DeckDetail->Clear();
	AnsiString s ="SELECT * FROM ";
	AnsiString t =(AnsiString)Decks->Text;
	QDeck->Close();
	QDeck->SQL->Text = s+t;
	QDeck->ExecSQL();
	QDeck->Open();
	for(int i=0;i<QDeck->RecordCount;i++) {
		DeckDetail->Items->Add();
		DeckDetail->Items->Item[i]->Caption = AnsiString(QDeck->FieldByName("Name") -> AsString).c_str();
		DeckDetail->Items->Item[i]->SubItems->Add(QDeck->FieldByName("Strength") -> AsInteger);
		DeckDetail->Items->Item[i]->SubItems->Add(AnsiString(QDeck->FieldByName("Place") ->AsString).c_str());
		QDeck->Next();
	}
	DeckDetail->Show();
	_di_IXMLmadeType Made = Getmade(Xuser);
	DLeader->Picture->Bitmap->LoadFromResourceID((unsigned)MyCards,Made->deck[Decks->ItemIndex]->leader);
	AnsiString sk = "skin/";
	AnsiString ki = Made->deck[Decks->ItemIndex]->skin;
	AnsiString in =".bmp";
	DSkin->Picture->Bitmap->LoadFromFile(sk+ki+in);
	StReport->Show();
    StReportL->Show();
	PReport->Show();
    PReportL->Show();
	Delete->Show();
    DeleteL->Show();
}
void __fastcall TForm4::StReportClick(TObject *Sender)
{
	int str =0;
    Deck temp;
    temp.clean();
	DeckDetail->Clear();
	AnsiString s ="SELECT * FROM ";
	AnsiString t =(AnsiString)Decks->Text;
	QDeck->Close();
	QDeck->SQL->Text = s+t;
	QDeck->ExecSQL();
	QDeck->Open();
	QDeck->First();
	for(int i=0;i<QDeck->RecordCount;i++) {
		Carddef t;
		t.name= AnsiString(QDeck->FieldByName("Name") -> AsString).c_str();
		t.strength=QDeck->FieldByName("Strength") -> AsInteger;
		t.position=AnsiString(QDeck->FieldByName("Place") ->AsString).c_str();
		temp.add(t);
		QDeck->Next();
	}
	for (int i=0; i < temp.size(); i++) {
    	str += temp.list[i].strength;
	}
	QDeck->Close();
	QDeck->SQL->Text = s+t;
	QDeck->ExecSQL();
	QDeck->Open();
	for(int i=0;i<QDeck->RecordCount;i++) {
		DeckDetail->Items->Add();
		DeckDetail->Items->Item[i]->Caption = AnsiString(QDeck->FieldByName("Name") -> AsString).c_str();
		DeckDetail->Items->Item[i]->SubItems->Add(QDeck->FieldByName("Strength") -> AsInteger);
		DeckDetail->Items->Item[i]->SubItems->Add(AnsiString(QDeck->FieldByName("Place") ->AsString).c_str());
		QDeck->Next();
	}
	AnsiString total;
	total="Total Strength: ";
	ShowMessage(total+str);
	temp.clean();
}
void __fastcall TForm4::PReportClick(TObject *Sender)
{
	int mcount=0;
	int scount=0;
	int rcount=0;
    Deck temp;
	DeckDetail->Clear();
	AnsiString s ="SELECT * FROM ";
	AnsiString t =(AnsiString)Decks->Text;
	QDeck->Close();
	QDeck->SQL->Text = s+t;
	QDeck->ExecSQL();
	QDeck->Open();
	QDeck->First();
	for(int i=0;i<QDeck->RecordCount;i++) {
		Carddef t;
		t.name= AnsiString(QDeck->FieldByName("Name") -> AsString).c_str();
		t.strength=QDeck->FieldByName("Strength") -> AsInteger;
		t.position=AnsiString(QDeck->FieldByName("Place") ->AsString).c_str();
		temp.add(t);
		QDeck->Next();
	}
	for(int i=0;i<temp.size();i++) {
		if(temp.list[i].position == "Siege") scount++;
		else if (temp.list[i].position == "Ranged") rcount++;
	  	else mcount++;
    }
	QDeck->Close();
	QDeck->SQL->Text = s+t;
	QDeck->ExecSQL();
	QDeck->Open();
	for(int i=0;i<QDeck->RecordCount;i++) {
		DeckDetail->Items->Add();
		DeckDetail->Items->Item[i]->Caption = AnsiString(QDeck->FieldByName("Name") -> AsString).c_str();
		DeckDetail->Items->Item[i]->SubItems->Add(QDeck->FieldByName("Strength") -> AsInteger);
		DeckDetail->Items->Item[i]->SubItems->Add(AnsiString(QDeck->FieldByName("Place") ->AsString).c_str());
		QDeck->Next();
	 }
	AnsiString total;
	AnsiString mt;
	AnsiString rt;
	AnsiString st;
	total="Deck contains:\n";
	mt=" melee cards\n";
	rt=" ranged cards\n";
	st=" siege cards";
	ShowMessage(total+mcount+mt+rcount+rt+scount+st);
    temp.clean();
}
void __fastcall TForm4::DeleteClick(TObject *Sender)
{
	if((AnsiString)Decks->Text=="NRPremade" || (AnsiString)Decks->Text=="SPremade" || (AnsiString)Decks->Text=="MPremade" || (AnsiString)Decks->Text=="NPremade") {
		ShowMessage("You cannot delete premade decks!");
	}
	else {
		AnsiString s ="DROP TABLE ";
		AnsiString t =(AnsiString)Decks->Text;
		QDeck->Close();
		QDeck->SQL->Text = s+t;
		QDeck->ExecSQL();
		DeckDetail->Clear();
		_di_IXMLmadeType Made = Getmade(Xuser);
		int index=0;
		for (int i=0; i < Made->Count; i++) {
			 if(Made->deck[i]->name==t) index=i;
		}
		Made->Delete(index);
		Xuser->SaveToFile(Xuser->FileName);
		for(int i=0;i<Decks->Items->Count;i++) {
			 Decks->Items->Delete(i);
		}
		Decks->Items->Clear();
		for(int i=0;i<Made->Count;i++) {
			 Decks->Items ->Add (Made->deck[i]->name);
		}
        Decks->ItemIndex=0;
		Decks->OnChange(Form4);
	}
}
void __fastcall TForm4::AllClick(TObject *Sender)
{
	if(All->Checked==true) {
		for(int i =0;i<CardList->Items->Count;i++) {
			CardList->Checked[i]=true;
		}
	}
	else {
		for(int i =0;i<CardList->Items->Count;i++) {
			CardList->Checked[i]=false;
		}
	}
}
void __fastcall TForm4::FormClose(TObject *Sender, TCloseAction &Action)
{
	allcards.clean();
	final.clean();
	build.clean();
    FreeLibrary(MyCards);
}
