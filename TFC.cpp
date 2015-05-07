#include <iostream>
#include <pqxx/pqxx> 

using namespace std;
using namespace pqxx;

int main(int argc, char* argv[])
{
   char * sql;
   
   try{
      connection C("dbname=postgres user=hitesh hostaddr=127.0.0.1 port=5432");
      
      /* Create SQL statement */
      sql = "SELECT pg_backend_pid()";

      /* Create a non-transactional object. */
      nontransaction N(C);
      
      /* Execute SQL query */
      result R( N.exec( sql ));
      
      /* List down all the records */
      for (result::const_iterator c = R.begin(); c != R.end(); ++c) 
      {
         cout << c[0].as<int>() << endl;
      }
      C.disconnect ();
   }
   catch (const std::exception &e)
   {
      cerr << e.what() << std::endl;
      return 1;
   }

   return 0;
}
