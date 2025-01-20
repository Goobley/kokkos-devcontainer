#include <Kokkos_Core.hpp>

#include <cstdio>
#include <iostream>

typedef float fp_t;

typedef Kokkos::LayoutRight Layout;
template <class T, typename... Args>
using KView = Kokkos::View<T, Layout, Args...>;

typedef Kokkos::DefaultExecutionSpace::memory_space DefaultMemSpace;
typedef Kokkos::HostSpace HostSpace;

typedef Kokkos::View<fp_t*    , Layout> Fp1d;
typedef Kokkos::View<fp_t**   , Layout> Fp2d;
typedef Kokkos::View<fp_t***  , Layout> Fp3d;
typedef Kokkos::View<fp_t**** , Layout> Fp4d;
typedef Kokkos::View<fp_t*****, Layout> Fp5d;

typedef Kokkos::View<const fp_t*    , Layout> FpConst1d;
typedef Kokkos::View<const fp_t**   , Layout> FpConst2d;
typedef Kokkos::View<const fp_t***  , Layout> FpConst3d;
typedef Kokkos::View<const fp_t**** , Layout> FpConst4d;
typedef Kokkos::View<const fp_t*****, Layout> FpConst5d;

template <int R, typename... Args>
using MDRange = Kokkos::MDRangePolicy<Kokkos::Rank<R, Kokkos::Iterate::Right, Kokkos::Iterate::Right>, Args...>;

int main(int argc, char* argv[]) {
  Kokkos::initialize(argc, argv);
  Kokkos::DefaultExecutionSpace().print_configuration(std::cout);
  {
    auto arr_mdr = Fp4d("stuff", 1024*1024, 1, 1, 1);
    auto arr_flat = Fp4d("stuff", 1024*1024, 1, 1, 1);

    Kokkos::parallel_for(
      "MDR Loop",
      MDRange<4>(
        {0, 0, 0, 0},
        {1024 * 1024, 1, 1, 1}
      ),
      KOKKOS_LAMBDA (int x, int y, int z, int w) {
        Kokkos::atomic_add(&arr_mdr(x, y, z, w), 1.0f);
      }
    );

    Kokkos::parallel_for(
      "Flat Loop",
      1024 * 1024,
      KOKKOS_LAMBDA (int x) {
        Kokkos::atomic_add(&arr_flat(x, 0, 0, 0), 1.0f);
      }
    );
    Kokkos::fence();

    fp_t max_mdr = 0.0f;
    fp_t max_flat = 0.0f;
    Kokkos::parallel_reduce(
      "Check MDR",
      MDRange<4>(
        {0, 0, 0, 0},
        {1024 * 1024, 1, 1, 1}
      ),
      KOKKOS_LAMBDA (int x, int y, int z, int w, float& lmax) {
        fp_t val = arr_mdr(x, y, z, w);
        if (val > lmax) {
          lmax = val;
        }
      },
      Kokkos::Max<fp_t>(max_mdr)
    );
    Kokkos::parallel_reduce(
      "Check flat",
      1024 * 1024,
      KOKKOS_LAMBDA (int x, float& lmax) {
        fp_t val = arr_flat(x, 0, 0, 0);
        if (val > lmax) {
          lmax = val;
        }
      },
      Kokkos::Max<fp_t>(max_flat)
    );

    Kokkos::fence();
    printf("Max mdr: %f, flat: %f. Expected 1.0\n", max_mdr, max_flat);
  }
  Kokkos::finalize();
  return 0;
}