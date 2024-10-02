#include "systemc.h"
#include "define.h"
#include <iostream>

using namespace std;

// vvvvv put your code here vvvvv
SC_MODULE( Conv1 ) {	
	sc_in_clk clk;
	sc_in < bool > rst;
	
	sc_out < bool > rom_rd;
	sc_out < sc_uint<16> > rom_addr;
	sc_in < DATA_TYPE > rom_data_out;
	
	sc_out < bool > ram_wr;
	sc_out < sc_uint<16> > ram_addr;
	sc_in < DATA_TYPE > ram_data_out;
	sc_out < DATA_TYPE > ram_data_in;
	
  sc_out<bool> pool1_en; 
  
	void run();
  
  int times,x,y,depth,ram_place,test;
  DATA_TYPE kernel[156],data[784],temp;
  MUL_DATA_TYPE calc;
	
	SC_CTOR( Conv1 )
	{
		SC_METHOD( run );
		sensitive << rst.pos() << clk.pos();
	}
};

SC_MODULE( Pool1 ) {	
	sc_in_clk clk;
	sc_in < bool > rst;
	
	sc_out < bool > rom_rd;
	sc_out < sc_uint<16> > rom_addr;
	sc_in < DATA_TYPE > rom_data_out;
	
	sc_out < bool > ram_wr;
	sc_out < sc_uint<16> > ram_addr;
	sc_in < DATA_TYPE > ram_data_out;
	sc_out < DATA_TYPE > ram_data_in;
	
  sc_in<bool> pool1_en;
  sc_out<bool> conv2_en; 
  
	void run();
  
  int times,x,y,depth,ram_place,test;
  DATA_TYPE data[3456],temp;
	
	SC_CTOR( Pool1 )
	{
		SC_METHOD( run );
		sensitive << rst.pos() << clk.pos();
	}
};

SC_MODULE( Conv2 ) {	
	sc_in_clk clk;
	sc_in < bool > rst;
	
	sc_out < bool > rom_rd;
	sc_out < sc_uint<16> > rom_addr;
	sc_in < DATA_TYPE > rom_data_out;
	
	sc_out < bool > ram_wr;
	sc_out < sc_uint<16> > ram_addr;
	sc_in < DATA_TYPE > ram_data_out;
	sc_out < DATA_TYPE > ram_data_in;
	
  sc_in<bool> conv2_en;
  sc_out<bool> pool2_en;
  
	void run();
  
  int times,x,y,depth,ram_place,test;
  DATA_TYPE kernel[2416],data[864],temp;
  MUL_DATA_TYPE calc;
	
	SC_CTOR( Conv2 )
	{
		SC_METHOD( run );
		sensitive << rst.pos() << clk.pos();
	}
};

SC_MODULE( Pool2 ) {	
	sc_in_clk clk;
	sc_in < bool > rst;
	
	sc_out < bool > rom_rd;
	sc_out < sc_uint<16> > rom_addr;
	sc_in < DATA_TYPE > rom_data_out;
	
	sc_out < bool > ram_wr;
	sc_out < sc_uint<16> > ram_addr;
	sc_in < DATA_TYPE > ram_data_out;
	sc_out < DATA_TYPE > ram_data_in;
	
  sc_in<bool> pool2_en;
  sc_out<bool> dense1_en; 
  
	void run();
  
  int times,x,y,depth,ram_place,test;
  DATA_TYPE data[1024],temp;
	
	SC_CTOR( Pool2 )
	{
		SC_METHOD( run );
		sensitive << rst.pos() << clk.pos();
	}
};

SC_MODULE( Dense1 ) {	
	sc_in_clk clk;
	sc_in < bool > rst;
	
	sc_out < bool > rom_rd;
	sc_out < sc_uint<16> > rom_addr;
	sc_in < DATA_TYPE > rom_data_out;
	
	sc_out < bool > ram_wr;
	sc_out < sc_uint<16> > ram_addr;
	sc_in < DATA_TYPE > ram_data_out;
	sc_out < DATA_TYPE > ram_data_in;
	
  sc_in<bool> dense1_en;
  sc_out<bool> dense2_en; 
  
	void run();
  
  int times,x,y,depth,ram_place,test;
  DATA_TYPE kernel[30841],data[256],temp;
  MUL_DATA_TYPE calc;
	
	SC_CTOR( Dense1 )
	{
		SC_METHOD( run );
		sensitive << rst.pos() << clk.pos();
	}
};

SC_MODULE( Dense2 ) {	
	sc_in_clk clk;
	sc_in < bool > rst;
	
	sc_out < bool > rom_rd;
	sc_out < sc_uint<16> > rom_addr;
	sc_in < DATA_TYPE > rom_data_out;
	
	sc_out < bool > ram_wr;
	sc_out < sc_uint<16> > ram_addr;
	sc_in < DATA_TYPE > ram_data_out;
	sc_out < DATA_TYPE > ram_data_in;
	
  sc_in<bool> dense2_en;
  sc_out<bool> dense3_en; 
  
	void run();
  
  int times,x,y,depth,ram_place,test;
  DATA_TYPE kernel[10165],data[120],temp;
  MUL_DATA_TYPE calc;
	
	SC_CTOR( Dense2 )
	{
		SC_METHOD( run );
		sensitive << rst.pos() << clk.pos();
	}
};

