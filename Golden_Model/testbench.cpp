//testbench for golden
#include <systemc.h>
#include "Top_ATM.h"
#include "driver.h"
// #include "monitor.h"

int sc_main(int argc, char* argv[]){
	//ports and signals
	sc_signal<bool> insert_card, language_flag, Another_OP,enter,cancel,button0 ,button1,button2,button3,button4,button5,button6,button7,button8,button9;
    sc_signal<sc_uint<16>> money_in;
    sc_signal<sc_uint<2>> op_select;
    sc_signal<sc_uint<64>> card_number;
    sc_signal<sc_uint<16>> money_out;
    sc_signal<bool> insufficient_money_account;
	sc_clock clock("clk",10,SC_NS);
    
	
	//module instances
	TOP_ATM ATM("ATM-Golden");
	driver dr("driver");
	// monitor mon("monitor");

	//clock
	ATM.clk(clock);
	
    //inputs
    ATM.insert_card(insert_card);
    ATM.language_flag(language_flag);
    ATM.Another_OP(Another_OP);
    ATM.enter(enter);
    ATM.cancel(cancel);
    ATM.button0(button0);
    ATM.button1(button1);
    ATM.button2(button2);
    ATM.button3(button3);
    ATM.button4(button4);
    ATM.button5(button5);
    ATM.button6(button6);
    ATM.button7(button7);
    ATM.button8(button8);
    ATM.button9(button9);
    ATM.money_in(money_in);
    ATM.op_select(op_select);
    ATM.card_number(card_number);

    dr.insert_card(insert_card);
    dr.language_flag(language_flag);
    dr.Another_OP(Another_OP);
    dr.enter(enter);
    dr.cancel(cancel);
    dr.button0(button0);
    dr.button1(button1);
    dr.button2(button2);
    dr.button3(button3);
    dr.button4(button4);
    dr.button5(button5);
    dr.button6(button6);
    dr.button7(button7);
    dr.button8(button8);
    dr.button9(button9);
    dr.money_in(money_in);
    dr.op_select(op_select);
    dr.card_number(card_number);

    //outputs
    ATM.money_out(money_out);
    ATM.insufficient_money_account(insufficient_money_account);

    // mon.money_out(money_out);
    // mon.insufficient_money_account(insufficient_money_account);
    // mon.insufficient_money_atm(insufficient_money_atm);
	
	//tracing
	// sc_trace_file *fp;
	// fp=sc_create_vcd_trace_file("vcd_trace");
	// fp->set_time_unit(100, SC_PS);
	
	// sc_trace(fp, s_din, "INPUT");
	// sc_trace(fp, clock, "CLK");
	// sc_trace(fp, clear, "CLR");
	// sc_trace(fp, s_dout, "OUTPUT");
	
	//simulation start
	sc_start(-1);
	// sc_close_vcd_trace_file(fp);
	return 0; //end
}
