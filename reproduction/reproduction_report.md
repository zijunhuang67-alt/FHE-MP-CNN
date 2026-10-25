# FHE-MP-CNN 复现报告

## 1. 判定

本次是 **artifact rerun attempt**。总体判定为 **partially reproduced**：官方 CNN 源码、加密参数和 CKKS 基础正确性已复现；ReLU 组件与整网推理未通过复现门槛；论文 headline accuracy/agreement/performance 为 `not assessable`。

不能把“程序编译成功”或“仓库自带一个正确结果文件”描述为论文结果已复现。

## 2. 已完成证据

### 2.1 版本与构建

官方仓库冻结到 `a752630b1da3c7ed9e5f7f7a7f9aa817db720fdd`。CNN target 在未改源码的情况下完成配置、编译和链接，生成二进制 SHA-256 `b9958f88…`。有效编译参数保留了目标的 `-O0`、C++17、OpenMP 和 `-march=native`。

### 2.2 参数与安全限定

代码使用 RNS-CKKS，`N=65536`，32 个系数模数素数，总计 1552 bit，初始 scale `2^46`，稀疏三元 secret key Hamming weight 192。修改版 SEAL 报告 `parameters_set=true`、`sec_level=tc128`，其该环维度的 128-bit 上限为 1792 bit。

这是“SEAL 内嵌 HE 标准表检查通过”，不是独立 LWE Estimator 复核；后者版本与参数仍为 unknown。

### 2.3 基础正确性

在与 CNN 相同的 N/Q/scale/secret 参数下进行了 6 个值的 CKKS encrypt → add_plain → decrypt → decode。最终验证运行的最大绝对误差为 `1.95647942e-11`，低于预设 `1e-6` 阈值。该结果验证编码、密钥生成、加解密与简单同态运算，不验证 bootstrapping、Remez ReLU 或 CNN。

### 2.4 作者仓库提供的样例

tracked `resnet20_cifar10_image0.txt` 报告 image 0 的真实/预测标签均为 3，总时间 2,188,790 ms；18 次 bootstrapping 合计 1,629,732 ms，占总时间 74.4581%。这些是作者工件内数据，不是本机测量，也不知道其硬件、重复次数或 warm-up。

## 3. 未通过与停止原因

### 3.1 ReLU 组件

原 `COMP` target 使用 C++11，而修改版 SEAL 需要 C++17，原样不能编译。仅在外部生成构建文件中改为 C++17 后可编译，但运行 MinimaxReLU 时抛出 `result ciphertext is transparent` 并退出 134。按正确性优先原则，在此停止性能测量；未关闭该检查，也未改多项式或参数来制造通过结果。

### 3.2 内存

当前机器只有 33 GiB RAM 且无 swap，README 建议单图约 384 GB。精确参数下测得单 rotation Galois key 的未压缩序列化大小为 1,040,714,991 bytes；代码请求 259 个唯一旋转步，简单乘积为约 251.034 GiB。这个计算只说明数量级合理，不能替代完整进程的峰值 RSS。

### 3.3 论文与数据

arXiv PDF 被代理 403 拒绝，因此 90.67% accuracy 和 98.67% exact agreement 只来自用户附件的二手转述。仓库还只带 1,000 张 CIFAR-10 文本输入，不足以直接重算标准 10,000 张测试集指标。需要论文 PDF、完整输入或权威生成流程，以及 plaintext predictions 才能验证 headline claims。

## 4. 性能对照原则

未进行跨 CPU 的频率缩放或归一化。论文平台与计时边界未核验，本机也没有完整 CNN 测量，因此没有可辩护的 head-to-head speedup。`normalized_results.csv` 只并列：二手论文值、作者 tracked 样例、当前基础测试；每项都标注测量边界和来源。

## 5. Claim-level verdict 摘要

| Claim | Verdict |
|---|---|
| 官方 CNN target 可构建 | reproduced |
| 代码参数通过 SEAL tc128 | reproduced |
| 精确参数 CKKS 基础运算正确 | reproduced |
| 独立 MinimaxReLU 组件 | not reproduced |
| 90.67% CIFAR-10 accuracy | not assessable |
| 98.67% FHE/plaintext agreement | not assessable |
| 作者 image0 结果的独立重跑 | not assessable |
| 18 次 bootstrapping 调度 | partially reproduced |
| CIFAR-100 支持 | not reproduced |
| ~384 GB 单图内存 | partially reproduced（数量级证据，非 RSS） |

逐项证据见 `claim_evidence_ledger.csv`。

## 6. 下一步（保持因果变量单一）

1. 用户上传论文 PDF，完成表格、硬件、准确率定义、安全说明与计时边界核验。
2. 在不改参数的情况下，于 Ubuntu 20.04 + ≥384 GiB RAM 平台先复现 `cnn 20 10 0 0`，记录 peak RSS、stdout、结果文件与退出码。
3. 单独调查 transparent-ciphertext：使用作者编译器/SEAL 构建选项复跑 COMP；一次只改变编译器版本或 transparent 检查之一。
4. 获取完整 10,000-image 输入与 plaintext predictions，再计算 accuracy 和 exact agreement。
5. 只有基线正确后，才把降 N/Q、减少旋转步或改变 packing 作为明确标注的 replication/extension。

## 7. 可移交性

全部工作位于 `/workspace/AI project/Codex project`，对应用户给出的 Windows 目标目录名。将该目录下载/同步到 `E:\AI project\Codex project` 即可。源码、探针、原始摘要、参数表、claim ledger、差异日志和命令账本均已保留。