SC_MODULE( Dense3 ) {	
	sc_in_clk clk;
	sc_in < bool > rst;
	
	sc_out < bool > rom_rd;
	sc_out < sc_uint<16> > rom_addr;
	sc_in < DATA_TYPE > rom_data_out;
	
	sc_out < bool > ram_wr;
	sc_out < sc_uint<16> > ram_addr;
	sc_in < DATA_TYPE > ram_data_out;
	sc_out < DATA_TYPE > ram_data_in;
	
  sc_in<bool> dense3_en;
	sc_out < DATA_TYPE > result;
	sc_out < bool > output_valid;
  
	void run();
  
  int times,x,y,depth,ram_place,test;
  DATA_TYPE kernel[851],data[84],temp;
  MUL_DATA_TYPE calc;
	
	SC_CTOR( Dense3 )
	{
		SC_METHOD( run );
		sensitive << rst.pos() << clk.pos();
	}
};

SC_MODULE( LeNet ) {	
	sc_in_clk clk;
	sc_in < bool > rst;
	
	sc_out < bool > rom_rd;
	sc_out < sc_uint<16> > rom_addr;
	sc_in < DATA_TYPE > rom_data_out;
	
	sc_out < bool > ram_wr;
	sc_out < sc_uint<16> > ram_addr;
	sc_in < DATA_TYPE > ram_data_out;
	sc_out < DATA_TYPE > ram_data_in;
	
  sc_out < DATA_TYPE > result;
	sc_out < bool > output_valid;
	
  sc_signal<bool> pool1_en,conv2_en,pool2_en,dense1_en,dense2_en,dense3_en;
  
  Conv1* conv1;
  Pool1* pool1;
  Conv2* conv2;
  Pool2* pool2;
  Dense1* dense1;
  Dense2* dense2;
  Dense3* dense3;
  
  void run();
	
	SC_CTOR( LeNet )
	{
    conv1=new Conv1("conv1");
    pool1=new Pool1("pool1");
    conv2=new Conv2("conv2");
    pool2=new Pool2("pool2");
    dense1=new Dense1("dense1");
    dense2=new Dense2("dense2");
    dense3=new Dense3("dense3");
    
    conv1->clk(clk);
	  conv1->rst(rst);
	  conv1->rom_rd(rom_rd);
	  conv1->rom_addr(rom_addr);
	  conv1->rom_data_out(rom_data_out);
	  conv1->ram_wr(ram_wr);
	  conv1->ram_addr(ram_addr);
	  conv1->ram_data_out(ram_data_out);
	  conv1->ram_data_in(ram_data_in);
    conv1->pool1_en(pool1_en);
    
    pool1->clk(clk);
	  pool1->rst(rst);
	  pool1->rom_rd(rom_rd);
	  pool1->rom_addr(rom_addr);
	  pool1->rom_data_out(rom_data_out);
	  pool1->ram_wr(ram_wr);
	  pool1->ram_addr(ram_addr);
	  pool1->ram_data_out(ram_data_out);
	  pool1->ram_data_in(ram_data_in);
    pool1->pool1_en(pool1_en);
    pool1->conv2_en(conv2_en);
    
    conv2->clk(clk);
	  conv2->rst(rst);
	  conv2->rom_rd(rom_rd);
	  conv2->rom_addr(rom_addr);
	  conv2->rom_data_out(rom_data_out);
	  conv2->ram_wr(ram_wr);
	  conv2->ram_addr(ram_addr);
	  conv2->ram_data_out(ram_data_out);
	  conv2->ram_data_in(ram_data_in);
    conv2->conv2_en(conv2_en);
    conv2->pool2_en(pool2_en);
    
    pool2->clk(clk);
	  pool2->rst(rst);
	  pool2->rom_rd(rom_rd);
	  pool2->rom_addr(rom_addr);
	  pool2->rom_data_out(rom_data_out);
	  pool2->ram_wr(ram_wr);
	  pool2->ram_addr(ram_addr);
	  pool2->ram_data_out(ram_data_out);
	  pool2->ram_data_in(ram_data_in);
    pool2->pool2_en(pool2_en);
    pool2->dense1_en(dense1_en);
    
    dense1->clk(clk);
	  dense1->rst(rst);
	  dense1->rom_rd(rom_rd);
	  dense1->rom_addr(rom_addr);
	  dense1->rom_data_out(rom_data_out);
	  dense1->ram_wr(ram_wr);
	  dense1->ram_addr(ram_addr);
	  dense1->ram_data_out(ram_data_out);
	  dense1->ram_data_in(ram_data_in);
    dense1->dense1_en(dense1_en);
    dense1->dense2_en(dense2_en);
    
    dense2->clk(clk);
	  dense2->rst(rst);
	  dense2->rom_rd(rom_rd);
	  dense2->rom_addr(rom_addr);
	  dense2->rom_data_out(rom_data_out);
	  dense2->ram_wr(ram_wr);
	  dense2->ram_addr(ram_addr);
	  dense2->ram_data_out(ram_data_out);
	  dense2->ram_data_in(ram_data_in);
    dense2->dense2_en(dense2_en);
    dense2->dense3_en(dense3_en);
    
    dense3->clk(clk);
	  dense3->rst(rst);
	  dense3->rom_rd(rom_rd);
	  dense3->rom_addr(rom_addr);
	  dense3->rom_data_out(rom_data_out);
	  dense3->ram_wr(ram_wr);
	  dense3->ram_addr(ram_addr);
	  dense3->ram_data_out(ram_data_out);
	  dense3->ram_data_in(ram_data_in);
    dense3->dense3_en(dense3_en);
    dense3->result(result);
    dense3->output_valid(output_valid);
    
		SC_METHOD( run );
		sensitive << rst.pos() << clk.pos();
	}
};
// ^^^^^ put your code here ^^^^^
