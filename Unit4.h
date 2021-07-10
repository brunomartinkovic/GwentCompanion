//---------------------------------------------------------------------------

#ifndef Unit4H
#define Unit4H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Data.DB.hpp>
#include <Data.Win.ADODB.hpp>
#include <Vcl.DBGrids.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.DBCtrls.hpp>
#include <Vcl.CheckLst.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Xml.XMLDoc.hpp>
#include <Xml.xmldom.hpp>
#include <Xml.XMLIntf.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Imaging.jpeg.hpp>
#include <Vcl.Imaging.pngimage.hpp>
//---------------------------------------------------------------------------
class TForm4 : public TForm
{
__published:	// IDE-managed Components
	TADOQuery *QCard;
	TDataSource *DCard;
	TComboBox *Factions;
	TDBGrid *DGrid;
	TCheckListBox *CardList;
	TDataSource *DDeck;
	TADOQuery *QDeck;
	TAutoIncField *QDeckID;
	TWideStringField *QDeckName;
	TIntegerField *QDeckStrength;
	TListView *DeckDetail;
	TXMLDocument *Xuser;
	TComboBox *Decks;
	TWideStringField *QDeckPlace;
	TADOConnection *DConnect;
	TImage *Background;
	TImage *Leader;
	TImage *Skin;
	TCheckBox *All;
	TImage *DLeader;
	TImage *DSkin;
	TImage *CreateD;
	TImage *AddS;
	TImage *StReport;
	TImage *PReport;
	TImage *Delete;
	TLabel *CreateDL;
	TLabel *AddSL;
	TLabel *StReportL;
	TLabel *PReportL;
	TLabel *DeleteL;
	void __fastcall FactionsChange(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall DecksChange(TObject *Sender);
	void __fastcall AllClick(TObject *Sender);
	void __fastcall CreateDClick(TObject *Sender);
	void __fastcall AddSClick(TObject *Sender);
	void __fastcall StReportClick(TObject *Sender);
	void __fastcall PReportClick(TObject *Sender);
	void __fastcall DeleteClick(TObject *Sender);


private:	// User declarations
public:		// User declarations
	__fastcall TForm4(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm4 *Form4;
//---------------------------------------------------------------------------
#endif
