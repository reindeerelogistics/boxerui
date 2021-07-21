#include <vector>
#include <limits>
#include <stdlib.h>
#include <iostream>

using namespace std;

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;


template <typename t_data, typename t_max, typename t_min, typename t_zero>
class RoboCMD{
    
    private:
    //************************* Default class varriables *************************//
    const uint8_t d_zero = 0;
    const uint8_t d_min = 0;

    //************************* class varriables *************************//
    vector<uint8_t> msg_;

    //************************* Temp class varriables *************************//
    char com_ = -1;
    t_data data_ = -1;
    t_max max_ = -1;
    t_min min_ = -1;
    t_zero zero_ = -1;
    char dir_ = -1;
    //*************************//

    void clrTmp(){
        data_ = -1;
        max_ = -1;
        min_ = -1;
        zero_ = -1;
        dir_ = -1;
    }

    void format(uint8_t com, t_data data, t_max max, t_min min, t_zero zero){
        switch(com){
            case 0x00: case 0x01: case 0x02: case 0x03: case 0x04: case 0x05: // cases of form: [direction bit] [scaler]

            zero_ = zero;
            dir_ = (data>zero_)? 0:1;
            data_ = abs(data);
            max_ = max;
            min_ = min;

            break;
            case 0x06: case 0x07: case 0x08:

            zero_ = zero;
            data_ = abs(data);
            max_= max;
            min_= min;

            break;

        }//switch (com)
    }//format(uint8_t com, t_data data, t_max max, t_min min, t_zero zero)

    void genMsg(){

     vector<uint8_t> msg; 

        switch(com_){
            case -1:break;

            case 0x00 ... 0x08:

            uint16_t val;


            if(data_ == zero_){
                val = 0;

            }else if(zero_ != max_ && zero_ != min_){
                val = (data_>zero_)? abs((data_-zero_)/(max_-zero_)) : abs((data_-zero_)/(zero_-min_));
            
            }else if (zero_ == min_){
                val = abs((data_-zero_)/(max_-zero_));

            }else if (zero_ == max_){
                val = abs((data_-zero_)/(zero_-min_));

            }

            msg.push_back(com_);

                switch(com_){
                    case 0x00 ... 0x05: //Commands of form [direction] [scaler(16-bit)]
                    msg.push_back(dir_);
                    msg.push_back((uint8_t)(val>>8));
                    msg.push_back((uint8_t)(val & 0xFF));
                    break;

                    case 0x06 ... 0x07: //commands of form [scaler(16-bit)]
                    msg.push_back((uint8_t)(val>>8));
                    msg.push_back((uint8_t)(val & 0xFF));
                    break;

                    case 0x08 ... 0x08: //commands of form [scaler(8-bit)]
                    msg.push_back((uint8_t)(val));
                }//switch(com_)

            break;

        }//switch (com_)

        msg_.insert(msg_.end(), msg.begin(),msg.end());
    }//genMsg()


    public:

    RoboCMD(){

    }

    /**
     * Formats and adds "data" to command queue accorrding to format specified for "com" in RoboCMD protocol. 
     * data direction will be determined by value of "data" relative to "zero" , and scaller will be determined acording to 
     * "data" relative to "zero" and "max" or "min" (according to direction).
     * @param com the command you wish to submit
     * @param data the value you wish to send
     * @param max the max value "data" could be
     * @param min the min value "data" could be
     * @param zero the zero point, used to determine direction and convert data to absolute value and scaller
     */ 
    void set(uint8_t com, t_data data, t_max max, t_min min, t_zero zero){
        format(com, data, max, min, zero);
        genMsg();



    }//set(uint8_t com, t_data data, t_max max, t_min min, t_zero zero)

    /**
     * Formats and adds "data" to command queue accorrding to format specified for "com" in RoboCMD protocol. 
     * data direction will be determined by value of "data" relative to default "zero" value of 0 ,
     * and scaller will be determined acording to "data" relative to default "zero" value and "max" or "min" (according to direction).
     * @param com the command you wish to submit
     * @param data the value you wish to send
     * @param max the max value "data" could be
     * @param min the min value "data" could be
     */ 
    void set(uint8_t com, t_data data, t_max max, t_min min){
        format(com, data, max, min, d_zero);
        genMsg();


    }//set(uint8_t com, t_data data, t_max max, t_min min)


    /**
     * Formats and adds "data" to command queue accorrding to format specified for "com" in RoboCMD protocol. 
     * this function assumes data direction will be irelevent for the command, if a command with direction is used an error may occure.
     * scaller will be determined acording to "data" relative to default "zero" value of 0 and "max".
     * @param com the command you wish to submit
     * @param data the value you wish to send
     * @param max the max value "data" could be
     */ 
    void set(uint8_t com, t_data data, t_max max){
        format(com, data, max, d_min, d_zero);
        genMsg();

        
    }//set (uint8_t com, t_data data, t_max max)


    /**
     * Formats and adds "data" to command queue accorrding to format specified for "com" in RoboCMD protocol. 
     * data direction will be determined by value of "data" relative to default "zero" value of 0 ,
     * and scaller will be determined acording to "data" relative to default "zero" value and "data" type max or "data" type min (according to direction).
     * @param com the command you wish to submit
     * @param data the value you wish to send
     */ 
    void set(uint8_t com, t_data data){
        format(com, data, numeric_limits<t_data>::max(), numeric_limits<t_data>::min(), d_zero);
        genMsg();

        
    }//set(uint8_t com, t_data data)

    void disMsg(){
        
        cout<<"message size: "<<msg_.size()<<endl;

    for(unsigned int i = 0; i<msg_.size();i++){
        cout<< " "<<msg_.at(i);
    }
    }
};