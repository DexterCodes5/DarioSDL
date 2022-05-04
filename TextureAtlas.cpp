#include "TextureAtlas.h"
#include "StdWilUtil.h"

#include <fstream>
#include <sstream>
using namespace std;

TextureAtlas::TextureAtlas()
{
	
}

bool TextureAtlas::loadData( string datafile )
{
	// atlas.txt generated by spritesheetpacker
	// http://spritesheetpacker.codeplex.com/
	// has its data in the form 
	// grass = 0 0 32 32
	// trees = 33 0 32 32
	ifstream in( datafile.c_str() );
	if( !in )
	{
		error( "Could not load texture atlas datafile %s!", datafile.c_str() );
		return false;
	}

	while( !in.eof() )
	{
		string line;
		getline( in, line );
		if( !line.size() )
			skip;
		istringstream is( line );
		string name, eq;
		is >> name;
		is >> eq; // discard the extra token
		
		SDL_Rect rect;
		is >> rect.x;
		is >> rect.y;
		is >> rect.w;
		is >> rect.h;
		spriteRects[ name ] = rect;
		
		printf( "%s @ (%d %d %d %d)\n", name.c_str(), rect.x, rect.y, rect.w, rect.h );
	}
	
	return true;
}