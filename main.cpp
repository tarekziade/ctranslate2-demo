#include <iostream>
#include <vector>
#include <sstream>
#include <chrono>

#include "ctranslate2/translator.h"
#include "sentencepiece_processor.h"


std::string readFileToString(const std::string& filename) {
    std::ifstream fileStream(filename);
    if (!fileStream.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return "";
    }
    std::stringstream buffer;
    buffer << fileStream.rdbuf();
    fileStream.close();
    return buffer.str();
}

void token2Text(std::string& text) {
    size_t pos = text.find("\u2581");
    while (pos != std::string::npos) {
        text.replace(pos, 3, " "); // Replace 3 characters with a space
        pos = text.find("\u2581", pos + 1);
    }
    pos = text.find("<0x0A>");
    while (pos != std::string::npos) {
        text.replace(pos, 6, "\n"); // Replace 6 characters with newline
        pos = text.find("<0x0A>", pos + 1);
    }
}

int main(int argc, char* argv[]) {
  const char* filename = "sandman.txt";
  std::string fileContent = readFileToString(filename);
  sentencepiece::SentencePieceProcessor processor;
  std::vector<std::string> pieces;

  const auto status = processor.Load("t5-small.spm.model");
  if (!status.ok()) {
     std::cerr << status.ToString() << std::endl;
  }


  processor.Encode(fileContent, &pieces);
  std::vector<std::vector<std::string>> text;
  text.push_back(pieces);

  const std::string model_path("models/falcon-text-summarization-quantized");
  const ctranslate2::models::ModelLoader model_loader(model_path);

  ctranslate2::Translator translator(model_loader);

  auto start = std::chrono::high_resolution_clock::now();
  auto results = translator.translate_batch(text);
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> duration = end - start;

  std::string joinedString = "";
  int tokens = 0;

  for (const auto& token : results[0].output()) {
    joinedString += token;
    tokens++;
  }
  token2Text(joinedString);
  std::cout << joinedString << std::endl;
  std::cout << tokens << " tokens generated (" << std::fixed << std::setprecision(2)
              << (tokens / duration.count()) << " token/s)" << std::endl;
  return 0;
}



