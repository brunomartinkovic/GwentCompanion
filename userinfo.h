
// ********************************************************************************** //
//                                                                                  
//                                 XML Data Binding                                 
//                                                                                  
//         Generated on: 16/05/2020 14:13:19                                        
//       Generated from: C:\Users\Bruno\Desktop\Gwent Guide PROGRESS\userinfo.xml   
//   Settings stored in: C:\Users\Bruno\Desktop\Gwent Guide PROGRESS\userinfo.xdb   
//                                                                                  
// ********************************************************************************** //

#ifndef   userinfoH
#define   userinfoH

#include <System.hpp>
#include <Xml.Xmldom.hpp>
#include <Xml.XMLIntf.hpp>
#include <Xml.XMLDoc.hpp>
#include <XMLNodeImp.h>
#include <Xml.xmlutil.hpp>


// Forward Decls 

__interface IXMLcollectedType;
typedef System::DelphiInterface<IXMLcollectedType> _di_IXMLcollectedType;
__interface IXMLcardType;
typedef System::DelphiInterface<IXMLcardType> _di_IXMLcardType;

// IXMLcollectedType 

__interface INTERFACE_UUID("{CB474A1F-23E3-4442-A0CA-FBFE9170BDAB}") IXMLcollectedType : public Xml::Xmlintf::IXMLNodeCollection
{
public:
public:
  // Property Accessors 
  virtual _di_IXMLcardType __fastcall Get_card(int Index) = 0;
  // Methods & Properties 
  virtual _di_IXMLcardType __fastcall Add() = 0;
  virtual _di_IXMLcardType __fastcall Insert(const int Index) = 0;
  __property _di_IXMLcardType card[int Index] = { read=Get_card };/* default */
};

// IXMLcardType 

__interface INTERFACE_UUID("{D80C6332-3C62-457D-849E-F9979D9C05B3}") IXMLcardType : public Xml::Xmlintf::IXMLNode
{
public:
  // Property Accessors 
  virtual System::UnicodeString __fastcall Get_name() = 0;
  virtual System::UnicodeString __fastcall Get_comment() = 0;
  virtual int __fastcall Get_id() = 0;
  virtual void __fastcall Set_name(System::UnicodeString Value) = 0;
  virtual void __fastcall Set_comment(System::UnicodeString Value) = 0;
  virtual void __fastcall Set_id(int Value) = 0;
  // Methods & Properties 
  __property System::UnicodeString name = { read=Get_name, write=Set_name };
  __property System::UnicodeString comment = { read=Get_comment, write=Set_comment };
  __property int id = { read=Get_id, write=Set_id };
};

// Forward Decls 

class TXMLcollectedType;
class TXMLcardType;

// TXMLcollectedType 

class TXMLcollectedType : public Xml::Xmldoc::TXMLNodeCollection, public IXMLcollectedType
{
  __IXMLNODECOLLECTION_IMPL__
protected:
  // IXMLcollectedType 
  virtual _di_IXMLcardType __fastcall Get_card(int Index);
  virtual _di_IXMLcardType __fastcall Add();
  virtual _di_IXMLcardType __fastcall Insert(const int Index);
public:
  virtual void __fastcall AfterConstruction(void);
};

// TXMLcardType 

class TXMLcardType : public Xml::Xmldoc::TXMLNode, public IXMLcardType
{
  __IXMLNODE_IMPL__
protected:
  // IXMLcardType 
  virtual System::UnicodeString __fastcall Get_name();
  virtual System::UnicodeString __fastcall Get_comment();
  virtual int __fastcall Get_id();
  virtual void __fastcall Set_name(System::UnicodeString Value);
  virtual void __fastcall Set_comment(System::UnicodeString Value);
  virtual void __fastcall Set_id(int Value);
};

// Global Functions 

_di_IXMLcollectedType __fastcall Getcollected(Xml::Xmlintf::_di_IXMLDocument Doc);
_di_IXMLcollectedType __fastcall Getcollected(Xml::Xmldoc::TXMLDocument *Doc);
_di_IXMLcollectedType __fastcall Loadcollected(const System::UnicodeString& FileName);
_di_IXMLcollectedType __fastcall  Newcollected();

#define TargetNamespace ""

#endif