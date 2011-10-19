#include <iostream>
#include "xmlsp.h"

using namespace std;

class MyParser: public XMLSP::Parser
{
public:

	virtual bool on_tag_open(std::string tag_name, XMLSP::StringMap& attributes);
	virtual bool on_cdata(std::string cdata);
	virtual bool on_tag_close(std::string tag_name);
	virtual bool on_comment(std::string comment);
	virtual bool on_processing(std::string value);
	virtual bool on_doctype(std::string value);
	virtual bool on_document_begin();
	virtual bool on_document_end();
	virtual void on_error(int errno, int line, int col, std::string message);
};


bool MyParser::on_tag_open(std::string tag_name, XMLSP::StringMap& attributes)
{
	XMLSP::StringMap::iterator i;
	cout<<"<"<<tag_name;

	for(i = attributes.begin(); i != attributes.end(); i++) {
		cout<<" "<<i->first<<"=\""<<i->second<<"\"";
	}

	cout<<">\n";

	return true;
}

bool MyParser::on_cdata(std::string cdata)
{
	cout<<"CDATA: "<<cdata<<endl;
	return true;
}

bool MyParser::on_tag_close(std::string tag_name)
{
	cout<<"</"<<tag_name<<">"<<endl;
	return true;
}

bool MyParser::on_comment(std::string comment)
{
	cout<<"<!--"<<comment<<"-->"<<endl;
	return true;
}

bool MyParser::on_processing(std::string value)
{
	cout<<"<?"<<value<<"?>"<<endl;
	return true;
}

bool MyParser::on_doctype(std::string value)
{
	cout<<"<!"<<value<<">"<<endl;
	return true;
}

bool MyParser::on_document_begin()
{
	cout<<"DOCUMENT BEGIN"<<endl;
	return true;
}

bool MyParser::on_document_end()
{
	cout<<"DOCUMENT END"<<endl;
	return true;
}

void MyParser::on_error(int errno, int line, int col, std::string message)
{
	cout<<"ERROR("<<errno<<"): "<<message<<", at "<<line<<":"<<col<<endl;
}


char* xml = "<?xml version=\"1.0\"?>\n"
	"<hello v=\"1\">&lt;Hello world&gt;<!-- small comment -->\n"
	" <subtag v1=\"1\" v2=\"2\" v3=\"3\" />\n"
	"</hello>";


int main(int argc, char* argv[])
{

	MyParser p;
	string s = xml;
	if (p.parse(s)) {
		cout<<"OK."<<endl;
	} else {
		cout<<"Aborted."<<endl;
	}
}



