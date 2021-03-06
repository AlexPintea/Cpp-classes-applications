#include <string.h>
#include <stdio.h>



// length of a string
int length( char word[] )
{
	int	length = 0;
	while ( word[ length ] )
		length = length + 1;

	return length;
}


// gets a file through filename
void get_file ( char filename[], char file[] )
{
	FILE* fi = fopen( filename, "r");

	// gets in file_temp, to make sure size is valid
	char file_temp[1000] = {0};

	char c; // char in which we input file data
	int iter = 0;
	while ( ( c = fgetc(fi) ) != EOF ) // check for EOF
	{
		file_temp[iter] = c;
		iter = iter + 1;
	}

	strcpy( file, file_temp );

	fclose( fi );
}

// sets a file through filename
void set_file ( char filename[], char file[] )
{
	FILE* fo = fopen( filename, "w");

	fprintf( fo, "%s", file );

	fclose( fo );
}

// adds to a file through filename
void add_to_file ( char filename[], char add[] )
{
	char file_temp[1000] = {0};
	get_file ( filename, file_temp );


	FILE* fo = fopen( filename, "w");

	fprintf( fo, "%s", file_temp );
	fprintf( fo, "%s", add );

	fclose( fo );
}

int main ()
{

	char filename[1000] = {0};
	strcpy( filename, "file" );
	char file_9[1000] = {0};
	strcpy ( file_9, "this is a file is\n\n\nthis is a\n\nfile\n" );
	set_file ( filename, file_9 );


	char file[1000] = {0};
	get_file ( filename, file );
	printf( "%s", file );


	char file_1[1000] = {0};
	strcpy( file_1, "a\n\n\nfile" );
	set_file( filename, file_1 );


	char add[1000] = {0};
	strcpy( add, "\nadded" );
	add_to_file( filename, add );


	return 0;
}
