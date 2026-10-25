# Environment lock

## 当前测量平台

- OS: Debian GNU/Linux 13.6 (trixie)，kernel 6.18.55，x86_64 KVM。
- CPU: AMD EPYC 9V74，5 vCPU，1 thread/core；`-march=native`。
- RAM: 33 GiB；swap: 0 B。
- Compiler: g++ 14.2.0；glibc 2.41；CMake 3.31.6；Git 2.52.0。
- 构建并行度：5。
- GPU/FPGA/ASIC: 无；纯 CPU。

## 加密库构建

- SEAL fork: 3.6.6，静态库。
- `SEAL_USE_CXX17=ON`
- `SEAL_BUILD_DEPS=ON`
- `SEAL_BUILD_TESTS=OFF`（fork 改了 Evaluator API，但上游测试未同步）
- `SEAL_THROW_ON_TRANSPARENT_CIPHERTEXT=ON`
- `SEAL_USE_GAUSSIAN_NOISE=OFF`（centered binomial，stddev 3.2）
- `SEAL_DEFAULT_PRNG=Blake2xb`
- CNN effective flags: `-O3 -DNDEBUG -w -O0 -std=c++17 -pthread -march=native -fopenmp`；后出现的 `-O0` 生效。

## 平台差异

仓库 README 声明 Ubuntu 20.04 开发/检查。本次不是同 OS、CPU 或内存配置，故本机延迟不得与论文绝对延迟直接比较。论文平台因 PDF 阻断仍为 `unknown`。

