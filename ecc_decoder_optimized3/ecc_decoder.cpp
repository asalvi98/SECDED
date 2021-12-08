#include<stdio.h>
#include<iostream>
#include"ap_fixed.h"
#include"ap_int.h"
#include"ecc.h"
#include<string>
using namespace::std;




void ecc_decoder(
		data_8 data_in, 	//in
		data_5 ecc_in,		//in
		data_8 *output,		//out
		data_1 *valid		//out
		)
{
//	#pragma HLS PIPELINE

//	printf("%d %d \n", int(data_in), int(ecc_in));
	data_8 pattern[5];

	int i, j, size_ecc=5, size_msg=8;

	pattern[0] = 0b11110000;
	pattern[1] = 0b10001110;
	pattern[2] = 0b01101101;
	pattern[3] = 0b01011011;
	pattern[4] = 0b10110111;


//	syndrome = 11100;
//	flip[0] = 1
	data_5 check_bits;

	data_8 temp_bit[5];
	for(i=0;i<size_ecc;i++)
	{
#pragma HLS UNROLL
//#pragma HLS PIPELINE
		check_bits[i]=0;
		temp_bit[i] = pattern[i] & data_in;
	}

	for(i=0;i<size_ecc;i++)
//	for(j=0;j<size_msg;j++)
	{
		#pragma HLS UNROLL
		//#pragma HLS PIPELINE

		for(j=0;j<size_msg;j++)
//		for(i=0;i<size_ecc;i++)
		{
#pragma HLS UNROLL
//#pragma HLS PIPELINE
			check_bits[i]=check_bits[i]^temp_bit[i][j];
		}
	}


//	printf("%d\n", int(check_bits));

//	cout<<" "<<int(check_bits);
//	*output = check_bits;
	data_5 syndrome;
//	for(i=0;i<size_ecc;i++)
//	{
//		syndrome[i]=check_bits[i]^ecc_in[i];
//	}
	syndrome = check_bits^ecc_in;
//	printf("%d\n", int(syndrome));

	data_8 flip=0b11111111;

	for(i=0;i<size_msg;i++)
	{
#pragma HLS UNROLL
		for(j=0;j<size_ecc;j++)
		{
#pragma HLS UNROLL
//			flip[i]= ~(syndrome[j]^pattern[size_ecc-1-j][size_msg-1-i]);
			flip[i]= flip[i] & (~(syndrome[j]^pattern[j][i]));
		}

	}
	data_8 temp;

//	cout<<int(flip)<<"\n";
//	for(i=0;i<size_msg;i++)
//	{
//		temp[i]=flip[i]^data1[i+5];
//	}
	temp = flip^data_in;
	*output = temp;

	data_4 sum_flip=0;
	for (i=0 ; i<8 ; i++)
	{
#pragma HLS UNROLL
		sum_flip = sum_flip + flip[i];
	}


	*valid = sum_flip[0] && flip!=0;

}
