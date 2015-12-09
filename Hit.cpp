
Hit::Hit(){
  t = 10000.0f;
  normal = Vec3f();
  mat = NULL;
  view = Vec3f();
}

Hit::Hit(double _t, Vec3f _n, Vec3f _r, Material* _m){
  t = _t;
  normal = _n;
  mat = _m;
  view = _r;
}

Hit::Hit(const Hit& h){
  t = h.t;
  normal = h.normal;
  mat = h.mat;
  view = h.view;
}

/*Hit& Hit::operator=(Hit& h){
  t = h.t;
  normal = h.normal;
  mat = h.mat;
  view = h.view;
}*/
