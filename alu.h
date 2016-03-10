//------------------------------------------------------------------
// Simple 4-bits adder
// 
// SystemC for VHDL engineers
// (c)www.ht-lab.com
//------------------------------------------------------------------
#ifndef ALU_H
#define ALU_H

#include <systemc.h>

SC_MODULE(alu) {
	sc_in<sc_uint<16> > ain, bin;
	sc_in<bool> ci;
	sc_in<sc_uint<4> > opALU;
	sc_out<sc_uint<16> > sum;
	sc_out<bool> co, zflag, oflag, ltflag;

	sc_uint<4> ADD = "0b0000";
	sc_uint<4> SUB = "0b0001";
	sc_uint<4> XOR = "0b0010";
	sc_uint<4> AND = "0b0011";
	sc_uint<4> OR = "0b0100";
	sc_uint<4> NOTA = "0b0101";
	sc_uint<4> SLT = "0b0110";


	bool co0, co1, co2, co3, co4, co5, co6, co7, co8, co9, co10, co11, co12, co13, co14, co15;
	sc_uint<16> sum_s;

	// 1-bit ripple carry fulladder, note the cof reference bool&
	bool fulladder(bool a, bool b, bool cif, bool& cof) {
		bool sumr;
		sumr = (a ^ b) ^ cif;
		cof = (a & b) | ((a ^ b) & cif);
		return sumr;
	}

	void p()
	{
		zflag.write(false);
		oflag.write(false);
		ltflag.write(false);
		sum.write(0);

		if (opALU.read() == ADD)
			p0(ADD);
		else if (opALU.read() == SUB)
			p0(SUB);
		else if (opALU.read() == XOR)
			p2();
		else if (opALU.read() == AND)
			p3();
		else if (opALU.read() == OR)
			p4();
		else if (opALU.read() == NOTA)
			p5();
		else if (opALU.read() == SLT)
			p6();
	}

	void p0(sc_uint<4> opCode) {
		/*cout << "Adding" << endl;
		cout << "Ain: ";
		for (int i = 15; i >= 0; i--) {
			cout << ain.read()[i];
		}
		cout << endl;
		cout << "Bin: ";
		for (int i = 15; i >= 0; i--) {
			cout << bin.read()[i];
		}
		cout << endl;*/
		sum_s[0] = fulladder(ain.read()[0], bin.read()[0] ^ opCode[0], ci.read(), co0);
		sum_s[1] = fulladder(ain.read()[1], bin.read()[1] ^ opCode[0], co0, co1);
		sum_s[2] = fulladder(ain.read()[2], bin.read()[2] ^ opCode[0], co1, co2);
		sum_s[3] = fulladder(ain.read()[3], bin.read()[3] ^ opCode[0], co2, co3);
		sum_s[4] = fulladder(ain.read()[4], bin.read()[4] ^ opCode[0], co3, co4);
		sum_s[5] = fulladder(ain.read()[5], bin.read()[5] ^ opCode[0], co4, co5);
		sum_s[6] = fulladder(ain.read()[6], bin.read()[6] ^ opCode[0], co5, co6);
		sum_s[7] = fulladder(ain.read()[7], bin.read()[7] ^ opCode[0], co6, co7);
		sum_s[8] = fulladder(ain.read()[8], bin.read()[8] ^ opCode[0], co7, co8);
		sum_s[9] = fulladder(ain.read()[9], bin.read()[9] ^ opCode[0], co8, co9);
		sum_s[10] = fulladder(ain.read()[10], bin.read()[10] ^ opCode[0], co9, co10);
		sum_s[11] = fulladder(ain.read()[11], bin.read()[11] ^ opCode[0], co10, co11);
		sum_s[12] = fulladder(ain.read()[12], bin.read()[12] ^ opCode[0], co11, co12);
		sum_s[13] = fulladder(ain.read()[13], bin.read()[13] ^ opCode[0], co12, co13);
		sum_s[14] = fulladder(ain.read()[14], bin.read()[14] ^ opCode[0], co13, co14);
		sum_s[15] = fulladder(ain.read()[15], bin.read()[15] ^ opCode[0], co14, co15);

		/*cout << "Sum_S: ";
		for (int i = 15; i >= 0; i--) {
			cout << sum_s[i];
		}
		cout << endl;*/

		sum_s += opCode[0];
		co.write(co15);

		bool isAllZero = sum_s[0] || sum_s[1] || sum_s[2] || sum_s[3]
			|| sum_s[4] || sum_s[5] || sum_s[6] || sum_s[7] || sum_s[8]
			|| sum_s[9] || sum_s[10] || sum_s[11] || sum_s[12] || sum_s[13]
			|| sum_s[14] || sum_s[14] || sum_s[15];
		sum.write(sum_s);
		zflag.write(!isAllZero);
		oflag.write(co15 == 1);
	}

	void p2()
	{
		for (int i = 0; i < 16; i++)
			sum_s[i] = ain.read()[i] ^ bin.read()[i];
		sum.write(sum_s);
	}

	void p3()
	{
		for (int i = 0; i < 16; i++)
			sum_s[i] = ain.read()[i] & bin.read()[i];
		sum.write(sum_s);
	}

	void p4()
	{
		for (int i = 0; i < 16; i++)
			sum_s[i] = (ain.read()[i] | bin.read()[i]);
		sum.write(sum_s);
	}

	void p5()
	{
		for (int i = 0; i < 16; i++)
			sum_s[i] = !ain.read()[i];
		sum.write(sum_s);
	}

	void p6()
	{
		for (int i = 15; i >= 0; i--) {
			if ((ain.read()[i] ^ bin.read()[i]) == 1) {
				ltflag.write(bin.read()[i]); break;
			}
		}
	}

	SC_CTOR(alu) {

		SC_METHOD(p);
		sensitive << ain << bin << ci << opALU;
	}
};
#endif

