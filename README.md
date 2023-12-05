# Summarization using CTranslate2

This demoes using `CTranslate2` and `sentencepiece` to summarize a text in C++.

Tokenization is done using `t5-small` and then a model is picked to produce a summary.

Make sure you have Python installed (used to download and convert models) and run:

```
make build
make model
make run
```

This will run using `Falconsai/text_summarization` but you can pass any model you want,
as long as you've downloaded and converted (and optionally quantized) it.
See the Makefile.
