# Source inventory

| 来源 | 状态 | 证据/哈希 | 用途 |
|---|---|---|---|
| 官方 GitHub 仓库 | 已获取 | HEAD `a752630b…`，tree `687690c3…` | 主要代码与数据证据 |
| arXiv PDF 2106.07229 | 阻断 | `arxiv.org`、`export.arxiv.org`、`browse.arxiv.org`、ar5iv 均 HTTP 403 | 论文声明待核验 |
| 用户附件 Markdown | 已获取 | SHA-256 `d227c507…` | 二手路线图，不作为论文原始证据 |
| README | 已冻结 | SHA-256 `f2cc74fb…` | 依赖、运行命令、内存要求 |
| 工件 sample image 0 | 已冻结 | SHA-256 `10394ff8…` | 作者仓库提供的单样本结果，不是本机测量 |
| 工件 label 0 result | 已冻结 | SHA-256 `22824d82…` | 作者仓库提供标签结果 |
| CIFAR-10 labels | 已冻结 | 1,000 entries，SHA-256 `e602a453…` | 数据覆盖审计 |

关键代码定位：

- 参数与推理编排：`sources/FHE-MP-CNN/cnn_ckks/cpu-ckks/single-key/cnn/infer_seal.cpp:251`
- 主入口与 CIFAR-100 注释：`sources/FHE-MP-CNN/cnn_ckks/run/run_cnn.cpp:8`
- 构建标志：`sources/FHE-MP-CNN/cnn_ckks/CMakeLists.txt:45`
- 样例结果：`sources/FHE-MP-CNN/result/resnet20_cifar10_image0.txt`

