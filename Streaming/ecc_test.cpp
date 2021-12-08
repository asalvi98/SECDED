#include<stdio.h>
#include<iostream>
#include"ap_fixed.h"
#include"ap_int.h"
#include<hls_stream.h>
#include"ecc.h"


using namespace::std;

int main()
{
	data_8 output_dec;


	data_8 mask = 0b00000001;
	data_1 valid;
	int i=0, j=0, k=0;
	hls::stream<axis_data_8> input_stream;
	hls::stream<axis_data_5> ecc_out_stream;

	data_8 input_arr[256];
	data_5 ecc_out_arr[256];
	axis_data_8 tmp1;
	axis_data_5 tmp2;

	for (i=0; i<256; i++)
	{
		tmp1.data=i;
		tmp1.last=0;
		if(i==255)
			{tmp1.last=1;}
		input_stream.write(tmp1);
	}

	ecc_encoder	(
					input_stream,
					ecc_out_stream
				);

	for (i=0; i<256; i++)
	{
		ecc_out_stream.read(tmp2);
		data_5 ecc_data;
		ecc_data = tmp2.data;
		printf("Input Data: %d, ECC result: %d\n",int(i),int(ecc_data));
	}

	return 0;
}
