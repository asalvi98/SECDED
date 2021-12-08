#include<stdio.h>
#include<iostream>
#include"ap_fixed.h"
#include"ap_int.h"
#include"ecc.h"
#include<string>
#include<hls_stream.h>
#include"ap_axi_sdata.h"
using namespace::std;




void ecc_encoder(
		hls::stream<axis_data_8> &data1, 	//in
		hls::stream<axis_data_5> &output 	//out
		)
{
#pragma HLS INTERFACE axis port=data1
#pragma HLS INTERFACE axis port=output
#pragma HLS INTERFACE s_axilite port=return

	data_8 pattern[5];
	pattern[0] = 0b11110000;
	pattern[1] = 0b10001110;
	pattern[2] = 0b01101101;
	pattern[3] = 0b01011011;
	pattern[4] = 0b10110111;

	int i, j, k, size_ecc=5, size_msg=8;
	axis_data_8 tmp1;
	data_8 inputs[256]; //array to stream the inputs into

	for(k=0;k<256;k++)
	{
		tmp1=data1.read();
		inputs[k]=tmp1.data;
	}



//#pragma HLS ARRAY_PARTITION variable=pattern type=cyclic factor=5 dim=1
	data_5 check_bits[256];

	data_8 temp_bit;
	for(k=0;k<256;k++)
	{
		for(i=0;i<size_ecc;i++)
		{
#pragma HLS UNROLL
			check_bits[k][i]=0;
			temp_bit = pattern[i] & inputs[k];
			for(j=0;j<size_msg;j++)
			{

//				check_bits[k][j]=check_bits[k][i]^temp_bit[j];
				check_bits[k][i]=check_bits[k][i]^temp_bit[j];
			}
		}
	}

	//Data Stream Out
	axis_data_5 tmp2;
	for(k=0;k<256;k++)
	{
		tmp2.last = 0;
		if(k==255)
			{tmp2.last=1;}
		tmp2.data = check_bits[k];
		output.write(tmp2);
	}

//	*output = check_bits;
}

