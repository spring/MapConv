#ifndef __SMT_H
#define __SMT_H

#include <OpenImageIO/imagebuf.h>

OIIO_NAMESPACE_USING
using namespace std;

#define DXT1 1

struct SMTHeader
{
    char magic[16] = "spring tilefile";   // "spring tilefile\0"
    int version = 1;      // must be 1 for now
    int nTiles = 0;       // total number of tiles in this file
    int tileRes = 32;      // x and y dimension of tiles, must remain 32 for now.
    int tileType = DXT1;     // must be 1=dxt1 for now
};

class SMT {
    // Tiles
    unsigned int nTiles    = 0,
                 tileType  = 1,
                 tileRes   = 32,
                 tileSize  = 680;

    // Input Files
    string fileName    = "output.smt";
    
public:
    bool  verbose, quiet,
          slow_dxt1 = false;

    SMT( bool v = false, bool q = false ) : verbose(v), quiet(q) { };
    SMT( string fileName, bool v = false, bool q = false ) : SMT(v, q) { load( fileName ); };

    void setFileName( string s );
    string getFileName( ){ return fileName; };

    void setTileRes( int s    ){ tileRes = s; setType(tileType); };
    void setType   ( int comp ); // 1=DXT1

    int getTileType( ){ return tileType; };
    int getTileRes ( ){ return tileRes;  };
    int getTileSize( ){ return tileSize; };
    int getNTiles  ( ){ return nTiles;   };

    // === Actions input ===
    bool load();
    bool load( string s ){ setFileName(s); return load(); };

    ImageBuf *getTile( int tile );
    bool append( ImageBuf * );
};

#endif //ndef __SMT_H
