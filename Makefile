
bin/python:
	python3 -m venv .
	bin/pip install ctranslate2

.PHONY: build
build:
	mkdir -p build
	cd build && cmake .. &&	make -j4

.PHONY: model
model: bin/python
	mkdir -p models
	bin/ct2-transformers-converter --model Falconsai/text_summarization --output_dir models/falcon-text-summarization-quantized --quantization int8 --force
	bin/ct2-transformers-converter --model Falconsai/text_summarization --output_dir models/falcon-text-summarization --force


.PHONY: run
run:
	./build/main -m falcon-text-summarization

.PHONY: run-quantized
run-quantized:
		./build/main -m falcon-text-summarization-quantized


