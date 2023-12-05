# Summarization using CTranslate2

This demoes using `CTranslate2` and `sentencepiece` to summarize a text in C++.

Tokenization is done using `t5-small` and then a model is picked to produce a summary.

Make sure you have Python installed (used to download and convert models) and run:

```
$ make build
$ make model
$ make run
./build/main -m falcon-text-summarization
Selected model: falcon-text-summarization
Input Text size: 9616
Number of tokens: 2605

The Sandman is a mythical character in European folklore. In Scandinavian folklore, he sprinkles sand or dust on or into the eyes of children at night. The Sandman is a traditional character in many children's stories and books.
61 tokens generated (48.53 token/s)
```

This will run using `Falconsai/text_summarization` but you can pass any model you want,
as long as you've downloaded and converted (and optionally quantized) it.
See the Makefile.
