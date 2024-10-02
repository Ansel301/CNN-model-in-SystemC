#include "LeNet.h"
// vvvvv put your code here vvvvv
void LeNet::run() {
  if(rst)
  {
    rom_rd=0;
    rom_addr=0;
    ram_wr=0;
    ram_addr=0;
    ram_data_in=0;
  }
}


void Conv1::run() {
  if(rst)
  {
    x=0;
    y=0;
    times=0;
    depth=1;
    test=1;
    ram_place=0;
    rom_rd=0;
    rom_addr=0;
    ram_wr=0;
    ram_addr=0;
    ram_data_in=0;
    pool1_en=0;
  }
  else if(!pool1_en.read())
  {
    //cout<<"In Conv1"<<endl;
    if(times<=157)
    {
      rom_rd.write(1);
      rom_addr.write(times);
      if(times>1) kernel[times-2]=rom_data_out.read();
      else temp=rom_data_out.read();
      times=times+1;
    }
    else if(times>=158 && times<=943)
    {
      rom_rd.write(1);
      rom_addr.write(44426+(times-158));
      if(times>159) data[times-160]=rom_data_out.read();
      else temp=rom_data_out.read();
      times=times+1;
    }
    else
    {
      /*if(test)
      {
        cout<<"-------------------------Conv1 kernel-------------------------"<<endl;
        for(int i=0;i<156;i=i+1)
        {
          cout<<kernel[i]<<endl;
        }
        cout<<"-------------------------Input-------------------------"<<endl;
        for(int i=0;i<784;i=i+1)
        {
          cout<<data[i]<<endl;
        }
        test=0;
      }*/
      rom_rd.write(0);
      calc=kernel[depth*26-1];
      for (int i=0;i<25;i=i+1)
      {
        if(i<5) calc=calc+data[x+y*28+i]*kernel[(depth-1)*26+i];
        else if(i>=5 && i<10) calc=calc+data[x+(y+1)*28+(i-5)]*kernel[(depth-1)*26+i];
        else if(i>=10 && i<15) calc=calc+data[x+(y+2)*28+(i-10)]*kernel[(depth-1)*26+i];
        else if(i>=15 && i<20) calc=calc+data[x+(y+3)*28+(i-15)]*kernel[(depth-1)*26+i];
        else calc=calc+data[x+(y+4)*28+(i-20)]*kernel[(depth-1)*26+i];
      }
      if(calc<0) calc=0;
      ram_place=ram_place+1; //1~3456
      ram_wr.write(0);
      ram_addr.write(ram_place);
      #ifdef fixed_DATA_TYPE
      ram_data_in.write(calc.range(25,10));
      #else
      ram_data_in.write(calc);
      #endif
      x=x+1;
      if(x>23)
      {
			  x=0;
		  	y=y+1;
		  }
      if(y>23)
      {
        y=0;
        depth=depth+1;
      }
      if(depth>6)
      {
        pool1_en.write(1);
      }
    }
  }
}

void Pool1::run() {
  if(rst)
  {
    x=0;
    y=0;
    times=0;
    depth=1;
    test=1;
    ram_place=3499;
    rom_rd=0;
    rom_addr=0;
    ram_wr=0;
    ram_addr=0;
    ram_data_in=0;
    conv2_en=0;
  }
  else if(pool1_en && !conv2_en)
  {
    //cout<<"In Pool1"<<endl;
    if(times<=3457)
    {
      ram_wr.write(1);
      ram_addr.write(times);
      if(times>1) data[times-2]=ram_data_out.read();
      else temp=ram_data_out.read();
      times=times+1;
    }
    else
    {
      /*if(test)
      {
        cout<<"-------------------------Conv1 result-------------------------"<<endl;
        for(int i=0;i<3456;i=i+1)
        {
          cout<<data[i]<<endl;
        }
        test=0;
      }*/
      temp=0;
      int place1,place2,place3,place4;
      place1=x+y*24+(depth-1)*576;
      place2=x+1+y*24+(depth-1)*576;
      place3=x+(y+1)*24+(depth-1)*576;
      place4=x+1+(y+1)*24+(depth-1)*576;
      if(temp<data[place1]) temp=data[place1];
      if(temp<data[place2]) temp=data[place2];
      if(temp<data[place3]) temp=data[place3];
      if(temp<data[place4]) temp=data[place4];
      ram_place=ram_place+1; //3500~4363
      ram_wr.write(0);
      ram_addr.write(ram_place);
      ram_data_in.write(temp);
      x=x+2;
      if(x==24)
      {
			  x=0;
		  	y=y+2;
		  }
      if(y==24)
      {
        y=0;
        depth=depth+1;
      }
      if(depth==7)
      {
        conv2_en.write(1);
      }
    }
  }
}

