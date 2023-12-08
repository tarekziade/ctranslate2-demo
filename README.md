# Summarization using CTranslate2

This demoes using `CTranslate2` and `sentencepiece` to summarize a text in C++.

Tokenization is done using `t5-small` and then a model is picked to produce a summary.

Make sure you have Python installed (used to download and convert models) and run:

```
✗ make build
✗ make model

✗ make run-quantized
CT2_VERBOSE=1 ./build/main -m falcon-text-summarization-quantized
Selected model: falcon-text-summarization-quantized
Input Text size: 9616
Number of tokens: 2605

[2023-12-08 13:53:24.167] [ctranslate2] [thread 12139814] [info] CPU: ARM (NEON=true)
[2023-12-08 13:53:24.168] [ctranslate2] [thread 12139814] [info]  - Selected ISA: NEON
[2023-12-08 13:53:24.168] [ctranslate2] [thread 12139814] [info]  - Use Intel MKL: false
[2023-12-08 13:53:24.168] [ctranslate2] [thread 12139814] [info]  - SGEMM backend: Accelerate (packed: false)
[2023-12-08 13:53:24.168] [ctranslate2] [thread 12139814] [info]  - GEMM_S16 backend: none (packed: false)
[2023-12-08 13:53:24.168] [ctranslate2] [thread 12139814] [info]  - GEMM_S8 backend: Ruy (packed: false, u8s8 preferred: false)
[2023-12-08 13:53:24.201] [ctranslate2] [thread 12139814] [info] Loaded model models/falcon-text-summarization-quantized on device cpu:0
[2023-12-08 13:53:24.201] [ctranslate2] [thread 12139814] [info]  - Binary version: 6
[2023-12-08 13:53:24.201] [ctranslate2] [thread 12139814] [info]  - Model specification revision: 7
[2023-12-08 13:53:24.201] [ctranslate2] [thread 12139814] [info]  - Selected compute type: int8_float32
Duration: 0.504883s
The Sandman is a mythical character in European folklore. In Scandinavian folklore, he sprinkles sand or dust on or into the eyes of children at night. The Sandman is a traditional character in many children's stories and books.
61 tokens generated (120.82 token/s)

✗ make run
CT2_VERBOSE=1 ./build/main -m falcon-text-summarization
Selected model: falcon-text-summarization
Input Text size: 9616
Number of tokens: 2605

[2023-12-08 13:53:33.740] [ctranslate2] [thread 12140361] [info] CPU: ARM (NEON=true)
[2023-12-08 13:53:33.741] [ctranslate2] [thread 12140361] [info]  - Selected ISA: NEON
[2023-12-08 13:53:33.741] [ctranslate2] [thread 12140361] [info]  - Use Intel MKL: false
[2023-12-08 13:53:33.741] [ctranslate2] [thread 12140361] [info]  - SGEMM backend: Accelerate (packed: false)
[2023-12-08 13:53:33.741] [ctranslate2] [thread 12140361] [info]  - GEMM_S16 backend: none (packed: false)
[2023-12-08 13:53:33.741] [ctranslate2] [thread 12140361] [info]  - GEMM_S8 backend: Ruy (packed: false, u8s8 preferred: false)
[2023-12-08 13:53:33.833] [ctranslate2] [thread 12140361] [info] Loaded model models/falcon-text-summarization on device cpu:0
[2023-12-08 13:53:33.833] [ctranslate2] [thread 12140361] [info]  - Binary version: 6
[2023-12-08 13:53:33.833] [ctranslate2] [thread 12140361] [info]  - Model specification revision: 7
[2023-12-08 13:53:33.833] [ctranslate2] [thread 12140361] [info]  - Selected compute type: float32
Duration: 1.29597s
The Sandman is a mythical character in European folklore. In Scandinavian folklore, he sprinkles sand or dust on or into the eyes of children at night. The Sandman is a traditional character in many children's stories and books.
61 tokens generated (47.07 token/s)
```

This will run using `Falconsai/text_summarization` but you can pass any model you want,
as long as you've downloaded and converted (and optionally quantized) it.
See the Makefile.
