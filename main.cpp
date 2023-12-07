#include <iostream>
#include <vector>
#include <sstream>
#include <chrono>
#include <unistd.h>

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

std::string cleanup(const std::string& str) {
    std::string cleaned_str = str;
    std::size_t pos = 0;

    // Loop through the string and remove spaces before dots
    while ((pos = cleaned_str.find(" .", pos)) != std::string::npos) {
        cleaned_str.erase(pos, 1); // Remove the space
    }

    // Trim leading whitespace
    cleaned_str.erase(cleaned_str.begin(), std::find_if_not(cleaned_str.begin(), cleaned_str.end(), ::isspace));

    // Trim trailing whitespace
    cleaned_str.erase(std::find_if_not(cleaned_str.rbegin(), cleaned_str.rend(), ::isspace).base(), cleaned_str.end());


    return cleaned_str;
}

int main(int argc, char* argv[]) {
  const char* model = "falcon-text-summarization-quantized";

  int opt;
  while ((opt = getopt(argc, argv, "m:")) != -1) {
      switch (opt) {
          case 'm':
              model = optarg; // Get the value of the option argument
              break;
          default:
              std::cerr << "Usage: " << argv[0] << " -m MODEL" << std::endl;
              return 1;
      }
  }
  std::cout << "Selected model: " << model << std::endl;

  const char* filename = "sandman.txt";
  std::string fileContent = readFileToString(filename);
  std::cout << "Input Text size: " << fileContent.length() << std::endl;

  sentencepiece::SentencePieceProcessor processor;
  std::vector<std::string> pieces;

  const auto status = processor.Load("t5-small.spm.model");
  if (!status.ok()) {
     std::cerr << status.ToString() << std::endl;
  }

  processor.Encode(fileContent, &pieces);
  std::vector<std::vector<std::string>> text;
  std::cout << "Number of tokens: " << pieces.size() << std::endl;
  std::cout << "" << std::endl;

  text.push_back(pieces);

  const std::string model_path("models/" + std::string(model));
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
  std::cout << cleanup(joinedString) << std::endl;
  std::cout << tokens << " tokens generated (" << std::fixed << std::setprecision(2)
              << (tokens / duration.count()) << " token/s)" << std::endl;
  return 0;
}



