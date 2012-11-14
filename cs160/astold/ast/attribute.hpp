#ifndef ATTRIBUTE_HPP
#define ATTRIBUTE_HPP

enum Basetype
{
	bt_undef,
	bt_integer,
	bt_boolean,
	bt_function,
	bt_intarray
};


class Attribute
{
  public:
  Basetype m_basetype; //type of the subtree
  int lineno; //line number on which that ast node resides

  Attribute() { 
	m_basetype = bt_undef;
	lineno = 0;
  }
};

#endif //ATTRIBUTE_HPP

