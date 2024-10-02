#include "RAM.h"

void RAM::read_data() {
	if ( wr.read() )
		{
      data_out = mem[addr.read()];
      //for(int i=0;i<=3456;i++) cout<<mem[i]<<endl;
    }
}

void RAM::write_data() {
	if ( !wr.read() )
		mem[addr.read()] = data_in;
}



