
bin/python:
	python3 -m venv .
	bin/pip install ctranslate2

.PHONY: build
build:
	mkdir -p build
	cd build && cmake -DCMAKE_OSX_ARCHITECTURES=arm64 -DWITH_ACCELERATE=ON -DWITH_MKL=OFF -DOPENMP_RUNTIME=NONE .. &&	make -j4

.PHONY: model
model: bin/python
	mkdir -p models
	bin/ct2-transformers-converter --model Falconsai/text_summarization --output_dir models/falcon-text-summarization-quantized --quantization int8 --force
	bin/ct2-transformers-converter --model Falconsai/text_summarization --output_dir models/falcon-text-summarization --force


.PHONY: run
run:
	CT2_VERBOSE=1 ./build/main -m falcon-text-summarization

.PHONY: run-quantized
run-quantized:
		CT2_VERBOSE=1 ./build/main -m falcon-text-summarization-quantized


