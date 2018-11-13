#include <iostream>
#include <string>
#include <fstream>
#include "Surface.h"
#include <cassert>

int main()
{
	std::cout << "This tool convets bitmap images to map files for a game!\n";
	std::cout << "Here's what the colors translate to:\n";
	std::cout << "Black(0,0,0): Floor(0),\n";
	std::cout << "White(255,255,255): Wall(1),\n";
	std::cout << "Red(255,0,0): BigBeetle(b),\n";
	std::cout << "Orange(255,127,0): Firebug(f), and\n";
	std::cout << "Yellow(255,255,0): Skorp(s).\n";

	std::cout << "Enter image path: ";
	std::string path;
	std::cin >> path;

	const Surface tileData = path;

	auto outFilePath = "LevelOut-" + path;
	outFilePath = outFilePath.substr( 0,outFilePath.length() - 3 );
	outFilePath += "lvl";
	std::ofstream out{ outFilePath };
	assert( out.good() );

	for( int y = 0; y < tileData.GetHeight(); ++y )
	{
		for( int x = 0; x < tileData.GetWidth(); ++x )
		{
			const auto curTile = tileData.GetPixel( x,y );
			switch( curTile.GetDword() )
			{
			case Colors::MakeRGB( 0,0,0 ).GetDword():
				out << '0';
				break;
			case Colors::MakeRGB( 255,255,255 ).GetDword():
				out << '1';
				break;
			case Colors::MakeRGB( 255,0,0 ).GetDword():
				out << 'b';
				break;
			case Colors::MakeRGB( 255,127,0 ).GetDword():
				out << 'f';
				break;
			case Colors::MakeRGB( 255,255,0 ).GetDword():
				out << 's';
				break;
			}
			if( x != tileData.GetWidth() - 1 ) out << ',';
		}
		if( y != tileData.GetHeight() - 1 ) out << '\n';
	}

	out.close();
	std::cout << "File created successfully!\n";
	std::cin.get();
	std::cin.get();

	return( 0 );
}