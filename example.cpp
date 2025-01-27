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

typedef Kokkos::TeamPolicy<Kokkos::DefaultExecutionSpace>::member_type TeamMember;
typedef Kokkos::TeamPolicy<Kokkos::DefaultExecutionSpace> TeamPolicy;

#define CONCAT_IMPL(x, y) x##y
#define CONCAT(x, y) CONCAT_IMPL(x, y)
#define MakeView() Fp2d CONCAT(view, __LINE__)("a", 256, 1024)

int main(int argc, char* argv[]) {
  Kokkos::initialize(argc, argv);
  Kokkos::DefaultExecutionSpace().print_configuration(std::cout);
  {
    typedef Kokkos::MaxLoc<fp_t, int> Reducer;
    typedef Reducer::value_type ReducerType;
    typedef Kokkos::MaxLoc<fp_t, int, Kokkos::DefaultExecutionSpace> ReducerDev;

    MakeView();
    MakeView();
    MakeView();
    MakeView();
    MakeView();
    MakeView();
    MakeView();
    MakeView();
    MakeView();
    MakeView();
    MakeView();
    MakeView();
    MakeView();
    MakeView();
    MakeView();
    MakeView();
    MakeView();
    printf("Allocated\n");

    ReducerType val;
    auto pol = TeamPolicy(320, Kokkos::AUTO(), 1);
    Kokkos::parallel_reduce(
      "Team stuff",
      pol,
      KOKKOS_LAMBDA (const TeamMember& member, ReducerType& lval) {
      },
      Reducer(val)
    );
    Kokkos::fence();

  }
  Kokkos::finalize();
  return 0;
}