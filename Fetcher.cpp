#include <iostream>
#include <pqxx/pqxx> 
#include <vector>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <fstream>
#define ARRAY_SIZE 2048

void sortingFuncAsc(std::vector<int> array);
void sortingFuncDesc(std::vector<int> array);


using namespace std;
using namespace pqxx;

char * ReturnToken()
{
	FILE * pFile;
	long lSize;
	char * buffer;
	size_t result;
	static char *s = 0;
	string PID;
	ifstream infile;
	
	/* Open pid_Process file and copy the PID into PID variable */
	infile.open ("/tmp/pid_Process.txt");
    getline(infile, PID); // Saves the line in STRING.
	cout<<PID<<'\n'; // Prints our STRING.
    infile.close();
	
	/* Store file location in fileLoc */
	string fileLoc = "/tmp/";
	fileLoc = fileLoc + PID;
	fileLoc = fileLoc + ".txt";
	
	pFile = fopen ( fileLoc.c_str() , "r" );
	if (pFile==NULL) {fputs ("File error",stderr); return s;}

	/* Obtain file size */
	fseek (pFile , 0 , SEEK_END);
	lSize = ftell (pFile);
	rewind (pFile);

	/* Allocate memory to contain the whole file */
	buffer = (char*) malloc (sizeof(char)*lSize);
	if (buffer == NULL) {fputs ("Memory error",stderr); exit (2);}

	/* Copy the file into the buffer */
	result = fread (buffer,1,lSize,pFile);
	if (result != lSize) {fputs ("Reading error",stderr); exit (3);}
	/* The whole file is now loaded in the memory buffer */

	/* Terminate */
	fclose (pFile);
	return buffer;
}

int main(int argc, char* argv[])
{
	/* Declare variables */
	char *token, *query_token, *dir_token;
	double duration1;
	vector<int> Postgres_Vector_Array;
	
	/* Start timer for analysis */
	time_t start,end;
	time (&start);
	
	/* Find the Query token and the Direction token */
	token = ReturnToken();
	query_token = strtok(token, "\n");
	dir_token = strtok(NULL, "\n");
	
	try
	{
		/* Open Database */
		connection C("dbname=postgres user=hitesh hostaddr=127.0.0.1 port=5432");
		if (C.is_open()) 
		{
			cout << "Opened database successfully: " << C.dbname() << endl;
		} 
		else 
		{
			cout << "Can't open database" << endl;
			return 1;
		}
		
		/* Create a non-transactional object. */
		nontransaction N(C);
      
		/* Execute SQL query */
		result R( N.exec( query_token ));
      
		/* List down all the records */
		for (result::const_iterator c = R.begin(); c != R.end(); ++c) 
		{
			Postgres_Vector_Array.push_back(c[0].as<int>());
		}
		printf("%s", dir_token);
		
		/* Sort the numbers on GPU */
		if (strcmp(dir_token, "ASC") == 0) /*Ascending Order*/
		{
			sortingFuncAsc(Postgres_Vector_Array);
		}
		else if (strcmp(dir_token, "DESC") == 0) /*Descending Order*/
		{
			sortingFuncDesc(Postgres_Vector_Array);
		}
		
		cout << "Sorting done successfully" << endl;
		time (&end);
		double dif = difftime (end,start);
		printf ("Elasped time for 1 Fetch, One Sort and One Copy to File opertaions is %.2lf seconds.\n", dif );
		
		/* Disconnect */
		C.disconnect ();
	}
	catch (const exception &e)
	{
		cerr << e.what() << endl;
		return 1;
	}

	return 0;
}


