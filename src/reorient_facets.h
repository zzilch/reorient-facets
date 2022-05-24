#include <igl/embree/reorient_facets_raycast.h>

void reorient_facets(
    const Eigen::MatrixXd &V,
    const Eigen::MatrixXi &F,
    int rays_total,
    int rays_minimum,
    bool facet_wise,
    bool use_parity,
    bool is_verbose,
    Eigen::MatrixXi &FF,
    Eigen::VectorXi &I,
    Eigen::VectorXi &C)
{
    if (rays_total == 0)
    {
        rays_total = V.rows() * 100;
    }
    igl::embree::reorient_facets_raycast(
        V,
        F,
        F.rows() * 100,
        rays_minimum,
        facet_wise,
        use_parity,
        is_verbose,
        I,  // is flipped
        C  // patch id
    );
    // apply reorientation
    FF.conservativeResize(F.rows(), F.cols());
    for (int i = 0; i < I.rows(); i++)
    {
        if (I(i))
        {
            FF.row(i) = (F.row(i).reverse()).eval();
        }
        else
        {
            FF.row(i) = F.row(i);
        }
    }
}