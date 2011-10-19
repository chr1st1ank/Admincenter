#include <iostream>
#include <sstream>
#include "xmlsp_dom.h"

using namespace std;


const char* xml = "<?xml version=\"1.0\"?>\n"
	"<hello v=\"1\">\n"
	" <key>&lt;Hello world&gt;</key>\n"
	" <value v1=\"1\" v2=\"2\" v3=\"3\" />\n"
	"</hello>";


string dumpAttributes(XMLSP::DOMElement* e)
{
	stringstream s;
	XMLSP::DOMStringList list = e->getAttributeList();
	XMLSP::DOMStringList::iterator i;
	for (i = list.begin(); i != list.end(); i++) {
		s<<" "<<*i<<"=\""<<e->getAttribute(*i)<<"\"";
	}
	return s.str();
}


void dumpElement(XMLSP::DOMElement* e, int depth)
{
	string p1, p2;
	XMLSP::DOMElements els;
	XMLSP::DOMElements::iterator i;


	p1.assign((depth-1)*4, ' ');
	p2.assign(depth*4, ' ');

	cout<<p1<<"[element] {"<<endl;
	cout<<p2<<"name: "<<e->getElementName()<<endl;
	if (e->attributeCount())
 		cout<<p2<<"attributes:"<<dumpAttributes(e)<<endl;


	if (e->hasChilds()) {
		cout<<p2<<"childs count: "<<e->childCount()<<endl;

		els = e->getChilds();
		for(i = els.begin(); i != els.end(); i++) {
			dumpElement(*i, depth+1);
		}
	} else if (e->getCData().size()) {
		cout<<p2<<"cdata: "<<e->getCData()<<endl;
	}


	cout<<p1<<"}"<<endl;
}


int main(int argc, char* argv[])
{
	XMLSP::DOMElement* root;
	root = XMLSP::DOMElement::loadXML(xml);
	if (root == NULL) {
		cerr<<"Failed to parse xml: "<<XMLSP::DOMElement::getLastError()<<endl;
	} else {
		cout<<"Parse OK.\n";
		dumpElement(root, 1);		
		cout<<"Deleting root... ";
		delete root;
		cout<<"done"<<endl;
	}
}



