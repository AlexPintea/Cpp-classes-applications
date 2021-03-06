#include <fstream>
#include <string>
#include <iostream>
#include <string.h>

using namespace std;

// cpp to h filename
string make_filename ( string a )
{
	string filename = "";

	for ( int i=0; i<a.length(); i=i+1 )
	{
		if ( a[i] == '.' )
			break;

		filename = filename + a[i];
	}

	return filename + ".h";
}

// checks for main
bool is_main ( string a )
{
	bool is_main_name;
	int main_iter;

	// check for main
	if ( a.length() >= 7 )
		for ( int i=0; i<a.length() - 3; i=i+1 )
			if ( a[i] == ' ' and a[i+1] == 'm' and a[i+2] == 'a' and a[i+3] == 'i' and a[i+4] == 'n' and a[i+5] == ' ' )
			{
				is_main_name = true;
				main_iter = i;
			}

	if ( is_main_name == false )
		return false;

	for ( int i=0; i<main_iter-1; i=i+1 )
		if ( a[i] == '/' and a[i+1] == '/' )
			return false;

	return true;	
}


// checks if a string is a subprogram header
bool is_subprogram ( string a )
{
	int brackets = 0;

	for ( int i=0; i<a.length(); i=i+1 )
		if ( a[i] == '(' or a[i] == ')' )
			brackets = brackets + 1;

	if ( brackets < 2 )
		return false;

	if ( is_main( a ) )
		return false;

	string type = "";

	for ( int i=0; i<a.length(); i=i+1 )
	{
		if ( a[i] == ' ' )
			break;

		type = type + a[i];
	}


	if ( type == "int" or type == "long" or type == "double" or type == "float" or type == "char" or type == "bool" or type == "string" or type == "void" )
		return true;

	return false;
}


// makes header file
void make_header_file ( string filename )
{
	ofstream file;

	file.open( make_filename( filename ) );
	file << "#include \"" << filename << "\"\n\n";

	ifstream fi;
	fi.open( filename );

	string temp;
	while ( getline( fi, temp ) )
		if ( is_subprogram( temp ) )
		{

			if ( temp[ temp.length() - 1 ] == '{' )
				temp[ temp.length() - 1 ] = '\0';
			temp = temp + ";";

			file << temp << "\n\n";
		}

	file.close();
	fi.close();


}


int main ()
{

	string filename;
	cout << "Filename ( with .cpp ): ";
	getline( cin, filename );

	make_header_file( filename );

	return 0;
}
