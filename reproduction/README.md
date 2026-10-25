# FHE-MP-CNN 复现包

本目录记录对 arXiv:2106.07229 与官方工件 `snu-ccl/FHE-MP-CNN` 的证据优先复现。任务类型是 **artifact rerun attempt**；当前 Debian/AMD EPYC 平台不是论文声明的 Ubuntu 20.04 环境，因此本机测量只能作为 contextual replication。

## 结论摘要

- 官方源码在精确提交 `a752630b1da3c7ed9e5f7f7a7f9aa817db720fdd` 上成功编译 CNN。
- 代码中的 CKKS 参数通过修改版 SEAL 的 `tc128` 安全检查；精确参数加密/加法/解密最大绝对误差为 `1.95647942e-11`（最终验证运行）。
- 独立 MinimaxReLU 组件原始 CMake 因 C++11/C++17 冲突不能编译；只修正生成构建文件的标准后可编译，但运行触发 `result ciphertext is transparent`，正确性层失败。
- 未运行整网推理：机器只有 33 GiB、无 swap，而 README 建议单图约 384 GB。259 个旋转步按单步 Galois key 的实测未压缩大小线性计算约 251.034 GiB；这是计算估计，不是峰值 RSS。
- arXiv PDF 被出口代理 HTTP 403 拒绝。附件中的 90.67% 准确率和 98.67% 一致率保留为二手声明，尚未逐页核验。

从 [reproduction_report.md](reproduction_report.md) 开始阅读。参数、声明和性能表分别见 [parameter_manifest.csv](parameter_manifest.csv)、[claim_evidence_ledger.csv](claim_evidence_ledger.csv)、[normalized_results.csv](normalized_results.csv)。

