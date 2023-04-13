//ATM PRoject Golden Reference
#include <systemc.h>
#include <cmath>
#include <string>
#include <vector>
using namespace std;

enum States {
  InsertCard,
  CheckButtons,
  LanguageUsed,
  CheckOperation,
  Operation1,
  Operation2,
  Operation3,
  AnotherOp
};

enum Buttons {
  Button0,
  Button1,
  Button2,
  Button3,
  Button4,
  Button5,
  Button6,
  Button7,
  Button8,
  Button9,
  NoButtonPressed,
  Enter,
  Cancel
};

typedef unsigned char uint8_t;
typedef unsigned int uint32_t;   
/*****************************/
/****************************/
//withdraw balance
void withdraw_money(const string& filename, const uint64_t& numToSearch, uint16_t money_left)
{
    ifstream file(filename); // Open input file in read mode
    vector<string> lines; // Store lines in memory

    if (file.is_open()) // Check if file is opened successfully
    {
        string line;
        while (getline(file, line)) // Read lines from the file
        {
            istringstream iss(line);
            string numString;
            string balanceString;
            getline(iss, numString, ',');

            uint64_t num = stoll(numString); // Convert the first number to uint64_t
            if (num == numToSearch) // Compare with the number to search
            {
                vector<string> fields; // Store fields in a vector

                // Split line into fields using commas as delimiter
                size_t pos = 0;
                string field;
                while ((pos = line.find(',')) != string::npos) {
                    field = line.substr(0, pos);
                    fields.push_back(field);
                    line.erase(0, pos + 1);
                }
                fields.push_back(line); // Last field after the last comma

                if (fields.size() >= 3) { // Modify the third field (data3)
                    fields[2] = to_string(money_left); // Replace with new value
                }

                // Join the fields back into a line
                line = fields[0];
                for (size_t i = 1; i < fields.size(); ++i) {
                    line += ',' + fields[i];
                }
            }
            lines.push_back(line); // Store the line in memory
        }
        file.close(); // Close the file

        // Write entire contents of the file back to disk
        ofstream outfile(filename, ios::out | ios::trunc);
        if (outfile.is_open()) {
            for (const auto& l : lines) {
                outfile << l << endl;
            }
            outfile.close(); // Close the output file
        } else {
            cout << "Failed to open file for writing." << endl;
        }
    } else {
        cout << "Failed to open file for reading." << endl;
    }
}


/*****************************/
/****************************/






bool is_pass_correct(const string& filename,const uint16_t& card_password ,const uint64_t& numToSearch)
{
    ifstream file(filename); // Open the file for reading

    if (file.is_open()) // Check if file is opened successfully
    {
        string line;
        while (getline(file, line)) // Read lines from the file
        {
            istringstream iss(line);
            string numString;
            string pinString;
            getline(iss, numString, ','); // Split the line by commas
            getline(iss, pinString, ','); //get the pass

            uint64_t num = stoll(numString); // Convert the first number to uint64_t
            uint16_t pin = stoll(pinString);
            if (num == numToSearch) // Compare with the number to search
            {
                if(pin == card_password){
                    cout<<"card passowrd is true\n";
                    return true; // Return true if found
                }
                else{
                    cout<<"card password is incorrect\n";
                    return false; //return false if incorrect
                }
                file.close(); // Close the file
            }
        }
        file.close(); // Close the file
    }
    cout<<"card is not found\n";
    return false; // Return false if not found or file not opened
}
//-------------------------------------------------------------------------
//check balance function
uint16_t check_balance(const string& filename, const uint64_t& numToSearch)
{
    ifstream file(filename); // Open the file for reading

    if (file.is_open()) // Check if file is opened successfully
    {
        string line;
        while (getline(file, line)) // Read lines from the file
        {
            istringstream iss(line);
            string numString;
            string balanceString;
            getline(iss, numString, ',');
            getline(iss, balanceString, ','); 
            getline(iss, balanceString, ',');

            uint64_t num = stoll(numString); // Convert the first number to uint64_t
            uint16_t balance = stoll(balanceString);
            if (num == numToSearch) // Compare with the number to search
            {
                file.close(); // Close the file
                return balance;
            }
        }
        file.close(); // Close the file
    }
    return 0;
}

