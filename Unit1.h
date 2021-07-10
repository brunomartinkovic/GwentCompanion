//---------------------------------------------------------------------------
#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Xml.XMLDoc.hpp>
#include <Xml.xmldom.hpp>
#include <Xml.XMLIntf.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Imaging.jpeg.hpp>
#include <Vcl.Imaging.pngimage.hpp>
#include <Data.DB.hpp>
#include <Data.Win.ADODB.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TImage *Multiplayer;
	TImage *Builder;
	TImage *CDB;
	TImage *Collection;
	TImage *WDecor;
	TImage *GDecor;
	TImage *Background;
	TLabel *MultiplayerL;
	TLabel *CDBL;
	TLabel *CollectionL;
	TLabel *BuilderL;
	void __fastcall MultiplayerClick(TObject *Sender);
	void __fastcall BuilderClick(TObject *Sender);
	void __fastcall CDBClick(TObject *Sender);
	void __fastcall CollectionClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
