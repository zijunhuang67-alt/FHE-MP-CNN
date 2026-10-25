# Correctness evidence

| Level | Test | Result | Meaning |
|---|---|---|---|
| Parameter | `parameter_probe` | PASS | Exact chain is accepted by SEAL at `tc128` |
| Primitive | `exact_parameter_ckks_smoke` | PASS | Encrypt/add/decrypt error < 1e-6 at exact N/Q/scale |
| Component | repository `compare` unchanged | BUILD FAIL | C++11 conflicts with C++17 SEAL headers |
| Component | diagnostic C++17 invocation | RUN FAIL | transparent ciphertext, exit 134 |
| End-to-end | `cnn 20 10 0 0` | NOT RUN | correctness stop condition plus insufficient RAM |

The two `.cpp` probes are source-controlled within this reproduction package; their binaries are local Linux artifacts and can be rebuilt using the commands in `commands.log`.

