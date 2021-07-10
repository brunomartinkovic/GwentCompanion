//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "Unit1.h"
#include "Unit5.h"
#include "decknames.h"
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <random>
#include <time.h>
#include<MMSystem.h>
#include<windows.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm5 *Form5;
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
class Deckdef {
public:
	AnsiString name;
	AnsiString faction;
	std::vector <Carddef> list;
	int mcount;
	int rcount;
	int scount;
	~Deckdef() {
		list.clear();
	}
	void set_info(AnsiString name, AnsiString faction) {
			this->name = name;
			this->faction = faction;
	}

	void add(Carddef a) {
		list.push_back(a);
	}
	void clean() {
        list.clear();
	}
	int size() {
       return(list.size());
	}
	void shuf() {
		for(int i=0;i<list.size();i++) {
			int j = i+ rand()%(list.size()-i);
			std::swap(list[i],list[j]);
        }
    }
};
__fastcall TForm5::TForm5(TComponent* Owner)
	: TForm(Owner)
{
	MyCards=LoadLibraryA("cards.dll");
    if(!MyCards) {
		ShowMessage("cards not found");
		return;
	}
    Background->SendToBack();
	Turn->Visible=false;
	A->Visible=false;
	E->Visible=false;
	AScore->Visible=false;
	EScore->Visible=false;
	AS->Visible=false;
	AR->Visible=false;
	AM->Visible=false;
	ES->Visible=false;
	ER->Visible=false;
	EM->Visible=false;
	Chat->Left=-1000;
	Send->Left=-1000;
    SendL->Left=-1000;
    Msg->Left=-1000;
}
void __fastcall TForm5::FormShow(TObject *Sender)
{
	_di_IXMLmadeType Made = Getmade(Xuser);
    Xuser->Active=true;
	for(int i=0;i<Made->Count;i++) {
		 Decks->Items ->Add (Made->deck[i]->name);
	}
	DConnect->Connected=true;
	Decks->ItemIndex=0;
	AnsiString s ="SELECT * FROM ";
	AnsiString t =(AnsiString)Decks->Text;
	AnsiString i =s+t;
	QDeck->Close();
	QDeck->SQL->Text = i;
	QDeck->ExecSQL();
	QDeck->Open();
	for(int i=0;i<QDeck->RecordCount;i++) {
		Deck->Items->Add();
		Deck->Items->Item[i]->Caption = AnsiString(QDeck->FieldByName("Name") -> AsString).c_str();
		Deck->Items->Item[i]->SubItems->Add(QDeck->FieldByName("Strength") -> AsInteger);
		Deck->Items->Item[i]->SubItems->Add(AnsiString(QDeck->FieldByName("Place") ->AsString).c_str());
		QDeck->Next();
	}
	Leader->Picture->Bitmap->LoadFromResourceID((unsigned)MyCards,Made->deck[Decks->ItemIndex]->leader);
	AnsiString sk = "skin/";
	AnsiString ki = Made->deck[Decks->ItemIndex]->skin;
	AnsiString in =".bmp";
    Skin->Picture->Bitmap->LoadFromFile(sk+ki+in);
}
void __fastcall TForm5::DecksChange(TObject *Sender)
{
	_di_IXMLmadeType Made = Getmade(Xuser);
	Deck->Clear();
	Deck->Show();
	AnsiString s ="SELECT * FROM ";
	AnsiString t =(AnsiString)Decks->Text;
	AnsiString i =s+t;
	QDeck->Close();
	QDeck->SQL->Text = i;
	QDeck->ExecSQL();
	QDeck->Open();
	for(int i=0;i<QDeck->RecordCount;i++) {
		Deck->Items->Add();
		Deck->Items->Item[i]->Caption = AnsiString(QDeck->FieldByName("Name") -> AsString).c_str();
		Deck->Items->Item[i]->SubItems->Add(QDeck->FieldByName("Strength") -> AsInteger);
		Deck->Items->Item[i]->SubItems->Add(AnsiString(QDeck->FieldByName("Place") ->AsString).c_str());
		QDeck->Next();
	}
	Leader->Picture->Bitmap->LoadFromResourceID((unsigned)MyCards,Made->deck[Decks->ItemIndex]->leader);
	AnsiString sk = "skin/";
	AnsiString ki = Made->deck[Decks->ItemIndex]->skin;
	AnsiString in =".bmp";
	Skin->Picture->Bitmap->LoadFromFile(sk+ki+in);
}
void __fastcall TForm5::PReportClick(TObject *Sender)
{
	int mcount=0;
	int scount=0;
	int rcount=0;
    Deckdef temp;
	Deck->Clear();
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
		Deck->Items->Add();
		Deck->Items->Item[i]->Caption = AnsiString(QDeck->FieldByName("Name") -> AsString).c_str();
		Deck->Items->Item[i]->SubItems->Add(QDeck->FieldByName("Strength") -> AsInteger);
		Deck->Items->Item[i]->SubItems->Add(AnsiString(QDeck->FieldByName("Place") ->AsString).c_str());
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
void __fastcall TForm5::StReportClick(TObject *Sender)
{
	int str =0;
    Deckdef temp;
    temp.clean();
	Deck->Clear();
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
		Deck->Items->Add();
		Deck->Items->Item[i]->Caption = AnsiString(QDeck->FieldByName("Name") -> AsString).c_str();
		Deck->Items->Item[i]->SubItems->Add(QDeck->FieldByName("Strength") -> AsInteger);
		Deck->Items->Item[i]->SubItems->Add(AnsiString(QDeck->FieldByName("Place") ->AsString).c_str());
		QDeck->Next();
	}
	AnsiString total;
	total="Total Strength: ";
	ShowMessage(total+str);
	temp.clean();;
}
Deckdef hand;
Deckdef enemy;
Deckdef residue;
int EMs=0;
int ERs=0;
int ESs=0;
int ETScore=0;
int ATScore=0;
int Aend=0;
int Eend=0;
int counter1=0;
int counter2=0;
int counter3=0;
int counter4=0;
int counter5=0;
int counter6=0;
int AW=0;
int EW=0;
int AMs=0;
int ARs=0;
int ASs=0;
int ASpecial=0;
int ESpecial=0;
int ALook=0;
int ELook=0;
int counterS=0;
int Game=0;
void __fastcall TForm5::ServerExecute(TIdContext *AContext)
{
	AnsiString sifra = AContext->Connection->Socket->ReadLn();
	if (sifra=="Setup") {
        PlaySound(TEXT("gwent.wav"), NULL, SND_LOOP | SND_ASYNC);
		residue.clean();
        enemy.clean();
		Carddef tmp;
		Clients->Host = AContext->Connection->Socket->ReadLn();
		ESpecial = AContext->Connection->Socket->ReadInt32();
		ELook=AContext->Connection->Socket->ReadInt32();
		for(int i=0;i<6;i++) {
			tmp.ID=AContext->Connection->Socket->ReadInt32();
			tmp.strength=AContext->Connection->Socket->ReadInt32();
			tmp.position=AContext->Connection->Socket->ReadLn();
            tmp.name=AContext->Connection->Socket->ReadLn();
			enemy.add(tmp);
		}
        Eend=enemy.size();
		_di_IXMLmadeType Made = Getmade(Xuser);
		AnsiString sk = "skin/";
		AnsiString ki = ELook;
		AnsiString in =".bmp";
		ESkin->Picture->Bitmap->LoadFromFile(sk+ki+in);
		ELeader->Picture->Bitmap->LoadFromResourceID((unsigned)MyCards,ESpecial);
		AnsiString s ="SELECT * FROM ";
		AnsiString t =(AnsiString)Decks->Text;
		AnsiString i =s+t;
		QDeck->Close();
		QDeck->SQL->Text = i;
		QDeck->ExecSQL();
		QDeck->Open();
		Deckdef temp;
		for(int i=0;i<QDeck->RecordCount;i++) {
			Carddef t;
			t.name= AnsiString(QDeck->FieldByName("Name") -> AsString).c_str();
			t.ID = QDeck->FieldByName("ID") -> AsInteger;
			t.strength=QDeck->FieldByName("Strength") -> AsInteger;
			t.position=AnsiString(QDeck->FieldByName("Place") ->AsString).c_str();
			temp.add(t);
			srand(time(NULL)+1);
			temp.shuf();
			QDeck->Next();
		}
		for(int i=0;i<6;i++) {
			hand.add(temp.list[i]);
		}
		for(int i=6;i<temp.size();i++) {
            residue.add(temp.list[i]);
		}
		Aend=hand.size();
		temp.clean();
		A->Visible=true;
		E->Visible=true;
		AScore->Visible=true;
		EScore->Visible=true;
		AS->Visible=true;
		AR->Visible=true;
		AM->Visible=true;
		ES->Visible=true;
		ER->Visible=true;
		EM->Visible=true;
		Turn->Visible=true;
		Local->Visible=false;
		LocalL->Visible=false;
        Server1L->Visible=false;
		Server1->Visible=false;
		Server2L->Visible=false;
		Server2->Visible=false;
		Create->Visible=false;
        CreateL->Visible=false;
		StReport->Visible=false;
        StReportL->Visible=false;
		PReport->Visible=false;
        PReportL->Visible=false;
		Skin->Visible=false;
		Deck->Visible=false;
		Decks->Visible=false;
		Leader->Visible=false;
		Chat->Left=24;
		Msg->Left=24;
		Send->Left=288;
		SendL->Left=313;
		Coin->Picture->LoadFromFile("skin/CoinE.png");
		Turn->Caption="Enemy Turn";
		Background->Picture->LoadFromFile("skin/Game.png");
		Background->Visible=true;
		Background->SendToBack();
		Coin->Picture->LoadFromFile("skin/CoinE.png");
		Card1->Visible = true;
		Card1->Picture->Bitmap->LoadFromResourceID((unsigned)MyCards,hand.list[0].ID);
		Card2->Visible = true;
		Card2->Picture->Bitmap->LoadFromResourceID((unsigned)MyCards,hand.list[1].ID);
		Card3->Visible = true;
		Card3->Picture->Bitmap->LoadFromResourceID((unsigned)MyCards,hand.list[2].ID);
		Card4->Visible = true;
		Card4->Picture->Bitmap->LoadFromResourceID((unsigned)MyCards,hand.list[3].ID);
		Card5->Visible = true;
		Card5->Picture->Bitmap->LoadFromResourceID((unsigned)MyCards,hand.list[4].ID);
		Card6->Visible = true;
		Card6->Picture->Bitmap->LoadFromResourceID((unsigned)MyCards,hand.list[5].ID);
		OCard1->Picture=ESkin->Picture;
		OCard1->Visible=true;
		OCard2->Picture=ESkin->Picture;
		OCard2->Visible=true;
		OCard3->Picture=ESkin->Picture;
		OCard3->Visible=true;
		OCard4->Picture=ESkin->Picture;
		OCard4->Visible=true;
		OCard5->Picture=ESkin->Picture;
		OCard5->Visible=true;
		OCard6->Picture=ESkin->Picture;
		Card1->OnClick = NULL;
		Card2->OnClick = NULL;
		Card3->OnClick = NULL;
		Card4->OnClick = NULL;
		Card5->OnClick = NULL;
		Card6->OnClick = NULL;
		AContext->Connection->Disconnect();
		ALeader->Picture->Bitmap->LoadFromResourceID((unsigned)MyCards,Made->deck[Decks->ItemIndex]->leader);
		ASpecial=Made->deck[Decks->ItemIndex]->leader;
		ALook=Made->deck[Decks->ItemIndex]->skin;
		sk = "skin/";
		ki = Made->deck[Decks->ItemIndex]->skin;
		in =".bmp";
		ASkin->Picture->Bitmap->LoadFromFile(sk+ki+in);
		Chat->Items->Add("Both players joined the game! Good luck!");
        Game=1;
		Clients->Connect();
		Clients->Socket->WriteLn("Reply");
		Clients->Socket->Write(ASpecial);
		Clients->Socket->Write(ALook);
		for(int i=0;i<6;i++) {
			Clients->Socket->Write(hand.list[i].ID);
			Clients->Socket->Write(hand.list[i].strength);
			Clients->Socket->WriteLn(hand.list[i].position);
            Clients->Socket->WriteLn(hand.list[i].name);
		};
		Clients->Disconnect();
	}
	else if (sifra=="Reply") {
		Carddef tmp;
		ESpecial = AContext->Connection->Socket->ReadInt32();
		ELook=AContext->Connection->Socket->ReadInt32();
		for(int i=0;i<6;i++) {
			tmp.ID=AContext->Connection->Socket->ReadInt32();
			tmp.strength=AContext->Connection->Socket->ReadInt32();
			tmp.position=AContext->Connection->Socket->ReadLn();
			tmp.name=AContext->Connection->Socket->ReadLn();
			enemy.add(tmp);
		}
        Eend=enemy.size();
		_di_IXMLmadeType Made = Getmade(Xuser);
		AnsiString sk = "skin/";
		AnsiString ki = ELook;
		AnsiString in =".bmp";
		ESkin->Picture->Bitmap->LoadFromFile(sk+ki+in);
		ELeader->Picture->Bitmap->LoadFromResourceID((unsigned)MyCards,ESpecial);
		Card1->Visible = true;
		Card1->Picture->Bitmap->LoadFromResourceID((unsigned)MyCards,hand.list[0].ID);
		Card2->Visible = true;
		Card2->Picture->Bitmap->LoadFromResourceID((unsigned)MyCards,hand.list[1].ID);
		Card3->Visible = true;
		Card3->Picture->Bitmap->LoadFromResourceID((unsigned)MyCards,hand.list[2].ID);
		Card4->Visible = true;
		Card4->Picture->Bitmap->LoadFromResourceID((unsigned)MyCards,hand.list[3].ID);
		Card5->Visible = true;
		Card5->Picture->Bitmap->LoadFromResourceID((unsigned)MyCards,hand.list[4].ID);
		Card6->Visible = true;
		Card6->Picture->Bitmap->LoadFromResourceID((unsigned)MyCards,hand.list[5].ID);
		OCard1->Picture=ESkin->Picture;
		OCard1->Visible=true;
		OCard2->Picture=ESkin->Picture;
		OCard2->Visible=true;
		OCard3->Picture=ESkin->Picture;
		OCard3->Visible=true;
		OCard4->Picture=ESkin->Picture;
		OCard4->Visible=true;
		OCard5->Picture=ESkin->Picture;
		OCard5->Visible=true;
		OCard6->Picture=ESkin->Picture;
		OCard6->Visible=true;
		Background->Picture->LoadFromFile("skin/Game.png");
		Background->SendToBack();
		Background->Visible=true;
        Aend=1;
		Card1->OnClick =Card1Click;
		Card2->OnClick =Card2Click;
		Card3->OnClick =Card3Click;
		Card4->OnClick =Card4Click;
		Card5->OnClick =Card5Click;
		Card6->OnClick =Card6Click;
		Chat->Items->Add("Both players joined the game! Good luck!");
		AContext->Connection->Disconnect();
	}
	else if (sifra=="Chat") {
		Chat->Items->Add(AContext->Connection->Socket->ReadLn());
		AContext->Connection->Disconnect();
	}
	else if (sifra=="EndTurn") {
		 Chat->Items->Add("Opponent passed");
		 Eend=0;
		 Turn->Visible=true;
		 Turn->Caption="Your Turn";
		 Card1->OnClick =Card1Click;
		 Card2->OnClick =Card2Click;
		 Card3->OnClick =Card3Click;
		 Card4->OnClick =Card4Click;
		 Card5->OnClick =Card5Click;
		 Card6->OnClick =Card6Click;
		 Coin->Picture->LoadFromFile("skin/Coin.png");
         AContext->Connection->Disconnect();
	}
	else if (sifra=="Roundover") {
		if(ATScore > ETScore) {
			AW++;
			Chat->Items->Add("You won the round!");
            A->Picture->LoadFromFile("skin/A1.png");
		}
		else if(ETScore>ATScore) {
			EW++;
			Chat->Items->Add("You lost the round!");
            E->Picture->LoadFromFile("skin/E1.png");
		}
		else if(ETScore==ATScore) {
			AW++;
			EW++;
			E->Picture->LoadFromFile("skin/E1.png");
            A->Picture->LoadFromFile("skin/A1.png");
			Chat->Items->Add("Draw round!");
		}
		if(AW==2 && EW!=2) {
        	A->Picture->LoadFromFile("skin/A2.png");
			ShowMessage("You Win!");
			AContext->Connection->Disconnect();
			Application->Terminate();
			Application->ProcessMessages();
		}
		else if(EW==2 && AW!=2) {
            E->Picture->LoadFromFile("skin/E2.png");
			ShowMessage("You Lost!");
			AContext->Connection->Disconnect();
			Application->Terminate();
			Application->ProcessMessages();
		}
		else if(EW==2 && AW==2) {
			A->Picture->LoadFromFile("skin/A2.png");
			E->Picture->LoadFromFile("skin/E2.png");
			ShowMessage("Game tied!");
            AContext->Connection->Disconnect();
			Application->Terminate();
			Application->ProcessMessages();
		}
		else {
			ATScore=0;
			ETScore=0;
			AScore->Caption=ATScore;
			EScore->Caption=ETScore;
			ASs=0;
			AS->Caption=ASs;
			ARs=0;
			AR->Caption=ARs;
			AMs=0;
			AM->Caption=AMs;
			ESs=0;
			ES->Caption=ESs;
			ERs=0;
			ER->Caption=ERs;
			EMs=0;
			EM->Caption=EMs;
			MPlayed1->Picture=NULL;
			MPlayed2->Picture=NULL;
			MPlayed3->Picture=NULL;
			MPlayed4->Picture=NULL;
			MPlayed5->Picture=NULL;
			MPlayed6->Picture=NULL;
			RPlayed1->Picture=NULL;
			RPlayed2->Picture=NULL;
			RPlayed3->Picture=NULL;
			RPlayed4->Picture=NULL;
			RPlayed5->Picture=NULL;
			RPlayed6->Picture=NULL;
			SPlayed1->Picture=NULL;
			SPlayed2->Picture=NULL;
			SPlayed3->Picture=NULL;
			SPlayed4->Picture=NULL;
			SPlayed5->Picture=NULL;
			SPlayed6->Picture=NULL;
			OMPlayed1->Picture=NULL;
			OMPlayed2->Picture=NULL;
			OMPlayed3->Picture=NULL;
			OMPlayed4->Picture=NULL;
			OMPlayed5->Picture=NULL;
			OMPlayed6->Picture=NULL;
			ORPlayed1->Picture=NULL;
			ORPlayed2->Picture=NULL;
			ORPlayed3->Picture=NULL;
			ORPlayed4->Picture=NULL;
			ORPlayed5->Picture=NULL;
			ORPlayed6->Picture=NULL;
			OSPlayed1->Picture=NULL;
			OSPlayed2->Picture=NULL;
			OSPlayed3->Picture=NULL;
			OSPlayed4->Picture=NULL;
			OSPlayed5->Picture=NULL;
			OSPlayed6->Picture=NULL;
			Deckdef help;
			enemy.clean();
			help.clean();
			Eend=AContext->Connection->Socket->ReadInt32();
            Carddef tmp;
			for(int i=0;i<Eend;i++) {
				tmp.ID=AContext->Connection->Socket->ReadInt32();
				tmp.strength=AContext->Connection->Socket->ReadInt32();
				tmp.position=AContext->Connection->Socket->ReadLn();
                tmp.name=AContext->Connection->Socket->ReadLn();
				enemy.add(tmp);
			}
			if(counter1==0) {
				help.add(hand.list[0]);
			}
			if(counter2==0) {
				help.add(hand.list[1]);
			}
			if(counter3==0) {
				help.add(hand.list[2]);
			}
			if(counter4==0) {
				help.add(hand.list[3]);
			}
			if(counter5==0) {
				help.add(hand.list[4]);
			}
			if(counter6==0) {
				help.add(hand.list[5]);
			}
			for(int i=0;i<3;i++) {
				if(help.size()<6) {
					help.add(residue.list[i]);
				}
				else {
					Chat->Items->Add(help.list[i].name + " was destroyed due to full hand!");
				}
			}
			residue.list.erase(residue.list.begin()+0);
			residue.list.erase(residue.list.begin()+1);
			residue.list.erase(residue.list.begin()+2);
			hand.clean();
			for(int i=0;i<help.size();i++) {
				hand.add(help.list[i]);
			}
			Aend=hand.size();
			if(Aend<=6) {
				if(Aend==1) {
					Card1->Picture->Bitmap->LoadFromResourceID((unsigned)MyCards,hand.list[0].ID);
					counter1=0;
				}
				else if(Aend==2) {
					Card1->Picture->Bitmap->LoadFromResourceID((unsigned)MyCards,hand.list[0].ID);
					Card2->Picture->Bitmap->LoadFromResourceID((unsigned)MyCards,hand.list[1].ID);
					counter1=0;
					counter2=0;
				}
				else if(Aend==3) {
					Card1->Picture->Bitmap->LoadFromResourceID((unsigned)MyCards,hand.list[0].ID);
					Card2->Picture->Bitmap->LoadFromResourceID((unsigned)MyCards,hand.list[1].ID);
					Card3->Picture->Bitmap->LoadFromResourceID((unsigned)MyCards,hand.list[2].ID);
					counter1=0;
					counter2=0;
					counter3=0;
				}
				else if(Aend==4) {
					Card1->Picture->Bitmap->LoadFromResourceID((unsigned)MyCards,hand.list[0].ID);
					Card2->Picture->Bitmap->LoadFromResourceID((unsigned)MyCards,hand.list[1].ID);
					Card3->Picture->Bitmap->LoadFromResourceID((unsigned)MyCards,hand.list[2].ID);
					Card4->Picture->Bitmap->LoadFromResourceID((unsigned)MyCards,hand.list[3].ID);
					counter1=0;
					counter2=0;
					counter3=0;
					counter4=0;
				}
				else if(Aend==5) {
					Card1->Picture->Bitmap->LoadFromResourceID((unsigned)MyCards,hand.list[0].ID);
					Card2->Picture->Bitmap->LoadFromResourceID((unsigned)MyCards,hand.list[1].ID);
					Card3->Picture->Bitmap->LoadFromResourceID((unsigned)MyCards,hand.list[2].ID);
					Card4->Picture->Bitmap->LoadFromResourceID((unsigned)MyCards,hand.list[3].ID);
					Card5->Picture->Bitmap->LoadFromResourceID((unsigned)MyCards,hand.list[4].ID);
					counter1=0;
					counter2=0;
					counter3=0;
					counter4=0;
					counter5=0;
				}
				else if(Aend==6) {
					Card1->Picture->Bitmap->LoadFromResourceID((unsigned)MyCards,hand.list[0].ID);
					Card2->Picture->Bitmap->LoadFromResourceID((unsigned)MyCards,hand.list[1].ID);
					Card3->Picture->Bitmap->LoadFromResourceID((unsigned)MyCards,hand.list[2].ID);
					Card4->Picture->Bitmap->LoadFromResourceID((unsigned)MyCards,hand.list[3].ID);
					Card5->Picture->Bitmap->LoadFromResourceID((unsigned)MyCards,hand.list[4].ID);
					Card6->Picture->Bitmap->LoadFromResourceID((unsigned)MyCards,hand.list[5].ID);
					counter1=0;
					counter2=0;
					counter3=0;
					counter4=0;
					counter5=0;
					counter6=0;
				}
			}
			if(Eend<=6) {
				if(Eend==1) {
					OCard1->Picture=ESkin->Picture;
                    OCard1->Visible=true;
				}
				else if(Eend==2) {
					OCard1->Picture=ESkin->Picture;
					OCard1->Visible=true;
					OCard2->Picture=ESkin->Picture;
                    OCard2->Visible=true;
				}
				else if(Eend==3) {
					OCard1->Picture=ESkin->Picture;
					OCard1->Visible=true;
					OCard2->Picture=ESkin->Picture;
					OCard2->Visible=true;
					OCard3->Picture=ESkin->Picture;
                    OCard3->Visible=true;
				}
				else if(Eend==4) {
					OCard1->Picture=ESkin->Picture;
					OCard1->Visible=true;
					OCard2->Picture=ESkin->Picture;
					OCard2->Visible=true;
					OCard3->Picture=ESkin->Picture;
                    OCard3->Visible=true;
					OCard4->Picture=ESkin->Picture;
                    OCard4->Visible=true;
				}
				else if(Eend==5) {
					OCard1->Picture=ESkin->Picture;
					OCard1->Visible=true;
					OCard2->Picture=ESkin->Picture;
					OCard2->Visible=true;
					OCard3->Picture=ESkin->Picture;
					OCard3->Visible=true;
					OCard4->Picture=ESkin->Picture;
					OCard4->Visible=true;
					OCard5->Picture=ESkin->Picture;
					OCard5->Visible=true;
				}
				else if(Eend==6) {
					OCard1->Picture=ESkin->Picture;
					OCard1->Visible=true;
					OCard2->Picture=ESkin->Picture;
					OCard2->Visible=true;
					OCard3->Picture=ESkin->Picture;
					OCard3->Visible=true;
					OCard4->Picture=ESkin->Picture;
					OCard4->Visible=true;
					OCard5->Picture=ESkin->Picture;
					OCard5->Visible=true;
					OCard6->Picture=ESkin->Picture;
					OCard6->Visible=true;
				}
			}
			Card1->OnClick=NULL;
			Card2->OnClick=NULL;
			Card3->OnClick=NULL;
			Card4->OnClick=NULL;
			Card5->OnClick=NULL;
			Card6->OnClick=NULL;
            Turn->Visible=true;
			Turn->Caption="Enemy turn";
			Coin->Picture->LoadFromFile("skin/CoinE.png");
			Clients->Connect();
			Clients->Socket->WriteLn("Roundoverreply");
			Clients->Socket->Write(Aend);
			for(int i=0;i<Aend;i++) {
				Clients->Socket->Write(hand.list[i].ID);
				Clients->Socket->Write(hand.list[i].strength);
				Clients->Socket->WriteLn(hand.list[i].position);
                Clients->Socket->WriteLn(hand.list[i].name);
			}
        }
	}
	else if(sifra=="Roundoverreply") {
		enemy.clean();
        Carddef tmp;
		Eend=AContext->Connection->Socket->ReadInt32();
		for(int i=0;i<Eend;i++) {
			tmp.ID=AContext->Connection->Socket->ReadInt32();
			tmp.strength=AContext->Connection->Socket->ReadInt32();
			tmp.position=AContext->Connection->Socket->ReadLn();
            tmp.name=AContext->Connection->Socket->ReadLn();
			enemy.add(tmp);
		}
		Turn->Visible=true;
		Turn->Caption="Your Turn";
		Coin->Picture->LoadFromFile("skin/Coin.png");
		if(Aend<=6) {
			if(Aend==1) {
				Card1->Picture->Bitmap->LoadFromResourceID((unsigned)MyCards,hand.list[0].ID);
				Card1->OnClick = Card1Click;
                counter1=0;
			}
			else if(Aend==2) {
				Card1->Picture->Bitmap->LoadFromResourceID((unsigned)MyCards,hand.list[0].ID);
				Card2->Picture->Bitmap->LoadFromResourceID((unsigned)MyCards,hand.list[1].ID);
				Card1->OnClick = Card1Click;
				Card2->OnClick = Card2Click;
                counter1=0;
				counter2=0;
			}
			else if(Aend==3) {
				Card1->Picture->Bitmap->LoadFromResourceID((unsigned)MyCards,hand.list[0].ID);
				Card2->Picture->Bitmap->LoadFromResourceID((unsigned)MyCards,hand.list[1].ID);
				Card3->Picture->Bitmap->LoadFromResourceID((unsigned)MyCards,hand.list[2].ID);
				Card1->OnClick = Card1Click;
				Card2->OnClick = Card2Click;
				Card3->OnClick = Card3Click;
                counter1=0;
				counter2=0;
				counter3=0;
			}
			else if(Aend==4) {
				Card1->Picture->Bitmap->LoadFromResourceID((unsigned)MyCards,hand.list[0].ID);
				Card2->Picture->Bitmap->LoadFromResourceID((unsigned)MyCards,hand.list[1].ID);
				Card3->Picture->Bitmap->LoadFromResourceID((unsigned)MyCards,hand.list[2].ID);
				Card4->Picture->Bitmap->LoadFromResourceID((unsigned)MyCards,hand.list[3].ID);
				Card1->OnClick = Card1Click;
				Card2->OnClick = Card2Click;
				Card3->OnClick = Card3Click;
				Card4->OnClick = Card4Click;
                counter1=0;
				counter2=0;
				counter3=0;
				counter4=0;
			}
			else if(Aend==5) {
				Card1->Picture->Bitmap->LoadFromResourceID((unsigned)MyCards,hand.list[0].ID);
				Card2->Picture->Bitmap->LoadFromResourceID((unsigned)MyCards,hand.list[1].ID);
				Card3->Picture->Bitmap->LoadFromResourceID((unsigned)MyCards,hand.list[2].ID);
				Card4->Picture->Bitmap->LoadFromResourceID((unsigned)MyCards,hand.list[3].ID);
				Card5->Picture->Bitmap->LoadFromResourceID((unsigned)MyCards,hand.list[4].ID);
				Card1->OnClick = Card1Click;
				Card2->OnClick = Card2Click;
				Card3->OnClick = Card3Click;
				Card4->OnClick = Card4Click;
				Card5->OnClick = Card5Click;
                counter1=0;
				counter2=0;
				counter3=0;
				counter4=0;
				counter5=0;
			}
			else if(Aend==6) {
				Card1->Picture->Bitmap->LoadFromResourceID((unsigned)MyCards,hand.list[0].ID);
				Card2->Picture->Bitmap->LoadFromResourceID((unsigned)MyCards,hand.list[1].ID);
				Card3->Picture->Bitmap->LoadFromResourceID((unsigned)MyCards,hand.list[2].ID);
				Card4->Picture->Bitmap->LoadFromResourceID((unsigned)MyCards,hand.list[3].ID);
				Card5->Picture->Bitmap->LoadFromResourceID((unsigned)MyCards,hand.list[4].ID);
				Card6->Picture->Bitmap->LoadFromResourceID((unsigned)MyCards,hand.list[5].ID);
				Card1->OnClick = Card1Click;
				Card2->OnClick = Card2Click;
				Card3->OnClick = Card3Click;
				Card4->OnClick = Card4Click;
				Card5->OnClick = Card5Click;
				Card6->OnClick = Card6Click;
				counter1=0;
				counter2=0;
				counter3=0;
				counter4=0;
				counter5=0;
				counter6=0;
			}
        }
		if(Eend<=6) {
			if(Eend==1) {
				OCard1->Picture=ESkin->Picture;
				OCard1->Visible=true;
			}
			else if(Eend==2) {
				OCard1->Picture=ESkin->Picture;
				OCard1->Visible=true;
				OCard2->Picture=ESkin->Picture;
				OCard2->Visible=true;
			}
			else if(Eend==3) {
				OCard1->Picture=ESkin->Picture;
				OCard1->Visible=true;
				OCard2->Picture=ESkin->Picture;
				OCard2->Visible=true;
				OCard3->Picture=ESkin->Picture;
				OCard3->Visible=true;
			}
			else if(Eend==4) {
				OCard1->Picture=ESkin->Picture;
				OCard1->Visible=true;
				OCard2->Picture=ESkin->Picture;
				OCard2->Visible=true;
				OCard3->Picture=ESkin->Picture;
				OCard3->Visible=true;
				OCard4->Picture=ESkin->Picture;
				OCard4->Visible=true;
			}
			else if(Eend==5) {
				OCard1->Picture=ESkin->Picture;
				OCard1->Visible=true;
				OCard2->Picture=ESkin->Picture;
				OCard2->Visible=true;
				OCard3->Picture=ESkin->Picture;
				OCard3->Visible=true;
				OCard4->Picture=ESkin->Picture;
				OCard4->Visible=true;
				OCard5->Picture=ESkin->Picture;
				OCard5->Visible=true;
			}
			else if(Eend==6) {
				OCard1->Picture=ESkin->Picture;
				OCard1->Visible=true;
				OCard2->Picture=ESkin->Picture;
				OCard2->Visible=true;
				OCard3->Picture=ESkin->Picture;
				OCard3->Visible=true;
				OCard4->Picture=ESkin->Picture;
				OCard4->Visible=true;
				OCard5->Picture=ESkin->Picture;
				OCard5->Visible=true;
				OCard6->Picture=ESkin->Picture;
				OCard6->Visible=true;
			}
		}
        AContext->Connection->Disconnect();
	}
	else if(sifra=="Leader") {
        int who = AContext->Connection->Socket->ReadInt32();
        if(who==46) {
			Chat->Items->Add("Your opponent used Foltest leader ability!");
			ETScore=ETScore-ESs;
			ESs=ESs*2;
			ES->Caption=ESs;
			ETScore=ETScore+ESs;
			EScore->Caption=ETScore;
			if(ATScore>ETScore) {
				AScore->Font->Color=RGB(204,172,0);
				EScore->Font->Color=clSilver;
			}
			else if(ATScore<ETScore) {
				EScore->Font->Color=RGB(204,172,0);
				AScore->Font->Color=clSilver;
			}
			else if(ATScore==ETScore) {
				AScore->Font->Color=clSilver;
				EScore->Font->Color=clSilver;
			}
		}
		else if(who==47) {
			Chat->Items->Add("Your opponent used Lady of the Lake leader ability!");
			ETScore=ETScore-ERs;
			ERs=ERs*2;
			ER->Caption=ARs;
			ETScore=ETScore+ERs;
			EScore->Caption=ETScore;
			if(ATScore>ETScore) {
				AScore->Font->Color=RGB(204,172,0);
				EScore->Font->Color=clSilver;
			}
			else if(ATScore<ETScore) {
				EScore->Font->Color=RGB(204,172,0);
				AScore->Font->Color=clSilver;
			}
			else if(ATScore==ETScore) {
				AScore->Font->Color=clSilver;
				EScore->Font->Color=clSilver;
			}
		}
		else if(who==48) {
			Chat->Items->Add("Your opponent used Eredin leader ability!");
			ATScore=ATScore-AMs;
			AMs=AMs/2;
			AM->Caption=AMs;
			ATScore=ATScore+AMs;
			AScore->Caption=ATScore;
			if(ATScore>ETScore) {
				AScore->Font->Color=RGB(204,172,0);
				EScore->Font->Color=clSilver;
			}
			else if(ATScore<ETScore) {
				EScore->Font->Color=RGB(204,172,0);
				AScore->Font->Color=clSilver;
			}
			else if(ATScore==ETScore) {
				AScore->Font->Color=clSilver;
				EScore->Font->Color=clSilver;
			}
		}
		else if(who==49) {
			Chat->Items->Add("Your opponent used Emyhr leader ability!");
		}
        AContext->Connection->Disconnect();
    }
	else if (sifra=="Card1") {
        Eend--;
		if(enemy.list[0].position=="Melee") {
			OMPlayed1->Picture->Bitmap->LoadFromResourceID((unsigned)MyCards,enemy.list[0].ID);
			EMs+=enemy.list[0].strength;
			EM->Caption=EMs;
		}
		else if(enemy.list[0].position=="Ranged") {
			ORPlayed1->Picture->Bitmap->LoadFromResourceID((unsigned)MyCards,enemy.list[0].ID);
			ERs+=enemy.list[0].strength;
			ER->Caption=ERs;
		}
		else {
			OSPlayed1->Picture->Bitmap->LoadFromResourceID((unsigned)MyCards,enemy.list[0].ID);
			ESs+=enemy.list[0].strength;
			ES->Caption=ESs;
		}
		OCard1->Picture=NULL;
		ETScore+=enemy.list[0].strength;
		EScore->Caption=ETScore;
		if(ATScore>ETScore) {
			AScore->Font->Color=RGB(204,172,0);
			EScore->Font->Color=clSilver;
		}
		else if(ATScore<ETScore) {
			EScore->Font->Color=RGB(204,172,0);
			AScore->Font->Color=clSilver;
		}
		else if(ATScore==ETScore) {
			AScore->Font->Color=clSilver;
			EScore->Font->Color=clSilver;
		}
        Turn->Visible=true;
		Turn->Caption="Your Turn";
		if(Aend==0) {
			Card1->OnClick =NULL;
			Card2->OnClick =NULL;
			Card3->OnClick =NULL;
			Card4->OnClick =NULL;
			Card5->OnClick =NULL;
			Card6->OnClick =NULL;

            Coin->Picture->LoadFromFile("skin/CoinE.png");
			Turn->Caption="Enemy Turn";
		}
		else{
			Card1->OnClick =Card1Click;
			Card2->OnClick =Card2Click;
			Card3->OnClick =Card3Click;
			Card4->OnClick =Card4Click;
			Card5->OnClick =Card5Click;
			Card6->OnClick =Card6Click;
			Coin->Picture->LoadFromFile("skin/Coin.png");
        }
	}
	else if (sifra=="Card2") {
    	Eend--;
		if(enemy.list[1].position=="Melee") {
			OMPlayed2->Picture->Bitmap->LoadFromResourceID((unsigned)MyCards,enemy.list[1].ID);
			EMs+=enemy.list[1].strength;
			EM->Caption=EMs;
		}
		else if(enemy.list[1].position=="Ranged") {
			ORPlayed2->Picture->Bitmap->LoadFromResourceID((unsigned)MyCards,enemy.list[1].ID);
			ERs+=enemy.list[1].strength;
			ER->Caption=ERs;
		}
		else {
			OSPlayed2->Picture->Bitmap->LoadFromResourceID((unsigned)MyCards,enemy.list[1].ID);
			ESs+=enemy.list[1].strength;
			ES->Caption=ESs;
		}
        OCard2->Picture=NULL;
		ETScore+=enemy.list[1].strength;
		EScore->Caption=ETScore;
		if(ATScore>ETScore) {
			AScore->Font->Color=RGB(204,172,0);
            EScore->Font->Color=clSilver;
		}
		else if(ATScore<ETScore) {
			EScore->Font->Color=RGB(204,172,0);
			AScore->Font->Color=clSilver;
		}
        else if(ATScore==ETScore) {
			AScore->Font->Color=clSilver;
			EScore->Font->Color=clSilver;
		}
        Turn->Visible=true;
		Turn->Caption="Your Turn";
		if(Aend==0) {
			Card1->OnClick =NULL;
			Card2->OnClick =NULL;
			Card3->OnClick =NULL;
			Card4->OnClick =NULL;
			Card5->OnClick =NULL;
			Card6->OnClick =NULL;
            Coin->Picture->LoadFromFile("skin/CoinE.png");
			Turn->Caption="Enemy Turn";
		}
		else{
			Card1->OnClick =Card1Click;
			Card2->OnClick =Card2Click;
			Card3->OnClick =Card3Click;
			Card4->OnClick =Card4Click;
			Card5->OnClick =Card5Click;
			Card6->OnClick =Card6Click;
			Coin->Picture->LoadFromFile("skin/Coin.png");
        }
	}
	else if (sifra=="Card3") {
        Eend--;
		if(enemy.list[2].position=="Melee") {
			OMPlayed3->Picture->Bitmap->LoadFromResourceID((unsigned)MyCards,enemy.list[2].ID);
			EMs+=enemy.list[2].strength;
			EM->Caption=EMs;
		}
		else if(enemy.list[2].position=="Ranged") {
			ORPlayed3->Picture->Bitmap->LoadFromResourceID((unsigned)MyCards,enemy.list[2].ID);
			ERs+=enemy.list[2].strength;
			ER->Caption=ERs;
		}
		else {
			OSPlayed3->Picture->Bitmap->LoadFromResourceID((unsigned)MyCards,enemy.list[2].ID);
			ESs+=enemy.list[2].strength;
			ES->Caption=ESs;
		}
		OCard3->Picture=NULL;
		ETScore+=enemy.list[2].strength;
		EScore->Caption=ETScore;
		if(ATScore>ETScore) {
			AScore->Font->Color=RGB(204,172,0);
            EScore->Font->Color=clSilver;
		}
		else if(ATScore<ETScore) {
			EScore->Font->Color=RGB(204,172,0);
			AScore->Font->Color=clSilver;
		}
        else if(ATScore==ETScore) {
			AScore->Font->Color=clSilver;
			EScore->Font->Color=clSilver;
		}
        Turn->Visible=true;
		Turn->Caption="Your Turn";
		if(Aend==0) {
			Card1->OnClick =NULL;
			Card2->OnClick =NULL;
			Card3->OnClick =NULL;
			Card4->OnClick =NULL;
			Card5->OnClick =NULL;
			Card6->OnClick =NULL;
			Coin->Picture->LoadFromFile("skin/CoinE.png");
			Turn->Caption="Enemy Turn";
		}
		else{
			Card1->OnClick =Card1Click;
			Card2->OnClick =Card2Click;
			Card3->OnClick =Card3Click;
			Card4->OnClick =Card4Click;
			Card5->OnClick =Card5Click;
			Card6->OnClick =Card6Click;
			Coin->Picture->LoadFromFile("skin/Coin.png");
		}
	}
	else if (sifra=="Card4") {
        Eend--;
		if(enemy.list[3].position=="Melee") {
			OMPlayed4->Picture->Bitmap->LoadFromResourceID((unsigned)MyCards,enemy.list[3].ID);
			EMs+=enemy.list[3].strength;
			EM->Caption=EMs;
		}
		else if(enemy.list[3].position=="Ranged") {
			ORPlayed4->Picture->Bitmap->LoadFromResourceID((unsigned)MyCards,enemy.list[3].ID);
			ERs+=enemy.list[3].strength;
			ER->Caption=ERs;
		}
		else {
			OSPlayed4->Picture->Bitmap->LoadFromResourceID((unsigned)MyCards,enemy.list[3].ID);
			ESs+=enemy.list[3].strength;
			ES->Caption=ESs;
		}
		OCard4->Picture=NULL;
		ETScore+=enemy.list[3].strength;
		EScore->Caption=ETScore;
		if(ATScore>ETScore) {
			AScore->Font->Color=RGB(204,172,0);
            EScore->Font->Color=clSilver;
		}
		else if(ATScore<ETScore) {
			EScore->Font->Color=RGB(204,172,0);
			AScore->Font->Color=clSilver;
		}
        else if(ATScore==ETScore) {
			AScore->Font->Color=clSilver;
			EScore->Font->Color=clSilver;
		}
        Turn->Visible=true;
		Turn->Caption="Your Turn";
		if(Aend==0) {
			Card1->OnClick =NULL;
			Card2->OnClick =NULL;
			Card3->OnClick =NULL;
			Card4->OnClick =NULL;
			Card5->OnClick =NULL;
			Card6->OnClick =NULL;
            Coin->Picture->LoadFromFile("skin/CoinE.png");
			Turn->Caption="Enemy Turn";
		}
		else{
			Card1->OnClick =Card1Click;
			Card2->OnClick =Card2Click;
			Card3->OnClick =Card3Click;
			Card4->OnClick =Card4Click;
			Card5->OnClick =Card5Click;
			Card6->OnClick =Card6Click;
			Coin->Picture->LoadFromFile("skin/Coin.png");
		}
	}
	else if (sifra=="Card5") {
        Eend--;
		if(enemy.list[4].position=="Melee") {
			OMPlayed5->Picture->Bitmap->LoadFromResourceID((unsigned)MyCards,enemy.list[4].ID);
			EMs+=enemy.list[4].strength;
			EM->Caption=EMs;
		}
		else if(enemy.list[4].position=="Ranged") {
			ORPlayed5->Picture->Bitmap->LoadFromResourceID((unsigned)MyCards,enemy.list[4].ID);
			ERs+=enemy.list[4].strength;
			ER->Caption=ERs;
		}
		else {
			OSPlayed5->Picture->Bitmap->LoadFromResourceID((unsigned)MyCards,enemy.list[4].ID);
			ESs+=enemy.list[4].strength;
			ES->Caption=ESs;
		}
		OCard5->Picture=NULL;
		ETScore+=enemy.list[4].strength;
		EScore->Caption=ETScore;
		if(ATScore>ETScore) {
			AScore->Font->Color=RGB(204,172,0);
            EScore->Font->Color=clSilver;
		}
		else if(ATScore<ETScore) {
			EScore->Font->Color=RGB(204,172,0);
			AScore->Font->Color=clSilver;
		}
        else if(ATScore==ETScore) {
			AScore->Font->Color=clSilver;
			EScore->Font->Color=clSilver;
		}
        Turn->Visible=true;
		Turn->Caption="Your Turn";
		if(Aend==0) {
			Card1->OnClick =NULL;
			Card2->OnClick =NULL;
			Card3->OnClick =NULL;
			Card4->OnClick =NULL;
			Card5->OnClick =NULL;
			Card6->OnClick =NULL;
			Coin->Picture->LoadFromFile("skin/CoinE.png");
			Turn->Caption="Enemy Turn";
		}
		else{
			Card1->OnClick =Card1Click;
			Card2->OnClick =Card2Click;
			Card3->OnClick =Card3Click;
			Card4->OnClick =Card4Click;
			Card5->OnClick =Card5Click;
			Card6->OnClick =Card6Click;
			Coin->Picture->LoadFromFile("skin/Coin.png");
		}
	}
	else if (sifra=="Card6") {
        Eend--;
		if(enemy.list[5].position=="Melee") {
			OMPlayed6->Picture->Bitmap->LoadFromResourceID((unsigned)MyCards,enemy.list[5].ID);
			EMs+=enemy.list[5].strength;
			EM->Caption=EMs;
		}
		else if(enemy.list[5].position=="Ranged") {
			ORPlayed6->Picture->Bitmap->LoadFromResourceID((unsigned)MyCards,enemy.list[5].ID);
			ERs+=enemy.list[5].strength;
			ER->Caption=ERs;
		}
		else {
			OSPlayed6->Picture->Bitmap->LoadFromResourceID((unsigned)MyCards,enemy.list[5].ID);
			ESs+=enemy.list[5].strength;
			ES->Caption=ESs;
		}
        OCard6->Picture=NULL;
		ETScore+=enemy.list[5].strength;
		EScore->Caption=ETScore;
		if(ATScore>ETScore) {
			AScore->Font->Color=RGB(204,172,0);
            EScore->Font->Color=clSilver;
		}
		else if(ATScore<ETScore) {
			EScore->Font->Color=RGB(204,172,0);
			AScore->Font->Color=clSilver;
		}
        else if(ATScore==ETScore) {
			AScore->Font->Color=clSilver;
			EScore->Font->Color=clSilver;
		}
        Turn->Visible=true;
		Turn->Caption="Your Turn";
		if(Aend==0) {
			Card1->OnClick =NULL;
			Card2->OnClick =NULL;
			Card3->OnClick =NULL;
			Card4->OnClick =NULL;
			Card5->OnClick =NULL;
			Card6->OnClick =NULL;
			Coin->Picture->LoadFromFile("skin/CoinE.png");
			Turn->Caption="Enemy Turn";
		}
		else{
			Card1->OnClick =Card1Click;
			Card2->OnClick =Card2Click;
			Card3->OnClick =Card3Click;
			Card4->OnClick =Card4Click;
			Card5->OnClick =Card5Click;
			Card6->OnClick =Card6Click;
			Coin->Picture->LoadFromFile("skin/Coin.png");
		}
	}
}
void __fastcall TForm5::EndTurnClick(TObject *Sender)
{
	Aend=0;
	Chat->Items->Add("You've passed");
	if(Aend==0 && Eend==0) {
		Deckdef help;
		help.clean();
        Clients->Connect();
		Clients->Socket->WriteLn("Roundover");
		if(ATScore > ETScore) {
			AW++;
			Chat->Items->Add("You won the round!");
            A->Picture->LoadFromFile("skin/A1.png");
		}
		else if(ETScore>ATScore) {
			EW++;
			Chat->Items->Add("You lost the round!");
			E->Picture->LoadFromFile("skin/E1.png");
		}
		else if(ETScore==ATScore) {
			AW++;
			EW++;
			A->Picture->LoadFromFile("skin/A1.png");
			E->Picture->LoadFromFile("skin/E1.png");
			Chat->Items->Add("Draw round!");
		}
		if(AW==2 && EW!=2) {
            A->Picture->LoadFromFile("skin/A2.png");
			ShowMessage("You Won the game!");
			Application->Terminate();
		}
		else if(EW==2 && AW!=2) {
            E->Picture->LoadFromFile("skin/E2.png");
			ShowMessage("You Lost the game!");
			Application->Terminate();
		}
		else if(EW==2 && AW==2) {
			A->Picture->LoadFromFile("skin/A2.png");
            E->Picture->LoadFromFile("skin/E2.png");
			ShowMessage("Game tied!");
			Application->Terminate();
		}
		if(counter1==0) {
			help.add(hand.list[0]);
		}
		if(counter2==0) {
			help.add(hand.list[1]);
		}
		if(counter3==0) {
			help.add(hand.list[2]);
		}
		if(counter4==0) {
			help.add(hand.list[3]);
		}
		if(counter5==0) {
			help.add(hand.list[4]);
		}
		if(counter6==0) {
			help.add(hand.list[5]);
		}
		for(int i=0;i<3;i++) {
			help.add(residue.list[i]);
		}
		hand.clean();
		for(int i=0;i<help.size();i++) {
			if(hand.size()<6) {
				hand.add(help.list[i]);
			}
			else {
                Chat->Items->Add(help.list[i].name+" was destroyed due to full hand");
            }
		}
		residue.list.erase(residue.list.begin()+0);
		residue.list.erase(residue.list.begin()+1);
		residue.list.erase(residue.list.begin()+2);
		Aend =hand.size();
		Clients->Socket->Write(Aend);
		for(int i=0;i<Aend;i++) {
			Clients->Socket->Write(hand.list[i].ID);
			Clients->Socket->Write(hand.list[i].strength);
			Clients->Socket->WriteLn(hand.list[i].position);
            Clients->Socket->WriteLn(hand.list[i].name);
		}
		Clients->Disconnect();
		Card1->OnClick = NULL;
		Card2->OnClick = NULL;
		Card3->OnClick = NULL;
		Card4->OnClick = NULL;
		Card5->OnClick = NULL;
		Card6->OnClick = NULL;
		ATScore=0;
		ETScore=0;
		AScore->Caption=ATScore;
		EScore->Caption=ETScore;
		ASs=0;
		AS->Caption=ASs;
		ARs=0;
		AR->Caption=ARs;
		AMs=0;
		AM->Caption=AMs;
		ESs=0;
		ES->Caption=ESs;
		ERs=0;
		ER->Caption=ERs;
		EMs=0;
		EM->Caption=EMs;
		MPlayed1->Picture=NULL;
		MPlayed2->Picture=NULL;
		MPlayed3->Picture=NULL;
		MPlayed4->Picture=NULL;
		MPlayed5->Picture=NULL;
		MPlayed6->Picture=NULL;
		RPlayed1->Picture=NULL;
		RPlayed2->Picture=NULL;
		RPlayed3->Picture=NULL;
		RPlayed4->Picture=NULL;
		RPlayed5->Picture=NULL;
		RPlayed6->Picture=NULL;
		SPlayed1->Picture=NULL;
		SPlayed2->Picture=NULL;
		SPlayed3->Picture=NULL;
		SPlayed4->Picture=NULL;
		SPlayed5->Picture=NULL;
		SPlayed6->Picture=NULL;
		OMPlayed1->Picture=NULL;
		OMPlayed2->Picture=NULL;
		OMPlayed3->Picture=NULL;
		OMPlayed4->Picture=NULL;
		OMPlayed5->Picture=NULL;
		OMPlayed6->Picture=NULL;
		ORPlayed1->Picture=NULL;
		ORPlayed2->Picture=NULL;
		ORPlayed3->Picture=NULL;
		ORPlayed4->Picture=NULL;
		ORPlayed5->Picture=NULL;
		ORPlayed6->Picture=NULL;
		OSPlayed1->Picture=NULL;
		OSPlayed2->Picture=NULL;
		OSPlayed3->Picture=NULL;
		OSPlayed4->Picture=NULL;
		OSPlayed5->Picture=NULL;
		OSPlayed6->Picture=NULL;
	}
	else {
		Card1->OnClick=NULL;
		Card2->OnClick=NULL;
		Card3->OnClick=NULL;
		Card4->OnClick=NULL;
		Card5->OnClick=NULL;
		Card6->OnClick=NULL;;

        Coin->Picture->LoadFromFile("skin/CoinE.png");
		Turn->Caption="Enemy Turn";
		Clients->Connect();
		Clients->Socket->WriteLn("EndTurn");
		Clients->Disconnect();
	}
}
void __fastcall TForm5::SendClick(TObject *Sender)
{
	Clients ->Connect();
	Clients ->Socket->WriteLn("Chat");
	Clients ->Socket->WriteLn(Msg->Text);
	Chat->Items->Add(Msg->Text);
	Clients->Disconnect();
	Msg->Clear();
}
void __fastcall TForm5::Card1Click(TObject *Sender)
{
	if (counter1==0) {
		if(Aend==0) {
			Card1->OnClick =NULL;
			Card2->OnClick =NULL;
			Card3->OnClick =NULL;
			Card4->OnClick =NULL;
			Card5->OnClick =NULL;
			Card6->OnClick = NULL;
		}
		else {
			counter1++;
			Clients ->Connect();
			Clients ->Socket->WriteLn("Card1");
			Clients->Disconnect();
			if(hand.list[0].position =="Melee") {
				MPlayed1->Picture=Card1->Picture;
				AMs+=hand.list[0].strength;
				AM->Caption=AMs;
			}
			else if(hand.list[0].position =="Ranged") {
				RPlayed1->Picture=Card1->Picture;
				ARs+=hand.list[0].strength;
				AR->Caption=ARs;
			}
			else {
				SPlayed1->Picture=Card1->Picture;
				ASs+=hand.list[0].strength;
				AS->Caption=ASs;
			}
			ATScore+=hand.list[0].strength;
			AScore->Caption=ATScore;
			if(ATScore>ETScore) {
				AScore->Font->Color=RGB(204,172,0);
				EScore->Font->Color=clSilver;
			}
			else if(ATScore<ETScore) {
				EScore->Font->Color=RGB(204,172,0);
				AScore->Font->Color=clSilver;
			}
			else if(ATScore==ETScore) {
				AScore->Font->Color=clSilver;
                EScore->Font->Color=clSilver;
			}
			Card1->Picture=NULL;
			if(Eend==0) {
				Turn->Visible=true;
				Turn->Caption="Your Turn";
				Coin->Picture->LoadFromFile("skin/Coin.png");
				Card1->OnClick=NULL;
				Card2->OnClick=Card2Click;
				Card3->OnClick=Card3Click;
				Card4->OnClick=Card4Click;
				Card5->OnClick=Card5Click;
				Card6->OnClick=Card6Click;
			}
			else {
				Card1->OnClick =NULL;
				Card2->OnClick =NULL;
				Card3->OnClick =NULL;
				Card4->OnClick =NULL;
				Card5->OnClick =NULL;
				Card6->OnClick =NULL;
                Coin->Picture->LoadFromFile("skin/CoinE.png");
				Turn->Caption="Enemy Turn";
			}
		}
	}
	else {
		Card1->OnClick=NULL;
	}
}
void __fastcall TForm5::Card2Click(TObject *Sender)
{
	if (counter2==0) {
		if(Aend==0) {
			Card1->OnClick =NULL;
			Card2->OnClick =NULL;
			Card3->OnClick =NULL;
			Card4->OnClick =NULL;
			Card5->OnClick =NULL;
			Card6->OnClick = NULL;
		}
		else {
			counter2++;
			Clients ->Connect();
			Clients ->Socket->WriteLn("Card2");
			Clients->Disconnect();
			if(hand.list[1].position =="Melee") {
				MPlayed2->Picture=Card2->Picture;
				AMs+=hand.list[1].strength;
				AM->Caption=AMs;
			}
			else if(hand.list[1].position =="Ranged") {
				RPlayed2->Picture=Card2->Picture;
				ARs+=hand.list[1].strength;
				AR->Caption=ARs;
			}
			else {
				SPlayed2->Picture=Card2->Picture;
				ASs+=hand.list[1].strength;
				AS->Caption=ASs;
			}
			ATScore+=hand.list[1].strength;
			AScore->Caption=ATScore;
			if(ATScore>ETScore) {
				AScore->Font->Color=RGB(204,172,0);
				EScore->Font->Color=clSilver;
			}
			else if(ATScore<ETScore) {
				EScore->Font->Color=RGB(204,172,0);
				AScore->Font->Color=clSilver;
			}
			else if(ATScore==ETScore) {
				AScore->Font->Color=clSilver;
                EScore->Font->Color=clSilver;
            }
			Card2->Picture=NULL;
			if(Eend==0) {
				Turn->Visible=true;
				Turn->Caption="Your Turn";
				Coin->Picture->LoadFromFile("skin/Coin.png");
				Card1->OnClick=Card1Click;
				Card2->OnClick=NULL;
				Card3->OnClick=Card3Click;
				Card4->OnClick=Card4Click;
				Card5->OnClick=Card5Click;
				Card6->OnClick=Card6Click;
			}
			else {
				Card1->OnClick =NULL;
				Card2->OnClick =NULL;
				Card3->OnClick =NULL;
				Card4->OnClick =NULL;
				Card5->OnClick =NULL;
				Card6->OnClick =NULL;
                Coin->Picture->LoadFromFile("skin/CoinE.png");
				Turn->Caption="Enemy Turn";
			}
		}
	}
	else {
		Card2->OnClick=NULL;
	}
}
void __fastcall TForm5::Card3Click(TObject *Sender)
{
	if (counter3==0) {
		if(Aend==0) {
			Card1->OnClick =NULL;
			Card2->OnClick =NULL;
			Card3->OnClick =NULL;
			Card4->OnClick =NULL;
			Card5->OnClick =NULL;
			Card6->OnClick = NULL;
		}
		else {
			counter3++;
			Clients ->Connect();
			Clients ->Socket->WriteLn("Card3");
			Clients->Disconnect();
			if(hand.list[2].position =="Melee") {
				MPlayed3->Picture=Card3->Picture;
				AMs+=hand.list[2].strength;
				AM->Caption=AMs;
			}
			else if(hand.list[2].position =="Ranged") {
				RPlayed3->Picture=Card3->Picture;
				ARs+=hand.list[2].strength;
				AR->Caption=ARs;
			}
			else {
				SPlayed3->Picture=Card3->Picture;
				ASs+=hand.list[2].strength;
				AS->Caption=ASs;
			}
			ATScore+=hand.list[2].strength;
			AScore->Caption=ATScore;
			if(ATScore>ETScore) {
				AScore->Font->Color=RGB(204,172,0);
				EScore->Font->Color=clSilver;
			}
			else if(ATScore<ETScore) {
				EScore->Font->Color=RGB(204,172,0);
				AScore->Font->Color=clSilver;
			}
			else if(ATScore==ETScore) {
				AScore->Font->Color=clSilver;
                EScore->Font->Color=clSilver;
            }
			Card3->Picture=NULL;
			if(Eend==0) {
				Turn->Visible=true;
				Turn->Caption="Your Turn";
				Coin->Picture->LoadFromFile("skin/Coin.png");
				Card1->OnClick=Card1Click;
				Card2->OnClick=Card2Click;
				Card3->OnClick=NULL;
				Card4->OnClick=Card4Click;
				Card5->OnClick=Card5Click;
				Card6->OnClick=Card6Click;
			}
			else {
				Card1->OnClick =NULL;
				Card2->OnClick =NULL;
				Card3->OnClick =NULL;
				Card4->OnClick =NULL;
				Card5->OnClick =NULL;
				Card6->OnClick =NULL;

                Coin->Picture->LoadFromFile("skin/CoinE.png");
				Turn->Caption="Enemy Turn";
			}
		}
	}
	else {
		Card3->OnClick=NULL;
	}
}
void __fastcall TForm5::Card4Click(TObject *Sender)
{
	if (counter4==0) {
		if(Aend==0) {
			Card1->OnClick =NULL;
			Card2->OnClick =NULL;
			Card3->OnClick =NULL;
			Card4->OnClick =NULL;
			Card5->OnClick =NULL;
			Card6->OnClick = NULL;
		}
		else {
			counter4++;
			Clients ->Connect();
			Clients ->Socket->WriteLn("Card4");
			Clients->Disconnect();
			if(hand.list[3].position =="Melee") {
				MPlayed4->Picture=Card4->Picture;
				AMs+=hand.list[3].strength;
				AM->Caption=AMs;
			}
			else if(hand.list[3].position =="Ranged") {
				RPlayed4->Picture=Card4->Picture;
				ARs+=hand.list[3].strength;
				AR->Caption=ARs;
			}
			else {
				SPlayed4->Picture=Card4->Picture;
				ASs+=hand.list[3].strength;
				AS->Caption=ASs;
			}
			ATScore+=hand.list[3].strength;
			AScore->Caption=ATScore;
			if(ATScore>ETScore) {
				AScore->Font->Color=RGB(204,172,0);
				EScore->Font->Color=clSilver;
			}
			else if(ATScore<ETScore) {
				EScore->Font->Color=RGB(204,172,0);
				AScore->Font->Color=clSilver;
			}
			else if(ATScore==ETScore) {
				AScore->Font->Color=clSilver;
                EScore->Font->Color=clSilver;
            }
			Card4->Picture=NULL;
			if(Eend==0) {
				Turn->Visible=true;
				Turn->Caption="Your Turn";
				Coin->Picture->LoadFromFile("skin/Coin.png");
				Card1->OnClick=Card1Click;
				Card2->OnClick=Card2Click;
				Card3->OnClick=Card3Click;
				Card4->OnClick=NULL;
				Card5->OnClick=Card5Click;
				Card6->OnClick=Card6Click;
			}
			else {
				Card1->OnClick =NULL;
				Card2->OnClick =NULL;
				Card3->OnClick =NULL;
				Card4->OnClick =NULL;
				Card5->OnClick =NULL;
				Card6->OnClick =NULL;

                Coin->Picture->LoadFromFile("skin/CoinE.png");
				Turn->Caption="Enemy Turn";
			}
		}
	}
	else {
		Card4->OnClick=NULL;
	}
}
void __fastcall TForm5::Card5Click(TObject *Sender)
{
	if (counter5==0) {
		if(Aend==0) {
			Card1->OnClick =NULL;
			Card2->OnClick =NULL;
			Card3->OnClick =NULL;
			Card4->OnClick =NULL;
			Card5->OnClick =NULL;
			Card6->OnClick = NULL;
		}
		else {
			counter5++;
			Clients ->Connect();
			Clients ->Socket->WriteLn("Card5");
			Clients->Disconnect();
			if(hand.list[4].position =="Melee") {
				MPlayed5->Picture=Card5->Picture;
				AMs+=hand.list[4].strength;
				AM->Caption=AMs;
			}
			else if(hand.list[4].position =="Ranged") {
				RPlayed5->Picture=Card5->Picture;
				ARs+=hand.list[4].strength;
				AR->Caption=ARs;
			}
			else {
				SPlayed5->Picture=Card5->Picture;
				ASs+=hand.list[4].strength;
				AS->Caption=ASs;
			}
			ATScore+=hand.list[4].strength;
			AScore->Caption=ATScore;
			if(ATScore>ETScore) {
				AScore->Font->Color=RGB(204,172,0);
				EScore->Font->Color=clSilver;
			}
			else if(ATScore<ETScore) {
				EScore->Font->Color=RGB(204,172,0);
				AScore->Font->Color=clSilver;
			}
			else if(ATScore==ETScore) {
				AScore->Font->Color=clSilver;
                EScore->Font->Color=clSilver;
            }
			Card5->Picture=NULL;
			if(Eend==0) {
				Turn->Visible=true;
				Turn->Caption="Your Turn";
				Coin->Picture->LoadFromFile("skin/Coin.png");
				Card1->OnClick=Card1Click;
				Card2->OnClick=Card2Click;
				Card3->OnClick=Card3Click;
				Card4->OnClick=Card4Click;
				Card5->OnClick=NULL;
				Card6->OnClick=Card6Click;
			}
			else {
				Card1->OnClick =NULL;
				Card2->OnClick =NULL;
				Card3->OnClick =NULL;
				Card4->OnClick =NULL;
				Card5->OnClick =NULL;
				Card6->OnClick =NULL;;

				Coin->Picture->LoadFromFile("skin/CoinE.png");
				Turn->Caption="Enemy Turn";
			}
		}
	}
	else {
		Card5->OnClick=NULL;
	}
}
void __fastcall TForm5::Card6Click(TObject *Sender)
{
	if (counter6==0) {
		if(Aend==0) {
			Card1->OnClick =NULL;
			Card2->OnClick =NULL;
			Card3->OnClick =NULL;
			Card4->OnClick =NULL;
			Card5->OnClick =NULL;
			Card6->OnClick = NULL;
		}
		else {
			counter6++;
			Clients ->Connect();
			Clients ->Socket->WriteLn("Card6");
			Clients->Disconnect();
			if(hand.list[5].position =="Melee") {
				MPlayed6->Picture=Card6->Picture;
				AMs+=hand.list[5].strength;
				AM->Caption=AMs;
			}
			else if(hand.list[5].position =="Ranged") {
				RPlayed6->Picture=Card6->Picture;
				ARs+=hand.list[5].strength;
				AR->Caption=ARs;
			}
			else {
				SPlayed6->Picture=Card6->Picture;
				ASs+=hand.list[5].strength;
				AS->Caption=ASs;
			}
			ATScore+=hand.list[5].strength;
			AScore->Caption=ATScore;
			if(ATScore>ETScore) {
				AScore->Font->Color=RGB(204,172,0);
				EScore->Font->Color=clSilver;
			}
			else if(ATScore<ETScore) {
				EScore->Font->Color=RGB(204,172,0);
				AScore->Font->Color=clSilver;
			}
			else if(ATScore==ETScore) {
				AScore->Font->Color=clSilver;
                EScore->Font->Color=clSilver;
            }
			Card6->Picture=NULL;
			if(Eend==0) {
				Turn->Visible=true;
				Turn->Caption="Your Turn";
				Coin->Picture->LoadFromFile("skin/Coin.png");
				Card1->OnClick=Card1Click;
				Card2->OnClick=Card2Click;
				Card3->OnClick=Card3Click;
				Card4->OnClick=Card4Click;
				Card5->OnClick=Card5Click;
				Card6->OnClick=NULL;
			}
			else {
				Card1->OnClick =NULL;
				Card2->OnClick =NULL;
				Card3->OnClick =NULL;
				Card4->OnClick =NULL;
				Card5->OnClick =NULL;
				Card6->OnClick =NULL;
				Coin->Picture->LoadFromFile("skin/CoinE.png");
                Turn->Caption="Enemy Turn";
			}
		}
	}
	else {
		Card6->OnClick=NULL;
	}
}
void __fastcall TForm5::ALeaderClick(TObject *Sender)
{
	if(counterS==0) {
		counterS++;
		int who= ASpecial;
		Clients->Connect();
		Clients->Socket->WriteLn("Leader");
		Clients->Socket->Write(who);
		Clients->Disconnect();
		if(who==46) {
			Chat->Items->Add("Foltest leader ability used");
			ATScore=ATScore-ASs;
			ASs=ASs*2;
			AS->Caption=ASs;
			ATScore=ATScore+ASs;
			AScore->Caption=ATScore;
			if(ATScore>ETScore) {
				AScore->Font->Color=RGB(204,172,0);
				EScore->Font->Color=clSilver;
			}
			else if(ATScore<ETScore) {
				EScore->Font->Color=RGB(204,172,0);
				AScore->Font->Color=clSilver;
			}
			else if(ATScore==ETScore) {
				AScore->Font->Color=clSilver;
				EScore->Font->Color=clSilver;
			}
		}
		else if(who==47) {
			Chat->Items->Add("Lady of the Lake leader ability used");
			ATScore=ATScore-ARs;
			ARs=ARs*2;
			AR->Caption=ARs;
			ATScore=ATScore+ARs;
			AScore->Caption=ATScore;
			if(ATScore>ETScore) {
				AScore->Font->Color=RGB(204,172,0);
				EScore->Font->Color=clSilver;
			}
			else if(ATScore<ETScore) {
				EScore->Font->Color=RGB(204,172,0);
				AScore->Font->Color=clSilver;
			}
			else if(ATScore==ETScore) {
				AScore->Font->Color=clSilver;
				EScore->Font->Color=clSilver;
			}
		}
		else if(who==48) {
			Chat->Items->Add("Eredin leader ability used");
			ETScore=ETScore-EMs;
			EMs=EMs/2;
			EM->Caption=EMs;
			ETScore=ETScore+EMs;
			EScore->Caption=ETScore;
			if(ATScore>ETScore) {
				AScore->Font->Color=RGB(204,172,0);
				EScore->Font->Color=clSilver;
			}
			else if(ATScore<ETScore) {
				EScore->Font->Color=RGB(204,172,0);
				AScore->Font->Color=clSilver;
			}
			else if(ATScore==ETScore) {
				AScore->Font->Color=clSilver;
				EScore->Font->Color=clSilver;
			}
		}
		else if(who==49) {
			Chat->Items->Add("Emhyr leader ability used");
			if(Eend==1) {
				OCard1->Picture->Bitmap->LoadFromResourceID((unsigned)MyCards,enemy.list[0].ID);
			}
			if(Eend==2) {
				OCard1->Picture->Bitmap->LoadFromResourceID((unsigned)MyCards,enemy.list[0].ID);
				OCard2->Picture->Bitmap->LoadFromResourceID((unsigned)MyCards,enemy.list[1].ID);
			}
			if(Eend==3) {
				OCard1->Picture->Bitmap->LoadFromResourceID((unsigned)MyCards,enemy.list[0].ID);
				OCard2->Picture->Bitmap->LoadFromResourceID((unsigned)MyCards,enemy.list[1].ID);
				OCard3->Picture->Bitmap->LoadFromResourceID((unsigned)MyCards,enemy.list[2].ID);
			}
			if(Eend==4) {
				OCard1->Picture->Bitmap->LoadFromResourceID((unsigned)MyCards,enemy.list[0].ID);
				OCard2->Picture->Bitmap->LoadFromResourceID((unsigned)MyCards,enemy.list[1].ID);
				OCard3->Picture->Bitmap->LoadFromResourceID((unsigned)MyCards,enemy.list[2].ID);
				OCard4->Picture->Bitmap->LoadFromResourceID((unsigned)MyCards,enemy.list[3].ID);
			}
			if(Eend==5) {
				OCard1->Picture->Bitmap->LoadFromResourceID((unsigned)MyCards,enemy.list[0].ID);
				OCard2->Picture->Bitmap->LoadFromResourceID((unsigned)MyCards,enemy.list[1].ID);
				OCard3->Picture->Bitmap->LoadFromResourceID((unsigned)MyCards,enemy.list[2].ID);
				OCard4->Picture->Bitmap->LoadFromResourceID((unsigned)MyCards,enemy.list[3].ID);
				OCard5->Picture->Bitmap->LoadFromResourceID((unsigned)MyCards,enemy.list[4].ID);
			}
			if(Eend==6) {
				OCard1->Picture->Bitmap->LoadFromResourceID((unsigned)MyCards,enemy.list[0].ID);
				OCard2->Picture->Bitmap->LoadFromResourceID((unsigned)MyCards,enemy.list[1].ID);
				OCard3->Picture->Bitmap->LoadFromResourceID((unsigned)MyCards,enemy.list[2].ID);
				OCard4->Picture->Bitmap->LoadFromResourceID((unsigned)MyCards,enemy.list[3].ID);
				OCard5->Picture->Bitmap->LoadFromResourceID((unsigned)MyCards,enemy.list[4].ID);
				OCard6->Picture->Bitmap->LoadFromResourceID((unsigned)MyCards,enemy.list[5].ID);
			}
		}

		else {
			Chat->Items->Add("Unknown leader");
		}
	}
	else {
		Chat->Items->Add("Leader already used!");
	}
}
void __fastcall TForm5::CoinClick(TObject *Sender)
{
	if(Turn->Caption=="Your Turn") {
		Aend=0;
		Chat->Items->Add("You've passed");
		if(Aend==0 && Eend==0) {
			Deckdef help;
			help.clean();
			Clients->Connect();
			Clients->Socket->WriteLn("Roundover");
			if(ATScore > ETScore) {
				AW++;
				A->Picture->LoadFromFile("skin/A1.png");
				Chat->Items->Add("You won the round!");
			}
			else if(ETScore>ATScore) {
				EW++;
                E->Picture->LoadFromFile("skin/E1.png");
				Chat->Items->Add("You lost the round!");
			}
			else if(ETScore==ATScore) {
				AW++;
				EW++;
				A->Picture->LoadFromFile("skin/A1.png");
				E->Picture->LoadFromFile("skin/E1.png");
				Chat->Items->Add("Draw round!");
			}
			if(AW==2 && EW!=2) {
				A->Picture->LoadFromFile("skin/A2.png");
				ShowMessage("You Won the game!");
				Application->Terminate();
			}
			else if(EW==2 && AW!=2) {
				E->Picture->LoadFromFile("skin/E2.png");
				ShowMessage("You Lost the game!");
				Application->Terminate();
			}
			else if(EW==2 && AW==2) {
				A->Picture->LoadFromFile("skin/A2.png");
                A->Picture->LoadFromFile("skin/E2.png");
				ShowMessage("Game tied!");
				Application->Terminate();
			}
			if(counter1==0) {
				help.add(hand.list[0]);
			}
			if(counter2==0) {
				help.add(hand.list[1]);
			}
			if(counter3==0) {
				help.add(hand.list[2]);
			}
			if(counter4==0) {
				help.add(hand.list[3]);
			}
			if(counter5==0) {
				help.add(hand.list[4]);
			}
			if(counter6==0) {
				help.add(hand.list[5]);
			}
			for(int i=0;i<3;i++) {
				help.add(residue.list[i]);
			}
			hand.clean();
			for(int i=0;i<help.size();i++) {
				if(hand.size()<6) {
					hand.add(help.list[i]);
				}
				else {
					Chat->Items->Add(help.list[i].name+" was destroyed due to full hand");
				}
			}
			residue.list.erase(residue.list.begin()+0);
			residue.list.erase(residue.list.begin()+1);
			residue.list.erase(residue.list.begin()+2);
			Aend =hand.size();
			Clients->Socket->Write(Aend);
			for(int i=0;i<Aend;i++) {
				Clients->Socket->Write(hand.list[i].ID);
				Clients->Socket->Write(hand.list[i].strength);
				Clients->Socket->WriteLn(hand.list[i].position);
				Clients->Socket->WriteLn(hand.list[i].name);
			}
			Clients->Disconnect();
			Card1->OnClick = NULL;
			Card2->OnClick = NULL;
			Card3->OnClick = NULL;
			Card4->OnClick = NULL;
			Card5->OnClick = NULL;
			Card6->OnClick = NULL;
			ATScore=0;
			ETScore=0;
			AScore->Caption=ATScore;
			EScore->Caption=ETScore;
			ASs=0;
			AS->Caption=ASs;
			ARs=0;
			AR->Caption=ARs;
			AMs=0;
			AM->Caption=AMs;
			ESs=0;
			ES->Caption=ESs;
			ERs=0;
			ER->Caption=ERs;
			EMs=0;
			EM->Caption=EMs;
			MPlayed1->Picture=NULL;
			MPlayed2->Picture=NULL;
			MPlayed3->Picture=NULL;
			MPlayed4->Picture=NULL;
			MPlayed5->Picture=NULL;
			MPlayed6->Picture=NULL;
			RPlayed1->Picture=NULL;
			RPlayed2->Picture=NULL;
			RPlayed3->Picture=NULL;
			RPlayed4->Picture=NULL;
			RPlayed5->Picture=NULL;
			RPlayed6->Picture=NULL;
			SPlayed1->Picture=NULL;
			SPlayed2->Picture=NULL;
			SPlayed3->Picture=NULL;
			SPlayed4->Picture=NULL;
			SPlayed5->Picture=NULL;
			SPlayed6->Picture=NULL;
			OMPlayed1->Picture=NULL;
			OMPlayed2->Picture=NULL;
			OMPlayed3->Picture=NULL;
			OMPlayed4->Picture=NULL;
			OMPlayed5->Picture=NULL;
			OMPlayed6->Picture=NULL;
			ORPlayed1->Picture=NULL;
			ORPlayed2->Picture=NULL;
			ORPlayed3->Picture=NULL;
			ORPlayed4->Picture=NULL;
			ORPlayed5->Picture=NULL;
			ORPlayed6->Picture=NULL;
			OSPlayed1->Picture=NULL;
			OSPlayed2->Picture=NULL;
			OSPlayed3->Picture=NULL;
			OSPlayed4->Picture=NULL;
			OSPlayed5->Picture=NULL;
			OSPlayed6->Picture=NULL;
		}
		else {
			Card1->OnClick=NULL;
			Card2->OnClick=NULL;
			Card3->OnClick=NULL;
			Card4->OnClick=NULL;
			Card5->OnClick=NULL;
			Card6->OnClick=NULL;;

			Coin->Picture->LoadFromFile("skin/CoinE.png");
			Turn->Caption="Enemy Turn";
			Clients->Connect();
			Clients->Socket->WriteLn("EndTurn");
			Clients->Disconnect();
		}
	}
	else {
        Chat->Items->Add("Wait for your turn!");
    }
}
void __fastcall TForm5::Card1MouseMove(TObject *Sender, TShiftState Shift, int X,
		  int Y)
{
	if(counter1==0 && Game!=0) {
      	Hover->Picture = Card1->Picture;
		HoverPosition->Caption=hand.list[0].position;
		HoverName->Caption=hand.list[0].name;
		HoverPosition->Visible=true;
		HoverName->Visible=true;
		Card1->Height=150;
		Card1->Width=130;
		Card1->Top=900;
        Card1->BringToFront();
	}
}
void __fastcall TForm5::Card1MouseLeave(TObject *Sender)
{
	Hover->Picture = NULL;
	HoverPosition->Visible=false;
	HoverName->Visible=false;
	Card1->Height=120;
	Card1->Width=100;
    Card1->Top=952;
}
void __fastcall TForm5::Card2MouseLeave(TObject *Sender)
{
	Hover->Picture = NULL;
	HoverPosition->Visible=false;
	HoverName->Visible=false;
	Card2->Height=120;
	Card2->Width=100;
	Card2->Top=952;
}
void __fastcall TForm5::Card2MouseEnter(TObject *Sender)
{
	if(counter2==0 && Game!=0) {
		Hover->Picture = Card2->Picture;
		HoverPosition->Caption=hand.list[1].position;
		HoverName->Caption=hand.list[1].name;
		HoverPosition->Visible=true;
		HoverName->Visible=true;
		Card2->Height=150;
		Card2->Width=130;
		Card2->Top=900;
		Card2->BringToFront();
    }
}
void __fastcall TForm5::Card3MouseEnter(TObject *Sender)
{
	if(counter3==0 && Game!=0) {
		Hover->Picture = Card3->Picture;
		HoverPosition->Caption=hand.list[2].position;
		HoverName->Caption=hand.list[2].name;
		HoverPosition->Visible=true;
		HoverName->Visible=true;
		Card3->Height=150;
		Card3->Width=130;
		Card3->Top=900;
		Card3->BringToFront();
	}
}
void __fastcall TForm5::Card3MouseLeave(TObject *Sender)
{
	Hover->Picture = NULL;
	HoverPosition->Visible=false;
	HoverName->Visible=false;
	Card3->Height=120;
	Card3->Width=100;
	Card3->Top=952;
}
void __fastcall TForm5::Card4MouseEnter(TObject *Sender)
{
	if(counter4==0 && Game!=0) {
		Hover->Picture = Card4->Picture;
		HoverPosition->Caption=hand.list[3].position;
		HoverName->Caption=hand.list[3].name;
		HoverPosition->Visible=true;
		HoverName->Visible=true;
		Card4->Height=150;
		Card4->Width=130;
		Card4->Top=900;
		Card4->BringToFront();
    }
}
void __fastcall TForm5::Card4MouseLeave(TObject *Sender)
{
	Hover->Picture = NULL;
	HoverPosition->Visible=false;
	HoverName->Visible=false;
	Card4->Height=120;
	Card4->Width=100;
	Card4->Top=952;
}
void __fastcall TForm5::Card5MouseLeave(TObject *Sender)
{
	Hover->Picture = NULL;
	HoverPosition->Visible=false;
	HoverName->Visible=false;
	Card5->Height=120;
	Card5->Width=100;
	Card5->Top=952;
}
void __fastcall TForm5::Card5MouseMove(TObject *Sender, TShiftState Shift, int X,
		  int Y)
{
	if(counter5==0 && Game!=0) {
		Hover->Picture = Card5->Picture;
		HoverPosition->Caption=hand.list[4].position;
		HoverName->Caption=hand.list[4].name;
		HoverPosition->Visible=true;
		HoverName->Visible=true;
		Card5->Height=150;
		Card5->Width=130;
		Card5->Top=900;
		Card5->BringToFront();
    }
}
void __fastcall TForm5::Card6MouseLeave(TObject *Sender)
{
	Hover->Picture = NULL;
	HoverPosition->Visible=false;
	HoverName->Visible=false;
	Card6->Height=120;
	Card6->Width=100;
	Card6->Top=952;
}
void __fastcall TForm5::Card6MouseMove(TObject *Sender, TShiftState Shift, int X,
		  int Y)
{
	if(counter6==0 && Game!=0) {
		Hover->Picture = Card6->Picture;
		HoverPosition->Caption=hand.list[5].position;
		HoverName->Caption=hand.list[5].name;
		HoverPosition->Visible=true;
		HoverName->Visible=true;
		Card6->Height=150;
		Card6->Width=130;
		Card6->Top=900;
		Card6->BringToFront();
    }
}
void __fastcall TForm5::MPlayed1MouseMove(TObject *Sender, TShiftState Shift, int X,int Y)
{
	if(counter1!=0 && hand.list[0].position=="Melee") {
		Hover->Picture = MPlayed1->Picture;
		HoverPosition->Caption=hand.list[0].position;
		HoverName->Caption=hand.list[0].name;
		HoverPosition->Visible=true;
		HoverName->Visible=true;
    }
}
void __fastcall TForm5::MPlayed1MouseLeave(TObject *Sender)
{
	Hover->Picture = NULL;
	HoverPosition->Visible=false;
	HoverName->Visible=false;
}
 void __fastcall TForm5::MPlayed2MouseMove(TObject *Sender, TShiftState Shift, int X,int Y)
{
	if(counter2!=0 && hand.list[1].position=="Melee") {
		Hover->Picture = MPlayed2->Picture;
		HoverPosition->Caption=hand.list[1].position;
		HoverName->Caption=hand.list[1].name;
		HoverPosition->Visible=true;
		HoverName->Visible=true;
    }
}
void __fastcall TForm5::MPlayed2MouseLeave(TObject *Sender)
{
	Hover->Picture = NULL;
	HoverPosition->Visible=false;
	HoverName->Visible=false;
}
 void __fastcall TForm5::MPlayed3MouseMove(TObject *Sender, TShiftState Shift, int X,int Y)
{
	if(counter3!=0 && hand.list[2].position=="Melee") {
		Hover->Picture = MPlayed3->Picture;
		HoverPosition->Caption=hand.list[2].position;
		HoverName->Caption=hand.list[2].name;
		HoverPosition->Visible=true;
		HoverName->Visible=true;
    }
}
void __fastcall TForm5::MPlayed3MouseLeave(TObject *Sender)
{
	Hover->Picture = NULL;
	HoverPosition->Visible=false;
	HoverName->Visible=false;
}
 void __fastcall TForm5::MPlayed4MouseMove(TObject *Sender, TShiftState Shift, int X,int Y)
{
	if(counter4!=0 && hand.list[3].position=="Melee") {
		Hover->Picture = MPlayed4->Picture;
		HoverPosition->Caption=hand.list[3].position;
		HoverName->Caption=hand.list[3].name;
		HoverPosition->Visible=true;
		HoverName->Visible=true;
    }
}
void __fastcall TForm5::MPlayed4MouseLeave(TObject *Sender)
{
	Hover->Picture = NULL;
	HoverPosition->Visible=false;
	HoverName->Visible=false;
}
 void __fastcall TForm5::MPlayed5MouseMove(TObject *Sender, TShiftState Shift, int X,int Y)
{
	if(counter5!=0 && hand.list[4].position=="Melee") {
		Hover->Picture = MPlayed5->Picture;
		HoverPosition->Caption=hand.list[4].position;
		HoverName->Caption=hand.list[4].name;
		HoverPosition->Visible=true;
		HoverName->Visible=true;
    }
}
void __fastcall TForm5::MPlayed5MouseLeave(TObject *Sender)
{
	Hover->Picture = NULL;
	HoverPosition->Visible=false;
	HoverName->Visible=false;
}
 void __fastcall TForm5::MPlayed6MouseMove(TObject *Sender, TShiftState Shift, int X,int Y)
{
	if(counter6!=0 && hand.list[5].position=="Melee") {
		Hover->Picture = MPlayed6->Picture;
		HoverPosition->Caption=hand.list[5].position;
		HoverName->Caption=hand.list[5].name;
		HoverPosition->Visible=true;
		HoverName->Visible=true;
    }
}
void __fastcall TForm5::MPlayed6MouseLeave(TObject *Sender)
{
	Hover->Picture = NULL;
	HoverPosition->Visible=false;
	HoverName->Visible=false;
}
void __fastcall TForm5::RPlayed1MouseMove(TObject *Sender, TShiftState Shift, int X,int Y)
{
	if(counter1!=0 && hand.list[0].position=="Ranged") {
		Hover->Picture = RPlayed1->Picture;
		HoverPosition->Caption=hand.list[0].position;
		HoverName->Caption=hand.list[0].name;
		HoverPosition->Visible=true;
		HoverName->Visible=true;
    }
}
void __fastcall TForm5::RPlayed1MouseLeave(TObject *Sender)
{
	Hover->Picture = NULL;
	HoverPosition->Visible=false;
	HoverName->Visible=false;
}
 void __fastcall TForm5::RPlayed2MouseMove(TObject *Sender, TShiftState Shift, int X,int Y)
{
	if(counter2!=0 && hand.list[1].position=="Ranged") {
		Hover->Picture = RPlayed2->Picture;
		HoverPosition->Caption=hand.list[1].position;
		HoverName->Caption=hand.list[1].name;
		HoverPosition->Visible=true;
		HoverName->Visible=true;
    }
}
void __fastcall TForm5::RPlayed2MouseLeave(TObject *Sender)
{
	Hover->Picture = NULL;
	HoverPosition->Visible=false;
	HoverName->Visible=false;
}
 void __fastcall TForm5::RPlayed3MouseMove(TObject *Sender, TShiftState Shift, int X,int Y)
{
	if(counter3!=0 && hand.list[2].position=="Ranged") {
		Hover->Picture = RPlayed3->Picture;
		HoverPosition->Caption=hand.list[2].position;
		HoverName->Caption=hand.list[2].name;
		HoverPosition->Visible=true;
		HoverName->Visible=true;
    }
}
void __fastcall TForm5::RPlayed3MouseLeave(TObject *Sender)
{
	Hover->Picture = NULL;
	HoverPosition->Visible=false;
	HoverName->Visible=false;
}
 void __fastcall TForm5::RPlayed4MouseMove(TObject *Sender, TShiftState Shift, int X,int Y)
{
	if(counter4!=0 && hand.list[3].position=="Ranged") {
		Hover->Picture = RPlayed4->Picture;
		HoverPosition->Caption=hand.list[3].position;
		HoverName->Caption=hand.list[3].name;
		HoverPosition->Visible=true;
		HoverName->Visible=true;
    }
}
void __fastcall TForm5::RPlayed4MouseLeave(TObject *Sender)
{
	Hover->Picture = NULL;
	HoverPosition->Visible=false;
	HoverName->Visible=false;
}
 void __fastcall TForm5::RPlayed5MouseMove(TObject *Sender, TShiftState Shift, int X,int Y)
{
	if(counter5!=0 && hand.list[4].position=="Ranged") {
		Hover->Picture = RPlayed5->Picture;
		HoverPosition->Caption=hand.list[4].position;
		HoverName->Caption=hand.list[4].name;
		HoverPosition->Visible=true;
		HoverName->Visible=true;
    }
}
void __fastcall TForm5::RPlayed5MouseLeave(TObject *Sender)
{
	Hover->Picture = NULL;
	HoverPosition->Visible=false;
	HoverName->Visible=false;
}
 void __fastcall TForm5::RPlayed6MouseMove(TObject *Sender, TShiftState Shift, int X,int Y)
{
	if(counter6!=0 && hand.list[5].position=="Ranged") {
		Hover->Picture = RPlayed6->Picture;
		HoverPosition->Caption=hand.list[5].position;
		HoverName->Caption=hand.list[5].name;
		HoverPosition->Visible=true;
		HoverName->Visible=true;
    }
}
void __fastcall TForm5::RPlayed6MouseLeave(TObject *Sender)
{
	Hover->Picture = NULL;
	HoverPosition->Visible=false;
	HoverName->Visible=false;
}
void __fastcall TForm5::SPlayed1MouseMove(TObject *Sender, TShiftState Shift, int X,int Y)
{
	if(counter1!=0 && hand.list[0].position=="Siege") {
		Hover->Picture = SPlayed1->Picture;
		HoverPosition->Caption=hand.list[0].position;
		HoverName->Caption=hand.list[0].name;
		HoverPosition->Visible=true;
		HoverName->Visible=true;
    }
}
void __fastcall TForm5::SPlayed1MouseLeave(TObject *Sender)
{
	Hover->Picture = NULL;
	HoverPosition->Visible=false;
	HoverName->Visible=false;
}
 void __fastcall TForm5::SPlayed2MouseMove(TObject *Sender, TShiftState Shift, int X,int Y)
{
	if(counter2!=0 && hand.list[1].position=="Siege") {
		Hover->Picture = SPlayed2->Picture;
		HoverPosition->Caption=hand.list[1].position;
		HoverName->Caption=hand.list[1].name;
		HoverPosition->Visible=true;
		HoverName->Visible=true;
    }
}
void __fastcall TForm5::SPlayed2MouseLeave(TObject *Sender)
{
	Hover->Picture = NULL;
	HoverPosition->Visible=false;
	HoverName->Visible=false;
}
 void __fastcall TForm5::SPlayed3MouseMove(TObject *Sender, TShiftState Shift, int X,int Y)
{
	if(counter3!=0 && hand.list[2].position=="Siege") {
		Hover->Picture = SPlayed3->Picture;
		HoverPosition->Caption=hand.list[2].position;
		HoverName->Caption=hand.list[2].name;
		HoverPosition->Visible=true;
		HoverName->Visible=true;
    }
}
void __fastcall TForm5::SPlayed3MouseLeave(TObject *Sender)
{
	Hover->Picture = NULL;
	HoverPosition->Visible=false;
	HoverName->Visible=false;
}
 void __fastcall TForm5::SPlayed4MouseMove(TObject *Sender, TShiftState Shift, int X,int Y)
{
	if(counter4!=0 && hand.list[3].position=="Siege") {
		Hover->Picture = SPlayed4->Picture;
		HoverPosition->Caption=hand.list[3].position;
		HoverName->Caption=hand.list[3].name;
		HoverPosition->Visible=true;
		HoverName->Visible=true;
    }
}
void __fastcall TForm5::SPlayed4MouseLeave(TObject *Sender)
{
	Hover->Picture = NULL;
	HoverPosition->Visible=false;
	HoverName->Visible=false;
}
 void __fastcall TForm5::SPlayed5MouseMove(TObject *Sender, TShiftState Shift, int X,int Y)
{
	if(counter5!=0 && hand.list[4].position=="Siege") {
		Hover->Picture = SPlayed5->Picture;
		HoverPosition->Caption=hand.list[4].position;
		HoverName->Caption=hand.list[4].name;
		HoverPosition->Visible=true;
		HoverName->Visible=true;
    }
}
void __fastcall TForm5::SPlayed5MouseLeave(TObject *Sender)
{
	Hover->Picture = NULL;
	HoverPosition->Visible=false;
	HoverName->Visible=false;
}
 void __fastcall TForm5::SPlayed6MouseMove(TObject *Sender, TShiftState Shift, int X,int Y)
{
	if(counter6!=0 && hand.list[5].position=="Siege") {
		Hover->Picture = SPlayed6->Picture;
		HoverPosition->Caption=hand.list[5].position;
		HoverName->Caption=hand.list[5].name;
		HoverPosition->Visible=true;
		HoverName->Visible=true;
    }
}
void __fastcall TForm5::SPlayed6MouseLeave(TObject *Sender)
{
	Hover->Picture = NULL;
	HoverPosition->Visible=false;
	HoverName->Visible=false;
}
void __fastcall TForm5::ALeaderMouseEnter(TObject *Sender)
{
	Hover->Picture=ALeader->Picture;
	switch (ASpecial) {
		case 46:
			HoverName->Show();
			HoverName->Caption="Foltest";
            HoverPosition->Show();
			HoverPosition->Caption="Leader";
            HoverFlavor->Show();
			HoverFlavor->Caption="Double Siege Points";
            return;
		case 47:
            HoverName->Show();
			HoverName->Caption="Lady of the Lake";
            HoverPosition->Show();
			HoverPosition->Caption="Leader";
            HoverFlavor->Show();
			HoverFlavor->Caption="Double Ranged Points";
            return;
		case 48:
            HoverName->Show();
			HoverName->Caption="Eredin";
			HoverPosition->Show();
			HoverPosition->Caption="Leader";
            HoverFlavor->Show();
			HoverFlavor->Caption="Halves enemy Melle Points";
            return;
		case 49:
            HoverName->Show();
			HoverName->Caption="Emyhrr";
            HoverPosition->Show();
			HoverPosition->Caption="Leader";
            HoverFlavor->Show();
			HoverFlavor->Caption="Reveal enemy Cards";
            return;
	}
}
void __fastcall TForm5::ALeaderMouseLeave(TObject *Sender)
{
	Hover->Picture=NULL;
	HoverName->Caption=NULL;
	HoverPosition->Caption=NULL;
	HoverFlavor->Caption=NULL;
	HoverName->Hide();
	HoverPosition->Hide();
	HoverFlavor->Hide();
}
void __fastcall TForm5::ELeaderMouseEnter(TObject *Sender)
{
	Hover->Picture=ELeader->Picture;
	switch (ESpecial) {
		case 46:
			HoverName->Show();
			HoverName->Caption="Foltest";
            HoverPosition->Show();
			HoverPosition->Caption="Leader";
            HoverFlavor->Show();
			HoverFlavor->Caption="Double Siege Points";
            return;
		case 47:
            HoverName->Show();
			HoverName->Caption="Lady of the Lake";
            HoverPosition->Show();
			HoverPosition->Caption="Leader";
            HoverFlavor->Show();
			HoverFlavor->Caption="Double Ranged Points";
            return;
		case 48:
            HoverName->Show();
			HoverName->Caption="Eredin";
			HoverPosition->Show();
			HoverPosition->Caption="Leader";
            HoverFlavor->Show();
			HoverFlavor->Caption="Halves Enemy Melee";
            return;
		case 49:
            HoverName->Show();
			HoverName->Caption="Emyhrr";
            HoverPosition->Show();
			HoverPosition->Caption="Leader";
			HoverFlavor->Show();
			HoverFlavor->Caption="Reveal enemy Cards";
            return;
	}
}
void __fastcall TForm5::ELeaderMouseLeave(TObject *Sender)
{
	Hover->Picture=NULL;
	HoverName->Caption=NULL;
	HoverPosition->Caption=NULL;
	HoverFlavor->Caption=NULL;
	HoverName->Hide();
	HoverPosition->Hide();
	HoverFlavor->Hide();
}
void __fastcall TForm5::LocalClick(TObject *Sender)
{
	PlaySound(TEXT("gwent.wav"), NULL, SND_LOOP | SND_ASYNC);
	A->Visible=true;
	E->Visible=true;
	AScore->Visible=true;
	EScore->Visible=true;
	AS->Visible=true;
	AR->Visible=true;
	AM->Visible=true;
	ES->Visible=true;
	ER->Visible=true;
	EM->Visible=true;
	Turn->Visible=true;
	Turn->Caption="Your Turn";
	Coin->Picture->LoadFromFile("skin/Coin.png");
	AnsiString s ="SELECT * FROM ";
	AnsiString t =(AnsiString)Decks->Text;
	AnsiString i =s+t;
	QDeck->Close();
	QDeck->SQL->Text = i;
	QDeck->ExecSQL();
	QDeck->Open();
	Deckdef temp;
	for(int i=0;i<QDeck->RecordCount;i++) {
		Carddef t;
		t.name= AnsiString(QDeck->FieldByName("Name") -> AsString).c_str();
		t.ID = QDeck->FieldByName("ID") -> AsInteger;
		t.strength=QDeck->FieldByName("Strength") -> AsInteger;
		t.position=AnsiString(QDeck->FieldByName("Place") ->AsString).c_str();
		temp.add(t);
		srand(time(NULL));
		temp.shuf();
		QDeck->Next();
	}
	for(int i=0;i<6;i++) {
		hand.list.push_back(temp.list[i]);
	}
	for(int i=6;i<temp.size();i++) {
		residue.add(temp.list[i]);
	}
	_di_IXMLmadeType Made = Getmade(Xuser);
	ALeader->Picture->Bitmap->LoadFromResourceID((unsigned)MyCards,Made->deck[Decks->ItemIndex]->leader);
	ASpecial=Made->deck[Decks->ItemIndex]->leader;
	ALook=Made->deck[Decks->ItemIndex]->skin;
	AnsiString sk = "skin/";
	AnsiString ki = Made->deck[Decks->ItemIndex]->skin;
	AnsiString in =".bmp";
	ASkin->Picture->Bitmap->LoadFromFile(sk+ki+in);
	A->Visible=true;
	E->Visible=true;
	AScore->Visible=true;
	EScore->Visible=true;
	AS->Visible=true;
	AR->Visible=true;
	AM->Visible=true;
	ES->Visible=true;
	ER->Visible=true;
	EM->Visible=true;
	Turn->Visible=true;
	Local->Visible=false;
	LocalL->Visible=false;
	Server1L->Visible=false;
	Server1->Visible=false;
	Server2L->Visible=false;
	Server2->Visible=false;
	Create->Visible=false;
	CreateL->Visible=false;
	StReport->Visible=false;
	StReportL->Visible=false;
	PReport->Visible=false;
	PReportL->Visible=false;
	Skin->Visible=false;
	Deck->Visible=false;
	Decks->Visible=false;
	Leader->Visible=false;
	Chat->Left=24;
	Msg->Left=24;
	Send->Left=288;
	SendL->Left=313;
	Chat->Left=24;
	Msg->Left=24;
	Send->Left=288;
	SendL->Left=313;
	StReport->Visible=false;
	PReport->Visible=false;
	Skin->Visible=false;
	Deck->Visible=false;
	Decks->Visible=false;
	Clients->Host = "127.0.0.1";
	Clients->Connect();
	Clients->Socket->WriteLn("Setup");
	Clients->Socket->WriteLn("127.0.0.1");
	Clients->Socket->Write(ASpecial);
	Clients->Socket->Write(ALook);
	for(int i=0;i<6;i++) {
		Clients->Socket->Write(hand.list[i].ID);
		Clients->Socket->Write(hand.list[i].strength);
		Clients->Socket->WriteLn(hand.list[i].position);
		Clients->Socket->WriteLn(hand.list[i].name);
	}
	Game=1;
	Clients->Disconnect();
}
void __fastcall TForm5::Server1Click(TObject *Sender)
{
	PlaySound(TEXT("gwent.wav"), NULL, SND_LOOP | SND_ASYNC);
	A->Visible=true;
	E->Visible=true;
	AScore->Visible=true;
	EScore->Visible=true;
	AS->Visible=true;
	AR->Visible=true;
	AM->Visible=true;
	ES->Visible=true;
	ER->Visible=true;
	EM->Visible=true;
	Turn->Visible=true;
	Turn->Caption="Your Turn";
	Coin->Picture->LoadFromFile("skin/Coin.png");
	AnsiString s ="SELECT * FROM ";
	AnsiString t =(AnsiString)Decks->Text;
	AnsiString i =s+t;
	QDeck->Close();
	QDeck->SQL->Text = i;
	QDeck->ExecSQL();
	QDeck->Open();
	Deckdef temp;
	for(int i=0;i<QDeck->RecordCount;i++) {
		Carddef t;
		t.name= AnsiString(QDeck->FieldByName("Name") -> AsString).c_str();
		t.ID = QDeck->FieldByName("ID") -> AsInteger;
		t.strength=QDeck->FieldByName("Strength") -> AsInteger;
		t.position=AnsiString(QDeck->FieldByName("Place") ->AsString).c_str();
		temp.add(t);
		srand(time(NULL));
		temp.shuf();
		QDeck->Next();
	}
	for(int i=0;i<6;i++) {
		hand.list.push_back(temp.list[i]);
	}
	for(int i=6;i<temp.size();i++) {
		residue.add(temp.list[i]);
	}
	_di_IXMLmadeType Made = Getmade(Xuser);
	ALeader->Picture->Bitmap->LoadFromResourceID((unsigned)MyCards,Made->deck[Decks->ItemIndex]->leader);
	ASpecial=Made->deck[Decks->ItemIndex]->leader;
	ALook=Made->deck[Decks->ItemIndex]->skin;
	AnsiString sk = "skin/";
	AnsiString ki = Made->deck[Decks->ItemIndex]->skin;
	AnsiString in =".bmp";
	ASkin->Picture->Bitmap->LoadFromFile(sk+ki+in);
	A->Visible=true;
	E->Visible=true;
	AScore->Visible=true;
	EScore->Visible=true;
	AS->Visible=true;
	AR->Visible=true;
	AM->Visible=true;
	ES->Visible=true;
	ER->Visible=true;
	EM->Visible=true;
	Turn->Visible=true;
	Local->Visible=false;
	LocalL->Visible=false;
	Server1L->Visible=false;
	Server1->Visible=false;
	Server2L->Visible=false;
	Server2->Visible=false;
	Create->Visible=false;
	CreateL->Visible=false;
	StReport->Visible=false;
	StReportL->Visible=false;
	PReport->Visible=false;
	PReportL->Visible=false;
	Skin->Visible=false;
	Deck->Visible=false;
	Decks->Visible=false;
	Leader->Visible=false;
	Chat->Left=24;
	Msg->Left=24;
	Send->Left=288;
	SendL->Left=313;
	Chat->Left=24;
	Msg->Left=24;
	Send->Left=288;
	SendL->Left=313;
	StReport->Visible=false;
	PReport->Visible=false;
	Skin->Visible=false;
	Deck->Visible=false;
	Decks->Visible=false;
	Clients->Host = "25.79.2.205";
	Clients->Connect();
	Clients->Socket->WriteLn("Setup");
	Clients->Socket->WriteLn("25.95.10.244");
	Clients->Socket->Write(ASpecial);
	Clients->Socket->Write(ALook);
	for(int i=0;i<6;i++) {
		Clients->Socket->Write(hand.list[i].ID);
		Clients->Socket->Write(hand.list[i].strength);
		Clients->Socket->WriteLn(hand.list[i].position);
		Clients->Socket->WriteLn(hand.list[i].name);
	}
	Game=1;
	Clients->Disconnect();
}
void __fastcall TForm5::Server2Click(TObject *Sender)
{
	PlaySound(TEXT("gwent.wav"), NULL, SND_LOOP | SND_ASYNC);
	A->Visible=true;
	E->Visible=true;
	AScore->Visible=true;
	EScore->Visible=true;
	AS->Visible=true;
	AR->Visible=true;
	AM->Visible=true;
	ES->Visible=true;
	ER->Visible=true;
	EM->Visible=true;
	Turn->Visible=true;
	Turn->Caption="Your Turn";
	Coin->Picture->LoadFromFile("skin/Coin.png");
	AnsiString s ="SELECT * FROM ";
	AnsiString t =(AnsiString)Decks->Text;
	AnsiString i =s+t;
	QDeck->Close();
	QDeck->SQL->Text = i;
	QDeck->ExecSQL();
	QDeck->Open();
	Deckdef temp;
	for(int i=0;i<QDeck->RecordCount;i++) {
		Carddef t;
		t.name= AnsiString(QDeck->FieldByName("Name") -> AsString).c_str();
		t.ID = QDeck->FieldByName("ID") -> AsInteger;
		t.strength=QDeck->FieldByName("Strength") -> AsInteger;
		t.position=AnsiString(QDeck->FieldByName("Place") ->AsString).c_str();
		temp.add(t);
		srand(time(NULL));
		temp.shuf();
		QDeck->Next();
	}
	for(int i=0;i<6;i++) {
		hand.list.push_back(temp.list[i]);
	}
	for(int i=6;i<temp.size();i++) {
		residue.add(temp.list[i]);
	}
	_di_IXMLmadeType Made = Getmade(Xuser);
	ALeader->Picture->Bitmap->LoadFromResourceID((unsigned)MyCards,Made->deck[Decks->ItemIndex]->leader);
	ASpecial=Made->deck[Decks->ItemIndex]->leader;
	ALook=Made->deck[Decks->ItemIndex]->skin;
	AnsiString sk = "skin/";
	AnsiString ki = Made->deck[Decks->ItemIndex]->skin;
	AnsiString in =".bmp";
	ASkin->Picture->Bitmap->LoadFromFile(sk+ki+in);
	A->Visible=true;
	E->Visible=true;
	AScore->Visible=true;
	EScore->Visible=true;
	AS->Visible=true;
	AR->Visible=true;
	AM->Visible=true;
	ES->Visible=true;
	ER->Visible=true;
	EM->Visible=true;
	Turn->Visible=true;
	Local->Visible=false;
	LocalL->Visible=false;
	Server1L->Visible=false;
	Server1->Visible=false;
	Server2L->Visible=false;
	Server2->Visible=false;
	Create->Visible=false;
	CreateL->Visible=false;
	StReport->Visible=false;
	StReportL->Visible=false;
	PReport->Visible=false;
	PReportL->Visible=false;
	Skin->Visible=false;
	Deck->Visible=false;
	Decks->Visible=false;
	Leader->Visible=false;
	Chat->Left=24;
	Msg->Left=24;
	Send->Left=288;
	SendL->Left=313;
	Chat->Left=24;
	Msg->Left=24;
	Send->Left=288;
	SendL->Left=313;
	StReport->Visible=false;
	PReport->Visible=false;
	Skin->Visible=false;
	Deck->Visible=false;
	Decks->Visible=false;
	Clients->Host = "25.97.96.0";
	Clients->Connect();
	Clients->Socket->WriteLn("Setup");
	Clients->Socket->WriteLn("25.95.10.244");
	Clients->Socket->Write(ASpecial);
	Clients->Socket->Write(ALook);
	for(int i=0;i<6;i++) {
		Clients->Socket->Write(hand.list[i].ID);
		Clients->Socket->Write(hand.list[i].strength);
		Clients->Socket->WriteLn(hand.list[i].position);
		Clients->Socket->WriteLn(hand.list[i].name);
	}
	Game=1;
	Clients->Disconnect();
}
void __fastcall TForm5::CreateClick(TObject *Sender)
{
	PlaySound(TEXT("gwent.wav"), NULL, SND_LOOP | SND_ASYNC);
	A->Visible=true;
	E->Visible=true;
	AScore->Visible=true;
	EScore->Visible=true;
	AS->Visible=true;
	AR->Visible=true;
	AM->Visible=true;
	ES->Visible=true;
	ER->Visible=true;
	EM->Visible=true;
	Turn->Visible=true;
	Turn->Caption="Your Turn";
	Coin->Picture->LoadFromFile("skin/Coin.png");
	AnsiString s ="SELECT * FROM ";
	AnsiString t =(AnsiString)Decks->Text;
	AnsiString i =s+t;
	QDeck->Close();
	QDeck->SQL->Text = i;
	QDeck->ExecSQL();
	QDeck->Open();
	Deckdef temp;
	for(int i=0;i<QDeck->RecordCount;i++) {
		Carddef t;
		t.name= AnsiString(QDeck->FieldByName("Name") -> AsString).c_str();
		t.ID = QDeck->FieldByName("ID") -> AsInteger;
		t.strength=QDeck->FieldByName("Strength") -> AsInteger;
		t.position=AnsiString(QDeck->FieldByName("Place") ->AsString).c_str();
		temp.add(t);
		srand(time(NULL));
		temp.shuf();
		QDeck->Next();
	}
	for(int i=0;i<6;i++) {
		hand.list.push_back(temp.list[i]);
	}
	for(int i=6;i<temp.size();i++) {
		residue.add(temp.list[i]);
	}
	_di_IXMLmadeType Made = Getmade(Xuser);
	ALeader->Picture->Bitmap->LoadFromResourceID((unsigned)MyCards,Made->deck[Decks->ItemIndex]->leader);
	ASpecial=Made->deck[Decks->ItemIndex]->leader;
	ALook=Made->deck[Decks->ItemIndex]->skin;
	AnsiString sk = "skin/";
	AnsiString ki = Made->deck[Decks->ItemIndex]->skin;
	AnsiString in =".bmp";
	ASkin->Picture->Bitmap->LoadFromFile(sk+ki+in);
	A->Visible=true;
	E->Visible=true;
	AScore->Visible=true;
	EScore->Visible=true;
	AS->Visible=true;
	AR->Visible=true;
	AM->Visible=true;
	ES->Visible=true;
	ER->Visible=true;
	EM->Visible=true;
	Turn->Visible=true;
	Local->Visible=false;
	LocalL->Visible=false;
	Server1L->Visible=false;
	Server1->Visible=false;
	Server2L->Visible=false;
	Server2->Visible=false;
	Create->Visible=false;
	CreateL->Visible=false;
	StReport->Visible=false;
	StReportL->Visible=false;
	PReport->Visible=false;
	PReportL->Visible=false;
	Skin->Visible=false;
	Deck->Visible=false;
	Decks->Visible=false;
	Leader->Visible=false;
	Chat->Left=24;
	Msg->Left=24;
	Send->Left=288;
	SendL->Left=313;
	Chat->Left=24;
	Msg->Left=24;
	Send->Left=288;
	SendL->Left=313;
	StReport->Visible=false;
	PReport->Visible=false;
	Skin->Visible=false;
	Deck->Visible=false;
	Decks->Visible=false;
    AnsiString Me = InputBox("Your IP", "Enter your IP:","");
	Clients->Host = "25.97.96.0";
	Clients->Connect();
	Clients->Socket->WriteLn("Setup");
	Clients->Socket->WriteLn("25.95.10.244");
	Clients->Socket->Write(ASpecial);
	Clients->Socket->Write(ALook);
	for(int i=0;i<6;i++) {
		Clients->Socket->Write(hand.list[i].ID);
		Clients->Socket->Write(hand.list[i].strength);
		Clients->Socket->WriteLn(hand.list[i].position);
		Clients->Socket->WriteLn(hand.list[i].name);
	}
	Game=1;
	Clients->Disconnect();
}
void __fastcall TForm5::ExitClick(TObject *Sender)
{
	Clients->Disconnect();
	Server->Active=false;
	QDeck->Close();
	Server->Bindings->Clear();
	hand.clean();
	Application->Terminate();
}

