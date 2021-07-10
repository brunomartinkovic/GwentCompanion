
// ************************************************************************************************************************** //
//                                                                                                                          
//                                                     XML Data Binding                                                     
//                                                                                                                          
//         Generated on: 3/10/2021 10:27:19 AM                                                                              
//       Generated from: C:\Bruno\Fakultet\Završni\Gwent Guide-20210301T194706Z-001\Gwent Guide\Win32\Debug\decknames.xml   
//   Settings stored in: C:\Bruno\Fakultet\Završni\Gwent Guide-20210301T194706Z-001\Gwent Guide\Win32\Debug\decknames.xdb   
//                                                                                                                          
// ************************************************************************************************************************** //

#ifndef   decknamesH
#define   decknamesH

#include <System.hpp>
#include <Xml.Xmldom.hpp>
#include <Xml.XMLIntf.hpp>
#include <Xml.XMLDoc.hpp>
#include <XMLNodeImp.h>
#include <Xml.xmlutil.hpp>


// Forward Decls 

__interface IXMLmadeType;
typedef System::DelphiInterface<IXMLmadeType> _di_IXMLmadeType;
__interface IXMLdeckType;
typedef System::DelphiInterface<IXMLdeckType> _di_IXMLdeckType;

// IXMLmadeType 

__interface INTERFACE_UUID("{37B4922B-6B99-4198-9F3F-7F10D23FC63A}") IXMLmadeType : public Xml::Xmlintf::IXMLNodeCollection
{
public:
public:
  // Property Accessors 
  virtual _di_IXMLdeckType __fastcall Get_deck(int Index) = 0;
  // Methods & Properties 
  virtual _di_IXMLdeckType __fastcall Add() = 0;
  virtual _di_IXMLdeckType __fastcall Insert(const int Index) = 0;
  __property _di_IXMLdeckType deck[int Index] = { read=Get_deck };/* default */
};

// IXMLdeckType 

__interface INTERFACE_UUID("{D7511BF9-D837-4321-93A1-889EADF49ACC}") IXMLdeckType : public Xml::Xmlintf::IXMLNode
{
public:
  // Property Accessors 
  virtual System::UnicodeString __fastcall Get_name() = 0;
  virtual int __fastcall Get_leader() = 0;
  virtual int __fastcall Get_skin() = 0;
  virtual void __fastcall Set_name(System::UnicodeString Value) = 0;
  virtual void __fastcall Set_leader(int Value) = 0;
  virtual void __fastcall Set_skin(int Value) = 0;
  // Methods & Properties 
  __property System::UnicodeString name = { read=Get_name, write=Set_name };
  __property int leader = { read=Get_leader, write=Set_leader };
  __property int skin = { read=Get_skin, write=Set_skin };
};

// Forward Decls 

class TXMLmadeType;
class TXMLdeckType;

// TXMLmadeType 

class TXMLmadeType : public Xml::Xmldoc::TXMLNodeCollection, public IXMLmadeType
{
  __IXMLNODECOLLECTION_IMPL__
protected:
  // IXMLmadeType 
  virtual _di_IXMLdeckType __fastcall Get_deck(int Index);
  virtual _di_IXMLdeckType __fastcall Add();
  virtual _di_IXMLdeckType __fastcall Insert(const int Index);
public:
  virtual void __fastcall AfterConstruction(void);
};

// TXMLdeckType 

class TXMLdeckType : public Xml::Xmldoc::TXMLNode, public IXMLdeckType
{
  __IXMLNODE_IMPL__
protected:
  // IXMLdeckType 
  virtual System::UnicodeString __fastcall Get_name();
  virtual int __fastcall Get_leader();
  virtual int __fastcall Get_skin();
  virtual void __fastcall Set_name(System::UnicodeString Value);
  virtual void __fastcall Set_leader(int Value);
  virtual void __fastcall Set_skin(int Value);
};

// Global Functions 

_di_IXMLmadeType __fastcall Getmade(Xml::Xmlintf::_di_IXMLDocument Doc);
_di_IXMLmadeType __fastcall Getmade(Xml::Xmldoc::TXMLDocument *Doc);
_di_IXMLmadeType __fastcall Loadmade(const System::UnicodeString& FileName);
_di_IXMLmadeType __fastcall  Newmade();

#define TargetNamespace ""

#endif