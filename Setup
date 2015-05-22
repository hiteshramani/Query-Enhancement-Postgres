#include <iostream>
#include <pqxx/pqxx> 
#include <string.h>
#include <fstream>

using namespace std;
using namespace pqxx;

int main(int argc, char* argv[])
{
	ifstream infile;
	string PID;
	
	/* Open pid_Process file and copy the PID into PID variable */
	infile.open ("/tmp/pid_Process.txt");
    getline(infile, PID); // Saves the line in STRING.
	cout<<PID<<'\n'; // Prints our STRING.
    infile.close();
    
	string sql;
   
   try{
      connection C("dbname=postgres user=hitesh hostaddr=127.0.0.1 port=5432");
      if (C.is_open()) {
         cout << "Opened database successfully: " << C.dbname() << endl;
      } else {
         cout << "Can't open database" << endl;
         return 1;
      }
      
		string csvfileLoc = "/tmp/";
		csvfileLoc = csvfileLoc + PID;
		csvfileLoc = csvfileLoc + ".csv";
      
      ofstream outfile;
      outfile.open (csvfileLoc.c_str());
      
      /* Create SQL statement */
      sql = "CREATE FOREIGN TABLE pglog_" + PID + "(x int) SERVER pglog OPTIONS ( filename '/tmp/" + PID + ".csv', format 'csv' );";

      /* Create a non-transactional object. */
      work W(C);
      
      /* Execute SQL query */
      W.exec( sql );
      W.commit();
      cout << "Table created successfully" << endl;
      
      C.disconnect ();
   }
   catch (const std::exception &e)
   {
      cerr << e.what() << std::endl;
      return 1;
   }

   return 0;
}
