
// ********************************************************************************* //
//                                                                                 
//                                XML Data Binding                                 
//                                                                                 
//         Generated on: 19/05/2020 01:48:12                                       
//       Generated from: C:\Users\Bruno\Desktop\Gwent Guide\Win32\Debug\lang.xml   
//   Settings stored in: C:\Users\Bruno\Desktop\Gwent Guide\Win32\Debug\lang.xdb   
//                                                                                 
// ********************************************************************************* //

#ifndef   langH
#define   langH

#include <System.hpp>
#include <Xml.Xmldom.hpp>
#include <Xml.XMLIntf.hpp>
#include <Xml.XMLDoc.hpp>
#include <XMLNodeImp.h>
#include <Xml.xmlutil.hpp>


// Forward Decls 

__interface IXMLlanguageType;
typedef System::DelphiInterface<IXMLlanguageType> _di_IXMLlanguageType;

// IXMLlanguageType 

__interface INTERFACE_UUID("{3D7B9EF5-55D4-4CE3-9542-5F0756ACA063}") IXMLlanguageType : public Xml::Xmlintf::IXMLNode
{
public:
  // Property Accessors 
  virtual int __fastcall Get_jezik() = 0;
  virtual void __fastcall Set_jezik(int Value) = 0;
  // Methods & Properties 
  __property int jezik = { read=Get_jezik, write=Set_jezik };
};

// Forward Decls 

class TXMLlanguageType;

// TXMLlanguageType 

class TXMLlanguageType : public Xml::Xmldoc::TXMLNode, public IXMLlanguageType
{
  __IXMLNODE_IMPL__
protected:
  // IXMLlanguageType 
  virtual int __fastcall Get_jezik();
  virtual void __fastcall Set_jezik(int Value);
};

// Global Functions 

_di_IXMLlanguageType __fastcall Getlanguage(Xml::Xmlintf::_di_IXMLDocument Doc);
_di_IXMLlanguageType __fastcall Getlanguage(Xml::Xmldoc::TXMLDocument *Doc);
_di_IXMLlanguageType __fastcall Loadlanguage(const System::UnicodeString& FileName);
_di_IXMLlanguageType __fastcall  Newlanguage();

#define TargetNamespace ""

#endif