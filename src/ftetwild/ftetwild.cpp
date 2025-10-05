#include <floattetwild/FloatTetwild.h>
#include <ftetwild/ftetwild.h>

namespace ftetwild {
class FtetWild::Impl
{
  public:
    int tetrahedralization(const Eigen::MatrixXd& InputV,
                           const Eigen::MatrixXd& InputF,
                           Eigen::MatrixXd&       OutV,
                           Eigen::MatrixXi&       OutT,
                           const Parameters&      parms)
    {
        spdlog::error("TODO: NOT FULLY IMPLEMENTED YET!");
        std::abort();

        floatTetWild::Parameters this_parms;
        GEO::Mesh                mesh;
        mesh.vertices.create_vertices(InputV.rows());
        for (int i = 0; i < InputV.rows(); i++) {
            mesh.vertices.point(i) = GEO::vec3(InputV(i, 0), InputV(i, 1), InputV(i, 2));
        }

        auto ret = floatTetWild::tetrahedralization(mesh,        // mesh
                                                    this_parms,  // parm
                                                    OutV,
                                                    OutT,  // out mesh
                                                    static_cast<int>(parms.boolean_op),
                                                    parms.skip_simplify);

        return ret;
    }
};

FtetWild::FtetWild()
    : impl(new Impl())
{}

int FtetWild::tetrahedralization(const Eigen::MatrixXd& InputV,
                                 const Eigen::MatrixXd& InputF,
                                 Eigen::MatrixXd&       OutV,
                                 Eigen::MatrixXi&       OutT,
                                 const Parameters&      params)
{
    return impl->tetrahedralization(InputV, InputF, OutV, OutT, params);
}

FtetWild::~FtetWild()
{
    delete impl;
}
}  // namespace ftetwild
