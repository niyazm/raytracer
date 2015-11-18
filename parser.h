// set PATH=D:\Borland\BCC55\Bin;%PATH%
// cd d:\csc\csuf\566-adv-gfx\566-prjs\code

#include <iostream>
#include <fstream> // For ifstream.

#include "camera.h"
#include "vec3.h"
using namespace std;

// ================================================== Classes ====
// Read tokens from a file, with 1-token backup.
class Token_reader
{
   public : // For Dev.
  string m_next_token; // File token to retry.
  // public : // For Rel.
  Token_reader( ) { reset( ); } // Default Ctor.
  void reset( ) { m_next_token = ""; }
  int ptoken( string rexp );
  string peekat_token( );
};

// ================================================== Globals ====
int g_more; // User isn't done?
ifstream g_fin; // Current open file stream.
Token_reader g_tr; // Machine to read a token at a time from file stream.

// ================================================== Supt Fcns ====
// Output an error msg.
void perr( string rerr, string rexp = "" )
{
  cout << "\nError: Bad " << rerr;
  if (0 < rexp.length()) cout << ", saw " << rexp;
  cout << endl;
}

// Check if next token is the given (expected) string.
// Output a parse error if it isn't.
int Token_reader::ptoken( string rexp )
{
  string stoken = m_next_token; // Get prepared token, if any.
  if ("" == stoken) g_fin >> stoken; // Input file tok if no prep'd tok.
  else m_next_token = ""; // Clear prep'd tok var.

  //*DBG*/ cout << "stoken='" << stoken << endl;
  if (rexp != stoken) perr( rexp, stoken); // Handle unexpected tok error.
  return (rexp == stoken); // Tell caller if expected token was found.
}

// Look at next token, but leave it to be parsed next.
// Typically used to check if next token will be a delimiter.
string Token_reader::peekat_token( )
{
  string stoken;
  g_fin >> stoken; // Get next token from file.
  m_next_token = stoken; // Prepare peeked token to be next actually parsed.
  //*DBG*/ cout << "peekat= " << stoken << endl;
  return stoken;
}

//================================================== Dummy Scene classes ====
/*
class Point3
{
  public : // For Dev.
  double x, y, z;
  void show( )
  {
    cout << "(Point3 " << x << ", " << y  << ", " << z << ")\n";
  }
};

class Background
{
  public : // For Dev.
  double r, g, b;
  void show( )
  {
    cout << "(Background color=" << r << ", " << g  << ", " << b << ")\n";
  }
};

enum{
  MATERIAL_NULL = 0,
  MATERIAL_PHONG
};

class Material
{
  public : // For Dev.
  int id, type;
  void show( )
  {
    cout << "(Material " << id << ", " << type << ")\n";
  }
};

class RGBAColor : public Point3 { };

class PhongMaterial : public Material
{
  public : // For Dev.
  RGBAColor ambient, diffuse, specular;
  float _shininess;
  void show( );
};

void PhongMaterial::show( )
{
  cout << "(PhongMaterial #" << id << ", type=" << type
       << ", diffuseColor=";
  diffuse.show( );
  cout << "  )\n";
}

class Object3D { };

class Plane : public Object3D
{
  public : // For Dev.
  Point3 normal;
  double offset;
  void show( )
  {
    cout << "(Plane " << offset << ", ";
    normal.show( );
    cout << "  )\n";
  }
};

class Sphere : public Object3D
{
  public : // For Dev.
  Point3 center;
  double radius;
  void show( )
  {
    cout << "(Sphere radius=" << radius << ", center=";
    center.show( );
    cout << "  )\n";
  }
};

class ViewPlane
{
  public : // For Dev.
  int width, height, pixelsize;
  void show( )
  {
    cout << "(ViewPlane width=" << width << ", height=" << height
         << ", pixelsize=" << pixelsize << ")\n";
  }
};
*/
//========================================== Point3 Supt Fcns ====
Point3 _parseVec3f( )
{
  Point3 p3;
  g_fin >> p3.x >> p3.y >> p3.z;
  return p3;
}

//========================================== Scene Section Parse Fcns ====

void _parsePhongMaterial( int id )
{
  PhongMaterial pm;
  pm.id = id;
  pm.type = MATERIAL_PHONG;
  do { // Once.
    if ( ! g_tr.ptoken( "PhongMaterial" )) break;
    if ( ! g_tr.ptoken( "{" )) break;
    if ( ! g_tr.ptoken( "diffuseColor" )) break;
    Point3 p3 = _parseVec3f( );
    pm.diffuse.x = p3.x;
    pm.diffuse.y = p3.y;
    pm.diffuse.z = p3.z;
    if ( ! g_tr.ptoken( "}" )) break;
  } while ( 0 ); // Once.
  pm.show( );
}

void _parseMaterials( )
{
  //Material mt;
  int num = 0;
  do { // Once.
    if ( ! g_tr.ptoken( "Materials" )) break;
    if ( ! g_tr.ptoken( "{" )) break;
    if ( ! g_tr.ptoken( "numMaterials" )) break;
    g_fin >> num;
    for ( int id = 0; id < num; ++id )
      {
        _parsePhongMaterial( id );
      }
    if ( ! g_tr.ptoken( "}" )) break;
  } while ( 0 ); // Once.
  //mt.show( );
}