//----------------------------------------------------------------------------------
//withdraw balance
void withdraw_money(const string& filename, const uint64_t& numToSearch, uint16_t money_left)
{
    ifstream file(filename); // Open input file in read mode
    vector<string> lines; // Store lines in memory

    if (file.is_open()) // Check if file is opened successfully
    {
        string line;
        while (getline(file, line)) // Read lines from the file
        {
            istringstream iss(line);
            string numString;
            string balanceString;
            getline(iss, numString, ',');

            uint64_t num = stoll(numString); // Convert the first number to uint64_t
            if (num == numToSearch) // Compare with the number to search
            {
                vector<string> fields; // Store fields in a vector

                // Split line into fields using commas as delimiter
                size_t pos = 0;
                string field;
                while ((pos = line.find(',')) != string::npos) {
                    field = line.substr(0, pos);
                    fields.push_back(field);
                    line.erase(0, pos + 1);
                }
                fields.push_back(line); // Last field after the last comma

                if (fields.size() >= 3) { // Modify the third field (data3)
                    fields[2] = to_string(money_left); // Replace with new value
                }

                // Join the fields back into a line
                line = fields[0];
                for (size_t i = 1; i < fields.size(); ++i) {
                    line += ',' + fields[i];
                }
            }
            lines.push_back(line); // Store the line in memory
        }
        file.close(); // Close the file

        // Write entire contents of the file back to disk
        ofstream outfile(filename, ios::out | ios::trunc);
        if (outfile.is_open()) {
            for (const auto& l : lines) {
                outfile << l << endl;
            }
            outfile.close(); // Close the output file
        } else {
            cout << "Failed to open file for writing." << endl;
        }
    } else {
        cout << "Failed to open file for reading." << endl;
    }
}



