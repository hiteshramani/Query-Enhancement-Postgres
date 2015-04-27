#include <iostream>
#include <pqxx/pqxx> 
#include <vector>
#include <stdlib.h>
#include <string.h>

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

	pFile = fopen ( "/home/hitesh/Desktop/Project/Project_Final_Work/Parsed_Query.txt" , "rb" );
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
	char *token;
	//char *query_token;
	char *dir_token;
	std::vector<int> myArray(20000010);
	char * sql;
	int counter = 0;
	
	token = ReturnToken();
	//query_token = strtok(token, "\n");
	dir_token = strtok(NULL, "\n");
	//printf("%s",query_token);
	
	try{
      connection C("dbname=postgres user=postgres hostaddr=127.0.0.1 port=5432");
      if (C.is_open()) {
         cout << "Opened database successfully: " << C.dbname() << endl;
         //printf("%s",query_token);
      } else {
         cout << "Can't open database" << endl;
         return 1;
      }
      //printf("%s",query_token);
      /* Create SQL statement */
      
		sql = strtok(token,"\n");
      //token = ReturnToken();
	//query_token = strtok(token, "\n");
	//dir_token = strtok(NULL, "\n");
      printf("%s",sql);

      /* Create a non-transactional object. */
      nontransaction N(C);
      
      /* Execute SQL query */
      result R( N.exec( sql ));
      
      /* List down all the records */
      for (result::const_iterator c = R.begin(); c != R.end(); ++c) {
		 myArray[counter] = c[0].as<int>();
		 //cout << myArray[counter] << "\n";
		 counter++;
         //cout << "ID = " << c[0].as<int>() << endl;
         //cout << "Name = " << c[1].as<string>() << endl;
         //cout << "Age = " << c[2].as<int>() << endl;
         //cout << "Address = " << c[3].as<string>() << endl;
         //cout << "Salary = " << c[4].as<float>() << endl;
      }
      
     /* for(int j=0;j<9;j++)
      {
		cout << myArray[j] << "\n";
      }*/
      sortingFunc(myArray);
      cout << "sorting done successfully" << endl;
      
      C.disconnect ();
   }catch (const std::exception &e){
      cerr << e.what() << std::endl;
      return 1;
   }

   return 0;
}


