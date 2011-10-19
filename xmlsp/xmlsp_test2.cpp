#include <iostream>
#include <sstream>
#include <fstream>
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
	cout<<"CDATA (in "<<get_tag()<<"): "<<cdata<<endl;
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


int main(int argc, char* argv[])
{
	MyParser p;
	ifstream is;
	string xml;
	string chunk;
	char buff[64];
	int len;
	

	// disable CDATA composed of whitespaces
	p.set_skip_whitespaces(true);
	
	// check if one (only one) file name given
	if (argc != 2) {
		cout<<"usage: xmlsp_test2 xml_file_to_parse"<<endl;
		return 0;
	}	

	// open input file
	is.open(argv[1]);
	if (!is) {
		cerr<<"File \""<<argv[1]<<"\" can not be opened"<<endl;
		return 1;
	}

	// begin parsing
	if (!p.begin()) {
		cerr<<"Failed to initialize parser"<<endl;
		return 1;
	}

	// first parse use chunks
	cout<<"Parsing \""<<argv[1]<<"\" as stream:"<<endl;

	// read chunks, parse them, and save for one chunk parse
	while (!is.eof() && is.good()) {
		// read file
		is.read(buff, 64);
		len = is.gcount();
		xml.append(buff, len);
		chunk.assign(buff, len);

		// try to parse
		if (p.parse_chunk(chunk) == false) {
			cout<<"Failed to parse chunk"<<endl;
			is.close();
			return 1;
		}
	}


	if (is.bad()) {
		cerr<<"Reading file failed"<<endl;
		is.close();
		return 1;
	}

	is.close();

	if (!p.end()) {
		cerr<<"Failed to finalize parsing"<<endl;
		return 1;
	}
	

	cout<<"Parse 1 finished"<<endl<<endl<<endl;

	cout<<"Parsing \""<<argv[1]<<"\" as single chunk:"<<endl;
	if (p.parse(xml)) {
		cout<<"Parse 2 finished"<<endl;
	} else {
		cerr<<"Failed to parse xml file"<<endl;
	}
}



