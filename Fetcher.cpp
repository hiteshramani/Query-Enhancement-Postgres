#include <iostream>
#include <pqxx/pqxx> 
#include <vector>
#include <stdlib.h>
#include <string.h>
#include <ctime>
#include <time.h>

void sortingFunc(std::vector<int> array);

using namespace std;
using namespace pqxx;

char * ReturnToken()
{
	FILE * pFile;
	long lSize;
	char * buffer;
	size_t result;
	static char *s = 0;

	pFile = fopen ( "/tmp/Parsed_Query.txt" , "r" );
	if (pFile==NULL) {fputs ("File error",stderr); return s;}

	// obtain file size:
	fseek (pFile , 0 , SEEK_END);
	lSize = ftell (pFile);
	rewind (pFile);

	// allocate memory to contain the whole file:
	buffer = (char*) malloc (sizeof(char)*lSize);
	if (buffer == NULL) {fputs ("Memory error",stderr); exit (2);}

	// copy the file into the buffer:
	result = fread (buffer,1,lSize,pFile);
	if (result != lSize) {fputs ("Reading error",stderr); exit (3);}
	// the whole file is now loaded in the memory buffer. 

	// terminate
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
		
		/* Sort the numbers on GPU */
		sortingFunc(Postgres_Vector_Array);
		cout << "Sorting done successfully" << endl;
      
		time (&end);
		double dif = difftime (end,start);
		printf ("Elasped time for 2 Fetch, One Sort and One Copy to File opertaions is %.2lf seconds.\n", dif );
		
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


