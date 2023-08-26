#include "catch.hpp"
#include "kqlib/memory.h"

using namespace kq;

TEST_CASE("unique_ptr with non-array", "[unique_ptr]")
{
    SECTION("default constructor")
    {
        unique_ptr<int> up;
        REQUIRE(!up);
    }

    SECTION("value constructor")
    {
        unique_ptr<int> up = make_unique<int>(100);
        REQUIRE(up);
        REQUIRE(*up == 100);
    }

    SECTION("move constructor")
    {
        unique_ptr<int> aux = make_unique<int>(50);
        unique_ptr<int> up = std::move(aux);

        REQUIRE(up);
        REQUIRE(*up == 50);
    }

    SECTION("move assignment")
    {
        unique_ptr<int> aux = make_unique<int>(50);
        unique_ptr<int> up;
        REQUIRE(!up);
        up = std::move(aux);
        REQUIRE(up);
        REQUIRE(*up == 50);
        REQUIRE(!aux);
    }

    SECTION("reseting")
    {
        unique_ptr<int> up;
        int* ptr = new int(100);

        REQUIRE(!up);
        up.reset(ptr);
        REQUIRE(up);
        REQUIRE(*up == 100);
        up.reset();
        REQUIRE(!up);
    }

    SECTION("releasing")
    {
        unique_ptr<int> up = make_unique<int>(100);
        
        REQUIRE(*(up.release()) == 100);
        REQUIRE(!up);
    }

    SECTION("swapping")
    {
        unique_ptr<int> up = make_unique<int>(100);
        unique_ptr<int> aux = make_unique<int>(5);
        up.swap(aux);
        REQUIRE(*up == 5);
        REQUIRE(up);
    }
}


TEST_CASE("unique_ptr with array")
{
    int N = 5;
    SECTION("default constructor")
    {
        unique_ptr<int[]> up;
        REQUIRE(!up);
    }

    SECTION("value constructor")
    {
        unique_ptr<int[]> up = make_unique<int[]>(N);
        REQUIRE(up);
        for (auto i = 0; i < N; ++i)
        {
            up[i] = i;
            REQUIRE(up[i] == i);
        }
    }

    SECTION("move constructor")
    {
        unique_ptr<int[]> aux = make_unique<int[]>(N);
        for (auto i = 0; i < N; ++i)
            aux[i] = i;

        unique_ptr<int[]> up = std::move(aux);

        REQUIRE(up);
        for (auto i = 0; i < N; ++i)
            REQUIRE(up[i] == i);
    }

    SECTION("move assignment")
    {
        unique_ptr<int[]> aux = make_unique<int[]>(N);
        for (auto i = 0; i < N; ++i)
            aux[i] = i;
        unique_ptr<int[]> up;
        REQUIRE(!up);
        up = std::move(aux);
        REQUIRE(up);
        for (auto i = 0; i < N; ++i)
            REQUIRE(up[i] == i);
        REQUIRE(!aux);
    }

    SECTION("reseting")
    {
        unique_ptr<int[]> up;
        int* ptr = new int[N];
        for (auto i = 0; i < N; ++i)
            ptr[i] = i;

        REQUIRE(!up);
        up.reset(ptr);
        REQUIRE(up);
        for (auto i = 0; i < N; ++i)
            REQUIRE(up[i] == i);
        up.reset();
        REQUIRE(!up);
    }

    SECTION("releasing")
    {
        unique_ptr<int[]> up = make_unique<int[]>(N);
        for (auto i = 0; i < N; ++i)
            up[i] = i;
        auto ptr = up.release();
        for (auto i = 0; i < N; ++i)
            REQUIRE(ptr[i] == i);
        REQUIRE(!up);
    }

    SECTION("swapping")
    {
        unique_ptr<int[]> up = make_unique<int[]>(N);
        for (auto i = 0; i < N; ++i)
            up[i] = i;
        unique_ptr<int[]> aux = make_unique<int[]>(N);
        for (auto i = 0; i < N; ++i)
            aux[i] = i + 1;

        up.swap(aux);

        for (auto i = 0; i < N; ++i)
            REQUIRE(up[i] == i + 1);
        for (auto i = 0; i < N; ++i)
            REQUIRE(aux[i] == i);
    }
}

TEST_CASE("matrix of unique_ptrs")
{
    auto N = 5;
    unique_ptr<unique_ptr<int[]>[]> mat = make_unique<unique_ptr<int[]>[]>(N);
    
    for (auto i = 0; i < N; ++i)
    {
        mat[i] = make_unique<int[]>(N);
        for (auto j = 0; j < N; ++j)
        {
            mat[i][j] = i * N + j;
        }
    }
    


    SECTION("Checking correct initialization")
    {
        for (auto i = 0; i < N; ++i)
        {
            for (auto j = 0; j < N; ++j)
            {
                REQUIRE(mat[i][j] == i * N + j);
            }
        }
    }

    SECTION("Swapping")
    {
        int M = 3;
        unique_ptr<unique_ptr<int[]>[]> aux = new unique_ptr<int[]>[M];
        for (auto i = 0; i < M; ++i)
        {
            aux[i] = new int[M];
            for (auto j = 0; j < M; ++j)
            {
                aux[i][j] = i * M + j;
            }
        }
        mat.swap(aux);

        for (auto i = 0; i < M; ++i)
        {
            for (auto j = 0; j < M; ++j)
            {
                REQUIRE(mat[i][j] == i * M + j);
            }
        }

        for (auto i = 0; i < N; ++i)
        {
            for (auto j = 0; j < N; ++j)
            {
                REQUIRE(aux[i][j] == i * N + j);
            }
        }
    }
}