void Conv2::run() {
  if(rst)
  {
    x=0;
    y=0;
    times=0;
    depth=1;
    test=1;
    ram_place=4399;
    rom_rd=0;
    rom_addr=0;
    ram_wr=0;
    ram_addr=0;
    ram_data_in=0;
    pool2_en=0;
  }
  else if(conv2_en && !pool2_en)
  {
    //cout<<"In Conv2"<<endl;
    if(times<=2417)
    {
      rom_rd.write(1);
      rom_addr.write(156+times);
      if(times>1) kernel[times-2]=rom_data_out.read();
      else temp=rom_data_out.read();
      times=times+1;
    }
    else if(times>=2418 && times<=3283)
    {
      rom_rd.write(0);
      ram_wr.write(1);
      ram_addr.write(3500+(times-2418));
      if(times>2418) data[times-2419]=ram_data_out.read();
      else temp=ram_data_out.read();
      times=times+1;
    }
    else
    {
      /*if(test)
      {
        cout<<"-------------------------Conv2 kernel-------------------------"<<endl;
        for(int i=0;i<2416;i=i+1)
        {
          cout<<kernel[i]<<endl;
        }
        cout<<"-------------------------Maxpool1 result-------------------------"<<endl;
        for(int i=0;i<864;i=i+1)
        {
          cout<<data[i]<<endl;
        }
        test=0;
      }*/
      calc=kernel[depth*151-1];
      for (int i=0;i<6;i=i+1) //input depth
      {
        for(int j=0;j<25;j=j+1)
        {
          if(j<5) calc=calc+data[x+y*12+j+144*i]*kernel[(depth-1)*151+j+25*i];
          else if(j>=5 && j<10) calc=calc+data[x+(y+1)*12+(j-5)+144*i]*kernel[(depth-1)*151+j+25*i];
          else if(j>=10 && j<15) calc=calc+data[x+(y+2)*12+(j-10)+144*i]*kernel[(depth-1)*151+j+25*i];
          else if(j>=15 && j<20) calc=calc+data[x+(y+3)*12+(j-15)+144*i]*kernel[(depth-1)*151+j+25*i];
          else calc=calc+data[x+(y+4)*12+(j-20)+144*i]*kernel[(depth-1)*151+j+25*i];
        }
      }
      if(calc<0) calc=0;
      ram_place=ram_place+1; //4400~5423
      ram_wr.write(0);
      ram_addr.write(ram_place);
      #ifdef fixed_DATA_TYPE
      ram_data_in.write(calc.range(25,10));
      #else
      ram_data_in.write(calc);
      #endif
      x=x+1;
      if(x==8)
      {
			  x=0;
		  	y=y+1;
		  }
      if(y==8)
      {
        y=0;
        depth=depth+1;
      }
      if(depth==17)
      {
        pool2_en.write(1);
      }
    }
  }
}

void Pool2::run() {
  if(rst)
  {
    x=0;
    y=0;
    times=0;
    depth=1;
    test=1;
    ram_place=5499;
    rom_rd=0;
    rom_addr=0;
    ram_wr=0;
    ram_addr=0;
    ram_data_in=0;
    dense1_en=0;
  }
  else if(pool2_en && !dense1_en)
  {
    if(times<=1024)
    {
      ram_wr.write(1);
      ram_addr.write(4400+times);
      if(times>0) data[times-1]=ram_data_out.read();
      else temp=ram_data_out.read();
      times=times+1;
    }
    else
    {
      //cout<<"In Pool2"<<endl;
      temp=0;
      int place1,place2,place3,place4;
      place1=x+y*8+(depth-1)*64;
      place2=x+1+y*8+(depth-1)*64;
      place3=x+(y+1)*8+(depth-1)*64;
      place4=x+1+(y+1)*8+(depth-1)*64;
      if(temp<data[place1]) temp=data[place1];
      if(temp<data[place2]) temp=data[place2];
      if(temp<data[place3]) temp=data[place3];
      if(temp<data[place4]) temp=data[place4];
      ram_place=ram_place+1; //5500~5755
      ram_wr.write(0);
      ram_addr.write(ram_place);
      ram_data_in.write(temp);
      x=x+2;
      if(x==8)
      {
			  x=0;
		  	y=y+2;
		  }
      if(y==8)
      {
        y=0;
        depth=depth+1;
      }
      if(depth==17)
      {
        dense1_en.write(1);
      }
    }
  }
}

