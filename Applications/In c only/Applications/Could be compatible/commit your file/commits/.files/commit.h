#include <fstream>
#include <string>
#include <iostream>
#include <string.h>

using namespace std;

int length(int a)
{
	if (a == 0)
		return 1;

	int i=0;

	while ( a != 0 )
	{
		i=i+1;
		a=a/10;
	}

	return i;
}

// inverts a string
void invert_string( string &a )
{
	int size = a.length();

	string b = "";

	for ( int i=size-1; i>=0; i=i-1 )
		b = b + a[i];

	a = b;
}

// is numeric char
bool is_numeric( char a )
{
	if ( a >= '0' and a <= '9' )
		return true;

	return false;
}

// converts a string to a char array
void string_to_chars ( string a, char chars[] ) 
{
	int size = a.length();

	for ( int i=0; i<size; i=i+1 )
		chars[i] = a[i];
}

// converts an int to a string
string int_to_string (int a)
{
	int size = length(a);

	bool is_neg = false;
	if ( a < 0 )
	{
		is_neg = true;
		a = -a;
	}

	string result = "";

	for (int i=0; i<size; i=i+1)
	{	
		char a_char = (char) (a % 10 + 48);

		if ( is_numeric( a_char ) )
			result = result + a_char;
		a = a / 10;
	}

	if ( is_neg )
		result = result + '-';

	invert_string( result );

	return result;
}


// get copy filename
void get_copy_filename ( string &filename, string copy_string )
{
	bool verif = false;
	for ( int i=0; i<filename.length(); i=i+1 )
		if ( filename[i] == '.' )
			verif = true;

	if ( verif )
	{
		// filename 1
		string filename_1 = "";
		string filename_2 = "";
		int i=0;
		while ( filename[i] != '.' )
		{
			filename_1 = filename_1 + filename[i];
			i=i+1;
		}
		i=i+1;
		for ( int l=i; l<filename.length(); l=l+1 )
			filename_2 = filename_2 + filename[l];

		filename = filename_1 + " " + copy_string + "." + filename_2;
	}
	else
		filename = filename + " " + copy_string;

}



// file



int counter = 0;
string file = "";


// makes file that stores our counter
void make_count_file ()
{
	ofstream f;
	f.open( "commits/.files/.count" );
	f.close();
}

void get_count()
{
	fstream f;
	f.open( "commits/.files/.count" );
	f >> counter;
	f.close();
}

// increases and saves counter if "commits/.files/.count" file
void count()
{
	get_count();

	fstream f;
	make_count_file();

	f.open( "commits/.files/.count" );
	counter = counter + 1;
	f << counter;
	f.close();
}


void save_choice ( string filename )
{
	string choice;
	cout << "Want to commit? ( y / n ): ";
	cin >> choice;

	if ( choice[0] == 'y' )
	{
		fstream f;
		f.open( filename );
		string temp;
		getline( f, temp ); // to continue
		while ( getline( f, temp ) )
			file = file + temp + "\n";
		f.close();

		count();

		ofstream f_ofstream;
		get_copy_filename( filename, '(' + int_to_string( counter ) + ')' );
		f_ofstream.open( filename );
		f_ofstream << file;
		f_ofstream.close();
	}
}

void save ( string filename, int num_compilations )
{
	count();

	if ( counter % num_compilations == 0 )
	{
		fstream f;
		f.open( filename );
		string temp;
		getline( f, temp ); // to continue
		while ( getline( f, temp ) )
			file = file + temp + "\n";
		f.close();

		count();

		ofstream f_ofstream;
		get_copy_filename( filename, '(' + int_to_string( counter ) + ')' );
		f_ofstream.open( filename );
		f_ofstream << file;
		f_ofstream.close();
	}
}

void save ( string filename )
{
	count();

	if ( counter % 10 == 0 )
	{
		fstream f;
		f.open( filename );
		string temp;
		getline( f, temp ); // to continue
		while ( getline( f, temp ) )
			file = file + temp + "\n";
		f.close();

		count();

		ofstream f_ofstream;
		get_copy_filename( filename, '(' + int_to_string( counter / 10 ) + ')' );
		f_ofstream.open( "commits/" + filename );
		f_ofstream << file;
		f_ofstream.close();

		cout << "( info ) File \'" << filename << "\' was saved.\n'";
	}
}

void reset ()
{
	make_count_file();
}


