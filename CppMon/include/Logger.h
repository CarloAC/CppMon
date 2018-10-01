//Gestisce tutti i dati che devono essere condivisi a schermo con l'utente  //SCREEN
//      e il log che deve essere salvato su file                            //FILE

#ifndef LOGGER_H
#define LOGGER_H
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Logger
{
public:
    Logger(std::string name, std::ofstream * o = NULL): _name(name), _out_s(o) {}

//SCREEN
    template<class T>                                                               //1
    void msg(T msg)
    {
        std::cout << "[" << _name << "] " << msg << std::endl;
    }

    template<class T1, class T2>                                                    //2
    void msg(T1 msg, T2 data)
    {
        std::cout << "[" << _name << "] " << msg << " : " << data << std::endl;
    }


//FILE
    template<class T>                                                               //1
    void fmsg(T msg)
    {
        if (_out_s)
        {
            *_out_s << "[" << _name << "] " << msg << std::endl;
        }
    }

    template<class T1, class T2>                                                    //2
    void fmsg(T1 msg, T2 data)
    {
        if (_out_s)
        {
            *_out_s << "[" << _name << "] " << msg << " : " << data << std::endl;
        }
    }

    template<class T1, class T2, class T3, class T4>                                //4
    void fmsg(T1 msg1, T2 data1, T3 msg2, T4 data2)
    {
        if (_out_s)
        {
            *_out_s << "[" << _name << "] " << msg1 << " " << data1 << " " << msg2 << " " << data2 << std::endl;
        }
    }

    template<class T1, class T2, class T3, class T4, class T5>                      //5
    void fmsg(T1 msg1, T2 data1, T3 msg2, T4 data2, T5 msg3)
    {
        if (_out_s)
        {
            *_out_s << "[" << _name << "] " << msg1 << " " << data1 << " " << msg2 << " " << data2<< " " << msg3 << std::endl;
        }
    }

    template<class T1, class T2, class T3, class T4, class T5, class T6>            //6
    void fmsg(T1 msg1, T2 data1, T3 msg2, T4 data2, T5 msg3, T6 data3)
    {
        if (_out_s)
        {
            *_out_s << "[" << _name << "] " << msg1 << " " << data1 << " " << msg2 << " " << data2<< " " << msg3 << " " << data3 << std::endl;
        }
    }

    template<class T1, class T2, class T3, class T4, class T5, class T6, class T7>  //7
    void fmsg(T1 msg1, T2 data1, T3 msg2, T4 data2, T5 msg3, T6 data3, T7 msg4)
    {
        if (_out_s)
        {
            *_out_s << "[" << _name << "] " << msg1 << " " << data1 << " " << msg2 << " " << data2<< " " << msg3 << " " << data3<< " " << msg4 << std::endl;
        }
    }


//GETTERS
    std::ofstream *get_file()       //ptr output.log.file request
    {
        return _out_s;
    }

private:
    std::string _name;              //Player name
    std::ofstream *_out_s;          //ptr to output.log.file
};

#endif // LOGGER_H
