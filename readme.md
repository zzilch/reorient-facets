# Executable

Build


```bash
mkdir build && cd build
cmake ..
cmake --build . --config Release -j 4
```

Usage

```
Reorient Facets
Usage: reorient-facets [OPTIONS] input_mesh output_mesh

Positionals:
  input_mesh TEXT:PATH(existing) REQUIRED
                              Input mesh
  output_mesh TEXT:PATH(non-existing) REQUIRED
                              Output mesh

Options:
  -h,--help                   Print this help message and exit
  -t INT:NONNEGATIVE [0]      Total number of rays that will be shot (default: 0, #F*100)
  -m INT:POSITIVE [10]        Minimum number of rays that each patch should receive (defulat: 10)
  -f                          Decision made for each face independently, no use of patches
  -p                          Use parity mode
  -v                          Verbose output to cout
```

# Python

Build

```
python setup.py install
```

Usage

```
from reorient_facets import reorient_facets
help(reorient_facets)

reorient_facets(...) method of builtins.PyCapsule instance
    reorient_facets(V: numpy.ndarray[numpy.float64[m, n]], F: numpy.ndarray[numpy.int32[m, n]], rays_total: int = 0, rays_minimum: int = 10, facet_wise: bool = False, use_parity: bool = False, is_verbose: bool = False) -> tuple(F_new, is_flipped, patch_id)
```