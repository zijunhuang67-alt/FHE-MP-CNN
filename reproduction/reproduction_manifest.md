# Reproduction manifest

## 任务边界

- 主任务：作者工件重跑（artifact rerun attempt）。
- 平台偏差部分：contextual replication；不与论文硬件做 head-to-head 延迟比较。
- 未进行：降低环维度/模数链、修改网络、增加 swap、把 `-O0` 改为 `-O3`。这些会成为 replication/extension，不属于基线。

## 冻结对象

| 对象 | 冻结值 |
|---|---|
| 论文标识 | arXiv:2106.07229；PDF 下载受 HTTP 403 阻断 |
| 官方代码 | `https://github.com/snu-ccl/FHE-MP-CNN.git` |
| 分支/提交 | `main-3.6.6` / `a752630b1da3c7ed9e5f7f7a7f9aa817db720fdd` |
| Git tree | `687690c3a077fdd47dd37b5dfb31238d15ced80e` |
| submodules | 无 |
| 修改版后端 | 仓库内 Microsoft SEAL 3.6.6 fork，同一提交树 |
| NTL | 11.5.1，提交 `91acd5b3a7df709c0d8bf88a99a24bc340dc34f7` |
| 数据 | 仓库自带 CIFAR-10 文本：1,000 labels / 3,072,000 values |
| 权重 | 仓库自带 `pretrained_parameters/`，约 74 MiB |
| 参考附件 | `FHE-MP-CNN复现全流程.md`，SHA-256 `d227c50761d90d04721cf5f6256994db715336aed34651dc00e645252738ca3b` |

## 验证阶梯

1. 源码/构建：通过（CNN target）。
2. 参数合法性与安全限定符：通过（`tc128`）。
3. 精确参数 CKKS 原语：通过。
4. ReLU 组合组件：失败（transparent ciphertext）。
5. 整网单图：未运行，组件正确性与内存均构成停止条件。
6. 准确率/一致率/论文性能：未评估。

## 停止条件

- 正确性在性能层之前失败。
- 33 GiB RAM / 0 swap 与工件 README 的约 384 GB 单图要求不匹配。
- 论文 PDF 无法获取，headline metric 的原始表格、硬件与计时边界不能核验。

