#include <systemc.h>
#include "Multiplier.h"
//#include "alu.h"

sc_signal<sc_uint<16> > multiplicand;
sc_signal<sc_uint<16> > multiplier;
sc_signal<sc_uint<16> > Q;
sc_signal<sc_uint<16> > A;
sc_signal<int> n;

/*sc_signal<sc_uint<16> > ain, bin, sum;
sc_signal<sc_uint<4> > opCode;
sc_signal<bool> ci, co, oflag, zflag, ltflag;*/

multiplication mul("MUL");

//alu adder("Adder");

void printResult()
{
	cout << "Multiplication" << endl;
	cout << multiplicand.read() << " X " << multiplier.read() << endl;
	cout << "Result: " << A.read() << " " << Q.read() << endl;
}

int sc_main(int argc, char* argv[])
{
	/*sc_clock clk("clk", 10, SC_NS, 0.5);
	sc_trace_file *ar;
	ar = sc_create_vcd_trace_file("wave");
	sc_trace(ar, multiplicand, "Multiplcand");
	sc_trace(ar, multiplier, "Multiplier");
	sc_trace(ar, A, "A");
	sc_trace(ar, Q, "Q");*/

	mul.multiplicand(multiplicand);
	mul.multiplier(multiplier);
	mul.n(n);
	mul.A(A);
	mul.Q(Q);

	multiplicand.write("0b0000000000001000");
	multiplier.write( "0b0000000000000111");
	n.write(16);
	//printResult();

	cout << "Start test cases" << endl;
	multiplicand.write("0b0000000000001101");
	multiplier.write( "0b0000000000001011");
	n.write(16);
	sc_start(100, SC_NS);
	printResult();				

	cout << "Start test cases" << endl;
	multiplicand.write("0b0000000000000100");
	multiplier.write("0b0000000000001111");
	n.write(16);
	sc_start(100, SC_NS);
	printResult();

	cout << "Start test cases" << endl;
	multiplicand.write("0b0000000000000100");
	multiplier.write("0b0000000000001111");
	n.write(16);
	sc_start(100, SC_NS);
	printResult();

	return 0;
}
