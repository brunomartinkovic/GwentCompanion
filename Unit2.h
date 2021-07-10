//---------------------------------------------------------------------------

#ifndef Unit2H
#define Unit2H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Xml.XMLDoc.hpp>
#include <Xml.xmldom.hpp>
#include <Xml.XMLIntf.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Imaging.jpeg.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Imaging.pngimage.hpp>
#include <Data.DB.hpp>
#include <Data.Win.ADODB.hpp>
//---------------------------------------------------------------------------
class TForm2 : public TForm
{
__published:	// IDE-managed Components
	TImage *Card1;
	TScrollBar *Scroll;
	TImage *Card2;
	TImage *Card3;
	TImage *Background;
	TImage *Card4;
	TXMLDocument *Xuser;
	TImage *Card5;
	TImage *Card6;
	TImage *Card7;
	TImage *Card8;
	TListView *Card1D;
	TListView *Card5D;
	TListView *Card6D;
	TListView *Card7D;
	TListView *Card8D;
	TListView *Card2D;
	TListView *Card3D;
	TListView *Card4D;
	TCheckBox *Hide;
	TScrollBar *ScrollS;
	TImage *HideBg;
	void __fastcall ScrollChange(TObject *Sender);
	void __fastcall HideClick(TObject *Sender);
	void __fastcall ScrollSChange(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
public:		// User declarations
	__fastcall TForm2(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm2 *Form2;
//---------------------------------------------------------------------------
#endif
