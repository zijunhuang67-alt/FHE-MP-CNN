# Discrepancy log

## D01 — 论文原文不可达

- 观察：所有 arXiv/ar5iv 下载均被出口代理 403 拒绝。
- 影响：论文表格、版本、硬件、计时边界、安全论述无法做主证据核验。
- 处理：附件数值标为 secondary；相关 claim 为 `not assessable`。

## D02 — COMP 目标的语言标准自相矛盾

- 观察：`COMP` 硬编码 C++11，SEAL fork 以 C++17 构建并暴露 C++17 头文件。
- 单变量测试：仅把外部生成的 `flags.make` 改为 C++17；源码未改，编译通过。
- 结论：基线构建脚本缺陷。

## D03 — MinimaxReLU 组件运行失败

- 观察：诊断性 C++17 构建在计算开始后抛出 `result ciphertext is transparent`，exit 134。
- 控制：`SEAL_THROW_ON_TRANSPARENT_CIPHERTEXT=ON`，未关闭安全检查。
- 结论：正确性层未通过，停止进入该组件性能测量。

## D04 — CIFAR-100 文档/代码不一致

- README 声明支持 CIFAR-100 ResNet-32。
- `run_cnn.cpp` 的 CIFAR-100 dispatch 和 `infer_seal.cpp` 实现均被注释。
- 命令会以 0 退出但只打印参数，不能视为推理成功。

## D05 — 数据覆盖不足

- README 接受 image ID 0–9999；仓库 CIFAR-10 文件只有 1,000 labels 和 3,072,000 values（恰为 1,000×3×32×32）。
- 影响：无法仅凭发布仓库重算标准 10,000-image CIFAR-10 准确率。

## D06 — 资源边界

- 当前 33 GiB RAM、无 swap；README 建议单图约 384 GB。
- 单个 rotation Galois key 未压缩序列化约 0.969 GiB，259 步线性计算约 251.034 GiB。
- 该估计不能替代峰值 RSS；未启动可能 OOM 的整网进程。

