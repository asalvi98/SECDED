#include<stdio.h>
#include"ap_fixed.h"
#include"ap_int.h"

typedef ap_uint<5> data_5;
typedef ap_uint<8> data_8;
typedef ap_uint<13> data_13;
typedef ap_uint<1> data_1;
typedef ap_uint<4> data_4;
void ecc_encoder(
		data_8 	data1,		//in
		data_5 	*output		//out
		);
void ecc_decoder(
		data_8 	data_in, 	//in
		data_5 	ecc_in,		//in
		data_8 	*output,	//out
		data_1 	*valid		//out
		);
