/*
Copyright (c) 2020 Albert Berger

This file is icensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may view the text of the License in the 'LICENSE' file
shipped with the distribution of Demo_tiny.

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/
#include "transd.hpp"

//TODO: specify your working directory where the Transd files are located and where the output file
// will be placed
std::string workingDir = "Y:\\your\\working\\directory\\"


using namespace std;

int width = 1000;
int height = 1000;
int sz = width * height * 3;


int wmain( int argc, wchar_t* argv[] )
{
	wstring testFilePath =  U16(workingDir) + L"asm.td";

	transd::HPROG prog = transd::createAssembly();

	transd::loadProgram( prog, testFilePath );
	transd::TDType* func = transd::getProc( prog, L"tst::getShade" );
	wstring sx = L"x", sy = L"y";
	double* x = (double*)transd::getExportVariable( prog, sx );
	double* y = (double*)transd::getExportVariable( prog, sy );

	vector<uint8_t> outbuf(sz);

	for( int i = 0; i < width; ++i ) {
		for( int k = 0; k < height; ++k ) {
			*x = (double)i - width / 2;
			*y = (double)k;

			int res = *(int*)transd::execute( func );
			uint8_t	shade = 255 * (1 - res);

			int k1 = height - k - 1;
			outbuf[3 * k1*width + 3 * i] = shade;
			outbuf[3 * k1*width + 3 * i + 1] = shade;
			outbuf[3 * k1*width + 3 * i + 2] = shade;
		}
	}

	string outFileName = workingDir + "graph.ppm";
	FILE* f = fopen( outFileName.c_str(), "wb" );
	char buf[40];
	sprintf( buf, "P6 %d %d 255\n", width, height );
	fwrite( buf, strlen( buf ), 1, f );
	unsigned char* p = (uint8_t*)&outbuf[0];
	for( int i = 0; i <= sz - width * 3; i += width * 3 ) {
		fwrite( p + i, width * 3, 1, f );
	}
	fclose( f );
	return 0;
}
