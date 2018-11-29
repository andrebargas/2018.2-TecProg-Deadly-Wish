// writing on a text file
#include <iostream>
#include <fstream>
#include <string>
// #include <ctime>

using namespace std;

#define INFO_LOG_PATH "INFO_LOG.txt"
#define GLOBAL_LOG_PATH "GLOBAL_LOG.txt"
#define ERROR_LOG_PATH "ERROR_LOG.txt"

class DeadlyLog{
  public:
    static void
    init_logs(){

      ofstream error_log("ERROR_LOG.txt");
      if (error_log.is_open())
      {
        error_log << "\t***** ERROR LOG *****\n\n";
        error_log << "\tFile name";
        error_log << "\t|\t\t\t Log message\n";
        error_log.close();
      }
      ofstream global_log("GLOBAL_LOG.txt");
      if (global_log.is_open())
      {
        global_log << "\t***** GLOBAL LOG *****\n\n";
        global_log << "\tFile name";
        global_log << "\t|\t\t\t Log message\n";
        global_log.close();
      }
      ofstream info_log("INFO_LOG.txt");
      if (info_log.is_open())
      {
        info_log << "\t***** INFO LOG *****\n\n";
        info_log << "\tFile name ";
        info_log << "\t|\t\t\tLog message\n";
        info_log.close();
      }
    }
    static void
    global_log(string text, string filename){

      ofstream myfile;
      myfile.open( GLOBAL_LOG_PATH, ios_base::app);
      if (myfile.is_open())
      {
        myfile << "\t" << filename << " ";
        myfile << "\t\t\t\t\t" << text << "\n";
        myfile.close();
      }
    }
    static void
    error_log(string text, string filename){

      ofstream myfile;
      myfile.open( ERROR_LOG_PATH, ios_base::app);
      if (myfile.is_open())
      {
        myfile << "\t" << filename << " ";
        myfile << "\t\t\t\t\t" << text << "\n";
        myfile.close();
      }
    }
    static void
    info_log(string text, string filename){

      ofstream myfile;
      myfile.open( INFO_LOG_PATH, ios_base::app);
      if (myfile.is_open())
      {
        myfile << "\t" << filename << " ";
        myfile << "\t\t\t\t\t" << text << "\n";
        myfile.close();
      }
    }

    static void
    do_log(int type, string filename,  string text) {
      global_log(text, filename);
      if(type == 1)
        info_log(text, filename);
      if (type == 2) {
        error_log(text, filename);
      }
    }

};
