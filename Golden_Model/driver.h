//driver
SC_MODULE(driver){
	sc_out<bool> insert_card,language_flag, Another_OP ,enter,cancel,button0 ,button1,button2,button3,button4,button5,button6,button7,button8,button9;
    sc_out<sc_uint<16>> money_in;
    sc_out<sc_uint<2>> op_select;
    sc_out<sc_uint<64>> card_number;
    

    void drive(void){
        wait(5,SC_NS);
        card_number = 5992448333886628;
        insert_card = 1;
        wait(10,SC_NS);
        insert_card = 0;
        button3 = 1;
        wait(10,SC_NS);
        button3 = 0;
        button4 = 1;
        wait(10,SC_NS);
        button4 = 0;
        button2 = 1;
        wait(10,SC_NS);
        button2 = 0;
        button3 = 1;
        wait(10,SC_NS);
        button3 = 0;
        enter = 1;
        wait(10,SC_NS);
        enter =0;
        language_flag = 1;
        wait(10,SC_NS);
        language_flag = 0;
        op_select = 1;
        wait(20,SC_NS);
        op_select = 0;
        Another_OP = 1;
        wait(10,SC_NS);
        Another_OP = 0;
        op_select = 2;
        wait(10,SC_NS);
        op_select = 0;
        button1 = 1;
        wait(10,SC_NS);
        button1 = 0;
        button0 = 1;
        wait(30,SC_NS);
        button0 = 0;
        enter = 1;
        wait(10,SC_NS);
        enter = 0;


    }
	
	SC_CTOR(driver){
		SC_THREAD(drive);
	}
};
