// 2001-11-21 Benjamin Kosnik  <bkoz@redhat.com>

// Copyright (C) 2001, 2002, 2003 Free Software Foundation
//
// This file is part of the GNU ISO C++ Library.  This library is free
// software; you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the
// Free Software Foundation; either version 2, or (at your option)
// any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License along
// with this library; see the file COPYING.  If not, write to the Free
// Software Foundation, 59 Temple Place - Suite 330, Boston, MA 02111-1307,
// USA.

// 22.2.2.1.1  num_get members

#include <locale>
#include <sstream>
#include <testsuite_hooks.h>

void test02()
{
  using namespace std;
  typedef istreambuf_iterator<wchar_t> iterator_type;

  bool test = true;

  // basic construction
  locale loc_c = locale::classic();
  locale loc_hk("en_HK");
  locale loc_fr("fr_FR@euro");
  locale loc_de("de_DE");
  VERIFY( loc_c != loc_de );
  VERIFY( loc_hk != loc_fr );
  VERIFY( loc_hk != loc_de );
  VERIFY( loc_de != loc_fr );

  // cache the numpunct facets
  const numpunct<wchar_t>& numpunct_c = use_facet<numpunct<wchar_t> >(loc_c); 
  const numpunct<wchar_t>& numpunct_de = use_facet<numpunct<wchar_t> >(loc_de); 
  const numpunct<wchar_t>& numpunct_hk = use_facet<numpunct<wchar_t> >(loc_hk); 

  // sanity check the data is correct.
  const wstring empty;
  char c;

  bool b1 = true;
  bool b0 = false;
  long l1 = 2147483647;
  long l2 = -2147483647;
  long l;
  unsigned long ul1 = 1294967294;
  unsigned long ul2 = 0;
  unsigned long ul;
  double d1 =  1.02345e+308;
  double d2 = 3.15e-308;
  double d;
  long double ld1 = 6.630025e+4;
  long double ld2 = 0.0;
  long double ld;
  void* v;
  const void* cv = &ul2;

  // cache the num_get facet
  wistringstream iss;
  iss.imbue(loc_c);
  const num_get<wchar_t>& ng = use_facet<num_get<wchar_t> >(iss.getloc()); 
  const ios_base::iostate goodbit = ios_base::goodbit;
  const ios_base::iostate eofbit = ios_base::eofbit;
  ios_base::iostate err = ios_base::goodbit;

  // C
  // bool, more twisted examples
  iss.str(L"true ");
  iss.clear();
  iss.setf(ios_base::boolalpha);
  err = goodbit;
  ng.get(iss.rdbuf(), 0, iss, err, b0);
  VERIFY( b0 == true );
  VERIFY( err == goodbit );

  iss.str(L"false ");
  iss.clear();
  iss.setf(ios_base::boolalpha);
  err = goodbit;
  ng.get(iss.rdbuf(), 0, iss, err, b1);
  VERIFY( b1 == false );
  VERIFY( err == goodbit );

  // unsigned long, in a locale that does not group
  iss.imbue(loc_c);
  iss.str(L"1294967294");
  iss.clear();
  err = goodbit;
  ng.get(iss.rdbuf(), 0, iss, err, ul);
  VERIFY( ul == ul1);
  VERIFY( err == eofbit );

  iss.str(L"0+++++++++++++++++++");
  iss.clear();
  err = goodbit;
  ng.get(iss.rdbuf(), 0, iss, err, ul);
  VERIFY( ul == ul2);
  VERIFY( err == goodbit );

  // double
  iss.imbue(loc_c);
  iss.str(L"1.02345e+308++++++++");
  iss.clear();
  iss.width(20);
  iss.setf(ios_base::left, ios_base::adjustfield);
  err = goodbit;
  ng.get(iss.rdbuf(), 0, iss, err, d);
  VERIFY( d == d1 );
  VERIFY( err == goodbit );

  iss.str(L"+3.15e-308");
  iss.clear();
  iss.width(20);
  iss.setf(ios_base::right, ios_base::adjustfield);
  err = goodbit;
  ng.get(iss.rdbuf(), 0, iss, err, d);
  VERIFY( d == d2 );
  VERIFY( err == eofbit );
}

int main()
{
  test02();
  return 0;
}


// Kathleen Hannah, humanitarian, woman, art-thief
