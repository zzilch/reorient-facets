#include <igl/read_triangle_mesh.h>
#include <igl/write_triangle_mesh.h>
#include "reorient_facets.h"
#include "CLI11.hpp"

int main(int argc, char *argv[])
{
  // options
  std::string input_mesh;
  std::string output_mesh;
  int rays_total = 0;
  int rays_minimum = 10;
  bool facet_wise = false;
  bool use_parity = false;
  bool is_verbose = false;

  // input
  Eigen::MatrixXd V;
  Eigen::MatrixXi F;

  // output
  Eigen::MatrixXi FF;
  Eigen::VectorXi I;
  Eigen::VectorXi C;

  CLI::App app{"Reorient Facets"};
  app.add_option("input_mesh", input_mesh, "Input mesh")
      ->check(CLI::ExistingPath)
      ->required();
  app.add_option("output_mesh", output_mesh, "Output mesh")
      ->check(CLI::NonexistentPath)
      ->required();
  app.add_option("-t", rays_total, "Total number of rays that will be shot (default: 0, #F*100)")
      ->check(CLI::NonNegativeNumber)
      ->default_val(0);
  app.add_option("-m", rays_minimum, "Minimum number of rays that each patch should receive (defulat: 10)")
      ->check(CLI::PositiveNumber)
      ->default_val(10);
  app.add_flag("-f", facet_wise, "Decision made for each face independently, no use of patches");
  app.add_flag("-p", use_parity, "Use parity mode");
  app.add_flag("-v", is_verbose, "Verbose output to cout");
  CLI11_PARSE(app, argc, argv);

  igl::read_triangle_mesh(input_mesh, V, F);
  reorient_facets(V,F,rays_total,rays_minimum,facet_wise,use_parity,is_verbose,FF,I,C);
  igl::write_triangle_mesh(output_mesh, V, FF);
}