void _parseBackground( )
{
  Background bk;
  do { // Once.
    if ( ! g_tr.ptoken( "Background" )) break;
    if ( ! g_tr.ptoken( "{" )) break;
    if ( ! g_tr.ptoken( "color" )) break;
    g_fin >> bk.r >> bk.g >> bk.b;
    if ( ! g_tr.ptoken( "}" )) break;
  } while ( 0 ); // Once.
  bk.show( );
}

void _parseviewPlane( )
{
  ViewPlane vp;
  do { // Once.
    if ( ! g_tr.ptoken( "ViewPlane" )) break;
    if ( ! g_tr.ptoken( "{" )) break;
    if ( ! g_tr.ptoken( "width" )) break;
    g_fin >> vp.width;
    if ( ! g_tr.ptoken( "height" )) break;
    g_fin >> vp.height;
    if ( ! g_tr.ptoken( "pixelsize" )) break;
    g_fin >> vp.pixelsize;
    if ( ! g_tr.ptoken( "}" )) break;
  } while ( 0 ); // Once.
  vp.show( );
}

void _parseCamera(arguments _a, world& w )
{
  do { // Once.
    if ( ! g_tr.ptoken( "OrthographicCamera" )) break;
    if ( ! g_tr.ptoken( "{" )) break;
    if ( ! g_tr.ptoken( "center" )) break;
    Point3 p3center = _parseVec3f( );
    if ( ! g_tr.ptoken( "direction" )) break;
    Point3 p3direction = _parseVec3f( );
    if ( ! g_tr.ptoken( "up" )) break;
    Point3 p3up = _parseVec3f( );
    if ( ! g_tr.ptoken( "}" )) break;
    /*DBG*/ cout << "(OrthographicCamera center=";
    /*DBG*/ p3center.show();
    /*DBG*/ cout << "  direction=";
    /*DBG*/ p3direction.show();
    /*DBG*/ cout << "  up=";
    /*DBG*/ p3up.show();
    /*DBG*/ cout << "  )\n";
  } while ( 0 ); // Once.
}

void _parsePlane( )
{
  Plane pn;
  do { // Once.
    if ( ! g_tr.ptoken( "Plane" )) break;
    if ( ! g_tr.ptoken( "{" )) break;
    if ( ! g_tr.ptoken( "normal" )) break;
    pn.normal = _parseVec3f( );
    if ( ! g_tr.ptoken( "offset" )) break;
    g_fin >> pn.offset;
    /*DBG*/ pn.show();
  } while ( 0 ); // Once.
}

void _parseSphere( )
{
  Sphere sp;
  do { // Once.
    if ( ! g_tr.ptoken( "Sphere" )) break;
    if ( ! g_tr.ptoken( "{" )) break;
    if ( ! g_tr.ptoken( "center" )) break;
    sp.center = _parseVec3f( );
    if ( ! g_tr.ptoken( "radius" )) break;
    g_fin >> sp.radius;
    if ( ! g_tr.ptoken( "}" )) break;
    /*DBG*/ sp.show();
  } while ( 0 ); // Once.
}

void _parseMaterialIndex( )
{
  do { // Once.
    if ( ! g_tr.ptoken( "MaterialIndex" )) break;
    int num;
    g_fin >> num;
    cout << "MaterialIndex= " << num << endl;
  } while ( 0 ); // Once.
}

void _parseGroup( )
{
  int num = 0;
  do { // Once.
    if ( ! g_tr.ptoken( "Group" )) break;
    if ( ! g_tr.ptoken( "{" )) break;
    if ( ! g_tr.ptoken( "numObjects" )) break;
    int cnt;
    g_fin >> cnt;
    cout << "Group numObjects= " << cnt << endl;
    int qmore = 1;
    do {
      string stoken = g_tr.peekat_token( );
      if ("MaterialIndex" == stoken) _parseMaterialIndex( );
      else if ("Sphere" == stoken) { _parseSphere( ); ++ num;}
      else if ("Plane" == stoken) { _parsePlane( ); ++ num;}
      else if ("}" == stoken) qmore = 0;
      else perr( "MaterialIndex, Sphere, Plane, or '}'", stoken );
    } while (qmore);
  } while ( 0 ); // Once.
  cout << "Saw Group of " << num << " objects\n";
}

// Open the file that the user indicates.
// Return false if it failed to open, else true.
void open_file_from_user( )
{
  cout << "Enter input file name, or q to quit> ";
  string fname;
  cin >> fname; // Get the user's filename.
  g_more = ( "q" != fname );
  //*DBG*/ cout << "g_more=" << g_more << endl;
  if ( g_more )
    {
      g_fin.open( fname.c_str() ); // Open into global var file stream.
      if ( ! g_fin ) perr( "file open" ); // Handle errors.
    }
}

// Listen to user.
void listen( )
{
  open_file_from_user( );
}

void parse_file( )
{
  g_tr.reset( ); // Reset the token reader for another file.
  _parseCamera( );
  _parseviewPlane( );
  _parseBackground( );
  _parseMaterials( );
  _parseGroup( );
}

// Respond to user.
void respond( )
{
   if ( g_more && g_fin ) // File opened?
    { // Parse scene file sections.
      parse_file( );
      g_fin.close( ); // Close the file.
    }
  else if ( g_more ) cout << "Can't parse the file.";
}

// Main: Run the Scene Parser against a file.
/*int main( )
{
  cout << "Pgm: Parse a Scene from file.\n"; // Hello msg.
  do {
    listen( );
    respond( );
  } while ( g_more );
  return 0;
}
*/
