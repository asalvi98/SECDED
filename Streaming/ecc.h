#include<stdio.h>
#include"ap_fixed.h"
#include"ap_int.h"
#include"ap_axi_sdata.h"
#include<hls_stream.h>

typedef ap_uint<5> data_5;
typedef ap_uint<8> data_8;
typedef ap_uint<13> data_13;
typedef ap_uint<1> data_1;
typedef ap_uint<4> data_4;

struct axis_data_8{
	data_8 data;
	bool last;
};

struct axis_data_5{
	data_5 data;
	bool last;
};

struct axis_data_1{
	data_1 data;
	bool last;
};



void ecc_encoder(
		hls::stream<axis_data_8> &data1,		//in
		hls::stream<axis_data_5> &output		//out
		);
void ecc_decoder(
		data_8 	data_in, 	//in
		data_5 	ecc_in,		//in
		data_8 	*output,	//out
		data_1 	*valid		//out
		);

