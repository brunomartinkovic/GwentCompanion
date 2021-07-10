
// ******************************************************************************************* //
//                                                                                           
//                                     XML Data Binding                                      
//                                                                                           
//         Generated on: 17/05/2020 21:49:51                                                 
//       Generated from: C:\Users\Bruno\Desktop\Gwent Guide PROGRESS\Win32\Debug\decks.xml   
//   Settings stored in: C:\Users\Bruno\Desktop\Gwent Guide PROGRESS\Win32\Debug\decks.xdb   
//                                                                                           
// ******************************************************************************************* //

#ifndef   decksH
#define   decksH

#include <System.hpp>
#include <Xml.Xmldom.hpp>
#include <Xml.XMLIntf.hpp>
#include <Xml.XMLDoc.hpp>
#include <XMLNodeImp.h>
#include <Xml.xmlutil.hpp>


// Forward Decls 

__interface IXMLdecksType;
typedef System::DelphiInterface<IXMLdecksType> _di_IXMLdecksType;

// IXMLdecksType 

__interface INTERFACE_UUID("{21ADD7AA-FBB7-455F-B176-FDF7C3C9B2F1}") IXMLdecksType : public Xml::Xmlintf::IXMLNodeCollection
{
public:
public:
  // Property Accessors 
  virtual System::UnicodeString __fastcall Get_name(int Index) = 0;
  // Methods & Properties 
  virtual Xml::Xmlintf::_di_IXMLNode __fastcall Add(const System::UnicodeString name) = 0;
  virtual Xml::Xmlintf::_di_IXMLNode __fastcall Insert(const int Index, const System::UnicodeString name) = 0;
  __property System::UnicodeString name[int Index] = { read=Get_name };/* default */
};

// Forward Decls 

class TXMLdecksType;

// TXMLdecksType 

class TXMLdecksType : public Xml::Xmldoc::TXMLNodeCollection, public IXMLdecksType
{
  __IXMLNODECOLLECTION_IMPL__
protected:
  // IXMLdecksType 
  virtual System::UnicodeString __fastcall Get_name(int Index);
  virtual Xml::Xmlintf::_di_IXMLNode __fastcall Add(const System::UnicodeString name);
  virtual Xml::Xmlintf::_di_IXMLNode __fastcall Insert(const int Index, const System::UnicodeString name);
public:
  virtual void __fastcall AfterConstruction(void);
};

// Global Functions 

_di_IXMLdecksType __fastcall Getdecks(Xml::Xmlintf::_di_IXMLDocument Doc);
_di_IXMLdecksType __fastcall Getdecks(Xml::Xmldoc::TXMLDocument *Doc);
_di_IXMLdecksType __fastcall Loaddecks(const System::UnicodeString& FileName);
_di_IXMLdecksType __fastcall  Newdecks();

#define TargetNamespace ""

#endif