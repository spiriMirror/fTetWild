#include <floattetwild/FloatTetDelaunay.h>
#include <floattetwild/FloatTetwild.h>
#include <ftetwild/ftetwild.h>
#include <tbb/global_control.h>

namespace ftetwild {
class Parameters::Impl
{
  public:
    // ideal_edge_length = diag_of_bbox * L. (double, optional, default: 0.05)
    double ideal_edge_length_rel = 1.0 / 20;

    // epsilon = diag_of_bbox * EPS. (double, optional, default: 1e-3)
    double eps_rel = 1.0e-3;

    std::string log_path = "";

    BooleanOp boolean_op = BooleanOp::None;

    bool skip_simplify = false;

    bool is_quiet = false;

    int log_level = 2;

    bool manifold_surface = false;

    uint32_t max_threads = ~0;
};

Parameters::Parameters()
    : impl(new Impl())
{}

Parameters::~Parameters()
{
    delete impl;
}

#define IMPL_GET_SET(T, name)    \
    void Parameters::name(T val) \
    {                            \
        impl->name = val;        \
    }                            \
    T Parameters::name() const   \
    {                            \
        return impl->name;       \
    }

IMPL_GET_SET(double, ideal_edge_length_rel);
IMPL_GET_SET(double, eps_rel);
IMPL_GET_SET(BooleanOp, boolean_op);
IMPL_GET_SET(bool, skip_simplify);
IMPL_GET_SET(bool, is_quiet);
IMPL_GET_SET(int, log_level);
IMPL_GET_SET(bool, manifold_surface);
IMPL_GET_SET(uint32_t, max_threads);

void Parameters::log_path(const char* val)
{
    impl->log_path = val;
}
const char* Parameters::log_path() const
{
    return impl->log_path.c_str();
}

#undef IMPL_GET_SET

static void fill_parameters(floatTetWild::Parameters& dst, const Parameters& src)
{
    dst.ideal_edge_length_rel = src.ideal_edge_length_rel();
    dst.eps_rel               = src.eps_rel();
    dst.log_path              = src.log_path();

    dst.is_quiet         = src.is_quiet();
    dst.log_level        = src.log_level();
    dst.manifold_surface = src.manifold_surface();
    floatTetWild::logger().set_level(static_cast<spdlog::level::level_enum>(dst.log_level));

#ifdef FLOAT_TETWILD_USE_TBB
    unsigned int num_threads = std::max(1u, std::thread::hardware_concurrency());
    num_threads              = std::min(src.max_threads(), num_threads);
    dst.num_threads          = num_threads;
    tbb::global_control control {tbb::global_control::max_allowed_parallelism, num_threads};
#endif
}

class FtetWild::Impl
{
  public:
    int tetrahedralization(const Eigen::MatrixXd& InputV,
                           const Eigen::MatrixXi& InputF,
                           Eigen::MatrixXd&       OutV,
                           Eigen::MatrixXi&       OutT,
                           const Parameters&      parms)
    {
        GEO::initialize();

        GEO::Mesh mesh;
        mesh.vertices.create_vertices(InputV.rows());
        for (int i = 0; i < InputV.rows(); i++) {
            mesh.vertices.point(i) = GEO::vec3(InputV(i, 0), InputV(i, 1), InputV(i, 2));
        }

        if (InputF.cols() == 3) {
            mesh.facets.create_triangles(InputF.rows());
            for (int i = 0; i < InputF.rows(); i++) {
                mesh.facets.set_vertex(i, 0, InputF(i, 0));
                mesh.facets.set_vertex(i, 1, InputF(i, 1));
                mesh.facets.set_vertex(i, 2, InputF(i, 2));
            }
        }
        else if (InputF.cols() == 4) {
            mesh.facets.create_quads(InputF.rows());
            for (int i = 0; i < InputF.rows(); i++) {
                mesh.facets.set_vertex(i, 0, InputF(i, 0));
                mesh.facets.set_vertex(i, 1, InputF(i, 1));
                mesh.facets.set_vertex(i, 2, InputF(i, 2));
                mesh.facets.set_vertex(i, 3, InputF(i, 3));
            }
        }
        else {
            floatTetWild::logger().error("InputF should have 3 or 4 columns.");
            return EXIT_FAILURE;
        }

        floatTetWild::Parameters this_parms;
        fill_parameters(this_parms, parms);

        auto ret = floatTetWild::tetrahedralization(mesh,        // mesh
                                                    this_parms,  // parm
                                                    OutV,
                                                    OutT,  // out mesh
                                                    static_cast<int>(parms.boolean_op()),
                                                    parms.skip_simplify());

        return ret;
    }
};

FtetWild::FtetWild()
    : impl(new Impl())
{}

int FtetWild::tetrahedralization(const Eigen::MatrixXd& InputV,
                                 const Eigen::MatrixXi& InputF,
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