SC_MODULE(TOP_ATM){
    sc_in<bool> clk, insert_card, Another_OP,language_flag,enter,cancel,button0 ,button1,button2,button3,button4,button5,button6,button7,button8,button9;
    sc_in<sc_uint<16>> money_in;
    sc_in<sc_uint<2>> op_select;
    sc_in<sc_uint<64>> card_number;
    sc_out<sc_uint<16>> money_out;
    sc_out<bool> insufficient_money_account;
    sc_out<bool> write_language, write_money, write_password, select_operation;
    //sc_out<bool> insufficient_money_atm;
    sc_out<bool> card_out;

    // Created the signals
  	sc_signal<States> state;
    sc_signal<sc_uint<16>> pass;
    int count1 ,count2;
    uint64_t card_num_temp;
    Buttons temp;
    uint16_t pass_temp;
    uint16_t balance;
    uint16_t money_wanted;
    int     sum;
    bool    pass_correct;

    void check_which_button(void){
        sum = button0+button1+button2+button3+button4+button5+button6+button7+button8+button9;
        if(sum > 1){
            return;
        }
        if(button0 == 1){
            cout<<"at "<<sc_time_stamp()<<" BUTTON 0 is pressed\n";
            temp = Button0;
        }
        else if(button1 == 1){
            cout<<"at "<<sc_time_stamp()<<" BUTTON 1 is pressed\n";
            temp = Button1;
        }
        else if(button2 == 1){
            cout<<"at "<<sc_time_stamp()<<" BUTTON 2 is pressed\n";
            temp = Button2;
        }
        else if(button3 == 1){
            cout<<"at "<<sc_time_stamp()<<" BUTTON 3 is pressed\n";
            temp = Button3;
        }
        else if(button4 == 1){
            cout<<"at "<<sc_time_stamp()<<" BUTTON 4 is pressed\n";
            temp = Button4;
        }
        else if(button5 == 1){
            cout<<"at "<<sc_time_stamp()<<" BUTTON 5 is pressed\n";
            temp = Button5;
        }
        else if(button6 == 1){
            cout<<"at "<<sc_time_stamp()<<" BUTTON 6 is pressed\n";
            temp = Button6;
        }
        else if(button7 == 1){
            cout<<"at "<<sc_time_stamp()<<" BUTTON 7 is pressed\n";
            temp = Button7;
        }
        else if(button8 == 1){
            cout<<"at "<<sc_time_stamp()<<" BUTTON 8 is pressed\n";
            temp = Button8;
        }
        else if(button9 == 1){
            cout<<"at "<<sc_time_stamp()<<" BUTTON 9 is pressed\n";
            temp = Button9;
        }
        else if(enter == 1){
            cout<<"at "<<sc_time_stamp()<<" Enter is pressed\n";
            temp = Enter;
        }
        else if(cancel ==1){
            cout<<"at "<<sc_time_stamp()<<" cancel is pressed\n";
            temp = Cancel;
        }
        else{
            cout<<"at "<<sc_time_stamp()<<" waiting for a Button to be pressed\n";
            temp = NoButtonPressed;
        } 
    }

    void ATM_Process(void){
        switch(state){
            case InsertCard:
                if(insert_card == 1){
                    cout<<"at "<<sc_time_stamp()<<" card inserted \n";
                    card_num_temp = card_number.read();
                    state = CheckButtons;
                    count1 = 0;
                    count2 = 0;
                    money_wanted = 0;
                    pass_temp = 0;
                    return;
                }
                else{
                    state = InsertCard;
                    return;
                }
            case CheckButtons:
                if(count1 < 32){
                    count1 = count1+1;
                    if(temp != NoButtonPressed && temp != Enter && temp != Cancel){
                        pass_temp = pass_temp + pow(10,(4-count2-1))*temp;
                        cout<<pass_temp<<"\n";
                        count2 = count2+1;
                        return;
                    } 
                    else if(temp == Cancel){
                        state = InsertCard;
                        pass_temp = 0;
                        count1 = 0;
                        count2 = 0;
                        cout<<pass_temp<<"\n";
                        
                    }
                    else if(temp == Enter){
                        //cout<<pass_temp<<"\n";
                        pass.write(pass_temp);
                        count1 = 0;
                        count2 = 0;
                        //check for password
                        pass_correct = is_pass_correct("numbers.txt",pass_temp,card_num_temp);
                        if(pass_correct){
                            state = LanguageUsed;
                        }
                        else{
                            state = InsertCard;
                        }
                        return;
                    }
                }
                else{
                    cout<<pass_temp<<"\n";
                    count1 = 0;
                    count2 = 0;
                    pass_temp = 0;
                    state = InsertCard;
                    cout<<"at "<<sc_time_stamp()<<" Timeout for password collecting\n";
                    return;
                }
            case LanguageUsed:
                if(count1 < 32){
                    if(language_flag){
                        state = CheckOperation;
                        count1=0;
                    }
                    count1 = count1 + 1;
                    return;
                }
                else{
                    state = InsertCard;
                    count1=0;
                    return;
                }
            case CheckOperation:
                if(count1 <32){
                    count1 = count1+1;
                    if(op_select.read() != 0){
                        if(op_select.read() == 1){
                            state = Operation1;
                            cout<<"at "<<sc_time_stamp()<<" check Balance operation selected\n";
                        }
                        else if(op_select.read() == 2){
                            state = Operation2;
                            cout<<"at "<<sc_time_stamp()<<" withdraw operation selected\n";
                        }
                        else{
                            state = InsertCard;
                            cout<<"at "<<sc_time_stamp()<<" deposit operation selected\n";
                        }
                        count1 = 0;
                        return;
                    }
                    return;
                }
                else{
                    state = InsertCard;
                    count1 = 0;
                    return;
                }


            case Operation1:
                balance = check_balance("numbers.txt", card_num_temp);
                cout<<"at "<<sc_time_stamp()<<" balance is checked and it is equivalent to the following "<<balance<<" Egyptian pounds\n";
                state = AnotherOp;
                return;


            case Operation2:
                if(count1 < 32){
                    count1 = count1+1;
                    if(temp != NoButtonPressed && temp != Enter && temp != Cancel){
                        money_wanted = 10*money_wanted + temp;
                        cout<<money_wanted<<" yep\n";
                        return;
                    } 
                    else if(temp == Cancel){
                        state = InsertCard;
                        money_wanted = 0;
                        count1 = 0;
                        cout<<money_wanted<<"\n";
                        return;
                        
                    }
                    else if(temp == Enter){
                        balance = check_balance("numbers.txt", card_num_temp);
                        if(money_wanted <= balance) {
                            withdraw_money("numbers.txt", card_num_temp,balance-money_wanted);
                            money_out.write(money_wanted);
                        }
                        else{
                            cout<<"at "<<sc_time_stamp()<<" insuffcient ammount in Balance!!"<<endl;
                        }
                        count1 = 0;
                        state = AnotherOp;
                        return;
                    }
                }
                else{
                    cout<<money_wanted<<"\n";
                    count1 = 0;
                    money_wanted = 0;
                    state = InsertCard;
                    cout<<"at "<<sc_time_stamp()<<" Timeout for password collecting\n";
                    return;
                }
            case AnotherOp:
                if(Another_OP.read() == 1){
                    cout<<"at "<<sc_time_stamp()<<" user checked for another operation \n";
                    state = CheckOperation;
                }
                else{
                    cout<<"at "<<sc_time_stamp()<<" user ended the operations \n";
                    state = InsertCard; 
                }
                
        }

    }
    void monitor_pass(void){
        cout<<"at "<<sc_time_stamp()<<" password is collected and it is as following "<<pass.read()<<"\n";

    }
    void monitor_money(void){
        cout<<"at "<<sc_time_stamp()<<" money is coming out and it is equal to "<<money_out.read()<<"\n";
    }
    SC_CTOR(TOP_ATM)        
  {
    SC_METHOD(ATM_Process); 
    sensitive << clk.pos();
    SC_METHOD(check_which_button); 
    sensitive <<button0<<button1<<button2<<button3<<button4<<button5<<button6<<button7<<button8<<button9;
    SC_METHOD(monitor_pass);
    sensitive <<pass;
    SC_METHOD(monitor_money);
    sensitive <<money_out;
  }      
};
