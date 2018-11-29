// writing on a text file
#include <iostream>
#include <fstream>
#include <string>
// #include <ctime>

using namespace std;

#define INFO_LOG_PATH "../logs/INFO_LOG.txt"
#define GLOBAL_LOG_PATH "../logs/GLOBAL_LOG.txt"
#define ERROR_LOG_PATH "../logs/ERROR_LOG.txt"

class DeadlyLog{
  private:
    string filename;
  public:
    DeadlyLog(string file_name):filename(file_name){

    }
    ~DeadlyLog();

    void
    init_logs(){

      ofstream error_log("ERROR_LOG.txt");
      if (error_log.is_open())
      {
        error_log << "ERROR LOG\n";
      }
      ofstream global_log("GLOBAL_LOG.txt");
      if (global_log.is_open())
      {
        global_log << "GLOBAL\n";
      }
      ofstream info_log("INFO_LOG.txt");
      if (info_log.is_open())
      {
        info_log << "INFO LOG\n";
      }
    }
    void
    global_log(string text){

      ofstream myfile;
      myfile.open( GLOBAL_LOG_PATH, ios_base::app);
      if (myfile.is_open())
      {
        myfile << filename << " ";
        myfile << text;
        myfile.close();
      }
    }
    void
    error_log(string text){

      ofstream myfile;
      myfile.open( ERROR_LOG_PATH, ios_base::app);
      if (myfile.is_open())
      {
        myfile << filename << " ";
        myfile << text;
        myfile.close();
      }
    }
    void
    info_log(string text){

      ofstream myfile;
      myfile.open( INFO_LOG_PATH, ios_base::app);
      if (myfile.is_open())
      {
        myfile << filename << " ";
        myfile << text;
        myfile.close();
      }
    }

    void
    do_log(int type, string text) {
      global_log(text);
      if(type == 1)
        info_log(text);
      if (type == 2) {
        error_log(text);
      }
    }

};
