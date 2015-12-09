class ViewPlane{
public:
    int hres;
    int vres;
    float s;
    float gamma;
    float inv_gamma;

    void print_ViewPlane(int tabs){
      tabsting = "";
      for (int i = 0; i < tabs; i++){
        tabstring += "\t";
      }
      cout << tabstring << "CAMERA :" << endl;
      cout << tabstring << "\t" << "hres:" << hres << " v:" << vres << " pixel size: " << s << endl;

    }
}
