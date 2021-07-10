//---------------------------------------------------------------------------
#ifndef Unit3H
#define Unit3H
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
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Mask.hpp>
#include <Vcl.Imaging.jpeg.hpp>
#include <Xml.XMLDoc.hpp>
#include <Xml.xmldom.hpp>
#include <Xml.XMLIntf.hpp>
#include <Vcl.Imaging.pngimage.hpp>
//---------------------------------------------------------------------------
class TForm3 : public TForm
{
__published:	// IDE-managed Components
	TDBEdit *DBEdit4;
	TImage *Card;
	TImage *Background;
	TCheckBox *Hide;
	TDataSource *DCard;
	TDBGrid *DGrid;
	TADOQuery *QCard;
	TWideStringField *QCardName;
	TWideStringField *QCardPosition;
	TIntegerField *QCardStrength;
	TWideStringField *QCardFaction;
	TWideStringField *QCardSource;
	TComboBox *Faction;
	TAutoIncField *QCardID;
	TIntegerField *QCardCollected;
	TXMLDocument *Xuser;
	TADOConnection *DConnect;
	TLabel *Name;
	TLabel *Strength;
	TLabel *Position;
	TLabel *Source;
	TImage *Collect;
	TImage *All;
	TImage *Reset;
	TLabel *CollectL;
	TLabel *AllL;
	TLabel *ResetL;
	void __fastcall HideClick(TObject *Sender);
	void __fastcall FactionChange(TObject *Sender);
	void __fastcall DCardDataChange(TObject *Sender, TField *Field);
	void __fastcall CollectClick(TObject *Sender);
	void __fastcall AllClick(TObject *Sender);
	void __fastcall ResetClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
public:		// User declarations
	__fastcall TForm3(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm3 *Form3;
//---------------------------------------------------------------------------
#endif
