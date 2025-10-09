#include <ftetwild/ftetwild.h>

int main()
{
    ftetwild::FtetWild ftetwild;

    // createa a single tet;
    Eigen::MatrixXd InputVs;
    InputVs.resize(4, 3);
    InputVs << 0, 0, 0,  //
      1, 0, 0,           //
      0, 1, 0,           //
      0, 0, 1;
    Eigen::MatrixXi InputFs;
    InputFs.resize(4, 3);
    InputFs << 0, 1, 2,  //
      0, 1, 3,           //
      0, 2, 3,           //
      1, 2, 3;
    Eigen::MatrixXd      OutV;
    Eigen::MatrixXi      OutT;
    ftetwild::Parameters parms;

    ftetwild.tetrahedralization(InputVs, InputFs, OutV, OutT, parms);
}