void Dense1::run() {
  if(rst)
  {
    x=0;
    y=0;
    times=0;
    depth=1;
    test=1;
    ram_place=5799;
    rom_rd=0;
    rom_addr=0;
    ram_wr=0;
    ram_addr=0;
    ram_data_in=0;
    dense2_en=0;
  }
  else if(dense1_en && !dense2_en)
  {
    //cout<<"In Dense1"<<endl;
    if(times<=256)
    {
      ram_wr.write(1);
      ram_addr.write(5500+times);
      if(times>0) data[500+times-1]=ram_data_out.read();
      else temp=ram_data_out.read();
      times=times+1;
    }
    else if(times>=257 && times<=31098)
    {
      rom_rd.write(1);
      rom_addr.write(2572+(times-257));
      if(times>257) kernel[times-258]=rom_data_out.read();
      else temp=rom_data_out.read();
      times=times+1;
    }
    else if(times==31099)
    {
      rom_rd.write(0);
      for(int i=0;i<4;i=i+1) //y
      {
        for(int j=0;j<4;j=j+1) //x
        {
          for(int k=0;k<16;k=k+1) //depth
          {
            data[k+16*j+64*i]=data[500+j+4*i+16*k];
          }
        }
      }
      times=times+1;
    }
    else
    {
      /*if(test)
      {
        cout<<"-------------------------Maxpool2 result(flattened)-------------------------"<<endl;
        for(int i=0;i<256;i=i+1)
        {
          cout<<data[i]<<endl;
        }
        cout<<"-------------------------Dense1 Kernel-------------------------"<<endl;
        for(int i=1;i<30841;i=i+1)
        {
          cout<<kernel[i]<<endl;
        }
        test=0;
      }*/
      calc=kernel[257*(x+1)];
      for(int i=0;i<256;i=i+1)
      {
        calc=calc+data[i]*kernel[257*x+i+1];
      }
      if(calc<0) calc=0;
      ram_place=ram_place+1; //5800~5919
      ram_wr.write(0);
      ram_addr.write(ram_place);
      #ifdef fixed_DATA_TYPE
      ram_data_in.write(calc.range(25,10));
      #else
      ram_data_in.write(calc);
      #endif
      x=x+1;
      if(x==120)
      {
        dense2_en.write(1);
		  }
    }
  }
}

void Dense2::run() {
  if(rst)
  {
    x=0;
    y=0;
    times=0;
    depth=1;
    test=1;
    ram_place=5999;
    rom_rd=0;
    rom_addr=0;
    ram_wr=0;
    ram_addr=0;
    ram_data_in=0;
    dense3_en=0;
  }
  else if(dense2_en && !dense3_en)
  {
    //cout<<"In Dense2"<<endl;
    if(times<=120)
    {
      ram_wr.write(1);
      ram_addr.write(5800+times);
      if(times>0) data[times-1]=ram_data_out.read();
      else temp=ram_data_out.read();
      times=times+1;
    }
    else if(times>=121 && times<=10286)
    {
      rom_rd.write(1);
      rom_addr.write(33412+(times-121));
      if(times>121) kernel[times-122]=rom_data_out.read();
      else temp=rom_data_out.read();
      times=times+1;
    }
    else
    {
      /*if(test)
      {
        cout<<"-------------------------Dense1 result-------------------------"<<endl;
        for(int i=0;i<120;i=i+1)
        {
          cout<<data[i]<<endl;
        }
        cout<<"-------------------------Dense2 Kernel-------------------------"<<endl;
        for(int i=1;i<10165;i=i+1)
        {
          cout<<kernel[i]<<endl;
        }
        test=0;
      }*/
      calc=kernel[121*(x+1)];
      for(int i=0;i<120;i=i+1)
      {
        calc=calc+data[i]*kernel[121*x+i+1];
      }
      if(calc<0) calc=0;
      ram_place=ram_place+1; //6000~6083
      ram_wr.write(0);
      ram_addr.write(ram_place);
      #ifdef fixed_DATA_TYPE
      ram_data_in.write(calc.range(25,10));
      #else
      ram_data_in.write(calc);
      #endif
      x=x+1;
      if(x==84)
      {
        dense3_en.write(1);
		  }
    }
  }
}

void Dense3::run() {
  if(rst)
  {
    x=0;
    y=0;
    times=0;
    depth=1;
    test=1;
    ram_place=0;
    rom_rd=0;
    rom_addr=0;
    ram_wr=0;
    ram_addr=0;
    ram_data_in=0;
    result=0;
    output_valid=0;
  }
  else if(dense3_en)
  {
    //cout<<"In Dense3"<<endl;
    if(times<=84)
    {
      ram_wr.write(1);
      ram_addr.write(6000+times);
      if(times>0) data[times-1]=ram_data_out.read();
      else temp=ram_data_out.read();
      times=times+1;
    }
    else if(times>=85 && times<=936)
    {
      rom_rd.write(1);
      rom_addr.write(43576+(times-85));
      if(times>85) kernel[times-86]=rom_data_out.read();
      else temp=rom_data_out.read();
      times=times+1;
    }
    else
    {
      /*if(test)
      {
        cout<<"-------------------------Dense2 result-------------------------"<<endl;
        for(int i=0;i<84;i=i+1)
        {
          cout<<data[i]<<endl;
        }
        cout<<"-------------------------Dense3 Kernel-------------------------"<<endl;
        for(int i=1;i<851;i=i+1)
        {
          cout<<kernel[i]<<endl;
        }
        test=0;
      }*/
      calc=kernel[85*(x+1)];
      for(int i=0;i<84;i=i+1)
      {
        calc=calc+data[i]*kernel[85*x+i+1];
      }
      x=x+1;
      output_valid.write(1);
      #ifdef fixed_DATA_TYPE
      result.write(calc.range(25,10));
      #else
      result.write(calc);
      #endif
    }
  }
}

// ^^^^^ put your code here ^^^^^
